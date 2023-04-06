/*Creati o aplicatie care permite:
· gestiunea unei liste de discipline. Disciplina: denumire, ore pe saptamana, tip, cadru
didactic
· adaugare, stergere, modificare si afisare discipline
· cautare disciplina
· filtrare discipline dupa: nr ore, cadru didactic
· sortare discipline dupa: denumire, nr ore, cadru didactic + tip*/

#include "entity.h"
#include "Repository.h"
#include "Service.h"
#include "UI.h"
#include "Validators.h"
#include <iostream>


void testAll() {
	testDomain();
	std::cout << "Finished domain tests." << std::endl;
	testRepository();
	std::cout << "Finished repo tests." << std::endl;
	//testAddService();
	//testDeleteService();
	//testlookforService();
	//testModifyService();
	testService();
	std::cout << "Finished service tests." << std::endl;
}

int main()
{
	int ok = 0;
	if(ok == 0)
	{
		SubjectRepository rep;
		SubjectValidator val;
		SubjectStore srv{ rep, val };
		UI ui{ srv };
		testAll();
		ui.StartUI();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}