#include <afxwin.h>
#include <afxcmn.h>
#include <afxext.h>
#include <afxdialogex.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <string.h>
#include "resource.h"


class CMyDialog : public CDialog
{
public:
	CMyDialog(CWnd* pParent = NULL);  
	enum { IDD = IDD_DIALOG1 };
	CEdit m_E[20];
	int E[20];
	CPoint *pt;
	bool LogInd[10];
	int cnt;
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    
	virtual void OnGI();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};

CMyDialog dialog;

class CMyFrameWnd:public CFrameWnd
{
	public :
		CMyFrameWnd();
		CMenu PopupMenu;
		int m_PointX;
		int m_PointY;
	protected :
		CStatusBar m_wndStatusBar;
		afx_msg int OnCreate(LPCREATESTRUCT IpCreateStruct);
		afx_msg void OnClose();
		afx_msg void OnAbout();
		afx_msg void OnBack();
		afx_msg void OnExit();
		afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnPaint();
		afx_msg void OnMouseMove(UINT nFlags, CPoint point);
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
		DECLARE_MESSAGE_MAP();
};

CMyFrameWnd *pFrame=NULL;

class PropDialog : public CDialog
{
public:
	PropDialog(CWnd* pParent = NULL);  
		enum { IDD = IDD_DIALOG2 };
	CEdit m_P[2];
	CPoint currprop;
	int propindex;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()
};

PropDialog prop;

BOOL CMyDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	for (int i=0; i<20; i++)
	{
		m_E[i].SetWindowText("0");
		E[i]=0;
	}
	return TRUE;
}

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_E[0]);
	DDX_Control(pDX, IDC_EDIT2, m_E[1]);
	DDX_Control(pDX, IDC_EDIT3, m_E[2]);
	DDX_Control(pDX, IDC_EDIT4, m_E[3]);
	DDX_Control(pDX, IDC_EDIT5, m_E[4]);
	DDX_Control(pDX, IDC_EDIT6, m_E[5]);
	DDX_Control(pDX, IDC_EDIT7, m_E[6]);
	DDX_Control(pDX, IDC_EDIT8, m_E[7]);
	DDX_Control(pDX, IDC_EDIT9, m_E[8]);
	DDX_Control(pDX, IDC_EDIT10, m_E[9]);
	DDX_Control(pDX, IDC_EDIT11, m_E[10]);
	DDX_Control(pDX, IDC_EDIT12, m_E[11]);
	DDX_Control(pDX, IDC_EDIT13, m_E[12]);
	DDX_Control(pDX, IDC_EDIT14, m_E[13]);
	DDX_Control(pDX, IDC_EDIT15, m_E[14]);
	DDX_Control(pDX, IDC_EDIT16, m_E[15]);
	DDX_Control(pDX, IDC_EDIT17, m_E[16]);
	DDX_Control(pDX, IDC_EDIT18, m_E[17]);
	DDX_Control(pDX, IDC_EDIT19, m_E[18]);
	DDX_Control(pDX, IDC_EDIT20, m_E[19]);
}

BEGIN_MESSAGE_MAP(CMyDialog,CDialog)
ON_COMMAND(IDC_BUTTON1,OnGI)
END_MESSAGE_MAP()

CMyDialog::CMyDialog(CWnd *pParent)
:CDialog(CMyDialog::IDD,pParent)
{

}

BOOL PropDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString buff_X;
	CString buff_Y;
	buff_X.Format("%d",currprop.x);
	buff_Y.Format("%d",currprop.y);
	m_P[0].SetWindowText(buff_X);
	m_P[1].SetWindowText(buff_Y);
	return TRUE;
}

void PropDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_P[0]);
	DDX_Control(pDX, IDC_EDIT2, m_P[1]);
}

BEGIN_MESSAGE_MAP(PropDialog,CDialog)
ON_BN_CLICKED(IDOK, &PropDialog::OnBnClickedOk)
END_MESSAGE_MAP()

PropDialog::PropDialog(CWnd *pParent)
:CDialog(PropDialog::IDD,pParent)
{

}

void PropDialog::OnBnClickedOk()
{
	char str[10];
	m_P[0].GetWindowText(str,10);
	dialog.pt[propindex].x=atoi(str);
	m_P[1].GetWindowText(str,10);
	dialog.pt[propindex].y=atoi(str);
	pFrame->RedrawWindow();
	CDialog::OnOK();
}


BEGIN_MESSAGE_MAP(CMyFrameWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_ABOUT,OnAbout)
	ON_COMMAND(ID_Back,OnBack)
	ON_COMMAND(ID_EXIT,OnExit)
	ON_WM_RBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP();

static UINT indicators[] =
{	
	IDS_STRING1,
	IDS_STRING2
};

CMyFrameWnd::CMyFrameWnd()
{
	m_PointX=0;
	m_PointY=0;
	Create(NULL,"Graphical Input", 
	WS_OVERLAPPEDWINDOW,rectDefault,NULL,MAKEINTRESOURCE(IDR_MENU1));
	PopupMenu.LoadMenu(IDR_MENU2); 
};

void CMyFrameWnd::OnClose() 
{ 
	dialog.SendMessage(WM_CLOSE);
    CWnd::OnClose();
}

int CMyFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(CFrameWnd::OnCreate(lpCreateStruct)==-1) return -1; 
	else {
		m_wndStatusBar.Create(this);
		m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
		m_wndStatusBar.SetPaneInfo(0,IDS_STRING1,SBPS_POPOUT,30);
		m_wndStatusBar.SetPaneInfo(1,IDS_STRING2,SBPS_POPOUT,30);
		return 0;
	}
}

void CMyFrameWnd::OnAbout()
{
	MessageBox("Copyright © 2014 Zalizetskiy.","About",MB_OK|MB_ICONINFORMATION);
}

void CMyFrameWnd::OnBack()
{
	this->ShowWindow(SW_HIDE);
	dialog.ShowWindow(SW_SHOWNORMAL);
	
	CString buff_X;
	CString buff_Y;
	int ind1=0, ind2=0;
	for (int i=0; i<10; i++)
	{
		if (dialog.LogInd[i])
		{
			buff_X.Format("%d",dialog.pt[ind1].x);
			buff_Y.Format("%d",dialog.pt[ind1].y);
			dialog.m_E[ind2].SetWindowText(buff_X);
			dialog.m_E[ind2+1].SetWindowText(buff_Y);
			ind1++;
		}
		ind2+=2;
	}
}

void CMyFrameWnd::OnExit()
{
	dialog.SendMessage(WM_CLOSE);
	SendMessage(WM_CLOSE);
}

void CMyFrameWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	CPoint t;
    GetCursorPos(&t);
	PopupMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,t.x, t.y, this);
}

void CMyFrameWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if((nFlags & MK_LBUTTON)==MK_LBUTTON)
	{
		for (int i=0; i<dialog.cnt; i++){
			if (point.x<dialog.pt[i].x+10 && point.x>dialog.pt[i].x-5)
				if (point.y<dialog.pt[i].y+10 && point.y>dialog.pt[i].y-5)
				{
					m_PointX=point.x-dialog.pt[i].x;
					m_PointY=point.y-dialog.pt[i].y;
					dialog.pt[i].x+=m_PointX;
					dialog.pt[i].y+=m_PointY;
					this->RedrawWindow();
				}
		}
	}
	CString buff_X;
	CString buff_Y;
	buff_X.Format("%d",point.x);
	buff_Y.Format("%d",point.y);
	m_wndStatusBar.SetPaneText(0,buff_X);
	m_wndStatusBar.SetPaneText(1,buff_Y);

	CFrameWnd::OnMouseMove(nFlags, point);
}

void CMyFrameWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	CFrameWnd::OnLButtonDown(nFlags, point);
}

void CMyFrameWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
		for (int i=0; i<dialog.cnt; i++){
			if (point.x<dialog.pt[i].x+10 && point.x>dialog.pt[i].x-5)
				if (point.y<dialog.pt[i].y+10 && point.y>dialog.pt[i].y-5)
				{
					prop.currprop.x=dialog.pt[i].x;
					prop.currprop.y=dialog.pt[i].y;
					prop.propindex=i;
					prop.DoModal();
				}
		}
	CFrameWnd::OnLButtonDblClk(nFlags, point);
}


void CMyDialog::OnGI() 
{	
	char str[10];
	bool nodigit,negative;
	for (int i=0; i<20; i++)
	{
		cnt=0;
		m_E[i].GetWindowText(str,10);
		
		if (!isdigit(str[0]) && !isdigit(str[1])) 
		{
			nodigit=true;
		}
		else if (atoi(str)<0)
		{
			negative=true;
		}
		else
		{
			E[i]=atoi(str);	
		}
	}

	for (int i=0; i<20; i++)
	{
		if (E[i]>0 && E[i+1]>0) {
			cnt++;
			LogInd[i/2]=true;
		}
		i++;
	}
	
	pt=new CPoint[cnt];
	int ind1=0;
	int ind2=0;
	for (int i=0; i<10; i++)
	{
		if (LogInd[i]) {
			pt[ind1]= CPoint(E[ind2],E[ind2+1]); ind1++; 
		}
		ind2+=2;
	}

	try
	{
		if (nodigit==true) throw "no digit!!!";
		else if (negative==true) throw "negative!!!";
		else
		{
			CString sMessage;
			sMessage.Format("%d",cnt);
			MessageBox("Вірних координат: "+sMessage+" з 10.","Info...",MB_OK|MB_ICONINFORMATION);

			this->ShowWindow(SW_HIDE);
			CMyFrameWnd *pMainWnd=new CMyFrameWnd;
			pMainWnd->ShowWindow(SW_SHOWNORMAL);
			pMainWnd->UpdateWindow();
			pFrame=pMainWnd;
		}
	}
	catch(char*s)
	{
		MessageBox(s,"Обробка...",MB_OK|MB_ICONWARNING);
	}
}

void CMyFrameWnd::OnPaint() 
{
	CPaintDC dc(this);
	CPen aPen;
	aPen.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	dc.SelectObject(&aPen);

	dc.Polygon(dialog.pt,dialog.cnt);

	for (int i=0; i<dialog.cnt; i++)
	{
		dc.Rectangle(dialog.pt[i].x-3,dialog.pt[i].y-3,dialog.pt[i].x+6,dialog.pt[i].y+6);
	}
}

class CMyApp:public CWinApp
{
	public:
		virtual BOOL InitInstance();
};

BOOL CMyApp ::InitInstance()
{	
	dialog.DoModal();
	return TRUE;
};

CMyApp app;
