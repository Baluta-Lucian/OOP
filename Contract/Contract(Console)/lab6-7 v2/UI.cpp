#include "UI.h"
#include <algorithm>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

using std::cin;
using std::cout;

void UI::StartUI() {
	int cmd = 0;
	while (true) {
		cout << "1. Add\n2. Printare\n3. Stergere\n4. Modifica\n5. Cautare\n6. Filtrare\n7. Sortare\n8. Add Contract\n9. Goleste contract\n10. Random add\n11. Par\n0. Exit\n";
		cout << "Introduceti comanda: ";
		cin >> cmd;
		if (cmd == 0)
		{
			break;
		}
		else if (cmd == 1)
		{
			string denumire;
			int ore;
			string tip;
			string cadru_didactic;
			cout << "Denumire: ";
			getline(cin >> std::ws, denumire);
			cout << "Ore: ";
			cin >> ore;
			cout << "Tip: ";
			getline(cin >> std::ws, tip);
			cout << "Cadru didactic: ";
			getline(cin >> std::ws, cadru_didactic);
			try {
				srv.add(denumire, ore, tip, cadru_didactic);
				cout << "Subject succesfully added!\n";
			}
			catch (const RepoException& ex)
			{
				cout << ex.getMessage();
			}
			catch (ValidationException& ve)
			{
				cout << ve.getErrorMessage();
			}
			
		}
		else if (cmd == 2)
		{
			const auto& subjects = srv.getAll();
			if (subjects.size() == 0)
			{
				cout << "Nu exista discipline de afisat\n";
			}
			else
			{
				std::for_each(subjects.begin(), subjects.end(), [](const Subject& s) {cout << "Denumire: " << s.getDenumire() << " | Ore: " << s.getOre() << " | Tip: " << s.getTip() << " | Cadru didactic: " << s.getCadru() << "\n"; });

			}
		}
		else if (cmd == 3)
		{
			string denumire;
			int ore;
			string tip;
			string cadru_didactic;
			cout << "Denumire: ";
			getline(cin >> std::ws, denumire);
			cout << "Ore: ";
			cin >> ore;
			cout << "Tip: ";
			getline(cin >> std::ws, tip);
			cout << "Cadru didactic: ";
			getline(cin >> std::ws, cadru_didactic);
			try {
				srv.sterge(denumire, ore, tip, cadru_didactic);
				cout << "Subject succesfully deleted!\n";
			}
			catch(const RepoException& ex ) {
				cout << ex.getMessage();
			}
		}
		else if (cmd == 4)
		{
			string denumire;
			int ore;
			string tip;
			string cadru_didactic;
			cout << "Denumire: ";
			getline(cin >> std::ws, denumire);
			cout << "Ore: ";
			cin >> ore;
			cout << "Tip: ";
			getline(cin >> std::ws, tip);
			cout << "Cadru didactic: ";
			getline(cin >> std::ws, cadru_didactic);
			string denumire1;
			int ore1;
			string tip1;
			string cadru_didactic1;
			cout << "Denumire (new): ";
			getline(cin >> std::ws, denumire1);
			cout << "Ore (new): ";
			cin >> ore1;
			cout << "Tip (new): ";
			getline(cin >> std::ws, tip1);
			cout << "Cadru didactic (new): ";
			getline(cin >> std::ws, cadru_didactic1);
			try {
				srv.modifica(denumire, ore, tip, cadru_didactic, denumire1, ore1, tip1, cadru_didactic1);
				cout << "Subject modified succesfuly\n";
			}
			catch (const RepoException& ex)
			{
				cout << ex.getMessage();
			}
			catch (ValidationException& ve)
			{
				cout << ve.getErrorMessage();
			}
		}
		else if (cmd == 5)
		{
			string denumire;
			cout << "Denumire: ";
			getline(cin >> std::ws, denumire);
			try {
				auto s = srv.cauta(denumire);
				cout << "Denumire: " << s.getDenumire() << " | Ore: " << s.getOre() << " | Tip: " << s.getTip() << " | Cadru didactic: " << s.getCadru() << "\n";
			}
			catch (const RepoException& ex)
			{
				cout << ex.getMessage();
			}
		}
		else if (cmd == 6)
		{
			int cmd1 = 0;
			cout << "1. By ore\n2. By cadru didactic\n";
			cout << "Introduceti tipul filtrarii:";
			cin >> cmd1;
			if (cmd1 == 1) {
				int ore;
				cout << "Introduceti orele saptamanale: ";
				cin >> ore;
				const auto& rez = srv.filtrareOre(ore);
				if (rez.size() == 0)
				{
					cout << "Nu exista discipline cu acest numar de ore\n";
				}
				else {
					std::for_each(rez.begin(), rez.end(), [](const Subject& s) {cout << "Denumire: " << s.getDenumire() << " | Ore: " << s.getOre() << " | Tip: " << s.getTip() << " | Cadru didactic: " << s.getCadru() << "\n"; });
				}

			}
			else if (cmd1 == 2)
			{
				string cadru_didactic;
				cout << "Introduceti cadrul didactic: ";
				getline(cin >> std::ws, cadru_didactic);
				const auto& rez = srv.filtrareCadru(cadru_didactic);
				if (rez.size() == 0)
				{
					cout << "Nu exista discipline cu acest cadru\n";
				}
				else {
					std::for_each(rez.begin(), rez.end(), [](const Subject& s) {cout << "Denumire: " << s.getDenumire() << " | Ore: " << s.getOre() << " | Tip: " << s.getTip() << " | Cadru didactic: " << s.getCadru() << "\n"; });
				}
			}
		}
		else if (cmd == 7) {
			//int k;
			//sortare discipline dupa : denumire, nr ore, cadru didactic + tip * /
			int cmd2 = 0;
			cout << "1. By denumire\n2. By ore\n3. By cadru + tip\n";
			cout << "Introduceti comanda: ";
			cin >> cmd2;
			if (cmd2 == 1)
			{
				srv.sortDenumire();
			}
			else if (cmd2 == 2)
			{
				srv.sortOre();
			}
			else if (cmd2 == 3)
			{
				srv.sortCT();
			}
		}
		else if (cmd == 8)
		{
			string denumire;
			cout << "Denumire: ";
			cin >> denumire;
			try {
				const auto& rez = srv.addToContract(denumire);
				cout << "Contract: \n";
				std::for_each(rez.begin(), rez.end(), [](const Subject& s) {cout << "Denumire: " << s.getDenumire() << " | Ore: " << s.getOre() << " | Tip: " << s.getTip() << " | Cadru didactic: " << s.getCadru() << "\n"; });
			}
			catch (RepoException& ex) {
				cout << ex.getMessage();
			}
		}
		else if (cmd == 9)
		{
			const auto& subjects = srv.golesteContract();
			if (subjects.size() == 0)
			{
				cout << "Nu exista discipline de afisat\n";
			}
			else
			{
				cout << "Contract: \n";
				std::for_each(subjects.begin(), subjects.end(), [](const Subject& s) {cout << "Denumire: " << s.getDenumire() << " | Ore: " << s.getOre() << " | Tip: " << s.getTip() << " | Cadru didactic: " << s.getCadru() << "\n"; });

			}
		}
		else if (cmd == 10) {
			int cate;
			cout << "Cate discipline: ";
			cin >> cate;
			const auto& subjects = srv.addRandom(cate);
			if (subjects.size() == 0)
			{
				cout << "Nu exista discipline de afisat\n";
			}
			else
			{
				cout << "Contract: \n";
				std::for_each(subjects.begin(), subjects.end(), [](const Subject& s) {cout << "Denumire: " << s.getDenumire() << " | Ore: " << s.getOre() << " | Tip: " << s.getTip() << " | Cadru didactic: " << s.getCadru() << "\n"; });

			}
		}
		else if (cmd == 11)
		{
		if (srv.Par())
			cout << "Exista cel putin o disciplina cu numar par de ore!\n";
		else
			cout << "Nu exsta discipline cu nr par de ore!\n";
 }
		else {
			cout << "Comanda invalida!\n";
			continue;
		}
		continue;
	}
	
}