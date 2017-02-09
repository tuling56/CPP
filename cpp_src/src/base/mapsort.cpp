/************************************************************************
* Copyright(c) 2015 tuling56
*
* File:	mapsort.cpp
* Brief: map≈≈–ÚŒ Ã‚
* Reference:http://www.cplusplus.com/reference/map/map/insert/
* Status: 
* Date:	[6/25/2015 jmy]
************************************************************************/
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

typedef map<string, int>::value_type myMap;

//Ωµ–Ú≈≈¡–
bool compWordCnt(pair<string, int> s1, pair<string, int> s2)
{
	if (s1.second >=s2.second)
		return false;
	else
		return true;
}

int main()
{
	map<string, int> word_cnt;

	//map insert 
	word_cnt.insert(myMap("hang", 3));
    word_cnt.insert(myMap("zhai", 4));

	pair<string, int> mpair = make_pair("ad4", 7);
	word_cnt.insert(mpair);


	pair<map<string, int>::iterator, bool> ret;
	ret = word_cnt.insert(pair<string, int>("dd4", 4));
	if (ret.second==false){
		cout << ret.first->first<< " already extist with a value of " << ret.first->second << endl;
	}
	else{
		cout << ret.first->first<<" doesn't exist" << endl;
	}
	
	//map iterator
	cout << "------------------≈≈–Ú«∞------------------------" << endl;
	for (map<string, int>::iterator it = word_cnt.begin(); it != word_cnt.end(); ++it){
		cout << "String:"<<it->first << "  Cnt:" << (it->second) << endl;
	}

	//map convert to vector
	vector<pair<string, int>> v_word_cnt;
	for (map<string, int>::iterator it = word_cnt.begin(); it != word_cnt.end(); ++it){
		v_word_cnt.push_back(*it);
	}


	//map sort
	cout << "------------------≈≈–Ú∫Û------------------------" << endl;
	sort(v_word_cnt.begin(), v_word_cnt.end(), compWordCnt);
	for (vector<pair<string, int>>::iterator it = v_word_cnt.begin(); it != v_word_cnt.end();++it)
	{
		cout << "String:" << it->first << "  Cnt:" << it->second << endl;
	}
	
	getchar();

	return 0;

}
