// elseMoney.cpp: 实现文件
//

#include "stdafx.h"
#include "Bank.h"
#include "elseMoney.h"
#include "afxdialogex.h"


// elseMoney 对话框

IMPLEMENT_DYNAMIC(elseMoney, CDialogEx)

elseMoney::elseMoney(double* money, double nm, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ELSEMONEY, pParent)
{
	m = money;
	*m = 0;
	nowMoney = nm;
}

elseMoney::~elseMoney()
{
}

void elseMoney::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(elseMoney, CDialogEx)
	ON_BN_CLICKED(IDOK, &elseMoney::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &elseMoney::OnBnClickedCancel)
END_MESSAGE_MAP()


// elseMoney 消息处理程序


void elseMoney::OnBnClickedOk()
{
	CString money;
	GetDlgItemText(IDC_EM, money);
	if (_wtof(money) > 10000)
	{
		AfxMessageBox(L"取款金额过大！");
		return;
	}
	*m = _wtof(money);
	if (*m > nowMoney)
	{
		AfxMessageBox(L"您的余额不足！");
		*m = 0;
		return;
	}
	int temp = *m;
	if (temp%100 != 0)
	{
		AfxMessageBox(L"您必须输入100的倍数！");
		*m = 0;
		return;
	}
	CDialogEx::OnOK();
}


void elseMoney::OnBnClickedCancel()
{
	EndDialog(IDD_ELSEMONEY);
}
