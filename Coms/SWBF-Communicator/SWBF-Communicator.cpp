// SWBF-Communicator.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <easyhook.h>
#include <stdlib.h>
#include <string>

inline bool ex(const std::string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

int main(int argc, char** argv)
{
    // 0 = Path To Battlefront.exe
    // 1 = Server Args

 

    std::cout << "Starting SWBF Classic Server Wrapper..." << std::endl;
 
    if (argc >= 3) {
        std::string exePath(argv[1]);
        exePath.append("\\Battlefront.exe");

        std::string serverArgs(argv[2]);

        std::cout << "Launching Server with args " << exePath << " " << serverArgs << "..." << std::endl;
        
        std::string launchP(exePath);
        launchP.append(" ");
        launchP.append(serverArgs);

        WCHAR* dllToInject = (WCHAR*)L"..\\..\\Debug\\SHOOK.dll";

        
        std::cout << "Trying to find injection library..." << std::endl;
        std::string f("..\\..\\Debug\\SHOOK.dll");

        if (!ex(f)) {
            std::cout << "Error: DLL not found: " << L"..\\..\\Debug\\SHOOK.dll";

            return -1;
        }
        DWORD freqOffset = 0;
        ULONG processId = 0;
        std::wstring wide_string = std::wstring(exePath.begin(), exePath.end());    
        std::wstring wide_string2 = std::wstring(L"/win /norender /noteamdamage /autonet dedicated /resolution 320 240 /nosound /noaim /tps 57 /gamename NoAI NoCP /playerlimit 12 /playercount 0 /bots 0 /difficulty 1 /throttle 3072 /spawn 5 bes2r 100 100 bes2a 100 100");

        WCHAR* exe_ = (WCHAR*)wide_string.c_str();
        WCHAR* arg = (WCHAR*)wide_string2.c_str();

        RhCreateAndInject(
            exe_,
            arg,
            NULL,
            EASYHOOK_INJECT_DEFAULT,
            dllToInject, // 32-bit
            NULL,		 // 64-bit not provided
            &freqOffset, // data to send to injected DLL entry point
            sizeof(DWORD),// size of data to send
            &processId
        );

        

        std::cout << "Process started as id " << processId << std::endl; 
       
        while (true)
        {
            std::cout << "Waiting for close..." << std::endl;
            Sleep(5000);

        }


        return 0;

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
