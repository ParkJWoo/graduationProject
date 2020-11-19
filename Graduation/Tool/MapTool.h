#pragma once
#include "afxwin.h"


// CMapTool 대화 상자입니다.

class CToolView;
class CMapTool : public CDialog
{
	DECLARE_DYNAMIC(CMapTool)

public:
	CMapTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMapTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelectObjectList();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedFrontSave();
	afx_msg void OnBnClickedFrontLoad();
	afx_msg void OnCbnSelBackgroundCombo();
	afx_msg void OnBnClickedSecondSave();
	afx_msg void OnBnClickedSecondLoad();
	afx_msg void OnBnClickedBackSave();
	afx_msg void OnBnClickedBackLoad();

public:
	void ImgFileLoad(TCHAR* tFilePath);
	void BackgroundImgLoad(TCHAR* tFilePath);


public:
	////////////////////////////////// user
	void HorizontalScroll();
	void Release();

public:
	// //////////////////////////////// control	// //////////////////////////////// control
	CComboBox	m_ComboBox;
	CListBox	m_ListBox;
	CStatic		m_PictureCtrl;
	CButton		m_Radio[3];

public:
	////////////////////////////////// value

public:
	////////////////////////////////// user
	// CImage: jpg, gif, bmp, png 형식들을 지원하는 MFC의 이미지 클래스.
	map<CString, CImage*>	m_MapImg;

	int						m_iDrawID = 0;
	int						m_iBackgroundID = 0;

	CString					strSelectName;
	afx_msg void OnBnClickedModeCheck();
};
