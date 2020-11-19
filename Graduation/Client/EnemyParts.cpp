#include "stdafx.h"
#include "EnemyParts.h"


CEnemyParts::CEnemyParts()
{
}


CEnemyParts::~CEnemyParts()
{
}

void CEnemyParts::Update(int iMessage, void * pData)
{
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
		}
	}
}
