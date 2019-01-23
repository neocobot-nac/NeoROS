/*****************************************************************************
*  Neocobot OdinClient library
*  Copyright (C) 2019 Huang Shaojie  shaojie@neocobot.com
*
*  @file     logger.h
*  @brief    ��־��¼�ӿ�
*
*  @detail   ͷ�ļ���������־�ȼ��Լ���־��Ϣ����
*            ʹ���̼߳����־��Ϣ���������

*  @author   Huang Shaojie
*  @email    shaojie@neocobot.com
*  @version  0.2.0
*  @date     2019/01/17
*
*----------------------------------------------------------------------------
*  Change History :
*  <Date>     | <Version> | <Author>       | <Description>
*----------------------------------------------------------------------------
*  2019/01/17 | 0.2.0     | Huang Shaojie  | �齨�����幦��
*----------------------------------------------------------------------------
*****************************************************************************/
#ifndef _LOGGER_H
#define _LOGGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <stdarg.h>

#include "argdefine.h"
#include "thread.h"
#include "safequeue.h"

using std::ofstream;
using std::cout;
using std::endl;
using std::to_string;
using std::string;

#if defined(WINDOWS) || defined(_WIN32)
#ifndef _DEBUG
#define _DEBUG 0
#endif

#else
;
#endif

/*
@brief ��־���Ͷ���
*/
enum class LogType {
	Debug,
	Info,
	Warning,
	Error,
	Fatal
};

/*
@brief ��־�ȼ�����
*/
enum class LogLevel {
	NONE,
	LOW,
	MEDIUM,
	HIGH,
	CRITICAL
};

/*
@brief ��־��Ϣ����
*/
typedef struct log_message
{
private:
	LogType				_type;		// ����
	LogLevel			_level;		// �ȼ�
	RobotEvent			_event;		// �����¼�
	string				_message;	// ��־��Ϣ

	/*
	@brief ����־����ת��Ϊ��Ӧ���ַ���
	@return string ��־�����ַ���
	*/
	string LogTypeStr()
	{
		switch (_type)
		{
		case LogType::Debug:
			return "DEBUG";
		case LogType::Info:
			return "INFO";
		case LogType::Warning:
			return "WARNING";
		case LogType::Fatal:
			return "FATAL";
		case LogType::Error:
		default:
			return "ERROR";
		}
	}

public:
	log_message(LogType type, LogLevel level, RobotEvent event, const char* message) :
		_type(type), _level(level), _event(event), _message(message) {};
	log_message() {};
	~log_message() {};

	/*
	@brief �����־��Ϣת��Ϊ�������ʽ
	@return string ������ַ���
	*/
	string format()
	{
		switch (_type)
		{
		case LogType::Debug:
		case LogType::Info:
			return LogTypeStr() + ": " + _message;
		case LogType::Warning:
		case LogType::Error:
		case LogType::Fatal:
		default:
			return LogTypeStr() + " " + +"(" + to_string(static_cast<unsigned int>(_event)) + ")" + ": " + _message;
		}
	}
}LogMessage, *pLogMessage;


/*
@brief ��־��¼
*/
class NeoLogger : Neothread::NeoThread
{
private:
	/* ��־��Ϣ���� */
	threadsafe_queue<LogMessage> _MsgQueue;

	bool isRunning;

private:
	NeoLogger() :NeoThread() {};
	~NeoLogger() {};

public:
	void operator=(NeoLogger const&) = delete;
	NeoLogger(NeoLogger const&) = delete;

	/*
	@brief ���ʵ��
	*/
	static NeoLogger& GetInstance()
	{
		static NeoLogger _instance;
		return _instance;
	}

	/*
	@brief ������־����
	*/
	static RobotEvent StartLog()
	{
		NeoLogger& _logger = GetInstance();
		_logger.isRunning = true;
		_logger.Start();
		return RobotEvent_Succeed;
	}

	/*
	@brief ʵ��NeoThread�߳����Run����
	*/
	virtual void Run()
	{
		time_t rawtime;
		struct tm* timeinfo;
		char logformat[32];

		// ������������ģʽ�²Ż����ļ���ʽ�����־��Ϣ
#ifdef _DEBUG
#else
		// ��ȡ��־·��
		char fileformat[32];
		string filepath;

		RobotEvent fret = NeoResource::Get(NeoResource::LOG_DIR, &filepath);
		if (RobotEvent_Succeed == fret)
		{
			time(&rawtime);
			timeinfo = localtime(&rawtime);
			strftime(fileformat, sizeof(fileformat), "%Y%m%d%H%M%S", timeinfo);

			filepath.append(PATH_OPERATOR);
			filepath.append(fileformat);
			filepath.append(".log");

			ofstream fout(filepath);
#endif
			while (isRunning)
			{
				LogMessage _msg;
				_MsgQueue.wait_and_pop(_msg);

				time(&rawtime);
				timeinfo = localtime(&rawtime);
				strftime(logformat, sizeof(logformat), "%Y-%m-%d %H:%M:%S", timeinfo);

				string err = _msg.format();
#ifdef _DEBUG
				printf("%s  %s\n", logformat, err.c_str());
#else
				fout << logformat << " " << err << endl;
#endif
			}

#ifdef _DEBUG
#else
			fout.close();
		}
#endif
	}

