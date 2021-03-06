// UsrHistory.cpp: 实现文件
//

#include "stdafx.h"
#include "Bank.h"
#include "UsrHistory.h"
#include "afxdialogex.h"

// UsrHistory 对话框

IMPLEMENT_DYNAMIC(UsrHistory, CDialogEx)

UsrHistory::UsrHistory(Consumer& nowCus,CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USRHISTORY, pParent), cus(nowCus)
{

}

UsrHistory::~UsrHistory()
{
}

void UsrHistory::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_LISTDEP, m_list1);
	DDX_Control(pDX, IDC_LISTFET, m_list2);
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(UsrHistory, CDialogEx)
END_MESSAGE_MAP()


// UsrHistory 消息处理程序


BOOL UsrHistory::OnInitDialog()
{
	CString temp;
	CDialogEx::OnInitDialog();
	m_list1.InsertColumn(0, L"姓名", LVCFMT_LEFT, 45);
	m_list1.InsertColumn(1, L"存款金额", LVCFMT_LEFT, 60);
	m_list1.InsertColumn(2, L"存款时间", LVCFMT_LEFT, 140);
	m_list2.InsertColumn(0, L"姓名", LVCFMT_LEFT, 45);
	m_list2.InsertColumn(1, L"取款金额", LVCFMT_LEFT, 60);
	m_list2.InsertColumn(2, L"取款时间", LVCFMT_LEFT, 140);
	m_list1.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_list2.SetExtendedStyle(LVS_EX_GRIDLINES);
	COleDateTime time = COleDateTime::GetCurrentTime();
	int t = time.GetHour();
	CString hello;
	if (t > 6 && t < 11)
	{
		hello = L"上午好！";
	}
	else if (t >= 11 && t < 14)
	{
		hello = L"中午好！";
	}
	else if (t >= 14 && t < 18)
	{
		hello = L"下午好！";
	}
	else if (t >= 18 && t < 24 || t >= 0 && t < 6)
	{
		hello = L"晚上好！";
	}
	CFont font;
	font.CreatePointFont(80, L"黑体");
	GetDlgItem(IDC_MESSAGE)->SetFont(&font);
	temp.Format(L"%s%s您当前余额为：%.2lf元", hello, cus.name, cus.money);
	GetDlgItem(IDC_MESSAGE)->SetWindowText(temp);
	//下面插入操作历史操作记录
	for (int i = 0; i < 20; i++)
	{
		if (!cus.dipositHistory[i].IsEmpty())//记录不为空，则插入记录
		{
			m_list1.InsertItem(i, cus.name);
			m_list1.SetItemText(i, 1, cus.dipositHistory[i].Mid(cus.dipositHistory[i].Find(L"款") + 1, cus.dipositHistory[i].Find(L"元")));//插入存款金额
			m_list1.SetItemText(i, 2, cus.dipositHistory[i].Mid(cus.dipositHistory[i].Find(L"于") +1, cus.dipositHistory[i].FindOneOf(L"于") + 10)); //插入存款时间
		}
		if (!cus.fetchHistory[i].IsEmpty())//记录不为空，则插入记录
		{
			m_list2.InsertItem(i, cus.name);
			m_list2.SetItemText(i, 1, cus.fetchHistory[i].Mid(cus.fetchHistory[i].Find(L"款") + 1, cus.fetchHistory[i].Find(L"元")));//插入存款金额
			m_list2.SetItemText(i, 2, cus.fetchHistory[i].Mid(cus.fetchHistory[i].Find(L"于") + 1, cus.fetchHistory[i].FindOneOf(L"于") + 10)); //插入存款时间
		}
	}
	return TRUE;
}
