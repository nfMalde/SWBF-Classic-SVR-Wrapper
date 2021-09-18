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

#include "IPCCommucator.h" 
#include "IListenerRegistrar.h";
#include "ExtRegistrar.h";
#include "IGalaxyInitOptions.h"
#include "IListenerType.h";
#include "ExtLobbyCreatedListener.h";

#pragma comment(lib, "Ws2_32.lib")
IPCCom com = IPCCom();
 
 

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
	com.sendMessage("HListenerRegistrar:: Inctercepting ListenerRegistrar.");

	HMODULE dll = LoadLibrary(L"Galaxy.dll");

	if (dll != 0) {
		com.sendMessage("HListenerRegistrar:: DLL found. Replacing object...");

		fListenerRegistrar f = (fListenerRegistrar)GetProcAddress(dll, "?ListenerRegistrar@api@galaxy@@YAPAVIListenerRegistrar@12@XZ");

		

		ExtRegistrar* extended = new ExtRegistrar(f(), new IPCCom());
		com.sendMessage("HListenerRegistrar:: Object is replaced.");
		return extended;
	}
	com.sendMessage("Error DLL NOT FOUND");

	return NULL;
}

typedef void(__cdecl* fInit)(IGalaxyInitOptions* initOptions);

void AddListeners(IListenerRegistrar* reg) {
	 
	//Lobby Created Listener
	ExtLobbyCreatedListener* L_LobbyCreated = new ExtLobbyCreatedListener();
	reg->Register(IListenerType::LOBBY_CREATED, L_LobbyCreated);
	

}

void HInit(IGalaxyInitOptions* initOptions) {
	com.sendMessage("Init is called");
	//Init is the point where we need to register our events!
	HMODULE dll = LoadLibrary(L"Galaxy.dll");

	if (dll != 0) {
		fInit f = (fInit)GetProcAddress(dll, "?Init@api@galaxy@@YAXABUInitOptions@12@@Z");

		f(initOptions);
		fListenerRegistrar listenerReg = (fListenerRegistrar)GetProcAddress(dll, "?ListenerRegistrar@api@galaxy@@YAPAVIListenerRegistrar@12@XZ");
		AddListeners(listenerReg());
		
		//TODO: Here we install our events!
	}
}

ULONG ACLEntries_HT_LISTENER_REGISTRAR[1] = { 0 };
HOOK_TRACE_INFO HT_LISTENER_REGISTRAR = { NULL };
ULONG ACLEntries_HT_INIT[1] = { 0 };
HOOK_TRACE_INFO HT_INIT = { NULL };
void _HOOK_Install_Galaxy_Init() {
	com.sendMessage("Installing Galaxy::API::Init Hook");
	//Init is the point where we need to register our events!
	HMODULE dll = LoadLibrary(L"Galaxy.dll");

	if (dll != 0) {
		NTSTATUS status = LhInstallHook(GetProcAddress(dll, "?Init@api@galaxy@@YAXABUInitOptions@12@@Z"), HInit, NULL, &HT_INIT);

		if (SUCCEEDED(status)) {
			com.sendMessage("Galaxy::API::Init Hook Installed!");
			LhSetExclusiveACL(ACLEntries_HT_INIT, 1, &HT_INIT);

		}
		else {
			com.sendMessage("[**ERR**] Error hooking init:");

			wstring ws = wstring(RtlGetLastErrorString());


			com.sendMessage(string(ws.begin(), ws.end()));
		}
	}

}

void _HOOK_Install_Galaxy_ListenerRegistrar() {
	com.sendMessage("Installing Hook: ListenerRegistrar");
	HMODULE dll = LoadLibrary(L"Galaxy.dll");

	if (dll != 0) {
		NTSTATUS x = LhInstallHook(GetProcAddress(dll, "?ListenerRegistrar@api@galaxy@@YAPAVIListenerRegistrar@12@XZ"), HListenerRegistrar, NULL, &HT_LISTENER_REGISTRAR);

		if (SUCCEEDED(x)) {
			LhSetExclusiveACL(ACLEntries_HT_LISTENER_REGISTRAR, 1, &HT_LISTENER_REGISTRAR);
			com.sendMessage("Hook installed: ListenerRegistrar");

		}
		else {
			com.sendMessage("[**ERR**] Error hooking listener registrar:");

			wstring ws = wstring(RtlGetLastErrorString());
			 

			com.sendMessage(string(ws.begin(), ws.end()));

			
		}
	}
	
	
}


void InstallGalaxyHook() {
	_HOOK_Install_Galaxy_Init();
	_HOOK_Install_Galaxy_ListenerRegistrar();

}

void __stdcall NativeInjectionEntryPoint(REMOTE_ENTRY_INFO* inRemoteInfo)
{


	com.sendMessage("Injection Begun....");
	com.sendMessage("Now hooking Galaxy.dll...");
	InstallGalaxyHook();
	com.sendMessage("Done. Continue Game...");

	 

	//LhSetExclusiveACL(ACLEntries, 1, &H_SOCK_INFO);
	//LhSetExclusiveACL(ACLEntries, 1, &H_SOCK_RECV_INFO);
 

	RhWakeUpProcess();  
}
