#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
ATOM InitApp(HINSTANCE hInst);
BOOL InitInstance(HINSTANCE hInst, int nCmdShow);
HFONT MyCreateFont(int nHeight, DWORD dwCharSet, LPCTSTR lpName);

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
	static HFONT hFont1;
	static HFONT hFont2;
	static HFONT hFont3;
	PAINTSTRUCT ps;
	HDC hdc;
	LPCTSTR lpszName1 = TEXT("星野太郎");
	LPCTSTR lpszName2 = TEXT("Hoshino Taro");

	switch (msg) {
	case WM_CREATE:
		hFont1 = MyCreateFont(40, SHIFTJIS_CHARSET, TEXT("HG行書体"));
		hFont2 = MyCreateFont(40, ANSI_CHARSET, TEXT("Fraktur JS"));
		hFont3 = MyCreateFont(40, SHIFTJIS_CHARSET, TEXT("ＭＳ 明朝"));
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps); // デバイスコンテキストを取得
		SelectObject(hdc, hFont1);
		TextOut(hdc, 0, 0, lpszName1, lstrlen(lpszName1));
		SelectObject(hdc, hFont2);
		TextOut(hdc, 0, 60, lpszName2, lstrlen(lpszName2));
		SelectObject(hdc, hFont3);
		TextOut(hdc, 0, 120, lpszName1, lstrlen(lpszName1));
		EndPaint(hWnd, &ps); // 描画処理を終了
		break;

	case WM_DESTROY:
		DeleteObject(hFont1);
		DeleteObject(hFont2);
		DeleteObject(hFont3);
		PostQuitMessage(0);
		break;

	default:
		return (DefWindowProc(hWnd, msg, wp, lp));
	}

	return 0;
}

// 論理フォントを作成し、そのフォントのハンドルを返す
HFONT MyCreateFont(int nHeight, DWORD dwCharSet, LPCTSTR lpName)
{
	return CreateFont(nHeight, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, dwCharSet,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, lpName);
}
