#pragma once
#include <process.h>
#include <Windows.h>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <list>

typedef char                    i8;
typedef unsigned char           u8;
typedef short                  i16;
typedef unsigned short          u16;
typedef long int                i32;
typedef unsigned long           u32;



namespace StringParser{







//�ӷָ����л������
inline int GetParamFromString(std::string Str, std::vector<i32>& IntVec, char Delim = ',')
{
    char* p = strtok((char*)Str.c_str(), &Delim); 
    while (p)
    {
        IntVec.push_back(atoi(p));
        p = strtok(NULL, &Delim); 
    }
    return IntVec.size();
}

inline int GetParamFromString(std::string Str, std::vector<float>& FloatVec, char Delim = ',')
{
    char* p = strtok((char*)Str.c_str(), &Delim); 
    while (p)
    {
        FloatVec.push_back(atof(p));
        p = strtok(NULL, &Delim); 
    }
    return FloatVec.size();
}

inline int GetParamFromString(std::string Str, std::vector<u32>& uiIntVec, char Delim = ',')
{
    char* p = strtok((char*)Str.c_str(), &Delim); 
    while (p)
    {
        uiIntVec.push_back(strtoul(p, NULL, 10));
        p = strtok(NULL, &Delim); 
    }
    return uiIntVec.size();
}

inline int GetParamFromString(std::string Str, std::vector<std::string>& StringVec, char Delim = ',')
{
    char* p = strtok((char*)Str.c_str(), &Delim); 
    while (p)
    {
        std::string buffer = p;
        StringVec.push_back(buffer);
        p = strtok(NULL, &Delim); 
    }
    return StringVec.size();
}

//�����ҷ��ŵõ������е�����ex:[3.1415;0.125][1000;9999]
template<typename T>
int GetParamFromArea(std::string Str, std::vector<std::vector<T> >& IntVec, char left = '[', char right = ']', char Delim = ';')
{
    char* pTarget = (char*)Str.c_str();
    for (;;)
    {
        char* pLeft = strchr(pTarget, left);
        char* pRight = strchr(pTarget, right);
        if (pLeft && pRight)
        {
            std::string strbuff;
            strbuff.insert(0, ++pLeft, pRight-pLeft);

            std::vector<T> Intbuff;
            if (GetParamFromString(strbuff, Intbuff, Delim))
            {
                IntVec.push_back(Intbuff);
            }
            pTarget = ++pRight;
        }
        else
        {
            break;
        }
    }
    return IntVec.size();
}









};