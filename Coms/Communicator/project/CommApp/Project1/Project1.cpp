// Project1.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <windows.h>
#include <iostream>
#include <shlobj.h>
#include <filesystem> 
#include <fileapi.h>
#include "addressbook.pb.h"
#include <fstream>
using namespace std;

void ListPeople(const tutorial::AddressBook& address_book) {
    for (int i = 0; i < address_book.people_size(); i++) {
        const tutorial::Person& person = address_book.people(i);

        cout << "Person ID: " << person.id() << endl;
        cout << "  Name: " << person.name() << endl;
        if (person.has_email()) {
            cout << "  E-mail address: " << person.email() << endl;
        }

        for (int j = 0; j < person.phones_size(); j++) {
            const tutorial::Person::PhoneNumber& phone_number = person.phones(j);

            switch (phone_number.type()) {
            case tutorial::Person::MOBILE:
                cout << "  Mobile phone #: ";
                break;
            case tutorial::Person::HOME:
                cout << "  Home phone #: ";
                break;
            case tutorial::Person::WORK:
                cout << "  Work phone #: ";
                break;
            }
            cout << phone_number.number() << endl;
        }
    }
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

void PromptForAddress(tutorial::Person* person) {
    cout << "Enter person ID number: ";
    int id;
    cin >> id;
    person->set_id(id);
    cin.ignore(256, '\n');

    cout << "Enter name: ";
    getline(cin, *person->mutable_name());

    cout << "Enter email address (blank for none): ";
    string email;
    getline(cin, email);
    if (!email.empty()) {
        person->set_email(email);
    }

    while (true) {
        cout << "Enter a phone number (or leave blank to finish): ";
        string number;
        getline(cin, number);
        if (number.empty()) {
            break;
        }

        tutorial::Person::PhoneNumber* phone_number = person->add_phones();
        phone_number->set_number(number);

        cout << "Is this a mobile, home, or work phone? ";
        string type;
        getline(cin, type);
        if (type == "mobile") {
            phone_number->set_type(tutorial::Person::MOBILE);
        }
        else if (type == "home") {
            phone_number->set_type(tutorial::Person::HOME);
        }
        else if (type == "work") {
            phone_number->set_type(tutorial::Person::WORK);
        }
        else {
            cout << "Unknown phone type.  Using default." << endl;
        }
    }
}

int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    CHAR my_documents[MAX_PATH];
    HRESULT result = SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);

    if (result != S_OK)
        std::cout << "Error: " << result << "\n";
    else {
            
        std::string path = std::string(my_documents);
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
        path = path.append("\\Ipc.file");

        while (true) {

            cout << "Reading IPC Stream..." << endl;
            tutorial::AddressBook address_book;

            {
                // Read the existing address book.
                fstream input(path, ios::in | ios::binary);
                if (!input) {
                    cout << path << ": File not found.  Creating a new file." << endl;
                    // Add an address.
                    PromptForAddress(address_book.add_people());

                    {
                        // Write the new address book back to disk.
                        fstream output(path, ios::out | ios::trunc | ios::binary);
                        if (!address_book.SerializeToOstream(&output)) {
                            cerr << "Failed to write address book." << endl;
                            return -1;
                        }
                    }
                }
                else if (!address_book.ParseFromIstream(&input)) {
                    cerr << "Failed to parse address book." << endl;
                    return -1;
                }
            }

            ListPeople(address_book);

            Sleep(1000);


       }

        google::protobuf::ShutdownProtobufLibrary();

    }

    std::cout << "Hello World!\n";
    return 0;

    // Path should be: Documents/SWBF-Wrapper/Data/Ipc.file
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
