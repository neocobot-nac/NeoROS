/*****************************************************************************
*  Neocobot OdinClient library
*  Copyright (C) 2019 Huang Shaojie  shaojie@neocobot.com
*
*  @file     task.h
*  @brief    ���������
*
*  @detail   �������������
*			 1.���������
*			 2.�����������Ϣ
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
#ifndef TASKS_H
#define TASKS_H

#include <map>
using std::map;

/*
@brief ������������
*/
typedef enum
{
	TASK_CONN = 100,
	TASK_C2S,
	TASK_HEART

}TaskType;

/*
@brief ������
*/
class Tasks
{
public:
	TaskType type;
	map<string, string> data;

	Tasks() 
	{
		data.clear();
	}

	~Tasks() 
	{
		data.clear();
	}
};

#endif