// Created by JalvinGaming/Chillaxe. All code uses the MIT license.
#include <BBEngine.hpp>
#include <math.h>
#include <stdio.h>

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
	wc.hCursor = LoadCursorW(GetModuleHandleW(NULL), MAKEINTRESOURCE(IDC_ARROW));
	RegisterClassExW(&wc);
	RECT wr = {0, 0, 1280, 720};
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, false);
	hwnd = CreateWindowExW(0, L"BuildingBuilderWC", title.english, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, wr.right - wr.left, wr.bottom - wr.top, NULL, NULL, GetModuleHandleW(NULL), NULL);
	ShowWindow(hwnd, 1);

	gpu = new BBGraphicsUnit(hwnd);

	while (msg.message != WM_QUIT) {
		while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}
	delete gpu;
	DestroyWindow(hwnd);
	UnregisterClassW(L"BuildingBuilderWC", GetModuleHandleW(NULL));
}