#include <windows.h>
#include <stdio.h>
#include <atlimage.h>
#include "Desk.h"
#include "resource.h"
HWND hNomodal;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ModalProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ModalProc1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ModalProc2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK NomodalProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void CharToWchar(const char *, wchar_t *);
void WcharToChar(char *, const wchar_t *);

enum UserMessage { UM_DATASENT_PLAYER1 = WM_USER + 1, UM_DATASENT_PLAYER2 = WM_USER + 2, UM_DATASENT_TIMER = WM_USER + 3, UM_DATASENT_KINGCOORDS = WM_USER + 4, UM_DATASENT_CASTLECOORDS = WM_USER + 5};
struct Message
{
	wchar_t * message;
};
Message mes;
bool flag = false;

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szCommLine, int nCmdShow)
{
	static LPCWSTR szProgName = L"My Window";
	MSG msg;
	WNDCLASSEX wndclass;

	wndclass.cbSize = sizeof(WNDCLASSEX);	
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);	
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInst;	
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szProgName;
	wndclass.lpszMenuName = NULL;

	RegisterClassEx(&wndclass);

	HWND hWnd = CreateWindow(szProgName, TEXT("Chess"), WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZE,
							100, 100, 300, 285,
							(HWND)NULL,	(HMENU)NULL, hInst, NULL );
	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while( GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc;
	static HICON hIcon;
	static PAINTSTRUCT ps;
	static RECT rect;
	static HWND button_new_game, button_load_game, text;
	static CImage bk;
	static wchar_t buffer[100];
	static HBRUSH hBrush;
	static HRGN hRgn;
	static CImage arr[12], background;
	static HMENU hMenu, hContextMenu;
	static Desk d;
	static int x, y, x1, y1;
	static bool flag_team = 1;
	static bool timer = 0;
	static bool paint = 0;
	static wchar_t * player1;
	static wchar_t * player2;
	static int ticks = 0;
	static int king_x, king_y, castle_x, castle_y;
	switch(message)
	{
	case WM_CREATE:
		{
			bk.Load(L"ChessBk1.jpg");
			button_new_game = CreateWindow(L"button",L"New Game", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 165, 19, 80, 30, hWnd, (HMENU)IDD_BUTTON_NEW, NULL, NULL); 
			button_load_game = CreateWindow(L"button",L"Load Game", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 165, 60, 80, 30, hWnd, (HMENU)IDD_BUTTON_LOAD, NULL, NULL, NULL);
			hContextMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDM_CONTEXT));
			hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDM_MENU_MAIN));
			text = CreateWindow(L"STATIC",L"123", WS_CHILD | WS_VISIBLE, 0, 290, 340, 20, hWnd, (HMENU)IDT_INFO_TEXT, NULL, NULL);
			background.Load(L"Desk.jpg");
			arr[0].Load(L"PawnBlack.bmp");
			arr[1].Load(L"PawnWhite.png");
			arr[2].Load(L"CastleBlack.bmp");
			arr[3].Load(L"CastleWhite.bmp");
			arr[4].Load(L"HorseBlack.bmp");
			arr[5].Load(L"HorseWhite.bmp");
			arr[6].Load(L"OfficerBlack.bmp");
			arr[7].Load(L"OfficerWhite.bmp");
			arr[8].Load(L"QueenBlack.bmp");
			arr[9].Load(L"QueenWhite.bmp");
			arr[10].Load(L"KingBlack.bmp");
			arr[11].Load(L"KingWhite.bmp");
			hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));
			SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
		}
		break;
	case UM_DATASENT_PLAYER1:
		player1 = new wchar_t [wcslen((wchar_t*)wParam)+1];
		wcscpy(player1, (wchar_t*)wParam);
		if (paint == 1)
		{
			d.ToNull();
		}
		paint = 1;
		ShowWindow(button_load_game, SW_HIDE);
		ShowWindow(button_new_game, SW_HIDE);
		break;
	case UM_DATASENT_PLAYER2:
		player2 = new wchar_t [wcslen((wchar_t*)wParam)+1];
		wcscpy(player2, (wchar_t*)wParam);
		break;
	case UM_DATASENT_TIMER:
		if (!wcscmp(L"Yes", (wchar_t*)wParam))
		{
			timer = 1;
			SetTimer(hWnd, 1, 1000, NULL);
		}
		else
		{
			timer = 0;
		}
		InvalidateRect(hWnd, NULL, 1);
		SetMenu(hWnd, hMenu);
		SetWindowPos(hWnd, NULL, 100, 100, 300, 367, NULL);
		flag_team = 1;
		if (flag_team)
			wcscpy(buffer, player1);
		else
		wcscpy(buffer, player2);
		wcscat(buffer, L" moves");
		SetWindowText(text, buffer);
		InvalidateRect(text, NULL, 1);
		break;
	case UM_DATASENT_KINGCOORDS:
		{
			MessageBox(NULL , (wchar_t*)wParam, L"Chess", MB_OK);
			wchar_t swap[255];
			wcscpy(swap, (wchar_t*)wParam);
			king_x = (char)swap[0]-97;
			king_y = 8-(swap[1]-48);
		}
		break;
	case UM_DATASENT_CASTLECOORDS:
		{
			MessageBox(NULL , (wchar_t*)wParam, L"Chess", MB_OK);
			wchar_t swap[255];
			wcscpy(swap, (wchar_t*)wParam);
			castle_x = (char)swap[0]-97;
			castle_y = 8-(swap[1]-48);
			d.Rokirovka(king_y, king_x, castle_y, castle_x);
			InvalidateRect(hWnd, NULL, 1);
			if (flag_team)
				flag_team = 0;
			else
				flag_team = 1;
		}
		break;
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDD_BUTTON_NEW:
				DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_MODAL), hWnd, (DLGPROC)ModalProc);
				break;
			case IDD_BUTTON_LOAD:
				{
					int team;
					string player11;
					string player22;
					d.Open(player11, player22, team);
					player1 = new wchar_t [player11.length()+1];
					for (int i = 0;i<player11.length()+1;i++)
					{
						player1[i] = wchar_t(player11[i]);
					}
					player2 = new wchar_t [player22.length()+1];
					for (int i = 0;i<player22.length()+1;i++)
					{
						player2[i] = wchar_t(player22[i]);
					}
					if (team == 1)
						flag_team = 1;
					else
						flag_team = 0;
					paint = 1;
					ShowWindow(button_load_game, SW_HIDE);
					ShowWindow(button_new_game, SW_HIDE);
					InvalidateRect(hWnd, NULL, 1);
					SetMenu(hWnd, hMenu);
					SetWindowPos(hWnd, NULL, 100, 100, 300, 367, NULL);
					if (flag_team)
						wcscpy(buffer, player1);
					else
						wcscpy(buffer, player2);
					wcscat(buffer, L" moves");
					SetWindowText(text, buffer);
					InvalidateRect(text, NULL, 1);
				}
				break;
			case IDM_MENU_FILE_EXIT:
				if (timer)
					KillTimer(hWnd, 1);
				PostQuitMessage(0);
				break;
			case IDM_MENU_FILE_NEW:
				DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_MODAL), hWnd, (DLGPROC)ModalProc);
				break;
			case IDM_MENU_FILE_SAVE:
				{
					int team;
					if (flag_team)
						team = 2;
					else
						team = 1;
					d.Save(player1, player2, team);
				}
				break;
			case IDM_MENU_FILE_OPEN:
				{
					int team;
					string player11;
					string player22;
					d.Open(player11, player22, team);
					player1 = new wchar_t [player11.length()+1];
					for (int i = 0;i<player11.length()+1;i++)
					{
						player1[i] = wchar_t(player11[i]);
					}
					player2 = new wchar_t [player22.length()+1];
					for (int i = 0;i<player22.length()+1;i++)
					{
						player2[i] = wchar_t(player22[i]);
					}
					if (team == 1)
						flag_team = 0;
					else
						flag_team = 1;
					paint = 1;
					ShowWindow(button_load_game, SW_HIDE);
					ShowWindow(button_new_game, SW_HIDE);
					InvalidateRect(hWnd, NULL, 1);
					SetMenu(hWnd, hMenu);
					SetWindowPos(hWnd, NULL, 100, 100, 300, 367, NULL);
					if (flag_team)
						wcscpy(buffer, player1);
					else
						wcscpy(buffer, player2);
					wcscat(buffer, L" moves");
					SetWindowText(text, buffer);
					InvalidateRect(text, NULL, 1);
				}
				break;
			case IDM_CONTEXT_SETTINGS:
				flag = true;
				DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_MODAL), hWnd, (DLGPROC)ModalProc);
				break;
			case IDM_CONTEXT_CANCEL:
				d.SetPosition((y1-16)/32 , (x1-16)/32,(y-16)/32, (x-16)/32);
				if (flag_team)
					flag_team = 0;
				else
					flag_team = 1;
				ticks = 0;
				InvalidateRect(hWnd, NULL, 1);
				if (flag_team)
					wcscpy(buffer, player1);
				else
					wcscpy(buffer, player2);
				wcscat(buffer, L" moves");
				if (timer)
				{
					wcscat(buffer, L" 00:");
					wchar_t buf[255];
					if (60 - ticks / 1000 < 10)
					{
						wcscat(buf, L"0");
					}
					_itow(60 - ticks/1000, buf, 10);
					wcscat(buffer, buf);
				}
				SetWindowText(text, buffer);
				InvalidateRect(hWnd, NULL, 1);
				break;
			case IDM_CONTEXT_ROKIROVKA:
				DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_MODAL1), hWnd, (DLGPROC)ModalProc1);
				break;
			case IDM_MENU_ABOUT_HELP:
				DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_MODAL2), hWnd, (DLGPROC)ModalProc2);
				break;
			}
		}
		break;
	case WM_TIMER:
		{
			if(wParam == 1)
			{
				ticks+=1000;
				if (ticks == 60000)
				{
					if (flag_team)
						flag_team = 0;
					else
						flag_team = 1;
					ticks = 0;
				}
				if (flag_team)
					wcscpy(buffer, player1);
				else
					wcscpy(buffer, player2);
				wcscat(buffer, L" moves");
				if (timer)
				{
					wcscat(buffer, L" 00:");
					wchar_t buf[255];
					if (60 - ticks / 1000 < 10)
					{
						wcscat(buf, L"0");
					}
					_itow(60 - ticks/1000, buf, 10);
					wcscat(buffer, buf);
				}
				SetWindowText(text, buffer);
				InvalidateRect(hWnd, NULL, 1);
			}
		}
		break;
	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			if (paint == 0)
			{
				bk.Draw(hdc, 0, 0);
			}
			else
			{
				background.Draw(hdc, 0, 0);
				d.Print(hdc, arr);
			}
			EndPaint(hWnd, &ps);
		}
		break;
	case WM_CONTEXTMENU:
		{
			if (paint == 1)
			{
				HMENU  hContextResource = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDM_CONTEXT));
				hContextMenu = GetSubMenu(hContextResource, 0);
				POINT pt;
				GetCursorPos(&pt);
				TrackPopupMenu(hContextMenu,TPM_LEFTALIGN | TPM_RIGHTBUTTON,pt.x, pt.y,	0,hWnd,NULL);
			}
		}
		break;
	case WM_LBUTTONDOWN:
		if (paint == 1)
		{	
			x = LOWORD(lParam);
			y = HIWORD(lParam);
		}
		break;
	case WM_LBUTTONUP:
		if (paint == 1)
		{
			x1 = LOWORD(lParam);
			y1 = HIWORD(lParam);
			if (((y-16)/32 < 8 && (y-16)/32 >= 0) && ((x-16)/32 < 8 && (x-16)/32 >= 0) && ((y1-16)/32 < 8 && (y1-16)/32 >= 0) && ((x1-16)/32 < 8 && (x1-16)/32 >= 0))
			{
				if (flag_team == 0)
				{
					if(!d.CheckTeam((y-16)/32, (x-16)/32, 1))
					{
						flag_team = 0;
						SetWindowText(text, L"You can't move the figures of your enemy");
						InvalidateRect(hWnd, NULL, 1);
						Sleep(1000);
					}
					else
					{
						d.Move(text, (y-16)/32, (x-16)/32 , (y1-16)/32 , (x1-16)/32);
						InvalidateRect(hWnd, NULL, 1);
						flag_team = 1;
					}
				}
				else
				{
					if(!d.CheckTeam((y-16)/32, (x-16)/32, 2))
					{
						flag_team = 1;
						SetWindowText(text,L"You can't move the figures of your enemy");
						InvalidateRect(hWnd, NULL, 1);
						Sleep(1000);
					}
					else
					{
						d.Move(text, (y-16)/32, (x-16)/32 , (y1-16)/32 , (x1-16)/32);
						InvalidateRect(hWnd, NULL, 1);
						flag_team = 0;
					}
				}
				if (timer)
					ticks = 0;
				else
				{
					if (flag_team)
						wcscpy(buffer, player1);
					else
						wcscpy(buffer, player2);
					wcscat(buffer, L" moves");
					SetWindowText(text, buffer);
					InvalidateRect(hWnd, NULL, 1);
				}
			}
			else
			{
				SetWindowText(text,L"Invalid position !!!");
				Sleep(1000);
				InvalidateRect(hWnd, NULL, 1);
			}
		}
		break;
	case WM_DESTROY:
		if (timer)
			KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}	
	return 0;
}

