
// convertDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "convert.h"
#include "convertDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CconvertDlg �Ի���

int state=-1;//���ⷴ�������ı����ݵ���Ӧ����������������ѭ��������state�������ƣ�0��������HEX->BIN�����У�1��������BIN->HEX�����У�-1����ȴ�״̬


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


// CconvertDlg ��Ϣ�������

BOOL CconvertDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CconvertDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CconvertDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CconvertDlg::OnBnClickedBexit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}

void CconvertDlg::OnEnChangeEhexh()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
