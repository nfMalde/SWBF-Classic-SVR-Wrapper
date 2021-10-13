// SWBFLogger.cpp : Hiermit werden die Funktionen für die statische Bibliothek definiert.
//

#include "pch.h"
#include "framework.h"
#include <string>
#include "swbflogger.pb.h"
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <shlobj.h>
#include <fstream>
using namespace std;

#ifndef SWBFLogger_HEADER
#define SWBFLogger_HEADER

class SWBFLogger {
private:
	string ipcPath;
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
			std::string path = std::string(my_documents);
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
	void init() {
		ipcPath = handleIPCPath("SWBFLOGGER");
	}

	std::string currentDateTime() {
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		localtime_s(&tstruct, &now);
		// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
		// for more information about date/time format
		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

		return buf;
	}

	void SetMessage(int id, string message, swbf::LogMessage* logmsg) {
		string datestr = currentDateTime();
		logmsg->set_id(id);
		logmsg->set_date(datestr);
		logmsg->set_message(message);

	}
public:
	SWBFLogger() {
		init();
	}

	

	void Clear() {
		swbf::Logger l;

		{
			// Read the existing address book.
			fstream input(ipcPath, ios::in | ios::binary);
			if (!input) {

			}
			else if (!l.ParseFromIstream(&input)) {
				cerr << "Failed to parse address book." << endl;

			}
		}

		l.clear_logmessages();

		{
			// Write the new address book back to disk.
			fstream output(ipcPath, ios::out | ios::trunc | ios::binary);
			if (!l.SerializeToOstream(&output)) {
				cerr << "Failed to write address book." << endl;
			}
		}
	}

	void Write(std::string message) {
		swbf::Logger l;

		{
			// Read the existing address book.
			fstream input(ipcPath, ios::in | ios::binary);
			if (!input) {

			}
			else if (!l.ParseFromIstream(&input)) {
				cerr << "Failed to parse address book." << endl;

			}
		}

		SetMessage(l.logmessages_size()+1,message, l.add_logmessages());

		{
			// Write the new address book back to disk.
			fstream output(ipcPath, ios::out | ios::trunc | ios::binary);
			if (!l.SerializeToOstream(&output)) {
				cerr << "Failed to write address book." << endl;
			}
		}


	}

	vector<swbf::LogMessage> GetMessages() {
		vector<swbf::LogMessage> queue;

		swbf::Logger l;

		{
			// Read the existing address book.
			fstream input(ipcPath, ios::in | ios::binary);
			if (!input) {

			}
			else if (!l.ParseFromIstream(&input)) {
				cerr << "Failed to parse address book." << endl;

			}
		}

		for (int j = 0; j <l.logmessages_size(); j++) {
				
			queue.push_back(l.logmessages(j));
		
		}

		return queue;
	}

	int GetMessageCount() {
		swbf::Logger l;

		{
			// Read the existing address book.
			fstream input(ipcPath, ios::in | ios::binary);
			if (!input) {

			}
			else if (!l.ParseFromIstream(&input)) {
				cerr << "Failed to parse address book." << endl;

			}
		}

		return l.logmessages_size();
	}


};
#endif