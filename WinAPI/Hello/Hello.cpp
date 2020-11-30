#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
ATOM InitApp(HINSTANCE hInst);
BOOL InitInstance(HINSTANCE hInst, int nCmdShow);

// ウィンドウクラス
TCHAR szClassName[] = TEXT("sample01");

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, LPSTR lpsCmdLine, int nCmdShow)
{
	MSG msg;
	BOOL bRet;

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
	wc.lpszMenuName = NULL;                   // メニュー名
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
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;

	switch (msg) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps); // デバイスコンテキストを取得

		hPen = CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
		hOldPen = (HPEN)SelectObject(hdc, hPen);

		hBrush = CreateSolidBrush(RGB(0, 255, 0));
		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, 10, 10, 100, 100);
		DeleteObject(hBrush);

		hBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(0, 255, 0));
		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, 50, 50, 150, 150);
		DeleteObject(hBrush);

		hBrush = CreateHatchBrush(HS_FDIAGONAL, RGB(0, 0, 255));
		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, 100, 100, 200, 200);
		DeleteObject(hBrush);

		hBrush = CreateHatchBrush(HS_CROSS, RGB(255, 0, 255));
		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, 150, 150, 250, 250);
		DeleteObject(hBrush);

		hBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 255, 0));
		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, 200, 200, 300, 300);
		DeleteObject(hBrush);

		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, 250, 250, 350, 350);
		DeleteObject(hBrush);

		DeleteObject(hPen);
		SelectObject(hdc, hOldPen);
		SelectObject(hdc, hOldBrush);

		EndPaint(hWnd, &ps); // 描画処理を終了
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return (DefWindowProc(hWnd, msg, wp, lp));
	}

	return 0;
}
