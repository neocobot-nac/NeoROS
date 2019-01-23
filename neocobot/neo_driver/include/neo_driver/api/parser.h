/*****************************************************************************
*  Neocobot OdinClient library
*  Copyright (C) 2019 Huang Shaojie  shaojie@neocobot.com
*
*  @file     parser.h
*  @brief    xml��Ϣ�����ʹ��ģ��
*
*  @detail   Ŀǰ�汾��ͷ�ļ�������xml��Ϣ�����ʹ��ģ��
*			 1.�ṩ��xml��Ϣ�Ĵ���ͽ������
*            2.�ṩ����Ϣת���е�У�鹦��
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
#ifndef PARSER_H
#define PARSER_H

#define XML_LEFT_BRACKET "<"
#define XML_LEFT_SLASH_BRACKET "</"
#define XML_RIGHT_BRACKET ">"
#define XML_RIGHT_SLASH_BRACKET "/>"
#define XML_SLASH "/"
#define XML_SPACE " "

#include "argdefine.h"
#include <string.h>
#include <string>
#include <map>
#include <vector>

using std::string;
using std::map;
using std::to_string;


typedef enum XML_Event
{
	XMLEvent_Succeed	= 0,	// �޴���
	XMLEvent_Error,				// ����

}XMLEvent;

/*
@brief xml��ǩ
*/
class NeoXmlElement
{
private:
	string xmlElement;

	string xml_name;
	size_t xml_size_of_name;
	size_t xml_start_name_index;
	size_t xml_end_name_index;

	string xml_text;
	size_t xml_size_of_text;
	size_t xml_text_index;

	vector<NeoXmlElement> children;

private:
	/*
	@brief ���±�ǩ����
	*/
	void _updateXMLParam();

public:
	NeoXmlElement(string element);
	NeoXmlElement();
	~NeoXmlElement();

	/*
	@brief ���ñ�ǩ��
	@param string name ��ǩ���ַ���
	*/
	void					setName(string name);

	/*
	@brief ���ñ�ǩ����
	@param string name ��ǩ�����ַ���
	*/
	void					setText(string text);

	/*
	@brief ���ӱ�ǩ����
	@param string name ���ӵı�ǩ�����ַ���
	*/
	void					linkText(string text);

	/*
	@brief ��ȡ��ǩ�ַ���
	@return string ���ر�ǩ��Ӧ���ַ���
	*/
	string					getElement();

	/*
	@brief ��ȡ��ǩ��
	@return string ���ر�ǩ��
	*/
	string					getName();

	/*
	@brief ��ȡ��ǩ����
	@return string ���ر�ǩ����
	*/
	string					getText();

	/*
	@brief ��ȡ�ӱ�ǩ
	@return vector<NeoXmlElement> �ӱ�ǩ����
	*/
	vector<NeoXmlElement>	getChildren();

	/*
	@brief ����ӱ�ǩ
	@param NeoXmlElement &element �ӱ�ǩ
	*/
	void					setChildren(NeoXmlElement &element);
};

/*
@brief xml�ļ�
*/
class NeoXmlDocument
{
private:
	string			xmlDocument;
	NeoXmlElement	root;

private:
	/*
	@brief ���ַ����н�����Ӧ�ı�ǩ
	@param string &s	��Ҫ�������ַ���
	@param string name	��ǩ��
	@return NeoXmlElement �����õ��ı�ǩ��
	*/
	NeoXmlElement	_getElement(string &s, string name);

	/*
	@brief ���ַ����л�ȡ��ǩ������
	@param string			&s		��Ҫ�������ַ���
	@param vector<string>	&name	��ǩ������
	@return XMLEvent �����¼�
	*/
	XMLEvent		_getElementNameVector(string &s, vector<string> &name);

	/*
	@brief �ݹ������б�ǩ
	@param NeoXmlElement &element �ӱ�ǩ
	@return XMLEvent �����¼�
	*/
	XMLEvent		_recursionParse(NeoXmlElement &element);

public:
	NeoXmlDocument();
	~NeoXmlDocument();

