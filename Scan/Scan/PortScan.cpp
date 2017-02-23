// PortScan.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Scan.h"
#include "PortScan.h"
#include "afxdialogex.h"


// CPortScan �Ի���

IMPLEMENT_DYNAMIC(CPortScan, CDialogEx)

CPortScan::CPortScan(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CPortScan::~CPortScan()
{
}

void CPortScan::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPortScan, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CPortScan::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPortScan::OnBnClickedButton2)
END_MESSAGE_MAP()


// CPortScan ��Ϣ�������


void CPortScan::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEdit *cp1, *cp2, *cstatus;
	cp1 = (CEdit*)GetDlgItem(IDC_EDIT1);
	cp2 = (CEdit*)GetDlgItem(IDC_EDIT2);
	cstatus = (CEdit*)GetDlgItem(IDC_EDIT3);
	cp1->GetWindowTextA(m_Address);
	cp2->GetWindowTextA(m_Port);
	OnTcpScan();
	cstatus->SetWindowTextA(m_Status);
}


void CPortScan::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEdit *cp1, *cp2, *cstatus;
	cp1 = (CEdit*)GetDlgItem(IDC_EDIT1);
	cp2 = (CEdit*)GetDlgItem(IDC_EDIT2);
	cstatus = (CEdit*)GetDlgItem(IDC_EDIT3);
	cp1->GetWindowTextA(m_Address);
	cp2->GetWindowTextA(m_Port);
	OnUdpScan();
	cstatus->SetWindowTextA(m_Status);
}

void CPortScan::OnTcpScan()
{
	UpdateData(true);
	m_Status += "TCP Port:";
	WSADATA WASdata;//�������ֽڰ�
	if (WSAStartup(MAKEWORD(2, 2), &WASdata) != 0)//
	{
		MessageBox("��ʼ��Winsockʧ��");
		return;
	}

	Socket = socket(AF_INET, SOCK_STREAM, 0);//�����������ֽ�
	if (Socket == INVALID_SOCKET)
	{
		MessageBox("�����ַ���ʧ��!");
		WSACleanup();
		return;
	}
	int ipAddress;
	ipAddress = inet_addr(m_Address);
	if (ipAddress == INADDR_NONE)//inaddr_noneָip��ַ��Ч
	{
		hostent* pHostent = gethostbyname(m_Address);
		if (pHostent)
			ipAddress = (*(in_addr*)pHostent->h_addr).s_addr;
	}

	sockaddr_in DestHost;
	memset(&DestHost, 0, sizeof(DestHost));
	DestHost.sin_family = AF_INET;//Э����,Socket�����ֻ��ʹ��AF_INET;
	int t = atoi(m_Port);
	DestHost.sin_port = htons(t);//���ö˿�,htons�������ֽ�����������
	DestHost.sin_addr.s_addr = ipAddress;//����ip��ַ

	int nConnect;     //�������������ϵ
	nConnect = connect(Socket, (sockaddr*)&DestHost, sizeof(DestHost));
	if (nConnect == SOCKET_ERROR)
	{
		m_Status += m_Port;
		m_Status += ": Close\r\n";
	}
	else
	{
		m_Status += m_Port;
		m_Status += ": Open\r\n";
	}
	UpdateData(false);
	closesocket(Socket);
	WSACleanup();//�ͷ��׽��ְ�
}

void CPortScan::OnUdpScan()
{
	UpdateData(true);
	m_Status += "UDP Port:";
	WSADATA WSAData;//�������ֽ�
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
	{
		MessageBox("��ʼ��Winsockʧ��!");
		return;
	}

	/*
	AF_INET��ʾipv4Э��
	SOCK_DGRAM��ʾudpЭ��
	*/
	Socket = socket(AF_INET, SOCK_DGRAM, 0);//�����������ֽ�

	if (Socket == INVALID_SOCKET)
	{
		MessageBox("����Socketʧ��!");
		WSACleanup();
		return;
	}
	int nIotrl;
	unsigned long Flag = 1;
	nIotrl = ioctlsocket(Socket, FIONBIO, &Flag);//������ģʽ
	if (nIotrl == SOCKET_ERROR)
	{
		MessageBox("����Socketģʽʧ��!");
		closesocket(Socket);
		WSACleanup();
		return;
	}
	int ipAddress;
	ipAddress = inet_addr(m_Address);//��ip��ַ˳��ת��������
	if (ipAddress == INADDR_NONE)
	{
		hostent *pHostent = gethostbyname(m_Address);
		if (pHostent)
			ipAddress = (*(in_addr*)pHostent->h_addr).s_addr;
	}
	sockaddr_in DestHost;
	memset(&DestHost, 0, sizeof(DestHost));
	DestHost.sin_family = AF_INET;
	DestHost.sin_port = htons(atoi(m_Port));
	DestHost.sin_addr.s_addr = ipAddress;

	//��host
	if (bind(Socket, (sockaddr*)&DestHost, sizeof(DestHost)) < 0)
	{
		m_Status += "bind error\r\n";
	}

	char *SendBuf;
	SendBuf = new char[4];
	memset(SendBuf, 0, 4);
	strcpy(SendBuf, "cd");
	int nSend;
	nSend = sendto(Socket, SendBuf, strlen(SendBuf), 0, (sockaddr*)&DestHost, sizeof(DestHost));
	if (nSend == SOCKET_ERROR)
	{
		MessageBox("UDP������ʧ��!");
		closesocket(Socket);
		WSACleanup();
		return;
	}
	Sleep(500);

	sockaddr_in SourceHost;
	int SourceSize;
	SourceSize = sizeof(SourceHost);
	memset(&SourceHost, 0, SourceSize);
	char *RecvBuf;
	RecvBuf = new char[4];
	memset(RecvBuf, 0, 4);
	int nRecv;			//����udp���ݰ�
						//����ʽ����
						//���޴��󽫷��ض�����ֽ���
	nRecv = recvfrom(Socket, RecvBuf, 4, 0, (sockaddr*)&SourceHost, &SourceSize);
	if (nRecv == SOCKET_ERROR)
	{
		int ErrorCode = WSAGetLastError();
		if (ErrorCode == 10054)
		{
			m_Status += m_Port;
			m_Status += ": Close\r\n";
		}
		if (ErrorCode == 10035)
		{
			m_Status += m_Port;
			m_Status += ": ���� \r\n";
		}
	}
	else
	{
		m_Status += m_Port;
		//		m_Status += "\r\ndata:";
		//		m_Status += RecvBuf;
		m_Status += ": Open\r\n";
	}

	UpdateData(false);
	closesocket(Socket);
	WSACleanup();
}