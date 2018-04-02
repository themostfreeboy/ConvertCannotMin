
// convertDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "convert.h"
#include "convertDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CconvertDlg 对话框

int state=-1;//避免反复触发改变内容的响应函数，导致陷入死循环，引入state变量控制：0代表正在HEX->BIN过程中；1代表正在BIN->HEX过程中；-1代表等待状态


CconvertDlg::CconvertDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CconvertDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CconvertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CconvertDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BEXIT, &CconvertDlg::OnBnClickedBexit)
	ON_EN_CHANGE(IDC_EHEXH, &CconvertDlg::OnEnChangeEhexh)
	ON_EN_CHANGE(IDC_EHEXL, &CconvertDlg::OnEnChangeEhexl)
	ON_EN_CHANGE(IDC_EBIN7, &CconvertDlg::OnEnChangeEbin7)
	ON_EN_CHANGE(IDC_EBIN6, &CconvertDlg::OnEnChangeEbin6)
	ON_EN_CHANGE(IDC_EBIN5, &CconvertDlg::OnEnChangeEbin5)
	ON_EN_CHANGE(IDC_EBIN4, &CconvertDlg::OnEnChangeEbin4)
	ON_EN_CHANGE(IDC_EBIN3, &CconvertDlg::OnEnChangeEbin3)
	ON_EN_CHANGE(IDC_EBIN2, &CconvertDlg::OnEnChangeEbin2)
	ON_EN_CHANGE(IDC_EBIN1, &CconvertDlg::OnEnChangeEbin1)
	ON_EN_CHANGE(IDC_EBIN0, &CconvertDlg::OnEnChangeEbin0)
END_MESSAGE_MAP()


// CconvertDlg 消息处理程序

BOOL CconvertDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	state=-1;
	SetDlgItemText(IDC_EHEXH,_T("0"));
	SetDlgItemText(IDC_EHEXL,_T("0"));
	SetDlgItemText(IDC_EBIN7,_T("0"));
	SetDlgItemText(IDC_EBIN6,_T("0"));
	SetDlgItemText(IDC_EBIN5,_T("0"));
	SetDlgItemText(IDC_EBIN4,_T("0"));
	SetDlgItemText(IDC_EBIN3,_T("0"));
	SetDlgItemText(IDC_EBIN2,_T("0"));
	SetDlgItemText(IDC_EBIN1,_T("0"));
	SetDlgItemText(IDC_EBIN0,_T("0"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CconvertDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CconvertDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CconvertDlg::OnBnClickedBexit()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}

void CconvertDlg::OnEnChangeEhexh()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if(state==1)	return;
	state=0;
	CString cstr=_T("");
	CString cstr_temp=_T("");
	int bit_temp=0;
	GetDlgItemText(IDC_EHEXH,cstr);
	int n=cstr.GetLength();
	char ch=cstr.GetAt(0);
	if(n==0)
	{
		SetDlgItemText(IDC_EBIN7,_T("0"));
		SetDlgItemText(IDC_EBIN6,_T("0"));
		SetDlgItemText(IDC_EBIN5,_T("0"));
		SetDlgItemText(IDC_EBIN4,_T("0"));
		SetDlgItemText(IDC_EHEXH,_T("0"));
	}
	else if(n==1)
	{
		hexh:
		if((ch>='A')&&(ch<='F'))
		{
			ch+=32;//'A'-'F'==>'a'-'f'
			cstr_temp.Format(_T("%c"),ch);
			SetDlgItemText(IDC_EHEXH,cstr_temp);
		}
		if((ch>='a')&&(ch<='f'))
		{
			ch-=87;//'a'-'f'==>10-15
		}
		else if((ch>='0')&&(ch<='9'))
		{
			ch-=48;//'0'-'9'==>0-9
		}
		else
		{
			SetDlgItemText(IDC_EHEXH,_T("0"));
			SetDlgItemText(IDC_EBIN7,_T("0"));
			SetDlgItemText(IDC_EBIN6,_T("0"));
			SetDlgItemText(IDC_EBIN5,_T("0"));
			SetDlgItemText(IDC_EBIN4,_T("0"));
			state=-1;
			return;
		}
		bit_temp=(ch>>3)&(0x01);
		cstr_temp.Format(_T("%d"),bit_temp);
		SetDlgItemText(IDC_EBIN7,cstr_temp);
		bit_temp=(ch>>2)&(0x01);
		cstr_temp.Format(_T("%d"),bit_temp);
		SetDlgItemText(IDC_EBIN6,cstr_temp);
		bit_temp=(ch>>1)&(0x01);
		cstr_temp.Format(_T("%d"),bit_temp);
		SetDlgItemText(IDC_EBIN5,cstr_temp);
		bit_temp=(ch)&(0x01);
		cstr_temp.Format(_T("%d"),bit_temp);
		SetDlgItemText(IDC_EBIN4,cstr_temp);
	}
	else
	{
		ch=cstr.GetAt(0);
		n=1;
		cstr_temp.Format(_T("%c"),ch);
		SetDlgItemText(IDC_EHEXH,cstr_temp);
		goto hexh;
	}
	state=-1;
}

