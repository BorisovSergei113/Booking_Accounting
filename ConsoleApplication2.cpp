
#include "stdafx.h"
#include <windows.h> //necessary lib for mysql lib
#include "mysql.h"
//#include <winsock.h>
#include <iostream>
//#pragma comment(lib, "libmysql.lib")//unresolve symbol сыпется, если убрать эту строку



MYSQL *connection, mysql;
MYSQL_RES *result;
MYSQL_ROW row;
int query_state;

bool ConnectionSQL() {
	mysql_init(&mysql);
	/*connection = mysql_real_connect(&mysql,"host","user","password","database",port,"unix_socket",clientflag);*/
	connection = mysql_real_connect(&mysql, "localhost","root", "1234", "mydb", 3306, 0, 0);
	if (connection == NULL) {
		std::cout << mysql_error(&mysql) << std::endl;
		return false;
	}
	//std::cout << mysql_get_host_info(&mysql)<<'\n'; //Type network protocol
	mysql_select_db(&mysql, "mydb");
	mysql_query(&mysql, "SET NAMES 'cp1251'");
	query_state = mysql_query(connection, "SELECT * FROM test_table ;");
	if (query_state != 0) {
		std::cout << mysql_error(connection) << std::endl;
		return false;
	}
	 result = mysql_store_result(connection);
	 return true;
}

LRESULT CALLBACK MainWinProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp);
// инициализируем главное окно и его класс
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int station_main_wnd) {
	if (ConnectionSQL() == false) return FALSE;
	/* создаем и регистрируем класс главного окна */
	WNDCLASS wc; //создание класса окна wc
	wc.style = 0; //задаём стиль
	wc.lpfnWndProc = MainWinProc; //процедура обработки событий окна
	wc.cbClsExtra = wc.cbWndExtra = 0; //размер доп памяти в системной структуре класса/окна для данных пользователя
	wc.hInstance = hInst; //дескриптор модуля (экземпляра программы) в котором реализована процедура обработки
	wc.hIcon = NULL; //дескриптор иконки окна (нет)
	wc.hCursor = NULL; //дескриптор курсора окна (нет)
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); //цвет фона окна
	wc.lpszMenuName = NULL; //имя структуры содержащие меню окна
	LPCWSTR a = L"MainWnd Class";
	LPCWSTR b = L"Booking_Accounting";
	wc.lpszClassName = a; //имя класса главного окна
	if (!RegisterClass(&wc)) return FALSE; //в случае НЕ регистрации класса окна выходим из ф-ии
    /* создаем главное окно и отображаем его */
    /*CreateWindow(lpszClassName имя класса окна,lpWindowName название окна,
    dwStyle тип вывода окна,int x горизонт позиция на экране,
	int y вертикальная позиция ,int nWidth Ширина, int nHeight Высота,hwndParent дескриптор род.Окна,
	hwndMenu дескриптор меню,hInstance дескриптор экземпляра программы,lpParam указатель на данные создания окна) */
	HWND hMainWnd = CreateWindow(a,b, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
	if (!hMainWnd) return FALSE; //в случае ошибки создание окна
	ShowWindow(hMainWnd, station_main_wnd); //выводим окно
	UpdateWindow(hMainWnd); //обновляем область прорисовываемую по WM_PAINT

							/* цикл обработки событий */
	MSG msg; //структура содержащая инф-ию из очереди сообщений потока
	INT buf;
	while ((buf = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0) { //NULL-извлекаем сообщения из всех окон в msg
		if (buf == -1) {
			return FALSE;//обработка исключений
		}
		else {
			TranslateMessage(&msg); //конвертируем информацию из потока
			DispatchMessage(&msg);//пересылаем сообщение оконной процедуре (в msg содержится HWND)
		}
	}
	return msg.wParam; //возращаем тоже значение что и оконная процедура MainWinProc
}

/* функция обработки сообщений для главного окна */
LRESULT CALLBACK MainWinProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp) {
	LPCWSTR y = L"Action_Message";
	LPCWSTR m = L"button";
	LPCWSTR c = L"Query mysql";
	static HWND hEditText;
	switch (msg) {
	case WM_CREATE: {
		/* при создании окна внедряем в него кнопочку */
		CreateWindow(m, c, WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 5, 5, 100, 20, hw, (HMENU)1, NULL, NULL);
		/* стиль WS_CHILD означает, что это дочернее окно и для него
		вместо дескриптора меню будет передан целочисленный идентификатор,
		который будет использоваться дочерним окном для оповещения
		родительского окна через WM_COMMAND */
		HINSTANCE hInst = ((LPCREATESTRUCT)lp)->hInstance;
		hEditText = CreateWindow(L"static", L"0", WS_CHILD | WS_VISIBLE,
			150, 180, 120, 20, hw, 0, hInst, NULL);
		ShowWindow(hEditText, SW_SHOWNORMAL);
		SetWindowText(hEditText, L"Test");
		break;
	}
	case WM_COMMAND: {
		LPCWSTR o = L"No member in DB";
		row = mysql_fetch_row(result);
		if (row == NULL) {
			SetWindowText(hEditText, L"All rows ended");
			break;
		}
			std::string a = row[0];
			std::string b = row[1];
			a = a + " "+ b;
			std::wstring s = std::wstring(a.begin(), a.end());
			o = s.c_str();
		if ((HIWORD(wp) == 0) && (LOWORD(wp) == 1))
			SetWindowText(hEditText, o);
		break;
	}
	case WM_DESTROY: {
		/* пользователь закрыл окно, программа может завершаться */
		mysql_free_result(result);
		mysql_close(connection);
		PostQuitMessage(0);
		break;
	}
		default: return DefWindowProc(hw, msg, wp, lp);
	}
}
