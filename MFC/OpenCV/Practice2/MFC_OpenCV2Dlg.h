
// MFC_OpenCV2Dlg.h : ヘッダー ファイル
//

#pragma once

#include "opencv2/opencv.hpp"

using namespace cv;

// CMFCOpenCV2Dlg ダイアログ
class CMFCOpenCV2Dlg : public CDialogEx
{
// コンストラクション
public:
	CMFCOpenCV2Dlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_OPENCV2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedBtnReadImg();
	afx_msg void OnClickedBtnGray();
	afx_msg void OnClickedBtnThreshold();
	afx_msg void OnClickedBtnCorners();
	afx_msg void OnClickedBtnContours();
	afx_msg void OnClickedBtnThinning();
	afx_msg void OnClickedBtnShape();
	CStatic m_cPicImg;
	Mat m_matImg;
	CString m_sStcInfo;
};
