
// ToolView.h : CToolView 클래스의 인터페이스
//

#pragma once


class CTerrain;
class CBackground;
class CToolDoc;
class CLine;
class CBackLayer;
class CFirstLayer;
class CSecondLayer;
class CFrontLayer;

class CToolView : public CScrollView // CScrollView: 스크롤바 형태를 갖는 윈도우의 자식 클래스.
{
protected: // serialization에서만 만들어집니다.
	CToolView();
	DECLARE_DYNCREATE(CToolView)

// 특성입니다.
public:
	CToolDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnInitialUpdate();

// 구현입니다.
public:
	virtual ~CToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

public:
	CTerrain*		GetTerrain() { return m_pTerrain; }
	CFirstLayer*	GetFirstLayer() { return m_pFirstLayer; }
	CFrontLayer*	GetFrontLayer() { return m_pFrontLayer; }
	CSecondLayer*	GetSecondLayer() { return m_pSecondLayer; }
	CBackLayer*		GetBackLayer() { return m_pBackLayer; }

private:
	CTerrain*			m_pTerrain;	
	CBackground*		m_pBackground;
	CLine*				m_pLine;

	CBackLayer*			m_pBackLayer;
	CFirstLayer*		m_pFirstLayer;
	CSecondLayer*		m_pSecondLayer;
	CFrontLayer*		m_pFrontLayer;
};

#ifndef _DEBUG  // ToolView.cpp의 디버그 버전
inline CToolDoc* CToolView::GetDocument() const
   { return reinterpret_cast<CToolDoc*>(m_pDocument); }
#endif

