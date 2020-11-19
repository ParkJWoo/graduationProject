// UnitTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool.h"
#include "afxdialogex.h"


// CUnitTool ��ȭ �����Դϴ�.

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

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_Radio[0].SetCheck(FALSE);

	m_hBitmap = (HBITMAP)LoadImage(nullptr, L"../Texture/JusinLogo1.bmp",
		IMAGE_BITMAP, 100, 50, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_PushBtn.SetBitmap(m_hBitmap);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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


// CUnitTool �޽��� ó�����Դϴ�.


void CUnitTool::OnBnClickedPushData()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	// UpdateData: ���� ���̾�α׿� ��ġ�� ��Ʈ���� �����Լ�.
	// TRUE: ���� ��Ʈ�ѿ� �Էµ� ������ �о��.
	// FALSE: ������ ����� ���� ��Ʈ�ѿ� �ݿ���.

	UpdateData(TRUE);

	m_strCopy = m_strInput;

	UpdateData(FALSE);
}


void CUnitTool::OnBnClickedAdd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
			// GetCheck: ���� ���� ��ư�� üũ�Ǿ����� Ȯ��.
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

		//// ��Ʈ�� ���� ���̵� ��Ʈ���� ID�����ε� ������ �� �ִ�.
		//if(dynamic_cast<CButton*>(GetDlgItem(IDC_CHECK1))->GetCheck())
		//	pData->byItem |= RUBY;
		//if (dynamic_cast<CButton*>(GetDlgItem(IDC_CHECK2))->GetCheck())
		//	pData->byItem |= DIAMOND;
		//if (dynamic_cast<CButton*>(GetDlgItem(IDC_CHECK3))->GetCheck())
		//	pData->byItem |= SAPPHIRE;


		m_MapData.insert({ m_strName,  pData });

		// AddString: ���� ����Ʈ �ڽ� ��Ͽ� �ش� ���ڿ��� �߰��Ѵ�.
		m_ListBox.AddString(m_strName);
	}	

	UpdateData(FALSE);
}

void CUnitTool::OnLbnSelectClass()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CString m_strSelectName = L"";

	// GetCurSel: ���� ����Ʈ�ڽ����� ���õ� ����� �ε����� ������ �Լ�.
	int iSelect = m_ListBox.GetCurSel();

	// GetText: �ε����� �ش��ϴ� ���ڿ��� ����Ʈ�ڽ��κ��� ������ �Լ�.
	m_ListBox.GetText(iSelect, m_strSelectName);

	auto& iter_find = m_MapData.find(m_strSelectName);

	if (m_MapData.end() == iter_find)
		return;

	m_strName = iter_find->second->strName;
	m_iAtt = iter_find->second->iAtt;
	m_iDef = iter_find->second->iDef;

	for (int i = 0; i < 3; ++i)
		m_Radio[i].SetCheck(FALSE);	// ���� ��ư üũ ����

	// ���� ����Ʈ ��Ͽ��� ���õ� �ε����� �ش��ϴ� ������ư üũ!
	m_Radio[iter_find->second->byJobIndex].SetCheck(TRUE);

	for (int i = 0; i < 3; ++i)
		m_CheckBox[i].SetCheck(FALSE);	// üũ�ڽ� üũ ����

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CString m_strSelectName = L"";

	int iSelect = m_ListBox.GetCurSel();

	// GetCurSel �Լ��� �ε����� ã�� ���ϴ� ��� -1�� ��ȯ.
	if (LB_ERR == iSelect)
		return;

	m_ListBox.GetText(iSelect, m_strSelectName);

	auto& iter_find = m_MapData.find(m_strSelectName);

	if (m_MapData.end() == iter_find)
		return;

	SafeDelete(iter_find->second);
	m_MapData.erase(m_strSelectName);

	// DeleteString: �ش� �ε����� ���ڿ��� ����Ʈ�ڽ� ��Ͽ��� ����.
	m_ListBox.DeleteString(iSelect);

	UpdateData(FALSE);
}

void CUnitTool::OnEnChangeSearch()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	// Edit control���� �Է��� ���ڿ��� ���� �� Ž��.
	auto& iter_find = m_MapData.find(m_strFindName);

	if (m_MapData.end() == iter_find)
		return;

	// FindString(���� �ε���, ã�� ���ڿ�): ���� �ε������� ã�� ���ڿ��� Ž���Ѵ�.
	// Ž���� �����ϸ� �ش� �ε����� ��ȯ�Ѵ�.
	int iFindIndex = m_ListBox.FindString(0, m_strFindName);

	// Ž���� �����ϸ� -1�� ��ȯ.
	if (LB_ERR == iFindIndex)
		return;

	// SetCurSel: ���� �ε����� ���õ� ��ó�� ����Ʈ�ڽ��� ǥ��.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	// CFileDialog: ���� ���� Ȥ�� ���� �۾��� �ʿ��� ��ȭ���ڸ� �����ϴ� ��ü.
	CFileDialog Dlg(FALSE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", this);

	TCHAR szPath[MAX_STR] = L"";

	// GetCurrentDirectory: ���� �۾� ��θ� ����.
	GetCurrentDirectory(MAX_STR, szPath);

	// Data������ �⺻ ��η� �����.
	
	// PathRemoveFileSpec: ��ü ��ο��� ���ϸ� �߶󳻴� �Լ�.
	// ��, ��� �� ���ϸ��� ���ٸ� ���� ���� �������� �߶��ش�.
	PathRemoveFileSpec(szPath);

	lstrcat(szPath, L"\\Data");

	// lpstrInitialDir: ��ȭ���ڸ� ������ �� �⺻ ��θ� ����. ������O
	Dlg.m_ofn.lpstrInitialDir = szPath;
	
	// DoModal: ��ȭ���ڸ� ����. IDOK Ȥ�� IDCANCEL�� ��ȯ.
	if (IDOK == Dlg.DoModal())
	{
		// GetPathName: ��ȭ���ڿ��� ����ڰ� ������ ���� ��� �� ���� ���� ����.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CFileDialog Dlg(TRUE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", this);

	TCHAR szPath[MAX_STR] = L"";
	GetCurrentDirectory(MAX_STR, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");

	// �⺻ ��� ����.
	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		// �ҷ����� ���� ������ map�� ����.
		for_each(m_MapData.begin(), m_MapData.end(), 
			[](auto& MyPair)
		{
			SafeDelete(MyPair.second);
		});

		m_MapData.clear();

		// �ҷ����� ���� ����Ʈ�ڽ� ��ϵ� ����.
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