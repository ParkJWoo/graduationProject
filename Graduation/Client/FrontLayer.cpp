#include "stdafx.h"
#include "FrontLayer.h"

CFrontLayer::CFrontLayer()
{
}


CFrontLayer::~CFrontLayer()
{
	Release();
}

HRESULT CFrontLayer::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Prop/Front/Front%d.png", L"Front",
		TEX_MULTI, L"Prop", 2)))
	{
		ERR_MSG(L"First Layer Props Image Insert Failed!!!");
		return E_FAIL;
	}

	return S_OK;
}

int CFrontLayer::Update()
{
	return NO_EVENT;
}

void CFrontLayer::LateUpdate()
{
}

void CFrontLayer::Render()
{
	//RECT rcWnd = {  };

	//::GetClientRect(g_hWnd, &rcWnd);

	//float fRatioX = WINCX / float(rcWnd.right - rcWnd.left);
	//float fRatioY = WINCY / float(rcWnd.bottom - rcWnd.top);

	//D3DXMATRIX matScale, matTrans, matWorld;

	//list<TERRAIN*>::iterator iter_begin = m_FrontTerrainLst.begin();
	//list<TERRAIN*>::iterator iter_end = m_FrontTerrainLst.end();

	//for (; iter_begin != iter_end; ++iter_begin)
	//{
	//	D3DXMatrixScaling(&matScale, fRatioX, fRatioY, 1.f);

	//	D3DXMatrixTranslation(&matTrans, (*iter_begin)->vPos.x - CScrollMgr::GetScroll().x, 300.f, 0.f);

	//	matWorld = matScale * matTrans;

	//	// SetTransform: ����� �ݿ��ϴ� �Լ�.
	//	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	//	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Front", L"Prop", 0);

	//	// �̹����� ���� ���ϱ�.
	//	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	//	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	//	// ������ ��� ������Ʈ�� �������� �� ���̿��� ����.
	//	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
	//		nullptr /*����� �̹��� ������ RECT*/,
	//		&D3DXVECTOR3(iCenterX, iCenterY, 0.f) /*����� �̹����� �߽� ��ǥ D3DXVECTOR3*/,
	//		nullptr /*����� ��ġ ��ǥ D3DXVECTOR3*/,
	//		D3DCOLOR_ARGB(255, 255, 255, 255));
	//}

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
		L"Front", L"Prop", 0);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX - 800.f, fCenterY - 300.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CFrontLayer::Release()
{
	for_each(m_FrontTerrainLst.begin(), m_FrontTerrainLst.end(), SafeDelete<TERRAIN*>);
	m_FrontTerrainLst.clear();
}

HRESULT CFrontLayer::LoadFrontLayer()
{
	return E_NOTIMPL; HANDLE hFile = CreateFile(L"../Data/FrontLayerData.Scene1.dat", GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		ERR_MSG(L"Front Laye Data Load Failed!!");
		return E_FAIL;
	}

	Release();

	TERRAIN tTerrain = {};
	DWORD dwByte = 0;

	while (true)
	{
		ReadFile(hFile, &tTerrain, sizeof(TERRAIN), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		TERRAIN* pTerrain = new TERRAIN(tTerrain);
		m_FrontTerrainLst.push_back(pTerrain);
	}

	CloseHandle(hFile);
	return S_OK;
}