// AnimationTool.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "AnimationTool.h"
#include "afxdialogex.h"


// CAnimationTool 대화 상자

IMPLEMENT_DYNAMIC(CAnimationTool, CDialog)

CAnimationTool::CAnimationTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_OBJECTTOOL, pParent)
{

}

CAnimationTool::~CAnimationTool()
{
}

void CAnimationTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAnimationTool, CDialog)
END_MESSAGE_MAP()


// CAnimationTool 메시지 처리기
