// MyLoadDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "axismod.h"
#include "MyLoadDialog.h"
#include "MySetting.h"

// MyLoadDialog �Ի���

IMPLEMENT_DYNAMIC(MyLoadDialog, CDialog)

MyLoadDialog::MyLoadDialog(CWnd* pParent /*=NULL*/)
	: CDialog(MyLoadDialog::IDD, pParent)
	, str_lines(_T(""))
{

}

MyLoadDialog::~MyLoadDialog()
{
}

void MyLoadDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_LBString(pDX, IDC_LIST1, str_lines);
}


BEGIN_MESSAGE_MAP(MyLoadDialog, CDialog)
END_MESSAGE_MAP()


// MyLoadDialog ��Ϣ�������


BOOL MyLoadDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	MySetting setting;
	str_lines += "adgflgjksef";
	this->UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
}
