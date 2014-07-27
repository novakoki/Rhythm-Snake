// net.cpp : 实现文件
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
#include"NetSnake.h"//直接控制的蛇，由客户机创建，被主机管理
int finish = 0;
char name[20][100];
int user[10];
int only=1;
CString severname;
// net 对话框
/*
字符第一个表示命令：
0：忽略，无内容
1：文字消息
2：加入玩家，后面是玩家名字
3：返回的ID，和名字
4：玩家的操作，包括ID,和按键
5：退出
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
	this->SetDlgItemTextW(IDC_EDIT3,L"当前分数：");
	this->SetDlgItemTextW(IDC_EDIT4,L"IP地址：");
	this->SetDlgItemTextW(IDC_EDIT5,L"消息列表：");
	this->SetDlgItemTextW(IDC_EDIT7,L"加速提示：");
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
SOCKET clientAccept;//创建通讯的SOCKET
// net 消息处理
void net::require(int dir,int id){
	char tt[4] = { 0 };
		tt[0] =  dir+'0';
		tt[1] = id+'0';
	
		// m.control[id]->SETDIR(direct);
	if(server){
		m.setdir(dir,id);
	}
	else{//客户机
		sendmessage('4',tt);
	}

}
void net::select(char a, CString s){//接受消息
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
		nn=m.login(dd); //客户机发出,由主机接受创建，并把结果发送
		sendmessage('3',dd);
		//
		break;
	case 3:
		if(server) this->MessageBox(L"case 3error");
		nn=m.login(dd);
		if(dd==name) n=nn;//客户机接受
		return;
	case 4://方向加id,客户机提出的方向改变请求
		//if(!server)   this->MessageBox(L"case 4;wrong");
		//return;}
		m.setdir(((char)s[0] - '0'),((char)s[1] - '0'));
		break;
	case 5:
		if(server) this->MessageBox(L"case 5 error");
		m.leave(s[0] - '0');//有人退出
		if(n==s[0]-'0')
			n=0;
		break;
	case 6:
		if(server) this->MessageBox(L"case 6 error");
		m.login("server");//第一个，为主机的
		::convtCStrToChar(dd,name);//客户机接受
		sendmessage('2',dd);//主机发送开始信息，客户机发送注册信息
		return ;
	case 7:
		if(server) this->MessageBox(L"case 7 error");
		m.control[dd[0]-'0']->grow(1);//变长
		//m.go();
		break;
	case 8:
		if(server) this->MessageBox(L"case 8error");
		::setfood(CPoint(dd[0],dd[1]));
		break;//食物
	case 9://方向的直接操作权利,传送绝对坐标，id,x,y\0.
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
	BytesRecv = recv(tem, recvBuf, 256, 0);//获取信息
	
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
	//cout << "收到客户端发来的数据:" << recvBuf << endl;
	memcpy(sendBuf, recvBuf, BytesRecv);

	//strcat(sendBuf, "收到");

	int ret;
	for (int i = 0; i < client.size(); i++)
	{
		ret = send(client[i], sendBuf, strlen(sendBuf) + 1, 0);//发送给每一个人
		
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
		str+="有人退出，连接中断\n";
	dlg.SetDlgItemTextW(IDC_EDIT1,str);
	closesocket(s);
	WSACleanup();
	return 1;
}
UINT SERVER(LPVOID P){
	//加载windows sockets动态库
	//MAKEWORD(2,2)表示使用WINSOCK2版本
	//.wsaData用来存储系统传回的关于WINSOCK的资料.
	//cout << "服务器在127.0.0.1:6666端口监听..." << endl;
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
		};//等待就受连接请求
		int h = 1;
		for (int i = 0; i < client.size(); i++){
			if (client[i] == clientAccept)
				h = 0;
		}
		if (h)
			client.push_back(clientAccept);
		//cout << "客户端连接成功，现在开始收发数据..." << endl;
		::AfxBeginThread(newclient, 0);
		//cout << "向客户端发送数据 " << sendBuf << "成功" << endl;
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
	// TODO:  在此添加控件通知处理程序代码
	
}//server
int net::initserver(){
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
		//cout << "WSAStartup error" << endl;
		::MessageBox(NULL, L"wsastartup ERROR", L"ERROR", 0);
	}
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//创建监听的SOCKET s
	if (s == INVALID_SOCKET){
		//cout << "socket error" << endl;
		WSACleanup();
		//return;
	}//创建一个流套接字，返回套接字号s
	struct sockaddr_in addrServ;//sockaddr_in 是在windows/linux下面的结构
	addrServ.sin_family = AF_INET;//指代协议族，在socket编程中只能是AF_INET
	addrServ.sin_port = htons(6666);//存储端口号，在linux下，端口号的范围0~65535,同时0~1024范围的端口号已经被系统使用或保留。

	char ipp[20];
	convtCStrToChar(ipp, ip);
	addrServ.sin_addr.S_un.S_addr = inet_addr(ipp);//sin_addr存储IP地址


	int runcode;
	runcode = bind(s, (struct sockaddr*)&addrServ, sizeof(struct sockaddr_in));
	if (runcode == SOCKET_ERROR){
		//cout << "bind error" << endl;
		WSACleanup();
		//return;
	};//将服务器协议族、地址、端口号与一个定义的socket -> s绑定


	runcode = listen(s, 2);
	if (runcode == SOCKET_ERROR){
		//cout << "listen error" << endl;
		::MessageBox(NULL, L"listen ERROR", L"ERROR", 0);
		WSACleanup();
		//return;
	};//设置套接字为监听接入连接的状态
	this->SetDlgItemTextW(IDC_EDIT1, CString("连接建立\n"));
	return 1;
}

UINT CLIENT(LPVOID P){	
	while (1){//主要部分
		char recvBuf[256], sendBuf[256];
		int BytesSend;
		memset(recvBuf, 0, 256);
		memset(sendBuf, 0, 256);
		strcpy(sendBuf, "0");
		int ret;
		ret = recv(s, recvBuf, 256, 0);//接受
		CString tt; tt=(recvBuf + 1);
		dlg.select(recvBuf[0], tt);//分拣
		if (ret == SOCKET_ERROR)
		{
			MessageBox(NULL,L"SOCKET_ERROR",L"as",0);
			break;
			//return 1;
		}

		//cout << "收到服务器发来的数据:" << recvBuf << endl;
	}
	closesocket(s);
	WSACleanup();
	return 1;
}
void net::OnBnClickedConnect()
{
	// TODO:  在此添加控件通知处理程序代码
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
	}//初始化Winsock


	 s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET)
	{
		MessageBox( L"SOCKET fail", L"as", 0);
		return 1;
	}//创建连接到服务器的SOCKET对象

	char ipp[20];
	this->GetDlgItemTextW(IDC_IPADDRESS1,ip);
	convtCStrToChar(ipp, ip);
	struct sockaddr_in addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr(ipp);//服务器地址
	addrSrv.sin_family = AF_INET;//指代协议族
	addrSrv.sin_port = htons(6666);//服务器端口号
	//搭建地址信息


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

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
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
		for (int i = 0; i < client.size(); i++){//主机
			if(a=='6'){//除了'6'其他部分主机都是直接给别人
				t[0]='6';t[1]++;
				BytesSend = send(client[i], t, 4, 0);}
			else{
			BytesSend = send(client[i], msg, strlen(msg) + 1, 0);//发送部分
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
		BytesSend = send(s, msg, strlen(msg) + 1, 0);//发送部分
		if (BytesSend == SOCKET_ERROR)//客户机
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
	// TODO:  在此添加控件通知处理程序代码
}


void net::OnIdok()
{
	// TODO:  在此添加命令处理程序代码
}


void net::OnIdcancel()
{
	// TODO:  在此添加命令处理程序代码
	this->DestroyWindow();
}


void net::OnBnClickedButton4()//开始按钮
{
	only=0;
	//m.login()
	char ss[200]={0};
	::convtCStrToChar(ss,name);
	n=m.login(ss);
	::Sleep(20);
	sendmessage('6', "go");
	// TODO:  在此添加控件通知处理程序代码
}
/*
字符第一个表示命令：
0：忽略，无内容
1：文字消息
2：加入玩家，后面是玩家名字
3：返回的ID，和名字
4：玩家的操作，包括按键ID,
5：退出
*/

void net::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	only=1;
	onstart=1;
}


void net::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	only=1;
	two=1;
}


void net::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	addai=1;
}
