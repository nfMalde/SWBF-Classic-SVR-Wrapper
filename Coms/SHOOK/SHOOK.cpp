#include "SHOOK.h"
#include "stdafx.h"
#include <easyhook.h>
#include <string>
#include <iostream>
#include <Windows.h>

HANDLE m_hChildStd_OUT_Rd = NULL;
HANDLE m_hChildStd_OUT_Wr = NULL;
HANDLE m_hreadDataFromExtProgram = NULL;

HRESULT RunExternalProgram(std::string externalProgram, std::string arguments)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	SECURITY_ATTRIBUTES saAttr;

	ZeroMemory(&saAttr, sizeof(saAttr));
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;

	// Create a pipe for the child process's STDOUT. 

	if (!CreatePipe(&m_hChildStd_OUT_Rd, &m_hChildStd_OUT_Wr, &saAttr, 0))
	{
		// log error
		return HRESULT_FROM_WIN32(GetLastError());
	}

	// Ensure the read handle to the pipe for STDOUT is not inherited.

	if (!SetHandleInformation(m_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0))
	{
		// log error
		return HRESULT_FROM_WIN32(GetLastError());
	}

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.hStdError = m_hChildStd_OUT_Wr;
	si.hStdOutput = m_hChildStd_OUT_Wr;
	si.dwFlags |= STARTF_USESTDHANDLES;

	ZeroMemory(&pi, sizeof(pi));

	std::string commandLine = extProgram + " " + arguments;

	// Start the child process. 
	if (!CreateProcessA(NULL,           // No module name (use command line)
		(TCHAR*)commandLine.c_str(),    // Command line
		NULL,                           // Process handle not inheritable
		NULL,                           // Thread handle not inheritable
		TRUE,                           // Set handle inheritance
		0,                              // No creation flags
		NULL,                           // Use parent's environment block
		NULL,                           // Use parent's starting directory 
		&si,                            // Pointer to STARTUPINFO structure
		&pi)                            // Pointer to PROCESS_INFORMATION structure
		)
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}
	else
	{
		m_hreadDataFromExtProgram = CreateThread(0, 0, readDataFromExtProgram, NULL, 0, NULL);
	}
	return S_OK;
}

DWORD __stdcall readDataFromExtProgram(void* argh)
{
	DWORD dwRead;
	CHAR chBuf[1024];
	BOOL bSuccess = FALSE;

	for (;;)
	{
		bSuccess = ReadFile(m_hChildStd_OUT_Rd, chBuf, 1024, &dwRead, NULL);
		if (!bSuccess || dwRead == 0) continue;

		// Log chBuf

		if (!bSuccess) break;
	}
	return 0;
}




typedef struct IListenerRegistrar IListenerRegistrar, * PIListenerRegistrar;

struct IListenerRegistrar { /* PlaceHolder Structure */
};

typedef IListenerRegistrar(__stdcall* fGameServerListenerRegistrar)();


fGameServerListenerRegistrar origCall;

IListenerRegistrar __stdcall hReg() {
	std::cout << "Registration is Hooked" << std::endl;

	return origCall();
}

extern "C" void __declspec(dllexport) __stdcall NativeInjectionEntryPoint(REMOTE_ENTRY_INFO * inRemoteInfo);

DWORD gFreqOffset = 0;

void __stdcall NativeInjectionEntryPoint(REMOTE_ENTRY_INFO* inRemoteInfo)
{

	 


	std::cout << "SHOOK::NativeInjectionEntryPoint: Injected by process Id: " << inRemoteInfo->HostPID << "\n";
	std::cout << "SHOOK::NativeInjectionEntryPoint: Passed in data size: " << inRemoteInfo->UserDataSize << "\n";


	 

	// Perform hooking
	HOOK_TRACE_INFO hHook = { NULL }; // keep track of our hook
	int ordinal = 5; 
	HMODULE dll = LoadLibrary(L"Galaxy.dll"); 
	LPCSTR f = MAKEINTRESOURCEA(ordinal);
	FARPROC fn = GetProcAddress(dll, f);


	std::cout << "\n";
	std::cout << "SHOOK::NativeInjectionEntryPoint: Win32 GameServerListener found at address: " << fn << "\n";

	origCall = (fGameServerListenerRegistrar)GetProcAddress(dll, f);

	std::cout << "SHOOK: Loaded original function " << origCall << std::endl;


	// Install the hook
	NTSTATUS result = LhInstallHook(
		GetProcAddress(dll, f),
		hReg,
		NULL,
		&hHook);

	if (FAILED(result))
	{
		std::wstring s(RtlGetLastErrorString());
		std::wcout << "NativeInjectionEntryPoint: Failed to install hook: " << s << "\n";
	}
	else
	{
		std::cout << "NativeInjectionEntryPoint: Hook 'myBeepHook installed successfully.\n";
	}

	// If the threadId in the ACL is set to 0,
	// then internally EasyHook uses GetCurrentThreadId()
	ULONG ACLEntries[1] = { 0 };

	// Disable the hook for the provided threadIds, enable for all others
	LhSetExclusiveACL(ACLEntries, 1, &hHook);
	RhWakeUpProcess();

	return;
}