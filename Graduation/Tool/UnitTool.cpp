// UnitTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool.h"
#include "afxdialogex.h"


// CUnitTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_UNITTOOL, pParent)
	, m_strInput(_T(""))
	, m_strCopy(_T(""))
	, m_strName(_T(""))
	, m_iAtt(0)
	, m_iDef(0)
	, m_strFindName(_T(""))
{

}

CUnitTool::~CUnitTool()
{
	Release();
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strInput);
	DDX_Text(pDX, IDC_EDIT2, m_strCopy);
	DDX_Text(pDX, IDC_EDIT3, m_strName);
	DDX_Text(pDX, IDC_EDIT4, m_iAtt);
	DDX_Text(pDX, IDC_EDIT5, m_iDef);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_RADIO1, m_Radio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_Radio[1]);
	DDX_Control(pDX, IDC_RADIO3, m_Radio[2]);
	DDX_Control(pDX, IDC_CHECK1, m_CheckBox[0]);
	DDX_Control(pDX, IDC_CHECK2, m_CheckBox[1]);
	DDX_Control(pDX, IDC_CHECK3, m_CheckBox[2]);
	DDX_Control(pDX, IDC_BUTTON1, m_PushBtn);
	DDX_Text(pDX, IDC_EDIT7, m_strFindName);
}

BOOL CUnitTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_Radio[0].SetCheck(FALSE);

	m_hBitmap = (HBITMAP)LoadImage(nullptr, L"../Texture/JusinLogo1.bmp",
		IMAGE_BITMAP, 100, 50, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_PushBtn.SetBitmap(m_hBitmap);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CUnitTool::OnBnClickedPushData)
	ON_BN_CLICKED(IDC_BUTTON2, &CUnitTool::OnBnClickedAdd)
	ON_LBN_SELCHANGE(IDC_LIST1, &CUnitTool::OnLbnSelectClass)
	ON_BN_CLICKED(IDC_BUTTON3, &CUnitTool::OnBnClickedDelete)
	ON_EN_CHANGE(IDC_EDIT7, &CUnitTool::OnEnChangeSearch)
	ON_BN_CLICKED(IDC_BUTTON4, &CUnitTool::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON5, &CUnitTool::OnBnClickedLoad)
END_MESSAGE_MAP()


// CUnitTool 메시지 처리기입니다.


void CUnitTool::OnBnClickedPushData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// UpdateData: 현재 다이얼로그에 배치된 컨트롤의 갱신함수.
	// TRUE: 현재 컨트롤에 입력된 값들을 읽어옴.
	// FALSE: 변수에 저장된 값을 컨트롤에 반영함.

	UpdateData(TRUE);

	m_strCopy = m_strInput;

	UpdateData(FALSE);
}


void CUnitTool::OnBnClickedAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	auto& iter_find = m_MapData.find(m_strName);

	if (m_MapData.end() == iter_find)
	{
		UNIT_DATA*	pData = new UNIT_DATA;

		pData->strName = m_strName;
		pData->iAtt = m_iAtt;
		pData->iDef = m_iDef;

		for (int i = 0; i < 3; ++i)
		{
			// GetCheck: 현재 라디오 버튼이 체크되었는지 확인.
			if (m_Radio[i].GetCheck())
			{
				pData->byJobIndex = i;
				break;
			}
		}

		pData->byItem = 0x00;	// 0000

		if (m_CheckBox[0].GetCheck())
			pData->byItem |= RUBY;
		if (m_CheckBox[1].GetCheck())
			pData->byItem |= DIAMOND;
		if (m_CheckBox[2].GetCheck())
			pData->byItem |= SAPPHIRE;

		//// 컨트롤 변수 없이도 컨트롤의 ID값으로도 제어할 수 있다.
		//if(dynamic_cast<CButton*>(GetDlgItem(IDC_CHECK1))->GetCheck())
		//	pData->byItem |= RUBY;
		//if (dynamic_cast<CButton*>(GetDlgItem(IDC_CHECK2))->GetCheck())
		//	pData->byItem |= DIAMOND;
		//if (dynamic_cast<CButton*>(GetDlgItem(IDC_CHECK3))->GetCheck())
		//	pData->byItem |= SAPPHIRE;


		m_MapData.insert({ m_strName,  pData });

		// AddString: 현재 리스트 박스 목록에 해당 문자열을 추가한다.
		m_ListBox.AddString(m_strName);
	}	

	UpdateData(FALSE);
}

