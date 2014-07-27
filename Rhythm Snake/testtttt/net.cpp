// net.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mysnake.h"
#include "net.h"
#include "afxdialogex.h"
#include<afxsock.h>
#include<stdlib.h>
#include"mysnakeView.h"
#include<string>
#include"manage.h"
#include"snake.h"
#include"NetSnake.h"//ֱ�ӿ��Ƶ��ߣ��ɿͻ�������������������
int finish = 0;
char name[20][100];
int user[10];
int only=1;
CString severname;
// net �Ի���
/*
�ַ���һ����ʾ���
0�����ԣ�������
1��������Ϣ
2��������ң��������������
3�����ص�ID��������
4����ҵĲ���������ID,�Ͱ���
5���˳�
*/

IMPLEMENT_DYNAMIC(net, CDialogEx)

net::net(CWnd* pParent /*=NULL*/)
	: CDialogEx(net::IDD, pParent)
{
	server=0;
	
}

net::~net()
{
}

void net::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	this->SetDlgItemTextW(IDC_EDIT3,L"��ǰ������");
	this->SetDlgItemTextW(IDC_EDIT4,L"IP��ַ��");
	this->SetDlgItemTextW(IDC_EDIT5,L"��Ϣ�б�");
	this->SetDlgItemTextW(IDC_EDIT7,L"������ʾ��");
}

BEGIN_MESSAGE_MAP(net, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &net::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_CONNECT, &net::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_BUTTON3, &net::OnBnClickedButton3)
	ON_COMMAND(IDOK, &net::OnIdok)
	ON_COMMAND(IDCANCEL, &net::OnIdcancel)
	ON_BN_CLICKED(IDC_BUTTON4, &net::OnBnClickedButton4)
//	ON_BN_CLICKED(IDC_BUTTON5, &net::OnBnClickedButton5)
ON_BN_CLICKED(IDC_BUTTON5, &net::OnBnClickedButton5)
ON_BN_CLICKED(IDC_BUTTON6, &net::OnBnClickedButton6)
ON_BN_CLICKED(IDC_BUTTON7, &net::OnBnClickedButton7)
END_MESSAGE_MAP()
void convtCStrToChar(char *nstringa,CString const & strParam)
{
	//char *ncharStr = new char[20]; 
	int i = 0;
	for (i = 0; i<wcslen(strParam); i++)
	{
		nstringa[i] = (char)strParam[i];
	}
	nstringa[i] = '\0';

}

