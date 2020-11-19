#pragma once
#include "afxwin.h"


// CMapTool ��ȭ �����Դϴ�.

class CToolView;
class CMapTool : public CDialog
{
	DECLARE_DYNAMIC(CMapTool)

public:
	CMapTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMapTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
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
	// CImage: jpg, gif, bmp, png ���ĵ��� �����ϴ� MFC�� �̹��� Ŭ����.
	map<CString, CImage*>	m_MapImg;

	int						m_iDrawID = 0;
	int						m_iBackgroundID = 0;

	CString					strSelectName;
	afx_msg void OnBnClickedModeCheck();
};
