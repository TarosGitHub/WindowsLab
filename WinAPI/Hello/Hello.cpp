#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
ATOM InitApp(HINSTANCE hInst);
BOOL InitInstance(HINSTANCE hInst, int nCmdShow);

// ウィンドウクラス
TCHAR szClassName[] = TEXT("bitmap02");

HINSTANCE hInst;
HDC hdc_mem1, hdc_mem2;
int show_no = 1;

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, LPSTR lpsCmdLine, int nCmdShow)
{
	MSG msg;
	BOOL bRet;
	hInst = hCurInst;

	// ウィンドウクラスの登録
	if (!InitApp(hCurInst)) {
		return FALSE;
	}

	// ウィンドウの生成
	if (!InitInstance(hCurInst, nCmdShow)) {
		return FALSE;
	}

	// メッセージループ
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (bRet == -1) {
			break;
		}
		else {
			TranslateMessage(&msg);    // メッセージを変換
			DispatchMessage(&msg);     // メッセージを送出
		}
	}

	return (int)msg.wParam;
}

// ウィンドウクラスの登録
ATOM InitApp(HINSTANCE hInst)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);           // 構造体のサイズ
	wc.style = CS_HREDRAW | CS_VREDRAW;       // クラスのスタイル
	wc.lpfnWndProc = WndProc;                 // プロシージャ名
	wc.cbClsExtra = 0;                        // 補助メモリ
	wc.cbWndExtra = 0;                        // 補助メモリ
	wc.hInstance = hInst;                     // インスタンス
	wc.hIcon = (HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION),	IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED); // アイコン
	wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED); // カーソル
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 背景ブラシ
	wc.lpszMenuName = TEXT("MYMENU");         // メニュー名
	wc.lpszClassName = szClassName;           // クラス名
	wc.hIconSm = (HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION), IMAGE_ICON, 0, 0,	LR_DEFAULTSIZE | LR_SHARED); // 小さいアイコン

	return (RegisterClassEx(&wc));
}

// ウィンドウの生成
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
	HWND hWnd;

	hWnd = CreateWindow(szClassName, // クラス名
		TEXT("猫でもわかるWindowsプログラミング"), // ウィンドウ名
		WS_OVERLAPPEDWINDOW,     // ウィンドウスタイル
		CW_USEDEFAULT,           // x位置
		CW_USEDEFAULT,           // y位置
		CW_USEDEFAULT,           // ウィンドウ幅
		CW_USEDEFAULT,           // ウィンドウ高さ
		NULL,  // 親ウィンドウのハンドル、親を作るときはNULL
		NULL,  // メニューハンドル、クラスメニューを使うときはNULL
		hInst, // インスタンスハンドル
		NULL   // ウィンドウ作成データ
	);

	if (!hWnd) {
		return FALSE;
	}

	// ウィンドウの表示状態を設定
	ShowWindow(hWnd, nCmdShow);
	
	// ウィンドウを更新
	UpdateWindow(hWnd);
	
	return TRUE;
}

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBITMAP hBmp;
	HDC hdc_memx;

	switch (msg) {
	case WM_CREATE:
		hdc = GetDC(hWnd);

		// メモリデバイスコンテキストhdc_mem1にビットマップリソースMYBMP1を読み込む
		hBmp = LoadBitmap(hInst, TEXT("MYBMP1"));
		hdc_mem1 = CreateCompatibleDC(hdc);
		SelectObject(hdc_mem1, hBmp);
		DeleteObject(hBmp);

		// メモリデバイスコンテキストhdc_mem2にビットマップリソースMYBMP2を読み込む
		hBmp = LoadBitmap(hInst, TEXT("MYBMP2"));
		hdc_mem2 = CreateCompatibleDC(hdc);
		SelectObject(hdc_mem2, hBmp);
		DeleteObject(hBmp);

		ReleaseDC(hWnd, hdc);
		break;

	case WM_PAINT:
		BeginPaint(hWnd, &ps); // デバイスコンテキストを取得

		if (1 == show_no) {
			hdc_memx = hdc_mem1;
		}
		else if (2 == show_no) {
			hdc_memx = hdc_mem2;
		}
		else {
			hdc_memx = hdc_mem1;
		}

		// ビットマップを転送
		BitBlt(ps.hdc, ps.rcPaint.left, ps.rcPaint.top,
			ps.rcPaint.right - ps.rcPaint.left,
			ps.rcPaint.bottom - ps.rcPaint.top,
			hdc_memx, ps.rcPaint.left, ps.rcPaint.top, SRCCOPY);

		EndPaint(hWnd, &ps); // 描画処理を終了
		break;

	case WM_COMMAND:
		// メニュー項目の選択時の処理
		switch (LOWORD(wp)) {
		case IDM_CAT1:
			show_no = 1;
			InvalidateRect(hWnd, NULL, TRUE); // 無効領域の発生(WM_PAINTメッセージの送信)
			break;

		case IDM_CAT2:
			show_no = 2;
			InvalidateRect(hWnd, NULL, TRUE); // 無効領域の発生(WM_PAINTメッセージの送信)
			break;

		case IDM_END:
			SendMessage(hWnd, WM_CLOSE, 0, 0); // WM_CLOSEメッセージ送信 -> DestroyWindow関数の自動実行 -> WM_DESTROYメッセージ発生
			break;
		}
		break;

	case WM_DESTROY:
		DeleteDC(hdc_mem1);
		DeleteDC(hdc_mem2);
		PostQuitMessage(0);
		break;

	default:
		return (DefWindowProc(hWnd, msg, wp, lp));
	}

	return 0;
}
