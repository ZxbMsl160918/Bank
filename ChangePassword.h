#pragma once
#include "Consumer.h"

// ChangePassword 对话框

class ChangePassword : public CDialogEx
{
	DECLARE_DYNAMIC(ChangePassword)

public:
	ChangePassword(Consumer*, CString, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ChangePassword();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHANGEPWD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	Consumer *nowCus;
	CString nowUse;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
