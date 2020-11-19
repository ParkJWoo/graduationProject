
// ToolView.h : CToolView Ŭ������ �������̽�
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

class CToolView : public CScrollView // CScrollView: ��ũ�ѹ� ���¸� ���� �������� �ڽ� Ŭ����.
{
protected: // serialization������ ��������ϴ�.
	CToolView();
	DECLARE_DYNCREATE(CToolView)

// Ư���Դϴ�.
public:
	CToolDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnInitialUpdate();

// �����Դϴ�.
public:
	virtual ~CToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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

#ifndef _DEBUG  // ToolView.cpp�� ����� ����
inline CToolDoc* CToolView::GetDocument() const
   { return reinterpret_cast<CToolDoc*>(m_pDocument); }
#endif