void CconvertDlg::OnEnChangeEhexl()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if(state==1)	return;
	CString cstr=_T("");
	CString cstr_temp=_T("");
	int bit_temp=0;
	GetDlgItemText(IDC_EHEXL,cstr);
	int n=cstr.GetLength();
	char ch=cstr.GetAt(0);
	if(n==0)
	{
		SetDlgItemText(IDC_EBIN3,_T("0"));
		SetDlgItemText(IDC_EBIN2,_T("0"));
		SetDlgItemText(IDC_EBIN1,_T("0"));
		SetDlgItemText(IDC_EBIN0,_T("0"));
		SetDlgItemText(IDC_EHEXL,_T("0"));
	}
	else if(n==1)
	{
		hexl:
		if((ch>='A')&&(ch<='F'))
		{
			ch+=32;//'A'-'F'==>'a'-'f'
			cstr_temp.Format(_T("%c"),ch);
			SetDlgItemText(IDC_EHEXL,cstr_temp);
		}
		if((ch>='a')&&(ch<='f'))
		{
			ch-=87;//'a'-'f'==>10-15
		}
		else if((ch>='0')&&(ch<='9'))
		{
			ch-=48;//'0'-'9'==>0-9
		}
		else
		{
			SetDlgItemText(IDC_EHEXL,_T("0"));
			SetDlgItemText(IDC_EBIN3,_T("0"));
			SetDlgItemText(IDC_EBIN2,_T("0"));
			SetDlgItemText(IDC_EBIN1,_T("0"));
			SetDlgItemText(IDC_EBIN0,_T("0"));
			state=-1;
			return;
		}
		bit_temp=(ch>>3)&(0x01);
		cstr_temp.Format(_T("%d"),bit_temp);
		SetDlgItemText(IDC_EBIN3,cstr_temp);
		bit_temp=(ch>>2)&(0x01);
		cstr_temp.Format(_T("%d"),bit_temp);
		SetDlgItemText(IDC_EBIN2,cstr_temp);
		bit_temp=(ch>>1)&(0x01);
		cstr_temp.Format(_T("%d"),bit_temp);
		SetDlgItemText(IDC_EBIN1,cstr_temp);
		bit_temp=(ch)&(0x01);
		cstr_temp.Format(_T("%d"),bit_temp);
		SetDlgItemText(IDC_EBIN0,cstr_temp);
	}
	else
	{
		ch=cstr.GetAt(0);
		n=1;
		cstr_temp.Format(_T("%c"),ch);
		SetDlgItemText(IDC_EHEXL,cstr_temp);
		goto hexl;
	}
	state=-1;
}

