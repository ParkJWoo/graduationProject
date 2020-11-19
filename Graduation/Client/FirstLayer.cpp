#include "stdafx.h"
#include "FirstLayer.h"

CFirstLayer::CFirstLayer()
{
}


CFirstLayer::~CFirstLayer()
{
	Release();
}

HRESULT CFirstLayer::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Prop/FirstLayer/First%d.png", L"First",
		TEX_MULTI, L"Prop", 8)))
	{
		ERR_MSG(L"First Layer Props Image Insert Failed!!!");
		return E_FAIL;
	}

	/*if (FAILED(LoadObjects()))
		return E_FAIL;*/

	/*list<TERRAIN*>::iterator iter_begin = m_TerrainLst.begin();
	list<TERRAIN*>::iterator iter_end = m_TerrainLst.end();

	for (; iter_begin != iter_end; ++iter_begin)
	{
		pTerrain->vPos = (*iter_begin)->vPos;
	}*/

	return S_OK;
}

int CFirstLayer::Update()
{
	D3DXMATRIX matScale, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matTrans;

	return NO_EVENT;
}

void CFirstLayer::LateUpdate()
{
}

void CFirstLayer::Render()
{
	//RECT rcWnd = {  };

	//::GetClientRect(g_hWnd, &rcWnd);
	//   
	//float fRatioX = WINCX / float(rcWnd.right - rcWnd.left);
	//float fRatioY = WINCY / float(rcWnd.bottom - rcWnd.top);

	//D3DXMATRIX matScale, matTrans, matWorld;

	//list<TERRAIN*>::iterator iter_begin = m_TerrainLst.begin();
	//list<TERRAIN*>::iterator iter_end = m_TerrainLst.end();

	//for (; iter_begin != iter_end; ++iter_begin)
	//{
	//	D3DXMatrixScaling(&matScale, fRatioX, fRatioY, 1.f);

	//	D3DXMatrixTranslation(&matTrans, ((*iter_begin)->vPos.x - 200.f), 455.f, 0.f);
	//	//D3DXMatrixTranslation(&matTrans, ((*iter_begin)->vPos.x - 509.603f) - CScrollMgr::GetScroll().x, 450.f, 0.f);

	//	matWorld = matScale * matTrans;

	//	// SetTransform: 행렬을 반영하는 함수.
	//	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	//	//const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"First", L"Prop", (*iter_begin)->byDrawID);
	//	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"First", L"Prop", m_iDrawID);


	//	// 이미지의 중점 구하기.
	//	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	//	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	//	// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	//	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
	//		nullptr /*출력할 이미지 영역의 RECT*/,
	//		&D3DXVECTOR3(iCenterX, iCenterY, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
	//		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
	//		D3DCOLOR_ARGB(255, 255, 255, 255));
	//}


	// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	//const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"First", L"Prop", (*iter_begin)->byDrawID);
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"First", L"Prop", m_iDrawID);

	// 이미지의 중점 구하기.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)iCenterX, (float)iCenterY, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CFirstLayer::Release()
{
	/*for_each(m_TerrainLst.begin(), m_TerrainLst.end(), SafeDelete<TERRAIN*>);
	m_TerrainLst.clear();*/
}

HRESULT CFirstLayer::LoadObjects()
{
	HANDLE hFile = CreateFile(L"../Data/FirstLayerData/Scene1.dat", GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		ERR_MSG(L"First Layer Load Failed!!");
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

		pTerrain = new TERRAIN(tTerrain);
		m_TerrainLst.push_back(pTerrain);
	}

	CloseHandle(hFile);
	return S_OK;
}