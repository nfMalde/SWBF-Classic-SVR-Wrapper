#pragma once
#include <string> 
#include "ProtoSockListener.h"
#include <google/protobuf/message.h>
#include "WorkerThread.h"
#include <queue>
#include "WinSock2.h"
#include <vector>
/// <summary>
/// /
/// </summary>
template <google::protobuf::Message* TMessage>
class BaseSocketConnection
{
	 
public:	
	
	/// <summary>
	/// Initializes a new instance of the <see cref="BaseSocketConnection"/> class.
	/// </summary>
	/// <param name="port">The port.</param>
	BaseSocketConnection(int _port);
	~BaseSocketConnection();

	void Send(google::protobuf::Message* message);

	void AddListener(const ProtoSockListener<TMessage>* listener);
	
	bool StartServer();

	bool StartClient();


private: 
	/// <summary>
	/// The port
	/// </summary>
	int port;
	bool isServer;
	WorkerThread worker;
	SOCKET _sock; // Server or Client socket
	std::vector<ProtoSockListener> listeners;

	const std::queue<char> senderQueue;
	 
	bool stop(); 
	void startListen(SOCKET s);
	void handleBroadcast(int csock, char* buff);
	google::protobuf::uint32 readHdr(char* buf);
	google::protobuf::Message* readBody(int csock, google::protobuf::uint32 siz);
}; 
