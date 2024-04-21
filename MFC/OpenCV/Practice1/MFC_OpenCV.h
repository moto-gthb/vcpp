
// MFC_OpenCV.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// メイン シンボル


// CMFCOpenCVApp:
// このクラスの実装については、MFC_OpenCV.cpp を参照してください
//

class CMFCOpenCVApp : public CWinApp
{
public:
	CMFCOpenCVApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CMFCOpenCVApp theApp;
