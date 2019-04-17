/*****************************************************************************
*  Neocobot OdinClient library
*  Copyright (C) 2019 Huang Shaojie  shaojie@neocobot.com
*
*  @file     argdefine.h
*  @brief    ���ö��弰����
*
*  @detail   ������Ŀǰʹ�õ������������Լ��ļ�·��Դ
*			 ������
*			 1.�˶�ģʽ�Ķ���
*			 2.���������ļ�(����ģʽ��
*			 3.Ԥ������δ���汾�п��ܳ��ֵ��˶�·�������������
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
#ifndef _ARGDEFINE_H
#define _ARGDEFINE_H

#include "tools.h"
#include "neoclient.h"

/* ·���ָ������ */
#if defined(WINDOWS) || defined(_WIN32)
#define PATH_OPERATOR "\\"
#else
#define PATH_OPERATOR "/"
#endif

/* ·�����ƶ��� */
#define PROPERTIES_FILE		"NeoClientResource.properties"
#define NEOCLIENT_PATH		"NeoClient"
#define LOG_PATH			            "log"
#define REPOSITORY_PATH		"repository"

/* ·�����Ͷ��� */
typedef unsigned int DirName;

/* �������Ͷ��� */
#if defined(WINDOWS) || defined(_WIN32)
;
#else
#define SOCKET_ERROR -1
typedef int SOCKET;
#endif

/* �ص��������Ͷ��� */
typedef void(*RobotEventCallback) (RobotEvent);

/*
@brief ����������Ϣ����ʱ���ṩ���ģ�
*/
typedef struct Setup_Param
{
	const char* channel_name = "/dev/pcanusb32";
	const char* channel_type = "PEAK_SYS_PCAN_USB";
	const char* protocol = "TMLCAN";
	int host_id = 10;
	int baud_rate = 500000;

}SetupParam;

/*
@brief ��е������ģʽ
SetupMode_RealMode��ʾ��ʵ����
SetupMode_VirtualMode��ʾ��������
*/
typedef enum Setup_Mode
{
	SetupMode_RealMode		= 0,
	SetupMode_VirtualMode	= 1

}SetupMode;

/*
@brief ��е���˶�ģʽ
RelativeMode_Absolute��ʾ����λ���˶�
RelativeMode_Relative��ʾ���λ���˶�
*/
typedef enum Relative_Mode
{
	RelativeMode_Absolute = 0,
	RelativeMode_Relative = 1

}RelativeMode;

/*
@brief ��е��·���ջ�ģʽ
TrajCloseMode_Closed��ʾ·���ջ�
TrajCloseMode_Open��ʾ·������
*/
typedef enum Traj_Close_Mode
{
	TrajCloseMode_Closed	= 0,
	TrajCloseMode_Open		= 1

}TrajCloseMode;

/*
@brief ����ϵͳ��Ϣ����
*/
typedef struct Local_System_Info
{
	const char* version;
	const char* system;
	const char* language;
}LocalSystemInfo;

/*
@brief ��е��ϵͳ��Ϣ����
*/
typedef struct Robot_System_Info
{
	const char* version;
	const char* system;
	const char* language;
}RobotSystemInfo;

/*
@brief ��е��ĩ��λ�ö���
*/
typedef struct _Position
{
	double x;
	double y;
	double z;

}Position;

/*
@brief ��е��ĩ����̬����
*/
typedef struct _Orientation
{
	double Rx;
	double Ry;
	double Rz;

}Orientation;

/*
@brief ��е��ĩ��λ�˶���
*/
typedef struct _Pose
{
	Position position;
	Orientation orientation;

}Pose;

/*
@brief ��е���ļ�·��Դ����
*/
class NeoResource
{
public:
	bool isSetup = false;

	string _userPath;
	string _neoclientPath;
	string _logPath;
	string _repositoryPath;

	const static DirName USER_DIR = 0x0001U;
	const static DirName NEOCLIENT_DIR = 0x0002U;
	const static DirName LOG_DIR = 0x0003U;
	const static DirName REPOSITORY_DIR = 0x0004U;

public:
	NeoResource() {};
	~NeoResource() {};

	void operator=(NeoResource const&) = delete;
	NeoResource(NeoResource const&) = delete;

	/*
	@brief ���ʵ��
	*/
	static NeoResource& GetInstance()
	{
		static NeoResource _instance;
		return _instance;
	}

	/*
	@brief ����·��,���ض����ļ���·��Ĭ�����û�·����
	@return RobotEvent �����¼�
	*/
	static RobotEvent Load()
	{
		NeoResource& _resource = GetInstance();

#if defined(WINDOWS) || defined(_WIN32)
		_resource._userPath = std::getenv("USERPROFILE");
#else
        _resource._userPath = std::getenv("HOME");
#endif
		/* �����ض����ļ� */
		RobotEvent ret_properties;
		NeoProperties _properties;
		ret_properties = _properties.open(PROPERTIES_FILE);
		if (RobotEvent_Succeed == ret_properties)
			_properties.load();

		/* ��ȡ·�� */
		RobotEvent ret_createDir;
		ret_createDir = RobotEvent_Succeed == ret_properties ? _properties.read("NEOCLIENT_PATH", &_resource._neoclientPath) : RobotEvent_ConfigError;
		if (RobotEvent_ConfigError == ret_createDir)
			_resource._neoclientPath = _resource._userPath + PATH_OPERATOR + NEOCLIENT_PATH;

		ret_createDir = createDirectory(_resource._neoclientPath);
		if (RobotEvent_Succeed != ret_createDir)
		{
			_properties.close();
			return ret_createDir;
		}

		ret_createDir = RobotEvent_Succeed == ret_properties ? _properties.read("LOG_PATH", &_resource._logPath) : RobotEvent_ConfigError;
		if (RobotEvent_ConfigError == ret_createDir)
			_resource._logPath = _resource._neoclientPath + PATH_OPERATOR + LOG_PATH;

		ret_createDir = createDirectory(_resource._logPath);
		if (RobotEvent_Succeed != ret_createDir)
		{
			_properties.close();
			return ret_createDir;
		}

		ret_createDir = RobotEvent_Succeed == ret_properties ? _properties.read("REPOSITORY_PATH", &_resource._repositoryPath) : RobotEvent_ConfigError;
		if (RobotEvent_ConfigError == ret_createDir)
			_resource._repositoryPath = _resource._neoclientPath + PATH_OPERATOR + REPOSITORY_PATH;

		ret_createDir = createDirectory(_resource._repositoryPath);
		if (RobotEvent_Succeed != ret_createDir)
		{
			_properties.close();
			return ret_createDir;
		}

		_resource.isSetup = true;
		return RobotEvent_Succeed;
	}

	/*
	@brief ��ȡ·��
	@param DirName name ·����Ӧ����
	@param string* path	����·��ֵ
	@return RobotEvent ��ȡ�¼�
	*/
	static RobotEvent Get(DirName name, string* path)
	{
		NeoResource& _resource = GetInstance();

		switch (name)
		{
		case NeoResource::USER_DIR:
			*path = _resource._userPath;
			break;
		case NeoResource::NEOCLIENT_DIR:
			*path = _resource._neoclientPath;
			break;
		case NeoResource::LOG_DIR:
			*path = _resource._logPath;
			break;
		case NeoResource::REPOSITORY_DIR:
			*path = _resource._repositoryPath;
			break;
		default:
			return RobotEvent_ConfigError;
		}

		return RobotEvent_Succeed;
	}
};

#endif
