
// MFCApp-CV-again.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCAppCVagainApp:
// �йش����ʵ�֣������ MFCApp-CV-again.cpp
//

class CMFCAppCVagainApp : public CWinApp
{
public:
	CMFCAppCVagainApp();

// ��д
public:
	virtual BOOL InitInstance();
	
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCAppCVagainApp theApp;