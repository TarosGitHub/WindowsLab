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
	HBRUSH hBrush, hOldBrush;
	POINT pt[4] = { {20, 20}, {20, 80}, {120, 50}, {100, 100} };
	POINT poly[7] = { {150, 20}, {200, 25}, {210, 70}, {145, 65},
	                  {180, 10}, {160, 90}, {205, 100} };
	INT nC[2] = { 4, 3 };

	switch (msg) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps); // デバイスコンテキストを取得

		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		// 1つの多角形を描画
		Polygon(hdc, pt, 4);

		// 2つの多角形を描画
		PolyPolygon(hdc, poly, nC, 2);

		DeleteObject(hBrush);
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
