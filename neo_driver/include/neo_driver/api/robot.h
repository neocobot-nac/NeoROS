/*****************************************************************************
*  Neocobot OdinClient library
*  Copyright (C) 2019 Huang Shaojie  shaojie@neocobot.com
*
*  @file     robot.h
*  @brief    OdinClient�û��ӿ�
*
*  @detail   Ŀǰ�汾��ͷ�ļ�������OdinClient�û��ӿ�
*            ����Ľӿڰ�����������:
*			 1. RobotLogin			��½������
*			 2. RobotLogout			�ǳ�������
*			 3. Setup				��е�۳�ʼ������
*			 4. Shutdown			�رջ�е��
*			 5. move_to_angles		�ؽڽǶ��˶�
*			 6. move_to_pose		ĩ��λ���˶�
*			 7. wait_for_motors		�ȴ��˶�����
*			 8. moveJ				�ؽڹ켣�˶�
*			 9. moveL				����ι켣�˶�
*			 10. moveP				���ӹ켣�˶�
*			 11. release			�ɿ���е�۹ؽ�
*			 12. hold				������е�۹ؽ�
*			 13. stop				ֹͣ��ǰ�˶������벻���˶�״̬
*			 14. recover			�ָ����˶�״̬
*			 15. calibrate			У׼
*			 16. reset				��λ
*			 17. get_motor_ids		��ȡ�ؽ�ID
*			 18. get_angles			��ȡ�ؽڽǶ�
*			 19. get_velocity		��ȡ�ؽ��ٶ�
*			 20. get_current		��ȡ�ؽڵ���
*			 21. get_pose			��ȡĩ��λ��
*			 22. forward			ǰ���˶�ѧ����
*			 23. inverse			�����˶�ѧ����
*			 24. get_input			��ȡIO��Ϣ
*			 25. set_output			����IO��Ϣ
*
*  @author   Huang Shaojie
*  @email    shaojie@neocobot.com
*  @version  0.2.0
*  @date     2019/01/14
*
*----------------------------------------------------------------------------
*  Change History :
*  <Date>     | <Version> | <Author>       | <Description>
*----------------------------------------------------------------------------
*  2019/01/14 | 0.2.0     | Huang Shaojie  | �ع�v0.1.0,���ע��
*----------------------------------------------------------------------------
*****************************************************************************/

#ifndef _ROBOT_H
#define _ROBOT_H

#include "client.h"

/* �ַ���ת���еķ���˵�� */
#define LEFT_BRACES			"{"
#define RIGHT_BRACES		"}"
#define LEFT_BRACKET		"["
#define RIGHT_BRACKET		"]"
#define DOT					","
#define QUOTATION			"\""
#define COLON				":"
#define SPACE				" "

/* ������ǰ��֧�ֵ�������� */
#define MAX_MOTORS		10

/*
@brief NeoClient�ӿ���
���⸺���ṩ�û��ӿ�,�������ɽӿڶ�Ӧ�����񲢴������񷵻�ֵ
*/
class Robot
{
private:
	/* ��Ϣ������ʵ�� */
	Client client;

	/* ��ǰ���ӻ�е�۵ĵ����ŵ�ʵ���������������� */
	vector<int>			_motorIds;
	size_t				_idSize;

	/* �û�IP */
	string				ip;

	/* ��е��ϵͳ��Ϣ */
	RobotSystemInfo		_robotSystemInfo;

	/* ��е�۵ĳ�ʼ������״̬,true��ʾ�Ѿ�����,false��֮ */
	bool				_isSetup;

private:
	/*
	@brief ��ȡ������������������_motorIds��_idSizeʵ����������
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step ����_motorIds��_idSizeʵ����������
	*/
	RobotEvent _getMotorIds();

	/*
	@brief ��SetupParan����ת��Ϊstring
	@param SetupParam	parameters	��е��ͨѶ���ò���
	@param string&		_setupParam	ת������ַ���
	@step ȡ����������
	@step �ַ���ƴ��
	*/
	void to_SetupParamString(SetupParam parameters, string& _setupParam);

	/*
	@brief �������Ų���ת��Ϊstring
	@param vector<int>	id_params		��е�۵���������
	@param string&		string_params	ת������ַ���
	@step ȡ����������
	@step �ַ���ƴ��
	*/
	void to_IdString(vector<int> id_params, string& string_params);