void CconvertDlg::OnEnChangeEbin7()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if(state==0)	return;
	state=1;
	CString cstr=_T("");
	CString cstr_temp=_T("");
	int bit_temp=0;
	GetDlgItemText(IDC_EBIN7,cstr);
	int n=cstr.GetLength();
	char ch=cstr.GetAt(0);
	if(n==0)
	{
		SetDlgItemText(IDC_EBIN7,_T("0"));
		ch='0';
		goto bin7;
	}
	else if(n==1)
	{
		bin7:
		if(ch=='0'||ch=='1')
		{
			ch-=48;//'0'-'1'==>0-1
		}
		else
		{
			SetDlgItemText(IDC_EBIN7,_T("0"));
		}
		GetDlgItemText(IDC_EBIN7,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN6,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN5,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN4,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		if((bit_temp>=0)&&(bit_temp<=9))
		{
			cstr_temp.Format(_T("%c"),bit_temp+48);//0-9==>'0'-'9'
		}
		else if((bit_temp>=10)&&(bit_temp<=15))
		{
			cstr_temp.Format(_T("%c"),bit_temp+87);//10-15==>'a'-'f'
		}
		SetDlgItemText(IDC_EHEXH,cstr_temp);
	}
	else
	{
		ch=cstr.GetAt(0);
		n=1;
		cstr_temp.Format(_T("%c"),ch);
		SetDlgItemText(IDC_EBIN7,cstr_temp);
		goto bin7;
	}
	state=-1;
}

void CconvertDlg::OnEnChangeEbin6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if(state==0)	return;
	state=1;
	CString cstr=_T("");
	CString cstr_temp=_T("");
	int bit_temp=0;
	GetDlgItemText(IDC_EBIN6,cstr);
	int n=cstr.GetLength();
	char ch=cstr.GetAt(0);
	if(n==0)
	{
		SetDlgItemText(IDC_EBIN6,_T("0"));
		ch='0';
		goto bin6;
	}
	else if(n==1)
	{
		bin6:
		if(ch=='0'||ch=='1')
		{
			ch-=48;//'0'-'1'==>0-1
		}
		else
		{
			SetDlgItemText(IDC_EBIN6,_T("0"));
		}
		GetDlgItemText(IDC_EBIN7,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN6,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN5,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN4,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		if((bit_temp>=0)&&(bit_temp<=9))
		{
			cstr_temp.Format(_T("%c"),bit_temp+48);//0-9==>'0'-'9'
		}
		else if((bit_temp>=10)&&(bit_temp<=15))
		{
			cstr_temp.Format(_T("%c"),bit_temp+87);//10-15==>'a'-'f'
		}
		SetDlgItemText(IDC_EHEXH,cstr_temp);
	}
	else
	{
		ch=cstr.GetAt(0);
		n=1;
		cstr_temp.Format(_T("%c"),ch);
		SetDlgItemText(IDC_EBIN6,cstr_temp);
		goto bin6;
	}
	state=-1;
}

void CconvertDlg::OnEnChangeEbin5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if(state==0)	return;
	state=1;
	CString cstr=_T("");
	CString cstr_temp=_T("");
	int bit_temp=0;
	GetDlgItemText(IDC_EBIN5,cstr);
	int n=cstr.GetLength();
	char ch=cstr.GetAt(0);
	if(n==0)
	{
		SetDlgItemText(IDC_EBIN5,_T("0"));
		ch='0';
		goto bin5;
	}
	else if(n==1)
	{
		bin5:
		if(ch=='0'||ch=='1')
		{
			ch-=48;//'0'-'1'==>0-1
		}
		else
		{
			SetDlgItemText(IDC_EBIN5,_T("0"));
		}
		GetDlgItemText(IDC_EBIN7,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN6,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN5,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN4,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		if((bit_temp>=0)&&(bit_temp<=9))
		{
			cstr_temp.Format(_T("%c"),bit_temp+48);//0-9==>'0'-'9'
		}
		else if((bit_temp>=10)&&(bit_temp<=15))
		{
			cstr_temp.Format(_T("%c"),bit_temp+87);//10-15==>'a'-'f'
		}
		SetDlgItemText(IDC_EHEXH,cstr_temp);
	}
	else
	{
		ch=cstr.GetAt(0);
		n=1;
		cstr_temp.Format(_T("%c"),ch);
		SetDlgItemText(IDC_EBIN5,cstr_temp);
		goto bin5;
	}
	state=-1;
}

