
// MFCApplication1Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1Dlg 대화 상자



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LEFT_LIST, m_left_list);
	DDX_Control(pDX, IDC_RIGHT_LIST, m_right_list);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_DBLCLK(IDC_LEFT_LIST, &CMFCApplication1Dlg::OnLbnDblclkLeftList)
	ON_LBN_DBLCLK(IDC_RIGHT_LIST, &CMFCApplication1Dlg::OnLbnDblclkRightList)
	ON_BN_CLICKED(IDC_R_CREATE_DIR_BTN, &CMFCApplication1Dlg::OnBnClickedRCreateDirBtn)
	ON_LBN_SELCHANGE(IDC_LEFT_LIST, &CMFCApplication1Dlg::OnLbnSelchangeLeftList)
	ON_BN_CLICKED(IDC_L_TO_R_COPY_BTN, &CMFCApplication1Dlg::OnBnClickedLToRCopyBtn)
	ON_BN_CLICKED(IDC_OPEN_DIR_BTN, &CMFCApplication1Dlg::OnBnClickedOpenDirBtn)
	ON_BN_CLICKED(IDC_R_DLE_BTN, &CMFCApplication1Dlg::OnBnClickedRDleBtn)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	wchar_t temp_path[MAX_PATH];
	int len = GetCurrentDirectory(MAX_PATH, temp_path);	// C:\temp 이런식으로 경로가 들어옴
	temp_path[len++] == '\\';	// C:\temp\로 경로명을 수정
	temp_path[len] == 0;		// 마지막에 NULL넣는 것도 잊지 말기

	SetDlgItemText(IDC_L_PATH_EDIT, temp_path);
	SetDlgItemText(IDC_R_PATH_EDIT, temp_path);

	DirToList(&m_left_list, temp_path);
	DirToList(&m_right_list, temp_path);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication1Dlg::DirToList(CListBox* ap_list_box, CString a_path)
{
	// 기존항목제거
	ap_list_box->ResetContent();

	CString path;
	WIN32_FIND_DATA file_data;
	a_path += L"\\";
	HANDLE h_file_list = FindFirstFile(a_path+L"*.*", &file_data);
	if (h_file_list != INVALID_HANDLE_VALUE) {
		do {
			//if (!(file_data.cFileName[0] == '.' && file_data.cFileName[1] == 0)) {// *.* 티렉토리 제외하기
				path = file_data.cFileName;
				if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) path = L"[" + path + L"]";
				ap_list_box->InsertString(-1, path);
			//}
		} while (FindNextFile(h_file_list, &file_data));
		FindClose(h_file_list);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCApplication1Dlg::ChangeDir(CListBox * ap_list_box, int a_path_ctrl_id)
{
	CString str, path;
	int index = ap_list_box->GetCurSel();

	ap_list_box->GetText(index, str);
	if (str[0] == '[') {		// 디렉터리
		GetDlgItemText(a_path_ctrl_id, path);
		str.TrimLeft('[');
		str.TrimRight(']');

		if (str == L"..") {
			// ex. c:\temp\aa -> c:\temp\

			path.TrimRight('\\');
			int pos = path.ReverseFind('\\');
			path.Delete(pos + 1, path.GetLength() - pos - 1);
		}
		else {
			// ex. c:\temp\ + aa -> c:\temp\aa

			path += L"\\";
			path += str;

			// ex. c:\temp\aa -> c:\temp\aa\

			//path += L"\\";
		}
		SetDlgItemText(a_path_ctrl_id, path);
		DirToList(ap_list_box, path);
	}
}

void CMFCApplication1Dlg::OnLbnDblclkLeftList()
{
	ChangeDir(&m_left_list, IDC_L_PATH_EDIT);
}


void CMFCApplication1Dlg::OnLbnDblclkRightList()
{
	ChangeDir(&m_right_list, IDC_R_PATH_EDIT);
}


void CMFCApplication1Dlg::OnBnClickedRCreateDirBtn()
{
	inputNameDlg ins_dlg;
	if (IDOK == ins_dlg.DoModal()) {
		CString path;
		GetDlgItemText(IDC_R_PATH_EDIT, path);
		CreateDirectory(path+ins_dlg.GetName(), NULL);

		DirToList(&m_right_list, path);
	}
}


void CMFCApplication1Dlg::OnLbnSelchangeLeftList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCApplication1Dlg::OnBnClickedLToRCopyBtn()
{
	int index = m_left_list.GetCurSel();
	if (index != LB_ERR) {
		CString name, src_path, dest_path;
		m_left_list.GetText(index, name);
		if (name[0] == '[') {
			// 디렉터리는 복사하지 않음
			MessageBox(L"디렉토리는 복사할 수 없습니다.", L"복사 실패", MB_ICONSTOP|MB_OK);
		}
		else {
			GetDlgItemText(IDC_L_PATH_EDIT, src_path);
			GetDlgItemText(IDC_R_PATH_EDIT, dest_path);
			CopyFile(src_path +L"\\" + name, dest_path + L"\\" + name, FALSE);
			// 마지막 FALSE는 덮어쓰겠는지? FALSE일경우 덮어쓴다.
			DirToList(&m_right_list, dest_path);
		}
	}
}


void CMFCApplication1Dlg::OnBnClickedOpenDirBtn()
{
	CString path;
	GetDlgItemText(IDC_R_PATH_EDIT, path);
	ShellExecute(NULL, L"open", L"explorer.exe", path, path, SW_SHOW);
}


void CMFCApplication1Dlg::OnBnClickedRDleBtn()
{
	int index = m_right_list.GetCurSel();
	if (index != LB_ERR) {
		CString name;
		m_right_list.GetText(index, name);
		if (name[0] == '[') {
			// 디렉터리 삭제 안함
			MessageBox(L"디렉토리는 삭제할 수 없습니다.", L"삭제 실패", MB_ICONSTOP | MB_OK);
		}
		else {
			if (IDOK == MessageBox(name, L"아래의 파일을 삭제하시겠습니까?", MB_ICONQUESTION | MB_OKCANCEL))
			{
				CString path;
				GetDlgItemText(IDC_R_PATH_EDIT, path);
				DeleteFile(path + name);
				DirToList(&m_right_list, path);
			}
		}
	}
}
