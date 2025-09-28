// Created by JalvinGaming/Chillaxe. All code uses the MIT license.
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <d3d11.h>
#include <d2d1_1.h>
#include <dxgi.h>
#include <CommonStates.h>
#include <DirectXMath.h>

struct KeyboardBitmask {
	unsigned char bytes[32];
};

struct TranslatableString {
	const wchar_t *english, *irish, *japanese;

};

class BBApplication {
	public:
		HWND hwnd;
		MSG msg = {};
		ID3D11Device* dev;
		ID3D11DeviceContext* ctx;
		IDXGIFactory* fac;
		IDXGISwapChain* sc;
		IDXGIDevice* dxdev;
		ID2D1Device* tdev;

		ID3D11RenderTargetView* rtv;
		ID3D11DepthStencilView* dsv;

		DirectX::CommonStates* cs;

		KeyboardBitmask keyboard = {};
		const TranslatableString title = {L"Building Builder", L"Tógálaí Túr", L"建物造り手"};

		bool isKeyPressed(const unsigned char key);
		static LRESULT CALLBACK wndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
		void Run();
};
extern BBApplication* bb;