// MapTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTool.h"
#include "afxdialogex.h"
#include "FileInfo.h"

#include "MainFrm.h"
#include "ToolView.h"
#include "Terrain.h"

#include "BackLayer.h"
#include "FrontLayer.h"
#include "FirstLayer.h"
#include "SecondLayer.h"


// CMapTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPTOOL, pParent)
{

}

CMapTool::~CMapTool()
{
	Release();
}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_PICTURE, m_PictureCtrl);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBox);
	DDX_Control(pDX, IDC_RADIO1, m_Radio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_Radio[1]);
	DDX_Control(pDX, IDC_RADIO3, m_Radio[2]);

}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnLbnSelectObjectList)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON2, &CMapTool::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON7, &CMapTool::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnBnClickedFrontSave)
	ON_BN_CLICKED(IDC_BUTTON3, &CMapTool::OnBnClickedFrontLoad)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMapTool::OnCbnSelBackgroundCombo)
	ON_BN_CLICKED(IDC_BUTTON4, &CMapTool::OnBnClickedSecondSave)
	ON_BN_CLICKED(IDC_BUTTON6, &CMapTool::OnBnClickedSecondLoad)
	ON_BN_CLICKED(IDC_BUTTON8, &CMapTool::OnBnClickedBackSave)
	ON_BN_CLICKED(IDC_BUTTON9, &CMapTool::OnBnClickedBackLoad)
	ON_BN_CLICKED(IDC_RADIO1, &CMapTool::OnBnClickedModeCheck)
END_MESSAGE_MAP()


// CMapTool �޽��� ó�����Դϴ�.


void CMapTool::OnLbnSelectObjectList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	int iSelect = m_ListBox.GetCurSel();

	if (LB_ERR == iSelect)
		return;

	//CString strSelectName;
	m_ListBox.GetText(iSelect, strSelectName);

	auto iter_find = m_MapImg.find(strSelectName);

	if (m_MapImg.end() == iter_find)
		return;

	// SetBitmap(CImage img): CImage ��ü�� ���� ���ҽ��� ��ó��Ʈ�ѿ� ���.
	m_PictureCtrl.SetBitmap(*(iter_find->second));

	// ����Ʈ�ڽ����� ���õ� Ÿ���� DrawID�� ����!
	int i = 0;

	for (; i < strSelectName.GetLength(); ++i)
	{
		// isdigit: ���� ���ڰ� �������� �˻�.
		// ���ڶ�� �Ǹ��� �� ��� 0�� �ƴ� ���� ��ȯ.
		if (0 != isdigit(strSelectName[i]))
			break;
	}

	// CString::Delete(start, count): ���� ���ڿ��� start��ġ���� count��ŭ ���ڵ��� ����.
	strSelectName.Delete(0, i);

	// _tstoi: ���ڸ� ����Ÿ������ ��ȯ�ϴ� �Լ�.
	m_iDrawID = _tstoi(strSelectName);	

	UpdateData(FALSE);
}

void CMapTool::OnBnClickedSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CFileDialog Dlg(FALSE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", this);

	TCHAR szPath[MAX_STR] = L"";

	GetCurrentDirectory(MAX_STR, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data\\FirstLayerData");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		HANDLE hFile = CreateFile(Dlg.GetPathName().GetString(), GENERIC_WRITE, 0, 0,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"Tile Save Failed!!");
			return;
		}

		CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplit.GetPane(0, 1));
		CTerrain*	pTerrain = pMainView->GetTerrain();
		vector<TILE*>& vecTile = pTerrain->GetVecTile();

		CFirstLayer* pFirstLayer = pMainView->GetFirstLayer();
		list<TERRAIN*>& FirstLst = pFirstLayer->GetFirstTerrainList();

		DWORD dwByte = 0;

		for (auto& pFirstLst : FirstLst)
			WriteFile(hFile, pFirstLst, sizeof(TERRAIN), &dwByte, nullptr);

		CloseHandle(hFile);
	}	

	UpdateData(FALSE);
}

