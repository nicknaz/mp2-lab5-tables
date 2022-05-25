#include <iostream>
#include <string>
#include "../include/unorderedTable.h"
#include "../include/RBTree.h"
#include "../include/hash_table.h"
#include "../include/Logger.h"
#include "../mp2-lab4-polinoms/include/list.h"
#include "../mp2-lab4-polinoms/include/Polinom.h"

void setPolinom(std::string key, Polinom &poli, HashQuadroTable<std::string, Polinom> &ht, UnorderedTable<std::string, Polinom> &ut, RBTree<std::string, Polinom> &rbt)
{
	ht.insertNode(key, &poli);
	ut.insert(key, poli);
	rbt.Insert(key, &poli);
	std::cout << ht;
	std::cout << ut;
}

int main()
{
	/*RBTree<std::string, int> RBT1;
	int a = 1, b = 2, c = 3;
	RBT1.Insert("key1", &a);
	RBT1.Insert("key2", &b);
	RBT1.Insert("key3", &c);

	std::cout << *RBT1.GetValue("key2");*/

	Logger logger;
	HashQuadroTable<std::string, Polinom> HT;
	UnorderedTable<std::string, Polinom> UT;
	RBTree<std::string, Polinom> RBT;
	while (true)
	{
		std::cout << "***MENU***\n";
		std::cout << "What you want?\n";
		std::cout << "1 - Add polinom\n";
		std::cout << "2 - Get polinom\n";
		std::cout << "3 - Action for polinom\n";
		std::cout << "4 - polinom1 * number\n";
		int choose;
		int choose2 = 1;
		std::string key;
		std::string key2;
		std::string key3;
		std::cin >> choose;
		switch (choose)
		{
		case 1:
		{
			logger.DebugLog("User add polinom");
			std::cout << "key: ";
			std::cin >> key;
			Polinom polinom1;
			setPolinom(key, polinom1, HT, UT, RBT);
		}
			break;
		case 2:
			std::cout << "key: ";
			std::cin >> key;
			logger.DebugLog("User get polinom with key: "+key);
			std::cout << "UT_POLI: " << UT.getValue(key) << std::endl;
			std::cout << "RBT_POLI: " << *RBT.GetValue(key) << std::endl;
			std::cout << "HT_POLI: " << *HT.getValue(key) << std::endl;
			break;
		case 3:
		{
			int choose = 0;
			std::cout << "key1: ";
			std::cin >> key;
			std::cout << "key2: ";
			std::cin >> key2;

			std::cout << "You want add result in table? 1/0\n";
			std::cin >> choose2;
			if (choose2)
			{
				std::cout << "key for new polinom: ";
				std::cin >> key3;
			}
			std::cout << "What you want?\n";
			std::cout << "1 - polinom1 + polinom2\n";
			std::cout << "2 - polinom1 * polinom2\n";
			std::cout << "3 - polinom1 - polinom2\n";
			std::cin >> choose;
			Polinom *res;
			switch (choose)
			{
			case 1:
			{
				std::cout << "polinom1 + polinom2 = " << UT.getValue(key) + UT.getValue(key2) << std::endl;
				logger.DebugLog("User sum two poli");
				res = &(UT.getValue(key) + UT.getValue(key2));
				if (choose2)
					setPolinom(key3, *res, HT, UT, RBT);
				break;
			}
			case 2:
				std::cout << "polinom1 * polinom2 = " << UT.getValue(key) * UT.getValue(key2) << std::endl;
				logger.DebugLog("User multiply two poli");
				res = &(UT.getValue(key) * UT.getValue(key2));
				if (choose2)
					setPolinom(key3, *res, HT, UT, RBT);
				break;
			case 3:
				std::cout << "polinom1 - polinom2 = " << UT.getValue(key) - UT.getValue(key2) << std::endl;
				logger.DebugLog("User subtraction two poli");
				res = &(UT.getValue(key) - UT.getValue(key2));
				if (choose2)
					setPolinom(key3, *res, HT, UT, RBT);
				break;
			default:
				break;
			}
			break;
		}
		case 4:
			
			break;
		default:
			break;
		}
	}
	/*
	HashQuadroTable<std::string, int> h;
	h.insertNode("key1", 1);
	h.insertNode("key2", 1);
	h.insertNode("key3", 1);
	h.insertNode("key4", 1);
	

	std::cout << h;
	cout << h.getSize() << endl;
	//cout << h->deleteNode(2) << endl;
	cout << h.getSize() << endl;
	cout << h.isEmpty() << endl;
	cout << h.getValue("key1");*/
	return 0;
}
