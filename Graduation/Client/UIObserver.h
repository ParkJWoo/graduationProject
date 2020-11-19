#pragma once
#include "Observer.h"
class CUIObserver :
	public CObserver
{
public:
	CUIObserver();
	virtual ~CUIObserver();

public:
	const DATA& GetData() const { return m_tData; }
	const D3DXMATRIX& GetMatrix() const { return m_matWorld; }

public:
	// CObserver��(��) ���� ��ӵ�
	virtual void Update(int iMessage, void * pData) override;

private:
	DATA		m_tData;
	D3DXMATRIX	m_matWorld;
};

