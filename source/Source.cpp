// An-memory item database
#include "Header.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

//int GameItem::numItems = 0;

int main() {
	ItemDatabase data;
	int selectedOption;
	map<string, GameItem*>::iterator it;

	do {
		cout << "\nWhat would you like to do?\n(1) Add new item\n(2) Find an item\n";
		cout << "(3) Remove an item\n(4) Check database occupancy\n(0) Exit\n:";
		cin >> selectedOption;

		switch( selectedOption ) {
		case 0:
			break;
		case 1:
			data.addNewItem();
			break;
		case 2:
			try {
				it = data.findItem();
				it->second->printInfo();
				break;
			} catch (invalid_argument ia) {
				cout << ia.what() << endl;
				break;
			}
		case 3:
			try {
				it = data.findItem();
				data.remItem(it);
				break;
			} catch (invalid_argument ia) {
				cout << ia.what() << endl;
				break;
			}
		case 4:
			cout << "Number of items in database: " << data.size() << endl;
			break;
		}

	} while ( selectedOption != 0 );


	////Hard-coded test values
	//string itemName = "Valor Coronet";
	//int itemLevel = 90;
	//int reqLevel = 50;
	//int sellsFor = 917;
	//int stackSize = 1;
	//bool UNIQUE = true;
	//bool UNTRADABLE = true;
	//vector<pair<string, int>> stats;
	//vector<string> reqClasses;
	//string slot = "Head";
	//int pDefense = 113;
	//int mDefense = 113;
	//int pDamage = 46;
	//int mDamage = 69;
	//float delay = 3.44f;
	//float autoAttack = 52.75f;
	//float DPS = 15.33f;
	//int blockRate = 118;
	//int blockStrength = 118;

	//stats.push_back(pair<string, int>("Strength", 18));
	//stats.push_back(pair<string, int>("Vitality", 20));
	//stats.push_back(pair<string, int>("Critical hit rate", 15));
	//stats.push_back(pair<string, int>("Accuracy", 21));

	//reqClasses.push_back("PLD");
	//reqClasses.push_back("MRD");

	////Instantiate a test piece of armor
	//Armor valorCoronet(itemName, itemLevel, reqLevel, sellsFor, stackSize, UNIQUE, UNTRADABLE, stats, reqClasses, slot, pDefense, mDefense);

	////Change value of variables and define a weapon
	//itemName = "Stardust Rod";
	//slot = "2H Weapon";
	//stats.clear();
	//stats.push_back(pair<string, int>("Vitality", 32));
	//stats.push_back(pair<string, int>("Intelligence", 31));
	//stats.push_back(pair<string, int>("Determination", 18));
	//stats.push_back(pair<string, int>("Spell Speed", 37));
	//reqClasses.clear();
	//reqClasses.push_back("BLM");
	//sellsFor = 1622;

	////Instatiate a weapon
	//Weapon stardustRod(itemName, itemLevel, reqLevel, sellsFor, stackSize, UNIQUE, UNTRADABLE, stats, reqClasses, slot, pDamage, mDamage, delay, autoAttack, DPS);

	////Display info for test armor
	//valorCoronet.printInfo();
	////Display info for test weapon
	//cout << '\n';
	//stardustRod.printInfo();
	//cout << '\n';
	//cout << "Number of items in database: " << GameItem::getNumItems() << endl;

	return 0;
}

void Armor::printInfo() const {
	printDivider();
	printStatLine("Item name", itemName);
	printStatLine("Slot", slot);
	string rClasses;
	for (unsigned i = 0; i < reqClasses.size(); ++i) {
		rClasses += reqClasses[i];
		rClasses += " ";
	}
	printStatLine("Requires", rClasses);
	cout << "\n";

	printStatLine("Defense", pDefense);
	printStatLine("Magic Defense", mDefense);
	cout << "\n";

	Gear::printInfo();
}

void Weapon::printInfo() const {
	printDivider();
	cout << setw(21) << left << "Item name:" << itemName << endl;
	cout << setw(21) << left << "Slot:" << slot << endl;
	string rClasses;
	for (unsigned i = 0; i < reqClasses.size(); ++i) {
		rClasses += reqClasses[i];
		rClasses += " ";
	}
	cout << setw(21) << left << "Requires:" << rClasses << endl;
	cout << "\n";
	cout << setw(21) << left << "Damage:" << pDamage << endl;
	cout << setw(21) << left << "Magic Damage:" << mDamage << endl;
	cout << setw(21) << left << "Delay:" << delay << endl;
	cout << setw(21) << left << "Auto-attack:" << autoAttack << endl;
	cout << setw(21) << left << "DPS:" << DPS << endl;
	cout << "\n";
	Gear::printInfo();
}

