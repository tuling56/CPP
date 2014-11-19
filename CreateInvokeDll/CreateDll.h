////头文件 CreateDll.h  
#ifndef CREATEDLL_H  
//导出函数

#define CREATEDLL_H
	extern "C" int _declspec(dllexport)recognize(const char * readFileName,const char * saveFileName);  
#endif  

