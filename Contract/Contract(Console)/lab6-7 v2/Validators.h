#pragma once
#include "entity.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

class ValidationException {
	vector<string>	errorMsg;
public:
	
	ValidationException(vector<string> errorMsg) :errorMsg{ errorMsg } {};
	string getErrorMessage() {
		string fullMsg = "";
		for (const string e : errorMsg)
		{
			fullMsg += e + "\n";
		}
		return fullMsg;
	}
};

class SubjectValidator {
	//Clasa pentru validarea disciplinelor
	/*denumire : numele materiei / disciplinei
		*
		*ore pe saptamana : minim o ora maxim 6 ore
		*
		*tip : obligatorie / facultativa
		*
		*cadru didactiv : Numele cadrului didactic, fiecare nume / prenume separat prin cate un spatiu, fara cifre
		* (exceptie fiica lui Elon Musk) (for real) si incepe cu litera mare, este permis caracterul '-' intre doua prenume;
		*/

public:
	void valideaza(const Subject& m) {
		vector<string> errors;
		if (m.getDenumire().length() < 2)
			errors.push_back("Denumirea trebuie sa aiba minim 2 caractere.");
		else
		{
			for (const char c : m.getDenumire())
			{
				if (c >= '0' && c <= '9')
				{
					errors.push_back("Denumirea nu trebuie sa contina cifre.");
					break;
				}
			}
		}
		if (m.getOre() < 1)
			errors.push_back("Trebuie sa existe cel putin o ora pe saptamana.");
		if (m.getOre() > 8)
			errors.push_back("Nu sunt permise mai mult de 8 ore pe saptamana.");
		if (m.getTip() != "facultativa" && m.getTip() != "obligatorie")
			errors.push_back("O disciplina poate avea tipul doar facultativa/obligatorie.");
		if (m.getCadru().length() < 2)
			errors.push_back("Cadrul didactic trebuie sa aiba minim 2 caractere.");
		if (m.getCadru() != "X Æ A-Xii")
		{
			int suma = 0;
			int ok = 0;
			int ok2 = 0;
			char cop{ 'c' };
			for (const char c : m.getCadru())
			{
				suma++;
				if (suma == 1)
					if (c < 'A' || c > 'Z')
						errors.push_back("Cadrul Didactic trebuie sa inceapa cu litera mare.");
				if (c >= '0' && c <= '9' && ok == 0)
				{
					errors.push_back("Cadrul didactic nu poate contine cifre");
					ok = 1;
				}
				if (suma > 1)
				{
					//cout << cop << " " << c << " " << suma << " ";
					if ((cop == ' ' || cop == '-') && (c < 'A' || c > 'Z') && ok2 == 0)
					{
						errors.push_back("Prenumele cadrului didactic trebuie sa inceapa cu litera mare.");
						ok2 = 1;
					}
					if ((cop != ' ' && cop != '-') && (c < 'a' || c > 'z') && (c != ' ' && c != '-') && (c < '0' || c > '9'))
						errors.push_back("Doar prima litera din nume/prenume a cadrului didactic contine litera mare.");
					if ((cop != ' ' && cop != '-') && (cop < 'A' || cop > 'Z') && (c >= 'A' && c <= 'Z'))
						errors.push_back("Numele/prenumele trebuie sa fie separat prin spatiu sau -");

				}

				cop = { c };
			}
		}

		if (errors.size() > 0)
			throw ValidationException(errors);
	}
};