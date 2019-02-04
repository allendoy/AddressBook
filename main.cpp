#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;


struct Contact {

    int id;
    string firstName, lastName, phoneNumber, emailAddress, address;
};

void readContactsFromExternalFile(vector<Contact> &contacts);
void addContact(vector<Contact> &contacts);
void findContactByFirstName(vector<Contact> contacts);
void findContactByLastName(vector<Contact> contacts);
void displayAllContacts(vector<Contact> contacts);
void editContactById(vector<Contact> &contacts);
void deleteContactById(vector<Contact> &contacts);
int measureContactsLength (vector<Contact> contacts);
int checkMaxId (vector<Contact> contacts, int sizeOfContacts);


int main() {
    vector<Contact> contacts;
    char programOption;

    readContactsFromExternalFile(contacts);

    while (true) {
        system("cls");
        cout << "----- KSIAZKA ADRESOWA -----" << endl;
        cout << "1. Dodaj kontakt" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkie kontakty" << endl;
        cout << "5. Usun kontakt" << endl;
        cout << "6. Edytuj kontakt" << endl;
        cout << "9. Zamknij program" << endl;
        cout << endl << "Twoj wybor: ";

        cin >> programOption;

        switch (programOption) {
        case '1':
            addContact(contacts);
            break;
        case '2':
            findContactByFirstName(contacts);
            break;
        case '3':
            findContactByLastName(contacts);
            break;
        case '4':
            displayAllContacts(contacts);
            break;
        case '5':
            deleteContactById(contacts);
            break;
        case '6':
            editContactById(contacts);
            break;
        case '9':
            exit(0);
            break;
        default:
            cout << "Wybrano nieprawidlowa opcje menu. Sprobuj ponownie!" << endl;
            Sleep(3000);
            break;
        }
    }
    return 0;
}

void addContact(vector<Contact> &contacts) {

    int sizeOfContacts, id, maxId;
    string firstName, lastName, phoneNumber, emailAddress, address;

    sizeOfContacts = measureContactsLength(contacts);
    maxId = checkMaxId (contacts,sizeOfContacts);

    cout << "Podaj imie: ";
    cin >> firstName;
    cout << "Podaj nazwisko: ";
    cin >> lastName;
    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin, phoneNumber);
    cout << "Podaj adres email: ";
    cin >> emailAddress;
    cout << "Podaj adres zamieszkania: ";
    cin.sync();
    getline(cin, address);
    id = maxId + 1;

    contacts.push_back( {id, firstName, lastName, phoneNumber, emailAddress, address} );

    fstream externalFile;
    externalFile.open("AddressBook.txt", ios::out | ios::app);
    externalFile << id << "|" << firstName << "|" << lastName << "|" << phoneNumber << "|" <<emailAddress << "|" << address << "|" << endl;
    externalFile.close();
    cout << "Kontakt zostal dodany!" << endl;
    Sleep(1500);
}

void findContactByFirstName(vector<Contact> contacts) {

    string searchedFirstName;
    int hitCount = 0;
    int i = 0;
    int sizeOfContacts = measureContactsLength(contacts);

    cout << "Wprowadz imie, po ktorym nastapi wyszukanie kontaktow: ";
    cin >> searchedFirstName;
    while (i < sizeOfContacts ) {
        if(contacts[i].firstName == searchedFirstName) {
            cout << contacts[i].id << endl;
            cout << contacts[i].firstName << endl;
            cout << contacts[i].lastName << endl;
            cout << contacts[i].phoneNumber << endl;
            cout << contacts[i].emailAddress << endl;
            cout << contacts[i].address << endl;
            cout << endl;
            hitCount++;
        }
        i++;
    }
    if (hitCount == 0) {
        cout << endl << "Nie znaleziono kontaktu!" << endl;
    } else {
        cout << "Liczba znaleznionych kontaktow: " << hitCount <<endl;
    }
    cout << "Aby kontynuowac, nacisnij dowolny klawisz...";
    getch();
}

