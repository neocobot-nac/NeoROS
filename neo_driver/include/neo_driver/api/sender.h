/*****************************************************************************
*  Neocobot OdinClient library
*  Copyright (C) 2019 Huang Shaojie  shaojie@neocobot.com
*
*  @file     sender.h
*  @brief    ��Ϣ�����߳�ģ��
*
*  @detail   ��������Ϣ����ģ��Ĺ���
*			 1.������ת��Ϊ��Ϣ���͸�������
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
#ifndef _SENDER_H
#define _SENDER_H

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
#include "safequeue.h"
#include "parser.h"
#include "logger.h"

/*
@brief ��Ϣ�����߳�ģ��
*/
class Sender : public Neothread::NeoThread
{
private:
	/* �����¼� */
	RobotEvent					_senderEvent;

	/* ����ģ�����־��������־ */
	bool						_isRunning;
	bool						_isLoad;

	/* socket��ض��� */
	SOCKET						_socket;

	/* ������ģ�� */
	Parser						_parser;

	/* ������� */
	threadsafe_queue<Tasks>		_tasksQueue;

	/* �ص�����ʵ�� */
	RobotEventCallback			_eventCallback;

private:
	/*
	@brief �¼��ص�����
	*/
	void _eventCall();

public:
	Sender();
	~Sender();

	/*
	@brief �ص�����ע��
	@param RobotEventCallback eventCallback �ص�����
	*/
	void RobotEventRegister(RobotEventCallback eventCallback);

	/*
	@brief ���Ѿ����ӵ�socket��½����Ϣ����ģ��,��ʼ����
	*/
	void Load(SOCKET &socket);

	/*
	@brief socket�ǳ�,ֹͣ����
	*/
	void Unload();

	/*
	@brief ��������ӵ����������
	@param Tasks task ����
	*/
	void AddTask(Tasks task);

	/*
	@brief ֹͣ�߳�
	*/
	void Run();

	/*
	@brief ����ģ���̺߳���
	*/
	void Stop();
};


#endif
