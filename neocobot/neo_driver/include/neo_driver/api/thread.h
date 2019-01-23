/*****************************************************************************
*  Neocobot OdinClient library
*  Copyright (C) 2019 Huang Shaojie  shaojie@neocobot.com
*
*  @file     thread.h
*  @brief    �߳�ģ��
*
*  @detail   �����˻����߳�ģ���ʵ��
*			 1.�̵߳�����ֹͣʵ��
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
#ifndef _THREAD_H_
#define _THREAD_H_

#ifdef _WIN32
#include <Windows.h>
#else
#include <pthread.h>
#include <semaphore.h>
#endif

/* �߳������ռ䶨�� */
#ifndef _NEOTHREAD_BEGIN
#define _NEOTHREAD_BEGIN namespace Neothread {
#endif

#ifndef NEOCOBOT_THREAD
#define NEOCOBOT_THREAD Neothread
#endif

#ifndef _NEOTHREAD_END
#define _NEOTHREAD_END }
#endif

_NEOTHREAD_BEGIN

/*
@brief �߳����װ
ͨ���̳и��ಢ��дRun()��������ʹ��
Start���ý�����һ���߳�ȥִ��Run����.
Wait���ý�������ǰ�������߳�ֱ��CThread�߳��˳�.
Terminate���ý�ǿ����ֹCThread�߳�, �ĵ���Ӧ����!
*/
class NeoThread
{
public:
	NeoThread();
	virtual ~NeoThread();

public:
	bool Start();
	virtual void Run() = 0;
	bool Join();
	bool Detach();
	bool Terminate();

	//��ͨ���Է���ֵǿ��ת��Ϊwindows�µ�handle
	inline unsigned long long GetThread() { return m_hThread; };
private:
	unsigned long long m_hThread;
};

_NEOTHREAD_END

#endif  // _THREAD_H_
