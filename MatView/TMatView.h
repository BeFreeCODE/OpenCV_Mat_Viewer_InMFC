#pragma once
#include "opencv2\opencv.hpp"

using namespace cv;
using namespace std;

#define T_CHECK_FOCUS	    3009
#define COLOR_MENU          RGB(45, 45, 48)
#define COLOR_BACKGROUND    RGB(10, 10, 18)
#define MAX_ZOOM            10.0
#define MIN_ZOOM            0.8


class CTMatView : public CWnd {
    DECLARE_DYNAMIC(CTMatView)

    enum eBTN_ID {
        eBTN_SAVE = 4009,
        eBTN_LOAD       ,
    };

    enum eRECT {
        eRECT_WND = 0   ,
        eRECT_PICTURE   ,
        eRECT_MENU      ,
        eRECT_ZOOM      ,
        eRECT_COORD     ,
        eRECT_PALETTE   ,
        eRECT_NUM       ,
    };

public:
    CTMatView();
    CTMatView(cv::Mat image);
    CTMatView(cv::Mat image, CRect rect);
    virtual ~CTMatView();

public:
    void            InitMatView();
    void            DisplayImage(HDC& hdc, cv::Mat& image);
    void            MoveWindow(CRect rect);

    cv::Mat         GetImage() { return m_orgImage; }
    cv::Point2d     ClientToImage(CPoint clientPt, CRect clientRect, cv::Mat image);


private:
    void            SetImage(cv::Mat image);
    void            SetRectArea(CRect rect);
    void            SetParentWnd();
    void            SetZoomRect(double dZoom, bool bZoomin = true);
    void            DisplayNavImage(HDC& hdc, BITMAPINFO& bitmapInfo);

    BOOL            LoadImageFile();
    BOOL            SaveImageFile();

    // Menu
    void            CreateMenu();
    void            CreateButton(CMFCButton& button, CRect rect, eBTN_ID btnID, LPCTSTR str = _T(""));


private:
    CWnd*           m_pwndParent = nullptr;

    cv::Mat		    m_orgImage;				// 현제 가지고 있는 이미지.
    cv::Mat         m_showImage;            // 실제 보여지는 이미지.
    cv::Mat         m_navImage;             // navigation 이미지.
    
    CRect           m_rect[eRECT_NUM];
    CRect           m_rectImage;            // 실제 출력된 Image 영역.
    CRect           m_rectZoom;             // zoom area
    
    cv::Point2d     m_ptImage;              // Image Mouse 좌표
    CPoint          m_ptView;

    double          m_dZoom = 1.0;
    
    bool		    m_bFocus;				// MatView선택

    // Menu
    CMFCButton	    m_btnLoad;
    CMFCButton	    m_btnSave;





public:
    DECLARE_MESSAGE_MAP()
    afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void	OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void	OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void	OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void	OnPaint();
    afx_msg void	OnTimer(UINT_PTR nIDEvent);
    virtual BOOL	OnCommand(WPARAM wParam, LPARAM lParam);
    afx_msg BOOL    OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    afx_msg void    OnMouseMove(UINT nFlags, CPoint point);
};