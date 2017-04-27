/*
-----------------------------------------
//:

Src: Q.mp4
Start: 61
Result: 13kb -> 12kb
Reason: Jump Over
*/
// MFCApp-CV-againDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApp-CV-again.h"
#include "MFCApp-CV-againDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/// 全局变量的声明与初始化
const int alpha_slider_max = 100;
int alpha_slider;
double alpha;
double beta;

cv::VideoCapture capture_track;
CString video_name;
int track_i_jump=0;
UINT step_run;


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


// CMFCAppCVagainDlg 对话框



CMFCAppCVagainDlg::CMFCAppCVagainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCAppCVagainDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCAppCVagainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCAppCVagainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCAppCVagainDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCAppCVagainDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFCAppCVagainDlg 消息处理程序

BOOL CMFCAppCVagainDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCAppCVagainDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCAppCVagainDlg::OnPaint()
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
HCURSOR CMFCAppCVagainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCAppCVagainDlg::OnBnClickedButton1(){
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK1);
	step_run = pBtn->GetCheck();

	CString file_write;
	GetDlgItem(IDC_EDIT3)->GetWindowText(file_write);
	CFile wfile;
	if(!wfile.Open(file_write,CFile::modeCreate|CFile::modeWrite))
		return;

  //CString str_num_jump;
  //GetDlgItem(IDC_EDIT2)->GetWindowText(str_num_jump);
  int num_jump=track_i_jump;//_ttoi(str_num_jump);

  GetDlgItem(IDC_EDIT1)->GetWindowText(video_name);
  // 打开视频文件
  cv::VideoCapture capture(video_name.GetBuffer(0));
  // 检查打开是否成功
  if (!capture.isOpened())
    return;

  // 取得帧速率
  double rate= capture.get(CV_CAP_PROP_FPS);

  bool stop(false);
  cv::Mat frame; // 当前视频帧

  // 根据帧速率计算帧之间的等待时间，单位ms
  int delay= 1000/rate;
  int i_jump=0;
		double xpt[]={-1,-1,-1,-1};
		double ypt[]={-1,-1,-1,-1};
	using namespace std;	ofstream outfile;	outfile.open("F:\\Based-Video-Data-Trans-Method\\out-MFCApp-CV-again.txt");

	// Black->0, White->1:
	int old_clr=0;

	int jump_times=0;
	int find_times=0;

  // 循环遍历视频中的全部帧
  while (!stop) {
	  //break;
	  
    // 读取下一帧（如果有）
    if (!capture.read(frame))
      break;

		i_jump++;
		if(i_jump<num_jump){
			continue;
		}
		if(xpt[0]==-1&&xpt[1]==-1&&xpt[2]==-1&&xpt[3]==-1){
			find_pos(frame,xpt,ypt,find_times);
		}else{
/////////////////////////////////////////////////////////////////////
		
//		imshow("srcImg",frame);
//		cv::waitKey(0);
		outfile<<"i_jump :"<<i_jump<<endl;
//		imwrite("frame.bmp",frame);

		cv::Mat imageROI;
		int ipt;
		for(ipt=0;ipt<4;ipt++){
			imageROI=Mat(frame,cv::Rect(xpt[ipt]-10,ypt[ipt]-10,20,20));
			int a_pos=chk_bk_b(imageROI);
			int b_pos=chk_bk_a(imageROI);
				//if(a_pos>5&&a_pos<15){
					xpt[ipt]=xpt[ipt]-10+a_pos;
				//}
				//if(b_pos>5&&b_pos<15){
					ypt[ipt]=ypt[ipt]-10+b_pos;	
				//}
		}

		if(false&&i_jump>210){
						imshow("srcImg",frame);
			cv::waitKey(0);
			imwrite("no-mark.bmp",frame);
			dr_border(imageROI);
		for(ipt=0;ipt<4;ipt++){
			cv::circle( frame ,Point(xpt[ipt],ypt[ipt]) , 3, Scalar(0,255, 255));
			outfile<<i_jump<<" :"<<ipt<<" "<<xpt[ipt]<<" , "<<ypt[ipt]<<endl;
		}

			imshow("srcImg",frame);
			cv::waitKey(0);
			imwrite("with-mark.bmp",frame);
		}

		int blue=0;
		int blue_sum=0;
		//outfile<<"xypt"<<xpt[ipt]-10<<"-"<<ypt[ipt]-10<<endl;
		imageROI=Mat(frame,cv::Rect(xpt[0]-10,ypt[0]-10,20,20));
		for(int i_judge=0;i_judge<imageROI.rows;i_judge++){
			for(int j_judge=0;j_judge<imageROI.cols;j_judge++){
				blue+=imageROI.at<cv::Vec3b>(i_judge,j_judge)[0];
				blue_sum+=imageROI.at<cv::Vec3b>(i_judge,j_judge)[0]+imageROI.at<cv::Vec3b>(i_judge,j_judge)[1]+\
					imageROI.at<cv::Vec3b>(i_judge,j_judge)[2];

			}
		}
		

		outfile<<blue<<"	"<<blue_sum<<endl;

int new_clr=blue>30000?1:0;// here affcted by 10 in code before
	if(old_clr!=new_clr){
	jump_times++;
}else{
	jump_times=0;
}

if(jump_times==3){
	old_clr=new_clr;

	std::vector<cv::Point2f> corners;
	cv::Point2f pt;

	//in clockwise
	for(ipt=0;ipt<4;ipt++){
		pt= cv::Point2f(xpt[ipt],ypt[ipt]);	corners.push_back(pt);
	}


	docode_data(frame,corners,wfile,stop);
	//imwrite("question.bmp",frame);
	//imshow("srcImg",frame);
	//cv::waitKey(0);
}
/////////////////////////////////////////////////////////////////////
		}

		//imwrite("black-80.jpg",frame);
	//imshow("srcImg",frame);
	//cv::waitKey(0);
		
//    if (cv::waitKey(delay)>=0)
//		stop= true;
  }
  outfile<<"end9999"<<endl;
  outfile.close();
  destroyWindow("quad");
  wfile.Close();
	INT_PTR nRes;     
	nRes = MessageBox(_T("成功保存文件！"), _T("Title"), MB_OKCANCEL | MB_ICONQUESTION);

  
}
	/*{
	Mat srcImg=imread("F:\\Based-Video-Data-Trans-Method\\frame.bmp");
	double xpt[]={-1,-1,-1,-1};
	double ypt[]={-1,-1,-1,-1};
	find_pos(srcImg,xpt,ypt);
}*/
void find_pos(Mat srcImg,double *xpt,double *ypt,int &times){
	//Mat srcImg=imread("F:\\Based-Video-Data-Trans-Method\\frame.bmp");
	//double xpt[]={-1,-1,-1,-1};
	//double ypt[]={-1,-1,-1,-1};

	using namespace std;	ofstream outfile;	outfile.open("F:\\Based-Video-Data-Trans-Method\\out-find_pos.txt");

	int chk_sz=15;
	cv::Mat imageROI;
	int pos_r[]={10000,10000,	-1,10000,	-1,-1,	10000,-1};
	int pos_g[]={10000,10000,	-1,10000,	-1,-1,	10000,-1};
	for(int i=0;i<srcImg.rows-chk_sz;i+=chk_sz){
		for(int j=0;j<srcImg.cols-chk_sz;j+=chk_sz){
			
			imageROI=Mat(srcImg,cv::Rect(j,i,chk_sz,chk_sz));
			//dr_border(imageROI);
			if(sum_clr(imageROI)=='r'){
				dr_border(imageROI);
				if(j+i<pos_r[0]+pos_r[1]){pos_r[0]=j;
				pos_r[1]=i;}
				if((j-i)>(pos_r[2]-pos_r[3])){pos_r[2]=j;
				pos_r[3]=i;}
				if(i+j>pos_r[4]+pos_r[5]){pos_r[4]=j;
				pos_r[5]=i;}
				if((j-i)<(pos_r[6]-pos_r[7])){pos_r[6]=j;
				pos_r[7]=i;}
			}
			if(sum_clr(imageROI)=='g'){
				if((j+i)<(pos_g[0]+pos_g[1])){pos_g[0]=j;
				pos_g[1]=i;}
				if((j-i)>(pos_g[2]-pos_g[3])){pos_g[2]=j;
				pos_g[3]=i;}
				if((i+j)>(pos_g[4]+pos_g[5])){pos_g[4]=j;
				pos_g[5]=i;}
				if((j-i)<(pos_g[6]-pos_g[7])){pos_g[6]=j;
				pos_g[7]=i;}
			}
			//dr_border(imageROI);
		}
	}
	if(pos_r[2]!=-1){
		times++;
		if(times!=2){
			return;
		}
	}
	if(pos_r[2]!=-1&&times==2){

			imshow("quad",srcImg);
			waitKey(0);

		imageROI=Mat(srcImg,cv::Rect(pos_r[0],pos_r[1],pos_g[0]+chk_sz- pos_r[0],pos_g[1]+chk_sz- pos_r[1]));//dr_border(imageROI);
		xpt[0]=pos_r[0]+chk_bk_b(imageROI);
		ypt[0]=pos_r[1]+chk_bk_a(imageROI);
		
		imageROI=Mat(srcImg,cv::Rect(pos_g[2],pos_r[3],pos_r[2]+chk_sz- pos_g[2],pos_g[3]+chk_sz- pos_r[3]));//dr_border(imageROI);
		xpt[1]=pos_g[2]+chk_bk_b(imageROI);
		ypt[1]=pos_r[3]+chk_bk_a(imageROI);
		
		imageROI=Mat(srcImg,cv::Rect(pos_g[4],pos_g[5],pos_r[4]+chk_sz-pos_g[4],pos_r[5]+chk_sz-pos_g[5]));//dr_border(imageROI);
		xpt[2]=pos_g[4]+chk_bk_b(imageROI);
		ypt[2]=pos_g[5]+chk_bk_a(imageROI);
		
		imageROI=Mat(srcImg,cv::Rect(pos_r[6],pos_g[7],pos_g[6]+chk_sz-pos_r[6],pos_r[7]+chk_sz- pos_g[7]));//dr_border(imageROI);
		xpt[3]=pos_r[6]+chk_bk_b(imageROI);
		ypt[3]=pos_g[7]+chk_bk_a(imageROI);

		for(int ipt=0;ipt<4;ipt++){
			cv::circle( srcImg ,Point(xpt[ipt],ypt[ipt]) , 3, Scalar(0,255,255));
		}

//in clockwise
//	for(int ipt=0;ipt<4;ipt++){
//		outfile<<xpt[ipt]<<"\t"<<ypt[ipt]<<endl;
//	}
	imshow("quad",srcImg);
	waitKey(0);

	get_pos(xpt,ypt);
//	outfile<<endl;	outfile<<endl;
//	for(int ipt=0;ipt<4;ipt++){
//		outfile<<xpt[ipt]<<"\t"<<ypt[ipt]<<endl;
//	}

		for(int ipt=0;ipt<4;ipt++){
			cv::circle( srcImg ,Point(xpt[ipt],ypt[ipt]) , 3, Scalar(255,0,255));			
		}
		
	imshow("quad",srcImg);
	waitKey(0);
	}
	outfile.close();
//	imshow("quad",srcImg);
//	waitKey(0);
}
void get_pos(double *xpt,double *ypt){
	using namespace std;	ofstream outfile;	outfile.open("F:\\Based-Video-Data-Trans-Method\\out-get_pos.txt");

	//double xpt[]={569,988,983,571};
	//double ypt[]={140,147,562,580};

	//notice the order 0->3->2->1
	double x[]={xpt[0],xpt[3],xpt[2],xpt[1]};//569,571,983,988};
	double y[]={ypt[0],ypt[3],ypt[2],ypt[1]};
	//t2
	double t=( (x[1]-x[0])*(y[2]-y[0]) - (x[2]-x[0])*(y[1]-y[0]) )\
		/( (x[2]-x[0])*(y[3]-y[1]) - (x[3]-x[1])*(y[2]-y[0]) );
	double a=0.5*(t-1)/(0.5-t);double b=1/a;double k=-1/a/(a+1);
double s2=-0.15;
	double s1=(1/(a+s2)-b)/k;
	xpt[3]=(x[3]-x[1])*s1+x[1];
	ypt[3]=(y[3]-y[1])*s1+y[1];
s2=1.15;
	s1=(1/(a+s2)-b)/k;
	xpt[1]=(x[3]-x[1])*s1+x[1];
	ypt[1]=(y[3]-y[1])*s1+y[1];

	//t1
	t=( (x[3]-x[1])*(y[2]-y[0])*t + (x[1]-x[0])*(y[2]-y[0]) )\
		/( (x[2]-x[0])*(y[2]-y[0]) );
	a=0.5*(t-1)/(0.5-t);b=1/a;k=-1/a/(a+1);
s2=-0.15;
	s1=(1/(a+s2)-b)/k;
	xpt[0]=(x[2]-x[0])*s1+x[0];
	ypt[0]=(y[2]-y[0])*s1+y[0];
s2=1.15;
	s1=(1/(a+s2)-b)/k;
	xpt[2]=(x[2]-x[0])*s1+x[0];
	ypt[2]=(y[2]-y[0])*s1+y[0];

//	outfile<<xpt[0]<<"\t"<<xpt[1]<<"\t"<<xpt[2]<<"\t"<<xpt[3]<<endl;
//	outfile<<ypt[0]<<"\t"<<ypt[1]<<"\t"<<ypt[2]<<"\t"<<ypt[3]<<endl;
	outfile.close();
}
char sum_clr(Mat srcImg){
	int r=0;
	int g=0;
	for(int i=0;i<srcImg.rows;i++){
		for(int j=0;j<srcImg.cols;j++){
			if(pt_clr_chk(srcImg.at<cv::Vec3b>(i,j))=='r'){r++;}
			if(pt_clr_chk(srcImg.at<cv::Vec3b>(i,j))=='g'){g++;}
		}
	}
	if(r>srcImg.rows*srcImg.cols*0.9){return 'r';}
	if(g>srcImg.rows*srcImg.cols*0.9){
		//dr_border(srcImg);
		return 'g';}
	return '0';
}
/*{
		for(int i=0;i<srcImg.rows;i++){
		for(int j=0;j<srcImg.cols;j++){
			if(pt_clr_chk(srcImg.at<cv::Vec3b>(i,j))=='k'){
				srcImg.at<cv::Vec3b>(i,j)[0]=0;
				srcImg.at<cv::Vec3b>(i,j)[1]=255;
				srcImg.at<cv::Vec3b>(i,j)[2]=255;
			}
		}
	}
			imshow("change",srcImg);
	waitKey(0);
	return '0';
}*/
void docode_data(Mat frame,std::vector<cv::Point2f> corners,CFile &wfile,bool &stop){
	// TODO: 在此添加控件通知处理程序代码
	//Mat frame=imread("F:\\Based-Video-Data-Trans-Method\\src-check\\32bmp.bmp");

	cv::Mat quad = cv::Mat::zeros(520, 520, CV_8UC3);

//	std::vector<cv::Point2f> corners;
//	cv::Point2f pt;
//
//	//in clockwise
//	pt= cv::Point2f(412,76);	corners.push_back(pt);
//	pt= cv::Point2f(979,101);	corners.push_back(pt);
//	pt= cv::Point2f(961,651);	corners.push_back(pt);
//	pt= cv::Point2f(404,658);	corners.push_back(pt);

	std::vector<cv::Point2f> quad_pts;
	quad_pts.push_back(cv::Point2f(0, 0));
	quad_pts.push_back(cv::Point2f(quad.cols, 0));
	quad_pts.push_back(cv::Point2f(quad.cols, quad.rows));
	quad_pts.push_back(cv::Point2f(0, quad.rows));

	cv::Mat transmtx = cv::getPerspectiveTransform(corners, quad_pts);
	cv::warpPerspective(frame, quad, transmtx, quad.size());


	

//	cv::Mat quad =frame;

	double x[4]={0,0,520,520};//{25,25,545,545};//{29,29,550.550};//;
	double y[4]={0,520,520,0};//{21,543,543,21};//{11,533,533,11};//;
	
//	CFile wfile;
//	if(!wfile.Open(_T("F:\\Based-Video-Data-Trans-Method\\info.png"),CFile::modeCreate|CFile::modeWrite))
//		return;
	CString str_sum=_T("");
	CString str_all=_T("");


	int i_end=-1,j_end=-1;
	using namespace std;	ofstream outfile;	outfile.open("F:\\Based-Video-Data-Trans-Method\\out_tmp.txt");
	for(int i=0;i<50;i++){
		cv::Mat imageROI(quad,cv::Rect(x[0],y[0]+10+i*10,10,10));
		int r_pixel=0;
			for(int i_tmp=0;i_tmp<imageROI.rows;i_tmp+=1){// part A->B
				for(int j_tmp=0;j_tmp<imageROI.cols;j_tmp+=1){
					if(pt_clr_chk(imageROI.at<cv::Vec3b>(i_tmp,j_tmp))=='r'){
						r_pixel++;
					}
				}
			}

		//outfile<<i<<": "<<r_pixel<<endl;

		if(r_pixel>0.5*10*10){// part B<-A , Is Right?
			i_end=i;
			break;
		}
		//dr_border(imageROI);
	}
	
	for(int j=0;j<50;j++){
		cv::Mat imageROI(quad,cv::Rect(x[0]+10+j*10,y[0],10,10));
		int r_pixel=0;
			for(int i_tmp=0;i_tmp<imageROI.rows;i_tmp+=1){// part A->B
				for(int j_tmp=0;j_tmp<imageROI.cols;j_tmp+=1){
					if(pt_clr_chk(imageROI.at<cv::Vec3b>(i_tmp,j_tmp))=='r'){
						r_pixel++;
					}
				}
			}

		//outfile<<j<<": "<<r_pixel<<endl;

		if(r_pixel>0.5*10*10){// part B<-A
			j_end=j+1;
			break;
		}
		//dr_border(imageROI);
	}
	//outfile<<"ij_end :"<<i_end<<" , "<<j_end<<endl;
	



	//50x50
	for(int i=0;i<50;i++){
		for(int j=0;j<50;j++){
			if(i==i_end&&j==j_end){break;}
			cv::Mat imageROI(quad,cv::Rect(x[0]+10+j*10,y[0]+10+i*10,10,10));
			if((i*50+j)==786){
				read_pixel_all(imageROI);
			}
			int krgb[4]={0,0,0,0};
			for(int i_tmp=2;i_tmp<imageROI.rows-2;i_tmp+=1){
				for(int j_tmp=2;j_tmp<imageROI.cols-2;j_tmp+=1){
					switch(pt_clr_chk(imageROI.at<cv::Vec3b>(i_tmp,j_tmp))){
					case 'k':
						krgb[0]++;
						break;
					case 'r':
						krgb[1]++;
						break;
					case 'g':
						krgb[2]++;
						break;
					case 'b':
						krgb[3]++;
						break;
					default:
						break;
					}
				}
			}

			int max_tmp=-1;
			int i_max=-1;
			//切记不要改变循环的迭代变量！
			for(int ii=0;ii<4;ii++){
				if(krgb[ii]>max_tmp){
					max_tmp=krgb[ii];
					i_max=ii;
				}
			}
			
			outfile<<i_max;
	CString str_tmp;
	str_tmp.Format(_T("%d"),i_max);
	str_sum+=str_tmp;
	if((50*i+j+1)%4==0){
		str_all+=str_sum;
	for(int i=0;i<str_sum.GetLength();i+=4){
		CString str=str_sum.Mid(i,4);
		byte buf[1];
		buf[0]=( ( ( ( ( (_ttoi(str.Mid(3,1))<<2) |_ttoi(str.Mid(2,1)) )<<2 )|_ttoi(str.Mid(1,1))) )<<2 )|_ttoi(str.Mid(0,1));
		wfile.Write(buf,1);
	}

	str_sum=_T("");
	
	}
			//dr_border(imageROI);
		}
		if(i==i_end){break;}
	}
	if(i_end!=-1){
		stop=true;
	}
	//outfile<<"i_end :"<<i_end<<endl;
	outfile.close();
	if(step_run==BST_CHECKED){
	imshow("quad",quad);
	cv::waitKey(0);}
	
}
int read_pixel_all(Mat frame){
	using namespace std;	ofstream outfile;	outfile.open("F:\\Based-Video-Data-Trans-Method\\out-tmp.txt");

	//Mat frame=imread("F:\\Based-Video-Data-Trans-Method\\question.bmp");
	for(int i_tmp=0;i_tmp<frame.rows;i_tmp++){
		for(int j_tmp=0;j_tmp<frame.cols;j_tmp++){
			outfile<<0+frame.at<cv::Vec3b>(i_tmp,j_tmp)[0]<<","<<0+frame.at<cv::Vec3b>(i_tmp,j_tmp)[1]<<\
				","<<0+frame.at<cv::Vec3b>(i_tmp,j_tmp)[2]<<" :"\
				<<pt_clr_chk(frame.at<cv::Vec3b>(i_tmp,j_tmp))<<endl;
		}
	}

	outfile.close();
	return 0;
}
char pt_clr_chk(Vec3b clr){
	if(clr[1]>60&&	clr[0]<20&&	clr[2]<20){return 'g';}
/*
g =

     8    68    19
     9    68    20
     9    68     8
    10    68     9
    16    67    18
     4    62     4
     5    63     4
    12    62    15
*/
	if(abs(clr[2]-clr[1])+abs(clr[2]-clr[0])+abs(clr[0]-clr[1])>100){
		if(clr[2]>clr[0]&&clr[2]>clr[1]){return 'r';}
		if(clr[1]>clr[0]&&clr[1]>clr[2]){return 'g';}
		if(clr[0]>clr[1]&&clr[0]>clr[2]){return 'b';}
	}
	return 'k';
}
void dr_border(Mat imageROI){
	for(int i_tmp=0;i_tmp<imageROI.rows;i_tmp++){
		imageROI.at<cv::Vec3b>(i_tmp,0)[0]=0;
		imageROI.at<cv::Vec3b>(i_tmp,0)[1]=255;
		imageROI.at<cv::Vec3b>(i_tmp,0)[2]=255;

		imageROI.at<cv::Vec3b>(i_tmp,imageROI.cols-1)[0]=0;
		imageROI.at<cv::Vec3b>(i_tmp,imageROI.cols-1)[1]=255;
		imageROI.at<cv::Vec3b>(i_tmp,imageROI.cols-1)[2]=255;
	}
	for(int j_tmp=0;j_tmp<imageROI.cols;j_tmp++){
		imageROI.at<cv::Vec3b>(0,j_tmp)[0]=0;
		imageROI.at<cv::Vec3b>(0,j_tmp)[1]=255;
		imageROI.at<cv::Vec3b>(0,j_tmp)[2]=255;

		imageROI.at<cv::Vec3b>(imageROI.rows-1,j_tmp)[0]=0;
		imageROI.at<cv::Vec3b>(imageROI.rows-1,j_tmp)[1]=255;
		imageROI.at<cv::Vec3b>(imageROI.rows-1,j_tmp)[2]=255;
	}
}
int chk_bk_a(Mat srcImg){
	using namespace std;	ofstream outfile;	outfile.open("F:\\Based-Video-Data-Trans-Method\\a-out.txt");

	int isRed;
	int isGreen;
	int value[500][2]={};//500 :凭经验取得一个足够大的数
	int i,j;
	for(i=0;i<srcImg.rows;i++){
		isRed=0;isGreen=0;
		for(j=0;j<srcImg.cols;j++){
		
			if( pt_clr_chk(srcImg.at<cv::Vec3b>(i,j))=='r' ){
				isRed++;
				outfile<<"r"<<endl;
			}
		
			if( pt_clr_chk(srcImg.at<cv::Vec3b>(i,j))=='g' ){
				isGreen++;
				outfile<<"g"<<endl;
			}
		}
		value[i][0]=isGreen;
		value[i][1]=isRed;
		outfile<<"| "<<i<<": "<<isGreen<<","<<isRed<<endl;
	}
	int re_max=0;
	int i_max=-1;
	int count=5;
	
	for(int i=count;i<srcImg.rows-count;i++){
		int re=0;
		for(int i_c=1;i_c<=count;i_c++){
			re+=value[i-i_c][0]-value[i-i_c][1];
			re+=-value[i+i_c][0]+value[i+i_c][1];
		}
		//outfile<<"=re :"<<re<<endl;
		re=abs(re);
		//outfile<<"=abs(re) :"<<re<<endl;
		
		if(re>re_max){
			i_max=i;
			re_max=re;
		}
	}
	//cout<<" i_max"<< i_max<<endl;
	outfile.close();
	return i_max;
}
int chk_bk_b(Mat srcImg){
	using namespace std;	ofstream outfile;	outfile.open("F:\\Based-Video-Data-Trans-Method\\b-out.txt");

	int isRed;
	int isGreen;
	int value[500][2]={};//500 :凭经验取得一个足够大的数
	int i,j;
	for(j=0;j<srcImg.cols;j++){
		isRed=0;isGreen=0;
		for(i=0;i<srcImg.rows;i++){
		
			if( pt_clr_chk(srcImg.at<cv::Vec3b>(i,j))=='r' ){
				isRed++;
			}
		
			if( pt_clr_chk(srcImg.at<cv::Vec3b>(i,j))=='g' ){
				isGreen++;
			}
		}
		value[j][0]=isGreen;
		value[j][1]=isRed;
		outfile<<"-- "<<j<<": "<<isGreen<<","<<isRed<<endl;
	}
	int re_max=0;
	int i_max=-1;
	int count=5;
	
	for(int i=count;i<srcImg.cols-count;i++){
		int re=0;
		for(int i_c=1;i_c<=count;i_c++){
			re+=value[i-i_c][0]-value[i-i_c][1];
			re+=-value[i+i_c][0]+value[i+i_c][1];
		}
		outfile<<re<<endl;
		re=abs(re);
		if(re>re_max){
			i_max=i;
			re_max=re;
		}
	}
	outfile<<i_max<<endl;
	outfile.close();
	return i_max;
}


