#include "stdafx.h"
#include "KeyMgr.h"

IMPLEMENT_SINGLETON(CKeyMgr)

CKeyMgr::CKeyMgr()
	: m_dwKey(0), m_dwKeyPressed(0), m_dwKeyDown(0)
{
}


CKeyMgr::~CKeyMgr()
{
}

// �� �����Ӹ��� ȣ���Ͽ� ���� Ű�� �����Ѵ�.
void CKeyMgr::KeyCheck()
{
	m_dwKey = 0;	// 0000

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		m_dwKey |= KEY_LBUTTON;	// 0000 |= 0001
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		m_dwKey |= KEY_RBUTTON; // 0001 |= 0010
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_dwKey |= KEY_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_dwKey |= KEY_RIGHT; // 0001 |= 0010
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_dwKey |= KEY_UP; 
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_dwKey |= KEY_DOWN;
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		m_dwKey |= KEY_RETURN;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		m_dwKey |= KEY_SPACE;
	if (GetAsyncKeyState('A') & 0x8000)
		m_dwKey |= KEY_A;
	if (GetAsyncKeyState('D') & 0x8000)
		m_dwKey |= KEY_D;
	if (GetAsyncKeyState('I') & 0x8000)
		m_dwKey |= KEY_I;
	if (GetAsyncKeyState('X') & 0x8000)
		m_dwKey |= KEY_X;

	// m_dwKey = 0011
}

bool CKeyMgr::KeyUp(DWORD dwKey)
{
	// dwKey(���� �˻��ϴ� Ű)�� m_dwKey(���� ���� Ű) �߿� �ߺ��Ǵ� ��Ʈ���� �ִ��� �˻�.
	if (m_dwKey & dwKey)
	{
		m_dwKeyPressed |= dwKey;
		return false;
	}
	// m_dwKeyPressed(������ ���ȴ� Ű)�� dwKey(���� �˻��ϴ� Ű) �߿� 
	// �ߺ��Ǵ� ��Ʈ���� �ִ��� �˻�. �ִٸ� ������ �ִٴ� ��.
	else if (m_dwKeyPressed & dwKey)
	{
		m_dwKeyPressed ^= dwKey;
		return true;
	}

	return false;
}

bool CKeyMgr::KeyDown(DWORD dwKey)
{
	// ���� �������� ���ſ� ������ ���� ��� True
	if ((m_dwKey & dwKey) && !(m_dwKeyDown & dwKey))
	{
		m_dwKeyDown |= dwKey;
		return true;
	}
	// ���� ������ �ʾ����� ���ſ� ������ �ִ� ��� false
	else if (!(m_dwKey & dwKey) && (m_dwKeyDown & dwKey))
	{
		m_dwKeyDown ^= dwKey;
		return false;
	}

	return false;
}

bool CKeyMgr::KeyPress(DWORD dwKey)
{
	if ((m_dwKey & dwKey) && (m_dwKeyDown & dwKey))
	{
		m_dwKeyDown |= dwKey;
		return true;
	}

	return false;
}

// �� Ű�� ������� ���� ��� ����.
bool CKeyMgr::KeyCombine(DWORD dwFirstKey, DWORD dwSecondKey)
{
	if (KeyDown(dwSecondKey) && (m_dwKey & dwFirstKey))
		return true;

	return false;
}