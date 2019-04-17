/*****************************************************************************
*  Neocobot OdinClient library
*  Copyright (C) 2019 Huang Shaojie  shaojie@neocobot.com
*
*  @file     neoclient.h
*  @brief    NeoClientȫ�ֶ��弰ϵͳ���ò���
*
*  @detail   Ŀǰ�汾��ͷ�ļ�������NeoClient��������
*            1.�ڲ��¼����󼰶�Ӧ�������
*            2.�����ռ�����
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
#ifndef _NEOCLIENT_H
#define _NEOCLIENT_H

/* NeoClient�����ռ䶨�� */
#ifndef _NEOCLIENT_BEGIN
#define _NEOCLIENT_BEGIN namespace NeoClient {
#endif

#ifndef NEOCLIENT
#define NEOCLIENT NeoClient
#endif

#ifndef _NEOCLIENT_END
#define _NEOCLIENT_END }
#endif

/*
@brief ��е���¼�����,������Ӧ������
*/
typedef enum Robot_Event
{
	RobotEvent_Succeed						= 0,			// �޴���

	// Client
	RobotEvent_SendError					= 1001011,		// ���ʹ���

	RobotEvent_RecvError					= 1002011,		// ���մ���
	RobotEvent_GetRecvError					= 1002021,		// ��ȡ���մ���

	RobotEvent_GenerateFailed				= 1003011,		// ������Ϣ����
	RobotEvent_UnwrapFailed					= 1003021,		// ��Ϣ�������
	RobotEvent_RecvTimeout					= 1003031,		// ���ճ�ʱ����

	RobotEvent_InitSocketError				= 1004011,		// socket��ʼ������
	RobotEvent_SocketConnectError			= 1004021,		// socket���Ӵ���

	RobotEvent_ConfigError					= 1005011,		// �������ô���

	// Server
	RobotEvent_FunctionNotFound				= 1001010,		// �޷��ҵ���Ӧ����
	RobotEvent_Version_Mismatch				= 1002010,		// �汾��ƥ��
	RobotEvent_UnexpectedArgs				= 1003010,		// ������ƥ��
	RobotEvent_RobotNotInit					= 1004010,		// ��е��δ��ʼ��
	RobotEvent_RobotAlreadyInit				= 1004020,		// ��е���Ѿ���ʼ��
	RobotEvent_RobotError					= 1004030,		// ��е�۹���ִ�д���

	RobotEvent_NonstandradRegisterParams	= 2001010,		// ע���������׼
	RobotEvent_RegisterError				= 2001020,		// ע�᲻�ɹ�
	RobotEvent_NotRegister					= 2002010,		// δע��
	RobotEvent_NonstandradInfoParams		= 2002020,		// ���Ӳ�������׼
	RobotEvent_NotConnected					= 2003010,		// ����ʧ��

	RobotEvent_ConnLackHead					= 3001010,		// ������Ϣȱ����Ϣͷ
	RobotEvent_HeadLackIdentifier			= 3001020,		// ������Ϣȱ����ݱ�ǩ
	RobotEvent_IdentifierNotMatch			= 3001030,		// ��ݱ�ǩ��ƥ��
	RobotEvent_IdentifierNotFound			= 3001040,		// ��ݱ�ǩȱʧ
	RobotEvent_ConnLackTail					= 3001050,		// ������Ϣȱ����Ϣβ
	RobotEvent_CtoSLackHead					= 3001060,		// ������Ϣȱ����Ϣͷ
	RobotEvent_HeadLackElement				= 3001070,		// ��Ϣͷȱ��Ԫ��
	RobotEvent_CtoSLackFunction				= 3001080,		// ������Ϣȱ�������ǩ
	RobotEvent_FunctionLackName				= 3001090,		// �����ǩȱ����������
	RobotEvent_FunctionLackParams			= 3001100,		// �����ǩȱ���������
	RobotEvent_CtoSLackTail					= 3001110,		// ������Ϣȱ����Ϣβ
	RobotEvent_ConnCheckSumFailed			= 3002010,		// ������Ϣ��У��ʧ��
	RobotEvent_CtoSCheckSumFailed			= 3002020,		// ������Ϣ��У��ʧ��
	RobotEvent_UncognizedTask				= 3002020,		// �޷�ʶ�������

	RobotEvent_SocketTimeout				= 4001010,		//ͨѶ��ʱ

}RobotEvent;


#endif

