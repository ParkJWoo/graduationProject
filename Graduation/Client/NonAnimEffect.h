#pragma once
#include "EffectIMP.h"
class CNonAnimEffect :
	public CEffectIMP
{
public:
	CNonAnimEffect();
	virtual ~CNonAnimEffect();

public:
	void SetTime(float fLifeTime) { m_fLifeTime = fLifeTime; }

public:
	// CEffectIMP��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	float	m_fLifeTime;	// �����ð�
	float	m_fTime;		// �����ð�
};