CString ip;
CString text;
CString acmsg;
SOCKET s;
vector<SOCKET> client;
SOCKET clientAccept;//����ͨѶ��SOCKET
// net ��Ϣ����
void net::require(int dir,int id){
	char tt[4] = { 0 };
		tt[0] =  dir+'0';
		tt[1] = id+'0';
	
		// m.control[id]->SETDIR(direct);
	if(server){
		m.setdir(dir,id);
	}
	else{//�ͻ���
		sendmessage('4',tt);
	}

}
void net::select(char a, CString s){//������Ϣ
	int nn ;CString str;
	char dd[20]={0};
	convtCStrToChar(dd, s);
	switch (a-'0')
	{
	case 0:
	case 1: 
		this->GetDlgItemTextW(IDC_EDIT1, str);
		this->SetDlgItemTextW(IDC_EDIT1,str+s);
		break;
	case 2:
		if(!server) {
			this->MessageBox(L"case 2;wrong");return;}
		nn=m.login(dd); //�ͻ�������,���������ܴ��������ѽ������
		sendmessage('3',dd);
		//
		break;
	case 3:
		if(server) this->MessageBox(L"case 3error");
		nn=m.login(dd);
		if(dd==name) n=nn;//�ͻ�������
		return;
	case 4://�����id,�ͻ�������ķ���ı�����
		//if(!server)   this->MessageBox(L"case 4;wrong");
		//return;}
		m.setdir(((char)s[0] - '0'),((char)s[1] - '0'));
		break;
	case 5:
		if(server) this->MessageBox(L"case 5 error");
		m.leave(s[0] - '0');//�����˳�
		if(n==s[0]-'0')
			n=0;
		break;
	case 6:
		if(server) this->MessageBox(L"case 6 error");
		m.login("server");//��һ����Ϊ������
		::convtCStrToChar(dd,name);//�ͻ�������
		sendmessage('2',dd);//�������Ϳ�ʼ��Ϣ���ͻ�������ע����Ϣ
		return ;
	case 7:
		if(server) this->MessageBox(L"case 7 error");
		m.control[dd[0]-'0']->grow(1);//�䳤
		//m.go();
		break;
	case 8:
		if(server) this->MessageBox(L"case 8error");
		::setfood(CPoint(dd[0],dd[1]));
		break;//ʳ��
	case 9://�����ֱ�Ӳ���Ȩ��,���;������꣬id,x,y\0.
		if(server) this->MessageBox(L"case 9error");
		m.control[(char)s[0] - '0']->d_go( (char)s[1] - '0',(char)s[2] - '0');
		break;
	
	default:
		break;
	
}
}
UINT newclient(LPVOID p){
	SOCKET tem = clientAccept;
	while (!finish){
	//////////////////////////////////////////////////////////////////////////
	char recvBuf[256], sendBuf[256];
	int BytesRecv;
	memset(recvBuf, 0, 256);
	memset(sendBuf, 0, 256);
	BytesRecv = recv(tem, recvBuf, 256, 0);//��ȡ��Ϣ
	
	char command = recvBuf[0];
	char use[22]={0};
	memcpy(use, recvBuf + 1, 20); use[20] = '\0';
	CString w=(recvBuf+1);
	dlg.sendmessage('1',recvBuf);
	dlg.select(recvBuf[0],w);
	if (BytesRecv == SOCKET_ERROR)
	{
		//cout << "recv error" << endl;
		MessageBox(NULL, L"recv ERROR", L"ERROR", 0);
			client.clear();
		finish=1;
		break;
	}
	char naaa[20];
	/*convtCStrToChar(naaa, dlg.name+"coming \n");
	dlg.select('1', naaa);*/
	//cout << "�յ��ͻ��˷���������:" << recvBuf << endl;
	memcpy(sendBuf, recvBuf, BytesRecv);

	//strcat(sendBuf, "�յ�");

	int ret;
	for (int i = 0; i < client.size(); i++)
	{
		ret = send(client[i], sendBuf, strlen(sendBuf) + 1, 0);//���͸�ÿһ����
		
		if (ret == SOCKET_ERROR)
		{
			::MessageBox(NULL, L"send --ERROR", L"ERROR", 0); 
			
			client.clear();
			finish=1;
			break;
		}
		
	}
}
		CString str;
	dlg.GetDlgItemTextW(IDC_EDIT1,str);
		str+="�����˳��������ж�\n";
	dlg.SetDlgItemTextW(IDC_EDIT1,str);
	closesocket(s);
	WSACleanup();
	return 1;
}
UINT SERVER(LPVOID P){
	//����windows sockets��̬��
	//MAKEWORD(2,2)��ʾʹ��WINSOCK2�汾
	//.wsaData�����洢ϵͳ���صĹ���WINSOCK������.
	//cout << "��������127.0.0.1:6666�˿ڼ���..." << endl;
	finish=0;
		struct sockaddr_in clientaddr;
		int len = sizeof(clientaddr);
	while (1){
		if (finish) break;
		clientAccept = accept(s, (struct sockaddr*)&clientaddr, &len);
		if (clientAccept == INVALID_SOCKET){
			//cout << "accept error" << endl;
			::MessageBox(NULL, L"ACCEPT ERROR", L"ERROR", 0);
			break;
			//return;
		};//�ȴ�������������
		int h = 1;
		for (int i = 0; i < client.size(); i++){
			if (client[i] == clientAccept)
				h = 0;
		}
		if (h)
			client.push_back(clientAccept);
		//cout << "�ͻ������ӳɹ������ڿ�ʼ�շ�����..." << endl;
		::AfxBeginThread(newclient, 0);
		//cout << "��ͻ��˷������� " << sendBuf << "�ɹ�" << endl;
		//::MessageBox(NULL, (LPCWSTR)sendBuf, L"OK", 0);
	}
	//dlg.setitem();

	return 1;
}