	/*
	@brief �������Ų���ת��Ϊstring
	@param const int	id_params		��е�۵�����
	@param string&		string_params	ת������ַ���
	@step ȡ����������
	@step �ַ���ƴ��
	*/
	void to_IdString(const int id_params, string& string_params);

	/*
	@brief �������Ų���ת��Ϊstring
	@param size_t		size			����������
	@param const int*	id_params		һ���е�۵�����
	@param string&		string_params	ת������ַ���
	@step ȡ����������
	@step �ַ���ƴ��
	*/
	void to_IdString(size_t size, const int* id_params, string& string_params);

	/*
	@brief ��int����ת��Ϊstring
	@param const int	int_params		int����
	@param string&		string_params	ת��Ϊ�ַ���
	@step ȡ����������
	@step �ַ���ƴ��
	*/
	void to_IntString(const int int_params, string& string_params);

	/*
	@brief ��int����ת��Ϊstring
	@param size_t		size			��������
	@param const int*	int_params		int����
	@param string&		string_params	ת��Ϊ�ַ���
	@step ȡ����������
	@step �ַ���ƴ��
	*/
	void to_IntString(size_t size, const int* int_params, string& string_params);

	/*
	@brief ��double����ת��Ϊstring
	@param const double	double_params	double����
	@param string&		string_params	ת��Ϊ�ַ���
	@step ȡ����������
	@step �ַ���ƴ��
	*/
	void to_DoubleString(const double double_params, string& string_params);

	/*
	@brief ��double����ת��Ϊstring
	@param size_t			size			��������
	@param const double*	double_params	double����
	@param string&			string_params	ת��Ϊ�ַ���
	@step ȡ����������
	@step �ַ���ƴ��
	*/
	void to_DoubleString(size_t size, const double* double_params, string& string_params);

	/*
	@brief ��io�źŲ���ת��Ϊstring
	@param const int		id_params		����������
	@param const int		signal_params	io�źŲ���
	@param string&			string_params	ת��Ϊ�ַ���
	@step ȡ����������
	@step �ַ���ƴ��
	*/
	void to_SignalString(const int id_params, const int signal_params, string& string_params);

	/*
	@brief ��io�źŲ���ת��Ϊstring
	@param size_t			size			����������
	@param const int*		id_params		һ�������
	@param const int*		signal_params	һ��io�źŲ���
	@param string&			string_params	ת��Ϊ�ַ���
	@step ȡ����������
	@step �ַ���ƴ��
	*/
	void to_SignalString(size_t size, const int* id_params, const int* signal_params, string& string_params);

	/*
	@brief ����������ת��Ϊstring
	@param Pose				pose_param		��������
	@param string&			string_params	ת��Ϊ�ַ���
	@step ȡ����������
	@step �ַ���ƴ��
	*/
	void to_PoseString(Pose pose_param, string& string_params);

	/*
	@brief ����������ת��Ϊstring
	@param size_t			size			������������
	@param Pose				pose_param		һ�鶯������
	@param string&			string_params	ת��Ϊ�ַ���
	@step ȡ����������
	@step �ַ���ƴ��
	*/
	void to_PointString(size_t size, Pose* point_param, string& string_params);

	/*
	@brief �ַ����ָ�
	@param const string&	origin_params	Դ�ַ�
	@param vector<string>&	split_params	�ָ����ַ�
	@param const string&	key_params		�ָ�ؼ��ַ�
	@step �����ַ�
	@step ǰ��ָ�����ָ����ַ�
	*/
	void SplitString(const string& origin_params, vector<string>& split_params, const string& key_params);

public:
	/*
	@brief Robot���캯��
	@step ��ʼ������
	*/
	Robot();

	/*
	@brief Robot��������
	@step �������
	*/
	~Robot();

	/*
	@brief ��½��������������
	@param const char*	ServerIp	������ip��ַ,��ʽΪxxx.xxx.xxx
	@param short int	ServerPort	�������˿�,��ֵ��ΧΪ0-65535
	@return RobotEvent ��е���¼�
	@step ��ʼ��socket����
	@step ����ע������
	@step ��ȡ���񷵻�ֵ
	@step �ж�ע���Ƿ�ɹ�
	@step ���ɻ�ȡ��Ϣ����
	@step ��ȡ���񷵻�ֵ
	@step ��¼��ȡ�ķ�����ϵͳ��Ϣ
	@step ʹ��_getMotorIds������ʼ������
	*/
	RobotEvent RobotLogin(const char* ServerIp, short int ServerPort);

