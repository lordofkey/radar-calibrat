#pragma once


// MyLoadDialog �Ի���

class MyLoadDialog : public CDialog
{
	DECLARE_DYNAMIC(MyLoadDialog)

public:
	MyLoadDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MyLoadDialog();

// �Ի�������
	enum { IDD = IDD_MYLOADDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString str_lines;
};