	/*
	@brief ͨ���ַ�����ȡ���б�ǩ
	@param string &s �ַ���
	@return XMLEvent �����¼�
	*/
	XMLEvent		parse(string &s);

	/*
	@brief ��ȡxml����ǩ
	@return NeoXmlElement ����ǩ
	*/
	NeoXmlElement	getRoot();

	/*
	@brief ͨ����ǩ�������ַ���
	@param NeoXmlElement &root ��ǩ��
	@return XMLEvent �����¼�
	*/
	XMLEvent		generate(NeoXmlElement &root);

	/*
	@brief ��ȡ����ǩ��Ӧ���ַ���
	@return string �ַ���
	*/
	string			getString();

};

/*
@brief У��ģ��
*/
class CheckSum
{
private:
	int					sum;
	vector<string>		_element;

public:
	CheckSum();
	~CheckSum();

	/*
	@brief ���У��Ԫ��
	@param string element ��ҪУ���Ԫ��
	*/
	void	AddElement(string element);

	/*
	@brief ��������ӵ�Ԫ�ؼ���У��ֵ
	@return int ����У��ֵ
	*/
	int		CalcSum();

};


/*
@brief xml��Ϣ����ģ��
*/
class Parser
{
public:
	/*
	@brief �����ע����Ϣ
	@param string				&msg	��������Ϣ
	@param map<string, string>	&data	���ǰ����
	@return RobotEvent �¼�
	*/
	RobotEvent wrap_license(string &msg, map<string, string> &data);

	/*
	@brief ����ɿͻ�����Ϣ��Ϣ
	@param string				&msg	��������Ϣ
	@param map<string, string>	&data	���ǰ����
	@return RobotEvent �¼�
	*/
	RobotEvent wrap_clientinfo(string &msg, map<string, string> &data);

	/*
	@brief �������������Ϣ
	@param string				&msg	��������Ϣ
	@param map<string, string>	&data	���ǰ����
	@return RobotEvent �¼�
	*/
	RobotEvent wrap_heart(string &msg, map<string, string> &data);

	/*
	@brief �����һ�㹦����Ϣ
	@param string				&msg	��������Ϣ
	@param map<string, string>	&data	���ǰ����
	@return RobotEvent �¼�
	*/
	RobotEvent wrap_msg(string &msg, map<string, string> &data);

	/*
	@brief ����������
	@param map<string, string>	&data	��������
	@param string				&msg	���ǰ��Ϣ
	@return RobotEvent �¼�
	*/
	RobotEvent unwrap(map<string, string> &data, string &msg);

	/*
	@brief �����������Ϣ��Ϣ
	@param map<string, string>	&data	��������
	@param string				&msg	���ǰ��Ϣ
	@return RobotEvent �¼�
	*/
	RobotEvent unwrap_ServerInfo(map<string, string> &data, string &msg);

	/*
	@brief ������ӽ����Ϣ
	@param map<string, string>	&data	��������
	@param string				&msg	���ǰ��Ϣ
	@return RobotEvent �¼�
	*/
	RobotEvent unwrap_ConnResult(map<string, string> &data, string &msg);

	/*
	@brief �����������Ϣ
	@param map<string, string>	&data	��������
	@param string				&msg	���ǰ��Ϣ
	@return RobotEvent �¼�
	*/
	RobotEvent unwrap_Heart(map<string, string> &data, string &msg);

	/*
	@brief ���������Ϣ
	@param map<string, string>	&data	��������
	@param string				&msg	���ǰ��Ϣ
	@return RobotEvent �¼�
	*/
	RobotEvent unwrap_Error(map<string, string> &data, string &msg);

	/*
	@brief ���һ����Ϣ
	@param map<string, string>	&data	��������
	@param string				&msg	���ǰ��Ϣ
	@return RobotEvent �¼�
	*/
	RobotEvent unwrap_Msg(map<string, string> &data, string &msg);

};

#endif