void CMapTool::OnBnClickedLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CFileDialog Dlg(TRUE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", this);

	TCHAR szPath[MAX_STR] = L"";

	GetCurrentDirectory(MAX_STR, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data\\FirstLayerData");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		HANDLE hFile = CreateFile(Dlg.GetPathName().GetString(), GENERIC_READ, 0, 0,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"Tile Load Failed!!");
			return;
		}

		CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplit.GetPane(0, 1));

		CFirstLayer* pFirstLayer = pMainView->GetFirstLayer();

		if (pFirstLayer == nullptr)
		{
			AfxMessageBox(L"First Layer Load Failed!!");
			return;
		}

		pFirstLayer->Release();
		list<TERRAIN*>& FirstLst = pFirstLayer->GetFirstTerrainList();

		TILE tTile = {};
		DWORD dwByte = 0;

		TERRAIN tTerrain = {};
		
		while (true)
		{
			ReadFile(hFile, &tTerrain, sizeof(TERRAIN), &dwByte, nullptr);

			if (0 == dwByte)
				break;

			TERRAIN* pTerrain = new TERRAIN(tTerrain);
			FirstLst.push_back(pTerrain);
		}

		CloseHandle(hFile);
		pMainView->Invalidate(FALSE);
	}

	UpdateData(FALSE);
}

void CMapTool::ImgFileLoad(TCHAR* tFilePath)
{
	TCHAR szFileName[MAX_STR] = L"";

	CFileFind fileFinder;
	BOOL bWorking = fileFinder.FindFile(tFilePath);

	while (bWorking)
	{
		bWorking = fileFinder.FindNextFileW();

		CString strRelativePath = CFileInfo::ConvertRelativePath(fileFinder.GetFilePath());

		CString strFileName = PathFindFileName(strRelativePath.GetString());

		lstrcpy(szFileName, strFileName.GetString());
		PathRemoveExtension(szFileName);

		strFileName = szFileName;

		auto iter_find = m_MapImg.find(strFileName);

		// �ش� Ű�� �������� ���� �� CImage�� map�� ���� �߰��Ѵ�.
		if (m_MapImg.end() == iter_find)
		{
			CImage* pImage = new CImage;
			pImage->Load(strRelativePath); // ����ηκ��� �̹����� �ε�.
	
			m_MapImg.insert({ strFileName, pImage });
			m_ListBox.AddString(szFileName);
		}
	}

	fileFinder.Close();
}

void CMapTool::BackgroundImgLoad(TCHAR * tFilePath)
{
	TCHAR szFileName[MAX_STR] = L"";

	CFileFind fileFinder;
	BOOL bWorking = fileFinder.FindFile(tFilePath);

	while (bWorking)
	{
		bWorking = fileFinder.FindNextFileW();

		CString strRelativePath = CFileInfo::ConvertRelativePath(fileFinder.GetFilePath());

		CString strFileName = PathFindFileName(strRelativePath.GetString());

		lstrcpy(szFileName, strFileName.GetString());
		PathRemoveExtension(szFileName);

		strFileName = szFileName;

		auto iter_find = m_MapImg.find(strFileName);

		// �ش� Ű�� �������� ���� �� CImage�� map�� ���� �߰��Ѵ�.
		if (m_MapImg.end() == iter_find)
		{
			CImage* pImage = new CImage;
			pImage->Load(strRelativePath); // ����ηκ��� �̹����� �ε�.

			m_MapImg.insert({ strFileName, pImage });
			m_ComboBox.AddString(szFileName);
		}
	}

	fileFinder.Close();
}


void CMapTool::HorizontalScroll()
{
	CString strName;
	CSize	size;

	// ����Ʈ �ڽ� ������ ���ڿ��� ���� �� �༮�� �������� ���� ��ũ�ѹ� ũ�⸦ ����.
	int iMaxCX = 0;

	CDC* pDC = m_ListBox.GetDC(); // ����Ʈ �ڽ��� DC�� ���´�.

	// CListBox::GetCount(): ���� ����Ʈ �ڽ��� ��� ������ ����.
	for (int i = 0; i < m_ListBox.GetCount(); ++i)
	{
		m_ListBox.GetText(i, strName);

		// CDC::GetTextExtent(string): string�� ���̸� �ȼ������� ��ȯ.
		size = pDC->GetTextExtent(strName);

		// �� �߿��� ���� �� �༮�� ã�´�.
		if (size.cx > iMaxCX)
			iMaxCX = size.cx;
	}

	// ������ ���� �Ǵٸ� DC�� ����.
	m_ListBox.ReleaseDC(pDC);

	// iMaxCX�� �������� ��ũ�ѹ� ����.
	if (iMaxCX > m_ListBox.GetHorizontalExtent())
		m_ListBox.SetHorizontalExtent(iMaxCX); // iMaxCX ũ�⸸ŭ ���� ��ũ�ѹٰ� ����!

}

void CMapTool::Release()
{
	for_each(m_MapImg.begin(), m_MapImg.end(), 
		[](auto& MyPair)
	{
		// Destroy: CImage��ü�� ���� �ִ� ���ҽ� �ڿ��� ���� �����Լ�.
		MyPair.second->Destroy();
		SafeDelete(MyPair.second);
	});

	m_MapImg.clear();
}

