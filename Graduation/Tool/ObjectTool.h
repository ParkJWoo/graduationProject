#pragma once


// CObjectTool 대화 상자

class CToolView;
class CObjectTool : public CDialog
{
	DECLARE_DYNAMIC(CObjectTool)
public:
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnCbnSelBackgroundCombo();

public:
	CObjectTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CObjectTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJECTTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	//virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	void ImgFileLoad(TCHAR* tFilePath);

public:
	void HorizontalScroll();
	void Release();

public:
	///////////////////////////////////////	CONTROL	/////////////////
	CComboBox m_ComboBox;
	CListBox m_ListBox;
	CStatic m_PictureCtrl;

public:
	///////////////////////////////////////	Value	/////////////////

public:
	////////////////////////////////////// USER	///////////////

	map<CString, CImage*> m_MapImg;

	int m_iDrawID = 0;

	CString strSelectName;
};
