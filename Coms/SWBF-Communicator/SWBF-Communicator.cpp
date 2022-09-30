// SWBF-Communicator.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//
#include <windows.h>
#include <iostream>

#include <shlobj.h>
#include <filesystem>

#include <fstream> 
#include <easyhook.h>
#include "../Lib/SWBFLogger/SWBFLogger.cpp"

using namespace std; 
SWBFLogger l;
vector<int> savedMessages;
void ClearIPC() {
    cout << "Clearing Interact IPC Buffer" << endl;
    l.Clear();
}

void HandleInteractionMessages() {
   

    while (true)
    {
        vector<swbf::LogMessage> messages = l.GetMessages();
        for(swbf::LogMessage msg:messages) {
            if (std::find(savedMessages.begin(), savedMessages.end(), msg.id()) != savedMessages.end())
                continue;
            else
            {
                cout << "[IPC][LOG][ " << msg.date() << "]" << msg.message() << endl;
                savedMessages.push_back(msg.id());
            }
        }

        if (l.GetMessageCount() > 1000) {
            l.Clear();
        }
       

        Sleep(1000);
    }
}

inline bool ex(const std::string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

std::wstring to_wide(const std::string& multi) {
    std::wstring wide; wchar_t w; mbstate_t mb{};
    size_t n = 0, len = multi.length() + 1;
    while (auto res = mbrtowc(&w, multi.c_str() + n, len - n, &mb)) {
        if (res == size_t(-1) || res == size_t(-2))
            throw "invalid encoding";

        n += res;
        wide += w;
    }
    return wide;
}

int main(int argc, char** argv)
{
   
    ClearIPC();


    //fstream input("swbfipccommunicator.gipc", ios::in | ios::binary);
    //if (!input) {
    //    cout << "swbfipccommunicator.gipc" << ": File not found.  Creating a new file." << endl;
    //}
    //else if (!interact.ParseFromIstream(&input)) {
    //    cerr << "Failed to parse address book." << endl;
    //    return -1;
    //}


    std::cout << "Starting SWBF Classic Com Services..." << std::endl;



    if (argc >= 3) {
        std::string exePath(argv[1]);
        exePath.append("\\Battlefront.exe");

        std::string serverArgs(argv[2]);

        std::cout << "Launching Server with args " << exePath << " " << serverArgs << "..." << std::endl;
        
        std::string launchP(exePath);
        launchP.append(" ");
        launchP.append(serverArgs);

        WCHAR* dllToInject = (WCHAR*)L"..\\..\\Release\\SHOOK.dll";

        
        std::cout << "Trying to find injection library..." << std::endl;
        std::string f("..\\..\\Release\\SHOOK.dll");

        if (!ex(f)) {
            std::cout << "Error: DLL not found: " << L"..\\..\\Release\\SHOOK.dll";

            return -1;
        }
        DWORD freqOffset = 0;
        ULONG processId = 0;
        std::wstring wide_string = std::wstring(exePath.begin(), exePath.end());    
        std::wstring wide_string2 = std::wstring(L"/win /norender /noteamdamage /autonet dedicated /resolution 320 240 /nosound /noaim /tps 57 /gamename NoAI NoCP /playerlimit 12 /playercount 0 /bots 0 /difficulty 1 /throttle 3072 /spawn 5 bes2r 100 100 bes2a 100 100");

        WCHAR* exe_ = (WCHAR*)wide_string.c_str();
        WCHAR* arg = (WCHAR*)wide_string2.c_str();
        wstring exeWS = to_wide(exePath);
        WCHAR* tt = (WCHAR*)exeWS.c_str();
        WCHAR* t2 = (WCHAR*)L"C:\\Gaming\\Steam\\steamapps\\common\\Star Wars Battlefront (Classic 2004)\\GameData\\Battlefront.exe";
        WCHAR* t3 = (WCHAR*)L"/win /norender /noteamdamage /autonet dedicated /resolution 320 240 /nosound /noaim /tps 57 /gamename STEST /playerlimit 12 /playercount 0 /bots 0 /difficulty 1 /throttle 3072 /sideselect /password foora /spawn 5 bes2r 100 100 bes2a 100 100";
        cout << tt << endl;
 

         // additional information
        STARTUPINFO si;
        PROCESS_INFORMATION pi;

        // set the size of the structures
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));
 

        string str = string("/win /norender /noteamdamage /autonet dedicated /resolution 320 240 /nosound /noaim /tps 57 /gamename NoAI NoCP /playerlimit 12 /playercount 0 /bots 0 /difficulty 1 /throttle 3072 /spawn 5 bes2r 100 100 bes2a 100 100");        // Command line

        LPSTR s = const_cast<char*>(str.c_str());
        std::wcout << "Enter the target process Id: (0=create new)";
        std::cin >> processId;
        
        if (processId > 0) {
            // Inject dllToInject into the target process Id, passing 
        // freqOffset as the pass through data.
            NTSTATUS nt = RhInjectLibrary(
                processId,   // The process to inject into
                0,           // ThreadId to wake up upon injection
                EASYHOOK_INJECT_DEFAULT,
                dllToInject, // 32-bit
                NULL,		 // 64-bit not provided
                NULL, // data to send to injected DLL entry point
                NULL// size of data to send
            );

            if (nt != 0)
            {
                printf("RhInjectLibrary failed with error code = %d\n", nt);
                PWCHAR err = RtlGetLastErrorString();
                std::wcout << err << "\n";
            }
            else
            {
                std::wcout << L"Library injected successfully.\n";
            }
        }
        else {
            NTSTATUS nt = RhCreateAndInject(
                t2,
                t3,
                NULL,
                EASYHOOK_INJECT_DEFAULT,
                dllToInject, // 32-bit
                NULL,		 // 64-bit not provided
                &freqOffset, // data to send to injected DLL entry point
                sizeof(DWORD),// size of data to send
                &processId
            );

            if (nt != 0)
            {
                printf("RhInjectLibrary failed with error code = %d\n", nt);
                PWCHAR err = RtlGetLastErrorString();
                std::wcout << err << "\n";
            }
            else
            {
                std::wcout << L"Library injected successfully.\n";
            }
        }

        HandleInteractionMessages();

    }
 

    return -1;
}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
