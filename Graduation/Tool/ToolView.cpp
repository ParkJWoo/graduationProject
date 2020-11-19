
// ToolView.cpp : CToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

CToolView::CToolView()
	: m_pTerrain(nullptr), m_pBackground(nullptr), m_pLine(nullptr)
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
{
}

CToolView::~CToolView()
{
	// ���� ����.
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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

// CToolView �׸���

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

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	CDevice::GetInstance()->Render_Begin();
	
	m_pBackground->Render(m_iDrawID);

	m_pBackLayer->Render();

	m_pFirstLayer->Render();

	m_pSecondLayer->Render();

	m_pFrontLayer->Render();

	m_pTerrain->Render();

	CDevice::GetInstance()->Render_End();

	CDevice::GetInstance()->GetLine()->SetWidth(5.f); // ������

	m_pLine->Render();

	CDevice::GetInstance()->GetDevice()->Present(nullptr, nullptr, nullptr, nullptr);
}


// CToolView �μ�

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CToolView ����

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView �޽��� ó����


void CToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// SetScrollSizes: ��ũ�� ���� ũ�⸦ �����ϴ� CScrollView�� ����Լ�.
	SetScrollSizes(MM_TEXT, CSize(TILECX * TILEX, TILECY * TILEY / 2));

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	g_hWnd = m_hWnd;

	// 1.���� ������ ũ�� ����
	// AfxGetMainWnd: ���� ���� �����츦 ��ȯ���ִ� MFC�� �����Լ��̴�.
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());

	// 1-1. ���� �������� ũ�� ������ ���´�.
	// GetWindowRect: ���� �������� ũ��(RECT)������ ������ �Լ�.
	RECT rcMainWnd = {};
	pMainFrm->GetWindowRect(&rcMainWnd);

	// 1-2. ���� rcWnd�� �����ϱ� �����ϰ� �»���� 0, 0�� ��ġ�� ����.
	SetRect(&rcMainWnd, 0, 0, rcMainWnd.right - rcMainWnd.left, rcMainWnd.bottom - rcMainWnd.top);

	// 1-3. View �������� RECT�� ���´�.
	RECT rcView = {};

	// GetClientRect: ���� �������� RECT�� ������ �Լ�.
	GetClientRect(&rcView);

	// 1-4. ���� �����Ӱ� View�� ����, ���� ���� ���Ѵ�.
	int iRowFrm = rcMainWnd.right - rcView.right;
	int iColFrm = rcMainWnd.bottom - rcView.bottom;

	// 1-5. ���� �����ӿ� WINCX + iRowFrm, WINCY + iColFrm ũ��� �����Ѵ�.
	// SetWindowPos: �μ���� �������� ��ġ�� ũ�⸦ �����ϴ� �Լ�.
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

// OnLButtonDown: ���콺 ��Ŭ�� ���� �� ȣ��Ǵ� �Լ�.
void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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

	//// GetScrollPos: CScrollView�� ����Լ�.

	//// Invalidate: WM_PAINT�� WM_ERASEBKGND �޽����� �߻�.
	Invalidate(FALSE);
}

// OnMouseMove: ���콺�� �����̴� ���� ȣ��Ǵ� �Լ�.
void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CScrollView::OnMouseMove(nFlags, point);

	//CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	//CMyForm* pMyForm = dynamic_cast<CMyForm*>(pMainFrm->m_MainSplit.GetPane(0, 0));
	////
	//int iDrawID = pMyForm->m_MapTool.m_iDrawID;

	point.x += GetScrollPos(0);
	point.y += GetScrollPos(1);

	//// Invalidate: WM_PAINT�� WM_ERASEBKGND �޽����� �߻�.
	Invalidate(FALSE);
}

void CToolView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
