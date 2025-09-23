// Created by JalvinGaming/Chillaxe. All code uses the MIT license.

#include <d3d11.h>
#include <dxgi.h>
#include <CommonStates.h>


class BBApplication {
	private:
		HWND hwnd;
		ID3D11Device* dev;
		ID3D11DeviceContext* ctx;
		IDXGISwapChain* sc;

		ID3D11RenderTargetView* rtv;
		ID3D11DepthStencilView* dsv;
	public:


};