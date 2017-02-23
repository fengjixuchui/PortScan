#pragma once


// CPortScan �Ի���

class CPortScan : public CDialogEx
{
	DECLARE_DYNAMIC(CPortScan)

public:
	CPortScan(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPortScan();
	CString m_Address;
	CString m_Status;
	CString m_Port;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnTcpScan();
	afx_msg void OnUdpScan();
private:
	SOCKET Socket;
};
