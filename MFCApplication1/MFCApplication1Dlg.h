
// MFCApplication1Dlg.h: 헤더 파일
//

#pragma once
#include "inputNameDlg.h"

// CMFCApplication1Dlg 대화 상자
class CMFCApplication1Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_left_list;
	CListBox m_right_list;
	void DirToList(CListBox* ap_list_box, CString a_path);
	afx_msg void OnLbnDblclkLeftList();
	afx_msg void OnLbnDblclkRightList();
	void ChangeDir(CListBox * ap_list_box, int a_path_ctrl_id);
	afx_msg void OnBnClickedRCreateDirBtn();
	afx_msg void OnLbnSelchangeLeftList();
	afx_msg void OnBnClickedLToRCopyBtn();
	afx_msg void OnBnClickedOpenDirBtn();
	afx_msg void OnBnClickedRDleBtn();
};
