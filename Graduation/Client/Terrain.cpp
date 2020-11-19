#include "stdafx.h"
#include "Terrain.h"
#include "Mouse.h"

CTerrain::CTerrain()
{

}

CTerrain::~CTerrain()
{
	Release();
}

HRESULT CTerrain::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Tile/Tile%d.png", 
		L"Terrain", TEX_MULTI, L"Tile", 39)))
	{
		ERR_MSG(L"Tile Texture Load Failed!");
		return E_FAIL;
	}

	if (FAILED(LoadTile()))
		return E_FAIL;

	return S_OK;
}

void CTerrain::LateInit()
{
	//ReadyAdjacency();
}

int CTerrain::Update()
{
	CObj::LateInit();	

	float fTime = CTimeMgr::GetInstance()->GetTime();

	if (0 > CMouse::GetMouse().x)
		CScrollMgr::SetScroll(500.f * fTime, 0.f);
	if (WINCX < CMouse::GetMouse().x)
		CScrollMgr::SetScroll(-500.f * fTime, 0.f);
	if (0 > CMouse::GetMouse().y)
		CScrollMgr::SetScroll(0.f, 500.f * fTime);
	if (WINCY < CMouse::GetMouse().y)
		CScrollMgr::SetScroll(0, -500.f * fTime);

	return NO_EVENT;
}

void CTerrain::LateUpdate()
{
}

void CTerrain::Render()
{
	D3DXMATRIX matScale, matTrans;

	// 컬링 적용.
	D3DXVECTOR3 vScroll = CScrollMgr::GetScroll();

	int iCullX = -(int)vScroll.x / TILECX;
	int iCullY = -(int)vScroll.y / (TILECY / 2);

	int iCullEndX = iCullX + WINCX / TILECX;
	int iCullEndY = iCullY + WINCY / (TILECY / 2);

	for (int i = iCullY; i < iCullEndY + 3; ++i)
	{
		for (int j = iCullX; j < iCullEndX + 2; ++j)
		{
			int iIndex = j + (TILEX * i);

			if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
				continue;

			D3DXMatrixIdentity(&m_tInfo.matWorld);
			D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 0.f);
			D3DXMatrixTranslation(&matTrans,
				m_vecTile[iIndex]->vPos.x + CScrollMgr::GetScroll().x,
				m_vecTile[iIndex]->vPos.y + CScrollMgr::GetScroll().y,
				m_vecTile[iIndex]->vPos.z);

			m_tInfo.matWorld = matScale * matTrans;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
				L"Terrain", L"Tile", m_vecTile[iIndex]->byDrawID);

			if (nullptr == pTexInfo)
				continue;

			float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
			float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

			CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
				&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}	
}

void CTerrain::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), SafeDelete<TILE*>);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

HRESULT CTerrain::LoadTile()
{
	/*HANDLE hFile = CreateFile(L"../Data/MapData4.dat", GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		ERR_MSG(L"Tile Load Failed!!");
		return E_FAIL;
	}			

	Release();

	TILE tTile = {};
	DWORD dwByte = 0;

	while (true)
	{
		ReadFile(hFile, &tTile, sizeof(TILE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		TILE* pTile = new TILE(tTile);
		m_vecTile.push_back(pTile);
	}

	CloseHandle(hFile);
	return S_OK;*/

	return S_OK;
}

// 인접관계를 구성하는 함수. (그래프를 구성)
//void CTerrain::ReadyAdjacency()
//{
//	m_vecAdjacency.resize(m_vecTile.size());
//
//	for (int i = 0; i < TILEY; ++i)
//	{
//		for (int j = 0; j < TILEX; ++j)
//		{
//			int iIndex = j + (TILEX * i);
//
//			// 8방향에 대해서 이웃관계를 검사한다.
//
//			// 상
//			if (0 <= iIndex - TILEX * 2 && 1 != m_vecTile[iIndex - TILEX * 2]->byOption)
//				m_vecAdjacency[iIndex].push_back(m_vecTile[iIndex - TILEX * 2]);
//
//			// 하
//			if((int)m_vecTile.size() > iIndex + TILEX * 2 && 1 != m_vecTile[iIndex + TILEX * 2]->byOption)
//				m_vecAdjacency[iIndex].push_back(m_vecTile[iIndex + TILEX * 2]);
//
//			// 좌
//			if(0 != iIndex % TILEX && 1 != m_vecTile[iIndex - 1]->byOption)
//				m_vecAdjacency[iIndex].push_back(m_vecTile[iIndex - 1]);
//
//			// 우
//			if(iIndex != TILEX * (i + 1) - 1 && 1 != m_vecTile[iIndex + 1]->byOption)
//				m_vecAdjacency[iIndex].push_back(m_vecTile[iIndex + 1]);
//
//
//			// 좌상
//			if (0 != i && (0 != iIndex % (TILEX * 2)))
//			{
//				if( (0 != i % 2) && 1 != m_vecTile[iIndex - TILEX]->byOption)
//					m_vecAdjacency[iIndex].push_back(m_vecTile[iIndex - TILEX]);
//				else if((0 == i % 2) && 1 != m_vecTile[iIndex - (TILEX + 1)]->byOption)
//					m_vecAdjacency[iIndex].push_back(m_vecTile[iIndex - (TILEX + 1)]);
//			}
//
//			// 우상
//			if (0 != i && !((TILEX * 2 - 1) == iIndex % (TILEX * 2)))
//			{
//				if ((0 != i % 2) && 1 != m_vecTile[iIndex - (TILEX - 1)]->byOption)
//					m_vecAdjacency[iIndex].push_back(m_vecTile[iIndex - (TILEX - 1)]);
//				else if ((0 == i % 2) && 1 != m_vecTile[iIndex - TILEX]->byOption)
//					m_vecAdjacency[iIndex].push_back(m_vecTile[iIndex - TILEX]);
//			}
//
//			// 좌하
//			if ((0 != iIndex % (TILEX * 2)) && i != (TILEY - 1))
//			{
//				if( (0 != i % 2) && 1 != m_vecTile[iIndex + TILEX]->byOption)
//					m_vecAdjacency[iIndex].push_back(m_vecTile[iIndex + TILEX]);
//				else if( (0 == i % 2) && 1 != m_vecTile[iIndex + (TILEX - 1)]->byOption)
//					m_vecAdjacency[iIndex].push_back(m_vecTile[iIndex + (TILEX - 1)]);
//			}
//
//
//			// 우하
//			if (!((TILEX * 2 - 1) == iIndex % (TILEX * 2)) && i != (TILEY - 1))
//			{
//				if ((0 != i % 2) && 1 != m_vecTile[iIndex + (TILEX + 1)]->byOption)
//					m_vecAdjacency[iIndex].push_back(m_vecTile[iIndex + (TILEX + 1)]);
//				else if ((0 == i % 2) && 1 != m_vecTile[iIndex + TILEX]->byOption)
//					m_vecAdjacency[iIndex].push_back(m_vecTile[iIndex + TILEX]);
//			}
//		}
//	}
//}
