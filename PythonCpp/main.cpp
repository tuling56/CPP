/************************************************************************
* Copyright(c) 2015 tuling56
*
* File:	main.cpp
* Brief: 演示python和cpp混合编程的用法
* Reference:http://blog.sina.com.cn/s/blog_6ec980ee0101cgax.html
            http://www.udpwork.com/item/10422.html
* Status: 
* Date:	[6/25/2015 jmy]
************************************************************************/
#include<Python.h>

int main()
{

	Py_Initialize();
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')"); //添加当前目录到python路径

	PyObject *pMode = NULL;
	PyObject *pfunc = NULL;
	PyObject* pClass = NULL;
	PyObject *pInstance = NULL;
	PyObject *pArg = NULL;

	//调用的模块文件名
	pMode = PyImport_ImportModule("script");
	//调用函数的函数名
	pfunc = PyObject_GetAttrString(pMode, "hello");
	//调用函数
	PyEval_CallObject(pfunc, NULL);
	//释放函数
	Py_DECREF(pfunc);

	//调用函数的函数名
	pfunc = PyObject_GetAttrString(pMode, "world");
	//调用函数
	pArg = Py_BuildValue("(s)", "function with argument");
	PyEval_CallObject(pfunc,pArg);
	//释放函数
	Py_DECREF(pfunc);

	//调用类
	pClass = PyObject_GetAttrString(pMode, "Student");
	if (!pClass){
		printf("cann't find Sudent class\n");
		return -1;
	}
	pInstance = PyInstance_New(pClass, NULL, NULL);
	if (!pInstance)
	{
		printf("cann't create sudent instance\n");
		return -1;
	}

	PyObject_CallMethod(pInstance, "SetName", "s", "myfamliy");
	PyObject_CallMethod(pInstance, "PrintName", NULL, NULL);
	
	//调用Py_Finalize，这个根Py_Initialize相对应的。
	Py_Finalize();
	

	getchar();
	return 0;


}
