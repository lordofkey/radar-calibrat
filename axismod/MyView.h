#pragma once
#include "atltypes.h"





// MyView ��ͼ

class MyView : public CView
{
	DECLARE_DYNCREATE(MyView)

protected:
	MyView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~MyView();

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
//	afx_msg void OnOpen();
	afx_msg LRESULT OnRefresh(WPARAM wParam, LPARAM lParam);
//	afx_msg void On32773();
	virtual void OnInitialUpdate();
	
	
	int layern;// ��n����״��������

	
	CPoint Lstpoint;// �������ʼλ��	
	CPoint Lenpoint;// ����ֹ��
	bool Lisdown;// ����Ƿ���

	CPoint Rstpoint;// �������ʼλ��	
	CPoint Renpoint;// ����ֹ��
	bool Risdown;// ����Ƿ���




	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	int isrl;
};


