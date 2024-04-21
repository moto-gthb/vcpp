
// MFC_OpenCV2Dlg.cpp : 実装ファイル
//

#include <vector>

#include "pch.h"
#include "framework.h"
#include "MFC_OpenCV2.h"
#include "MFC_OpenCV2Dlg.h"
#include "afxdialogex.h"
#include "opencv2/imgproc/types_c.h"
#include "opencv2/imgproc/imgproc_c.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

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


// CMFCOpenCV2Dlg ダイアログ



CMFCOpenCV2Dlg::CMFCOpenCV2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_OPENCV2_DIALOG, pParent)
	, m_sStcInfo(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCOpenCV2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_IMG, m_cPicImg);
	DDX_Text(pDX, IDC_STC_INFO, m_sStcInfo);
}

BEGIN_MESSAGE_MAP(CMFCOpenCV2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_READ_IMG, &CMFCOpenCV2Dlg::OnClickedBtnReadImg)
	ON_BN_CLICKED(IDC_BTN_GRAY, &CMFCOpenCV2Dlg::OnClickedBtnGray)
	ON_BN_CLICKED(IDC_BTN_THRESHOLD, &CMFCOpenCV2Dlg::OnClickedBtnThreshold)
	ON_BN_CLICKED(IDC_BTN_CORNERS, &CMFCOpenCV2Dlg::OnClickedBtnCorners)
	ON_BN_CLICKED(IDC_BTN_CONTOURS, &CMFCOpenCV2Dlg::OnClickedBtnContours)
	ON_BN_CLICKED(IDC_BTN_THINNING, &CMFCOpenCV2Dlg::OnClickedBtnThinning)
	ON_BN_CLICKED(IDC_BTN_SHAPE, &CMFCOpenCV2Dlg::OnClickedBtnShape)
END_MESSAGE_MAP()


// CMFCOpenCV2Dlg メッセージ ハンドラー

BOOL CMFCOpenCV2Dlg::OnInitDialog()
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

	// ピクチャボックスサイズ取得
	CRect rctImg;
	m_cPicImg.GetClientRect(&rctImg);
	rctImg.SetRect(rctImg.left + 10, rctImg.top + 10, 500 + rctImg.left, 500 + rctImg.top);
	m_cPicImg.MoveWindow(rctImg);

	// Matサイズ設定（4の倍数）
	Size szMatImg = Size(rctImg.Width() & ~0x03, rctImg.Height() & ~0x03);

	// Mat作成
	if (m_matImg.empty()) {
		m_matImg = Mat(szMatImg, CV_8UC3, Scalar::all(255));
	}

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CMFCOpenCV2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCOpenCV2Dlg::OnPaint()
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
	CDialog::UpdateWindow();
	CDC *pDc = m_cPicImg.GetDC();
	HDC dstDC = pDc->GetSafeHdc();

	// ピクチャボックスサイズ取得
	CRect rctImg;
	m_cPicImg.GetClientRect(&rctImg);

	// Matサイズ設定（4の倍数）
	Size szMatImg(rctImg.Width() & ~0x03, rctImg.Height() & ~0x03);

	// Mat作成
	Mat matImg(szMatImg, CV_8UC3, Scalar::all(255));
	m_matImg.copyTo(matImg);

	// MatをPictureBoxサイズにリサイズ
	resize(matImg, matImg, szMatImg);

	// 下記のBITMAPINFOのbiHeightに正値を指定するため画像を上下反転（biHeightはもともと負）
	flip(matImg, matImg, 0);

	// ビットマップ情報設定
	BITMAPINFO info = {};
	info.bmiHeader.biBitCount = 24;						// ピクセルあたりのビット数（RGB各8bit)
	info.bmiHeader.biWidth = szMatImg.width;			// ビットマップ幅（ピクセル）
	info.bmiHeader.biHeight = szMatImg.height;			// ビットマップ高さ（ピクセル）
	info.bmiHeader.biPlanes = 1;						// プレーン数（基本1）
	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);	// 構造体必要バイト数
	info.bmiHeader.biCompression = BI_RGB;				// 圧縮の種類（圧縮無し指定）

	// DIB（Bitmap）、JPG、PNGイメージ内のピクセル色データを指定した先へコピー
	StretchDIBits(dstDC,	// ターゲットデバイスコンテキスハンドル
		0,					// コピー先左上隅X
		0,					// コピー先左上隅Y
		szMatImg.width,		// ターゲット四角形幅
		szMatImg.height,	// ターゲット四角形高さ
		0,					// コピー元X
		0,					// コピー元Y
		szMatImg.width,		// コピー元幅
		szMatImg.height,	// コピー元高さ
		matImg.data,		// 格納されるイメージビットポインター
		&info,				// BITMAPINFO構造体ポインター
		DIB_RGB_COLORS,		// BITMAPINFO構造体のbmiColorsが指定されたかどうかの指定（ここではリテラルRGB値）
		SRCCOPY);			// 新しいイメージ作成方法（ここではコピー元四角形をコピー先四角形に直接コピー）

	ReleaseDC(pDc);
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CMFCOpenCV2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 画像読み込みボタンクリック
void CMFCOpenCV2Dlg::OnClickedBtnReadImg()
{
	// 画像読み込み
	m_matImg = imread(".\\Img\\test2.jpg");
	if (m_matImg.empty() == true) {
		return;
	}
	//imshow("test", m_matImg);

	// 再描画
	Invalidate();
}

