// Link.cpp: implementation of the CLink class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Link.h"
#include <atlstr.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLink::CLink()
{
	m_hSocket = NULL;
	m_nPort = 6666;
}

CLink::~CLink()
{

}
//�õ���������IP��ַ;
int CLink::GetHostIP()
{
	char szhostname[128];
    CString str;
//�õ���������IP��ַ:
	if( gethostname(szhostname, 128) == 0 )
	{
		// get host adresses
		struct hostent * phost;
		int i;
 
		phost = gethostbyname(szhostname);
        m_szHostname = szhostname;

		i=0;
 		int j;
        int h_length=4;
 		for( j = 0; j<h_length; j++ )
 		{
			CString addr;
 
 			if( j > 0 )
 				str += ".";
 
 			addr.Format("%u", (unsigned int)((unsigned
		 	char*)phost->h_addr_list[i])[j]);
			str += addr;
		}  //end for~
	}
    m_szIpaddress = str;
	return 1;
}

//��ʼ����̬����;
CString CLink::m_szHostname = _T("");
CString CLink::m_szIpaddress = _T("");

//����һ����������socket;
void CLink::SocketInit()
{
	//����winsock����
	CString str;

	WSADATA wsd;   //�����Ϣ;

	if (WSAStartup(MAKEWORD(2,2), &wsd) != 0) 
	{
		AfxMessageBox("WSAStartup() failed !\n");
	}

}

//����һ���׽���;
void CLink::Create()
{	/* �����׽��� */
	m_hSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (m_hSocket == INVALID_SOCKET)
	{
		CString str;
		str.Format("m_hSocket ��ʼ��ʧ��: %d\n", WSAGetLastError() );
		AfxMessageBox(str);
	}
}
//�ر�һ���׽���;
void CLink::Close()
{
	if(m_hSocket != NULL)
	{
		if( closesocket(m_hSocket) == SOCKET_ERROR )
		{
			AfxMessageBox("�رմ���!");
		}
	}
}
//�׽��ְ�;
void CLink::Bind()
{
	struct sockaddr_in sa;
	/* ����������ַ�ṹ */
	memset(&sa, 0, sizeof(sa));
	sa.sin_family			= AF_INET;
	sa.sin_port				= htons(m_nPort);
	sa.sin_addr.S_un.S_addr	= htonl(INADDR_ANY);

	/* ���׽��ֵ���������ַ�ṹ */
	if ( bind(m_hSocket, (const sockaddr *)&sa,sizeof(sa)) != 0 )
	{
		CString str;
		str.Format("Bind() failed: %d\n", WSAGetLastError() );
		AfxMessageBox(str);
	}
}
//����
void CLink::Listen()
{
	// �����׽��� 
	if( m_hSocket != NULL )
	{
		if( listen(m_hSocket,5) == SOCKET_ERROR )
		{
			CString str;
			str.Format("Listen() failed: %d\n", WSAGetLastError() );
			AfxMessageBox(str);
		}
	}
}

//���տͻ�;
void CLink::Accept(CLink* pServer_Link)
{
	struct sockaddr_in cliaddr;
	int len = sizeof(SOCKADDR);

	pServer_Link->m_hSocket = accept(m_hSocket, (struct sockaddr *)&cliaddr, &len);
	
	if ( pServer_Link->m_hSocket == INVALID_SOCKET )
	{
		CString str;
		str.Format("Accept() failed: %d\n", WSAGetLastError() );
		AfxMessageBox(str);
		closesocket(m_hSocket);
	}
}
//��������;
int CLink::Connect(CString addr)
{
	unsigned long Server_Addr; /* ת����ķ�������ַ */
	struct sockaddr_in sa;

	Server_Addr = inet_addr(addr);

	memset(&sa, 0, sizeof(sa));
	sa.sin_family			= AF_INET;
	sa.sin_port				= htons(m_nPort);
	sa.sin_addr.S_un.S_addr	= Server_Addr;
	//�ͻ��������;
	if( connect(m_hSocket, (const sockaddr *)&sa,sizeof(sa)) != NULL )
	{
		CString str;
		str.Format("Connect() failed: %d\n", WSAGetLastError() );
		AfxMessageBox(str);
		return 0;
	}
	return 1;
}
//��������;
int CLink::Send(void* pbuffer,int nSize)
{
	int nBytesSent;
	if( (nBytesSent = send(m_hSocket,(const char*)pbuffer,nSize,0)) == SOCKET_ERROR )
	{
		AfxMessageBox("���ʹ���,�п�������������Ѿ��˳���Ϸ!\n��Ϸ����!");
		Close();
		::ExitProcess(NULL);
		return SOCKET_ERROR;
	}
	return nBytesSent;
}
//��������;
int CLink::Recv(void* pbuffer,int nSize)
{
	int nBytesReceive;
	if( (nBytesReceive = recv(m_hSocket,(char*)pbuffer,nSize,0)) == SOCKET_ERROR )
	{
		AfxMessageBox("���մ���,�п�������������Ѿ��˳���Ϸ!\n��Ϸ����!");
		Close();
		::ExitProcess(NULL);
		return SOCKET_ERROR;
	}
	return nBytesReceive;
}


