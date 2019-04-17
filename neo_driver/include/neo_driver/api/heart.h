/*****************************************************************************
*  Neocobot OdinClient library
*  Copyright (C) 2019 Huang Shaojie  shaojie@neocobot.com
*
*  @file     heart.h
*  @brief    ������ͷ�ļ�
*
*  @detail   �������������ļ�����, 10sһ������
*			 ������
*			 1.�������̵߳�������ֹͣ
*			 2.����������,ͨ���ص���������������

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
#ifndef _HEART_H
#define _HEART_H

#include <time.h>
#include "argdefine.h"
#include "thread.h"
#include "parser.h"
#include "logger.h"

/* �������ص��������Ͷ��� */
typedef void(*HeartEventCallback) (void);

/*
@brief �������߳���
*/
class Heart : public Neothread::NeoThread
{
private:
	/* ����������־ */
	bool						_isRunning;
	bool						_isEnable;

	/* �������� */
	time_t						_startTime;
	time_t						_stopTime;
	double						_durationTime;

	/* �ص�����ʵ�� */
	HeartEventCallback			_heartCallback;

private:
	/*
	@brief �¼��ص�����
	*/
	void _eventCall();

public:
	Heart();
	~Heart();

	/*
	@brief �ص�����ע��
	@param HeartEventCallback eventCallback �ص�����
	*/
	void HeartEventRegister(HeartEventCallback eventCallback);

	/*
	@brief ������ʹ��
	*/
	void Enable();

	/*
	@brief ������ʧ��
	*/
	void Disable();

	/*
	@brief �������̺߳���
	*/
	void Run();

	/*
	@brief ֹͣ�߳�
	*/
	void Stop();
};


#endif
