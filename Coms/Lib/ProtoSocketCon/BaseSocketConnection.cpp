#include "pch.h"
#include "BaseSocketConnection.h" 
#include "ProtoSockListener.h"
#include <google/protobuf/message.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h> 
#include <iostream>
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <windows.h>
#include <winsock2.h>
#include <chrono>
#include <thread>
#include "WorkerThread.h"
#include <queue>
#include <vector>
using namespace std;
using namespace google::protobuf::io;


template <google::protobuf::Message* TMessage>
BaseSocketConnection<TMessage>::BaseSocketConnection(int _port) 
{
    port = _port;
    worker = WorkerThread();  
}
template <google::protobuf::Message* TMessage>
BaseSocketConnection<TMessage>::~BaseSocketConnection() 
{
    //Cleanup
    stop();
} 
template <google::protobuf::Message* TMessage>
void BaseSocketConnection<TMessage>::Send(google::protobuf::Message* message)
{ 
 
    worker.doAsync([message] {
        int siz = payload.ByteSize() + 4;
        char* pkt = new char[siz];
        google::protobuf::io::ArrayOutputStream aos(pkt, siz);
        CodedOutputStream* coded_output = new CodedOutputStream(&aos);
        coded_output->WriteVarint32(payload.ByteSize());
        payload.SerializeToCodedStream(coded_output);
        // Package is ready
        senderQueue.push(pkt);
    });

   

}
template <google::protobuf::Message* TMessage>
bool BaseSocketConnection<TMessage>::StartServer()
{ 
    struct addrinfo* result = NULL, * ptr = NULL, hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the local address and port to be used by the server
    iResult = getaddrinfo(NULL, port, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return false;
    }

    SOCKET ListenSocket = INVALID_SOCKET;
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    
    if (ListenSocket == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    _sock = ListenSocket;

    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
        printf("Listen failed with error: %ld\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Launch WorkerThread

    worker.doAsync([] {

        do {
            ClientSocket = INVALID_SOCKET;

            // Accept a client socket
            ClientSocket = accept(ListenSocket, NULL, NULL);
            if (ClientSocket == INVALID_SOCKET) {
                printf("accept failed: %d\n", WSAGetLastError());
                closesocket(ListenSocket);
                WSACleanup();
                return false;
            }

            startListen(ClientSocket);

        } while (true); 
    });

    return true;
}

template <google::protobuf::Message* TMessage>
bool BaseSocketConnection<TMessage>::StartClient() {
    struct addrinfo* result = NULL,
        *ptr = NULL,
        hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;


    iResult = getaddrinfo(NULL, port, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return false;
    }

    SOCKET ConnectSocket = INVALID_SOCKET;
    // Attempt to connect to the first address returned by
    // the call to getaddrinfo
    ptr = result;

    // Create a SOCKET for connecting to server
    SOCKET ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
        ptr->ai_protocol);


    if (ConnectSocket == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return false;
    }

    _sock = ConnectSocket;

    startListen(_sock);


     return true;
}

template <google::protobuf::Message* TMessage>
void BaseSocketConnection<TMessage>::startListen(SOCKET s) 
{
     
    worker.doAsync([senderQueue] {
        do {
            char recvbuf[4];
            int iResult, iSendResult;
            int recvbuflen = 4;

            memset(buffer, '\0', 4);

            iResult = recv(ClientSocket, recvbuf, recvbuflen, MSG_PEEK);

            if (iResult > 0) {
                handleBroadcast(recvbuf);
            }

            std::queue q = senderQueue;
            while (!q.empty()) {

               
                iSendResult = send(ClientSocket, q.pop(), iResult, 0);
                if (iSendResult == SOCKET_ERROR) {
                    printf("send failed: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                    return;
                }
            }

        } while(true);
    });
}

template <google::protobuf::Message* TMessage>
void BaseSocketConnection<TMessage>::handleBroadcast(int csock, char* buff) {
    //Decompress message
    return readBody(csock, readHdr(buff));
}
 
template <google::protobuf::Message* TMessage>
google::protobuf::uint32 BaseSocketConnection<TMessage>::readHdr(char* buf) {
    google::protobuf::uint32 size;
    google::protobuf::io::ArrayInputStream ais(buf, 4);
    CodedInputStream coded_input(&ais);
    coded_input.ReadVarint32(&size);//Decode the HDR and get the size
    cout << "size of payload is " << size << endl;
    return size;
}


template <typename google::protobuf::Message* TMessage>
google::protobuf::Message* BaseSocketConnection<TMessage>::readBody(int csock, google::protobuf::uint32 siz) {
    int bytecount;
    google::protobuf::Message* payload;
    char buffer[siz + 4];//size of the payload and hdr
    //Read the entire buffer including the hdr
    if ((bytecount = recv(csock, (void*)buffer, 4 + siz, MSG_WAITALL)) == -1) {
        fprintf(stderr, "Error receiving data %d\n", errno);
    }
    cout << "Second read byte count is " << bytecount << endl;
    //Assign ArrayInputStream with enough memory 
    google::protobuf::io::ArrayInputStream ais(buffer, siz + 4);
    CodedInputStream coded_input(&ais);
    //Read an unsigned integer with Varint encoding, truncating to 32 bits.
    coded_input.ReadVarint32(&siz);
    //After the message's length is read, PushLimit() is used to prevent the CodedInputStream 
    //from reading beyond that length.Limits are used when parsing length-delimited 
    //embedded messages
    google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(siz);
    //De-Serialize
    payload.ParseFromCodedStream(&coded_input);
    //Once the embedded message has been parsed, PopLimit() is called to undo the limit
    coded_input.PopLimit(msgLimit);

    return payload;
}
template <typename google::protobuf::Message* TMessage>
void BaseSocketConnection<TMessage>::AddListener(const ProtoSockListener<TMessage>* listener) {
    listeners.push_back(listener);
}


template <typename google::protobuf::Message* TMessage>
bool BaseSocketConnection<TMessage>::stop() {
    iResult = shutdown(_sock, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return false;
    }
    
    // cleanup
    closesocket(_sock);
    WSACleanup();
}