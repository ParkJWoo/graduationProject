#pragma once
class CEnemyParts
{
public:
	CEnemyParts();
	~CEnemyParts();

public:
	const D3DXMATRIX& GetMatrix() const { return m_matWorld; }

public:
	void Update(int iMessage, void* pData);

private:
	DATA m_tData;
	D3DXMATRIX m_matWorld;
};

