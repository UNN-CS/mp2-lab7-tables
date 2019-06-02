#include "TListHash.h"
#include "TSortTaable.h"
#include "TBalanceTree.h"
#include <iostream>
#include <string>
#include <vector>
#include <time.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

string Rand_String(const char* alph, int alph_size, int string_size) {
	string str;
	srand(time(NULL));
	for (int i = 0; i < string_size; i++) {
		str.push_back(alph[rand() % alph_size]);
	}

	return str;
}

int main() {
	const char alph[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };//26
	int rec_num = 100;
	string key;
	string rnd_key;

	for (rec_num = 100; rec_num < 1601; rec_num *= 2) {
		cout << endl << endl << "Number of records: " << rec_num << endl;

		TScanTable *scan_table = new TScanTable(rec_num);
		TSortTable *sort_table = new TSortTable(rec_num);
		sort_table->SetSortMethod(QUICK_SORT);
		TTreeTable *tree_table = new TTreeTable;
		TBalanceTree *balance_tree_table = new TBalanceTree;
		TListHash *list_hash_table = new TListHash(rec_num);

		//Инициализация
		for (int i = 0; i < rec_num - 1; i++) {
			key = Rand_String(alph, 26, 5);

			if (i == rec_num / 2)
				rnd_key = key;

			scan_table->InsRecord(key, nullptr);
			sort_table->InsRecord(key, nullptr);
			tree_table->InsRecord(key, nullptr);
			balance_tree_table->InsRecord(key, nullptr);
			list_hash_table->InsRecord(key, nullptr);
		}

		cout << endl << "Data count of scan table " <<scan_table->GetDataCount()<<endl;
		cout << endl << "Data count of sort table " << sort_table->GetDataCount() << endl;
		cout << endl << "Data count of tree table " << tree_table->GetDataCount() << endl;
		cout << endl << "Data count of balance tree table " << balance_tree_table->GetDataCount() << endl;
		cout << endl << "Data count of list hash table " << list_hash_table->GetDataCount() << endl;

		key = "AACDE";

		//Вставка
		cout << endl << "Insert record test" << endl;

		// Сброс параметра эффективности
		scan_table->ResetEfficiency();
		sort_table->ResetEfficiency();
		tree_table->ResetEfficiency();
		balance_tree_table->ResetEfficiency();
		list_hash_table->ResetEfficiency();
		scan_table->Reset();
		sort_table->Reset();
		tree_table->Reset();
		balance_tree_table->Reset();
		list_hash_table->Reset();

		scan_table->InsRecord(key, nullptr);
		sort_table->InsRecord(key, nullptr);
		tree_table->InsRecord(key, nullptr);
		balance_tree_table->InsRecord(key, nullptr);
		list_hash_table->InsRecord(key, nullptr);

		cout << "Scan table efficiency: " << scan_table->GetEfficiency() << endl;
		cout << "Sort table efficiency: " << sort_table->GetEfficiency() << endl;
		cout << "Tree table efficiency: " << tree_table->GetEfficiency() << endl;
		cout << "Bal tree table efficiency: " << balance_tree_table->GetEfficiency() << endl;
		cout << "List hash table efficiency: " << list_hash_table->GetEfficiency() << endl;

		//Поиск
		cout << endl << "Search efficiency test" << endl;

		// Сброс параметра эффективности
		scan_table->ResetEfficiency();
		sort_table->ResetEfficiency();
		tree_table->ResetEfficiency();
		balance_tree_table->ResetEfficiency();
		list_hash_table->ResetEfficiency();
		scan_table->Reset();
		sort_table->Reset();
		tree_table->Reset();
		balance_tree_table->Reset();
		list_hash_table->Reset();

		scan_table->FindRecord(rnd_key);
		sort_table->FindRecord(rnd_key);
		tree_table->FindRecord(rnd_key);
		balance_tree_table->FindRecord(rnd_key);
		list_hash_table->FindRecord(rnd_key);

		cout << "Scan table efficiency: " << scan_table->GetEfficiency() << endl;
		cout << "Sort table efficiency: " << sort_table->GetEfficiency() << endl;
		cout << "Tree table efficiency: " << tree_table->GetEfficiency() << endl;
		cout << "Bal tree table efficiency: " << balance_tree_table->GetEfficiency() << endl;
		cout << "List hash table efficiency: " << list_hash_table->GetEfficiency() << endl;

		//Удаление
		cout << endl << "Removal efficiency test" << endl;

		// Сброс параметра эффективности
		scan_table->ResetEfficiency();
		sort_table->ResetEfficiency();
		tree_table->ResetEfficiency();
		balance_tree_table->ResetEfficiency();
		list_hash_table->ResetEfficiency();
		scan_table->Reset();
		sort_table->Reset();
		tree_table->Reset();
		balance_tree_table->Reset();
		list_hash_table->Reset();

		scan_table->DelRecord(rnd_key);
		sort_table->DelRecord(rnd_key);
		tree_table->DelRecord(rnd_key);
		balance_tree_table->DelRecord(rnd_key);
		list_hash_table->DelRecord(rnd_key);

		cout << "Scan table efficiency: " << scan_table->GetEfficiency() << endl;
		cout << "Sort table efficiency: " << sort_table->GetEfficiency() << endl;
		cout << "Tree table efficiency: " << tree_table->GetEfficiency() << endl;
		cout << "Bal tree table efficiency: " << balance_tree_table->GetEfficiency() << endl;
		cout << "List hash table efficiency: " << list_hash_table->GetEfficiency() << endl;

		delete scan_table;
		delete sort_table;
		delete tree_table;
		delete balance_tree_table;
		delete list_hash_table;
	}
	return 0;
}
