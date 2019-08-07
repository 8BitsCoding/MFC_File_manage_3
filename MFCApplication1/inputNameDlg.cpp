// inputNameDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "inputNameDlg.h"
#include "afxdialogex.h"


// inputNameDlg 대화 상자

IMPLEMENT_DYNAMIC(inputNameDlg, CDialogEx)

inputNameDlg::inputNameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INPUT_NAME_DLG, pParent)
{

}

inputNameDlg::~inputNameDlg()
{
}

void inputNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(inputNameDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &inputNameDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// inputNameDlg 메시지 처리기


void inputNameDlg::OnBnClickedOk()
{
	if(GetDlgItemText(IDC_NAME_EDIT, m_name) > 0) CDialogEx::OnOK();

}
