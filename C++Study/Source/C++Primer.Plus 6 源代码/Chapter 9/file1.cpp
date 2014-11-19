// file1.cpp -- example of a three-file program
/*
 *文件之间的关系是：在coordin.h头文件中定义了polar和rect结构体，同时声明了以下两个函数原型
 *     polar rect_to_polar(rect xypos);
 *     void show_polar(polar dapos); 
 *这两个原型是定义在file2.cpp文件中的，file1.cpp是主调文件，调用这个两个函数
 */

#include <iostream>
#include "coordin.h" // structure templates, function prototypes

using namespace std;

int main()
{
    rect rplace;
    polar pplace;

    cout << "Enter the x and y values: ";
    while (cin >> rplace.x >> rplace.y)  // slick use of cin
    {
        pplace = rect_to_polar(rplace);
        show_polar(pplace);
        cout << "Next two numbers (q to quit): ";
    }
    cout << "Bye!\n";
// keep window open in MSVC++
/*
    cin.clear();
    while (cin.get() != '\n')
        continue;
    cin.get();
*/
    return 0; 
}