void CconvertDlg::OnEnChangeEbin4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if(state==0)	return;
	state=1;
	CString cstr=_T("");
	CString cstr_temp=_T("");
	int bit_temp=0;
	GetDlgItemText(IDC_EBIN4,cstr);
	int n=cstr.GetLength();
	char ch=cstr.GetAt(0);
	if(n==0)
	{
		SetDlgItemText(IDC_EBIN4,_T("0"));
		ch='0';
		goto bin4;
	}
	else if(n==1)
	{
		bin4:
		if(ch=='0'||ch=='1')
		{
			ch-=48;//'0'-'1'==>0-1
		}
		else
		{
			SetDlgItemText(IDC_EBIN4,_T("0"));
		}
		GetDlgItemText(IDC_EBIN7,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN6,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN5,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN4,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		if((bit_temp>=0)&&(bit_temp<=9))
		{
			cstr_temp.Format(_T("%c"),bit_temp+48);//0-9==>'0'-'9'
		}
		else if((bit_temp>=10)&&(bit_temp<=15))
		{
			cstr_temp.Format(_T("%c"),bit_temp+87);//10-15==>'a'-'f'
		}
		SetDlgItemText(IDC_EHEXH,cstr_temp);
	}
	else
	{
		ch=cstr.GetAt(0);
		n=1;
		cstr_temp.Format(_T("%c"),ch);
		SetDlgItemText(IDC_EBIN4,cstr_temp);
		goto bin4;
	}
	state=-1;
}

void CconvertDlg::OnEnChangeEbin3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if(state==0)	return;
	state=1;
	CString cstr=_T("");
	CString cstr_temp=_T("");
	int bit_temp=0;
	GetDlgItemText(IDC_EBIN3,cstr);
	int n=cstr.GetLength();
	char ch=cstr.GetAt(0);
	if(n==0)
	{
		SetDlgItemText(IDC_EBIN3,_T("0"));
		ch='0';
		goto bin3;
	}
	else if(n==1)
	{
		bin3:
		if(ch=='0'||ch=='1')
		{
			ch-=48;//'0'-'1'==>0-1
		}
		else
		{
			SetDlgItemText(IDC_EBIN3,_T("0"));
		}
		GetDlgItemText(IDC_EBIN3,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN2,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN1,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN0,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		if((bit_temp>=0)&&(bit_temp<=9))
		{
			cstr_temp.Format(_T("%c"),bit_temp+48);//0-9==>'0'-'9'
		}
		else if((bit_temp>=10)&&(bit_temp<=15))
		{
			cstr_temp.Format(_T("%c"),bit_temp+87);//10-15==>'a'-'f'
		}
		SetDlgItemText(IDC_EHEXL,cstr_temp);
	}
	else
	{
		ch=cstr.GetAt(0);
		n=1;
		cstr_temp.Format(_T("%c"),ch);
		SetDlgItemText(IDC_EBIN3,cstr_temp);
		goto bin3;
	}
	state=-1;
}

