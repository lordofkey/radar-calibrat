// MyView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "axismod.h"
#include "MyView.h"
#include "transformxis.h"

// MyView

IMPLEMENT_DYNCREATE(MyView, CView)


#ifdef _DEBUG
transformaxis test(CRect clientrect,float xs,float xe,float ys,float ye);

#endif


MyView::MyView()
: layern(0)
, Lstpoint(0)
, Lenpoint(0)
, Lisdown(false)
, Rstpoint(0)
, Renpoint(0)
, Risdown(false)
, isrl(1)
{
}


MyView::~MyView()
{
}

BEGIN_MESSAGE_MAP(MyView, CView)
	ON_MESSAGE(WM_REFRESH,&MyView::OnRefresh)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// MyView ��ͼ

void MyView::OnDraw(CDC* pDC)
{

	int *x = NULL;
	int *y = NULL;
	CRect drect;
	this->GetClientRect(&drect);

	transformaxis trans(drect,-10000,10000,-10000,1000);
	CDC dcMem;                                   //���ڻ�����ͼ���ڴ�DC
	CBitmap bmp;                                 //�ڴ��г�����ʱͼ���λͼ
	dcMem.CreateCompatibleDC(pDC);               //��������DC���������ڴ�DC
	bmp.CreateCompatibleBitmap(pDC,drect.Width(),drect.Height());//��������λͼ
	dcMem.SelectObject(&bmp);                          //��λͼѡ����ڴ�DC
	dcMem.FillSolidRect(drect,RGB(225,225,225));       //���ñ�����ɫ
	dcMem.Rectangle(Lstpoint.x,Lstpoint.y,Lenpoint.x,Lenpoint.y);
	dcMem.Rectangle(Rstpoint.x,Rstpoint.y,Renpoint.x,Renpoint.y);
	printf("roi1: x:%d y:%d ox:%f oy%f\n",Lstpoint.x,Lstpoint.y,trans.getox(Lstpoint.x),trans.getoy(Lstpoint.y));

	Mymodfunc::GetInstance()->lroix_min = trans.getox(Lstpoint.x);
	Mymodfunc::GetInstance()->lroix_max = trans.getox(Lenpoint.x);
	Mymodfunc::GetInstance()->lroiy_min = trans.getoy(Lenpoint.y);
	Mymodfunc::GetInstance()->lroiy_max = trans.getoy(Lstpoint.y);

	Mymodfunc::GetInstance()->rroix_min = trans.getox(Rstpoint.x);
	Mymodfunc::GetInstance()->rroix_max = trans.getox(Renpoint.x);
	Mymodfunc::GetInstance()->rroiy_min = trans.getoy(Renpoint.y);
	Mymodfunc::GetInstance()->rroiy_max = trans.getoy(Rstpoint.y);

	CBrush pbrush = CBrush(RGB(255,0,0));
	dcMem.SelectObject(&pbrush);
	dcMem.SelectStockObject(NULL_PEN);
	dcMem.Ellipse(trans.gettx(0)-5,trans.getty(0)-5,trans.gettx(0)+5,trans.getty(0)+5);
	if(Mymodfunc::GetInstance()->Getpiecen(layern,&x ,&y))
	{
		for(int i = (isrl-1) * 180;i<180 * isrl;i++)
		{
			dcMem.SetPixel(trans.gettx(x[i]),trans.getty(y[i]),RGB(0,0,0));
			dcMem.SetPixel(trans.gettx(x[i])+1,trans.getty(y[i]),RGB(0,0,0));
			dcMem.SetPixel(trans.gettx(x[i])-1,trans.getty(y[i]),RGB(0,0,0));
			dcMem.SetPixel(trans.gettx(x[i]),trans.getty(y[i])+1,RGB(0,0,0));
			dcMem.SetPixel(trans.gettx(x[i]),trans.getty(y[i])-1,RGB(0,0,0));
		}
		delete x;
		delete y;
	}
	pDC->BitBlt(0,0,drect.Width(),drect.Height(),&dcMem,0,0,SRCCOPY);//���ڴ�DC�ϵ�ͼ�󿽱���ǰ̨
	dcMem.DeleteDC();                                          //ɾ��DC
	bmp.DeleteObject();                                        //ɾ��λͼ
}


// MyView ���

#ifdef _DEBUG
void MyView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void MyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// MyView ��Ϣ�������
LRESULT MyView::OnRefresh(WPARAM wParam, LPARAM lParam)  
{
	layern = wParam;
	if(lParam != NULL)
		isrl = lParam;
	this->Invalidate();
	return 0;
}

void MyView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	Mymodfunc::GetInstance()->h_view = this->m_hWnd;
}

void MyView::OnLButtonDown(UINT nFlags, CPoint point)
{
	Lstpoint = point;
	Lisdown = true;
	CView::OnLButtonDown(nFlags, point);
}

void MyView::OnMouseMove(UINT nFlags, CPoint point)
{
	if(Lisdown == true)
	{
		Lenpoint = point;
		this->Invalidate();
	}
	else if(Risdown == true)
	{
		Renpoint = point;
		this->Invalidate();
	}
	CView::OnMouseMove(nFlags, point);
}

void MyView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(Lisdown == true)
	{
		Lisdown = false;
		Lenpoint = point;
		this->Invalidate();
	}
	CView::OnLButtonUp(nFlags, point);
}

void MyView::OnRButtonDown(UINT nFlags, CPoint point)
{
	Rstpoint = point;
	Risdown = true;
	CView::OnRButtonDown(nFlags, point);
}

void MyView::OnRButtonUp(UINT nFlags, CPoint point)
{
	if(Risdown == true)
	{
		Risdown = false;
		Renpoint = point;
		this->Invalidate();
	}
	CView::OnRButtonUp(nFlags, point);
}

BOOL MyView::OnEraseBkgnd(CDC* pDC)
{
	return true;
//	return CView::OnEraseBkgnd(pDC);
}