void Shield::printInfo() const {
	printDivider();
	cout << setw(21) << left << "Item name:" << itemName << endl;
	cout << setw(21) << left << "Slot:" << slot << endl;
	string rClasses;
	for (unsigned i = 0; i < reqClasses.size(); ++i) {
		rClasses += reqClasses[i];
		rClasses += " ";
	}
	cout << setw(21) << left << "Requires:" << rClasses << endl;
	cout << "\n";
	cout << setw(21) << left << "Block rate:" << blockRate << endl;
	cout << setw(21) << left << "Block strength:" << blockStrength << endl;
	cout << "\n";
	Gear::printInfo();
}

void Item::printInfo() const {
	printDivider();
	cout << setw(21) << left << "Item name:" << itemName << endl;
	cout << "\n";
	cout << description << endl;
	cout << "\n";
	if (UNIQUE) cout << "UNIQUE" << endl;
	if (UNTRADABLE) cout << "UNTRADABLE" << endl;
	cout << "\n";
	cout << setw(21) << left << "Item level:" << itemLevel << endl;
	cout << setw(21) << left << "Required level:" << reqLevel << endl;
	cout << "\n";
	cout << setw(21) << left << "Sells for:" << sellsFor << " Gil" << endl;
	cout << setw(21) << left << "Stack size:" << stackSize << endl;
	printDivider();
}

void Gear::printInfo() const {
	for (unsigned i = 0; i < stats.size(); ++i) {
		cout << setw(21) << left << stats[i].first + ":" << stats[i].second << endl;
	}
	cout << "\n";
	if (UNIQUE) cout << "UNIQUE" << endl;
	if (UNTRADABLE) cout << "UNTRADABLE" << endl;
	cout << "\n";
	cout << setw(21) << left << "Item level:" << itemLevel << endl;
	cout << setw(21) << left << "Required level:" << reqLevel << endl;
	cout << "\n";
	cout << setw(21) << left << "Sells for:" << sellsFor << " Gil" << endl;
	cout << setw(21) << left << "Stack size:" << stackSize << endl;
	printDivider();
}

void printDivider() {
	string divider = "++--------------------------------++";
	cout << divider << endl;
}

//Main-function functions
void ItemDatabase::addNewItem() {
	int selection;
	cout << "What type of item do you want to add?\n(1)Weapon\n(2)Shield\n(3)Armor\n(4)Item\n:";
	cin >> selection;

	switch( selection ) {
	case 1:
		ItemDatabase::addWeapon();
		break;
	case 2:
		ItemDatabase::addShield();
		break;
	case 3:
		ItemDatabase::addArmor();
		break;
	case 4:
		ItemDatabase::addItem();
		break;
	default:
		cout << "Action canceled, returning to main menu." << endl;
		break;
	}
}

void ItemDatabase::addWeapon() {
	string itemName;
	string slot = "Weapon";
	int itemLevel;
	int reqLevel;
	int sellsFor;
	int stackSize;
	bool UNIQUE;
	bool UNTRADABLE;
	string tempStatName;
	int tempStatVal;
	vector< pair<string, int> > stats;
	string tempClass;
	vector<string> reqClasses;
	int pDamage;
	int mDamage;
	float delay;
	float autoAttack;
	float DPS;

	cout << "Item name: ";
	cin.ignore();
	getline(cin, itemName);

	while(true) {
		cout << "Required classes (0 when done): ";
		cin >> tempClass;
		if (tempClass != "0")
			reqClasses.push_back(tempClass);
		else
			break;
	}
	cout << "Damage: ";
	cin >> pDamage;
	cout << "Magic Damage: ";
	cin >> mDamage;
	cout << "Delay: ";
	cin >> delay;
	cout << "Auto-attack: ";
	cin >> autoAttack;
	cout << "DPS: ";
	cin >> DPS;

	while(true) {
		cout << "Stat name (0 when done): ";
		cin.ignore();
		getline(cin, tempStatName);
		if (tempStatName != "0") {
			cout << tempStatName + " value: ";
			cin >> tempStatVal;
			stats.push_back(pair<string, int>(tempStatName, tempStatVal));
		}
		else
			break;
	}

	cout << "Unique (0/1)?";
	cin >> UNIQUE;
	cout << "Untradable (0/1)?";
	cin >> UNTRADABLE;

	cout << "Item level: ";
	cin >> itemLevel;
	cout << "Required level: ";
	cin >> reqLevel;
	cout << "Sells for: ";
	cin >> sellsFor;
	cout << "Stack size: ";
	cin >> stackSize;

	Weapon *newWeapon = new Weapon(itemName, itemLevel, reqLevel, sellsFor, stackSize, UNIQUE, UNTRADABLE, stats, reqClasses, slot, pDamage, mDamage, delay, autoAttack, DPS);
	database[itemName] = newWeapon;
}

