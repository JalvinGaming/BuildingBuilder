#include <BBEngine.hpp>
#include <math.h>

LRESULT CALLBACK BBApplication::wndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
	switch(umsg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_KEYDOWN:
			bb->keyboard.bytes[(unsigned char)floor(wparam / 8)] |= 1 << (wparam % 8);
			break;
		case WM_KEYUP:
			bb->keyboard.bytes[(unsigned char)floor(wparam / 8)] &= 0xff - (1 << (wparam % 8));
			break;
	}
	return DefWindowProcW(hwnd, umsg, wparam, lparam);
}

bool BBApplication::isKeyPressed(const unsigned char key) {
	return bb->keyboard.bytes[(unsigned char)floor(key / 8)] & 1 << (key % 8) != 0;
}

void BBApplication::Run() {
	WNDCLASSEXW wc = {};
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.lpszClassName = L"BuildingBuilderWC";
	wc.lpfnWndProc = wndProc;
	wc.hInstance = GetModuleHandleW(NULL);
	RegisterClassExW(&wc);
	hwnd = CreateWindowExW(0, L"BuildingBuilderWC", title.english, WS_OVERLAPPEDWINDOW | WS_MAXIMIZE, CW_USEDEFAULT, 0, 1280, 720, NULL, NULL, GetModuleHandleW(NULL), NULL);
	ShowWindow(hwnd, 1);

	while (msg.message != WM_QUIT) {
		while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}
	DestroyWindow(hwnd);
	UnregisterClassW(L"BuildingBuilderWC", GetModuleHandleW(NULL));
}