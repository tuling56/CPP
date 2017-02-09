//error1.cpp -- using the abort() function
#include <iostream>
#include <cstdlib>  //�쳣abort()����������ͷ�ļ�
double hmean(double a, double b);

int error1()
{
    double x, y, z;

    std::cout << "Enter two numbers: ";
    while (std::cin >> x >> y)
    {
        z = hmean(x,y);
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
    {
        std::cout << "untenable arguments to hmean()\n";
        std::abort(); //��ֱ����ֹ���򣬶������ȷ��ص�main()���˳�
    }
    return 2.0 * a * b / (a + b); 
}
