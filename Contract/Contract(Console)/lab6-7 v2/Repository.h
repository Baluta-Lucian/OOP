#pragma once
#include "entity.h"
#include <vector>
#include <string>
#include <iostream>

using std::vector;

class RepoException {
private:
	string msg;
public:
	RepoException(string msg) : msg{ msg } {}
	string getMessage() const;
};

class SubjectRepository {
private:
	vector<Subject> subjects;
public:
	SubjectRepository() = default;
	SubjectRepository(const SubjectRepository& ot) = delete;
	~SubjectRepository() = default;

	void store(const Subject& subject);
	const vector<Subject>& getAll() noexcept;
	void del(const Subject& subject);
	void modify(const Subject& subject, const Subject& subject1);
	const Subject& find(string denumire);
	void sortByDenumire();
	void sortByOre();
	void sortByCT();
};

void testRepository();