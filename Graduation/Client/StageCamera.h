#pragma once
class CStageCamera
{
	DECLARE_SINGLETON(CStageCamera)
private:
	CStageCamera();
	~CStageCamera();

public:
	void SetTransform();

public:
	HRESULT Initialize(int iWidth, int iHeight, float fAngle, D3DXVECTOR3 vFaceFactors);
	void Update();
	void Following();
	void UnFollow();

	void Release();

	bool isFollowing();
	void isShake();

private:
	float	m_fSpeed;
	float m_fAngle;

	D3DXVECTOR3 m_vScaleFactors;

	D3DXMATRIX m_matOrthographic;
	D3DXMATRIX m_matIdentity;
	D3DXMATRIX m_matView;

	DATA m_tData;

	CObj* m_pTarget;

	int iWidth, iHeight;

	LPDIRECT3DDEVICE9 m_Device;

	CDevice* m_pDevice;

	D3DXMATRIX matCamera;

	bool		m_bIsShake = true;

	CObj* pHpCase;
	CObj* pHpBar;

	CObj* pMpBar;
	CObj* pMpBar2;
	CObj* pMpCase;

	CObj* pInvenIcon;
	CObj* pInventory;
};

