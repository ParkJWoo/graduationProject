#pragma once
#include "Obj.h"
class CCageDoor :
	public CObj
{
public:
	CCageDoor();
	virtual ~CCageDoor();

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	LARGE_INTEGER	m_CurTime;
	LARGE_INTEGER	m_OldTime1;
	LARGE_INTEGER	m_OldTime2;
	LARGE_INTEGER	m_CpuTick;	// Cpu ������(Ŭ�� ��)

	float			m_fTime;

};

