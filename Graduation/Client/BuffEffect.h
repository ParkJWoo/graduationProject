#pragma once
#include "Effect.h"
class CBuffEffect :
	public CEffect
{
public:
	CBuffEffect();
	virtual ~CBuffEffect();

public:
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	CObj*	m_pTarget;	// 공전 대상. (부모 행렬)
	float	m_fRevAngle; // 공전 각도.
};

