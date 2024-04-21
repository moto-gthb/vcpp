
// MFC_OpenCV2.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// メイン シンボル


// CMFCOpenCV2App:
// このクラスの実装については、MFC_OpenCV2.cpp を参照してください
//

class CMFCOpenCV2App : public CWinApp
{
public:
	CMFCOpenCV2App();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CMFCOpenCV2App theApp;
