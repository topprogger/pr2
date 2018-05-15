#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

#include "data.cpp"
using namespace std;

class DataBase
{
	int last_inserted_id;
	vector<Cost*> db;

public:
	DataBase() : last_inserted_id(1)
	{
		db.resize(0);	
	}
	~DataBase()
	{
		for (int i = 0; i < db.size(); i++) {
			delete db[i];
		}
	}

	int count()
	{
		return db.size();
	}

	void add(Cost *new_item)
	{
		db.push_back(new_item);
	}	

	Cost* edit(int id)
	{
		id--;
		return db.at(id);
	}

	void remove(int id)
	{
		id--;
		db.erase(db.begin() + id);
	}

	void view()
	{
		cout << setfill(' ')
			 << setw(6) << "ID|" << setfill(' ') << setw(35) << "Caption|" << setw(12) << "Price|" << setw(12) << "Count|" << setw(12) << "Date|" << '\n';
		cout << setfill('-') << setw(80) << '\n' << setfill(' ');
		for (int i = 0; i < db.size(); i++) {
			cout << setw(5) << (i+1) << "|" 
				 << setw(34) << db[i]->getCaption() << "|" 
				 << setw(11) << db[i]->getPrice() << "|"
				 << setw(11) << db[i]->getCount() << "|" 
				 << setw(11) << db[i]->getDate() << "|" << '\n';
		}
	}
	
	void view(int i)
	{
		i--;
	
		cout << setfill(' ')
			 << setw(6) << "ID|" << setfill(' ') << setw(35) << "Caption|" << setw(12) << "Price|" << setw(12) << "Count|" << setw(12) << "Date|" << '\n';
		cout << setfill('-') << setw(80) << '\n' << setfill(' ');
		cout << setw(5) << (i+1) << "|" 
			 << setw(34) << db[i]->getCaption() << "|" 
			 << setw(11) << db[i]->getPrice() << "|"
			 << setw(11) << db[i]->getCount() << "|" 
			 << setw(11) << db[i]->getDate() << "|" << '\n';
	}

};

