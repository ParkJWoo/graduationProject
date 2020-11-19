// ObjectTool.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "ObjectTool.h"
#include "afxdialogex.h"
#include "FileInfo.h"


// CObjectTool 대화 상자

IMPLEMENT_DYNAMIC(CObjectTool, CDialog)

CObjectTool::CObjectTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_OBJECTTOOL, pParent)
{

}

CObjectTool::~CObjectTool()
{
	Release();
}

void CObjectTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_COMBO1, m_ComboBox);
	//DDX_Control(pDX, IDC_LIST1, m_ListBox);
	//DDX_Control(pDX, IDC_PICTURE2, m_PictureCtrl);
}


BEGIN_MESSAGE_MAP(CObjectTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CObjectTool::OnLbnSelchangeList1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CObjectTool::OnCbnSelBackgroundCombo)
END_MESSAGE_MAP()


// CObjectTool 메시지 처리기


void CObjectTool::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	int iSelect = m_ListBox.GetCurSel();

	if (LB_ERR == iSelect)
		return;

	//CString strSelectName;
	m_ListBox.GetText(iSelect, strSelectName);

	auto iter_find = m_MapImg.find(strSelectName);

	if (m_MapImg.end() == iter_find)
		return;

	// SetBitmap(CImage img): CImage 객체가 가진 리소스를 픽처컨트롤에 출력.
	m_PictureCtrl.SetBitmap(*(iter_find->second));

	// 리스트박스에서 선택된 타일의 DrawID를 얻어내자!
	int i = 0;

	for (; i < strSelectName.GetLength(); ++i)
	{
		// isdigit: 현재 문자가 숫자인지 검사.
		// 숫자라고 판명이 날 경우 0이 아닌 값을 반환.
		if (0 != isdigit(strSelectName[i]))
			break;
	}

	// CString::Delete(start, count): 현재 문자열의 start위치부터 count만큼 문자들을 제거.
	strSelectName.Delete(0, i);

	// _tstoi: 문자를 정수타입으로 변환하는 함수.
	m_iDrawID = _tstoi(strSelectName);

	UpdateData(FALSE);
}

void CObjectTool::OnCbnSelBackgroundCombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

//BOOL CObjectTool::OnInitDialog()
//{
//	CDialog::OnInitDialog();
//
//	// TODO:  여기에 추가 초기화 작업을 추가합니다.
//	UpdateData(TRUE);
//
//	m_ListBox.ResetContent();
//
//	TCHAR szFilePath_SecondLayer[MAX_STR] = L"../Texture/Prop/Icon/SecondLayer/*.bmp";
//	TCHAR szFilePath_Back[MAX_STR] = L"../Texture/Prop/Icon/BackLayer/*.bmp";
//
//	ImgFileLoad(szFilePath_SecondLayer);
//	ImgFileLoad(szFilePath_Back);
//
//
//	UpdateData(FALSE);
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
//}

void CObjectTool::ImgFileLoad(TCHAR * tFilePath)
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

		// 해당 키가 존재하지 않을 때 CImage를 map에 새로 추가한다.
		if (m_MapImg.end() == iter_find)
		{
			CImage* pImage = new CImage;
			pImage->Load(strRelativePath); // 상대경로로부터 이미지를 로드.

			m_MapImg.insert({ strFileName, pImage });
			m_ListBox.AddString(szFileName);
		}
	}

	fileFinder.Close();
}

void CObjectTool::HorizontalScroll()
{
	CString strName;
	CSize	size;

	// 리스트 박스 내에서 문자열이 가장 긴 녀석을 기준으로 가로 스크롤바 크기를 결정.
	int iMaxCX = 0;

	CDC* pDC = m_ListBox.GetDC(); // 리스트 박스의 DC를 얻어온다.

	// CListBox::GetCount(): 현재 리스트 박스의 목록 개수를 얻어옴.
	for (int i = 0; i < m_ListBox.GetCount(); ++i)
	{
		m_ListBox.GetText(i, strName);

		// CDC::GetTextExtent(string): string의 길이를 픽셀단위로 변환.
		size = pDC->GetTextExtent(strName);

		// 이 중에서 제일 긴 녀석을 찾는다.
		if (size.cx > iMaxCX)
			iMaxCX = size.cx;
	}

	// 위에서 얻어온 또다른 DC를 해제.
	m_ListBox.ReleaseDC(pDC);

	// iMaxCX를 기준으로 스크롤바 생성.
	if (iMaxCX > m_ListBox.GetHorizontalExtent())
		m_ListBox.SetHorizontalExtent(iMaxCX); // iMaxCX 크기만큼 가로 스크롤바가 생성!
}

void CObjectTool::Release()
{
	for_each(m_MapImg.begin(), m_MapImg.end(),
		[](auto& MyPair)
		{
			// Destroy: CImage객체가 갖고 있던 리소스 자원에 대한 해제함수.
			MyPair.second->Destroy();
			SafeDelete(MyPair.second);
		});

	m_MapImg.clear();
}
