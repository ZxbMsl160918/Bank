#pragma once
#include "Consumer.h"

// UsrHistory 对话框

class UsrHistory : public CDialogEx
{
	DECLARE_DYNAMIC(UsrHistory)

public:
	UsrHistory(Consumer& nowCus, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~UsrHistory();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USRHISTORY };
#endif

protected:
	CListCtrl m_list1;//存款
	CListCtrl m_list2;//取款
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	Consumer &cus;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
