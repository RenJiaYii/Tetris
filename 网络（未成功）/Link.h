// Link.h: interface for the CLink class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINK_H__287CDDA6_0405_4A4C_AF03_E29CB5624C55__INCLUDED_)
#define AFX_LINK_H__287CDDA6_0405_4A4C_AF03_E29CB5624C55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLink  
{
private:


	char buff[256]; /* ��ŷ���˷��ص���Ϣ */

	unsigned long uladdr; /* ת����ķ�������ַ */

	int m_nPort;		/* Ĭ��ȥ���ӵĶ˿� */
	SOCKET m_hSocket;

	struct sockaddr_in cliaddr; /* ��ŷ��صĿͻ���ַ��Ϣ */
public:
	static CString	m_szHostname;	  //������;
	static CString  m_szIpaddress;  //����IP��ַ;
	static int GetHostIP();
public:
	CLink();
	virtual ~CLink();

	void SocketInit();

	void Create();
	void Bind();
	void Close();

	void Listen();
	void Accept(CLink* pServer_Link);
	int Connect(CString);   //0��ʾʧ��,1��ʾ�ɹ�;

	int Send(void* pbuffer,int nSize);
	int Recv(void* pbuffer,int nSize);
};

#endif // !defined(AFX_LINK_H__287CDDA6_0405_4A4C_AF03_E29CB5624C55__INCLUDED_)
