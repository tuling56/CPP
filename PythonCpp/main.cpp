/************************************************************************
* Copyright(c) 2015 tuling56
*
* File:	main.cpp
* Brief: ��ʾpython��cpp��ϱ�̵��÷�
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
	PyRun_SimpleString("sys.path.append('./')"); //��ӵ�ǰĿ¼��python·��

	PyObject *pMode = NULL;
	PyObject *pfunc = NULL;
	PyObject* pClass = NULL;
	PyObject *pInstance = NULL;
	PyObject *pArg = NULL;

	//���õ�ģ���ļ���
	pMode = PyImport_ImportModule("script");
	//���ú����ĺ�����
	pfunc = PyObject_GetAttrString(pMode, "hello");
	//���ú���
	PyEval_CallObject(pfunc, NULL);
	//�ͷź���
	Py_DECREF(pfunc);

	//���ú����ĺ�����
	pfunc = PyObject_GetAttrString(pMode, "world");
	//���ú���
	pArg = Py_BuildValue("(s)", "function with argument");
	PyEval_CallObject(pfunc,pArg);
	//�ͷź���
	Py_DECREF(pfunc);

	//������
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
	
	//����Py_Finalize�������Py_Initialize���Ӧ�ġ�
	Py_Finalize();
	

	getchar();
	return 0;


}
