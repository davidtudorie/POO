#include <fstream>
#include <string>
#include <iostream>

using namespace std;
class Person {
    
public:
    Person() : name(nullptr), age(0), surname(nullptr) {}
    Person(const string& n, const string& s, int a) : age(a) {
        name = new char[n.size() + 1];
        strcpy_s(name, n.size() + 1, n.c_str());
        surname = new char[s.size() + 1];
        strcpy_s(surname, s.size() + 1, s.c_str());
    }

    // Destructor pentru a elibera memoria alocata dinamic
    ~Person() {
        delete[] name;
        delete[] surname;
    }

    // Funcție de serializare
    void Serialize(ofstream& ofs) const {
        size_t nameLength = strlen(name) + 1;
        size_t surnameLength = strlen(surname) + 1;
        ofs.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength)); // Scriem lungimea numelui
        ofs.write(name, nameLength);
        ofs.write(reinterpret_cast<const char*>(&surnameLength), sizeof(surnameLength));
        ofs.write(surname, surnameLength);
        ofs.write(reinterpret_cast<const char*>(&age), sizeof(age));
        
    }

    // Funcție de deserializare
    void Deserialize(ifstream& ifs) {
        size_t nameLength;
        size_t surnameLength;
        ifs.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength)); 
        ifs.read(reinterpret_cast<char*>(&surnameLength), sizeof(surnameLength));// Citim lungimea numelui
        delete[] name;
        delete[] surname;
        name = new char[nameLength];
        surname = new char[surnameLength];
        ifs.read(name, nameLength);
        ifs.read(surname, surnameLength);
        ifs.read(reinterpret_cast<char*>(&age), sizeof(age));
    }

    void DisplayInfo() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }

private:
    char* name;
    int age;
    char* surname;
};

int main1() {
    // Salvare obiect într-un fișier binar
    {
        ofstream outputFile("person.dat", ios::binary);
        if (!outputFile) {
            cerr << "Error opening file for writing." << endl;
            return 1;
        }

        Person personToSave("John", 25, "david");
        personToSave.Serialize(outputFile);

        cout << "Object saved successfully." << endl;
    }

    // Restaurare obiect din fișier binar
    {
        ifstream inputFile("person.dat", ios::binary);
        if (!inputFile) {
            cerr << "Error opening file for reading." << endl;
            return 1;
        }

        Person restoredPerson;
        restoredPerson.Deserialize(inputFile);

        cout << "Object restored successfully." << endl;
        restoredPerson.DisplayInfo();
    }

    return 0;
}