// MFCApplication3Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication3Dlg 对话框



CMFCApplication3Dlg::CMFCApplication3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication3Dlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplication3Dlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_OpenFile, &CMFCApplication3Dlg::OnBnClickedOpenfile)
END_MESSAGE_MAP()


// CMFCApplication3Dlg 消息处理程序

BOOL CMFCApplication3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_EDIT3)->SetWindowText(_T("“在这里输入您要传送文件的路径”"));
	GetDlgItem(IDC_EDIT2)->SetWindowText(_T("一只手拿着手机对着“播放区域”摄像，\r\n另一只手点击按钮“开始解读文件，并“播放视频””开始播放。\r\n\r\n\r\n然后将获得的视频放到软件“接收端”去处理..."));




	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication3Dlg::OnBnClickedButton1(){
	::AfxBeginThread(DrawLine,NULL);
}
UINT DrawLine(LPVOID pParam){
	using namespace std;	ofstream outfile;	outfile.open("out-MFCApp3.txt");

	int l_origin=600;
	int t_origin=100;
	int w=50;
	int size=10;
		
CRect rc; // 定义一个矩形区域变量
AfxGetApp()->m_pMainWnd->GetClientRect(rc);
int nWidth = rc.Width();
int nHeight = rc.Height();

CDC *pDC = AfxGetApp()->m_pMainWnd->GetDC(); // 定义设备上下文
CDC MemDC; // 定义一个内存显示设备对象
CBitmap MemBitmap; // 定义一个位图对象


//建立与屏幕显示兼容的内存显示设备
MemDC.CreateCompatibleDC(pDC);
//建立一个与屏幕显示兼容的位图，位图的大小可选用窗口客户区的大小
MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);
//将位图选入到内存显示设备中，只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上
CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);
	MemDC.FillSolidRect(0,0,(w+4)*size,(w+4)*size,RGB(255,255,255));
	
	MemDC.FillSolidRect(size,0,size,size,RGB(255,0,0));
	MemDC.FillSolidRect(0,size,size,size,RGB(0,255,0));
	
	MemDC.FillSolidRect(0,(w+2)*size,size,size,RGB(255,0,0));
	MemDC.FillSolidRect(size,(w+3)*size,size,size,RGB(0,255,0));
	MemDC.FillSolidRect(size,(w+2)*size,size,size,RGB(0,0,255));
	MemDC.FillSolidRect(0,(w+3)*size,size,size,RGB(0,0,255));
	
	MemDC.FillSolidRect((w+3)*size,(w+2)*size,size,size,RGB(255,0,0));
	MemDC.FillSolidRect((w+2)*size,(w+3)*size,size,size,RGB(0,255,0));
	MemDC.FillSolidRect((w+2)*size,(w+2)*size,size,size,RGB(0,0,255));
	MemDC.FillSolidRect((w+3)*size,(w+3)*size,size,size,RGB(0,0,255));
	
	MemDC.FillSolidRect((w+2)*size,0,size,size,RGB(255,0,0));
	MemDC.FillSolidRect((w+3)*size,size,size,size,RGB(0,255,0));
	MemDC.FillSolidRect((w+2)*size,size,size,size,RGB(0,0,255));
	MemDC.FillSolidRect((w+3)*size,0,size,size,RGB(0,0,255));

	MemDC.FillSolidRect(size*2,size*2,size*5,size*5,RGB(255,0,0));
		MemDC.FillSolidRect(size*7,size*7,size*5,size*5,RGB(0,255,0));
	MemDC.FillSolidRect(size*2,size*(2+w-5),size*5,size*5,RGB(255,0,0));
		MemDC.FillSolidRect(size*7,size*(2+w-10),size*5,size*5,RGB(0,255,0));
	MemDC.FillSolidRect(size*(2+w-5),size*2,size*5,size*5,RGB(255,0,0));
		MemDC.FillSolidRect(size*(2+w-10),size*7,size*5,size*5,RGB(0,255,0));
	MemDC.FillSolidRect(size*(2+w-5),size*(2+w-5),size*5,size*5,RGB(255,0,0));
		MemDC.FillSolidRect(size*(2+w-10),size*(2+w-10),size*5,size*5,RGB(0,255,0));
	
	// Jump Detect Block:
	MemDC.FillSolidRect(0,0,size,size,RGB(0,0,0));
	MemDC.FillSolidRect(size,size,size,size,RGB(0,0,0));

	pDC->BitBlt(l_origin-size-size,t_origin-size-size,(w+4)*size,(w+4)*size,&MemDC,0,0,SRCCOPY);

	Sleep(1000);
