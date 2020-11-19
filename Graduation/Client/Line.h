#pragma once
class CLine
{
public:
	CLine();
	CLine(LINEINFO& rInfo);
	~CLine();

public:
	const LINEINFO& GetInfo() const { return m_tInfo; }

public:
	void Render();

private:
	LINEINFO m_tInfo;
};