// グレースケールボタンクリック
void CMFCOpenCV2Dlg::OnClickedBtnGray()
{
	// グレースケール画像
	Mat matGray;

	// グレースケール
	cvtColor(m_matImg, matGray, COLOR_BGR2GRAY);
	cvtColor(matGray, matGray, COLOR_GRAY2BGR);
	matGray.copyTo(m_matImg);
	//imshow("test", m_matImg);

	// 再描画
	Invalidate();
}

// 二値化ボタンクリック
void CMFCOpenCV2Dlg::OnClickedBtnThreshold()
{
	// 2値化画像
	Mat matThresholdLower;
	Mat matThresholdUpper;

	// 2値化
	threshold(m_matImg, matThresholdLower, 20, 255, THRESH_BINARY_INV);
	threshold(m_matImg, matThresholdUpper, 0, 255, THRESH_BINARY);
	bitwise_and(matThresholdLower, matThresholdUpper, m_matImg);

	// 再描画
	Invalidate();
}

// コーナー検出ボタンクリック
void CMFCOpenCV2Dlg::OnClickedBtnCorners()
{
	// コーナー検出画像
	Mat matGray;
	Mat matCorners = m_matImg.clone();
	vector<Point2f> vecptCorners;

	// グレースケール変換
	cvtColor(m_matImg, matGray, COLOR_BGR2GRAY);

	// コーナー検出
	goodFeaturesToTrack(matGray, vecptCorners, 60, 0.09, 9);
	vector<Point2f>::iterator itrCorners = vecptCorners.begin();
	for (; itrCorners != vecptCorners.end(); ++itrCorners) {
		circle(matCorners, Point(itrCorners->x, itrCorners->y), 1, Scalar(0, 0, 255), -1);
		circle(matCorners, Point(itrCorners->x, itrCorners->y), 8, Scalar(0, 0, 255));
	}
	
	matCorners.copyTo(m_matImg);

	// 再描画
	Invalidate();
}

// 輪郭抽出ボタンクリック
void CMFCOpenCV2Dlg::OnClickedBtnContours()
{
	// 輪郭抽出領域
	Mat matGray;
	Mat matBlur;
	Mat matCanny;
	vector<vector<Point>> vvpoContours;
	vector<Vec4i> v4iHierarcy;
	Mat matDrawing = Mat::zeros(m_matImg.size(), CV_8UC3);

	// グレースケール変換
	cvtColor(m_matImg, matGray, COLOR_BGR2GRAY);

	// 平滑化
	blur(matGray, matBlur, Size(3, 3));

	// アルゴリズム設定
	Canny(matBlur, matCanny, 100, 100 * 2);

	// 輪郭抽出
	findContours(matCanny, vvpoContours, v4iHierarcy, RETR_TREE, CHAIN_APPROX_NONE);
	drawContours(matCanny, vvpoContours, -1, (Scalar)(0, 0, 0), CV_FILLED, 8, v4iHierarcy);

	for (size_t i = 0; i < vvpoContours.size(); i++) {
		drawContours(matDrawing, vvpoContours, (int)i, Scalar(0, 0, 255));
	}

	matDrawing.copyTo(m_matImg);

	// 再描画
	Invalidate();
}


void thinningIte(Mat& img, int pattern) {

	Mat del_marker = Mat::ones(img.size(), CV_8UC1);
	int x, y;

	for (y = 1; y < img.rows - 1; ++y) {

		for (x = 1; x < img.cols - 1; ++x) {

			int v9, v2, v3;
			int v8, v1, v4;
			int v7, v6, v5;

			v1 = img.data[y   * img.step + x * img.elemSize()];
			v2 = img.data[(y - 1) * img.step + x * img.elemSize()];
			v3 = img.data[(y - 1) * img.step + (x + 1) * img.elemSize()];
			v4 = img.data[y   * img.step + (x + 1) * img.elemSize()];
			v5 = img.data[(y + 1) * img.step + (x + 1) * img.elemSize()];
			v6 = img.data[(y + 1) * img.step + x * img.elemSize()];
			v7 = img.data[(y + 1) * img.step + (x - 1) * img.elemSize()];
			v8 = img.data[y   * img.step + (x - 1) * img.elemSize()];
			v9 = img.data[(y - 1) * img.step + (x - 1) * img.elemSize()];

			int S = (v2 == 0 && v3 == 1) + (v3 == 0 && v4 == 1) +
				(v4 == 0 && v5 == 1) + (v5 == 0 && v6 == 1) +
				(v6 == 0 && v7 == 1) + (v7 == 0 && v8 == 1) +
				(v8 == 0 && v9 == 1) + (v9 == 0 && v2 == 1);

			int N = v2 + v3 + v4 + v5 + v6 + v7 + v8 + v9;

			int m1 = 0, m2 = 0;

			if (pattern == 0) m1 = (v2 * v4 * v6);
			if (pattern == 1) m1 = (v2 * v4 * v8);

			if (pattern == 0) m2 = (v4 * v6 * v8);
			if (pattern == 1) m2 = (v2 * v6 * v8);

			if (S == 1 && (N >= 2 && N <= 6) && m1 == 0 && m2 == 0)
				del_marker.data[y * del_marker.step + x * del_marker.elemSize()] = 0;
		}
	}

	img &= del_marker;
}

