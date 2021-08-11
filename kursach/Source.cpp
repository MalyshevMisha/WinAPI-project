#define IDM_CREATE 1230
#pragma comment (lib, "winmm.lib")
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h> // підключення бібліотеки з функціями API
#include "Header.h"
#include <mmsystem.h>
#include <ctime>
#include <fstream>
#include <string>

// Глобальні змінні:
HINSTANCE hInst; 	//Дескриптор програми	
LPCTSTR szWindowClass = "QWERTY";
LPCTSTR szTitle = "Game";
static SHORT x = 0;
static SHORT y = 0;
int * tower1 = new int[8]{ 1,2,3,4,5,6,7,8 };	//массив для башни №1
int * tower2 = new int[8]{ 0 };	//массив для башни №2
int * tower3 = new int[8]{ 0 };	//массив для башни №3
int raisedRing = 0; //поднятое кольцо
int indexArray;
static HPEN hPen, hPen1, hPen2, hPen3, hPen4, hPen5, hPen6, hPen7, hPen8;
static HBRUSH hB, hB1, hB2, hB3, hB4, hB5, hB6, hB7, hB8;
bool tower = false,
music = false,
newGame = true;
int firstTime;
HWND hEdit;
std::string writeToFile;
// Попередній опис функцій

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HMENU hMenu, hMenuPopup;

// Основна програма 
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	hMenu = CreateMenu();
	hMenuPopup = CreateMenu();
	AppendMenu(hMenuPopup, MF_STRING, IDM_CREATE, "&New game");
	AppendMenu(hMenuPopup, MF_STRING, IDM_CREATE + 1, "&Result");
	AppendMenu(hMenu, MF_POPUP, (UINT)hMenuPopup, "&Game");
	AppendMenu(hMenu, MF_POPUP, IDM_CREATE + 2, "&Rules");

	MSG msg;

	// Реєстрація класу вікна 
	MyRegisterClass(hInstance);

	// Створення вікна програми
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	// Цикл обробки повідомлень
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW; 		//стиль вікна
	wcex.lpfnWndProc = (WNDPROC)WndProc; 		//віконна процедура
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance; 			//дескриптор програми
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		//визначення іконки
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); 	//визначення курсору
	wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW); //установка фону
	wcex.lpszMenuName = NULL; 				//визначення меню
	wcex.lpszClassName = szWindowClass; 		//ім’я класу
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex); 			//реєстрація класу вікна
}

// FUNCTION: InitInstance (HANDLE, int)
// Створює вікно програми і зберігає дескриптор програми в змінній hInst

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance; //зберігає дескриптор додатка в змінній hInst
	hWnd = CreateWindow(szWindowClass, 	// ім’я класу вікна
		szTitle, 				// назва програми
		WS_DLGFRAME | WS_MINIMIZEBOX | WS_SYSMENU | WS_MAXIMIZE,			// стиль вікна
		0, 			// положення по Х	
		0,			// положення по Y	
		1500, 			// розмір по Х
		900, 			// розмір по Y
		NULL, 					// дескриптор батьківського вікна	
		hMenu, 					// дескриптор меню вікна
		hInstance, 				// дескриптор програми
		NULL); 				// параметри створення.

	if (!hWnd) 	//Якщо вікно не творилось, функція повертає FALSE
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow); 		//Показати вікно
	UpdateWindow(hWnd); 				//Оновити вікно
	return TRUE;
}

