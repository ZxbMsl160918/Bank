// ModifyUsr.cpp: 实现文件
//

#include "stdafx.h"
#include "Bank.h"
#include "ModifyUsr.h"
#include "afxdialogex.h"


// ModifyUsr 对话框

IMPLEMENT_DYNAMIC(ModifyUsr, CDialogEx)

ModifyUsr::ModifyUsr(Consumer* c, int count, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODIFY, pParent), cus(c), cusCount(count)
{
	m_Row = m_Col = -1;
	judge = FALSE;
}

ModifyUsr::~ModifyUsr()
{
}

void ModifyUsr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MODIFYEDIT, m_list);
	DDX_Control(pDX, IDC_TEMPEDIT, m_edit);
}


BEGIN_MESSAGE_MAP(ModifyUsr, CDialogEx)
	ON_BN_CLICKED(IDOK, &ModifyUsr::OnBnClickedOk)
	ON_NOTIFY(NM_DBLCLK, IDC_MODIFYEDIT, &ModifyUsr::OnDblclkModifyedit)
	ON_EN_KILLFOCUS(IDC_TEMPEDIT, &ModifyUsr::OnKillfocusTempedit)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// ModifyUsr 消息处理程序


void ModifyUsr::OnBnClickedOk()
{
	
}


void ModifyUsr::OnDblclkModifyedit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CRect rc;
	m_Row = pNMListView->iItem;//获得选中的行  
	m_Col = pNMListView->iSubItem;//获得选中列  
	if (m_Col != -1) //如果选择的不是空白处;  
	{
		m_list.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);//获得子项的RECT；  
		m_edit.SetParent(&m_list);//转换坐标为列表框中的坐标  
		m_edit.MoveWindow(rc);//移动Edit到RECT坐在的位置;  
		str = m_list.GetItemText(m_Row, m_Col);//获取当前的项中的字符串
		m_edit.SetWindowText(str);//将该子项中的值放在Edit控件中；  
		m_edit.ShowWindow(SW_SHOW);//显示Edit控件；  
		m_edit.SetFocus();//设置Edit焦点  
		m_edit.ShowCaret();//显示光标  
		m_edit.SetSel(-1);//将光标移动到最后  
	}
	*pResult = 0;
}


BOOL ModifyUsr::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_edit.ShowWindow(SW_HIDE);
	m_list.InsertColumn(0, L"卡号", LVCFMT_CENTER, 90);
	m_list.InsertColumn(1, L"姓名", LVCFMT_CENTER, 75);
	m_list.InsertColumn(2, L"余额", LVCFMT_CENTER, 85);
	m_list.InsertColumn(3, L"身份证", LVCFMT_CENTER, 90);
	m_list.InsertColumn(4, L"地址", LVCFMT_CENTER, 90);
	m_list.InsertColumn(5, L"电话", LVCFMT_CENTER, 90);
	m_list.InsertColumn(6, L"密码", LVCFMT_CENTER, 85);
	m_list.InsertColumn(7, L"使用状态", LVCFMT_CENTER, 70);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle()| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//m_list.SetBkColor(RGB(238, 238, 209));
	//m_list.SetTextBkColor(RGB(238, 238, 209));
	CString temp;
	for (int i = 0; i < cusCount; i++)
	{
		m_list.InsertItem(i, cus[i].cardNumber);
		m_list.SetItemText(i, 1, cus[i].name);
		temp.Format(L"%.2lf", cus[i].money);
		m_list.SetItemText(i, 2, temp);
		m_list.SetItemText(i, 3, cus[i].id);
		m_list.SetItemText(i, 4, cus[i].addr);
		m_list.SetItemText(i, 5, cus[i].phone);
		m_list.SetItemText(i, 6, cus[i].usrPwd);
		if (cus[i].errCount > 3)//输入密码错误大于3则冻结
		{
			m_list.SetItemText(i, 7, L"冻结");
		}
		else
		{
			m_list.SetItemText(i, 7, L"正常");
		}
	}
	return TRUE;  
}


void ModifyUsr::OnKillfocusTempedit()
{
	CString temp;
	m_edit.GetWindowText(temp);    //得到用户输入的新的内容 
	if (temp.Find(L".") != -1)
	{
		temp.Format(L"%.2lf", _wtof(temp));
	}
	if (m_Col == 7)//判断第七列的输入内容是否是正常或冻结
	{
		if (temp != L"冻结" && temp != L"正常")
		{
			AfxMessageBox(L"用户状态只能为“冻结”或“正常”！");
			m_edit.SetFocus();
			return;
		}
	}
	if (temp != str)//如果修改过了内容
	{
		judge = TRUE;
	}
	m_list.SetItemText(m_Row, m_Col, temp);   //设置编辑框的新内容  
	m_edit.ShowWindow(SW_HIDE);                //应藏编辑框  
	m_Col = -1;
}


void ModifyUsr::OnClose()
{
	if (judge)//修改了内容更新数组
	{
		if (AfxMessageBox(L"是否保存更改？", MB_YESNO) == IDNO)
			EndDialog(IDD_MODIFY);
		else
		{
			CString state;//用户状态
			for (int i = 0; i < cusCount; i++)//纠结统一更新，还是边改变更新
			{
				cus[i].cardNumber = m_list.GetItemText(i, 0);
				cus[i].name = m_list.GetItemText(i, 1);
				cus[i].money = _wtof(m_list.GetItemText(i, 2));
				cus[i].id = m_list.GetItemText(i, 3);
				cus[i].addr = m_list.GetItemText(i, 4);
				cus[i].phone = m_list.GetItemText(i, 5);
				cus[i].usrPwd = m_list.GetItemText(i, 6);
				cus[i].confirmUsrPwd = cus[i].usrPwd;
				state = m_list.GetItemText(i, 7);
				//如果用户状态为“冻结”则设置cerrCount > 3
				if (state == L"冻结")
				{
					cus[i].errCount = 4;
				}
				else if (state == L"正常")
				{
					cus[i].errCount = 0;
				}
			}
		}
	}
	CDialogEx::OnClose();
}


void ModifyUsr::OnOK()
{
	CString temp;
	m_edit.GetWindowText(temp);    //得到用户输入的新的内容 
	if (temp.Find(L".") != -1)
	{
		temp.Format(L"%.2lf", _wtof(temp));
	}
	if (m_Col == 7)//判断第七列的输入内容是否是正常或冻结
	{
		if (temp != L"冻结" && temp != L"正常")
		{
			AfxMessageBox(L"用户状态只能为“冻结”或“正常”！");
			m_edit.SetFocus();
			return;
		}
	}
	if (temp != str)//如果修改过了内容
	{
		judge = TRUE;
	}
	m_list.SetItemText(m_Row, m_Col, temp);   //设置编辑框的新内容  
	m_edit.ShowWindow(SW_HIDE);                //应藏编辑框  
}


BOOL ModifyUsr::PreTranslateMessage(MSG* pMsg)
{
	if (m_Col != -1)
	{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN: //Enter按键事件  
			OnOK();
		default:break;
		}
	}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
