#include "stdafx.h"
#include "Fade.h"

#include "Button.h"

CFade::CFade()
{
}

CFade::~CFade()
{
	Release();
}

HRESULT CFade::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Intro/IntroBack.png", L"IntroBack", TEX_SINGLE)))
	{
		ERR_MSG(L"IntroBackground Image Insert Failed!!!");
		return E_FAIL;
	}

	pStart = CAbstractFactory<CButton>::CreateObj(D3DXVECTOR3(1700.f, 80.f, 0.f));
	dynamic_cast<CButton*>(pStart)->SetImageKey(L"Start");

	return S_OK;
}

int CFade::Update()
{
	m_fAlphaCnt += (float)0.05;
	return NO_EVENT;
}

void CFade::LateUpdate()
{
	//if (pStart->GetClicked() == true)
	//{

	//}
}

void CFade::Render()
{
	const TEXINFO* pTexInfo3 = CTextureMgr::GetInstance()->GetTexture(L"IntroBack");

	D3DXMATRIX matScale3, matRotZ3, matTrans3, matWorld3;

	D3DXMatrixScaling(&matScale3, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans3, 500.f, 300.f, 0.f);

	matWorld3 = matScale3 * matTrans3;

	//// SetTransform: ����� �ݿ��ϴ� �Լ�.
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld3);

	//// �̹����� ���� ���ϱ�.
	int iCenterX3 = pTexInfo3->tImgInfo.Width / 2;
	int iCenterY3 = pTexInfo3->tImgInfo.Height / 2;

	//// ������ ��� ������Ʈ�� �������� �� ���̿��� ����.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo3->pTexture,
		nullptr /*����� �̹��� ������ RECT*/,
		&D3DXVECTOR3((float)iCenterX3, (float)iCenterY3, 0.f) /*����� �̹����� �߽� ��ǥ D3DXVECTOR3*/,
		nullptr /*����� ��ġ ��ǥ D3DXVECTOR3*/,
		D3DCOLOR_ARGB((int)m_fAlphaCnt, 255, 255, 255));
}

void CFade::Release()
{
}
