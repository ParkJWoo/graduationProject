#include "stdafx.h"
#include "BackLayer.h"

CBackLayer::CBackLayer()
	:m_fAngle(0.f), m_fRotSpeed(0.0001f)
{
}

CBackLayer::~CBackLayer()
{
	Release();
}

HRESULT CBackLayer::LoadBackLayer()
{
	HANDLE hFile = CreateFile(L"../Data/BackLayerData.Scene1.dat", GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		ERR_MSG(L"BackLayerData Load Failed!!");
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
		m_BackTerrainLst.push_back(pTerrain);
	}

	CloseHandle(hFile);
	return S_OK;
}

HRESULT CBackLayer::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Prop/Back/Back%d.png", L"Back",
		TEX_MULTI, L"Prop", 3)))
	{
		ERR_MSG(L"Back Layer Props Insert Failed!!!");
		return E_FAIL;
	}

	/*if (FAILED(LoadBackLayer()))
		return E_FAIL;*/

	return S_OK;
}

int CBackLayer::Update()
{
	m_fAngle += m_fRotSpeed;

	if (m_fAngle >= 0.5f)
	{
		m_fRotSpeed *= -1.f;
	}

	if (m_fAngle <= -0.5f)
	{
		m_fRotSpeed *= -1.f;
	}

	D3DXMATRIX matScale, matRotZ, matTrans;

	D3DXMatrixIdentity(&m_tInfo.matWorld);

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);

	D3DXMatrixRotationZ(&matRotZ, m_fAngle);

	//D3DXMatrixRotationAxis(&matRotZ, &D3DXVECTOR3(0.f, 0.f, -400.f), m_fAngle);

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	//m_tInfo.matWorld = matScale * matRotZ * matTrans;

	m_tInfo.matWorld = matScale * matTrans;


	return NO_EVENT;
}

void CBackLayer::LateUpdate()
{
}

void CBackLayer::Render()
{
	//RECT rcWnd = {};

	//::GetClientRect(g_hWnd, &rcWnd);

	//float fRatioX = WINCX / float(rcWnd.right - rcWnd.left);
	//float fRatioY = WINCY / float(rcWnd.bottom - rcWnd.top);

	//D3DXMATRIX matScale, matTrans, matWorld;

	//list<TERRAIN*>::iterator	iter_begin = m_BackTerrainLst.begin();
	//list<TERRAIN*>::iterator	iter_end = m_BackTerrainLst.end();

	//for (; iter_begin != iter_end; ++iter_begin)
	//{
	//	D3DXMatrixScaling(&matScale, fRatioX, fRatioY, 1.f);

	//	D3DXMatrixTranslation(&matTrans, (*iter_begin)->vPos.x - CScrollMgr::GetScroll().x, 0.f - CScrollMgr::GetScroll().y, 0.f);

	//	matWorld = matScale * matTrans;

	//	// SetTransform: 행렬을 반영하는 함수.
	//	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	//	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Back", L"Prop", (*iter_begin)->byDrawID);

	//	// 이미지의 중점 구하기.
	//	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	//	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	//	// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	//	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
	//		nullptr /*출력할 이미지 영역의 RECT*/,
	//		&D3DXVECTOR3(iCenterX, 0.f, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
	//		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
	//		D3DCOLOR_ARGB(255, 255, 255, 255));
	//}

	// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	//const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Back", L"Prop", (*iter_begin)->byDrawID);
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Back", L"Prop", m_iDrawID);

	// 이미지의 중점 구하기.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)iCenterX, (float)(iCenterY), 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBackLayer::Release()
{
	/*for_each(m_BackTerrainLst.begin(), m_BackTerrainLst.end(), SafeDelete<TERRAIN*>);
	m_BackTerrainLst.clear();*/
}