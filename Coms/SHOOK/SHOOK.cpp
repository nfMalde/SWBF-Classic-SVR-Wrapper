#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <shlobj.h>
#include <easyhook.h>
#include <string>
#include <fstream> 
#include <stdio.h>
#include "SHOOK.h"
#include "stdafx.h"
extern "C" void __declspec(dllexport) __stdcall NativeInjectionEntryPoint(REMOTE_ENTRY_INFO * inRemoteInfo);

// link with ws2_32.lib
using namespace std;
 
#include "IListenerRegistrar.h";
#include "ExtRegistrar.h";
#include "IGalaxyInitOptions.h"
#include "IListenerType.h";
#include "ExtLobbyCreatedListener.h";
#include "../Lib/SWBFLogger/SWBFLogger.cpp"
#include "IMatchmaking.h" 
#include "ExtMemberStateListener.h"
#include "ExtMemberUpdateListener.h"
#include "ExtLobbyDataListener.h"
#include "IFriends.h"
#include "INetworking.h"
#include "ExtNetworking.h"
#include "ExtLobbyMessageListener.h"
#include "ExtNetworkingListener.h"

#pragma comment(lib, "Ws2_32.lib")
IPCCom com = IPCCom(); 
 
SWBFLogger logger;

void* get_in_addr(struct sockaddr* sa)
{
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in*)sa)->sin_addr);
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

wchar_t* convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}

const  char* xinet_ntop(int af, const void* src, char* dst, socklen_t size)
{
	struct sockaddr_storage ss;
	unsigned long s = size;

	ZeroMemory(&ss, sizeof(ss));
	ss.ss_family = af;

	switch (af) {
	case AF_INET:
		((struct sockaddr_in*)&ss)->sin_addr = *(struct in_addr*)src;
		break;
	case AF_INET6:
		((struct sockaddr_in6*)&ss)->sin6_addr = *(struct in6_addr*)src;
		break;
	default:
		return NULL;
	}
	/* cannot direclty use &size because of strict aliasing rules */
	return (WSAAddressToStringW((struct sockaddr*)&ss, sizeof(ss), NULL, convertCharArrayToLPCWSTR(dst), &s) == 0) ?
		dst : NULL;
} 

typedef IListenerRegistrar*(__cdecl* fListenerRegistrar)();

IListenerRegistrar* HListenerRegistrar() {
	logger.Write("HListenerRegistrar:: Inctercepting ListenerRegistrar.");

	HMODULE dll = LoadLibrary(L"Galaxy.dll");

	if (dll != 0) {
		logger.Write("HListenerRegistrar:: DLL found. Replacing object...");

		fListenerRegistrar f = (fListenerRegistrar)GetProcAddress(dll, "?ListenerRegistrar@api@galaxy@@YAPAVIListenerRegistrar@12@XZ");

		

		ExtRegistrar* extended = new ExtRegistrar(f(), new SWBFLogger());
		logger.Write("HListenerRegistrar:: Object is replaced.");
		return extended;
	}
	logger.Write("Error DLL NOT FOUND");

	return NULL;
}

typedef void(__cdecl* fInit)(IGalaxyInitOptions* initOptions);

/// <summary>
/// Adds the listeners.
/// </summary>
/// <param name="reg">The reg.</param>
/// <param name="m">The m.</param>
/// <param name="friends">The friends.</param>
void AddListeners(IListenerRegistrar* reg, IMatchmaking* m, IFriends* friends, INetworking* networking) {
	logger.Write("Registrering Listeners...");
	//Lobby Created Listener



	ExtLobbyCreatedListener* L_LobbyCreated = new ExtLobbyCreatedListener(reg);
	reg->Register(IListenerType::LOBBY_CREATED, L_LobbyCreated);
	logger.Write("LOBBY_CREATED listener registered.");

	// Lobby Member State Listener

	ExtMemberStateListener* L_LobbyMemberStateChanged = new ExtMemberStateListener(m, friends, networking);
	reg->Register(IListenerType::LOBBY_MEMBER_STATE, L_LobbyMemberStateChanged);
	logger.Write("LOBBY_MEMBER_STATE listener registered.");
	// Lobby Member Updated Listener
	ExtLobbyDataListener* L_LobbyUpdated = new ExtLobbyDataListener(m, friends);
	reg->Register(IListenerType::LOBBY_DATA, L_LobbyUpdated);
	logger.Write("LOBBY_DATA listener registered.");

	ExtLobbyMessageListener* L_LobbyMessage = new ExtLobbyMessageListener(m);
	reg->Register(IListenerType::LOBBY_MESSAGE, L_LobbyMessage);
	logger.Write("LOBBY_MESSAGE listener registered.");

	ExtNetworkingListener* L_NETWORK = new ExtNetworkingListener(networking);
	reg->Register(IListenerType::NETWORKING, L_NETWORK);
	logger.Write("NETWORKING listener registered.");
	

}
typedef IMatchmaking* (__cdecl* fMatchmaking)();
typedef IFriends* (__cdecl* fFriends)();


