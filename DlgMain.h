#pragma once

#include "atlwin.h"
#include "easy-htmlui.h"

class MainDialog :
	public CAxDialogImpl<MainDialog, CAxWindow>,
	public IDispEventImpl<IDC_WEB,MainDialog>
{
public:
	MainDialog(void);
	~MainDialog(void);

public:
	enum	{IDD	= IDD_MAIN};

private:
	CAxWindow		m_ctrlWeb;
	IWebBrowser2*	m_pWeb;
	
private:
	typedef	MainDialog								thisClass;
	typedef	CAxDialogImpl<MainDialog, CAxWindow>	superClass;

	void			do_CloseWindow();

public:
	BEGIN_SINK_MAP(MainDialog)
		SINK_ENTRY(IDC_WEB, 264, WindowSetLeftWeb)
		SINK_ENTRY(IDC_WEB, 265, WindowSetTopWeb)
		SINK_ENTRY(IDC_WEB, 266, WindowSetWidthWeb)
		SINK_ENTRY(IDC_WEB, 267, WindowSetHeightWeb)
		SINK_ENTRY(IDC_WEB, 262, WindowSetResizableWeb)
	END_SINK_MAP()
	void __stdcall WindowSetLeftWeb(long Left);
	void __stdcall WindowSetTopWeb(long Top);
	void __stdcall WindowSetWidthWeb(long Width);
	void __stdcall WindowSetHeightWeb(long Height);
	void __stdcall WindowSetResizableWeb(BOOL Resizable);

private:
	BEGIN_MSG_MAP(MainDialog)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
	END_MSG_MAP()
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};

