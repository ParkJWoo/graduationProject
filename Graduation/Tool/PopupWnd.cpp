// PopupWnd.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "PopupWnd.h"
#include "afxdialogex.h"


// CPopupWnd ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CPopupWnd, CDialog)

CPopupWnd::CPopupWnd(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_POPUPWND, pParent)
{

}

CPopupWnd::~CPopupWnd()
{
	SafeDelete(m_pMySheet);
}

void CPopupWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPopupWnd, CDialog)
END_MESSAGE_MAP()


// CPopupWnd �޽��� ó�����Դϴ�.


BOOL CPopupWnd::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_pMySheet = new CMySheet;

	// Create: ��޸��� �������� ����.
	m_pMySheet->Create(this, WS_CHILD | WS_VISIBLE);
	m_pMySheet->MoveWindow(0, 0, 500, 400); // ���� �������� ��ġ�� ũ�� ����.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
