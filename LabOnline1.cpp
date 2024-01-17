/*
	implementarea clasei spital cu atributele:
	*cif- val tip char, se atribuie la creearea obj si e nemodificabila
	* nume sir char
	* adresa sir char
	* medici vector de siruri de char
	* vector de valori string alocat dinamic
	* nrMedici
	* nrSpitale(retine nr obj de tip spital instantiate vreodata)

	Se vor implementa:
	-constructor fara param
	-constr cu toti param
	-constr de copiere
	-destructor

	-supraincarcare op=
	-supraincare op << si >>
	-suptraincarcare op [] - returneaza medicu de pe poz data--atat scriere cat is citere
	-supraincare op !
	-cast explicit int - returneaza nr de spitale instantiate

	-metode de get si set
	-cel putin unul dintre atributele sir de char trebuie sa fie de tip char*
*/

#include <iostream>
#include <cstring>

class Spital {
private:
	const std::string cif;
	char* nume;
	std::string adresa;
	std::string* medici;
	int nrMedici;
	static int nrSpitale;
public:
	Spital():cif("") {
		this->nume = nullptr;
		this->adresa = "";
		this->medici = nullptr;
		this->nrMedici = 0;
		Spital::nrSpitale++;
	}
	Spital(std::string cif, const char* nume, std::string adresa, const std::string* medici, int nrMedici) : cif(cif), adresa(adresa), nrMedici(nrMedici){
		if (nume != nullptr) {
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);

		}
		else
			this->nume = nullptr;
		this->medici = new std::string[nrMedici];
		for (int i = 0; i < nrMedici; i++) {
			this->medici[i] = medici[i];
		}
		Spital::nrSpitale++;
	}
	Spital(Spital& s) :Spital(s.cif,s.nume,s.adresa,s.medici,s.nrMedici) {
		Spital::nrSpitale--;
	}
	Spital& operator=(const Spital& s)
	{
		if (this == &s) return *this;
		delete[] this->nume;
		this->nume = new char[strlen(s.nume) + 1];
		strcpy_s(this->nume, strlen(s.nume) + 1, s.nume);
		delete[] this->medici;
		this->nrMedici = s.nrMedici;
		this->medici = new std::string[s.nrMedici];
		for (int i = 0; i < s.nrMedici; i++)
		{
			this->medici[i] = s.medici[i];
		}
		this->adresa = s.adresa;

		return *this;
	}
	void setNume(const char* nume) {
		if (nume != nullptr) {
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
	else this->nume = nullptr;
	}
	void setAdresa(std::string _adresa) { adresa = _adresa; }
	void setMedici(const std::string* m, int nrM) {
		if (m != nullptr && nrM >0) {
			delete[] medici;
			medici = new std::string[nrM];
			for (int i = 0; i < nrM; i++) {
				medici[i] = m[i];
			}
		}
		else {
			medici = nullptr;
			nrMedici = 0;
		}
	}
	char* getNume() {
		char* copy = new char[strlen(nume) + 1];
		strcpy_s(copy, strlen(nume) + 1, nume);
		return copy;
	}
	std::string getCIF() {
		return cif;
	}
	friend std::ostream& operator<<(std::ostream& os, Spital s);
	friend std::istream& operator>>(std::istream& is, Spital& s);

	explicit operator int() {
		return Spital::nrSpitale;
	}

	~Spital() {
		delete[] this->nume;
		delete[] this->medici;
		Spital::nrSpitale--;
	}
};
int Spital::nrSpitale = 0;
std::ostream& operator<<(std::ostream& os, Spital s) {
	os << "CIF: " << s.cif << '\n';
	os << "Nume: " << s.nume << '\n';
	os << "Adresa: " << s.adresa << '\n';
	os<< "NrMedici: " << s.nrMedici << '\n';
	for (int i = 0; i < s.nrMedici; i++)
		os << s.medici[i] << "    ";
	return os;
}

std::istream& operator>>(std::istream& is, Spital& s) {
	char* tmp = new char[256];
	std::cout << "\nNume: ";
	is.getline(tmp, 256);
	s.setNume(tmp);
	std::cout << "\nAdresa: ";
	is.getline(tmp, 256);
	s.setAdresa(tmp);
	std::cout << "\nNr Medici: ";
	is >> s.nrMedici;
	is.getline(tmp, 256);
	std::cout << "\nMedici:";
	std::string* medici = new std::string[s.nrMedici];
	for (int i = 0; i < s.nrMedici; i++) {
		is.getline(tmp, 256);
		medici[i] = (std::string)tmp;
	}
	s.setMedici(medici, s.nrMedici);
	return is;
}

int main() {
	std::string* medici = new std::string[3];
	medici[0] = "Medic 1";
	medici[1] = "Medic 2";
	medici[2] = "Medic 3";
	Spital s1, s2("RO1234", "Floreasca", "Bucuresti", medici, 3);
	s2 = s2;
	
	s1 = s2;
	//s1.setNume("Nume Nou");
	std::cout << s2;
	Spital s3;
	//std::cin >> s3;

	Spital s4 = s3;

	std::cout << (int)s1;

	return 0;
}
