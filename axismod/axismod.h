// axismod.h : axismod Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CaxismodApp:
// �йش����ʵ�֣������ axismod.cpp
//

class CaxismodApp : public CWinApp
{
public:
	CaxismodApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CaxismodApp theApp;