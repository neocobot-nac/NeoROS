/*****************************************************************************
*  Neocobot OdinClient library
*  Copyright (C) 2019 Huang Shaojie  shaojie@neocobot.com
*
*  @file     receiver.h
*  @brief    ��Ϣ�����߳�ģ��
*
*  @detail   ��������Ϣ����ģ��Ĺ���
*			 1.���շ�������Ϣ��ת��Ϊ�ɶ�����
*			 2.�ṩ���¼��ص���ע��
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
#ifndef _RECEIVER_H
#define _RECEIVER_H

#ifdef _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS 0
#include <Ws2tcpip.h>
#include <Winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <algorithm>
#include <sstream>
#endif

#include "argdefine.h"
#include "thread.h"
#include "tasks.h"
#include "safemap.h"
#include "parser.h"
#include "logger.h"

#define BUFLEN 1024

/*
@brief ��Ϣ�����߳�ģ��
*/
class Receiver : public Neothread::NeoThread
{
private:
	/* �����¼� */
	RobotEvent										_receiverEvent;

	/* ����ģ�����־��������־ */
	bool											_isRunning;
	bool											_isLoad;

	/* socket��ض��� */
	SOCKET											_socket;
	char											_buf[BUFLEN];
	string											_buffer;

	/* ��Ϣ����ģ�� */
	Parser											_parser;

	/* ������Ϣ��map���� */
	threadsafe_map<string, map<string, string> >	_recvMap;

	/* �ص�����ʵ�� */
	RobotEventCallback								_eventCallback;

private:
	/*
	@brief ��Ϣ���ɺ���,��������buffer�н��յ����ַ�,�����ɿɶ���Ϣ
	@return RobotEvent �¼�
	*/
	RobotEvent	_GenerateMsg(string &msg);

	/*
	@brief �¼��ص�����
	*/
	void		_eventCall();

public:
	Receiver();
	~Receiver();

	/*
	@brief �ص�����ע��
	@param RobotEventCallback eventCallback �ص�����
	*/
	void		RobotEventRegister(RobotEventCallback eventCallback);

	/*
	@brief ͨ������������Ϣ�����ж�Ӧ����Ϣ
	@param string				index	��Ϣ����
	@param map<string, string>	&data	��ȡ������Ϣ
	@return RobotEvent �¼�
	*/
	RobotEvent	GetRecv(string index, map<string, string> &data);

	/*
	@brief ���Ѿ����ӵ�socket��½����Ϣ����ģ��,��ʼ����
	*/
	void		Load(SOCKET &socket);

	/*
	@brief socket�ǳ�,ֹͣ����
	*/
	void		Unload();

	/*
	@brief ����ģ���̺߳���
	*/
	void		Stop();

	/*
	@brief ֹͣ�߳�
	*/
	void		Run();

};


#endif