BOOL CMapTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	UpdateData(TRUE);

	m_Radio[0].SetCheck(TRUE);

	m_ListBox.ResetContent();

	TCHAR szFilePath_FirstLayer[MAX_STR] = L"../Texture/Prop/Icon/FirstLayer/*.bmp" ;
	TCHAR szFilePath_Front[MAX_STR] = L"../Texture/Prop/Icon/FrontLayer/*.bmp";
	TCHAR szFilePath_SecondLayer[MAX_STR] = L"../Texture/Prop/Icon/SecondLayer/*.bmp";
	TCHAR szFilePath_Back[MAX_STR] = L"../Texture/Prop/Icon/BackLayer/*.bmp";

	TCHAR szFilePath_Background[MAX_STR] = L"../Texture/Background/*.png";

	ImgFileLoad(szFilePath_FirstLayer);
	ImgFileLoad(szFilePath_SecondLayer);
	ImgFileLoad(szFilePath_Front);
	ImgFileLoad(szFilePath_Back);

	BackgroundImgLoad(szFilePath_Background);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CMapTool::OnBnClickedFrontSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CFileDialog Dlg(FALSE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", this);

	TCHAR szPath[MAX_STR] = L"";

	GetCurrentDirectory(MAX_STR, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data\\FrontLayerData");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		HANDLE hFile = CreateFile(Dlg.GetPathName().GetString(), GENERIC_WRITE, 0, 0,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"Front Layer Props Save Failed!!");
			return;
		}

		CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplit.GetPane(0, 1));

		CFrontLayer* pFrontLayer = pMainView->GetFrontLayer();
		list<TERRAIN*>& FrontLst = pFrontLayer->GetFrontTerrainLst();

		DWORD dwByte = 0;

		for (auto& pFrontLst : FrontLst)
			WriteFile(hFile, pFrontLst, sizeof(TERRAIN), &dwByte, nullptr);

		CloseHandle(hFile);
	}

	UpdateData(FALSE);
}


void CMapTool::OnBnClickedFrontLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CFileDialog Dlg(TRUE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", this);

	TCHAR szPath[MAX_STR] = L"";

	GetCurrentDirectory(MAX_STR, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data\\FrontLayerData");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		HANDLE hFile = CreateFile(Dlg.GetPathName().GetString(), GENERIC_READ, 0, 0,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"Front Layer Props Load Failed!!");
			return;
		}

		CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplit.GetPane(0, 1));

		CFrontLayer* pFrontLayer = pMainView->GetFrontLayer();

		if (pFrontLayer == nullptr)
		{
			AfxMessageBox(L"Front Layer Load Failed!!");
			return;
		}

		pFrontLayer->Release();
		list<TERRAIN*>& FrontLst = pFrontLayer->GetFrontTerrainLst();

		TERRAIN tTerrain = {};
		DWORD dwByte = 0;

		while (true)
		{
			ReadFile(hFile, &tTerrain, sizeof(TERRAIN), &dwByte, nullptr);

			if (0 == dwByte)
				break;

			TERRAIN* pTerrain = new TERRAIN(tTerrain);
			FrontLst.push_back(pTerrain);
		}

		CloseHandle(hFile);
		pMainView->Invalidate(FALSE);
	}

	UpdateData(FALSE);

}


void CMapTool::OnCbnSelBackgroundCombo()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	int iSelect = m_ComboBox.GetCurSel();

	if (LB_ERR == iSelect)
		return;

	//CString strSelectName;
	m_ComboBox.GetLBText(iSelect, strSelectName);

	auto iter_find = m_MapImg.find(strSelectName);

	if (m_MapImg.end() == iter_find)
		return;

	// SetBitmap(CImage img): CImage ��ü�� ���� ���ҽ��� ��ó��Ʈ�ѿ� ���.

	// ����Ʈ�ڽ����� ���õ� Ÿ���� DrawID�� ����!
	int i = 0;

	for (; i < strSelectName.GetLength(); ++i)
	{
		// isdigit: ���� ���ڰ� �������� �˻�.
		// ���ڶ�� �Ǹ��� �� ��� 0�� �ƴ� ���� ��ȯ.
		if (0 != isdigit(strSelectName[i]))
			break;
	}

	// CString::Delete(start, count): ���� ���ڿ��� start��ġ���� count��ŭ ���ڵ��� ����.
	strSelectName.Delete(0, i);

	// _tstoi: ���ڸ� ����Ÿ������ ��ȯ�ϴ� �Լ�.
	m_iBackgroundID = _tstoi(strSelectName);

	UpdateData(FALSE);
}


