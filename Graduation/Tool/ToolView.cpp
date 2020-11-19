
// ToolView.cpp : CToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Tool.h"
#endif

#include "MainFrm.h"
#include "ToolDoc.h"
#include "ToolView.h"
#include "Terrain.h"
#include "MyForm.h"
#include "MapTool.h"
#include "Background.h"
#include "Line.h"

#include "FirstLayer.h"
#include "SecondLayer.h"
#include "BackLayer.h"
#include "FrontLayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND g_hWnd;

// CToolView

IMPLEMENT_DYNCREATE(CToolView, CScrollView)

BEGIN_MESSAGE_MAP(CToolView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CToolView 생성/소멸

CToolView::CToolView()
	: m_pTerrain(nullptr), m_pBackground(nullptr), m_pLine(nullptr)
	// TODO: 여기에 생성 코드를 추가합니다.
{
}

CToolView::~CToolView()
{
	// 순서 주의.
	SafeDelete(m_pFirstLayer);
	SafeDelete(m_pSecondLayer);
	SafeDelete(m_pBackLayer);
	SafeDelete(m_pFrontLayer);

	SafeDelete(m_pTerrain);
	SafeDelete(m_pBackground);

	CTextureMgr::GetInstance()->DestroyInstance();
	CDevice::GetInstance()->DestroyInstance();
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CToolView 그리기

void CToolView::OnDraw(CDC* pDC)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMyForm* pMyForm = dynamic_cast<CMyForm*>(pMainFrm->m_MainSplit.GetPane(0, 0));

	int m_iDrawID = pMyForm->m_MapTool.m_iBackgroundID;

	CDevice::GetInstance()->GetDevice()->Clear(0, nullptr, D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET,
		D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CDevice::GetInstance()->Render_Begin();
	
	m_pBackground->Render(m_iDrawID);

	m_pBackLayer->Render();

	m_pFirstLayer->Render();

	m_pSecondLayer->Render();

	m_pFrontLayer->Render();

	m_pTerrain->Render();

	CDevice::GetInstance()->Render_End();

	CDevice::GetInstance()->GetLine()->SetWidth(5.f); // 선굵기

	m_pLine->Render();

	CDevice::GetInstance()->GetDevice()->Present(nullptr, nullptr, nullptr, nullptr);
}


// CToolView 인쇄

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CToolView 진단

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView 메시지 처리기


void CToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// SetScrollSizes: 스크롤 바의 크기를 지정하는 CScrollView의 멤버함수.
	SetScrollSizes(MM_TEXT, CSize(TILECX * TILEX, TILECY * TILEY / 2));

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	g_hWnd = m_hWnd;

	// 1.메인 프레임 크기 보정
	// AfxGetMainWnd: 현재 메인 윈도우를 반환해주는 MFC의 전역함수이다.
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());

	// 1-1. 메인 프레임의 크기 정보를 얻어온다.
	// GetWindowRect: 현재 윈도우의 크기(RECT)정보를 얻어오는 함수.
	RECT rcMainWnd = {};
	pMainFrm->GetWindowRect(&rcMainWnd);

	// 1-2. 얻어온 rcWnd를 연산하기 수월하게 좌상단을 0, 0의 위치로 설정.
	SetRect(&rcMainWnd, 0, 0, rcMainWnd.right - rcMainWnd.left, rcMainWnd.bottom - rcMainWnd.top);

	// 1-3. View 윈도우의 RECT를 얻어온다.
	RECT rcView = {};

	// GetClientRect: 현재 윈도우의 RECT를 얻어오는 함수.
	GetClientRect(&rcView);

	// 1-4. 메인 프레임과 View의 가로, 세로 갭을 구한다.
	int iRowFrm = rcMainWnd.right - rcView.right;
	int iColFrm = rcMainWnd.bottom - rcView.bottom;

	// 1-5. 메인 프레임에 WINCX + iRowFrm, WINCY + iColFrm 크기로 설정한다.
	// SetWindowPos: 인수대로 윈도우의 위치와 크기를 조정하는 함수.
	pMainFrm->SetWindowPos(nullptr, 0, 0, WINCX + iRowFrm, WINCY + iColFrm, SWP_NOZORDER);

	if (FAILED(CDevice::GetInstance()->InitDevice()))
	{
		AfxMessageBox(L"Device Init Failed!!!");
		return;
	}

	m_pFirstLayer = new CFirstLayer;
	m_pFirstLayer->Initialize();
	m_pFirstLayer->SetMainView(this);

	m_pSecondLayer = new CSecondLayer;
	m_pSecondLayer->Initialize();
	m_pSecondLayer->SetMainView(this);

	m_pBackLayer = new CBackLayer;
	m_pBackLayer->Initialize();
	m_pBackLayer->SetMainView(this);

	m_pFrontLayer = new CFrontLayer;
	m_pFrontLayer->Initialize();
	m_pFrontLayer->SetMainView(this);

	m_pTerrain = new CTerrain;
	m_pTerrain->Initialize();
	m_pTerrain->SetMainView(this);

	m_pBackground = new CBackground;
	m_pBackground->Initialize();
	m_pBackground->SetMainView(this);

	m_pLine = new CLine;
	m_pLine->Initialize();
	m_pLine->SetMainView(this);
}

