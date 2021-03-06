#pragma once


// elseMoney 对话框

class elseMoney : public CDialogEx
{
	DECLARE_DYNAMIC(elseMoney)

public:
	elseMoney(double* money, double nm, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~elseMoney();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ELSEMONEY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	double *m;
	double nowMoney;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