void CUnitTool::OnLbnSelectClass()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString m_strSelectName = L"";

	// GetCurSel: 현재 리스트박스에서 선택된 목록의 인덱스를 얻어오는 함수.
	int iSelect = m_ListBox.GetCurSel();

	// GetText: 인덱스에 해당하는 문자열을 리스트박스로부터 얻어오는 함수.
	m_ListBox.GetText(iSelect, m_strSelectName);

	auto& iter_find = m_MapData.find(m_strSelectName);

	if (m_MapData.end() == iter_find)
		return;

	m_strName = iter_find->second->strName;
	m_iAtt = iter_find->second->iAtt;
	m_iDef = iter_find->second->iDef;

	for (int i = 0; i < 3; ++i)
		m_Radio[i].SetCheck(FALSE);	// 라디오 버튼 체크 해제

	// 현재 리스트 목록에서 선택된 인덱스에 해당하는 라디오버튼 체크!
	m_Radio[iter_find->second->byJobIndex].SetCheck(TRUE);

	for (int i = 0; i < 3; ++i)
		m_CheckBox[i].SetCheck(FALSE);	// 체크박스 체크 해제

	if (iter_find->second->byItem & RUBY)
		m_CheckBox[0].SetCheck(TRUE);
	if (iter_find->second->byItem & DIAMOND)
		m_CheckBox[1].SetCheck(TRUE);
	if (iter_find->second->byItem & SAPPHIRE)
		m_CheckBox[2].SetCheck(TRUE);

	UpdateData(FALSE);	
}

void CUnitTool::OnBnClickedDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString m_strSelectName = L"";

	int iSelect = m_ListBox.GetCurSel();

	// GetCurSel 함수가 인덱스를 찾지 못하는 경우 -1을 반환.
	if (LB_ERR == iSelect)
		return;

	m_ListBox.GetText(iSelect, m_strSelectName);

	auto& iter_find = m_MapData.find(m_strSelectName);

	if (m_MapData.end() == iter_find)
		return;

	SafeDelete(iter_find->second);
	m_MapData.erase(m_strSelectName);

	// DeleteString: 해당 인덱스의 문자열을 리스트박스 목록에서 제거.
	m_ListBox.DeleteString(iSelect);

	UpdateData(FALSE);
}

void CUnitTool::OnEnChangeSearch()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	// Edit control에서 입력한 문자열을 토대로 맵 탐색.
	auto& iter_find = m_MapData.find(m_strFindName);

	if (m_MapData.end() == iter_find)
		return;

	// FindString(시작 인덱스, 찾을 문자열): 시작 인덱스부터 찾을 문자열을 탐색한다.
	// 탐색에 성공하면 해당 인덱스를 반환한다.
	int iFindIndex = m_ListBox.FindString(0, m_strFindName);

	// 탐색에 실패하면 -1을 반환.
	if (LB_ERR == iFindIndex)
		return;

	// SetCurSel: 현재 인덱스가 선택된 것처럼 리스트박스에 표시.
	m_ListBox.SetCurSel(iFindIndex);

	m_strName = iter_find->second->strName;
	m_iAtt = iter_find->second->iAtt;
	m_iDef = iter_find->second->iDef;

	for (int i = 0; i < 3; ++i)
	{
		m_Radio[i].SetCheck(FALSE);
		m_CheckBox[i].SetCheck(FALSE);
	}

	m_Radio[iter_find->second->byJobIndex].SetCheck(TRUE);

	if (iter_find->second->byItem & RUBY)
		m_CheckBox[0].SetCheck(TRUE);
	if (iter_find->second->byItem & DIAMOND)
		m_CheckBox[1].SetCheck(TRUE);
	if (iter_find->second->byItem & SAPPHIRE)
		m_CheckBox[2].SetCheck(TRUE);


	UpdateData(FALSE);
}


