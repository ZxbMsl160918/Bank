// AllHistory.cpp: 实现文件
//

#include "stdafx.h"
#include "Bank.h"
#include "AllHistory.h"
#include "afxdialogex.h"


// AllHistory 对话框

IMPLEMENT_DYNAMIC(AllHistory, CDialogEx)

AllHistory::AllHistory(Consumer *c, int cusCount, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADMINHISTORY, pParent), cus(c)
{
	this->cusCount = cusCount;
	countPos = 0;
	nPos = 0;
}

AllHistory::~AllHistory()
{
}

void AllHistory::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_LISTALL, m_list);
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AllHistory, CDialogEx)

	ON_NOTIFY(NM_CLICK, IDC_LISTALL, &AllHistory::OnClickListall)
	ON_BN_CLICKED(IDC_BUTTON1, &AllHistory::OnBnClickedButton1)
END_MESSAGE_MAP()


// AllHistory 消息处理程序


BOOL AllHistory::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString temp;
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
	temp.Format(L"%s管理员，所有用户信息如下，您可以随意删除记录！", hello);
	GetDlgItem(IDC_MSG)->SetWindowText(temp);
	m_list.InsertColumn(0, L"记录一览表", LVCFMT_CENTER, 430);
	m_list.SetExtendedStyle(1|LVS_EX_CHECKBOXES);
	int insertCount = 0;//现在应该插入哪一行
	for (int i = 0; i < cusCount; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (!cus[i].dipositHistory[j].IsEmpty())
			{
				m_list.InsertItem(insertCount++, cus[i].dipositHistory[j]); pos[nPos].i = i;
				pos[nPos].j = j;
				pos[nPos].type = TRUE;
				nPos++;
			}
			if (!cus[i].fetchHistory[j].IsEmpty())
			{
				m_list.InsertItem(insertCount++, cus[i].fetchHistory[j]); pos[nPos].i = i;
				pos[nPos].j = j;
				pos[nPos].type = FALSE;
				nPos++;
			}
		}
	}
	return TRUE;
}



void AllHistory::OnClickListall(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	DWORD dwPos = GetMessagePos();//获取光标在整个屏幕位置
	CPoint pt(dwPos);
	m_list.ScreenToClient(&pt);//屏幕位置变为对话框相对位置
	UINT nFlag;
	int nItem = m_list.HitTest(pt, &nFlag);//获取选中哪一项 返回参数pHitTestInfo指定位置的项的索引
	if (nFlag == LVHT_ONITEMSTATEICON)
	{
		BOOL bCheckState = m_list.GetCheck(nItem);
		if (bCheckState)//勾选为false,不勾为true
		{
			for (int i = nItem; i < countPos - 1; i++)
			{
				Count[i] = Count[i + 1];
				countPos--;
			}
		}
		else//勾选
		{
			Count[countPos++] = nItem;
		}
	}
	*pResult = 0;
}


void AllHistory::OnBnClickedButton1()
{
	if (countPos == 0)
	{
		AfxMessageBox(L"您还没有选中需要删除项！");
		return;
	}
	if (AfxMessageBox(L"确定删除选中？", MB_YESNO) == IDYES)
	{
		for (int i = 0; i < countPos; i++)
		{
			if (pos[Count[i]].type == TRUE)
			{
				cus[pos[Count[i]].i].dipositHistory[pos[Count[i]].j] = L"";//记录置为空
			}
			else
			{
				cus[pos[Count[i]].i].fetchHistory[pos[Count[i]].j] = L"";//记录置为空
			}
		}
		AfxMessageBox(L"记录删除成功！");
		EndDialog(IDD_ADMINHISTORY);
	}
}
