
// convertDlg.h : ͷ�ļ�
//

#pragma once


// CconvertDlg �Ի���
class CconvertDlg : public CDialogEx
{
// ����
public:
	CconvertDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CONVERT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBexit();
	afx_msg void OnEnChangeEhexh();
	afx_msg void OnEnChangeEhexl();
	afx_msg void OnEnChangeEbin7();
	afx_msg void OnEnChangeEbin6();
	afx_msg void OnEnChangeEbin5();
	afx_msg void OnEnChangeEbin4();
	afx_msg void OnEnChangeEbin3();
	afx_msg void OnEnChangeEbin2();
	afx_msg void OnEnChangeEbin1();
	afx_msg void OnEnChangeEbin0();
};