void net::OnBnClickedButton2()//server
{
	only=0;
	this->GetDlgItemTextW(IDC_NAME, name);
	server = 1;
	//this->GetDlgItem(IDC_IPADDRESS1);
	this->GetDlgItemTextW(IDC_IPADDRESS1, ip);
	this->initserver();
	CWinThread *p = AfxBeginThread(SERVER,0);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
}//server
int net::initserver(){
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
		//cout << "WSAStartup error" << endl;
		::MessageBox(NULL, L"wsastartup ERROR", L"ERROR", 0);
	}
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//����������SOCKET s
	if (s == INVALID_SOCKET){
		//cout << "socket error" << endl;
		WSACleanup();
		//return;
	}//����һ�����׽��֣������׽��ֺ�s
	struct sockaddr_in addrServ;//sockaddr_in ����windows/linux����Ľṹ
	addrServ.sin_family = AF_INET;//ָ��Э���壬��socket�����ֻ����AF_INET
	addrServ.sin_port = htons(6666);//�洢�˿ںţ���linux�£��˿ںŵķ�Χ0~65535,ͬʱ0~1024��Χ�Ķ˿ں��Ѿ���ϵͳʹ�û�����

	char ipp[20];
	convtCStrToChar(ipp, ip);
	addrServ.sin_addr.S_un.S_addr = inet_addr(ipp);//sin_addr�洢IP��ַ


	int runcode;
	runcode = bind(s, (struct sockaddr*)&addrServ, sizeof(struct sockaddr_in));
	if (runcode == SOCKET_ERROR){
		//cout << "bind error" << endl;
		WSACleanup();
		//return;
	};//��������Э���塢��ַ���˿ں���һ�������socket -> s��


	runcode = listen(s, 2);
	if (runcode == SOCKET_ERROR){
		//cout << "listen error" << endl;
		::MessageBox(NULL, L"listen ERROR", L"ERROR", 0);
		WSACleanup();
		//return;
	};//�����׽���Ϊ�����������ӵ�״̬
	this->SetDlgItemTextW(IDC_EDIT1, CString("���ӽ���\n"));
	return 1;
}

UINT CLIENT(LPVOID P){	
	while (1){//��Ҫ����
		char recvBuf[256], sendBuf[256];
		int BytesSend;
		memset(recvBuf, 0, 256);
		memset(sendBuf, 0, 256);
		strcpy(sendBuf, "0");
		int ret;
		ret = recv(s, recvBuf, 256, 0);//����
		CString tt; tt=(recvBuf + 1);
		dlg.select(recvBuf[0], tt);//�ּ�
		if (ret == SOCKET_ERROR)
		{
			MessageBox(NULL,L"SOCKET_ERROR",L"as",0);
			break;
			//return 1;
		}

		//cout << "�յ�����������������:" << recvBuf << endl;
	}
	closesocket(s);
	WSACleanup();
	return 1;
}
void net::OnBnClickedConnect()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	only=0;
	this->GetDlgItemTextW(IDC_NAME, name);
	this->initclient();
	sendmessage('1', "hello");
	CWinThread *p = AfxBeginThread(CLIENT, 0);
}
int net::initclient(){
	WORD wVersionRequested;
	WSADATA wsaData;
	int  ret;
	server = 0;
	wVersionRequested = MAKEWORD(2, 2);
	ret = WSAStartup(wVersionRequested, &wsaData);
	if (ret != 0) {
		MessageBox( L"Winsockfail", L"as", 0);
		return 1;
	}//��ʼ��Winsock


	 s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET)
	{
		MessageBox( L"SOCKET fail", L"as", 0);
		return 1;
	}//�������ӵ���������SOCKET����

	char ipp[20];
	this->GetDlgItemTextW(IDC_IPADDRESS1,ip);
	convtCStrToChar(ipp, ip);
	struct sockaddr_in addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr(ipp);//��������ַ
	addrSrv.sin_family = AF_INET;//ָ��Э����
	addrSrv.sin_port = htons(6666);//�������˿ں�
	//���ַ��Ϣ


	int namelen = sizeof(struct sockaddr);

	ret = connect(s, (struct sockaddr*)&addrSrv, namelen);
	if (ret == SOCKET_ERROR)
	{
		MessageBox( L"connect fail", L"as", 0);
		return 1;
	}
	char ss[200]={0};
	::convtCStrToChar(ss,name+" coming!\n \0");
	sendmessage('1',ss);

