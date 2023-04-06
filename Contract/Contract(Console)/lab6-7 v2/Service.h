#pragma once
#include "Repository.h"
#include "Validators.h"
#include "Contract.h"

class SubjectStore {
private:
	SubjectRepository& rep;
	SubjectValidator& val;

	SubjectContract contract;
public:
	SubjectStore() = default;	
	SubjectStore(SubjectRepository& rep, SubjectValidator& val) noexcept : rep{ rep }, val{ val } {}
	SubjectStore(const SubjectStore& ot) = delete;
	void operator=(const SubjectStore& ot) = delete;
	~SubjectStore() = default;
	void add(const string& denumire, const int& ore, const string& tip, const string& cadru_didactic);
	vector <Subject> getAll();
	void sterge(string denumire, int ore, string tip, string cadru_didactic);
	void modifica(string denumire, int ore, string tip, string cadru_didactic, string denumire1, int ore1, string tip1, string cadru_didactic1);
	Subject cauta(string denumire);
	vector<Subject>filtrareOre(const int ore);
	vector<Subject>filtrareCadru(const string cadru_didactic);
	void sortDenumire();
	void sortOre();
	void sortCT();
	const vector<Subject>& addToContract(const string& denumire);
	const vector<Subject>& addRandom(int cate);
	const vector<Subject>& golesteContract();
	const vector<Subject>& toateDinContract();

	bool Par();
};

void testService();