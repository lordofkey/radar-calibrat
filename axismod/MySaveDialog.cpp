// MySaveDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "axismod.h"
#include "MySaveDialog.h"


// MySaveDialog �Ի���

IMPLEMENT_DYNAMIC(MySaveDialog, CDialog)

MySaveDialog::MySaveDialog(CWnd* pParent /*=NULL*/)
	: CDialog(MySaveDialog::IDD, pParent)
	, linetext(_T(""))
{

}

MySaveDialog::~MySaveDialog()
{
}

void MySaveDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, linetext);
}


BEGIN_MESSAGE_MAP(MySaveDialog, CDialog)
END_MESSAGE_MAP()


// MySaveDialog ��Ϣ�������

void MySaveDialog::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	this->UpdateData(true);
	if(linetext.IsEmpty())
	{
		MessageBox("��·���Ʋ��������ף���������д��");
		return;
	}
	CDialog::OnOK();
}
