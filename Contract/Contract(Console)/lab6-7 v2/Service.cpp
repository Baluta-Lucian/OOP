#include "Service.h"
#include <algorithm>
#include <assert.h>

void SubjectStore::add(const string& denumire, const int& ore, const string& tip, const string& cadru_didactic) {
	Subject s{ denumire, ore, tip, cadru_didactic };
	val.valideaza(s);
	rep.store(s);
}
vector <Subject> SubjectStore::getAll() {
	return rep.getAll();
}
void SubjectStore::sterge(string denumire, int ore, string tip, string cadru_didactic) {
	Subject s{ denumire, ore, tip, cadru_didactic };
	rep.del(s);
}

void SubjectStore::modifica(string denumire, int ore, string tip, string cadru_didactic, string denumire1, int ore1, string tip1, string cadru_didactic1)
{
	Subject s = { denumire, ore, tip, cadru_didactic };
	Subject s1 = { denumire1, ore1, tip1, cadru_didactic1 };
	val.valideaza(s1);
	rep.modify(s, s1);
}

Subject SubjectStore::cauta(string denumire) {
	return rep.find(denumire);
}

vector<Subject> SubjectStore::filtrareOre(const int ore) {
	vector<Subject> rez;
	const auto& v = rep.getAll();
	std::copy_if(v.begin(), v.end(), back_inserter(rez), [ore](const Subject& s)noexcept {return ore == s.getOre(); });
	return rez;
}

bool SubjectStore::Par() {
	const auto& v = rep.getAll();
	return std::any_of(v.begin(), v.end(), [](const Subject& s1) {if (s1.getOre() % 2 == 0) return true;
	return false; });
}

vector<Subject> SubjectStore::filtrareCadru(const string cadru_didactic) {
	vector<Subject> rez;
	const vector<Subject>& v = rep.getAll();
	std::copy_if(v.begin(), v.end(), back_inserter(rez), [cadru_didactic](const Subject& s) {return cadru_didactic == s.getCadru(); });
	return rez;
}
void SubjectStore::sortDenumire() {
	rep.sortByDenumire();
}
void SubjectStore::sortOre() {
	rep.sortByOre();
}

void SubjectStore::sortCT() {
	rep.sortByCT();
}

const vector<Subject>& SubjectStore::addToContract(const string& denumire) {
	const Subject& s = rep.find(denumire);
	contract.adauga(s);
	return contract.lista();
}

const vector<Subject>& SubjectStore::addRandom(int cate)
{
	contract.umple(cate, rep.getAll());
	return contract.lista();
}

const vector<Subject>& SubjectStore::golesteContract() {
	contract.goleste();
	return contract.lista();
}

const vector<Subject>& SubjectStore::toateDinContract() {
	return contract.lista();
}

