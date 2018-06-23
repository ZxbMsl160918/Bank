#pragma once
class Consumer
{
public:
	Consumer();
	~Consumer();
	CString cardNumber;//卡号
	CString name;//用户姓名
	double money;//开户金额
	CString id;//身份证号码
	CString addr;//用户地址（具体到门牌号）
	CString phone;//用户号码
	CString usrPwd;//用户密码 必须六位
	CString confirmUsrPwd;//确认用户密码必须六位
	CString dipositHistory[20];//只保存最近的存款20条记录
	int errCount;//密码错误的次数
	int dpos;
	int fpos;
	CString fetchHistory[20];//只保存最近的取款20条记录
};