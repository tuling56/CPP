/************************************************************************
* Copyright(c) 2015 tuling56
*
* File:	findFileDir.cpp
* Brief: 获取当前文件夹下的所有文件和目录
* Source:
* Status: 
* Date:	[1/30/2015 jmy]
************************************************************************/
#include <io.h>
#include <stdio.h>
#include <time.h>
#include <iostream>

using namespace std;

void findFileDir( void )
{
	struct _finddata_t c_file;
	long hFile;

	if( (hFile = _findfirst( "*.*", &c_file )) == -1L )
		printf( "No *.c files in current directory!\n" );
	else
	{
		printf( "Listing of files\n\n" );
		printf( "\nRDO HID SYS ARC  FILE         DATE %25c SIZE\n", ' ' );
		printf( "--- --- --- ---  ----         ---- %25c ----\n", ' ' );
		printf( ( c_file.attrib & _A_RDONLY ) ? " Y  " : " N  " );
		printf( ( c_file.attrib & _A_SYSTEM ) ? " Y  " : " N  " );
		printf( ( c_file.attrib & _A_HIDDEN ) ? " Y  " : " N  " );
		printf( ( c_file.attrib & _A_ARCH )   ? " Y  " : " N  " );
		printf( " %-12s %.24s  %9ld\n", c_file.name, ctime( &( c_file.time_write ) ), c_file.size );

		while( _findnext( hFile, &c_file ) == 0 )
		{
			printf( ( c_file.attrib & _A_RDONLY ) ? " Y  " : " N  " );
			printf( ( c_file.attrib & _A_SYSTEM ) ? " Y  " : " N  " );
			printf( ( c_file.attrib & _A_HIDDEN ) ? " Y  " : " N  " );
			printf( ( c_file.attrib & _A_ARCH )   ? " Y  " : " N  " );
			printf( " %-12s %.24s  %9ld\n",c_file.name, ctime( &( c_file.time_write ) ), c_file.size );
		}

		_findclose( hFile );
	}
}

//功能测试区
//int main()
//{
//	findFileDir();
//	cin.get();
//	return 0;
//}