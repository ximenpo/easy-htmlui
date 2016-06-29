#pragma once

#include "atlwin.h"
#include "easy-htmlui.h"

class WebExternalObject;

class MainDialog :
	public CAxDialogImpl<MainDialog, CAxWindow>,
	public IDispEventImpl<IDC_WEB,MainDialog>
{
public:
	MainDialog(void);
	~MainDialog(void);

public:
	enum	{IDD	= IDD_MAIN};

	bool	PreProcessKeyboardMessage(MSG* msg);

private:
	CAxWindow		m_ctrlWeb;
	IWebBrowser2*	m_pWeb;
	
	WebExternalObject*	m_pExternalObject;

	HICON			m_hIcon;

private:
	typedef	MainDialog								thisClass;
	typedef	CAxDialogImpl<MainDialog, CAxWindow>	superClass;

private:
	void			do_CloseWindow();

public:
	BEGIN_SINK_MAP(MainDialog)
	END_SINK_MAP()

private:
	BEGIN_MSG_MAP(MainDialog)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};

