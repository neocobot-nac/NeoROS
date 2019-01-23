/*****************************************************************************
*  Neocobot OdinClient library
*  Copyright (C) 2019 Huang Shaojie  shaojie@neocobot.com
*
*  @file     client.h
*  @brief    socket����ģ��ͷ�ļ�
*
*  @detail   Ŀǰ�汾��ͷ�ļ�������socket����ģ��
*			 1.����socket�Ŀ����͹ر�
*            2.ά�����ܺͷ����߳�
*            3.ά��������
*            4.����ײ��¼�
*
*  @author   Huang Shaojie
*  @email    shaojie@neocobot.com
*  @version  0.2.0
*  @date     2019/01/17
*
*----------------------------------------------------------------------------
*  Change History :
*  <Date>     | <Version> | <Author>       | <Description>
*----------------------------------------------------------------------------
*  2019/01/17 | 0.2.0     | Huang Shaojie  | ���鲢���幦��
*----------------------------------------------------------------------------
*****************************************************************************/
#ifndef _CLIENT_H
#define _CLIENT_H

#ifdef _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS 0
#include <Ws2tcpip.h>
#include <Winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <string>
#else
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <algorithm>
#include <sstream>
#endif

#include "argdefine.h"
#include "sender.h"
#include "receiver.h"
#include "heart.h"
#include "logger.h"

/*
@brief socket����ģ��
*/
class Client
{
private:
	/* socket�������� */
#ifdef _WIN32
	WSADATA					_wsa;
#else
	;
#endif

	struct sockaddr_in		_socketAddr;
	SOCKET					_socket;

	/* �¼���¼ */
	RobotEvent				_clientEvent;

	/* ����ϵͳ��Ϣ��¼ */
	LocalSystemInfo			_localSystemInfo;

	/* �Ƿ��½��־ */
	bool					_isLogin;

	/* ����,����,�������߳�ģ��ʵ���� */
	Receiver	receiver;
	Sender		sender;
	Heart		heart;

private:
	/* �¼��ص��������������ص����� */
	static void _eventCallback(RobotEvent event);
	static void _heartCallback();

	/*
	@brief ���ر���ϵͳ��Ϣ
	@return RobotEvent �����¼�
	*/
	RobotEvent _loadLocalSystemInfo();

public:
	/* ��ָ��,ʹ�ص���������ʹ�����Ա���������� */
	static Client* pOdinClientCallback;

public:
	Client();
	~Client();

	/*
	@brief �������
	@param Tasks task ����
	@return RobotEvent �����¼�
	*/
	RobotEvent		AddTasks(Tasks task);

	/*
	@brief ���ر���ϵͳ��Ϣ
	@param string				name	��Ҫ��ȡ����Ϣ����
	@param map<string, string>	&data	��Ҫ���Ķ�Ӧ����
	@return RobotEvent �����¼�
	*/
	RobotEvent		GetResult(string name, map<string, string> &data);

	/*
	@brief ��ʼ��socket����
	@param const char*	ServerIp	���ӵķ�����ip
	@param short int	ServerPort	���ӵķ������˿�
	@return RobotEvent �����¼�
	*/
	RobotEvent		InitializeSocket(const char* ServerIp, short int ServerPort);

	/*
	@brief �Ͽ�socket����
	@return RobotEvent �����¼�
	*/
	RobotEvent		FinalizeSocket();

	/*
	@brief ��ȡ����ip
	@param string &ip ��ȡ����ip
	*/
	void			GetClientIP(string &ip);

	/*
	@brief ��ȡ����ϵͳ��Ϣ
	@return LocalSystemInfo ���ر���ϵͳ��Ϣ
	*/
	LocalSystemInfo	GetLocalSystemInfo();
};

#endif