void CUnitTool::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	// CFileDialog: 파일 열기 혹은 저장 작업에 필요한 대화상자를 생성하는 객체.
	CFileDialog Dlg(FALSE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", this);

	TCHAR szPath[MAX_STR] = L"";

	// GetCurrentDirectory: 현재 작업 경로를 얻어옴.
	GetCurrentDirectory(MAX_STR, szPath);

	// Data폴더를 기본 경로로 만들기.
	
	// PathRemoveFileSpec: 전체 경로에서 파일명만 잘라내는 함수.
	// 단, 경로 상에 파일명이 없다면 제일 말단 폴더명을 잘라준다.
	PathRemoveFileSpec(szPath);

	lstrcat(szPath, L"\\Data");

	// lpstrInitialDir: 대화상자를 열었을 때 기본 경로를 설정. 절대경로O
	Dlg.m_ofn.lpstrInitialDir = szPath;
	
	// DoModal: 대화상자를 실행. IDOK 혹은 IDCANCEL을 반환.
	if (IDOK == Dlg.DoModal())
	{
		// GetPathName: 대화상자에서 사용자가 지정한 파일 경로 및 파일 명을 얻어옴.
		CString strGetPath = Dlg.GetPathName();
		const TCHAR* pGetPath = strGetPath.GetString();

		HANDLE hFile = CreateFile(pGetPath, GENERIC_WRITE, 0, 0,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"UnitTool Save Failed!!");
			return;
		}

		DWORD dwByte = 0;

		for (auto& MyPair : m_MapData)
		{
			const TCHAR* pName = MyPair.second->strName.GetString();
			int iLength = MyPair.second->strName.GetLength() + 1;

			WriteFile(hFile, &iLength, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, pName, sizeof(TCHAR) * iLength, &dwByte, nullptr);
			WriteFile(hFile, &MyPair.second->iAtt, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &MyPair.second->iDef, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &MyPair.second->byJobIndex, sizeof(BYTE), &dwByte, nullptr);
			WriteFile(hFile, &MyPair.second->byItem, sizeof(BYTE), &dwByte, nullptr);
		}

		CloseHandle(hFile);
	}

	UpdateData(FALSE);
}


void CUnitTool::OnBnClickedLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CFileDialog Dlg(TRUE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", this);

	TCHAR szPath[MAX_STR] = L"";
	GetCurrentDirectory(MAX_STR, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");

	// 기본 경로 설정.
	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		// 불러오기 전에 기존의 map을 비운다.
		for_each(m_MapData.begin(), m_MapData.end(), 
			[](auto& MyPair)
		{
			SafeDelete(MyPair.second);
		});

		m_MapData.clear();

		// 불러오기 전에 리스트박스 목록도 비운다.
		m_ListBox.ResetContent();

		CString strGetName = Dlg.GetPathName();
		HANDLE hFile = CreateFile(strGetName.GetString(), GENERIC_READ, 0, 0,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"UnitTool Load Failed!!");
			return;
		}

		int iLength = 0;
		DWORD dwByte = 0;
		TCHAR* pName = nullptr;
		int iAtt = 0, iDef = 0;
		BYTE byJobIndex = 0;
		BYTE byItem = 0;

		UNIT_DATA* pData = nullptr;

		while (true)
		{
			ReadFile(hFile, &iLength, sizeof(int), &dwByte, nullptr);

			pName = new TCHAR[iLength];
			ReadFile(hFile, pName, sizeof(TCHAR) * iLength, &dwByte, nullptr);
			ReadFile(hFile, &iAtt, sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &iDef, sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &byJobIndex, sizeof(BYTE), &dwByte, nullptr);
			ReadFile(hFile, &byItem, sizeof(BYTE), &dwByte, nullptr);

			if (0 == dwByte)
			{
				if (pName)
				{
					delete[] pName;
					pName = nullptr;
				}

				break;
			}

			pData = new UNIT_DATA;
			pData->strName = pName;
			delete[] pName;
			pName = nullptr;

			pData->iAtt = iAtt;
			pData->iDef = iDef;
			pData->byJobIndex = byJobIndex;
			pData->byItem = byItem;

			m_MapData.insert({ pData->strName, pData });
			m_ListBox.AddString(pData->strName);
		}

		CloseHandle(hFile);
	}
	

	UpdateData(FALSE);
}

void CUnitTool::Release()
{
	for_each(m_MapData.begin(), m_MapData.end(),
		[](auto& MyPair)
	{
		SafeDelete(MyPair.second);
	});

	m_MapData.clear();

	DeleteObject(m_hBitmap);
}