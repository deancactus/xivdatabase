/*
 * Header.h
 *
 *  Created on: Feb 14, 2014
 *      Author: dean
 */


#include <iostream>
#include <iomanip>
#include <string>
#include <utility>	//pair<> class
#include <vector>	//vector<> class
#include <map>		//map<pair<key, value>> class

using namespace std;

void printDivider();
//void addNewItem();
//void addWeapon();

template<class T>
void printStatLine(const string &statName, const T &statValue) {
	cout << setw(21) << left << statName + ":" << statValue << endl;
}

class GameItem {
//public:
	//static int numItems;	//Number of instances of game items
protected:
	string itemName;	//Item name
	int itemLevel;		//Item level
	int reqLevel;		//Required level
	int sellsFor;		//Amount of gil item can be vendored for
	int stackSize;		//Stack size
	bool UNIQUE;		//Whether or not item is unique
	bool UNTRADABLE;	//Whether or not item is tradable

	GameItem(const string &myitemName, const int &myitemLevel, const int &myreqLevel, const int &mysellsFor, const int &mystackSize, const bool &myUNIQUE, const bool &myUNTRADABLE)
	: itemName(myitemName), itemLevel(myitemLevel), reqLevel(myreqLevel), sellsFor(mysellsFor), stackSize(mystackSize), UNIQUE(myUNIQUE), UNTRADABLE(myUNTRADABLE) {}

public:
	virtual void printInfo() const = 0; //Pure virtual
	virtual ~GameItem() {
		cout << "GameItem destructor called!\n";
	}
	//static int getNumItems() {return numItems;}
};

class Gear : public GameItem {
protected:
	vector<pair<string, int> > stats;	//Types of stats and their corresponding values
	vector<string> reqClasses;			//Three letter class/job abbv.s
	string slot;						//Slot to which the gear can be equipped
	virtual void printInfo() const; // Defined in Source.cpp

	Gear(const string &myitemName, const int &myitemLevel, const int &myreqLevel, const int &mysellsFor, const int &mystackSize, const bool &myUNIQUE, const bool &myUNTRADABLE, const vector< pair<string, int> > &mystats, const vector<string> &myreqClasses, const string &myslot)
	: GameItem(myitemName, myitemLevel, myreqLevel, mysellsFor, mystackSize, myUNIQUE, myUNTRADABLE), stats(mystats), reqClasses(myreqClasses), slot(myslot) {}
	virtual ~Gear() {
		cout << "Gear destructor called!\n";
	}

};

class Armor : public Gear {
protected:
	int pDefense;		//Defense
	int mDefense;		//Magic defense
public:
	Armor(const string &myitemName, const int &myitemLevel, const int &myreqLevel, const int &mysellsFor, const int &mystackSize, const bool &myUNIQUE, const bool &myUNTRADABLE, const vector< pair<string, int> > &mystats, const vector<string> &myreqClasses, const string &myslot, const int mypDefense, const int mymDefense)
	: Gear(myitemName, myitemLevel, myreqLevel, mysellsFor, mystackSize, myUNIQUE, myUNTRADABLE, mystats, myreqClasses, myslot), pDefense(mypDefense), mDefense(mymDefense) {}

	virtual void printInfo() const; //Must now be defined
	virtual ~Armor() {}
};

class Weapon : public Gear {
protected:
	int pDamage;		//Physical damage
	int mDamage;		//Magic damage
	float delay;		//Delay
	float autoAttack;	//Auto-attack
	float DPS;			//DPS
public:
	Weapon(const string &myitemName, const int &myitemLevel, const int &myreqLevel,
			const int &mysellsFor, const int &mystackSize, const bool &myUNIQUE,
			const bool &myUNTRADABLE, const vector< pair<string, int> > &mystats,
			const vector<string> &myreqClasses, const string &myslot,
			const int &mypDamage, const int &mymDamage, const float &mydelay,
			const float &myautoAttack, const float &myDPS)
	: Gear(myitemName, myitemLevel, myreqLevel, mysellsFor, mystackSize, myUNIQUE, myUNTRADABLE, mystats, myreqClasses, myslot),
	  pDamage(mypDamage), mDamage(mymDamage), delay(mydelay), autoAttack(myautoAttack), DPS(myDPS) {}
	virtual void printInfo() const; //Must now be defined
	virtual ~Weapon() {
		cout << "Weapon destructor called!\n";
	}
};

class Shield : public Gear {
protected:
	int blockRate;		//Block rate
	int blockStrength;	//Block strength
public:
	Shield(const string &myitemName, const int &myitemLevel, const int &myreqLevel,
			const int &mysellsFor, const int &mystackSize, const bool &myUNIQUE,
			const bool &myUNTRADABLE, const vector< pair<string, int> > &mystats,
			const vector<string> &myreqClasses, const string &myslot,
			const int &myblockRate, const int &myblockStrength)
	: Gear(myitemName, myitemLevel, myreqLevel, mysellsFor, mystackSize, myUNIQUE, myUNTRADABLE, mystats, myreqClasses, myslot),
	  blockRate(myblockRate), blockStrength(myblockStrength) {}
	virtual void printInfo() const; //Must now be defined
	virtual ~Shield() {}
};

class Item : public GameItem {
protected:
	string description;
public:
	Item(const string &myitemName, const int &myitemLevel, const int &myreqLevel, const int &mysellsFor, const int &mystackSize, const bool &myUNIQUE, const bool &myUNTRADABLE, const string &mydescription)
	: GameItem(myitemName, myitemLevel, myreqLevel, mysellsFor, mystackSize, myUNIQUE, myUNTRADABLE),
	  description(mydescription) {}

	virtual void printInfo() const; //Defined in Source.cpp
	virtual ~Item() {}
};

class ItemDatabase {
public:
	map<string, GameItem*> database;
	void addNewItem();
	void addWeapon();
	void addArmor();
	void addShield();
	void addItem();
	map<string, GameItem*>::iterator findItem();
	void remItem(map<string, GameItem*>::iterator it);
	int size() { return database.size(); }

	~ItemDatabase() {
		cout << "ItemDatabase destructor called!\n";
		for (map<string, GameItem*>::iterator it = database.begin(); it != database.end(); database.erase(it++)) {
			delete it->second;
		}
	}
};