void ItemDatabase::addShield() {
	string itemName;
	string slot = "Off-hand";
	int itemLevel;
	int reqLevel;
	int sellsFor;
	int stackSize;
	bool UNIQUE;
	bool UNTRADABLE;
	string tempStatName;
	int tempStatVal;
	vector< pair<string, int> > stats;
	string tempClass;
	vector<string> reqClasses;
	int blockRate;
	int blockStrength;

	cout << "Item name: ";
	cin.ignore();
	getline(cin, itemName);

	while(true) {
		cout << "Required classes (0 when done): ";
		cin >> tempClass;
		if (tempClass != "0")
			reqClasses.push_back(tempClass);
		else
			break;
	}
	cout << "Block Rate: ";
	cin >> blockRate;
	cout << "Block Strength: ";
	cin >> blockStrength;

	while(true) {
		cout << "Stat name (0 when done): ";
		cin.ignore();
		getline(cin, tempStatName);
		if (tempStatName != "0") {
			cout << tempStatName + " value: ";
			cin >> tempStatVal;
			stats.push_back(pair<string, int>(tempStatName, tempStatVal));
		}
		else
			break;
	}

	cout << "Unique (0/1)?";
	cin >> UNIQUE;
	cout << "Untradable (0/1)?";
	cin >> UNTRADABLE;

	cout << "Item level: ";
	cin >> itemLevel;
	cout << "Required level: ";
	cin >> reqLevel;
	cout << "Sells for: ";
	cin >> sellsFor;
	cout << "Stack size: ";
	cin >> stackSize;

	Shield *newShield = new Shield(itemName, itemLevel, reqLevel, sellsFor, stackSize, UNIQUE, UNTRADABLE, stats, reqClasses, slot, blockRate, blockStrength);
	database[itemName] = newShield;
}

void ItemDatabase::addArmor() {
	string itemName;
	string slot;
	int itemLevel;
	int reqLevel;
	int sellsFor;
	int stackSize;
	bool UNIQUE;
	bool UNTRADABLE;
	string tempStatName;
	int tempStatVal;
	vector< pair<string, int> > stats;
	string tempClass;
	vector<string> reqClasses;
	int pDefense;
	int mDefense;

	cout << "Item name: ";
	cin.ignore();
	getline(cin, itemName);
	cout << "Slot: ";
	//cin.ignore();
	getline(cin, slot);

	while(true) {
		cout << "Required classes (0 when done): ";
		cin >> tempClass;
		if (tempClass != "0")
			reqClasses.push_back(tempClass);
		else
			break;
	}
	cout << "Defense: ";
	cin >> pDefense;
	cout << "Magic Defense: ";
	cin >> mDefense;

	while(true) {
		cout << "Stat name (0 when done): ";
		cin.ignore();
		getline(cin, tempStatName);
		if (tempStatName != "0") {
			cout << tempStatName + " value: ";
			cin >> tempStatVal;
			stats.push_back(pair<string, int>(tempStatName, tempStatVal));
		}
		else
			break;
	}

	cout << "Unique (0/1)?";
	cin >> UNIQUE;
	cout << "Untradable (0/1)?";
	cin >> UNTRADABLE;

	cout << "Item level: ";
	cin >> itemLevel;
	cout << "Required level: ";
	cin >> reqLevel;
	cout << "Sells for: ";
	cin >> sellsFor;
	cout << "Stack size: ";
	cin >> stackSize;

	Armor *newArmor = new Armor(itemName, itemLevel, reqLevel, sellsFor, stackSize, UNIQUE, UNTRADABLE, stats, reqClasses, slot, pDefense, mDefense);
	database[itemName] = newArmor;
}

void ItemDatabase::addItem() {
	string itemName;
	string description;
	int itemLevel;
	int reqLevel;
	int sellsFor;
	int stackSize;
	bool UNIQUE;
	bool UNTRADABLE;

	cout << "Item name: ";
	cin.ignore();
	getline(cin, itemName);

	cout << "Description: ";
	//cin.ignore();
	getline(cin, description);

	//Debug
	cout << description << endl;

	cout << "Unique (0/1)?";
	cin >> UNIQUE;
	cout << "Untradable (0/1)?";
	cin >> UNTRADABLE;

	cout << "Item level: ";
	cin >> itemLevel;
	cout << "Required level: ";
	cin >> reqLevel;
	cout << "Sells for: ";
	cin >> sellsFor;
	cout << "Stack size: ";
	cin >> stackSize;

	Item *newItem = new Item(itemName, itemLevel, reqLevel, sellsFor, stackSize, UNIQUE, UNTRADABLE, description);
	database[itemName] = newItem;
}

map<string, GameItem*>::iterator ItemDatabase::findItem() {
	string searchName;
	map<string, GameItem*>::iterator it;

	cout << "Enter name of item to be found: ";
	cin.ignore();
	getline(cin, searchName);
	it = database.find(searchName);
	if (it != database.end())
		return it;
	else
		throw invalid_argument("--Item not found!--");
}

void ItemDatabase::remItem(map<string, GameItem*>::iterator it) {
	delete it->second;
	database.erase(it);
	cout << "--Item deleted!--" << endl;
}
/*
 * Source.cpp
 *
 *  Created on: Feb 14, 2014
 *      Author: dean
 */