	/*
	@brief �ǳ�������
	@return RobotEvent ��е���¼�
	@step �ر�socket
	*/
	RobotEvent RobotLogout();

	/*
	@brief ���û�е�۲���ʼ��
	@param const char*	name		��е������
	@param SetupParam	parameters	���Ӳ���
	@param SetupMode	mode		����ģʽ,SetupMode_RealModeΪ����ʵ�ʻ�е��,SetupMode_VirtualModeΪ���������е��
	@return RobotEvent ��е���¼�
	@step ���ɻ�е�۳�ʼ������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ����óɹ�
	*/
	RobotEvent Setup(const char* name, SetupParam parameters, SetupMode mode);

	/*
	@brief ���û�е�۲���ʼ��
	@return RobotEvent ��е���¼�
	@step ���ɽ�����������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�����ɹ�
	*/
	RobotEvent Shutdown();

	/*
	@brief �ؽڽǶ��˶�
	@param const int		motor_ids		������
	@param const double		angles			��Ŷ�Ӧ�ĽǶ�ֵ
	@param float			velocity		�˶�����ٶ�ֵ(Ĭ��ֵΪ30.0)
	@param float			acceleration	�˶������ٶ�ֵ(Ĭ��ֵΪ150.0)
	@param RelativeMode		relative		����ģʽ,RelativeMode_Absolute��ʾ��ǰ�Ƕ�ֵΪ���ԽǶ�,RelativeMode_Relative��ʾ��ǰ�Ƕ�ֵΪ�Ƕ�����(Ĭ��ֵΪRelativeMode_Absolute)
	@return RobotEvent ��е���¼�
	@step ���ɹؽڽǶ��˶�����
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ���ճɹ�
	*/
	RobotEvent move_to_angles(const int motor_ids, const double angles, float velocity = 30.0, float acceleration = 150.0, RelativeMode relative = RelativeMode_Absolute);
		
	/*
	@brief �ؽڽǶ��˶�
	@param size_t			size			�˶��ĵ������
	@param const int*		motor_ids		һ�������
	@param const double*	angles			һ�����Ŷ�Ӧ�ĽǶ�ֵ
	@param float			velocity		�˶�����ٶ�ֵ(Ĭ��ֵΪ30.0)
	@param float			acceleration	�˶������ٶ�ֵ(Ĭ��ֵΪ150.0)
	@param RelativeMode		relative		����ģʽ,RelativeMode_Absolute��ʾ��ǰ�Ƕ�ֵΪ���ԽǶ�,RelativeMode_Relative��ʾ��ǰ�Ƕ�ֵΪ�Ƕ�����(Ĭ��ֵΪRelativeMode_Absolute)
	@return RobotEvent ��е���¼�
	@step ���ɹؽڽǶ��˶�����
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ���ճɹ�����
	*/
	RobotEvent move_to_angles(size_t size, const int* motor_ids, const double* angles, float velocity = 30.0, float acceleration = 150.0, RelativeMode relative = RelativeMode_Absolute);

	/*
	@brief ĩ��λ���˶�
	@param Pose				pose			ĩ��λ�ˣ�����λ��ֵ(x,y,z),��ֵ̬(Rx,Ry,Rz)
	@param float			velocity		�˶�����ٶ�ֵ(Ĭ��ֵΪ30.0)
	@param float			acceleration	�˶������ٶ�ֵ(Ĭ��ֵΪ150.0)
	@param RelativeMode		relative		����ģʽ,RelativeMode_Absolute��ʾ��ǰ�Ƕ�ֵΪ���ԽǶ�,RelativeMode_Relative��ʾ��ǰ�Ƕ�ֵΪ�Ƕ�����(Ĭ��ֵΪRelativeMode_Absolute)
	@return RobotEvent ��е���¼�
	@step ����ĩ��λ���˶�����
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ���ճɹ�����
	*/
	RobotEvent move_to_pose(Pose pose, float velocity = 30.0, float acceleration = 150.0, RelativeMode relative = RelativeMode_Absolute);

	/*
	@brief �ȴ�����˶�����
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ��˶�����
	*/
	RobotEvent wait_for_motors();

	/*
	@brief �ȴ�����˶�����
	@param const int motor_ids ������
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ��˶�����
	*/
	RobotEvent wait_for_motors(const int motor_ids);

