#pragma once


// MySaveDialog �Ի���

class MySaveDialog : public CDialog
{
	DECLARE_DYNAMIC(MySaveDialog)

public:
	MySaveDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MySaveDialog();

// �Ի�������
	enum { IDD = IDD_MYSAVEDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CString linetext;
};
