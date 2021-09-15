
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <shlobj.h>
#include "SHOOK.h"
#include "stdafx.h"
#include <easyhook.h>
#include <string>
#include <fstream>
#include "swbf.pb.h"  
#include "GalaxyIDH.h"  


// link with ws2_32.lib
using namespace std;

#pragma comment(lib, "Ws2_32.lib")
template <typename T>
std::string tostring(const T& t)
{
	std::ostringstream ss;
	ss << t;
	return ss.str();
}

 

int dirExists(const char* path)
{
	struct stat info;

	if (stat(path, &info) != 0)
		return 0;
	else if (info.st_mode & S_IFDIR)
		return 1;
	else
		return 0;
}

string handleIPCPath(const char* ipcHandleName) {
	CHAR my_documents[MAX_PATH];
	HRESULT result = SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);

	if (result != S_OK)
		std::cout << "Error: " << result << "\n";
	else {
		std::string path = std::string("C:\\ipc");
		path = path.append("\\");
		path = path.append("SWBF-ServerMgr");

		if (!dirExists(path.c_str())) {
			std::cout << "Creating directoy " << path << std::endl;
			CreateDirectoryA(path.c_str(), NULL);
		}

		path = path.append("\\Data");

		if (!dirExists(path.c_str())) {
			std::cout << "Creating directoy " << path << std::endl;
			CreateDirectoryA(path.c_str(), NULL);
		}

		std::cout << "Path completed. Creating IPC Headers and File...";
		path = path.append("\\");
		path = path.append(ipcHandleName);
		path = path.append(".ipc-file");
		return path;
	}
	return "";
}


void sendMessage(string msg) {
	string ipcpath = handleIPCPath("interact");
	cout << "Reading IPC Interact" << endl;

	swbf::Interact  interaction;
	{
		// Read the existing address book.
		fstream input(ipcpath, ios::in | ios::binary);
		if (!input) {
			cout << "No Messages so far..." << endl;



		}
		else if (!interaction.ParseFromIstream(&input)) {
			cerr << "Failed to parse address book." << endl;
			return;
		}
	}

	interaction.add_textmessages(msg);
	// Write the new address book back to disk.
	fstream output(ipcpath, ios::out | ios::trunc | ios::binary);
	if (!interaction.SerializeToOstream(&output)) {
		cout << "Failed to write ipc." << endl;
		return;
	}

}
extern "C" void __declspec(dllexport) __stdcall NativeInjectionEntryPoint(REMOTE_ENTRY_INFO * inRemoteInfo);

