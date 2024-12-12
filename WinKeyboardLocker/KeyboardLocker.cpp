#include <windows.h>
#include <string.h>
#include <strsafe.h>
#include <tchar.h>
#include "Resource.h"
#include "Name.h"
#include"wintoastlib.h"
//Zur Vereinheitlichung des Rufnamens ist das Präfix WKBDL_

//Definiere WinProc Die verarbeiteten Informationen, die nach dem Vorgang an das Tray-Icon gesendet werden WM_TRAYICON benachrichtugung
#define WM_TRAYICON WM_USER+1

enum
{
	MENU_ACTION_LOCK,
	MENU_ACTION_UNLOCK,
	MENU_ACTION_EXIT
};

//Globale Handles verwenden
HINSTANCE hInst;
HHOOK KBHook;//Hook-Handle

//Mit Hilfe der globalen Variablen isLocked um den aktuellen Sperrstatus des Tastenfeldes zu ermitteln
bool isLocked = false;
//Stellen Sie fest, ob das aktuelle Betriebssystem Folgendes unterstützt Toast
bool SystemIsCopatiple = false;

//Trayicon
NOTIFYICONDATA TrayIcon = {};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK KbdHkProc(int, WPARAM, LPARAM);

void CreatTrayMenu(HWND);//Menü anzeigen
void KeyboardLocker();//Kernprogramm, das auf Hookhandle zum Sperren/Entsperren der Tastatur wirkt
void ShowMessage_Lock();
void ShowMessage_Unlock();

void APP_EXIT(HWND);//Opt-out-Verfahren
void APP_ERROR(int);

using namespace WinToastLib;

//Dies ist der Punkt, an dem die Verwirklichung des Toast zur Manipulation von Kontrollkästchen
class WinToastHandler : public IWinToastHandler {
public:
	void toastActivated() const {
		//click toast
	}

	void toastActivated(int actionIndex) const {
		//click button
		//Um zu verhindern, dass die Tastatur gesperrt wird, wenn der Benutzer auf „Entsperren“ klickt, während die Tastatur entsperrt ist, muss es möglich sein, den Zustand „Gesperrt“ zu erreichen.
		isLocked = true;
		KeyboardLocker();
	}

	void toastDismissed(WinToastDismissalReason state) const {
		//switch state
	}

	void toastFailed() const {
		//error
	}
};

WinToastTemplate InitializeWinToastTemlate();
WinToastTemplate Toast32;


int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	//windows Standardeinstellungen für Fenster
	WNDCLASS wcex;
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WKBL_APP_NAME;

	if (!RegisterClass(&wcex))
	{
		APP_ERROR(3);
	}

	hInst = hInstance;

	//Erstellen eines unsichtbaren Fensters
	HWND hwnd = CreateWindow(WKBL_APP_NAME, WKBL_APP_TITLE, WS_OVERLAPPEDWINDOW, 0, 0, 0, 0, 0, 0, hInstance, NULL);
	if (!hwnd)
	{
		APP_ERROR(2);
	}

	//Tablett-Symbole definieren
	TrayIcon.cbSize = sizeof(NOTIFYICONDATA);
	TrayIcon.hWnd = hwnd;
	TrayIcon.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_KEYBOARDLOCKER));
	TrayIcon.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_INFO;
	TrayIcon.uCallbackMessage = WM_TRAYICON;
	StringCchCopy(TrayIcon.szTip, ARRAYSIZE(TrayIcon.szTip), WKBL_TRAYICON_HOVER);
	StringCchCopy(TrayIcon.szInfoTitle, ARRAYSIZE(TrayIcon.szInfoTitle), WKBL_APP_TITLE);
	StringCchCopy(TrayIcon.szInfo, ARRAYSIZE(TrayIcon.szInfo), WKBL_NOTIFY_START);
	Shell_NotifyIcon(NIM_ADD, &TrayIcon);

	//Initialisierungs Toast
	if (WinToast::isCompatible())
	{
		SystemIsCopatiple = true;
		WinToast::instance()->setAppName(WKBL_APP_NAME);
		WinToast::instance()->setAppUserModelId(WKBL_APP_TITLE);
		WinToast::instance()->initialize();
		Toast32 = InitializeWinToastTemlate();
	}


	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		if (HIWORD(wParam) == 0)
		{
			if (LOWORD(wParam) == MENU_ACTION_LOCK)
			{
				KeyboardLocker();
			}
			if (LOWORD(wParam) == MENU_ACTION_EXIT)
			{
				APP_EXIT(hwnd);
			}
		}
		break;

	case WM_TRAYICON:
		if (lParam == WM_RBUTTONUP)
		{
			SetForegroundWindow(hwnd);//Nachdem Sie das Menü eingeblendet haben, klicken Sie außerhalb des Menüs, damit das Kontrollkästchen verschwindet.
			CreatTrayMenu(hwnd);
		}
		//Sperren/Entsperren der Tastatur bei Doppelklick auf das Symbol
		else if (lParam == WM_LBUTTONDBLCLK)
		{
			KeyboardLocker();
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
		break;
	}
	return 0;
}

