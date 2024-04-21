
// MFC_OpenCVDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "MFC_OpenCV.h"
#include "MFC_OpenCVDlg.h"
#include "afxdialogex.h"

#include "opencv2/opencv.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCOpenCVDlg ダイアログ



CMFCOpenCVDlg::CMFCOpenCVDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_OPENCV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCOpenCVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCOpenCVDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_RUN, &CMFCOpenCVDlg::OnClickedBtnRun)
END_MESSAGE_MAP()


// CMFCOpenCVDlg メッセージ ハンドラー

BOOL CMFCOpenCVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CMFCOpenCVDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CMFCOpenCVDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CMFCOpenCVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCOpenCVDlg::OnClickedBtnRun()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CDC *dc = GetDlgItem(IDC_PIC_IMG)->GetDC();
	HDC dstDC = dc->GetSafeHdc();	// 出力デバイスコンテキスト取得
	CRect rc;

	// ピクチャボックスサイズ取得
	GetDlgItem(IDC_PIC_IMG)->GetClientRect(&rc);

	// Matのリサイズ用サイズ設定（4の倍数）
	cv::Size size(rc.Width() & ~0x03, rc.Height() & ~0x03);

	// Mat作成
	cv::Mat img(size.width, size.height, CV_8UC3);

	// Matをピクチャボックス様にリサイズ
	cv::resize(img, img, size);

	// Line描画(mat, StartPoint, EndPoint, 色, 線幅, 連結)
	cv::line(img, cv::Point(0, 0), cv::Point(100, 100), cv::Scalar(255, 0, 0), 1, cv::LINE_8);

	// 矩形描画(mat, StartPoint), EndPoint, 色, 線幅, 連結)
	cv::rectangle(img, cv::Point(0, 110), cv::Point(100, 210), cv::Scalar(0, 0, 255), 1, cv::LINE_4);
	cv::rectangle(img, cv::Point(110, 110), cv::Point(210, 210), cv::Scalar(0, 255, 0), -1, cv::LINE_AA);

	// 円描画(mat, 中心座標, 半径, 色, 線幅, 連結)
	cv::circle(img, cv::Point(50, 270), 50, cv::Scalar(255, 255, 0), 1, cv::LINE_AA);
	cv::circle(img, cv::Point(160, 270), 50, cv::Scalar(0, 255, 255), -1, cv::LINE_AA);

	// 楕円・円弧描画(mat, 中心座標, (長径・短径）, 回転角度, 円弧開始角度, 円弧終了角度, 色, 線幅, 連結)
	cv::ellipse(img, cv::Point(50, 380), cv::Size(50, 30), 0, 0, 0 + 360, cv::Scalar(128, 0, 0), 1, cv::LINE_AA);
	cv::ellipse(img, cv::Point(160, 380), cv::Size(20, 50), 30, 0 - 200, 0 + 100, cv::Scalar(0, 128, 0), -1, cv::LINE_AA);

	// 折れ線描画
	cv::Point ptPoly[][2] =
	{
		{ cv::Point(210, 0), cv::Point(210, 100)},
		{ cv::Point(210, 100), cv::Point(310, 50)},
		{ cv::Point(210, 100), cv::Point(310, 150)},
	};
	const cv::Point *pptPoly[] = { ptPoly[0], ptPoly[1], ptPoly[2], ptPoly[3] };
	int iNppt[] = { 2, 2, 2 };
	cv::polylines(img, pptPoly, iNppt, _countof(iNppt), false, cv::Scalar(10, 200, 200), 3, cv::LINE_8);

	// ポリゴン
	cv::Point ptPoly2[][3] = 
	{
		{ cv::Point(210, 200), cv::Point(210, 300), cv::Point(260, 260)},
		{ cv::Point(210, 300), cv::Point(310, 250), cv::Point(310, 300)},
		{ cv::Point(210, 300), cv::Point(310, 350), cv::Point(310, 330)}
	};
	const cv::Point *pptPoly2[] = { ptPoly2[0], ptPoly2[1], ptPoly2[2], ptPoly2[3] };
	int iNppt2[] = { 3, 3, 3};
	cv::fillPoly(img, pptPoly2, iNppt2, _countof(iNppt2), cv::Scalar(200, 200, 10), cv::LINE_AA);

	// 下記のBITMAPINFOのbiHeightに正値を指定するため画像を上下反転（biHeightはもともと負）
	cv::flip(img, img, 0);

	// ビットマップ情報設定
	BITMAPINFO info = {};
	info.bmiHeader.biBitCount = 24;						// ピクセルあたりのビット数（RGB各8bit)
	info.bmiHeader.biWidth = size.width;				// ビットマップ幅（ピクセル）
	info.bmiHeader.biHeight = size.height;				// ビットマップ高さ（ピクセル）
	info.bmiHeader.biPlanes = 1;						// プレーン数（基本1）
	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);	// 構造体必要バイト数
	info.bmiHeader.biCompression = BI_RGB;				// 圧縮の種類（圧縮無し指定）

	// DIB（Bitmap）、JPG、PNGイメージ内のピクセル色データを指定した先へコピー
	StretchDIBits(	dstDC,	// ターゲットデバイスコンテキスハンドル
		0,					// コピー先左上隅X
		0,					// コピー先左上隅Y
		size.width,			// ターゲット四角形幅
		size.height,		// ターゲット四角形高さ
		0,					// コピー元X
		0,					// コピー元Y
		size.width,			// コピー元幅
		size.height,		// コピー元高さ
		img.data,			// 格納されるイメージビットポインター
		&info,				// BITMAPINFO構造体ポインター
		DIB_RGB_COLORS,		// BITMAPINFO構造体のbmiColorsが指定されたかどうかの指定（ここではリテラルRGB値） 
		SRCCOPY);			// 新しいイメージ作成方法（ここではコピー元四角形をコピー先四角形に直接コピー）

	ReleaseDC(dc);




}
