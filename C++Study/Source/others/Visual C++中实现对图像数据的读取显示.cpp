/*Visual C++中实现对图像数据的读取显示
在利用VC进行数据库编程时，经常需要处理数据库中的图像数据，将该图像从数据库中读取出来并显示，图像数据与文本字段不同，
它是作为OLE字段在数据库中存储，通过数据集对象的成员变量自动交换得到的图像数据，得到的数据并不能直接显示，
如何处理图像数据，一直是数据库编程中的一个难点，目前关于VC进行数据库编程的资料不少，但很少涉及图像数据的操作，
笔者针对一现状，结合自己开发的一个项目，解决了如何显示数据库中的图像这一问题，本文以操作ACESS数据库为例子，
讲解一下自己的实现思路，希望对爱好VC编程的朋友们有所帮助，以起到抛砖引玉的作用。 

为了简化问题，该数据库的表中只有一个名为Images的OLE字段，我使用DAO连接操作数据库，读取的图像数据显示在一个对话框上，
至于使用ODBC、DAO还是ADO，这要根据具体情况而定，但无论使用哪一种，对图像的显示来说，实现的过程是大同小异的。
由于篇幅有限，文章中对如何实现数据库的连接不再作具体的说明，有兴趣的读者朋友可以参考VC数据库编程的资料。
*/

//实现过程中，首先定义一个CDaoRecordset的子类 CimageData如下： 

class CimageData : public CDaoRecordset 
{ 
	public: 
		CimageData (CDaoDatabase* pDatabase = NULL); 
		DECLARE_DYNAMIC(CimageData) 
		file://{{AFX_FIELD(CimageData, CDaoRecordset) 
		CByteArray m_Images;//声明字节数组用来存放图像数据 
		// Overrides 
		// ClassWizard generated virtual function overrides 
	public: 
		virtual CString GetDefaultDBName(); 
		virtual CString GetDefaultSQL(); 
		virtual void DoFieldExchange(CDaoFieldExchange* pFX); 
		
}

　　 //该类的实现为： 

CimageData:: CimageData (CDaoDatabase* pdb) : CDaoRecordset(pdb) 
{ 
	m_nFields = 1;//数据库的表中仅有一个字段 
	m_nDefaultType = dbOpenDynaset;//以动态集方式打开数据库 
} 
CString CimageData::GetDefaultDBName() 
{ 
	return _T("E:\\IMAGES.mdb");//默认的ACESS数据库在E盘，名为IMAGES 
} 

CString CimageData::GetDefaultSQL() 
{ 
	return _T("[Table]");//默认打开数据库中名为"Table"的表 
} 

void CimageData::DoFieldExchange(CDaoFieldExchange* pFX) 
{ 
	pFX->SetFieldType(CDaoFieldExchange::outputColumn); 
    DFX_Binary(pFX, _T("[Images]"), m_Images);//以二进制方式在Images字段和m_Images变量间交换数据 

}

 //有了该类，就可以定义相应的对象来与数据库中的图像字段交换数据，下面定义的函数GetImageData()
//说明了如何根据读取的OLE字段数据生成待显示的图像，需要注意的是该函数中使用的CBitmap类的变量Bitmap是预定义的一个全局变量： 


BOOL CImageDlg:: GetImageData(CByteArray & DBArray) 
{ 
	CByteArray Array; 
	Array.Copy( DBArray); 
	int HeaderLen = 78 + sizeof(BITMAPFILEHEADER); file://确定图像头信息的起始位置 
	Array.RemoveAt( 0, HeaderLen ); // 移动到图像头信息的起始位置 
	BITMAPINFOHEADER &bmiHeader = *(LPBITMAPINFOHEADER)Array.GetData() ; 
	BITMAPINFO &bmInfo = *(LPBITMAPINFO)Array.GetData() ; 
	file://得到图像数据的头信息 
	int nColors=bmiHeader.biClrUsed ? bmiHeader.biClrUsed : 1 << bmiHeader.biBitCount; 
	file://确定图像的颜色数 
	LPVOID lpDIBBits; 
	if( bmInfo.bmiHeader.biBitCount > 8 ) 
		lpDIBBits=(LPVOID)((LPDWORD)(bmInfo.bmiColors+bmInfo.bmiHeader.biClrUsed)+ 
	               ((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0)); 
	else 
		lpDIBBits = (LPVOID)(bmInfo.bmiColors + nColors); 
	file://得到图像各个像素的具体数据 
	CClientDC dc(NULL); 
	HBITMAP hBmp = CreateDIBitmap( dc.m_hDC, &bmiHeader, CBM_INIT, 	lpDIBBits, 	&bmInfo, DIB_RGB_COLORS); 
	file://生成位图句柄 
	Bitmap.Attach( hBmp );//将该句柄与定义的Bitmap对象联系在一起 
	Array.RemoveAll(); 
    file://释放内存 

	return TRUE; 

} 


// 有了上面的准备工作，现在可以实现图像的显示函数了，其实现如下： 


void CImageDlg::OnShowImage() 
{ 
	CimageData db;//定义记录集对象 
	db.Open();打开数据库 
	GetImageData(db.m_Images);//根据记录集对象的成员变量生成图像对象 
	file://以下是在对话框的固定区域显示图像 
	CPaintDC dc(this); 
	if (!(Bitmap.m_hObject == NULL)) 
	{
		CDC dcMem; 
		dcMem.CreateCompatibleDC( &dc ); file://create a Memory Image 
		CBitmap* pbmpOld ; 
		BITMAP BmpSize ; 
		Bitmap.GetBitmap(&BmpSize); file://get Image Size 
		pbmpOld = dcMem.SelectObject(&Bitmap); 
		dc.StretchBlt( 20, 20, 200, 200, &dcMem, 0, 0, BmpSize.bmWidth, BmpSize.bmHeight, SRCCOPY); 
		dcMem.SelectObject( pbmpOld ); 
    }

} 

　// 以上代码中使用的数据库为ACESS97，程序在windows98、Visual C++6.0环境下编译通过，运行正常。
