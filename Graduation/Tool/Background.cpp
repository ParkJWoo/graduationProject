#include "stdafx.h"
#include "Background.h"
#include "ToolView.h"


CBackground::CBackground()
	:m_pMainView(nullptr), m_iDrawID(0)
{
}


CBackground::~CBackground()
{
	Release();
}

void CBackground::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Background/Scene%d.png", L"Background",
		TEX_MULTI, L"Background", 5)))
	{
		AfxMessageBox(L"Background Image Insert Failed!!!");
		return;
	}
}

void CBackground::Update()
{

}

void CBackground::Render(int iDrawID)
{
	CRect rcWnd = {  };

	::GetClientRect(m_pMainView->m_hWnd, &rcWnd);

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Background", L"Background", iDrawID);

	float fRatioX = WINCX / float(rcWnd.right - rcWnd.left);
	float fRatioY = WINCY / float(rcWnd.bottom - rcWnd.top);

	D3DXMATRIX matScale, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, fRatioX, fRatioY, 1.f);
	D3DXMatrixTranslation(&matTrans, 400.f - m_pMainView->GetScrollPos(0), 300.f - m_pMainView->GetScrollPos(1), 0.f);

	matWorld = matScale * matTrans;

	// SetTransform: ����� �ݿ��ϴ� �Լ�.
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	// �̹����� ���� ���ϱ�.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	// ������ ��� ������Ʈ�� �������� �� ���̿��� ����.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*����� �̹��� ������ RECT*/,
		&D3DXVECTOR3((float)400, (float)iCenterY, 0.f) /*����� �̹����� �߽� ��ǥ D3DXVECTOR3*/,
		nullptr /*����� ��ġ ��ǥ D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBackground::Release()
{

}