// FUNCTION: WndProc (HWND, unsigned, WORD, LONG)
// Віконна процедура. Приймає і обробляє всі повідомлення, що приходять в додаток


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;

	switch (message)
	{
	case WM_CREATE: 				//Повідомлення приходить при створенні вік-на
		hEdit = CreateWindow("edit", "Entr your name",
			WS_CHILD | WS_VISIBLE | ES_CENTER,
			10, 200, 1480, 20,
			hWnd, NULL, hInst, NULL);
		break;

	case WM_PAINT: 				//Перемалювати вікно
		hdc = BeginPaint(hWnd, &ps); 	//Почати графічний вивід	
		GetClientRect(hWnd, &rt); 		//Область вікна для малювання

		//if (music)
		//{
		//	PlaySoundA((LPCSTR)"D:\\lessons\\SPRO\\kursach\\National Anthem of Ukraine.wav", NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
		//	music = false;
		//}

		hPen8 = CreatePen(BS_SOLID, 0, RGB(248, 6, 3));
		hB8 = CreateSolidBrush(RGB(248, 6, 3));
		//SelectObject(hdc, hPen8);
		//SelectObject(hdc, hB8);
		//Rectangle(hdc, 38, 750, 463, 800);
		//Rectangle(hdc, 538, 750, 963, 800);
		//Rectangle(hdc, 1038, 750, 1463, 800);

		hPen7 = CreatePen(BS_SOLID, 0, RGB(211, 139, 225));
		hB7 = CreateSolidBrush(RGB(211, 139, 225));
		//SelectObject(hdc, hPen7);
		//SelectObject(hdc, hB7);
		//Rectangle(hdc, 63, 700, 438, 750);
		//Rectangle(hdc, 563, 700, 938, 750);
		//Rectangle(hdc, 1063, 700, 1438, 750);

		hPen6 = CreatePen(BS_SOLID, 0, RGB(242, 112, 28));
		hB6 = CreateSolidBrush(RGB(242, 112, 28));
		//SelectObject(hdc, hPen6);
		//SelectObject(hdc, hB6);
		//Rectangle(hdc, 88, 650, 413, 700);
		//Rectangle(hdc, 588, 650, 913, 700);
		//Rectangle(hdc, 1088, 650, 1413, 700);

		hPen5 = CreatePen(BS_SOLID, 0, RGB(22, 14, 191));
		hB5 = CreateSolidBrush(RGB(22, 14, 191));
		//SelectObject(hdc, hPen5);
		//SelectObject(hdc, hB5);
		//Rectangle(hdc, 113, 600, 388, 650);
		//Rectangle(hdc, 613, 600, 888, 650);
		//Rectangle(hdc, 1113, 600, 1388, 650);

		hPen4 = CreatePen(BS_SOLID, 0, RGB(0, 108, 254));
		hB4 = CreateSolidBrush(RGB(0, 108, 254));
		//SelectObject(hdc, hPen4);
			//SelectObject(hdc, hB4);
			//Rectangle(hdc, 138, 550, 363, 600);
			//Rectangle(hdc, 638, 550, 863, 600);
			//Rectangle(hdc, 1138, 550, 1363, 600);

		hPen3 = CreatePen(BS_SOLID, 0, RGB(0, 124, 73));
		hB3 = CreateSolidBrush(RGB(0, 124, 73));
		//SelectObject(hdc, hPen3);
		//SelectObject(hdc, hB3);
		//Rectangle(hdc, 163, 500, 338, 550);
		//Rectangle(hdc, 663, 500, 838, 550);
		//Rectangle(hdc, 1163, 500, 1338, 550);

		hPen2 = CreatePen(BS_SOLID, 0, RGB(242, 234, 0));
		hB2 = CreateSolidBrush(RGB(242, 234, 0));
		//SelectObject(hdc, hPen2);
			//SelectObject(hdc, hB2);
			//Rectangle(hdc, 188, 450, 313, 500);
			//Rectangle(hdc, 688, 450, 813, 500);
			//Rectangle(hdc, 1188, 450, 1313, 500);

		hPen1 = CreatePen(BS_SOLID, 0, RGB(134, 5, 134));
		hB1 = CreateSolidBrush(RGB(134, 5, 134));
		//SelectObject(hdc, hPen1);
		//SelectObject(hdc, hB1);
		//Rectangle(hdc, 213, 400, 288, 450);
		//Rectangle(hdc, 713, 400, 788, 450);
		//Rectangle(hdc, 1213, 400, 1288, 450);

		if (tower)
		{
			SelectObject(hdc, hPen4);
			SelectObject(hdc, hB4);
			Rectangle(hdc, 0, 0, 1500, 450);
			SelectObject(hdc, hPen2);
			SelectObject(hdc, hB2);
			Rectangle(hdc, 0, 450, 1500, 900);
		}

		DeleteObject(hPen2);
		DeleteObject(hB2);

		DeleteObject(hPen4);
		DeleteObject(hB4);

		if (tower)
		{
			hPen4 = CreatePen(BS_SOLID, 0, RGB(10, 118, 264));
			hB4 = CreateSolidBrush(RGB(10, 118, 264));
		}
		else
		{
			hPen4 = CreatePen(BS_SOLID, 0, RGB(0, 108, 254));
			hB4 = CreateSolidBrush(RGB(0, 108, 254));
			//SelectObject(hdc, hPen4);
			//SelectObject(hdc, hB4);
			//Rectangle(hdc, 138, 550, 363, 600);
			//Rectangle(hdc, 638, 550, 863, 600);
			//Rectangle(hdc, 1138, 550, 1363, 600);
		}

		if (tower)
		{
			hPen2 = CreatePen(BS_SOLID, 0, RGB(252, 244, 10));
			hB2 = CreateSolidBrush(RGB(252, 244, 10));
		}
		else
		{
			hPen2 = CreatePen(BS_SOLID, 0, RGB(242, 234, 0));
			hB2 = CreateSolidBrush(RGB(242, 234, 0));
			//SelectObject(hdc, hPen2);
			//SelectObject(hdc, hB2);
			//Rectangle(hdc, 188, 450, 313, 500);
			//Rectangle(hdc, 688, 450, 813, 500);
			//Rectangle(hdc, 1188, 450, 1313, 500);
		}


		hPen = CreatePen(BS_SOLID, 0, RGB(227, 175, 112));
		hB = CreateSolidBrush(RGB(227, 175, 112));
		SelectObject(hdc, hPen);
		SelectObject(hdc, hB);
		Rectangle(hdc, 235, 390, 265, 820);	//столб №1
		Rectangle(hdc, 28, 800, 473, 830);
		Rectangle(hdc, 735, 390, 765, 820);	//столб №2
		Rectangle(hdc, 528, 800, 973, 830);
		Rectangle(hdc, 1235, 390, 1265, 820);	//столб №3
		Rectangle(hdc, 1028, 800, 1473, 830);

		switch (raisedRing)
		{
		case (1):
			SelectObject(hdc, hPen1);
			SelectObject(hdc, hB1);
			Rectangle(hdc, 713, 300, 788, 350);
			break;
		case (2):
			SelectObject(hdc, hPen2);
			SelectObject(hdc, hB2);
			Rectangle(hdc, 688, 300, 813, 350);
			break;
		case (3):
			SelectObject(hdc, hPen3);
			SelectObject(hdc, hB3);
			Rectangle(hdc, 663, 300, 838, 350);
			break;
		case (4):
			SelectObject(hdc, hPen4);
			SelectObject(hdc, hB4);
			Rectangle(hdc, 638, 300, 863, 350);

			break;
		case (5):
			SelectObject(hdc, hPen5);
			SelectObject(hdc, hB5);
			Rectangle(hdc, 613, 300, 888, 350);
			break;
		case (6):
			SelectObject(hdc, hPen6);
			SelectObject(hdc, hB6);
			Rectangle(hdc, 588, 300, 913, 350);
			break;
		case (7):
			SelectObject(hdc, hPen7);
			SelectObject(hdc, hB7);
			Rectangle(hdc, 563, 300, 938, 350);
			break;
		case (8):
			SelectObject(hdc, hPen8);
			SelectObject(hdc, hB8);
			Rectangle(hdc, 538, 300, 963, 350);
			break;
		}

		if (ArraySearch(tower1, 8, indexArray))
		{
			SelectObject(hdc, hPen8);
			SelectObject(hdc, hB8);
			indexArray = (indexArray+1-8) * 50;
			Rectangle(hdc, 38, 750+indexArray, 463, 800+indexArray);
		}

		if (ArraySearch(tower1, 7, indexArray))
		{
			SelectObject(hdc, hPen7);
			SelectObject(hdc, hB7);
			indexArray = (indexArray + 1 - 7) * 50;
			Rectangle(hdc, 63, 700+indexArray, 438, 750+indexArray);
		}

		if (ArraySearch(tower1, 6, indexArray))
		{
			SelectObject(hdc, hPen6);
			SelectObject(hdc, hB6);
			indexArray = (indexArray + 1 - 6) * 50;
			Rectangle(hdc, 88, 650+indexArray, 413, 700+indexArray);
		}

		if (ArraySearch(tower1, 5, indexArray))
		{
			SelectObject(hdc, hPen5);
			SelectObject(hdc, hB5);
			indexArray = (indexArray + 1 - 5) * 50;
			Rectangle(hdc, 113, 600+indexArray, 388, 650+indexArray);
		}

		if (ArraySearch(tower1, 4, indexArray))
		{
			SelectObject(hdc, hPen4);
			SelectObject(hdc, hB4);
			indexArray = (indexArray + 1 - 4) * 50;
			Rectangle(hdc, 138, 550+indexArray, 363, 600+indexArray);
		}

		if (ArraySearch(tower1, 3, indexArray))
		{
			SelectObject(hdc, hPen3);
			SelectObject(hdc, hB3);
			indexArray = (indexArray + 1 - 3) * 50;
			Rectangle(hdc, 163, 500+indexArray, 338, 550+indexArray);
		}

		if (ArraySearch(tower1, 2, indexArray))
		{
			SelectObject(hdc, hPen2);
			SelectObject(hdc, hB2);
			indexArray = (indexArray + 1 - 2) * 50;
			Rectangle(hdc, 188, 450+indexArray, 313, 500+indexArray);
		}

		if (ArraySearch(tower1, 1, indexArray))
		{
			SelectObject(hdc, hPen1);
			SelectObject(hdc, hB1);
			indexArray = (indexArray + 1 - 1) * 50;
			Rectangle(hdc, 213, 400+indexArray, 288, 450+indexArray);
		}


		if (ArraySearch(tower2, 8, indexArray))
		{
			SelectObject(hdc, hPen8);
			SelectObject(hdc, hB8);
			indexArray = (indexArray + 1 - 8) * 50;
			Rectangle(hdc, 38+500, indexArray, 463+500, 800+indexArray);
		}

		if (ArraySearch(tower2, 7, indexArray))
		{
			SelectObject(hdc, hPen7);
			SelectObject(hdc, hB7);
			indexArray = (indexArray + 1 - 7) * 50;
			Rectangle(hdc, 63 + 500, 700+indexArray, 438 + 500, 750+indexArray);
		}

		if (ArraySearch(tower2, 6, indexArray))
		{
			SelectObject(hdc, hPen6);
			SelectObject(hdc, hB6);
			indexArray = (indexArray + 1 - 6) * 50;
			Rectangle(hdc, 88 + 500, 650+indexArray, 413 + 500, 700+indexArray);
		}

		if (ArraySearch(tower2, 5, indexArray))
		{
			SelectObject(hdc, hPen5);
			SelectObject(hdc, hB5);
			indexArray = (indexArray + 1 - 5) * 50;
			Rectangle(hdc, 113 + 500, 600+indexArray, 388 + 500, 650+indexArray);
		}

		if (ArraySearch(tower2, 4, indexArray))
		{
			SelectObject(hdc, hPen4);
			SelectObject(hdc, hB4);
			indexArray = (indexArray + 1 - 4) * 50;
			Rectangle(hdc, 138 + 500, 550+indexArray, 363 + 500, 600+indexArray);
		}

		if (ArraySearch(tower2, 3, indexArray))
		{
			SelectObject(hdc, hPen3);
			SelectObject(hdc, hB3);
			indexArray = (indexArray + 1 - 3) * 50;
			Rectangle(hdc, 163 + 500, 500+ indexArray, 338 + 500, 550+indexArray);
		}

		if (ArraySearch(tower2, 2, indexArray))
		{
			SelectObject(hdc, hPen2);
			SelectObject(hdc, hB2);
			indexArray = (indexArray + 1 - 2) * 50;
			Rectangle(hdc, 188 + 500, 450+ indexArray, 313 + 500, 500+ indexArray);
		}

		if (ArraySearch(tower2, 1, indexArray))
		{
			SelectObject(hdc, hPen1);
			SelectObject(hdc, hB1);
			indexArray= (indexArray + 1 - 1) *50;
			Rectangle(hdc, 213 + 500, 400+ indexArray, 288 + 500, 450+ indexArray);
		}


		if (ArraySearch(tower3, 8, indexArray))
		{
			SelectObject(hdc, hPen8);
			SelectObject(hdc, hB8);
			indexArray = (indexArray + 1 - 8) * 50;
			Rectangle(hdc, 38+1000, 750+indexArray, 463 + 1000, 800+indexArray);
		}

		if (ArraySearch(tower3, 7, indexArray))
		{
			SelectObject(hdc, hPen7);
			SelectObject(hdc, hB7);
			indexArray = (indexArray + 1 - 7) * 50;
			Rectangle(hdc, 63 + 1000, 700+indexArray, 438 + 1000, 750+indexArray);
		}

		if (ArraySearch(tower3, 6, indexArray))
		{
			SelectObject(hdc, hPen6);
			SelectObject(hdc, hB6);
			indexArray = (indexArray + 1 - 6) * 50;
			Rectangle(hdc, 88 + 1000, 650+indexArray, 413 + 1000, 700+indexArray);
		}

		if (ArraySearch(tower3, 5, indexArray))
		{
			SelectObject(hdc, hPen5);
			SelectObject(hdc, hB5);
			indexArray = (indexArray + 1 - 5) * 50;
			Rectangle(hdc, 113 + 1000, 600+indexArray, 388 + 1000, 650+indexArray);
		}

		if (ArraySearch(tower3, 4, indexArray))
		{
			SelectObject(hdc, hPen4);
			SelectObject(hdc, hB4);
			indexArray = (indexArray + 1 - 4) * 50;
			Rectangle(hdc, 138 + 1000, 550+indexArray, 363 + 1000, 600+indexArray);
		}

		if (ArraySearch(tower3, 3, indexArray))
		{
			SelectObject(hdc, hPen3);
			SelectObject(hdc, hB3);
			indexArray = (indexArray + 1 - 3) * 50;
			Rectangle(hdc, 163 + 1000, 500+indexArray, 338 + 1000, 550+indexArray);
		}

		if (ArraySearch(tower3, 2, indexArray))
		{
			SelectObject(hdc, hPen2);
			SelectObject(hdc, hB2);
			indexArray = (indexArray + 1 - 2) * 50;
			Rectangle(hdc, 188 + 1000, 450+indexArray, 313 + 1000, 500+indexArray);
		}

		if (ArraySearch(tower3, 1, indexArray))
		{
			SelectObject(hdc, hPen1);
			SelectObject(hdc, hB1);
			indexArray = (indexArray + 1 - 1) * 50;
			Rectangle(hdc, 213 + 1000, 400+indexArray, 288 + 1000, 450+indexArray);
		}

		DeleteObject(hPen);
		DeleteObject(hB);

		DeleteObject(hPen1);
		DeleteObject(hB1);

		DeleteObject(hPen2);
		DeleteObject(hB2);

		DeleteObject(hPen3);
		DeleteObject(hB3);

		DeleteObject(hPen4);
		DeleteObject(hB4);

		DeleteObject(hPen5);
		DeleteObject(hB5);

		DeleteObject(hPen6);
		DeleteObject(hB6);

		DeleteObject(hPen7);
		DeleteObject(hB7);

		DeleteObject(hPen8);
		DeleteObject(hB8);

		if (tower3[0] == 1)
		{
			char str[100];
			TextOut(hdc, 705, CW_USEDEFAULT, str, wsprintf(str, "You Win!!!"));
			std::fstream fout("D:\\lessons\\SPRO\\kursach\\Leaders.txt", std::ios_base::app);
			char buffArr[200];
			int buffTime;
			GetWindowTextA(hEdit, (LPSTR)buffArr, 200);
			writeToFile = writeToFile + buffArr;
			writeToFile.push_back('-');
			buffTime = clock();
			buffTime = buffTime - firstTime;
			std::string buffStringTime;
			buffStringTime = std::to_string(buffTime);
			writeToFile = writeToFile + buffStringTime;
			writeToFile.push_back('\n');
			fout << writeToFile;
			buffStringTime.clear();
			writeToFile.clear();
			fout.close();
		}

		if (tower1[0] == 1)
		{
			firstTime = clock();
		}


		EndPaint(hWnd, &ps); 		//Закінчити графічний вивід	
		break;

	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		if (y > 380 && x > 0 && x < 500)
		{
			if (raisedRing)
			{
				PutRingDown(1, raisedRing, tower1, tower2, tower3);
			}
			else
			{
				RingLift(1, raisedRing, tower1, tower2, tower3);
			}
			InvalidateRect(hWnd, NULL, true);
		}
		if (y > 380 && x > 500 && x < 1000)
		{
			if (raisedRing)
			{
				PutRingDown(2, raisedRing, tower1, tower2, tower3);
			}
			else
			{
				RingLift(2, raisedRing, tower1, tower2, tower3);
			}
			InvalidateRect(hWnd, NULL, true);
		}
		if (y > 380 && x > 1000 && x < 1500)
		{
			if (raisedRing)
			{
				PutRingDown(3, raisedRing, tower1, tower2, tower3);
			}
			else
			{
				RingLift(3, raisedRing, tower1, tower2, tower3);
			}
			InvalidateRect(hWnd, NULL, true);
		}
		if (y < 2 && x < 1500 && x >1400)
		{
			tower = true;
			music = true;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_CREATE:
			raisedRing = 0;
			for (int i = 0; i < 8; i++)
			{
				tower1[i] = i + 1;
				tower2[i] = 0;
				tower3[i] = 0;
				tower = false;
				music = false;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case IDM_CREATE + 1:
			ShellExecute(NULL, "open", "D:\\lessons\\SPRO\\kursach\\Leaders.txt", NULL, NULL, SW_SHOWNORMAL);
			break;

		case IDM_CREATE + 2:
			ShellExecute(NULL, "open", "D:\\lessons\\SPRO\\kursach\\Rules.txt", NULL, NULL, SW_SHOWNORMAL);
			break;
		}
		break;

	case WM_DESTROY: 				//Завершення роботи
		PostQuitMessage(0);
		break;
	default:
		//Обробка повідомлень, які не оброблені користувачем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
