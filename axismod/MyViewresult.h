#pragma once
#include "transformxis.h"
#include "limdata.h"

// MyViewresult ��ͼ


class MyViewresult : public CView
{
	DECLARE_DYNCREATE(MyViewresult)

protected:
	MyViewresult();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~MyViewresult();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnRefresh(WPARAM wParam, LPARAM lParam);
	int layern;// ��n����״��������
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void drawlim(CDC* pdc,transformaxis trans);


	bool isinlim(int* x, int* y);
};


