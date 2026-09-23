# MFC OpenCV program

## 概要

OpenCVでの図形描画。

<br>

## ソースコード説明

~~~
CRect rc;
GetDlgItem(IDC_PIC_IMG)->GetClientRect(&rc);
cv::Size size(rc.Width() & ~0x03, rc.Height() & ~0x03)
~~~
ピクチャボックス（ID:IDC_PIC_IMG）へ描画するためにサイズを取得。

<br>

~~~
cv::Mat img(size.width, size.height, CV_8UC3);
~~~
空のMAT（8Bit×3色）を作成。

<br>

~~~
cv::line(img, cv::Point(0, 0), cv::Point(100, 100), cv::Scalar(255, 0, 0), 1, cv::LINE_8);
~~~
座標（X:0, Y:0）から座標（X:100, Y:100）まで青（B:255, G:0, R:0）の太さ1、８連結の線を描画。

<br>

~~~
cv::rectangle(img, cv::Point(0, 110), cv::Point(100, 210), cv::Scalar(0, 0, 255), 1, cv::LINE_4);
cv::rectangle(img, cv::Point(110, 110), cv::Point(210, 210), cv::Scalar(0, 255, 0), -1, cv::LINE_AA);
~~~

- 左上座標（X:0, Y:110）、右下座標（X:100, Y:210）で赤（B:0, G:0, R:255）の枠線の太さ１、4連結の四角形を描画。
- 左上座標（X:110, Y:110）、右下座標（X:210, Y:210）で緑（B:0, G:255, R:0）の塗りつぶし（-1）、<br>
アンチエイリアス（LINE_AA）の四角形を描画。

<br>

~~~
cv::circle(img, cv::Point(50, 270), 50, cv::Scalar(255, 255, 0), 1, cv::LINE_AA);
cv::circle(img, cv::Point(160, 270), 50, cv::Scalar(0, 255, 255), -1, cv::LINE_AA);
~~~
- 中心点座標（X:50, Y:270）、半径50でシアン（B:255, G:255, R:0）の枠線の太さ1、<br>
アンチエイリアス（LINE_AA）の円を描画。
- 中心点座標（X:160, Y:270）、半径50で黄（B:0, G:255, R:255）の塗りつぶし（-1）、<br>
アンチエイリアス（LINE_AA）の円を描画。

<br>

~~~
cv::ellipse(img, cv::Point(50, 380), cv::Size(50, 30), 0, 0, 0 + 360, cv::Scalar(128, 0, 0), 1, cv::LINE_AA);
cv::ellipse(img, cv::Point(160, 380), cv::Size(20, 50), 30, 0 - 200, 0 + 100, cv::Scalar(0, 128, 0), -1, cv::LINE_AA);
~~~
- 中心点座標（X:50, Y:380）、長径50短径30、回転角度0°、開始角度0°、終了角度360°で<br>
紺色（B:128, G:0, R:0）の太さ1、アンチエイリアス（LINE_AA）の楕円を描画。
- 中心点座標（X:160, Y:380）、長径20短径50、回転角度30°、開始角度-200°、終了角度100°で<br>
ダークグリーン（B:0, G:128, R:0）の塗りつぶし、アンチエイリアス（LINE_AA）の楕円を描画。

<br>

~~~
cv::Point ptPoly[][2] =
{
	{ cv::Point(210, 0), cv::Point(210, 100)},
	{ cv::Point(210, 100), cv::Point(310, 50)},
	{ cv::Point(210, 100), cv::Point(310, 150)},
};
const cv::Point *pptPoly[] = { ptPoly[0], ptPoly[1], ptPoly[2], ptPoly[3] };
int iNppt[] = { 2, 2, 2 };
cv::polylines(img, pptPoly, iNppt, _countof(iNppt), false, cv::Scalar(10, 200, 200), 3, cv::LINE_8);
~~~
折れ線座標配列（pptPoly）、各折れ線の頂点数配列（iNppt）、3本の折れ線（iNpptの要素数）で、<br>
黄土色（G:10, B:200, R:200）、太さ３、8連結の折れ線を描画。

<br>

~~~
cv::Point ptPoly2[][3] = 
{
	{ cv::Point(210, 200), cv::Point(210, 300), cv::Point(260, 260)},
	{ cv::Point(210, 300), cv::Point(310, 250), cv::Point(310, 300)},
	{ cv::Point(210, 300), cv::Point(310, 350), cv::Point(310, 330)}
};
const cv::Point *pptPoly2[] = { ptPoly2[0], ptPoly2[1], ptPoly2[2], ptPoly2[3] };
int iNppt2[] = { 3, 3, 3};
cv::fillPoly(img, pptPoly2, iNppt2, _countof(iNppt2), cv::Scalar(200, 200, 10), cv::LINE_AA);
~~~
ポリゴン配列（pptPoly2）、各ポリゴンの頂点数配列（iNppt2）、輪郭数（iNppt2の要素数）で、<br>
ターコイズブルー（G:10, B:200, R:200）、エイリアス（LINE_AA）のポリゴンを描画。

<br>

~~~
cv::flip(img, img, 0);
~~~ 
MATをX軸回りで反転（0）。<br>
※ピクチャボックスに描画するビットマップ設定（BITMAPINFO）のbiHeightに正値を指定するため<br>
画像を上下反転（biHeightはもともと負）。

<br>

~~~
BITMAPINFO info = {};
info.bmiHeader.biBitCount = 24;						// ピクセルあたりのビット数（RGB各8bit)
info.bmiHeader.biWidth = size.width;				// ビットマップ幅（ピクセル）
info.bmiHeader.biHeight = size.height;				// ビットマップ高さ（ピクセル）
info.bmiHeader.biPlanes = 1;						// プレーン数（基本1）
info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);	// 構造体必要バイト数
info.bmiHeader.biCompression = BI_RGB;				// 圧縮の種類（圧縮無し指定）
~~~
ピクチャボックスに描画するビットマップ設定。

<br>

~~~
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
~~~
DIB（Bitmap）、JPG、PNGイメージ内のピクセル色データをピクチャボックスへコピー。