// OnLButtonDown: 마우스 좌클릭 했을 때 호출되는 함수.
void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CScrollView::OnLButtonDown(nFlags, point);

	Invalidate(FALSE);

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMyForm* pMyForm = dynamic_cast<CMyForm*>(pMainFrm->m_MainSplit.GetPane(0, 0));

	TERRAIN* pTerrain = new TERRAIN;

	int iDrawID = pMyForm->m_MapTool.m_iDrawID;
	int iBackgroundID = pMyForm->m_MapTool.m_iBackgroundID;

	//int iObjDrawID = pMyForm->m_AnimationTool.m_iDrawID;

	point.x += GetScrollPos(0);
	point.y += GetScrollPos(1);

	if (pMyForm->m_MapTool.m_ListBox.GetCurSel() >= 0 && pMyForm->m_MapTool.m_ListBox.GetCurSel() <= 2)
	{
		m_pBackLayer->SetPosition(D3DXVECTOR3((float)point.x, (float)point.y, 0.f));
		m_pBackLayer->SetDrawID(iDrawID);

		m_pBackLayer->Update();
	}

	if (pMyForm->m_MapTool.m_ListBox.GetCurSel() >= 3 && pMyForm->m_MapTool.m_ListBox.GetCurSel() <= 5)
	{
		m_pFirstLayer->SetPosition(D3DXVECTOR3((float)point.x, (float)point.y, 0.f));
		m_pFirstLayer->SetDrawID(iDrawID);

		m_pFirstLayer->Update();
	}

	if (pMyForm->m_MapTool.m_ListBox.GetCurSel() == 6)
	{
		m_pFrontLayer->SetPosition(D3DXVECTOR3((float)point.x, (float)point.y, 0.f));
		m_pFrontLayer->SetDrawID(iDrawID);

		m_pFrontLayer->Update();
	}

	if (pMyForm->m_MapTool.m_ListBox.GetCurSel() >= 7 && pMyForm->m_MapTool.m_ListBox.GetCurSel() <= 8)
	{
		m_pSecondLayer->SetPosition(D3DXVECTOR3((float)point.x, (float)point.y, 0.f));
		m_pSecondLayer->SetDrawID(iDrawID);

		m_pSecondLayer->Update();
	}

	if (m_pFirstLayer->GetFirstTerrainList().empty() || m_pFrontLayer->GetFrontTerrainLst().empty()
		|| m_pSecondLayer->GetSecondTerrainLst().empty() || m_pBackLayer->GetBackTerrainLst().empty())
		return;

	//// GetScrollPos: CScrollView의 멤버함수.

	//// Invalidate: WM_PAINT와 WM_ERASEBKGND 메시지를 발생.
	Invalidate(FALSE);
}

// OnMouseMove: 마우스가 움직이는 동안 호출되는 함수.
void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CScrollView::OnMouseMove(nFlags, point);

	//CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	//CMyForm* pMyForm = dynamic_cast<CMyForm*>(pMainFrm->m_MainSplit.GetPane(0, 0));
	////
	//int iDrawID = pMyForm->m_MapTool.m_iDrawID;

	point.x += GetScrollPos(0);
	point.y += GetScrollPos(1);

	//// Invalidate: WM_PAINT와 WM_ERASEBKGND 메시지를 발생.
	Invalidate(FALSE);
}

void CToolView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CScrollView::OnRButtonDown(nFlags, point);

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMyForm* pMyForm = dynamic_cast<CMyForm*>(pMainFrm->m_MainSplit.GetPane(0, 0));

	if (pMyForm->m_MapTool.m_ListBox.GetCurSel() >= 0 && pMyForm->m_MapTool.m_ListBox.GetCurSel() <= 2)
		m_pBackLayer->PopBackTerrainLst();

	if (pMyForm->m_MapTool.m_ListBox.GetCurSel() >= 3 && pMyForm->m_MapTool.m_ListBox.GetCurSel() <= 5)
		m_pFirstLayer->PopFirstTerrainLst();

	if (pMyForm->m_MapTool.m_ListBox.GetCurSel() == 6)
		m_pFrontLayer->PopFrontTerrainLst();

	if (pMyForm->m_MapTool.m_ListBox.GetCurSel() >= 7 && pMyForm->m_MapTool.m_ListBox.GetCurSel() <= 8)
		m_pSecondLayer->PopSecondTerrainLst();

	Invalidate(FALSE);
}
