
// ScanDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Scan.h"
#include "ScanDlg.h"
#include "afxdialogex.h"
#include"PortScan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CScanDlg �Ի���



CScanDlg::CScanDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SCAN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CScanDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CScanDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CScanDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CScanDlg ��Ϣ�������

BOOL CScanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CScanDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CScanDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CScanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CScanDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEdit *p1, *p2, *pStatus;
	CString address_1, address_2, Address;
	p1 = (CEdit*)GetDlgItem(IDC_EDIT1);
	p2 = (CEdit*)GetDlgItem(IDC_EDIT2);
	pStatus = (CEdit*)GetDlgItem(IDC_EDIT3);
	p1->GetWindowText(address_1);
	p2->GetWindowText(address_2);

	CString s1 = address_1.Right(3);
	CString s2 = address_2.Right(3);
	Address = address_1.Left(address_1.GetLength() - 3);
	//�������ת��������
	int a1 = atoi(s1);
	int a2 = atoi(s2);

	//ѭ�����ж˿�ɨ��
	for (int i = a1; i <= a2; i++)
	{
		CString port, temp;
		port.Format("%d", i);
		temp = Address;
		temp.Append(port);
		m_Address = temp;
		OnScan();
		pStatus->SetWindowText(m_Status);
	}
}


void CScanDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPortScan cpdlg;
	cpdlg.DoModal();
	this->ShowWindow(SW_SHOW);
}

void CScanDlg::OnScan()
{
	UpdateData(true);
	WSADATA WSAData;             //������Socket�İ�
								 //MAKEWORD(2,2)��ʾʹ��WINSOCK2�汾.wsaData�����洢ϵͳ���صĹ���WINSOCK������.
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
	{
		MessageBox("WSAStartup��ʼ��ʧ��!");
		WSACleanup();
		return;
	}
	/*
	AF_INET��ʾipv4Э��
	SOCK_RAW��ʾԭʼ���ֽ�
	IPPROTO_ICMP��ʾICMPЭ��
	*/
	Socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	int code = WSAGetLastError();
	if (Socket == INVALID_SOCKET)
	{
		MessageBox("Sokcet����ʧ��");
		WSACleanup();
		return;
	}
	int SendTimeout = 1000;//���÷���ʱ��
	if (setsockopt(Socket, SOL_SOCKET, SO_SNDTIMEO, (char*)&SendTimeout, sizeof(SendTimeout)) == SOCKET_ERROR)
	{
		MessageBox("���÷��ͳ�ʱ!");
		closesocket(Socket);
		WSACleanup();
		return;
	}
	int RecvTimeout = 1000;              //���ý��ܳ�ʱʱ��
										 //��ֹ����ӵ��
	if (setsockopt(Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&RecvTimeout, sizeof(RecvTimeout)) == SOCKET_ERROR)
	{
		MessageBox("���÷��ͳ�ʱʱ��!");
		closesocket(Socket);
		WSACleanup();
		return;
	}
	int IpAddress;
	IpAddress = inet_addr(m_Address);
	if (IpAddress == INADDR_NONE)
	{
		hostent *pHostent = gethostbyname(m_Address);
		if (pHostent)
			IpAddress = (*(in_addr*)pHostent->h_addr).s_addr;
	}
	sockaddr_in DestHost;     //����Ŀ��������ַ
	memset(&DestHost, 0, sizeof(DestHost));
	DestHost.sin_family = AF_INET;
	DestHost.sin_addr.s_addr = IpAddress;
	char IcmpData[MAX_PACKET];//���icmp���ݰ�
	icmp_head *IcmpHead;
	int IcmpSize;
	memset(IcmpData, 0, MAX_PACKET);
	IcmpHead = (icmp_head*)IcmpData;
	IcmpSize = DEF_PACKET + sizeof(icmp_head);
	IcmpHead->Type = 8;
	IcmpHead->Code = 0;
	IcmpHead->Identifier = (unsigned short)GetCurrentThreadId();
	IcmpHead->Sequence = 1;
	IcmpHead->HeadCheckSum = CheckSum((short*)IcmpData, IcmpSize);
	int nSend;                  //�������ݰ�
	nSend = sendto(Socket, IcmpData, IcmpSize, 0, (sockaddr*)&DestHost, sizeof(DestHost));
	if (nSend == SOCKET_ERROR || nSend < IcmpSize)
	{
		MessageBox("ICMP������ʧ��!");
		closesocket(Socket);
		WSACleanup();
		return;
	}
	sockaddr_in SourceHost;
	int SourceSize;
	char *RecvBuf;
	int RecvSize;
	SourceSize = sizeof(SourceHost);
	memset(&SourceHost, 0, SourceSize);
	RecvSize = MAX_PACKET + sizeof(ip_head);
	RecvBuf = new char[RecvSize];
	memset(RecvBuf, 0, RecvSize);
	int nRecv;
	nRecv = recvfrom(Socket, RecvBuf, RecvSize, 0, (sockaddr*)&SourceHost, &SourceSize);
	if (nRecv == SOCKET_ERROR)
	{
		m_Status += m_Address;
		m_Status += ": Closed\r\n";
	}
	else
	{
		ip_head *IpHead;
		int IpSize;
		IpHead = (ip_head*)RecvBuf;
		IpSize = (IpHead->HeadLen & 0x0f) * 4;
		IcmpHead = (icmp_head*)(RecvBuf + IpSize);
		if (nRecv < IpSize + ICMP_MIN)
		{
			m_Status += m_Address;
			m_Status += ": Closed\r\n";
		}
		else
		{
			if (IcmpHead->Type != 0)
			{
				m_Status += m_Address;
				m_Status += ": Closed\r\n";
			}
			else
			{
				if (IcmpHead->Identifier != (short)GetCurrentThreadId())
				{
					m_Status += m_Address;
					m_Status += ": Closed\r\n";
				}
				else
				{
					m_Status += m_Address;
					m_Status += ": Open\r\n";
				}
			}
		}
	}

	UpdateData(false);
	closesocket(Socket);
	WSACleanup();
}

short CScanDlg::CheckSum(short *buffer,int size)
{
	int Sum = 0;
	while (size > 0)
	{
		Sum += *(buffer++);
		size -= sizeof(short);
	}
	if (size)
		Sum += *(char*)buffer;
	Sum = (Sum >> 16) + (Sum & 0xffff);
	Sum += (Sum >> 16);
	return (short)(~Sum);
}
