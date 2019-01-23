/*****************************************************************************
*  Neocobot OdinClient library
*  Copyright (C) 2019 Huang Shaojie  shaojie@neocobot.com
*
*  @file     tools.h
*  @brief    ���ù��ߺ�������
*
*  @detail   ������Ŀǰʹ�õ��Ĺ��ߺ����򹤾���
*			 ������
*			 1.��Ϣ�ļ���ʱ���,������������Ϣ
*			 2.timesleep����
*			 3.���ַ�������Ϊ��е���¼�
*			 4.�ļ��еĴ���
*			 5.�ض����ļ��ļ�����
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
#ifndef _TOOLS_H
#define _TOOLS_H

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#include <direct.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#endif

#include <algorithm>
#include <stdint.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>

#include "neoclient.h"

using std::string;
using std::vector;
using std::multimap;
using std::ifstream;
using std::ptr_fun;
using std::not1;

/* ��ƽ̨�ļ���ȡ�ʹ������� */
#if defined(WINDOWS) || defined(_WIN32)
#define ACCESS(fileName,accessMode) _access(fileName,accessMode)
#define MKDIR(path) _mkdir(path)
#else
#define ACCESS(fileName,accessMode) access(fileName,accessMode)
#define MKDIR(path) mkdir(path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#endif

/* ���·�����ȶ��� */
#define MAX_PATH_LEN	256

/* ���ʱ��� */
#define MAX_STAMP		10240

/*
@brief ��ȡʱ���
@return int ����ʱ���
*/
int	GetTimeStamp();

/*
@brief ���ߺ���
@param double sec ��Ҫ���ߵ��¼�,��λΪ��
*/
void TimeSleep(double sec);

/*
@brief �ַ����ָ�
@param string result ����Ľ���ַ���
@return RobotEvent ��Ӧ���¼�
*/
RobotEvent GetRobotEvent(string result);

/*
@brief ����Ŀ¼
@param const string &directoryPath ��Ҫ������·��
@return RobotEvent �¼�
*/
RobotEvent createDirectory(const string &directoryPath);

/*
@brief �ض����ļ�����
*/
class NeoProperties
{
private:
	string						path;
	vector<string>				vLine;
	multimap<string, string>	msKV;
	bool						mulremark = false;

private:
	/*
	@brief ȥ������ո�
	@param string &s ��Ҫȥ���ո���ַ���
	*/
	void trim(string &str);

public:
	NeoProperties() {};
	virtual ~NeoProperties() {};

	/*
	@brief ���ض����ļ�
	@param const char* path �ļ�Ŀ¼
	@return RobotEvent �¼�
	*/
	RobotEvent open(const char* path);

	/*
	@brief ��������
	@return RobotEvent �¼�
	*/
	RobotEvent load();

	/*
	@brief �ر��ļ�
	*/
	void close();

	/*
	@brief ����·���ؼ��ּ���·��
	@param const char	*k		�ؼ���
	@param string*		path	·��
	@return RobotEvent �¼�
	*/
	RobotEvent read(const char *k, string* path);
};

#endif

