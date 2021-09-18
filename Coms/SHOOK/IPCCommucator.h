#pragma once
#include "swbf.pb.h"
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
using namespace std;

namespace {

	class IPCCom
	{


	public:
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

	private:
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

				if (!this->dirExists(path.c_str())) {
					std::cout << "Creating directoy " << path << std::endl;
					CreateDirectoryA(path.c_str(), NULL);
				}

				path = path.append("\\Data");

				if (!this->dirExists(path.c_str())) {
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
	};
}

