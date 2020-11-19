#include "stdafx.h"
#include "FirstLayer.h"
#include "ToolView.h"

CFirstLayer::CFirstLayer()
	:m_pMainView(nullptr), m_iPropDrawID(0)
{
}


CFirstLayer::~CFirstLayer()
{
	Release();
}

void CFirstLayer::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Prop/FirstLayer/First%d.png", L"First",
		TEX_MULTI, L"Prop", 3)))
	{
		AfxMessageBox(L"First Layer Props Image Insert Failed!!!");
		return;
	}
}

void CFirstLayer::Update()
{
	TERRAIN* pTerrain = new TERRAIN;

	pTerrain->vPos = vPosition;
	pTerrain->byDrawID = m_iPropDrawID;
	pTerrain->byOption = 0;

	m_FirstTerrainLst.push_back(pTerrain);
}

void CFirstLayer::Render(/*list<TERRAIN*> pTerrainLst*/)
{
	CRect rcWnd = {  };

	::GetClientRect(m_pMainView->m_hWnd, &rcWnd);

	float fRatioX = WINCX / float(rcWnd.right - rcWnd.left);
	float fRatioY = WINCY / float(rcWnd.bottom - rcWnd.top);

	D3DXMATRIX matScale, matTrans, matWorld;

	list<TERRAIN*>::iterator iter_begin = m_FirstTerrainLst.begin();
	list<TERRAIN*>::iterator iter_end = m_FirstTerrainLst.end();

	for (; iter_begin != iter_end; ++iter_begin)
	{
		D3DXMatrixScaling(&matScale, fRatioX, fRatioY, 1.f);

		D3DXMatrixTranslation(&matTrans, (*iter_begin)->vPos.x - m_pMainView->GetScrollPos(0), 420.f, 0.f);

		matWorld = matScale * matTrans;

		// SetTransform: ����� �ݿ��ϴ� �Լ�.
		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"First", L"Prop", (*iter_begin)->byDrawID);

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

void CFirstLayer::Release()
{
	for_each(m_FirstTerrainLst.begin(), m_FirstTerrainLst.end(), SafeDelete<TERRAIN*>);
	m_FirstTerrainLst.clear();
}

void CFirstLayer::PopFirstTerrainLst()
{
	if (m_FirstTerrainLst.empty())
		return;

	m_FirstTerrainLst.pop_back();
}