	/*
	@brief �ȴ�����˶�����
	@param size_t		size		��Ҫ�ȴ��ĵ������
	@param const int*	motor_ids	һ�������
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ��˶�����
	*/
	RobotEvent wait_for_motors(size_t size, const int* motor_ids);

	/*
	@brief ��е�۹ؽڹ켣�˶�
	@param size_t			size			·��������
	@param Pose*			points			һϵ��·����
	@param float			velocity		��е���˶�����ٶ�(Ĭ��ֵΪ30.0)
	@param float			acceleration	��е���˶������ٶ�(Ĭ��ֵΪ150.0)
	@param float			interval		�켣��岹���(Ĭ��ֵΪ0.04)
	@param Traj_Close_Mode	mode			�켣�ջ�ģʽ,TrajCloseMode_Closed��ʾ�켣�ջ�,TrajCloseMode_Open��ʾ�켣����(Ĭ��ֵΪTrajCloseMode_Open)
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ��˶�����
	*/
	RobotEvent moveJ(size_t size, Pose* points, float velocity = 20.0, float acceleration = 150.0, float interval = 0.04, Traj_Close_Mode mode = TrajCloseMode_Open);

	/*
	@brief ��е��ĩ�˶���ι켣�˶�
	@param size_t			size			·��������
	@param Pose*			points			һϵ��·����
	@param const double*	radius			��Ӧ��·���㽻�ڰ뾶
	@param float			velocity		��е���˶�����ٶ�(Ĭ��ֵΪ30.0)
	@param float			acceleration	��е���˶������ٶ�(Ĭ��ֵΪ150.0)
	@param float			interval		�켣��岹���(Ĭ��ֵΪ0.04)
	@param Traj_Close_Mode	mode			�켣�ջ�ģʽ,TrajCloseMode_Closed��ʾ�켣�ջ�,TrajCloseMode_Open��ʾ�켣����(Ĭ��ֵΪTrajCloseMode_Open)
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ��˶�����
	*/
	RobotEvent moveL(size_t size, Pose* points, const double* radius, float velocity = 30.0, float acceleration = 150.0, float interval = 0.04, Traj_Close_Mode mode = TrajCloseMode_Open);

	/*
	@brief ��е��ĩ�˸��ӹ켣�˶�
	@param size_t			size			·��������
	@param Pose*			points			һϵ��·����
	@param float			velocity		��е���˶�����ٶ�(Ĭ��ֵΪ30.0)
	@param float			acceleration	��е���˶������ٶ�(Ĭ��ֵΪ150.0)
	@param float			interval		�켣��岹���(Ĭ��ֵΪ0.04)
	@param Traj_Close_Mode	mode			�켣�ջ�ģʽ,TrajCloseMode_Closed��ʾ�켣�ջ�,TrajCloseMode_Open��ʾ�켣����(Ĭ��ֵΪTrajCloseMode_Open)
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ��˶�����
	*/
	RobotEvent moveP(size_t size, Pose* points, float velocity = 30.0, float acceleration = 150.0, float interval = 0.04, Traj_Close_Mode mode = TrajCloseMode_Open);

