// file1.cpp -- example of a three-file program
/*
 *�ļ�֮��Ĺ�ϵ�ǣ���coordin.hͷ�ļ��ж�����polar��rect�ṹ�壬ͬʱ������������������ԭ��
 *     polar rect_to_polar(rect xypos);
 *     void show_polar(polar dapos); 
 *������ԭ���Ƕ�����file2.cpp�ļ��еģ�file1.cpp�������ļ������������������
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
