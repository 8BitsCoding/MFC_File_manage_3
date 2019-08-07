#pragma once


// inputNameDlg 대화 상자

class inputNameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(inputNameDlg)

public:
	inputNameDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~inputNameDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUT_NAME_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_name;

	const wchar_t * GetName() { return m_name; }
};