enum ListenerType
{
	LISTENER_TYPE_BEGIN,
	LOBBY_LIST = LISTENER_TYPE_BEGIN,
	LOBBY_CREATED,
	LOBBY_ENTERED,
	LOBBY_LEFT,
	LOBBY_DATA,
	LOBBY_MEMBER_STATE,
	LOBBY_OWNER_CHANGE,
	AUTH,
	LOBBY_MESSAGE,
	NETWORKING,
	USER_DATA,
	USER_STATS_AND_ACHIEVEMENTS_RETRIEVE,
	STATS_AND_ACHIEVEMENTS_STORE,
	ACHIEVEMENT_CHANGE,
	LEADERBOARDS_RETRIEVE,
	LEADERBOARD_ENTRIES_RETRIEVE,
	LEADERBOARD_SCORE_UPDATE_LISTENER,
	PERSONA_DATA_CHANGED,
	RICH_PRESENCE_CHANGE_LISTENER,
	GAME_JOIN_REQUESTED_LISTENER,
	OPERATIONAL_STATE_CHANGE,
	FRIEND_LIST_RETRIEVE,
	ENCRYPTED_APP_TICKET_RETRIEVE,
	ACCESS_TOKEN_CHANGE,
	LEADERBOARD_RETRIEVE,
	SPECIFIC_USER_DATA,
	INVITATION_SEND,
	RICH_PRESENCE_LISTENER,
	GAME_INVITATION_RECEIVED_LISTENER,
	NOTIFICATION_LISTENER,
	LOBBY_DATA_RETRIEVE,
	USER_TIME_PLAYED_RETRIEVE,
	OTHER_SESSION_START,
	FILE_SHARE,
	SHARED_FILE_DOWNLOAD,
	CUSTOM_NETWORKING_CONNECTION_OPEN,
	CUSTOM_NETWORKING_CONNECTION_CLOSE,
	CUSTOM_NETWORKING_CONNECTION_DATA,
	OVERLAY_INITIALIZATION_STATE_CHANGE,
	OVERLAY_VISIBILITY_CHANGE,
	CHAT_ROOM_WITH_USER_RETRIEVE_LISTENER,
	CHAT_ROOM_MESSAGE_SEND_LISTENER,
	CHAT_ROOM_MESSAGES_LISTENER,
	FRIEND_INVITATION_SEND_LISTENER,
	FRIEND_INVITATION_LIST_RETRIEVE_LISTENER,
	FRIEND_INVITATION_LISTENER,
	FRIEND_INVITATION_RESPOND_TO_LISTENER,
	FRIEND_ADD_LISTENER,
	FRIEND_DELETE_LISTENER,
	CHAT_ROOM_MESSAGES_RETRIEVE_LISTENER,
	USER_FIND_LISTENER,
	NAT_TYPE_DETECTION,
	SENT_FRIEND_INVITATION_LIST_RETRIEVE_LISTENER,
	LOBBY_DATA_UPDATE_LISTENER,
	LOBBY_MEMBER_DATA_UPDATE_LISTENER,
	USER_INFORMATION_RETRIEVE_LISTENER,
	RICH_PRESENCE_RETRIEVE_LISTENER,
	GOG_SERVICES_CONNECTION_STATE_LISTENER,
	TELEMETRY_EVENT_SEND_LISTENER,
	LISTENER_TYPE_END
};

 enum LobbyCreateResult
{
	LOBBY_CREATE_RESULT_SUCCESS,
	LOBBY_CREATE_RESULT_ERROR,
	LOBBY_CREATE_RESULT_CONNECTION_FAILURE
}; 

class MyListener {
public:
	void OnLobbyCreated(const void* lobbyID, void* result) {
		sendMessage("Lobby created:");
		 
	} 

	static ListenerType GetListenerType() {
		return ListenerType::LOBBY_CREATED;
	}
};


class NetworkingL {
	void OnP2PPacketAvailable(uint32_t msgSize, uint8_t channel) {
		sendMessage("Packaged available");
	}

	static ListenerType GetListenerType() {
		return ListenerType::NETWORKING;
	}
}; 

extern struct IListenerRegistrar { /* PlaceHolder Structure */
	void Register(void* listenerType, void* listener);
	void Unregister(void* listenerType, void* listener);
};


void IListenerRegistrar::Register(void* listenerType, void* listener)
{
	 
	 

}



void IListenerRegistrar::Unregister(void* listenerType, void* listener)
{
}

class MyListener2 {
public:
	void OnLobbyCreated(void* lobbyID, void* result) {
		sendMessage("Lobby created:");

	}

	static int GetListenerType() {
		return 1;
	}
};

typedef IListenerRegistrar(__cdecl* fListenerRegistrar)();
fListenerRegistrar origCall;

typedef void(__cdecl* gInit)(void* param_1);

gInit initCall;

typedef int(__stdcall* fConnect)(SOCKET s, sockaddr* name, int namelen);
fConnect conCall;

IListenerRegistrar hListener() {
	sendMessage("Listener called!");
	
	return origCall();
};
 

int Hconnect(SOCKET s, sockaddr* name, int namelen) {
	char hostname[NI_MAXHOST];
	char servInfo[NI_MAXSERV];

	getnameinfo((struct sockaddr*)&name,
		sizeof(struct sockaddr),
		hostname,
		NI_MAXHOST, servInfo, NI_MAXSERV, NI_NUMERICSERV); 
	
	sendMessage("Socket Connection Started:"); 
	sendMessage(hostname);
	sendMessage(servInfo);

	return conCall(s, name, namelen);
}