LRESULT CALLBACK KbdHkProc(int code, WPARAM wParam, LPARAM lParam)
{
	//Ignorieren Sie Tastaturaktionen und erweitern Sie vielleicht in Zukunft die Arten von Eingaben, die hier ignoriert werden.
	if (code == HC_ACTION)
	{
		return 1;
	}
	return CallNextHookEx(NULL, code, wParam, lParam);
}

//Menüs erstellen
void CreatTrayMenu(HWND hwnd)
{
	HMENU hMenu = CreatePopupMenu();

	//Menüoptionen definieren
	if (isLocked)
	{
		AppendMenu(hMenu, MF_STRING, MENU_ACTION_LOCK, WKBL_MENU_UNLOCK);//Da die Tastatur gesperrt ist, sollte dort „entsperrt“ stehen.
	}
	else
	{
		AppendMenu(hMenu, MF_STRING, MENU_ACTION_LOCK, WKBL_MENU_LOCK);
	}
	AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(hMenu, MF_STRING, MENU_ACTION_EXIT, WKBL_MENU_EXIT);

	//Mausklick auf das Menü, um eine Nachricht zu senden
	POINT pt;
	GetCursorPos(&pt);
	TrackPopupMenu(hMenu, TPM_RIGHTALIGN, pt.x, pt.y, 0, hwnd, NULL);
}

//Opt-out-Verfahren
void APP_EXIT(HWND hwnd)
{
	Shell_NotifyIcon(NIM_DELETE, &TrayIcon);
	::DestroyWindow(hwnd);
}

void APP_ERROR(int ErrorNumber)
{
	MessageBox(NULL, WKBL_APP_ERROR, WKBL_APP_TITLE, NULL);
	exit(ErrorNumber);
}

WinToastTemplate InitializeWinToastTemlate()
{
	WinToastTemplate temp(WinToastTemplate::Text03);
	temp.setFirstLine(WKBL_APP_TITLE);
	temp.setSecondLine(WKBL_NOTIFY_LOCK);
	temp.setAttributionText(WKBL_NOTIFY_LOCK2);
	temp.addAction(WKBL_MENU_UNLOCK);
	temp.setDuration(WinToastTemplate::Duration::Short);
	return temp;
}

//显示消息
void ShowMessage_Unlock()
{
	StringCchCopy(TrayIcon.szInfo, ARRAYSIZE(TrayIcon.szInfo), WKBL_NOTIFY_UNLOCK);
	Shell_NotifyIcon(NIM_MODIFY, &TrayIcon);
}
void ShowMessage_Lock()
{
	StringCchCopy(TrayIcon.szInfo, ARRAYSIZE(TrayIcon.szInfo), WKBL_NOTIFY_LOCK);
	Shell_NotifyIcon(NIM_MODIFY, &TrayIcon);
}

//核心程序，控制解锁与否
void KeyboardLocker()
{
	if (isLocked)
	{
		UnhookWindowsHookEx(KBHook);//解锁
		ShowMessage_Unlock();
		isLocked = false;
	}
	else
	{
		KBHook = SetWindowsHookEx(13, (HOOKPROC)KbdHkProc, (HINSTANCE)GetModuleHandle(NULL), 0);//锁定键盘
		if (SystemIsCopatiple)
		{
			WinToast::instance()->showToast(Toast32, new WinToastHandler());
		}
		else
		{
			ShowMessage_Lock();
		}
		isLocked = true;
	}
}
