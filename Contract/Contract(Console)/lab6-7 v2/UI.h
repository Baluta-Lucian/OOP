#pragma once
#include "Service.h"

class UI {
private:
	SubjectStore& srv;
public:
	UI(SubjectStore& srv) noexcept : srv{srv}{}
	void StartUI();
};