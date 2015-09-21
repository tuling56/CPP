#include "stock00.h"
#include <iostream>

using namespace  std;


void Stock::acqurire(const string &co, long n, double pr)
{
	company = co;
	shares = n;
	share_val = pr;
}

void Stock::sell(long sum,double price){
	shares -= sum;
	total_val -= price*sum;
}

void Stock::buy(long sum,double price){
	shares += sum;
	total_val += sum*price;
}

void Stock::show(){
	cout << "share_val:" << share_val << endl;
	cout << "shares:" << shares << endl;
	set_tol();
	cout << "total_val:" << total_val << endl;
}

void Stock::update(double price){
	share_val = price;
}


//²âÊÔ½Ó¿Ú
//int main()
//{
//	Stock s1;
//	Stock s2;
//
//	s1.acqurire("heli", 10, 24);
//	s1.show();
//
//	s1.sell(3, 5);
//	s1.show();
//
//	getchar();
//
//	return 0;
//
//}