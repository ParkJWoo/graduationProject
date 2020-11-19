#include "stdafx.h"
#include "FrontLayer.h"
#include "ToolView.h"

CFrontLayer::CFrontLayer()
	:m_pMainView(nullptr), m_iPropDrawID(0)
{
}


CFrontLayer::~CFrontLayer()
{
	Release();
}

void CFrontLayer::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Prop/Front/Front%d.png", L"Front",
		TEX_MULTI, L"Prop", 2)))
	{
		AfxMessageBox(L"First Layer Props Image Insert Failed!!!");
		return;
	}
}

void CFrontLayer::Update()
{
	TERRAIN* pTerrain = new TERRAIN;

	pTerrain->vPos = m_vPosition;
	pTerrain->byDrawID = m_iPropDrawID;
	pTerrain->byOption = 0;

	m_FrontTerrainLst.push_back(pTerrain);
}

void CFrontLayer::Render()
{
	CRect rcWnd = {  };

	::GetClientRect(m_pMainView->m_hWnd, &rcWnd);

	float fRatioX = WINCX / float(rcWnd.right - rcWnd.left);
	float fRatioY = WINCY / float(rcWnd.bottom - rcWnd.top);

	D3DXMATRIX matScale, matTrans, matWorld;

	list<TERRAIN*>::iterator iter_begin = m_FrontTerrainLst.begin();
	list<TERRAIN*>::iterator iter_end = m_FrontTerrainLst.end();

	for (; iter_begin != iter_end; ++iter_begin)
	{
		D3DXMatrixScaling(&matScale, fRatioX, fRatioY, 1.f);

		D3DXMatrixTranslation(&matTrans, (*iter_begin)->vPos.x - m_pMainView->GetScrollPos(0), 300.f, 0.f);

		matWorld = matScale * matTrans;

		// SetTransform: ����� �ݿ��ϴ� �Լ�.
		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Front", L"Prop", (*iter_begin)->byDrawID);

		// �̹����� ���� ���ϱ�.
		int iCenterX = pTexInfo->tImgInfo.Width / 2;
		int iCenterY = pTexInfo->tImgInfo.Height / 2;

		// ������ ��� ������Ʈ�� �������� �� ���̿��� ����.
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
			nullptr /*����� �̹��� ������ RECT*/,
			&D3DXVECTOR3(iCenterX, iCenterY, 0.f) /*����� �̹����� �߽� ��ǥ D3DXVECTOR3*/,
			nullptr /*����� ��ġ ��ǥ D3DXVECTOR3*/,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

}

void CFrontLayer::Release()
{
	for_each(m_FrontTerrainLst.begin(), m_FrontTerrainLst.end(), SafeDelete<TERRAIN*>);
	m_FrontTerrainLst.clear();
}

void CFrontLayer::PopFrontTerrainLst()
{
	if (m_FrontTerrainLst.empty())
		return;

	m_FrontTerrainLst.pop_back();
}