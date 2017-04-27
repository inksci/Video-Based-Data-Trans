// MFCApplication3Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFCApplication3Dlg �Ի���



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


// CMFCApplication3Dlg ��Ϣ�������

BOOL CMFCApplication3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	GetDlgItem(IDC_EDIT3)->SetWindowText(_T("��������������Ҫ�����ļ���·����"));
	GetDlgItem(IDC_EDIT2)->SetWindowText(_T("һֻ�������ֻ����š�������������\r\n��һֻ�ֵ����ť����ʼ����ļ�������������Ƶ������ʼ���š�\r\n\r\n\r\nȻ�󽫻�õ���Ƶ�ŵ���������նˡ�ȥ����..."));




	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCApplication3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		
CRect rc; // ����һ�������������
AfxGetApp()->m_pMainWnd->GetClientRect(rc);
int nWidth = rc.Width();
int nHeight = rc.Height();

CDC *pDC = AfxGetApp()->m_pMainWnd->GetDC(); // �����豸������
CDC MemDC; // ����һ���ڴ���ʾ�豸����
CBitmap MemBitmap; // ����һ��λͼ����


//��������Ļ��ʾ���ݵ��ڴ���ʾ�豸
MemDC.CreateCompatibleDC(pDC);
//����һ������Ļ��ʾ���ݵ�λͼ��λͼ�Ĵ�С��ѡ�ô��ڿͻ����Ĵ�С
MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);
//��λͼѡ�뵽�ڴ���ʾ�豸�У�ֻ��ѡ����λͼ���ڴ���ʾ�豸���еط���ͼ������ָ����λͼ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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


	//���Կ���ȥ�� <Start
	//���Կ���ȥ�� End>


	// OnBnClickedButton4();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	

	//������ƽ�����ʾ


	//��ͼ��ɺ������
	MemDC.SelectObject(MemBitmap);
	MemBitmap.DeleteObject();
	rfile.Close();
	outfile.close();
	Sleep(300);

	AfxGetApp()->m_pMainWnd->MessageBox(_T("�ļ������ɣ�\r\nȥ��������նˡ�����������Ƶ�ɣ�"), _T("Message��"), MB_OKCANCEL | MB_ICONQUESTION);
	return 0;
}

/*{
    int l_origin=0;
    int t_origin=0;
    int w=50;
    int size=10;
        
    CRect rc; // ����һ�������������
    
    AfxGetApp()->m_pMainWnd->GetClientRect(rc);
    CDC *pDC =AfxGetApp()->m_pMainWnd->GetDC();// �����豸������
    
    int nWidth = rc.Width();
    int nHeight = rc.Height();
    
    CDC MemDC; // ����һ���ڴ���ʾ�豸����
    CBitmap MemBitmap; // ����һ��λͼ����
    
    
    //��������Ļ��ʾ���ݵ��ڴ���ʾ�豸
    MemDC.CreateCompatibleDC(pDC);
    //����һ������Ļ��ʾ���ݵ�λͼ��λͼ�Ĵ�С��ѡ�ô��ڿͻ����Ĵ�С
    MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);
    //��λͼѡ�뵽�ڴ���ʾ�豸�У�ֻ��ѡ����λͼ���ڴ���ʾ�豸���еط���ͼ������ָ����λͼ��
    CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);

    MemDC.FillSolidRect(0,0,(w+4)*size,(w+4)*size,RGB(255,0,255));

    pDC->BitBlt(l_origin-size-size,t_origin-size-size,(w+4)*size,(w+4)*size,&MemDC,0,0,SRCCOPY);
    //��ͼ��ɺ������
    MemDC.SelectObject(MemBitmap);
    MemBitmap.DeleteObject();
    return 0;
}*/
void CMFCApplication3Dlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�


	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication3Dlg::OnBnClickedButton2(){}

void CMFCApplication3Dlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�



	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication3Dlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT3)->SetWindowText(_T("F:\\Based-Video-Data-Trans-Method\\info.txt"));
}


void CMFCApplication3Dlg::OnBnClickedButton4(){}
void CMFCApplication3Dlg::OnBnClickedButton5(){}
void CMFCApplication3Dlg::OnBnClickedButton6(){}
void CMFCApplication3Dlg::OnBnClickedButton7(){}

void CMFCApplication3Dlg::OnBnClickedOpenfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL isOpen = TRUE;     //�Ƿ��(����Ϊ����)  
    CString defaultDir = L"C:\\Users\\Administrator\\Pictures";   //Ĭ�ϴ򿪵��ļ�·��  
    CString fileName = L"";         //Ĭ�ϴ򿪵��ļ���  
    CString filter = L"�ļ� (*.txt; *.bmp; *.png; *.jpg; *.jpeg)|*.txt;*.bmp;*.png;*.jpg;*.jpeg||";   //�ļ����ǵ�����  
    CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY|OFN_READONLY, filter, NULL);  
    openFileDlg.GetOFN().lpstrInitialDir = L"C:\\Users\\Administrator\\Pictures\\robot (1).jpg";  
    INT_PTR result = openFileDlg.DoModal();  
    CString filePath = defaultDir + "\\robot (1).jpg";  
    if(result == IDOK) {  
        filePath = openFileDlg.GetPathName();  
    }  
	GetDlgItem(IDC_EDIT3)->SetWindowText(filePath);
}
