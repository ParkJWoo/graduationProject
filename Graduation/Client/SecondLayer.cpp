#include "stdafx.h"
#include "SecondLayer.h"

CSecondLayer::CSecondLayer()
{
}


CSecondLayer::~CSecondLayer()
{
	Release();
}

HRESULT CSecondLayer::Initialize()
{
	//m_vecInfo.clear();

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Prop/SecondLayer/Second%d.png", L"Second",
		TEX_MULTI, L"Prop", 2)))
	{
		ERR_MSG(L"Second Layer Props Insert Failed!!!");
		return E_FAIL;
	}

	if (FAILED(LoadObjects()))
		return E_FAIL;

	m_tInfo.vSize = { 200.f,210.f,0.f };


	//for (size_t i = 0; i < m_vecTerrain.size(); i++)
	//{
	//	D3DXMatrixIdentity(&m_vecTerrain[i]->matWorld);
	//	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	//	D3DXMatrixTranslation(&matTrans,
	//		m_vecTerrain[i]->vPos.x, m_vecTerrain[i]->vPos.y, m_vecTerrain[i]->vPos.z);

	//	m_vecTerrain[i]->matWorld = matScale * matTrans;

	//	CObj* tInfo = {};


	//	//m_vecInfo.push_back(tInfo);
	//}

	return S_OK;
}

int CSecondLayer::Update()
{
	//cout << "Props Position: " << m_tRect.left << ", " << m_tRect.right << endl;

	//cout << "2번째 프랍 위치: " << m_TerrainLst.back()->vPos.x << endl;

	D3DXMatrixIdentity(&m_tInfo.matWorld);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTrans;

	return NO_EVENT;
}

void CSecondLayer::LateUpdate()
{
}

void CSecondLayer::Render()
{
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
		L"Second", L"Prop", 0);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CSecondLayer::Release()
{
	/*for_each(m_vecTerrain.begin(), m_vecTerrain.end(), SafeDelete<TERRAIN*>);
	m_vecTerrain.clear();
	m_vecTerrain.shrink_to_fit();*/
}

HRESULT CSecondLayer::LoadObjects()
{
	HANDLE hFile = CreateFile(L"../Data/SecondLayerData/SceneTest.dat", GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		ERR_MSG(L"Second Layer Data Load Failed!!");
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

		m_vecTerrain.push_back(pTerrain);
	}

	CloseHandle(hFile);
	return S_OK;
}