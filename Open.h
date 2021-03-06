#pragma once
#include "Consumer.h"
// Open 对话框

class Open : public CDialogEx
{
	DECLARE_DYNAMIC(Open)

public:
	Open(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Open();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USROPEN };
#endif

protected:
	Consumer cus;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CFont m_editFont;
	DECLARE_MESSAGE_MAP()
public:
	bool judge;//是否开户成功
	Consumer Get_Cus();//获取用户
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
