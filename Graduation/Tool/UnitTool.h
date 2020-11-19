#pragma once
#include "afxwin.h"


// CUnitTool ��ȭ �����Դϴ�.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUnitTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
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

	// ��Ʈ�� ����������
	CButton		m_PushBtn;

public:
	//////////////////////////// value
	// �Է� ���ڿ�
	CString m_strInput;

	// ��� ���ڿ�
	CString m_strCopy;
	
	// �̸�
	CString m_strName;
	// ���ݷ�
	int m_iAtt;
	// ����
	int m_iDef;

	// �˻� ���
	CString m_strFindName;

public:
	//////////////////////////// user
	map<CString, UNIT_DATA*>	m_MapData;	
	HBITMAP						m_hBitmap;	
};
