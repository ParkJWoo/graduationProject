#include "stdafx.h"
#include "EffectIMP.h"


CEffectIMP::CEffectIMP()
	: m_pObj(nullptr), m_bIsInit(false), m_wstrStateKey(L"")
{
}


CEffectIMP::~CEffectIMP()
{
}

void CEffectIMP::LateInit()
{
	if (!m_bIsInit)
	{
		this->LateInit();
		m_bIsInit = true;
	}
}
