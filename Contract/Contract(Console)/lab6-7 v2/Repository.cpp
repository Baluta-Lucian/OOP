#include "Repository.h"
#include <algorithm>
#include <assert.h>

string RepoException::getMessage() const {
	return msg;
}

void SubjectRepository::store(const Subject& subject) {
	auto found = std::find_if(subjects.begin(), subjects.end(), [&subject](const Subject& s) {
		return subject.getDenumire() == s.getDenumire();
		});
	if (found != subjects.end()) {
		throw RepoException("Subject already exists!\n");
	}
	subjects.push_back(subject);
};
const vector<Subject>& SubjectRepository::getAll() noexcept {
	return subjects;
}

void SubjectRepository::del(const Subject& subject) {
	vector<Subject>::iterator it;
	it = std::find(subjects.begin(), subjects.end(), subject);
	if (it != subjects.end()) {
		subjects.erase(it);
		return;
	}
	throw RepoException("Subject does not exist!\n");
}

void SubjectRepository::modify(const Subject& subject, const Subject& subject1) {
	vector<Subject>::iterator it;
	it = std::find(subjects.begin(), subjects.end(), subject1);
	if (it != subjects.end())
	{
		throw RepoException("The new subject already exists in list\n");
	}
	it = std::find(subjects.begin(), subjects.end(), subject);
	if (it != subjects.end()) {
		std::replace(subjects.begin(), subjects.end(), subject, subject1);
		return;
	}
	throw RepoException("Subject does not exist\n");
}

const Subject& SubjectRepository::find(string denumire) {
	auto found = find_if(subjects.begin(), subjects.end(), [&](const Subject& s) {return denumire == s.getDenumire(); });
	if (found == subjects.end())
	{
		throw RepoException("Subject does not exist\n");
	}
	return *found;
}

void SubjectRepository::sortByDenumire() {
	std::sort(subjects.begin(), subjects.end(), [](const Subject& s1, const Subject& s2) { if (s1.getDenumire().compare(s2.getDenumire()) > 0)
		return false;
	else
		return true;
		});
}

void SubjectRepository::sortByOre()
{
	std::sort(subjects.begin(), subjects.end(), [](const Subject& s1, const Subject& s2) { return s1.getOre() < s2.getOre();});
}

void SubjectRepository::sortByCT()
{
	std::sort(subjects.begin(), subjects.end(), [](const Subject& s1, const Subject& s2) { if (s1.getCadru().compare(s2.getCadru()) == 0) {
		if (s1.getTip().compare(s2.getTip()) < 0)
			return true;
		else
			return false;
	}
	else if (s1.getCadru().compare(s2.getCadru()) < 0)
		return true;
	else
		return false;
	});

}

void testAddRepo() {
	SubjectRepository testRepo;
	Subject subject1{ "Religie", 1, "facultativa", "Branzan" };
	testRepo.store(subject1);
	assert(testRepo.getAll().size() == 1);

	Subject subject2{ "Religie", 3, "obligatore", "Branzan" };
	try {
		testRepo.store(subject2);
	}
	catch (RepoException) {
		assert(true);
	}


}
void testRepoFind(){

SubjectRepository testRepo;
Subject subject2{ "Religie", 1, "facultativa", "Branzan" };
Subject subject1{ "Chimie", 4, "obligatorie", "Talaba" };
Subject subject3{ "Informatica", 8, "obligatorie", "Eugenia Maria-Ohota" };

testRepo.store(subject1);
testRepo.store(subject2);

Subject subject4 = testRepo.find("Religie");
assert(subject4 == subject2);
try {
	Subject s = testRepo.find("Mate");
}
catch(RepoException& ex){
	assert(ex.getMessage() == "Subject does not exist\n");
}
}

void testRepoDel() {
	SubjectRepository testRepo;
	Subject subject2{ "Religie", 1, "facultativa", "Branzan" };
	Subject subject1{ "Chimie", 4, "obligatorie", "Talaba" };
	Subject subject3{ "Informatica", 8, "obligatorie", "Eugenia Maria-Ohota" };

	testRepo.store(subject1);
	testRepo.store(subject2);

	assert(testRepo.getAll().size() == 2);
	Subject s = { "Religie", 1, "facultativa", "Branzan" };
	testRepo.del(subject2);
	assert(testRepo.getAll().size() == 1);
	try {
		testRepo.del(s);
	}
	catch (RepoException& ex) {
		assert(ex.getMessage() == "Subject does not exist!\n");
	}
}
void testRepoModify() {
	SubjectRepository testRepo;
	Subject subject2{ "Religie", 1, "facultativa", "Branzan" };
	Subject subject1{ "Chimie", 4, "obligatorie", "Talaba" };
	Subject subject3{ "Informatica", 8, "obligatorie", "Eugenia Maria-Ohota" };

	testRepo.store(subject1);
	testRepo.store(subject2);

	Subject s{ "Mate", 3, "obligatorie", "Nanu" };

	testRepo.modify(subject2, s);

	Subject subject4 = testRepo.find("Mate");
	assert(subject4 == s);
	try {
		testRepo.modify(s, s);
	}
	catch (RepoException& ex)
	{
		assert(ex.getMessage() == "The new subject already exists in list\n");
	}
	try {
		testRepo.modify(subject2, subject2);
	}
	catch (RepoException& ex) {
		assert(ex.getMessage() == "Subject does not exist\n");
	}
}

void testRepoSort() {
	SubjectRepository testRepo;
	Subject subject2{ "Religie", 1, "facultativa", "Branzan" };
	Subject subject1{ "Chimie", 4, "obligatorie", "Talaba" };
	Subject subject3{ "Informatica", 8, "obligatorie", "Eugenia Maria-Ohota" };

	testRepo.store(subject1);
	testRepo.store(subject2);
	testRepo.store(subject3);
	
	testRepo.sortByDenumire();
	testRepo.sortByOre();
	Subject subject4{ "Desen", 1, "facultativa", "Eugenia Maria-Ohota" };
	testRepo.store(subject4);
	testRepo.sortByCT();
}

void testRepository() {
	testAddRepo();
	testRepoFind();
	testRepoDel();
	testRepoModify();
	testRepoSort();
}