typedef INetworking* (__cdecl* fNetworking)();
void HInit(IGalaxyInitOptions* initOptions) {
	logger.Write("Init is called");
	//Init is the point where we need to register our events!
	HMODULE dll = LoadLibrary(L"Galaxy.dll");

	if (dll != 0) {
		fInit f = (fInit)GetProcAddress(dll, "?Init@api@galaxy@@YAXABUInitOptions@12@@Z");
		fNetworking fn = (fNetworking)GetProcAddress(dll, "?Networking@api@galaxy@@YAPAVINetworking@12@XZ");

		INetworking* origN = fn();

		f(initOptions);
		logger.Write("Init is finished. Injecting listeners...");

		fListenerRegistrar listenerReg = (fListenerRegistrar)GetProcAddress(dll, "?ListenerRegistrar@api@galaxy@@YAPAVIListenerRegistrar@12@XZ");
		logger.Write("fListenerRegistrar initalized...");
		IListenerRegistrar* register_ = listenerReg();
		logger.Write("IListenerRegistrar* loaded...");
		fMatchmaking m = (fMatchmaking)GetProcAddress(dll, "?Matchmaking@api@galaxy@@YAPAVIMatchmaking@12@XZ");
		logger.Write("fMatchmaking initalized...");
		IMatchmaking* matchmaking = m();
		logger.Write("IMatchmaking* loaded...");
		fFriends _friends =  (fFriends)GetProcAddress(dll, "?Friends@api@galaxy@@YAPAVIFriends@12@XZ");
		logger.Write("_friends initalized...");
		IFriends* friends = _friends();
		logger.Write("IFriends* loaded...");
		AddListeners(register_, matchmaking, friends, origN);
		
		//TODO: Here we install our events!
	}
}
 
INetworking* HNetworking() {
	 
	HMODULE dll = LoadLibrary(L"Galaxy.dll");

	if (dll != 0) {
		fNetworking f = (fNetworking)GetProcAddress(dll, "?Networking@api@galaxy@@YAPAVINetworking@12@XZ");

		INetworking* origN = f();

		return new ExtNetworking(origN); 
	}
}
 

ULONG ACLEntries_HT_LISTENER_REGISTRAR[1] = { 0 };
HOOK_TRACE_INFO HT_LISTENER_REGISTRAR = { NULL };
ULONG ACLEntries_HT_INIT[1] = { 0 };
HOOK_TRACE_INFO HT_INIT = { NULL }; 
ULONG ACLEntries_HT_NETWORKING[1] = { 0 };
HOOK_TRACE_INFO HT_NETWORKING = { NULL };

void _HOOK_Install_Galaxy_Init() {
	logger.Write("Installing Galaxy::API::Init Hook");
	//Init is the point where we need to register our events!
	HMODULE dll = LoadLibrary(L"Galaxy.dll");

	if (dll != 0) {
		NTSTATUS status = LhInstallHook(GetProcAddress(dll, "?Init@api@galaxy@@YAXABUInitOptions@12@@Z"), HInit, NULL, &HT_INIT);

		if (SUCCEEDED(status)) {
			logger.Write("Galaxy::API::Init Hook Installed!");
			LhSetExclusiveACL(ACLEntries_HT_INIT, 1, &HT_INIT);

		}
		else {
			logger.Write("[**ERR**] Error hooking init:");

			wstring ws = wstring(RtlGetLastErrorString());


			logger.Write(string(ws.begin(), ws.end()));
		}
	}

}

void _HOOK_Install_Galaxy_ListenerRegistrar() {
	logger.Write("Installing Hook: ListenerRegistrar");
	HMODULE dll = LoadLibrary(L"Galaxy.dll");

	if (dll != 0) {
		NTSTATUS x = LhInstallHook(GetProcAddress(dll, "?ListenerRegistrar@api@galaxy@@YAPAVIListenerRegistrar@12@XZ"), HListenerRegistrar, NULL, &HT_LISTENER_REGISTRAR);

		if (SUCCEEDED(x)) {
			LhSetExclusiveACL(ACLEntries_HT_LISTENER_REGISTRAR, 1, &HT_LISTENER_REGISTRAR);
			logger.Write("Hook installed: ListenerRegistrar");

		}
		else {
			logger.Write("[**ERR**] Error hooking listener registrar:");

			wstring ws = wstring(RtlGetLastErrorString());
			 

			logger.Write(string(ws.begin(), ws.end()));

			
		}
	}
	
	
}

//?Networking@api@galaxy@@YAPAVINetworking@12@XZ
void _HOOK_Install_Galaxy_Networking() {
	logger.Write("Installing Hook: Networking");
	HMODULE dll = LoadLibrary(L"Galaxy.dll");

	if (dll != 0) {
		NTSTATUS x = LhInstallHook(GetProcAddress(dll, "?Networking@api@galaxy@@YAPAVINetworking@12@XZ"), HNetworking, NULL, &HT_NETWORKING);

		if (SUCCEEDED(x)) {
			LhSetExclusiveACL(ACLEntries_HT_NETWORKING, 1, &HT_NETWORKING);
			logger.Write("Hook installed: Networking");

		}
		else {
			logger.Write("[**ERR**] Error hooking Networking:");

			wstring ws = wstring(RtlGetLastErrorString());


			logger.Write(string(ws.begin(), ws.end()));


		}
	}
}
 

void InstallGalaxyHook() {
	_HOOK_Install_Galaxy_Init();
	//_HOOK_Install_Galaxy_Networking();
	//_HOOK_Install_Galaxy_ListenerRegistrar(); 

}

void __stdcall NativeInjectionEntryPoint(REMOTE_ENTRY_INFO* inRemoteInfo)
{
	 

	logger.Write("Injection Begun....");
	logger.Write("Now hooking Galaxy.dll...");
	InstallGalaxyHook();
	logger.Write("Done. Continue Game...");

	 

	//LhSetExclusiveACL(ACLEntries, 1, &H_SOCK_INFO);
	//LhSetExclusiveACL(ACLEntries, 1, &H_SOCK_RECV_INFO);
 

	RhWakeUpProcess();  
}
