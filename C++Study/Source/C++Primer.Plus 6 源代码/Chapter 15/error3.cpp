// error3.cpp -- using an exception
#include <iostream>
double hmean(double a, double b);

//int main()
int error3()
{
    double x, y, z;

    std::cout << "Enter two numbers: ";
    while (std::cin >> x >> y)
    {
        try {                   // start of try block
            z = hmean(x,y);
        }                       // end of try block
		//处理程序以catch开头，随后是位于括号中的类型声明，它指出了异常处理程序要响应的异常类型
        catch (const char * s)  // start of exception handler
        {
            std::cout << s << std::endl;
            std::cout << "Enter a new pair of numbers: ";
            continue;
        }                       // end of handler
		
        std::cout << "Harmonic mean of " << x << " and " << y
            << " is " << z << std::endl;
        std::cout << "Enter next set of numbers <q to quit>: ";
    }
    std::cout << "Bye!\n";
    return 0;
}

double hmean(double a, double b)
{
    if (a == -b)
        throw "bad hmean() arguments: a = -b not allowed";
	//throw 关键字表示引发异常，紧随其后的值（字符串或对象）指出了异常的特征
    return 2.0 * a * b / (a + b); 
}