void thinning(const Mat& src, Mat& dst) {
	dst = src.clone();
	dst /= 255;         // 0は0 , 1以上は1に変換される

	Mat prev = Mat::zeros(dst.size(), CV_8UC1);
	Mat diff;

	do {
		thinningIte(dst, 0);
		thinningIte(dst, 1);
		absdiff(dst, prev, diff);
		dst.copyTo(prev);
	} while (countNonZero(diff) > 0);

	dst *= 255;
}

// 細分化
void CMFCOpenCV2Dlg::OnClickedBtnThinning()
{
	// グレースケール変換
	Mat matGray;
	cvtColor(m_matImg, matGray, COLOR_BGR2GRAY);

	// 2値化
	Mat matThresholdUpper;
	threshold(matGray, matThresholdUpper, 10, 255, THRESH_BINARY);

	// 細分化
	//	thinning(matThresholdUpper, m_matImg);

	// 再描画
	Invalidate();
}


// 図形ボタンクリック
void CMFCOpenCV2Dlg::OnClickedBtnShape()
{
	/*
	Mat matShape = Mat::zeros(m_matImg.size(), CV_16U);
	Mat matThresh;
	Mat matMask = matShape.clone();

	// 矩形
	rectangle(matShape, Point(100, 100), Point(109, 109), (2000 - 10), -1, CV_AA);
	// 二値化
	threshold(matShape, matThresh, 1900, 255, THRESH_BINARY);
	matThresh.convertTo(matThresh, CV_8U);

	vector<vector<Point>> vvpoContours;
	vector<Vec4i> v4iHierarcy;
	//輪郭抽出
	findContours(matThresh, vvpoContours, v4iHierarcy, RETR_TREE, CHAIN_APPROX_NONE);
	fillConvexPoly(matMask, vvpoContours[0], UINT16_MAX);
	matShape = 2000 - matShape;
	bitwise_and(matShape, matMask, matShape);

	double dSum = sum(matShape)[0];
	CString sTest;
	sTest.Format(_T("合計 : %lf\n"), dSum);
	m_sStcInfo = sTest;

	matShape.convertTo(matShape, CV_8U);
	cvtColor(matShape, matShape, CV_GRAY2BGR);
	matShape.copyTo(m_matImg);
	*/
	Mat mtRRct = Mat::zeros(m_matImg.size(), CV_16U);
	Mat mtRRctTest = Mat::zeros(m_matImg.size(), CV_16U);
	RotatedRect rorcRect = RotatedRect(Point2f(200, 200), Size2f(100 - 1, 50 - 1), 30);	// Sizeは始点を含まないため両側に-1が必要。
	Point2f pofRect[4];
	rorcRect.points(pofRect);
	vector<Point> vpoRect(4);
	for (int i = 0; i < 4; i++) {
		vpoRect[i].x = floor(pofRect[i].x);
		vpoRect[i].y = floor(pofRect[i].y);
	}
	fillConvexPoly(mtRRctTest, vpoRect, Scalar(10000));
	double dSumTest = sum(mtRRctTest)[0];
	
	RotatedRect rorcArea = minAreaRect(vpoRect);
	Point2f pofArea[4];
	rorcArea.points(pofArea);
	Point poArea[4];
	for (int i = 0; i < 4; i++) poArea[i] = pofArea[i];

	fillConvexPoly(mtRRct, poArea, 4, Scalar(10000));

	cout << mtRRct << endl;

	double dSum = sum(mtRRct)[0];
	CString sInfo;
	sInfo.Format(_T("X : %f\nY : %f\n合計 : %lf, %lf\n"), rorcArea.size.width + 1, rorcArea.size.height + 1, dSumTest, dSum);
	m_sStcInfo = sInfo;

	// 変換
	mtRRct.convertTo(mtRRct, CV_8U);
	cvtColor(mtRRct, mtRRct, CV_GRAY2BGR);
	mtRRct.copyTo(m_matImg);

	// 再描画
	UpdateData(FALSE);
	Invalidate();
}