void CMFCAppCVagainDlg::OnBnClickedButton2(){
	GetDlgItem(IDC_EDIT1)->GetWindowText(video_name);
	use_track();
}
void use_track(){
  //CString video_name;
  //AfxGetApp()->m_pMainWnd->GetDlgItem(IDC_EDIT1)->GetWindowText(video_name);
  // 打开视频文件
  capture_track=cv::VideoCapture(video_name.GetBuffer(0));

  // 检查打开是否成功
  if (!capture_track.isOpened())
    return;

  track_i_jump=0;
  //获取整个帧数
  long totalFrameNumber = capture_track.get(CV_CAP_PROP_FRAME_COUNT);

 /// 初始化为零
 alpha_slider = 0;

 /// 创建窗体
 namedWindow("Linear Blend", 1);

 /// 在创建的窗体中创建一个滑动条控件
 char TrackbarName[50];
 sprintf( TrackbarName, "进度: %d",20  );
 

 createTrackbar( TrackbarName, "Linear Blend", &alpha_slider, totalFrameNumber, on_trackbar );

 /// 结果在回调函数中显示
 on_trackbar( alpha_slider, 0 );

 /// 按任意键退出
 waitKey(0);
 return;
}
void on_trackbar( int, void* ){
	if(track_i_jump>alpha_slider){
		//AfxGetApp()->m_pMainWnd->GetDlgItem(IDC_EDIT1)->GetWindowText(video_name);
		// 打开视频文件
		capture_track=cv::VideoCapture(video_name.GetBuffer(0));

		// 检查打开是否成功
		if (!capture_track.isOpened())
			return;

		track_i_jump=0;	
	}else{
	    // 读取下一帧（如果有）
		cv::Mat frame; // 当前视频帧
		while(true){
		if (!capture_track.read(frame))
			break;
			track_i_jump++;
		if(track_i_jump<alpha_slider){
			continue;
		}else{break;}
	}
	imshow("Linear Blend",frame);
	}
}
