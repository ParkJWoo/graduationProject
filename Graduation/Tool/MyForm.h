#pragma once

// CMyForm 폼 뷰입니다.
#include "UnitTool.h"
#include "MapTool.h"
#include "PathFind.h"
#include "ObjectTool.h"
#include "AnimationTool.h"

class CMyForm : public CFormView
{
	DECLARE_DYNCREATE(CMyForm)

protected:
	CMyForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMyForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

public:	
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedUnitTool();
	afx_msg void OnBnClickedMapTool();
	afx_msg void OnBnClickedPathFind();
	afx_msg void OnBnClickedObjectTool();

public:
	CFont			m_Font;	// MFC에서 제공하는 폰트 객체
	CUnitTool		m_UnitTool;
	CMapTool		m_MapTool;
	CPathFind		m_Pathfind;
	//CObjectTool		m_ObjectTool;

	CAnimationTool	m_AnimationTool;
};