	/*
	@brief �ɿ���е�۹ؽ�
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent release();

	/*
	@brief �ɿ���е�۹ؽ�
	@param const int motor_ids ������
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent release(const int motor_ids);

	/*
	@brief �ɿ���е�۹ؽ�
	@param size_t		size		��Ҫ�ȴ��ĵ������
	@param const int*	motor_ids	һ�������
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent release(size_t size, const int* motor_ids);

	/*
	@brief ������е�۹ؽ�
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent hold();

	/*
	@brief ������е�۹ؽ�
	@param const int motor_ids ������
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent hold(const int motor_ids);

	/*
	@brief ������е�۹ؽ�
	@param size_t		size		��Ҫ�ȴ��ĵ������
	@param const int*	motor_ids	һ�������
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent hold(size_t size, const int* motor_ids);

	/*
	@brief ֹͣ��е���˶������벻���˶�״̬
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent stop();

	/*
	@brief �ָ�����е�ۿ��˶�״̬
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent recover();

	/*
	@brief У׼��е��
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent calibrate();

	/*
	@brief ��λ��е��
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent reset();

	/*
	@brief ��ȡ��������������
	@param size_t		&size		���������������
	@param int*			motor_ids	һ������Ų�������
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent get_motor_ids(size_t &size, int* motor_ids);

	/*
	@brief ��ȡ�ؽڽǶ�
	@param const int	motor_ids	������
	@param double		&angles		���صĽǶ�ֵ
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent get_angles(const int motor_ids, double &angles);

	/*
	@brief ��ȡ�ؽڽǶ�
	@param double*		angles		�������йؽڵĽǶ�ֵ
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent get_angles(double* angles);

	/*
	@brief ��ȡ�ؽڽǶ�
	@param size_t		size		��Ҫ��ȡ�Ƕȵĵ������
	@param const int*	motor_ids	һ�������
	@param double*		angles		�����Ŷ�Ӧ�ĽǶ�ֵ
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent get_angles(size_t size, const int* motor_ids, double* angles);

	/*
	@brief ��ȡ�ؽ��ٶ�
	@param const int	motor_ids	������
	@param double		&velocity	���ص��ٶ�ֵ
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent get_velocity(const int motor_ids, double &velocity);

	/*
	@brief ��ȡ�ؽ��ٶ�
	@param double*		velocity		�������йؽڵ��ٶ�ֵ
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent get_velocity(double* velocity);

	/*
	@brief ��ȡ�ؽ��ٶ�
	@param size_t		size		��Ҫ��ȡ�ٶȵĵ������
	@param const int*	motor_ids	һ�������
	@param double*		velocity	�����Ŷ�Ӧ���ٶ�ֵ
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent get_velocity(size_t size, const int* motor_ids, double* velocity);

	/*
	@brief ��ȡ�ؽڵ���
	@param const int	motor_ids	������
	@param double		&current	���صĵ���ֵ
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent get_current(const int motor_ids, double &current);

	/*
	@brief ��ȡ�ؽڵ���
	@param double*		current		�������йؽڵĵ���ֵ
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent get_current(double* current);

	/*
	@brief ��ȡ�ؽڵ���
	@param size_t		size		��Ҫ��ȡ�����ĵ������
	@param const int*	motor_ids	һ�������
	@param double*		current		�����Ŷ�Ӧ�ĵ���ֵ
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent get_current(size_t size, const int* motor_ids, double* current);

	/*
	@brief ��ȡĩ��λ��
	@param Pose			&pose		��ȡ��ĩ��λ�˷���ֵ
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent get_pose(Pose &pose);

	/*
	@brief ǰ���˶�ѧ����
	@param const double*	angles		��ؽ�������Ӧ��һЩ�йؽڽǶ�ֵ
	@param Pose				&pose		�����õ�ĩ��λ��ֵ
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent forward(const double* angles, Pose &pose);

	/*
	@brief �����˶�ѧ����
	@param const Pose	pose		��е��ĩ��λ��ֵ
	@param double*		angles		�����õĹؽڽǶ�ֵ
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent inverse(Pose pose, double* angles);

	/*
	@brief ��ȡ�ؽ�io����
	@param const int	motor_ids	������
	@param int			&signal	���ص��ź�ֵ
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent get_input(const int motor_ids, int &signal);

	/*
	@brief ��ȡ�ؽ�io����
	@param int		&signal		�������йؽڵ��ź�ֵ
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent get_input(int* signal);

	/*
	@brief ��ȡ�ؽ�io����
	@param size_t		size		��Ҫ��ȡ�źŵĵ������
	@param const int	motor_ids	һ�������
	@param int			&signal		�����Ŷ�Ӧ���ź�ֵ
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent get_input(size_t size, const int* motor_ids, int* signal);

	/*
	@brief ���ùؽ�io���
	@param const int	motor_ids	һ�������
	@param const int	signal		�����Ŷ�Ӧ���ź�ֵ
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent set_output(const int motor_ids, const int signal);

	/*
	@brief ���ùؽ�io���
	@param size_t		size		��Ҫ�����źŵĵ������
	@param const int	motor_ids	һ�������
	@param const int*	&signal		�����Ŷ�Ӧ���ź�ֵ
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent set_output(size_t size, const int* motor_ids, const int* signal);

	/*
	@brief ����ĩ�˹��߶���
	@param const char*	name		ĩ�˹�������
	@param const char*	action		��������
	@return RobotEvent ��е���¼�
	@step ��������
	@step ��ȡ���񷵻�ֵ
	@step �����Ƿ�ɹ�
	*/
	RobotEvent set_EOAT_action(const char* name, const char* action);

};







#endif
