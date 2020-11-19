#pragma once
#include "afxwin.h"


// CUnitTool 대화 상자입니다.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUnitTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedPushData();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnLbnSelectClass();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnEnChangeSearch();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();

public:
	void Release();

public:
	//////////////////////////// constrol
	CListBox	m_ListBox;
	CButton		m_Radio[3];
	CButton		m_CheckBox[3];

	// 비트맵 입혀볼거임
	CButton		m_PushBtn;

public:
	//////////////////////////// value
	// 입력 문자열
	CString m_strInput;

	// 출력 문자열
	CString m_strCopy;
	
	// 이름
	CString m_strName;
	// 공격력
	int m_iAtt;
	// 방어력
	int m_iDef;

	// 검색 기능
	CString m_strFindName;

public:
	//////////////////////////// user
	map<CString, UNIT_DATA*>	m_MapData;	
	HBITMAP						m_hBitmap;	
};