void findContactByLastName(vector<Contact> contacts) {
    string searchedLastName;
    int hitCount = 0;
    int i = 0;
    int sizeOfContacts = measureContactsLength(contacts);

    cout << "Wprowadz nazwisko, po ktorym nastapi wyszukanie kontaktow: ";
    cin >> searchedLastName;
    while (i < sizeOfContacts ) {
        if (contacts[i].lastName == searchedLastName) {
            cout << contacts[i].id << endl;
            cout << contacts[i].firstName << endl;
            cout << contacts[i].lastName << endl;
            cout << contacts[i].phoneNumber << endl;
            cout << contacts[i].emailAddress << endl;
            cout << contacts[i].address << endl;
            cout << endl;
            hitCount++;
        }
        i++;
    }
    if (hitCount == 0) {
        cout << endl << "Nie znaleziono kontaktu!" << endl;
    } else {
        cout << "Liczba znaleznionych kontaktow: " << hitCount <<endl;
    }
    cout << "Aby kontynuowac, nacisnij dowolny klawisz...";
    getch();
}

void displayAllContacts(vector<Contact> contacts) {
    int sizeOfContacts = measureContactsLength(contacts);

    for(int i=0; i < sizeOfContacts; i++) {
        cout << contacts[i].id << endl;
        cout << contacts[i].firstName << endl;
        cout << contacts[i].lastName << endl;
        cout << contacts[i].phoneNumber << endl;
        cout << contacts[i].emailAddress << endl;
        cout << contacts[i].address << endl;
        cout << endl;
    }
    cout << "Liczba wyswietlonych kontaktow: " << sizeOfContacts << endl;
    cout << "Aby kontynuowac, nacisnij dowolny klawisz...";
    getch();
}

void readContactsFromExternalFile(vector<Contact> &contacts) {
    fstream externalFile;
    string line;
    vector <string> contactComponent;
    externalFile.open("AddressBook.txt", ios::in);

    if (externalFile.good() == true) {
        while (!externalFile.eof()) {
            getline(externalFile, line);
            stringstream splitContact(line);
            string intermediate;

            while(getline(splitContact, intermediate, '|')) {
                contactComponent.push_back(intermediate);
            }
        }
        for(int i = 0; i < contactComponent.size(); i++) {
            string fraction = contactComponent[i];
            stringstream composeContact(fraction);
            int convertedId = 0;
            composeContact >> convertedId;
            contacts.push_back ({convertedId, contactComponent[i+1], contactComponent[i+2], contactComponent[i+3], contactComponent[i+4], contactComponent[i+5]});
            i+=5;
        }
    }
    externalFile.close();
}

