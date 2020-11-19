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
	// �ʿ��� ������ Subject�κ��� ��û�� �� -> pull ������ ����.
	list<void*>* pDataLst = CDataSubject::GetInstance()->GetDataLst(iMessage);

	if (nullptr != pDataLst)
	{
		// find: <algorithm>���� �����ϴ� Ž�� �Լ�.
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