return 1;
}

BOOL net::OnInitDialog()
{
	srand(time(NULL));
	CDialogEx::OnInitDialog();
	ip = "127.0.0.1";
	char s[10]="new";s[3]=('0'+rand()%20);
	CString ee=s;
	
	this->SetDlgItemTextW(IDC_IPADDRESS1, ip);
	this->SetDlgItemTextW(IDC_NAME, ee);
	this->GetDlgItemTextW(IDC_NAME, name);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
int net::sendmessage(char a, char *c){
	//if(a=='t') return ;
	char msg[250] = { 0 };
	strcpy(msg + 1, c);
	msg[0] = a;
	if(s)
	if(!(a==4&&n==0))
	if (server){
		int BytesSend;
		char t[3]={0};t[1]=2+'0';
		for (int i = 0; i < client.size(); i++){//����
			if(a=='6'){//����'6'����������������ֱ�Ӹ�����
				t[0]='6';t[1]++;
				BytesSend = send(client[i], t, 4, 0);}
			else{
			BytesSend = send(client[i], msg, strlen(msg) + 1, 0);//���Ͳ���
			}
		if (BytesSend == SOCKET_ERROR)
		{
			MessageBox(L"send fail-server", L"as", 0);
			client.erase(client.begin(),client.begin()+1);
			return 1;
		}
		}
	}
	else{

		int BytesSend;
		BytesSend = send(s, msg, strlen(msg) + 1, 0);//���Ͳ���
		if (BytesSend == SOCKET_ERROR)//�ͻ���
		{
			//MessageBox(L"send fail-client", L"as", 0);
			closesocket(s);s=0;
			WSACleanup();
			return 1;
		}
	}
	
	return 1;
}


void net::OnBnClickedButton3()
{
	only=0;
	CString text;
	this->GetDlgItemTextW(IDC_EDIT2, text);
	text ;
	char ff[20];
	convtCStrToChar(ff, text);
	sendmessage('1', ff);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void net::OnIdok()
{
	// TODO:  �ڴ���������������
}


void net::OnIdcancel()
{
	// TODO:  �ڴ���������������
	this->DestroyWindow();
}


void net::OnBnClickedButton4()//��ʼ��ť
{
	only=0;
	//m.login()
	char ss[200]={0};
	::convtCStrToChar(ss,name);
	n=m.login(ss);
	::Sleep(20);
	sendmessage('6', "go");
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
/*
�ַ���һ����ʾ���
0�����ԣ�������
1��������Ϣ
2��������ң��������������
3�����ص�ID��������
4����ҵĲ�������������ID,
5���˳�
*/

void net::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	only=1;
	onstart=1;
}


void net::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	only=1;
	two=1;
}


void net::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	addai=1;
}