//	INT_PTR nRes;     
//	nRes = MessageBox(_T("456789"), _T("Title"), MB_OKCANCEL | MB_ICONQUESTION);
		
	
	CFile rfile;
	CString name_rfile;
	AfxGetApp()->m_pMainWnd->GetDlgItem(IDC_EDIT3)->GetWindowText(name_rfile);
	if(!rfile.Open(name_rfile,CFile::modeRead))
		return 0;
	BYTE buf[1];
	UINT readed;
	CString str_sum = _T("");
	int i_chk=0;
	int order12=0;
	while((readed=rfile.Read(buf,1))>0)
	{
		if(i_chk==2500){
			i_chk=0;
	
	// OnBnClickedButton4();
	// TODO: 在此添加控件通知处理程序代码

	if(order12==0){
	MemDC.FillSolidRect(0,0,size,size,RGB(255,255,255));
	MemDC.FillSolidRect(size,size,size,size,RGB(255,255,255));	
		order12=1;
	}else{

	MemDC.FillSolidRect(0,0,size,size,RGB(0,0,0));
	MemDC.FillSolidRect(size,size,size,size,RGB(0,0,0));
		order12=0;
	}


	CString my_str=str_sum;
	str_sum=_T("");
	int check_len=my_str.GetLength();
	int i=0;
	for(i=0;i<my_str.GetLength();i++){
		int num_if=_ttoi(my_str.Mid(i,1));
		outfile<<num_if;
		if(num_if==0){
			MemDC.FillSolidRect(size+size+i%w*size,size+size+i/w*size,size,size,RGB(0,0,0));					
		}else if(num_if==1){
			MemDC.FillSolidRect(size+size+i%w*size,size+size+i/w*size,size,size,RGB(255,0,0));			
		}else if(num_if==2){
			MemDC.FillSolidRect(size+size+i%w*size,size+size+i/w*size,size,size,RGB(0,255,0));				
		}else if(num_if==3){
			MemDC.FillSolidRect(size+size+i%w*size,size+size+i/w*size,size,size,RGB(0,0,255));				
		}
	}
	///////////////////////////////////
	pDC->BitBlt(l_origin-size-size,t_origin-size-size,(w+2)*size,(w+2)*size,&MemDC,0,0,SRCCOPY);

	Sleep(300);

		}//if(i_chk==2500){		
		byte* bytes=buf;
		CString str;
		int len=4;
		
		while(len--){
 			str.Format(_T("%d"), bytes[0] & 3);str_sum+= str;
			bytes[0]>>=2;
		}
		i_chk+=4;// is 4, not i_chk++

	}


	//可以考虑去掉 <Start
	//可以考虑去掉 End>


	// OnBnClickedButton4();
	// TODO: 在此添加控件通知处理程序代码
	if(order12==0){
	MemDC.FillSolidRect(0,0,size,size,RGB(255,255,255));
	MemDC.FillSolidRect(size,size,size,size,RGB(255,255,255));
		order12=1;
	}else{

	MemDC.FillSolidRect(0,0,size,size,RGB(0,0,0));
	MemDC.FillSolidRect(size,size,size,size,RGB(0,0,0));
		order12=0;
	}

	CString my_str=str_sum;
	str_sum=_T("");
	int check_len=my_str.GetLength();
	int i=0;
	for(i=0;i<my_str.GetLength();i++){
		int num_if=_ttoi(my_str.Mid(i,1));
		outfile<<num_if;
		if(num_if==0){
			MemDC.FillSolidRect(size+size+i%w*size,size+size+i/w*size,size,size,RGB(0,0,0));					
		}else if(num_if==1){
			MemDC.FillSolidRect(size+size+i%w*size,size+size+i/w*size,size,size,RGB(255,0,0));			
		}else if(num_if==2){
			MemDC.FillSolidRect(size+size+i%w*size,size+size+i/w*size,size,size,RGB(0,255,0));				
		}else if(num_if==3){
			MemDC.FillSolidRect(size+size+i%w*size,size+size+i/w*size,size,size,RGB(0,0,255));				
		}
	}
	int tmp=(i%w+1);
	tmp=(i/w+2);
	MemDC.FillSolidRect((i%w+1)*size,size,size,size,RGB(255,0,0));
	MemDC.FillSolidRect(size,(i/w+2)*size,size,size,RGB(255,0,0));
	///////////////////////////////////
	pDC->BitBlt(l_origin-size-size,t_origin-size-size,(w+4)*size,(w+4)*size,&MemDC,0,0,SRCCOPY);
	

	//可以设计进度提示


	//绘图完成后的清理
	MemDC.SelectObject(MemBitmap);
	MemBitmap.DeleteObject();
	rfile.Close();
	outfile.close();
	Sleep(300);

	AfxGetApp()->m_pMainWnd->MessageBox(_T("文件解读完成！\r\n去软件“接收端”处理您的视频吧！"), _T("Message："), MB_OKCANCEL | MB_ICONQUESTION);
	return 0;
}

