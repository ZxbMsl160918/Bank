// Draw.cpp: 实现文件
//

#include "stdafx.h"
#include "Bank.h"
#include "Draw.h"
#include "elseMoney.h"
#include "afxdialogex.h"


// Draw 对话框

IMPLEMENT_DYNAMIC(Draw, CDialogEx)

Draw::Draw(Consumer c,int count, Consumer *arrayc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DRAW, pParent)
{
	cus = arrayc;
	cusCount = count;
	nowCus = c;
	depositMoney = 0;
	drawMoney = 0;
}

Draw::~Draw()
{
}

void Draw::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Draw, CDialogEx)
	ON_BN_CLICKED(IDOK, &Draw::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &Draw::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &Draw::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &Draw::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON3, &Draw::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &Draw::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON7, &Draw::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON6, &Draw::OnBnClickedButton6)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDPAY, &Draw::OnBnClickedOk2)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// Draw 消息处理程序


BOOL Draw::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString money;
	money.Format(L"%.2lf", nowCus.money);
	SetDlgItemText(IDC_YUE, money);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Draw::OnBnClickedOk()
{
	CString money;
	GetDlgItemText(IDC_EDIT1, money);
	if (money.IsEmpty())
	{
		AfxMessageBox(L"请输入存款金额！");
		return;
	}
	int dm = depositMoney = _wtof(money);
	if (dm%100)
	{
		AfxMessageBox(L"您必须存入面值为100的人民币！");
		depositMoney = 0;
		return;
	}
	CString str;//目前的时间
	COleDateTime time = COleDateTime::GetCurrentTime();//获取当前时间
	str.Format(L"%d年%d月%d日%d时%d分%d秒", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	nowCus.dipositHistory[nowCus.dpos++] = L"用户：" + nowCus.name + L"于" + str + L"存款" + money + L"元";
	AfxMessageBox(L"存款成功！");
	EndDialog(IDD_DRAW);
}


void Draw::OnBnClickedButton1()
{
	if (AfxMessageBox(L"确认取款100元吗？", MB_YESNO, MB_ICONQUESTION) == IDYES)
	{
		if (nowCus.money < 100)
		{
			AfxMessageBox(L"您的余额不足！");
			return;
		}
		drawMoney = 100;
		CString str;//目前的时间
		COleDateTime time = COleDateTime::GetCurrentTime();//获取当前时间
		str.Format(L"%d年%d月%d日%d时%d分%d秒", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
		nowCus.fetchHistory[nowCus.fpos++] = L"用户：" + nowCus.name + L"于" + str + L"取款100元";
		AfxMessageBox(L"取款成功！");
		OnBnClickedButton7();
	}
}


void Draw::OnBnClickedButton4()
{
	if (AfxMessageBox(L"确认取款300元吗？", MB_YESNO, MB_ICONQUESTION) == IDYES)
	{
		if (nowCus.money < 300)
		{
			AfxMessageBox(L"您的余额不足！");
			return;
		}
		drawMoney =300;
		CString str;//目前的时间
		COleDateTime time = COleDateTime::GetCurrentTime();//获取当前时间
		str.Format(L"%d年%d月%d日%d时%d分%d秒", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
		nowCus.fetchHistory[nowCus.fpos++] = L"用户：" + nowCus.name + L"于" + str + L"取款300元";
		AfxMessageBox(L"取款成功！");
		OnBnClickedButton7();
	}
}


void Draw::OnBnClickedButton5()
{
	if (AfxMessageBox(L"确认取款500元吗？", MB_YESNO, MB_ICONQUESTION) == IDYES)
	{
		if (nowCus.money < 500)
		{
			AfxMessageBox(L"您的余额不足！");
			return;
		}
		drawMoney = 500;
		CString str;//目前的时间
		COleDateTime time = COleDateTime::GetCurrentTime();//获取当前时间
		str.Format(L"%d年%d月%d日%d时%d分%d秒", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
		nowCus.fetchHistory[nowCus.fpos++] = L"用户：" + nowCus.name + L"于" + str + L"取款500元";
		AfxMessageBox(L"取款成功！");
		OnBnClickedButton7();
	}
}


void Draw::OnBnClickedButton3()
{
	if (AfxMessageBox(L"确认取款1000元吗？", MB_YESNO, MB_ICONQUESTION) == IDYES)
	{
		if (nowCus.money < 1000)
		{
			AfxMessageBox(L"您的余额不足！");
			return;
		}
		drawMoney = 1000;
		CString str;//目前的时间
		COleDateTime time = COleDateTime::GetCurrentTime();//获取当前时间
		str.Format(L"%d年%d月%d日%d时%d分%d秒", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
		nowCus.fetchHistory[nowCus.fpos++] = L"用户：" + nowCus.name + L"于" + str + L"取款1000元";
		AfxMessageBox(L"取款成功！");
		OnBnClickedButton7();
	}
}


void Draw::OnBnClickedButton2()
{
	if (AfxMessageBox(L"确认取款2000元吗？", MB_YESNO, MB_ICONQUESTION) == IDYES)
	{
		if (nowCus.money < 2000)
		{
			AfxMessageBox(L"您的余额不足！");
			return;
		}
		drawMoney = 2000;
		CString str;//目前的时间
		COleDateTime time = COleDateTime::GetCurrentTime();//获取当前时间
		str.Format(L"%d年%d月%d日%d时%d分%d秒", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
		nowCus.fetchHistory[nowCus.fpos++] = L"用户：" + nowCus.name + L"于" + str + L"取款2000元";
		AfxMessageBox(L"取款成功！");
		OnBnClickedButton7();
	}
}


void Draw::OnBnClickedButton7()
{
	EndDialog(IDD_DRAW);
}


void Draw::OnBnClickedButton6()
{
	elseMoney em(&drawMoney, nowCus.money);
	em.DoModal();
	if (drawMoney > 0)
	{
		CString str;//目前的时间
		CString m;
		m.Format(L"%.0lf", drawMoney);
		COleDateTime time = COleDateTime::GetCurrentTime();//获取当前时间
		str.Format(L"%d年%d月%d日%d时%d分%d秒", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
		nowCus.fetchHistory[nowCus.fpos++] = L"用户：" + nowCus.name + L"于" + str + L"取款" + m + L"元";
	}
	OnBnClickedButton7();
}


void Draw::OnDestroy()
{
	nowCus.money += depositMoney;
	nowCus.money -= drawMoney;
	CDialogEx::OnDestroy();
}


void Draw::OnBnClickedOk2()
{
	CString payCard;//转账账户
	CString payMoney;//转账金额
	GetDlgItemText(IDC_PAYCARD, payCard);
	GetDlgItemText(IDC_PAYMONEY, payMoney);
	if (payCard.IsEmpty())
	{
		AfxMessageBox(L"请输入对方账户！");
		return;
	}
	if (payMoney.IsEmpty())
	{
		AfxMessageBox(L"请转账金额！");
		return;
	}
	if (nowCus.money < _wtof(payMoney))
	{
		AfxMessageBox(L"余额不足！");
		return;
	}
	int i;
	for (i = 0; i < cusCount; i++)//寻找对应的账户
	{
		if (cus[i].cardNumber == payCard)
		{
			break;
		}
	}
	if (i > cusCount)//未找到
	{
		AfxMessageBox(L"未找到转账账户，请重新输入！");
		return;
	}
	double money = _wtof(payMoney);
	cus[i].money += money;//转账用户加钱
	nowCus.money -= money;//被转账用户减钱
	AfxMessageBox(L"转账成功！");
}


void Draw::OnClose()
{
	
	CDialogEx::OnClose();
}