void editContactById(vector<Contact> &contacts) {
    fstream externalFile;
    string line;
    vector <string> contactComponent;
    char option;
    int identifier;
    string editedFirstName, editedLastName, editedPhoneNumber, editedEmailAddress, editedAddress;

    int sizeOfContacts = measureContactsLength(contacts);

    cout << "Podaj id kontaktu, dla ktorego chcesz zmodyfikowac dane: ";
    cin >> identifier;


    for (int k = 0; k < sizeOfContacts; k++) {
        if (contacts[k].id == identifier) {

            cout << "----- Edycja -----" << endl;
            cout << "1. Imie" << endl;
            cout << "2. Nazwisko" << endl;
            cout << "3. Numer telefonu" << endl;
            cout << "4. Email" << endl;
            cout << "5. Adres" << endl;
            cout << "6. Powrot do menu glownego" << endl;
            cout << endl << "Wybierz opcje: ";
            cin >> option;

            switch (option) {

            case '1':
                cout << "Wprowadz imie: ";
                cin >> editedFirstName;

                for (int i = 0; i < sizeOfContacts; i++) {
                    if (contacts[i].id == identifier) {
                        contacts[i].firstName = editedFirstName;
                    }
                }
                externalFile.open("AddressBook.txt", ofstream::out | std::ofstream::trunc);
                for (int j = 0; j <sizeOfContacts; j++) {
                    externalFile << contacts[j].id << "|" << contacts[j].firstName << "|" << contacts[j].lastName << "|" << contacts[j].phoneNumber << "|" <<contacts[j].emailAddress << "|" << contacts[j].address << "|" << endl;
                }
                cout << "Kontakt zostal zmieniony!";
                Sleep(1500);
                break;
            case '2':
                cout << "Wprowadz nazwisko: ";
                cin >> editedLastName;
                for (int i = 0; i < sizeOfContacts; i++) {
                    if (contacts[i].id == identifier) {
                        contacts[i].lastName = editedLastName;
                    }
                }
                externalFile.open("AddressBook.txt", ofstream::out | std::ofstream::trunc);
                for (int j = 0; j < sizeOfContacts; j++) {
                    externalFile << contacts[j].id << "|" << contacts[j].firstName << "|" << contacts[j].lastName << "|" << contacts[j].phoneNumber << "|" <<contacts[j].emailAddress << "|" << contacts[j].address << "|" << endl;
                }
                cout << "Kontakt zostal zmieniony!";
                Sleep(1500);
                break;
            case '3':
                cout << "Wprowadz numer telefonu: ";
                cin.clear();
                cin.sync();
                getline(cin, editedPhoneNumber);

                for (int i = 0; i < sizeOfContacts; i++) {
                    if (contacts[i].id == identifier) {
                        contacts[i].phoneNumber = editedPhoneNumber;
                    }
                }
                externalFile.open("AddressBook.txt", ofstream::out | std::ofstream::trunc);
                for (int j = 0; j < sizeOfContacts; j++) {
                    externalFile << contacts[j].id << "|" << contacts[j].firstName << "|" << contacts[j].lastName << "|" << contacts[j].phoneNumber << "|" <<contacts[j].emailAddress << "|" << contacts[j].address << "|" << endl;
                }
                cout << "Kontakt zostal zmieniony!";
                Sleep(1500);
                break;
            case '4':
                cout << "Wprowadz adres email: ";
                cin >> editedEmailAddress;
                for (int i = 0; i < sizeOfContacts; i++) {
                    if (contacts[i].id == identifier) {
                        contacts[i].emailAddress = editedEmailAddress;
                    }
                }
                externalFile.open("AddressBook.txt", ofstream::out | std::ofstream::trunc);
                for (int j = 0; j < sizeOfContacts; j++) {
                    externalFile << contacts[j].id << "|" << contacts[j].firstName << "|" << contacts[j].lastName << "|" << contacts[j].phoneNumber << "|" <<contacts[j].emailAddress << "|" << contacts[j].address << "|" << endl;
                }
                cout << "Kontakt zostal zmieniony!";
                Sleep(1500);
                break;
            case '5':
                cout << "Wprowadz adres: ";
                cin.clear();
                cin.sync();
                getline(cin, editedAddress);
                for (int i = 0; i < sizeOfContacts; i++) {
                    if (contacts[i].id == identifier) {
                        contacts[i].address = editedAddress;
                    }
                }
                externalFile.open("AddressBook.txt", ofstream::out | std::ofstream::trunc);
                for (int j = 0; j < sizeOfContacts; j++) {
                    externalFile << contacts[j].id << "|" << contacts[j].firstName << "|" << contacts[j].lastName << "|" << contacts[j].phoneNumber << "|" <<contacts[j].emailAddress << "|" << contacts[j].address << "|" << endl;
                }
                cout << "Kontakt zostal zmieniony!";
                Sleep(1500);
                break;
            case '6':
                break;
            }
        }
    }
}

void deleteContactById(vector<Contact> &contacts) {
    fstream externalFile;
    int identifier;
    cout << "Wprowadz id kontaktu, ktory nalezy usunac: ";
    cin >> identifier;
    char deleteConfirmation;

    vector<Contact>::iterator searchProperId = contacts.begin();
    while (searchProperId != contacts.end()) {
        if (searchProperId-> id == identifier) {
            cout << "Aby zatwierdzic operacje, wcisnij 't'" << endl;
            cin >> deleteConfirmation;
            if (deleteConfirmation == 't') {
                searchProperId = contacts.erase(searchProperId);
                externalFile.open("AddressBook.txt", ofstream::out | std::ofstream::trunc);
                for(int i = 0; i < contacts.size(); i++) {
                    externalFile << contacts[i].id << "|" << contacts[i].firstName << "|" << contacts[i].lastName << "|" << contacts[i].phoneNumber << "|" <<contacts[i].emailAddress << "|" << contacts[i].address << "|" << endl;
                }
                cout << "Kontakt zostal usuniety!";
                Sleep(1500);
                break;
            } else {
                cout << "Operacja usuniecie niewlasciwie potwierdzona!" << endl;
                Sleep(1500);
                break;
            }
        } else {
       searchProperId++;
        }
    }
}

int measureContactsLength (vector<Contact> contacts) {
    return contacts.size();
}

int checkMaxId (vector<Contact> contacts, int sizeOfVector) {
    int maxId = 0;
    if (sizeOfVector >= 1) {
        for (int i = 0; i < sizeOfVector; i++) {
            if (maxId < contacts[i].id) {
                maxId = contacts[i].id;
            }
        }
    }
    return maxId;
}