LRESULT CALLBACK ModalProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND EditBox[2], radioButton[2], button[2], text[4];
	static wchar_t buffer_player1[255];
	static wchar_t buffer_player2[255];
	static wchar_t buffer_timer[255];
	static HICON hIcon;
	switch(message)
	{
	case WM_INITDIALOG:
		{
			if (flag == true)
				SetWindowText(hDlg, L"Load Game");
			text[0] = CreateWindow(L"STATIC",L"Player 1: ", WS_CHILD | WS_VISIBLE, 16, 16, 200, 20, hDlg, (HMENU)IDS_TEXT1, NULL, NULL);
			text[1] = CreateWindow(L"STATIC",L"Player 2:", WS_CHILD | WS_VISIBLE, 16, 66, 200, 20, hDlg, (HMENU)IDS_TEXT2, NULL, NULL);
			text[2] = CreateWindow(L"STATIC",L"With timer: ", WS_CHILD | WS_VISIBLE, 16, 116, 200, 20, hDlg, (HMENU)IDS_TEXT3, NULL, NULL);
			EditBox[0] = CreateWindow(L"edit",L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 16, 36, 200, 20, hDlg, (HMENU)IDE_EDIT1, NULL, NULL);
			EditBox[1] = CreateWindow(L"edit",L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 16, 86, 200, 20, hDlg, (HMENU)IDE_EDIT2, NULL, NULL);
			radioButton[0] = CreateWindow(L"button", L"Yes", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 16, 136, 80, 20, hDlg, (HMENU)IDB_RBUTTON1, NULL, NULL);
			radioButton[1] = CreateWindow(L"button", L"No", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 16, 166, 80, 20, hDlg, (HMENU)IDB_RBUTTON2, NULL, NULL);
			button[0] = CreateWindow(L"button", L"OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 16, 196, 90, 20, hDlg, (HMENU)IDB_BUTTONOK, NULL, NULL);
			button[1] = CreateWindow(L"button", L"Cancel", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 126, 196, 90, 20, hDlg, (HMENU)IDB_BUTTONCAN, NULL, NULL);
			hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));
			SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
		}
		break;
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDE_EDIT1:
				{
					if(HIWORD(wParam) == EN_CHANGE)
					{
						SendMessage(EditBox[0], WM_GETTEXT, 255, (LPARAM)buffer_player1);
						GetWindowText(EditBox[0], buffer_player1, 255);
					}
				}
				break;
			case IDE_EDIT2:
				{
					if(HIWORD(wParam) == EN_CHANGE)
					{
						SendMessage(EditBox[1], WM_GETTEXT, 255, (LPARAM)buffer_player2);
						GetWindowText(EditBox[1], buffer_player2, 255);
					}
				}
				break;
			case IDB_BUTTONOK:
				{
					SendMessage(GetParent(hDlg), UM_DATASENT_PLAYER1, (WPARAM)buffer_player1, NULL);
					SendMessage(GetParent(hDlg), UM_DATASENT_PLAYER2, (WPARAM)buffer_player2, NULL);
					wchar_t buffer_timer[255];
					if(SendMessage(radioButton[0], BM_GETCHECK, 0, 0) & BST_CHECKED)
					{
						wcscpy(buffer_timer, L"Yes");
					}
					else
					{
						wcscpy(buffer_timer, L"No");
					}
					SendMessage(GetParent(hDlg), UM_DATASENT_TIMER, (WPARAM)buffer_timer, NULL);
					EndDialog(hDlg, 0);
				}
				break;
			case IDB_BUTTONCAN:
				EndDialog(hDlg, 0);
				break;
			}
		}
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;
	}
	return 0;
}
LRESULT CALLBACK ModalProc1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND EditBox[2], button[2], text[2];
	static wchar_t buffer_king[255];
	static wchar_t buffer_castle[255];
	static HICON hIcon;
	switch(message)
	{
	case WM_INITDIALOG:
		{
			if (flag == true)
				SetWindowText(hDlg, L"Settings");
			text[0] = CreateWindow(L"STATIC",L"Enter king coords: ", WS_CHILD | WS_VISIBLE, 16, 16, 200, 20, hDlg, (HMENU)IDS_TEXT1, NULL, NULL);
			text[1] = CreateWindow(L"STATIC",L"Enter castle coords:", WS_CHILD | WS_VISIBLE, 16, 66, 200, 20, hDlg, (HMENU)IDS_TEXT2, NULL, NULL);
			EditBox[0] = CreateWindow(L"edit",L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 16, 36, 200, 20, hDlg, (HMENU)IDE_EDIT1, NULL, NULL);
			EditBox[1] = CreateWindow(L"edit",L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 16, 86, 200, 20, hDlg, (HMENU)IDE_EDIT2, NULL, NULL);
			button[0] = CreateWindow(L"button", L"OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 16, 116, 90, 30, hDlg, (HMENU)IDB_BUTTONOK, NULL, NULL);
			button[1] = CreateWindow(L"button", L"Cancel", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 126, 116, 90, 30, hDlg, (HMENU)IDB_BUTTONCAN, NULL, NULL);
			hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));
			SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
		}
		break;
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDE_EDIT1:
				{
					if(HIWORD(wParam) == EN_CHANGE)
					{
						SendMessage(EditBox[0], WM_GETTEXT, 255, (LPARAM)buffer_king);
						GetWindowText(EditBox[0], buffer_king, 255);
					}
				}
				break;
			case IDE_EDIT2:
				{
					if(HIWORD(wParam) == EN_CHANGE)
					{
						SendMessage(EditBox[1], WM_GETTEXT, 255, (LPARAM)buffer_castle);
						GetWindowText(EditBox[1], buffer_castle, 255);
					}
				}
				break;
			case IDB_BUTTONOK:
				{
					SendMessage(GetParent(hDlg), UM_DATASENT_KINGCOORDS, (WPARAM)buffer_king, NULL);
					SendMessage(GetParent(hDlg), UM_DATASENT_CASTLECOORDS, (WPARAM)buffer_castle, NULL);
					EndDialog(hDlg, 0);
				}
				break;
			case IDB_BUTTONCAN:
				EndDialog(hDlg, 0);
				break;
			}
		}
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;
	}
	return 0;
}

LRESULT CALLBACK ModalProc2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HICON hIcon;
	switch(message)
	{
	case WM_INITDIALOG:
		{
			hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));
			SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
		}
		break;
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDOK:
				{
					EndDialog(hDlg, 0);
				}
				break;
			}
		}
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;
	}
	return 0;
}
