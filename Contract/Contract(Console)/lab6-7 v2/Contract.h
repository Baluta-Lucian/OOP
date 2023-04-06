#pragma once
#include <vector>
#include <algorithm>
#include <random> //std::default_random_engine
#include <chrono> //std::chrono::system_clock
using std::vector;

#include "entity.h"

class SubjectContract {
	vector<Subject> inCos;
public:
	SubjectContract() = default;
	//~SubjectContract() = default;
	void adauga(const Subject& s)
	{
		inCos.push_back(s);
	}
	void goleste() noexcept
	{
		inCos.clear();
	}

	void umple(size_t cate, vector<Subject> subjects)
	{
		std::shuffle(subjects.begin(), subjects.end(), std::default_random_engine(std::random_device{}()));
		while (inCos.size() < cate && subjects.size() > 0)
		{
			inCos.push_back(subjects.back());
			subjects.pop_back();
		}
	}

	const vector<Subject>& lista() const {
		return inCos;
	}
};
