
// ScanDlg.h : ͷ�ļ�
//

#pragma once

#define ICMP_MIN 8
#define DEF_PACKET 32
#define MAX_PACKET 1024

// CScanDlg �Ի���
class CScanDlg : public CDialogEx
{
// ����
public:
	CScanDlg(CWnd* pParent = NULL);	// ��׼���캯��

	CString m_Address;
	CString m_Status;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCAN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	afx_msg void OnScan();

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

private:
	short CheckSum(short *buffer, int size);
	SOCKET Socket;
	typedef struct IP_HEAD
	{
		union
		{
			unsigned char Version;	//�汾
			unsigned char HeadLen;	//ͷ������
		};
		unsigned char ServiceType;	//��������
		unsigned short TotalLen;	//�ܳ���
		unsigned short Identifier;	//��ʶ��
		union
		{
			unsigned short Flags;	//��־
			unsigned short FragOffset;	//Ƭƫ��
		};
		unsigned char TimeToLive;
		unsigned char Protocol;		//Э��
		unsigned short HeadCheckSum;	//ͷ��У���
		unsigned int SourceAddr;	//Դ��ַ
		unsigned int DestAddr;		//Ŀ��ip
	}ip_head;

	typedef struct ICMP_HEAD
	{
		unsigned char Type;
		unsigned char Code;   //����
		unsigned HeadCheckSum;  //У���
		unsigned short Identifier;
		unsigned short Sequence;
	}icmp_head;
};
