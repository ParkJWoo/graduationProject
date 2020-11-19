// MyForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MyForm.h"


// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_MYFORM)
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyForm::OnBnClickedUnitTool)
	ON_BN_CLICKED(IDC_BUTTON6, &CMyForm::OnBnClickedMapTool)
	ON_BN_CLICKED(IDC_BUTTON9, &CMyForm::OnBnClickedPathFind)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyForm::OnBnClickedObjectTool)
END_MESSAGE_MAP()


// CMyForm �����Դϴ�.

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyForm �޽��� ó�����Դϴ�.	


void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	// CreatePointFont(��Ʈ ũ��, �۾�ü)
	//m_Font.CreatePointFont(180, L"�ü�");

	//// GetDlgItem: ���� ���̾�α׿� ��ġ�� ������Ʈ�� ������ �Լ�.
	GetDlgItem(IDC_BUTTON1)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON6)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON9)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON2)->SetFont(&m_Font);
}


void CMyForm::OnBnClickedUnitTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//AfxMessageBox(L"Hello world");

	// GetSafeHwnd: ���� ���̾�α��� �����츦 ��ȯ.
	// nullptr�� ��ȯ�Ѵٸ� ���� ���̾�α״� �������� ����.
	if(nullptr == m_UnitTool.GetSafeHwnd())
		m_UnitTool.Create(IDD_UNITTOOL);	// �ش� ID�� �´� ���̾�αװ� �����ȴ�.

	m_UnitTool.ShowWindow(SW_SHOW);		// â ������� ���
}


void CMyForm::OnBnClickedMapTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if (nullptr == m_MapTool.GetSafeHwnd())
		m_MapTool.Create(IDD_MAPTOOL);	// �ش� ID�� �´� ���̾�αװ� �����ȴ�.

	m_MapTool.ShowWindow(SW_SHOW);		// â ������� ���
}

void CMyForm::OnBnClickedPathFind()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (nullptr == m_Pathfind.GetSafeHwnd())
		m_Pathfind.Create(IDD_PATHFIND);	// �ش� ID�� �´� ���̾�αװ� �����ȴ�.

	m_Pathfind.ShowWindow(SW_SHOW);		// â ������� ���
}


void CMyForm::OnBnClickedObjectTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if (m_AnimationTool.GetSafeHwnd() == nullptr)
		m_AnimationTool.Create(IDD_OBJECTTOOL);

	m_AnimationTool.ShowWindow(SW_SHOW);
}