void __stdcall NativeInjectionEntryPoint(REMOTE_ENTRY_INFO* inRemoteInfo)
{
	
	// 


	//std::cout << "SHOOK::NativeInjectionEntryPoint: Injected by process Id: " << inRemoteInfo->HostPID << "\n";
	//std::cout << "SHOOK::NativeInjectionEntryPoint: Passed in data size: " << inRemoteInfo->UserDataSize << "\n";


	// 

	//// Perform hooking
	//HOOK_TRACE_INFO hHook = { NULL }; // keep track of our hook
	//int ordinal = 5; 
	//HMODULE dll = LoadLibrary(L"Galaxy.dll"); 
	//LPCSTR f = MAKEINTRESOURCEA(ordinal);
	//FARPROC fn = GetProcAddress(dll, f);


	//std::cout << "\n";
	//std::cout << "SHOOK::NativeInjectionEntryPoint: Win32 GameServerListener found at address: " << fn << "\n";

	//origCall = (fGameServerListenerRegistrar)GetProcAddress(dll, f);

	//std::cout << "SHOOK: Loaded original function " << origCall << std::endl;


	//// Install the hook
	///*NTSTATUS result = LhInstallHook(
	//	GetProcAddress(dll, f),
	//	hReg,
	//	NULL,
	//	&hHook);

	//if (FAILED(result))
	//{
	//	std::wstring s(RtlGetLastErrorString());
	//	std::wcout << "NativeInjectionEntryPoint: Failed to install hook: " << s << "\n";
	//}
	//else
	//{
	//	std::cout << "NativeInjectionEntryPoint: Hook 'myBeepHook installed successfully.\n";
	//}*/

	//// If the threadId in the ACL is set to 0,
	//// then internally EasyHook uses GetCurrentThreadId()
	//ULONG ACLEntries[1] = { 0 };

	//// Disable the hook for the provided threadIds, enable for all others
	//LhSetExclusiveACL(ACLEntries, 1, &hHook);

	  


	//sendMessage("Hello from inside the swbf client.");
	HMODULE dll = LoadLibrary(L"WS2_32.dll");


	HOOK_TRACE_INFO hHook = { NULL }; // keep track of our hook


	if (dll) {
		try {

			bool found = false;
			//void __cdecl galaxy::api::Init(InitOptions *param_1)
		while (!found) {
		 
		 
			FARPROC addressConnect = GetProcAddress(dll, "connect");

			//sendMessage("Found ListenerRegistrar at address");
			//sendMessage(string());

			//sendMessage("Trying to call...");
			if (NULL != addressConnect) {
				conCall = (fConnect)GetProcAddress(dll, "connect");
				//sendMessage("Orig Call Found. Ready.");
				found = true;
			}

			int ordinalListener = 15;

			LPCSTR fListener = MAKEINTRESOURCEA(ordinalListener);

			origCall = (fListenerRegistrar)GetProcAddress(dll, fListener);

			NTSTATUS result = LhInstallHook(
				GetProcAddress(dll, "connect"),
				Hconnect,
				NULL,
				&hHook);
			

			
			Sleep(1000);
		}

	


		/*if (origCall)
		//sendMessage("Sending...");


		ListenerType t = ListenerType::LOBBY_CREATED;
		result.Register(t, new MyListener());*/

		//sendMessage("Hook is installed.");
		}
		catch (const std::exception& e) { 
				
			//sendMessage("Register call failed");
			//sendMessage(string(e.what()));
		
		}
		sendMessage("OK");
	}

	// If the threadId in the ACL is set to 0,
	// then internally EasyHook uses GetCurrentThreadId()
	ULONG ACLEntries[1] = { 0 };

	// Disable the hook for the provided threadIds, enable for all others
	LhSetExclusiveACL(ACLEntries, 1, &hHook);
	 

	// Now register listeners:


	RhWakeUpProcess(); 

	 
	
	return;
}
