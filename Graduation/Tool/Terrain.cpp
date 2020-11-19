#include "stdafx.h"
#include "Terrain.h"
#include "ToolView.h"

CTerrain::CTerrain()
	: m_pMainView(nullptr)
{
}


CTerrain::~CTerrain()
{
	Release();
}

void CTerrain::Initialize()
{
	// ��Ƽ �ؽ��� �ε�
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Tile/Tile%d.png", L"Terrain",
		TEX_MULTI, L"Tile", 39)))
	{
		AfxMessageBox(L"Terrain Image Insert Failed!!!");
		return;
	}

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			TILE* pTile = new TILE;

			float fX = float(TILECX * 0.5f + TILECX * j);
			float fY = float((TILECY * 0.5f + TILECY * i));

			pTile->vPos = D3DXVECTOR3(fX, fY, 0.f);
			pTile->vSize = D3DXVECTOR3((float)TILECX, (float)TILECY, 0.f);
			pTile->byOption = 0;
			pTile->byDrawID = 38;
			pTile->iIndex = j + (TILEX * i);
			pTile->iParentIdx = 0;

			m_vecTile.push_back(pTile);
		}
	}
}

void CTerrain::Update()
{
}

void CTerrain::Render()
{
	// ȭ�� ũ�⿡ ���� ������ ����.
	RECT rcWnd = {};

	// GetWindowRect: ���� �����츦 ���ΰ� �ִ� ��ũ�ѹٳ� �������� ũ����� ���´�.
	//m_pMainView->GetWindowRect(&rcWnd);

	// GetClientRect: ���ڷ� ������ �������� ��Ȯ�� View������ ���´�.
	::GetClientRect(m_pMainView->m_hWnd, &rcWnd);

	float fRatioX = WINCX / float(rcWnd.right - rcWnd.left);
	float fRatioY = WINCY / float(rcWnd.bottom - rcWnd.top);

	D3DXMATRIX matWorld, matScale, matTrans;

	TCHAR szIndex[MIN_STR] = L"";

	for (size_t i = 0; i < m_vecTile.size(); ++i )
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, fRatioX * 0.5f, fRatioY * 0.5f, 0.f);
		D3DXMatrixTranslation(&matTrans, 
			(m_vecTile[i]->vPos.x - m_pMainView->GetScrollPos(0)/*0: x�� ��ũ�� ��*/) * fRatioX,
			(m_vecTile[i]->vPos.y - m_pMainView->GetScrollPos(1)/*1: y�� ��ũ�� ��*/) * fRatioY,
			m_vecTile[i]->vPos.z);

		matWorld = matScale * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
			L"Terrain", L"Tile", m_vecTile[i]->byDrawID);

		if (nullptr == pTexInfo)
			continue;

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		// ��Ʈ ���
		swprintf_s(szIndex, L"Tile: %d", i + 1);

		CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(),
			szIndex, lstrlen(szIndex), CRect(-(int)fCenterX, -(int)fCenterY, 400, 100), 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CTerrain::MiniRender()
{
	D3DXMATRIX matWorld, matScale, matTrans;

	TCHAR szIndex[MIN_STR] = L"";

	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 0.3f, 0.3f, 0.f);
		D3DXMatrixTranslation(&matTrans,
			m_vecTile[i]->vPos.x * 0.3f,
			m_vecTile[i]->vPos.y * 0.3f,
			m_vecTile[i]->vPos.z);

		matWorld = matScale * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
			L"Terrain", L"Tile", m_vecTile[i]->byDrawID);

		if (nullptr == pTexInfo)
			continue;

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));		
	}
}

void CTerrain::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), SafeDelete<TILE*>);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

void CTerrain::TileChange(const D3DXVECTOR3 & vPos, const int & iDrawID, int iOption)
{
	int iIndex = GetTileIndex(vPos);

	if (-1 == iIndex)
		return;

	m_vecTile[iIndex]->byDrawID = iDrawID;
	m_vecTile[iIndex]->byOption = iOption;
}

int CTerrain::GetTileIndex(const D3DXVECTOR3& vPos)
{
	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		if (Picking(vPos, i))
			return i;
	}

	return -1;	// �ε��� ã�� ����!
}

bool CTerrain::Picking(const D3DXVECTOR3 & vPos, const int & iIndex)
{
	// ������ �̿��� ��ŷ

	// 1. 12�ø� �������� �ð� ������ ������ �������� ���Ѵ�.
	D3DXVECTOR3 vPoint[4] =
	{
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + (TILECY * 0.5f), 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - (TILECY * 0.5f), 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y, 0.f)
	};

	// 2. �ð� �������� ���� ���͸� ���Ѵ�.
	D3DXVECTOR3 vDir[4] =
	{
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3],
	};

	// 3. �� ���� ���͸� ���Ѵ�.
	D3DXVECTOR3 vNormal[4] =
	{
		D3DXVECTOR3(-vDir[0].y, vDir[0].x, 0.f),
		D3DXVECTOR3(-vDir[1].y, vDir[1].x, 0.f),
		D3DXVECTOR3(-vDir[2].y, vDir[2].x, 0.f),
		D3DXVECTOR3(-vDir[3].y, vDir[3].x, 0.f),
	};

	// 4. ���� ���� ���͵��� �������ͷ� ����� �ش�.
	for (int i = 0; i < 4; ++i)
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);

	// 5. �� �������� ���콺 ���� ���⺤�͸� ���Ѵ�.
	D3DXVECTOR3 vMouseDir[4] = 
	{
		vPos - vPoint[0],
		vPos - vPoint[1],
		vPos - vPoint[2],
		vPos - vPoint[3]
	};

	for (int i = 0; i < 4; ++i)
		D3DXVec3Normalize(&vMouseDir[i], &vMouseDir[i]);

	// 4�鿡 ���ؼ� vMouseDir�� vNormal�� �����Ͽ� ���� ����� �а�(����)�̸� true!
	for (int i = 0; i < 4; ++i)
	{
		// �ϳ��� ����� ������ false
		if (0.f < D3DXVec3Dot(&vMouseDir[i], &vNormal[i]))
			return false;
	}

	return true;
}
