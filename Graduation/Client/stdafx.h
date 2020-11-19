// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

//	콘솔창 띄움
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>


// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <string>
#include <io.h>
#include <ctime>

#include <iostream>

using namespace std;

// d3d9: 장치(GPU)를 제어하기 위한 자료형이나 함수를 제공한다.
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

//#include "fmod.h"
//#pragma comment(lib, "fmodex_vc.lib")
//#pragma comment(lib, "fmodx_vc.lib")

#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
//#include <stdio.h>

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")


// d3dx9: 다이렉트에서 사용할 벡터, 행렬 자료형이나 연산함수들을 제공한다.
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "Extern.h"
#include "Define.h"
#include "Constant.h"
#include "Typedef.h"
#include "Enum.h"
#include "Struct.h"
#include "Function.h"
#include "Functor.h"

// managers
#include "TimeMgr.h"
#include "Device.h"
#include "TextureMgr.h"
#include "AbstractFactoy.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "ScrollMgr.h"
#include "DataSubject.h"
#include "Camera.h"
#include "Stage2Camera.h"
#include "CStageCamera.h"
#include "StageCamera.h"
#include "LineMgr.h"
#include "CollisionMgr.h"
#include "Stage2LineMgr.h"
#include "TutorialSound.h"
//#include "MathMgr.h"