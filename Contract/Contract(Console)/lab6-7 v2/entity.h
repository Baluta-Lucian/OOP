#pragma once
#include <iostream>
#include <string>
/* gestiunea unei liste de discipline. Disciplina: denumire, ore pe saptamana, tip, cadru
didactic*/

using std::string;

class Subject {
private:
	string denumire;
	int ore;
	string tip;
	string cadru_didactic;
public:
	Subject() = delete;
	Subject(string denumire, int ore, string tip, string cadru_didactic) : denumire{ denumire }, ore{ ore }, tip{ tip }, cadru_didactic{ cadru_didactic }{

	}
	Subject(const Subject& ot) : denumire{ ot.denumire }, ore{ ot.ore }, tip{ ot.tip }, cadru_didactic{ ot.cadru_didactic }{
		std::cout << "[SUBJECT] Copy Constructor called!\n";
	}
	/*Subject(Subject&&) = default;
	Subject& operator=(const Subject&) = default;
	Subject& operator=(Subject&&) = default;*/
	~Subject() = default;
	string getDenumire() const;
	int getOre() const noexcept;
	string getTip() const;
	string getCadru() const;


	

	bool operator==(const Subject& ot) noexcept{
		if (this->denumire == ot.denumire && this->ore == ot.ore && this->tip == ot.tip && this->cadru_didactic == ot.cadru_didactic)
		{
			return true;
		}
	return false;
	}
	


};

void testDomain();