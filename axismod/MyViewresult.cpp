// MyViewresult.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "axismod.h"
#include "MyViewresult.h"
#include "atlimage.h"
#define DRAWPOINTS
#define COLOR1 RGB(255,0,0)
#define COLOR2 RGB(0,255,255)
#define COLOR3 RGB(0,0,255)
#define COLOR4 RGB(255,255,0)
#define COLOR5 RGB(255,0,0)
#define COLOR6 RGB(0,255,0)
// MyViewresult

IMPLEMENT_DYNCREATE(MyViewresult, CView)

MyViewresult::MyViewresult()
{

}

MyViewresult::~MyViewresult()
{
}

BEGIN_MESSAGE_MAP(MyViewresult, CView)
	ON_MESSAGE(WM_REFRESH,&MyViewresult::OnRefresh)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// MyViewresult ��ͼ

void MyViewresult::OnDraw(CDC* pDC)
{

	int *x = NULL;   //��Ҫ��ʾ��x����ָ��
	int *y = NULL;   //��Ҫ��ʾ��y����ָ��
	CRect drect;
	this->GetClientRect(&drect);
	transformaxis trans(drect,-4000,4000,-1000,6000);			    //�趨��ʾ��Χ


#pragma region ˫����initial
	CDC dcMem;														//���ڻ�����ͼ���ڴ�DC
	CBitmap bmp;													//�ڴ��г�����ʱͼ���λͼ
	dcMem.CreateCompatibleDC(pDC);									//��������DC���������ڴ�DC
	bmp.CreateCompatibleBitmap(pDC,drect.Width(),drect.Height());	//��������λͼ
	dcMem.SelectObject(&bmp);                          //��λͼѡ����ڴ�DC
	dcMem.FillSolidRect(drect,RGB(125,125,125));//��ԭ���������ͻ�������Ȼ���Ǻ�ɫ
#pragma endregion ˫����initial


	CPen ppen(1,2,RGB(0,255,0));
	dcMem.SelectObject(&ppen);

	dcMem.MoveTo(trans.gettx(-2440),trans.getty(0));
	dcMem.LineTo(trans.gettx(2440),trans.getty(0));
	dcMem.MoveTo(trans.gettx(0),trans.getty(0));
	dcMem.LineTo(trans.gettx(0),trans.getty(5540));

	drawlim(&dcMem,trans);//���޿���ʾ
	bool pic = false;

#pragma region �״���ͼ
	if(Mymodfunc::GetInstance()->Getpiecenmod(layern,&x ,&y))
	{
		if(!isinlim(x,y))
			pic = true;
		for(int i = 0;i<180;i++)
		{

			dcMem.SetPixel(trans.gettx(x[i]),trans.getty(y[i]),RGB(255,0,0));
#ifdef DRAWPOINTS  //�������DRAWPOINTS����һ����ĵ�
			dcMem.SetPixel(trans.gettx(x[i])+1,trans.getty(y[i]),RGB(255,0,0));
			dcMem.SetPixel(trans.gettx(x[i])-1,trans.getty(y[i]),RGB(255,0,0));
			dcMem.SetPixel(trans.gettx(x[i]),trans.getty(y[i])+1,RGB(255,0,0));
			dcMem.SetPixel(trans.gettx(x[i]),trans.getty(y[i])-1,RGB(255,0,0));
#endif
		}
		delete x;
		delete y;
	}
	if(Mymodfunc::GetInstance()->Getpiecenmodr(layern,&x ,&y))
	{
		if(!isinlim(x,y))
			pic = true;
		for(int i = 0;i<180;i++)
		{
			dcMem.SetPixel(trans.gettx(x[i]),trans.getty(y[i]),  RGB(0,0,255));
#ifdef DRAWPOINTS  //�������DRAWPOINTS����һ����ĵ�
			dcMem.SetPixel(trans.gettx(x[i])+1,trans.getty(y[i]),  RGB(0,0,255));
			dcMem.SetPixel(trans.gettx(x[i])-1,trans.getty(y[i]),  RGB(0,0,255));
			dcMem.SetPixel(trans.gettx(x[i]),trans.getty(y[i])+1,  RGB(0,0,255));
			dcMem.SetPixel(trans.gettx(x[i]),trans.getty(y[i])-1,  RGB(0,0,255));
#endif
		}
		delete x;
		delete y;
	}
#pragma endregion �״���ͼ

	if(false)
	{
		CImage imgTemp;     
        imgTemp.Attach(bmp.operator HBITMAP());
		CString tem;
		tem.Format("%d",this->layern);
		tem += ".BMP";
        imgTemp.Save(tem);
	}
	pDC->BitBlt(0,0,drect.Width(),drect.Height(),&dcMem,0,0,SRCCOPY);//���ڴ�DC�ϵ�ͼ�󿽱���ǰ̨
	dcMem.DeleteDC();                                       //ɾ��DC
	bmp.DeleteObject();
}


// MyViewresult ���

#ifdef _DEBUG
void MyViewresult::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void MyViewresult::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


LRESULT MyViewresult::OnRefresh(WPARAM wParam, LPARAM lParam)  
{
	layern = wParam;
	this->Invalidate();
	return 0;
}
// MyViewresult ��Ϣ�������

void MyViewresult::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	Mymodfunc::GetInstance()->h_viewm = this->m_hWnd;
}

BOOL MyViewresult::OnEraseBkgnd(CDC* pDC)
{
	return true;
//	return CView::OnEraseBkgnd(pDC);
}