	/*
	@brief ������Ϣ������Debugģʽ�²Ż����
	@param string message Debugģʽ�����Ϣ
	*/
	static void Debug(const char* message, ...)
	{
#ifdef _DEBUG
		va_list args;
		va_start(args, message);

		NeoLogger& _logger = GetInstance();
		string print_msg = _logger.LogPrint(message, args);
		LogMessage* _msg = new LogMessage(LogType::Debug, LogLevel::NONE, RobotEvent_Succeed, print_msg.c_str());
		_logger._MsgQueue.push(*_msg);

		va_end(args);
#endif
	}

	/*
	@brief ��־������Ϣ���
	@param string message �����Ϣ
	*/
	static void Info(const char* message, ...)
	{
		va_list args;
		va_start(args, message);

		NeoLogger& _logger = GetInstance();
		string print_msg = _logger.LogPrint(message, args);
		LogMessage* _msg = new LogMessage(LogType::Info, LogLevel::NONE, RobotEvent_Succeed, print_msg.c_str());
		_logger._MsgQueue.push(*_msg);

		va_end(args);
	}

	/*
	@brief ��־������Ϣ�����һ�㲻Ӱ���������п��������޸����þ��汨��
	@param RobotEvent	event  ������
	@param string		message ����(����)��ϸ��Ϣ
	*/
	static void Warning(RobotEvent event, const char* message, ...)
	{
		va_list args;
		va_start(args, message);

		NeoLogger& _logger = GetInstance();
		string print_msg = _logger.LogPrint(message, args);
		LogMessage* _msg = new LogMessage(LogType::Warning, LogLevel::NONE, event, print_msg.c_str());
		_logger._MsgQueue.push(*_msg);

		va_end(args);
	}

	/*
	@brief ��־������Ϣ�����һ��Ӱ�쵽���ֹ������е��������ó���������˳����Դ�����ʽ����
	@param LogLevel		level   �����𣬷�ΪLOW/MEDIUM/HIGH/CRITICAL���ֵȼ�
	@param RobotEvent	event	������
	@param string		message ���д�����ϸ��Ϣ
	*/
	static void Error(LogLevel level, RobotEvent event, const char* message, ...)
	{
		va_list args;
		va_start(args, message);

		NeoLogger& _logger = GetInstance();
		string print_msg = _logger.LogPrint(message, args);
		LogMessage* _msg = new LogMessage(LogType::Error, level, event, print_msg.c_str());
		_logger._MsgQueue.push(*_msg);

		va_end(args);
	}

	/*
	@brief ��־ʧ����Ϣ�����һ������������صĴ����³����޷����л��������Fatal��ʽ��������
	@param RobotEvent	event	������
	@param string		message ����ʧ����ϸ��Ϣ
	*/
	static void Fatal(RobotEvent event, const char* message, ...)
	{
		va_list args;
		va_start(args, message);

		NeoLogger& _logger = GetInstance();
		string print_msg = _logger.LogPrint(message, args);
		LogMessage* _msg = new LogMessage(LogType::Fatal, LogLevel::CRITICAL, event, print_msg.c_str());
		_logger._MsgQueue.push(*_msg);

		va_end(args);
	}

	/*
	@brief ��־��Ϣת��,��ʽ�����
	@param const char*	message	��־��Ϣ
	@param va_list		args	�ɱ�����б�
	@return string ��ʽ������ַ���
	*/
	string LogPrint(const char* message, va_list args)
	{
		string	s_log;
		string	arg_type;
		char*	str_tmp = NULL;
		bool	isfind = false;

		while (*message != '\0')
		{
			switch (*message)
			{
			case '%':
				isfind = true;
				arg_type.clear();
				break;

			case 'u':
			case 'd':
				if (isfind)
				{
					isfind = false;
					s_log.append(to_string(va_arg(args, int)));
					break;
				}

			case 'f':
				if (isfind)
				{
					isfind = false;
					s_log.append(to_string(va_arg(args, double)));
					break;
				}

			case 'c':
				if (isfind)
				{
					isfind = false;
					s_log.append(to_string(va_arg(args, int)));
					break;
				}

			case 's':
				if (isfind)
				{
					isfind = false;
					str_tmp = (char*)va_arg(args, int);
					while (*str_tmp != '\0')
					{
						s_log.append(1, *str_tmp);
						str_tmp++;
					}
					break;
				}

			default:
				s_log.append(1, *message);
				break;
			}
			if (isfind)
			{
				arg_type.append(1, *message);
			}
			message++;
		}

		return s_log;
	}
};

#endif