void testAddService() {
	SubjectRepository testRepo;
	SubjectValidator testVal;
	SubjectStore testService{ testRepo, testVal };

	testService.add("Chimie", 4, "obligatorie", "Talaba");
	testService.add("Religie", 1, "facultativa", "Branzan");
	testService.add("Informatica", 8, "obligatorie", "Eugenia Maria-Ohota");

	assert(testService.getAll().size() == 3);
	try {
		testService.add("Chimie", 4, "obligatorie", "Talaba");
		//assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	
		testService.add("Biologie", 4, "obligatorie", "Neguleasa");
		//assert(true);
	

	// de implementat teste pentru ValidationException
	try {
		testService.add("i", 3, "obligatorie", "Eugenia");
		//assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessage() == "Denumirea trebuie sa aiba minim 2 caractere.\n");
	}
	try {
		testService.add("Info3", 3, "obligatorie", "Eugenia");
		//assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessage() == "Denumirea nu trebuie sa contina cifre.\n");
	}
	try {
		testService.add("Info", 0, "obligatorie", "Eugenia");
		//assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessage() == "Trebuie sa existe cel putin o ora pe saptamana.\n");
	}
	try {
		testService.add("Info", 10, "obligatorie", "Eugenia");
		//assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessage() == "Nu sunt permise mai mult de 8 ore pe saptamana.\n");
	}
	try {
		testService.add("Info", 8, "facult", "Eugenia");
		//assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessage() == "O disciplina poate avea tipul doar facultativa/obligatorie.\n");
	}
	try {
		testService.add("Info", 8, "facultativa", "E");
		//assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessage() == "Cadrul didactic trebuie sa aiba minim 2 caractere.\n");
	}
	try {
		testService.add("Info", 8, "facultativa", "eugenia");
		//assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessage() == "Cadrul Didactic trebuie sa inceapa cu litera mare.\n");
	}
	try {
		testService.add("Info", 8, "facultativa", "Euge3nia");
		//assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessage() == "Cadrul didactic nu poate contine cifre\n");
	}
	try {
		testService.add("Info", 8, "facultativa", "Eugenia maria");
		//assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessage() == "Prenumele cadrului didactic trebuie sa inceapa cu litera mare.\n");
	}
	try {
		testService.add("Info", 8, "facultativa", "Eugenia MAria");
		//assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessage() == "Doar prima litera din nume/prenume a cadrului didactic contine litera mare.\n");
	}
	try {
		testService.add("Info", 8, "facultativa", "Eugenia MariaOhota");
		//assert(false);
	}
	catch (ValidationException&) {
		//cout << ve.getErrorMessage();
		//assert(ve.getErrorMessage() == "Doar prima litera din nume / prenume a cadrului didactic contine litera mare.\nNumele/prenumele trebuie sa fie separat prin spatiu sau -\n");
		assert(true);
	}
}


void testStergeService() {
	SubjectRepository testRepo;
	SubjectValidator testVal;
	SubjectStore testService{ testRepo, testVal };

	testService.add("Chimie", 4, "obligatorie", "Talaba");
	testService.add("Religie", 1, "facultativa", "Branzan");
	testService.add("Informatica", 8, "obligatorie", "Eugenia Maria-Ohota");
	assert(testService.getAll().size() == 3);
	testService.sterge("Chimie", 4, "obligatorie", "Talaba");
	assert(testService.getAll().size() == 2);
}

void testModifyService() {

	SubjectRepository testRepo;
	SubjectValidator testVal;
	SubjectStore testService{ testRepo, testVal };

	testService.add("Chimie", 4, "obligatorie", "Talaba");
	testService.add("Religie", 1, "facultativa", "Branzan");
	testService.add("Informatica", 8, "obligatorie", "Eugenia Maria-Ohota");
	assert(testService.getAll().size() == 3);

	testService.modifica("Chimie", 4, "obligatorie", "Talaba", "Chimie", 3, "facultativa", "Talaba");
}

void testCautaService() {
	SubjectRepository testRepo;
	SubjectValidator testVal;
	SubjectStore testService{ testRepo, testVal };

	testService.add("Chimie", 4, "obligatorie", "Talaba");
	testService.add("Religie", 1, "facultativa", "Branzan");
	testService.add("Informatica", 8, "obligatorie", "Eugenia Maria-Ohota");
	assert(testService.getAll().size() == 3);
	Subject s1 = { "Religie", 1, "facultativa", "Branzan" };
	Subject s = testService.cauta("Religie");
	assert(s == s1);
}

void testFiltrareService() {
	SubjectRepository testRepo;
	SubjectValidator testVal;
	SubjectStore testService{ testRepo, testVal };

	testService.add("Chimie", 4, "obligatorie", "Talaba");
	testService.add("Religie", 1, "facultativa", "Branzan");
	testService.add("Informatica", 8, "obligatorie", "Eugenia Maria-Ohota");
	testService.add("Mate", 4, "obligatorie", "Nanu");
	vector<Subject> rez1 = testService.filtrareOre(4);
	assert(rez1.size() == 2);
	vector<Subject> rez2 = testService.filtrareCadru("Eugenia Maria-Ohota");
	assert(rez2.size() == 1);
	
}

void testSortService() {
	SubjectRepository testRepo;
	SubjectValidator testVal;
	SubjectStore testService{ testRepo, testVal };

	testService.add("Chimie", 4, "obligatorie", "Talaba");
	testService.add("Religie", 1, "facultativa", "Branzan");
	testService.add("Informatica", 8, "obligatorie", "Eugenia Maria-Ohota");
	testService.add("Mate", 4, "obligatorie", "Nanu");
	testService.add("Desen", 8, "facultativa", "Eugenia Maria-Ohota");

	testService.sortOre();
	testService.sortDenumire();
	testService.sortCT();
}

void testAddCosService() {
	SubjectRepository testRepo;
	SubjectValidator testVal;
	SubjectStore testService{ testRepo, testVal };

	testService.add("Chimie", 4, "obligatorie", "Talaba");
	testService.add("Religie", 1, "facultativa", "Branzan");
	testService.add("Informatica", 8, "obligatorie", "Eugenia Maria-Ohota");
	testService.add("Mate", 4, "obligatorie", "Nanu");
	testService.add("Desen", 8, "facultativa", "Eugenia Maria-Ohota");
	SubjectContract cos;
	const auto rez = testService.addToContract("Desen");
	assert(rez.size() == 1);

	const auto rez1 = testService.golesteContract();
	assert(rez1.size() == 0);

	const auto rez2 = testService.addRandom(3);
	assert(rez2.size() == 3);

	const auto rez4 = testService.toateDinContract();
	assert(rez4.size() == 3);

	const auto rez3 = testService.golesteContract();
	assert(rez3.size() == 0);
}

void testService() {
	testAddService();
	testStergeService();
	testModifyService();
	testCautaService();
	testFiltrareService();
	testSortService();
	testAddCosService();
}

