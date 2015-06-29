#ifndef STOCK00_H
#define STOCK00_H

#include <string>

//class declaration
class Stock{
private:
	std::string company;
	long shares;
	double share_val;
	double total_val;
	//inline fun
	void set_tol(){ total_val = shares*share_val; }
public:
	void acqurire(const std::string &co, long n, double pr);
	void buy(long sum, double price);
	void sell(long sum, double price);
	void update(double price);
	void show();
};//note the fenhao at the end

#endif