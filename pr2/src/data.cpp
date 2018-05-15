#pragma once

#include <string>
using namespace std;

class Cost
{
	string cost_caption;
	int cost_price;
	int cost_count;
	string cost_date;

public:
	Cost(string Ccaption, int price, int count, string Cdate) :
		 cost_caption(caption), cost_price(price), cost_count(count), cost_date(date)
	{}
	
	string getCaption()
	{
		return cost_caption;
	}

	void setCaption(string caption)
	{
		cost_caption = caption;
	}

	int getPrice()
	{
		return cost_price;
	}
	
	void setPrice(int price)
	{
		cost_price = price;
	}

	int getCount()
	{
		return cost_count;
	}

	void setCount(int count)
	{
		cost_count = count;
	}

	string getDate()
	{
		return cost_date;
	}
	
	void setDate(string date)
	{
		cost_date = date;
	}

};

