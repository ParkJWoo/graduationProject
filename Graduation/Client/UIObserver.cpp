#include "stdafx.h"
#include "UIObserver.h"


CUIObserver::CUIObserver()
{
}


CUIObserver::~CUIObserver()
{
}

void CUIObserver::Update(int iMessage, void * pData)
{
	// 필요한 정보를 Subject로부터 요청할 것 -> pull 옵저버 패턴.
	list<void*>* pDataLst = CDataSubject::GetInstance()->GetDataLst(iMessage);

	if (nullptr != pDataLst)
	{
		// find: <algorithm>에서 제공하는 탐색 함수.
		auto iter_find = find(pDataLst->begin(), pDataLst->end(), pData);

		if (pDataLst->end() == iter_find)
			return;

		switch (iMessage)
		{
		case PLAYER_DATA:
			m_tData = *reinterpret_cast<DATA*>(*iter_find);
			break;
		case PLAYER_MATRIX:
			m_matWorld = *reinterpret_cast<D3DXMATRIX*>(*iter_find);
			break;
		case CAMERA_MATRIX:
			m_matWorld = *reinterpret_cast<D3DXMATRIX*>(*iter_find);
			break;
		case ENEMY_DATA:
			m_tData = *reinterpret_cast<DATA*>(*iter_find);
			break;
		case ENEMY_MATRIX:
			m_matWorld = *reinterpret_cast<D3DXMATRIX*>(*iter_find);
			break;
		}
	}
}