/*{
    int l_origin=0;
    int t_origin=0;
    int w=50;
    int size=10;
        
    CRect rc; // 定义一个矩形区域变量
    
    AfxGetApp()->m_pMainWnd->GetClientRect(rc);
    CDC *pDC =AfxGetApp()->m_pMainWnd->GetDC();// 定义设备上下文
    
    int nWidth = rc.Width();
    int nHeight = rc.Height();
    
    CDC MemDC; // 定义一个内存显示设备对象
    CBitmap MemBitmap; // 定义一个位图对象
    
    
    //建立与屏幕显示兼容的内存显示设备
    MemDC.CreateCompatibleDC(pDC);
    //建立一个与屏幕显示兼容的位图，位图的大小可选用窗口客户区的大小
    MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);
    //将位图选入到内存显示设备中，只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上
    CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);

    MemDC.FillSolidRect(0,0,(w+4)*size,(w+4)*size,RGB(255,0,255));

    pDC->BitBlt(l_origin-size-size,t_origin-size-size,(w+4)*size,(w+4)*size,&MemDC,0,0,SRCCOPY);
    //绘图完成后的清理
    MemDC.SelectObject(MemBitmap);
    MemBitmap.DeleteObject();
    return 0;
}*/
void CMFCApplication3Dlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。


	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication3Dlg::OnBnClickedButton2(){}

void CMFCApplication3Dlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。



	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication3Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT3)->SetWindowText(_T("F:\\Based-Video-Data-Trans-Method\\info.txt"));
}


void CMFCApplication3Dlg::OnBnClickedButton4(){}
void CMFCApplication3Dlg::OnBnClickedButton5(){}
void CMFCApplication3Dlg::OnBnClickedButton6(){}
void CMFCApplication3Dlg::OnBnClickedButton7(){}

void CMFCApplication3Dlg::OnBnClickedOpenfile()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL isOpen = TRUE;     //是否打开(否则为保存)  
    CString defaultDir = L"C:\\Users\\Administrator\\Pictures";   //默认打开的文件路径  
    CString fileName = L"";         //默认打开的文件名  
    CString filter = L"文件 (*.txt; *.bmp; *.png; *.jpg; *.jpeg)|*.txt;*.bmp;*.png;*.jpg;*.jpeg||";   //文件过虑的类型  
    CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY|OFN_READONLY, filter, NULL);  
    openFileDlg.GetOFN().lpstrInitialDir = L"C:\\Users\\Administrator\\Pictures\\robot (1).jpg";  
    INT_PTR result = openFileDlg.DoModal();  
    CString filePath = defaultDir + "\\robot (1).jpg";  
    if(result == IDOK) {  
        filePath = openFileDlg.GetPathName();  
    }  
	GetDlgItem(IDC_EDIT3)->SetWindowText(filePath);
}
