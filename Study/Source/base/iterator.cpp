#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int strout()
{
	cout<<"i am here"<<endl;
	return 0;
}

// Return whether first element is greater than the second
bool UDgreater ( int elem1, int elem2 )
{
	return elem1 > elem2;
}



int main()
{
	cout<<"hello"<<endl;
	strout();


	/************************************************************************/
	/* vector容器的迭代器测试                                               */
	/************************************************************************/
	//定义并赋值输出   
	vector<int> ivec;   
	cout<<"Befort *2 the elements are:"<<endl;   
	for(vector<int>::size_type ix=0; ix!=10;++ix)
	{
		ivec.push_back(ix);   
		cout<<ivec[ix]<<' ';   
	}   
	//把每个值乘以2并输出   
	cout<<endl<<"After *2 the elements are:"<<endl;   
	for(vector<int>::iterator iter=ivec.begin(); iter!=ivec.end();++iter)  
	{   
		*iter*=2; cout<<*iter<<' ';   
	} 
	/************************************************************************/
	/*    sort() function                                               */
	/************************************************************************/
	vector <int> v1;
	vector <int>::iterator Iter1;

	int i;
	for ( i = 0 ; i <= 5 ; i++ )
	{
		v1.push_back( 2 * i );
	}

	int ii;
	for ( ii = 0 ; ii <= 5 ; ii++ )
	{
		v1.push_back( 2 * ii + 1 );
	}

	cout << endl<<"Original vector v1 = ( " ;
	for ( Iter1 = v1.begin( ) ; Iter1 != v1.end( ) ; Iter1++ )
		cout << *Iter1 << " ";
	cout << ")" << endl;

	sort( v1.begin( ), v1.end( ) ); //默认是升序排列
	cout << "Sorted vector v1 = ( " ;
	for ( Iter1 = v1.begin( ) ; Iter1 != v1.end( ) ; Iter1++ )
		cout << *Iter1 << " ";
	cout << ")" << endl;

	// To sort in descending order. specify binary predicate
	sort( v1.begin( ), v1.end( ), greater<int>( ) );
	cout << "Resorted (greater) vector v1 = ( " ;
	for ( Iter1 = v1.begin( ) ; Iter1 != v1.end( ) ; Iter1++ )
		cout << *Iter1 << " ";
	cout << ")" << endl;

	// A user-defined (UD) binary predicate can also be used
	sort( v1.begin( ), v1.end( ), UDgreater );
	cout << "Resorted (UDgreater) vector v1 = ( " ;
	for ( Iter1 = v1.begin( ) ; Iter1 != v1.end( ) ; Iter1++ )
		cout << *Iter1 << " ";
	cout << ")" << endl;

	getchar();
	return 0;  
}