void CMapTool::OnBnClickedSecondSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CFileDialog Dlg(FALSE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", this);

	TCHAR szPath[MAX_STR] = L"";

	GetCurrentDirectory(MAX_STR, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data\\SecondLayerData");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		HANDLE hFile = CreateFile(Dlg.GetPathName().GetString(), GENERIC_WRITE, 0, 0,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"FronSecondt Layer Props Save Failed!!");
			return;
		}

		CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplit.GetPane(0, 1));

		CSecondLayer* pSecondLayer = pMainView->GetSecondLayer();
		list<TERRAIN*>& SecondLst  = pSecondLayer->GetSecondTerrainLst();

		DWORD dwByte = 0;

		for (auto& pFrontLst : SecondLst)
			WriteFile(hFile, pFrontLst, sizeof(TERRAIN), &dwByte, nullptr);

		CloseHandle(hFile);
	}

	UpdateData(FALSE);
}


void CMapTool::OnBnClickedSecondLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CFileDialog Dlg(TRUE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", this);

	TCHAR szPath[MAX_STR] = L"";

	GetCurrentDirectory(MAX_STR, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data\\SecondLayerData");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		HANDLE hFile = CreateFile(Dlg.GetPathName().GetString(), GENERIC_READ, 0, 0,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"Second Layer Props Load Failed!!");
			return;
		}

		CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplit.GetPane(0, 1));

		CSecondLayer* pSecondLayer = pMainView->GetSecondLayer();

		if (pSecondLayer == nullptr)
		{
			AfxMessageBox(L"Second Layer Load Failed!!");
			return;
		}

		pSecondLayer->Release();
		list<TERRAIN*>& SecondLst = pSecondLayer->GetSecondTerrainLst();

		TERRAIN tTerrain = {};
		DWORD dwByte = 0;

		while (true)
		{
			ReadFile(hFile, &tTerrain, sizeof(TERRAIN), &dwByte, nullptr);

			if (0 == dwByte)
				break;

			TERRAIN* pTerrain = new TERRAIN(tTerrain);
			SecondLst.push_back(pTerrain);
		}

		CloseHandle(hFile);
		pMainView->Invalidate(FALSE);
	}

	UpdateData(FALSE);
}


void CMapTool::OnBnClickedBackSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CFileDialog Dlg(FALSE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", this);

	TCHAR szPath[MAX_STR] = L"";

	GetCurrentDirectory(MAX_STR, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data\\BackLayerData");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		HANDLE hFile = CreateFile(Dlg.GetPathName().GetString(), GENERIC_WRITE, 0, 0,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"Back Layer Props Save Failed!!");
			return;
		}

		CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplit.GetPane(0, 1));

		CBackLayer* pBackLayer = pMainView->GetBackLayer();
		list<TERRAIN*>& BackLst = pBackLayer->GetBackTerrainLst();

		DWORD dwByte = 0;

		for (auto& pBackLst : BackLst)
			WriteFile(hFile, pBackLst, sizeof(TERRAIN), &dwByte, nullptr);

		CloseHandle(hFile);
	}

	UpdateData(FALSE);
}


void CMapTool::OnBnClickedBackLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CFileDialog Dlg(TRUE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", this);

	TCHAR szPath[MAX_STR] = L"";

	GetCurrentDirectory(MAX_STR, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data\\BackLayerData");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		HANDLE hFile = CreateFile(Dlg.GetPathName().GetString(), GENERIC_READ, 0, 0,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"Back Layer Props Load Failed!!");
			return;
		}

		CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplit.GetPane(0, 1));

		CBackLayer* pBackLayer = pMainView->GetBackLayer();

		if (pBackLayer == nullptr)
		{
			AfxMessageBox(L"Back Layer Load Failed!!");
			return;
		}

		pBackLayer->Release();
		list<TERRAIN*>& BackLst = pBackLayer->GetBackTerrainLst();

		TERRAIN tTerrain = {};
		DWORD dwByte = 0;

		while (true)
		{
			ReadFile(hFile, &tTerrain, sizeof(TERRAIN), &dwByte, nullptr);

			if (0 == dwByte)
				break;

			TERRAIN* pTerrain = new TERRAIN(tTerrain);
			BackLst.push_back(pTerrain);
		}

		CloseHandle(hFile);
		pMainView->Invalidate(FALSE);
	}

	UpdateData(FALSE);

}


void CMapTool::OnBnClickedModeCheck()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

}
