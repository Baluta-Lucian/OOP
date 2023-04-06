#include "entity.h"
#include <assert.h>

string Subject::getDenumire() const {
	return denumire;
}
int Subject::getOre() const noexcept {
	return ore;
}
string Subject::getTip() const {
	return tip;
}
string Subject::getCadru() const {
	return cadru_didactic;
}

void testGet()
{
	Subject subject1{ "Chimie", 4, "obligatorie", "Talaba" };
	assert(subject1.getDenumire() == "Chimie");
	assert(subject1.getOre() == 4);
	assert(subject1.getTip() == "obligatorie");
	assert(subject1.getCadru() == "Talaba");

	Subject subject2{ "Religie", 1, "facultativa", "Branzan" };
	assert(subject2.getDenumire() == "Religie");
	assert(subject2.getOre() == 1);
	assert(subject2.getTip() == "facultativa");
	assert(subject2.getCadru() == "Branzan");

}

void testDomain() {
	testGet();
}