void MyViewresult::drawlim(CDC* pdc, transformaxis trans)
{

	CPen fpen1(PS_SOLID,1,COLOR1);
	CPen fpen2(PS_SOLID,1,COLOR2);
	CPen fpen3(PS_SOLID,1,COLOR3);
	CPen fpen4(PS_SOLID,1,COLOR4);
	CPen fpen5(PS_SOLID,1,COLOR5);
	CPen fpen6(PS_SOLID,1,COLOR6);
	pdc->SelectObject(&fpen1);
	pdc->MoveTo(trans.gettx(-m_trainlimit[0]),trans.getty(m_measuredheight[0]));
	for(int i = 1;i<287;i++)
	{
		if(m_trainlimit[i] != 0)
			pdc->LineTo(trans.gettx(-m_trainlimit[i]),trans.getty(m_measuredheight[i]));
		else
		{
			pdc->LineTo(trans.gettx(m_trainlimit[i-1]),trans.getty(m_measuredheight[i-1]));
			break;
		}
		if(i == 286)
		{
			pdc->LineTo(trans.gettx(m_trainlimit[i]),trans.getty(m_measuredheight[i]));
		}
	}
	pdc->MoveTo(trans.gettx(m_trainlimit[0]),trans.getty(m_measuredheight[0]));
	for(int i = 1;i<287;i++)
	{
		if(m_trainlimit[i] != 0)
			pdc->LineTo(trans.gettx(m_trainlimit[i]),trans.getty(m_measuredheight[i]));
		else
		{
			break;
		}
	}


	pdc->SelectObject(&fpen2);
	pdc->MoveTo(trans.gettx(-m_firstlimit[35]),trans.getty(m_measuredheight[35]));
	for(int i = 35;i<287;i++)
	{
		if(m_firstlimit[i] != 0)
			pdc->LineTo(trans.gettx(-m_firstlimit[i]),trans.getty(m_measuredheight[i]));
		else
		{
			pdc->LineTo(trans.gettx(m_firstlimit[i-1]),trans.getty(m_measuredheight[i-1]));
			break;
		}
		if(i == 286)
		{
			pdc->LineTo(trans.gettx(m_firstlimit[i]),trans.getty(m_measuredheight[i]));
		}
	}
	pdc->MoveTo(trans.gettx(m_firstlimit[35]),trans.getty(m_measuredheight[35]));
	for(int i = 35;i<287;i++)
	{
		if(m_firstlimit[i] != 0)
			pdc->LineTo(trans.gettx(m_firstlimit[i]),trans.getty(m_measuredheight[i]));
		else
		{
			break;
		}
	}


	pdc->SelectObject(&fpen3);
	pdc->MoveTo(trans.gettx(-m_secondlimit[0]),trans.getty(m_measuredheight[0]));
	for(int i = 1;i<287;i++)
	{
		if(m_secondlimit[i] != 0)
			pdc->LineTo(trans.gettx(-m_secondlimit[i]),trans.getty(m_measuredheight[i]));
		else
		{
			pdc->LineTo(trans.gettx(m_secondlimit[i-1]),trans.getty(m_measuredheight[i-1]));
			break;
		}
		if(i == 286)
		{
			pdc->LineTo(trans.gettx(m_secondlimit[i]),trans.getty(m_measuredheight[i]));
		}
	}
	pdc->MoveTo(trans.gettx(m_secondlimit[0]),trans.getty(m_measuredheight[0]));
	for(int i = 1;i<287;i++)
	{
		if(m_secondlimit[i] != 0)
			pdc->LineTo(trans.gettx(m_secondlimit[i]),trans.getty(m_measuredheight[i]));
		else
		{
			break;
		}
	}


	pdc->SelectObject(&fpen4);
	pdc->MoveTo(trans.gettx(-m_buildinglimit[0]),trans.getty(m_measuredheight[0]));
	for(int i = 1;i<287;i++)
	{
		if(m_buildinglimit[i] != 0)
			pdc->LineTo(trans.gettx(-m_buildinglimit[i]),trans.getty(m_measuredheight[i]));
		else
		{
			pdc->LineTo(trans.gettx(m_buildinglimit[i-1]),trans.getty(m_measuredheight[i-1]));
			break;
		}
		if(i == 286)
		{
			pdc->LineTo(trans.gettx(m_buildinglimit[i]),trans.getty(m_measuredheight[i]));
		}
	}
	pdc->MoveTo(trans.gettx(m_buildinglimit[0]),trans.getty(m_measuredheight[0]));
	for(int i = 1;i<287;i++)
	{
		if(m_buildinglimit[i] != 0)
			pdc->LineTo(trans.gettx(m_buildinglimit[i]),trans.getty(m_measuredheight[i]));
		else
		{
			break;
		}
	}
}


bool MyViewresult::isinlim(int* x, int* y)
{
	for(int i = 0;i < 180;i++)
	{
		if((x[i]>-2440)&&(x[i] < 2440)&&(y[i] > 1250)&&(y[i] < 5550))
		{
			if(y[i]>4800)
				return false;
			else
			{
				int j = 0;
				while(true)
				{
					if(y[i]<m_measuredheight[j])
						break;
					j++;
				}
				int xlim = m_trainlimit[j-1]+(m_trainlimit[j]-m_trainlimit[j-1])*(y[i]-m_measuredheight[j-1])/(m_measuredheight[j] - m_measuredheight[j-1]);
				if((x[i]<-xlim)||(x[i]>xlim))
				{
					return false;
				}
			}
		}
	}
	return true;
}