void CconvertDlg::OnEnChangeEbin2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if(state==0)	return;
	state=1;
	CString cstr=_T("");
	CString cstr_temp=_T("");
	int bit_temp=0;
	GetDlgItemText(IDC_EBIN2,cstr);
	int n=cstr.GetLength();
	char ch=cstr.GetAt(0);
	if(n==0)
	{
		SetDlgItemText(IDC_EBIN2,_T("0"));
		ch='0';
		goto bin2;
	}
	else if(n==1)
	{
		bin2:
		if(ch=='0'||ch=='1')
		{
			ch-=48;//'0'-'1'==>0-1
		}
		else
		{
			SetDlgItemText(IDC_EBIN2,_T("0"));
		}
		GetDlgItemText(IDC_EBIN3,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN2,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN1,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN0,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		if((bit_temp>=0)&&(bit_temp<=9))
		{
			cstr_temp.Format(_T("%c"),bit_temp+48);//0-9==>'0'-'9'
		}
		else if((bit_temp>=10)&&(bit_temp<=15))
		{
			cstr_temp.Format(_T("%c"),bit_temp+87);//10-15==>'a'-'f'
		}
		SetDlgItemText(IDC_EHEXL,cstr_temp);
	}
	else
	{
		ch=cstr.GetAt(0);
		n=1;
		cstr_temp.Format(_T("%c"),ch);
		SetDlgItemText(IDC_EBIN2,cstr_temp);
		goto bin2;
	}
	state=-1;
}

void CconvertDlg::OnEnChangeEbin1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if(state==0)	return;
	state=1;
	CString cstr=_T("");
	CString cstr_temp=_T("");
	int bit_temp=0;
	GetDlgItemText(IDC_EBIN1,cstr);
	int n=cstr.GetLength();
	char ch=cstr.GetAt(0);
	if(n==0)
	{
		SetDlgItemText(IDC_EBIN1,_T("0"));
		ch='0';
		goto bin1;
	}
	else if(n==1)
	{
		bin1:
		if(ch=='0'||ch=='1')
		{
			ch-=48;//'0'-'1'==>0-1
		}
		else
		{
			SetDlgItemText(IDC_EBIN1,_T("0"));
		}
		GetDlgItemText(IDC_EBIN3,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN2,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN1,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN0,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		if((bit_temp>=0)&&(bit_temp<=9))
		{
			cstr_temp.Format(_T("%c"),bit_temp+48);//0-9==>'0'-'9'
		}
		else if((bit_temp>=10)&&(bit_temp<=15))
		{
			cstr_temp.Format(_T("%c"),bit_temp+87);//10-15==>'a'-'f'
		}
		SetDlgItemText(IDC_EHEXL,cstr_temp);
	}
	else
	{
		ch=cstr.GetAt(0);
		n=1;
		cstr_temp.Format(_T("%c"),ch);
		SetDlgItemText(IDC_EBIN1,cstr_temp);
		goto bin1;
	}
	state=-1;
}

void CconvertDlg::OnEnChangeEbin0()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if(state==0)	return;
	state=1;
	CString cstr=_T("");
	CString cstr_temp=_T("");
	int bit_temp=0;
	GetDlgItemText(IDC_EBIN0,cstr);
	int n=cstr.GetLength();
	char ch=cstr.GetAt(0);
	if(n==0)
	{
		SetDlgItemText(IDC_EBIN0,_T("0"));
		ch='0';
		goto bin0;
	}
	else if(n==1)
	{
		bin0:
		if(ch=='0'||ch=='1')
		{
			ch-=48;//'0'-'1'==>0-1
		}
		else
		{
			SetDlgItemText(IDC_EBIN0,_T("0"));
		}
		GetDlgItemText(IDC_EBIN3,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN2,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN1,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		GetDlgItemText(IDC_EBIN0,cstr_temp);
		bit_temp=cstr_temp==_T("1")?((bit_temp<<1)+1):(bit_temp<<1);
		if((bit_temp>=0)&&(bit_temp<=9))
		{
			cstr_temp.Format(_T("%c"),bit_temp+48);//0-9==>'0'-'9'
		}
		else if((bit_temp>=10)&&(bit_temp<=15))
		{
			cstr_temp.Format(_T("%c"),bit_temp+87);//10-15==>'a'-'f'
		}
		SetDlgItemText(IDC_EHEXL,cstr_temp);
	}
	else
	{
		ch=cstr.GetAt(0);
		n=1;
		cstr_temp.Format(_T("%c"),ch);
		SetDlgItemText(IDC_EBIN0,cstr_temp);
		goto bin0;
	}
	state=-1;
}
