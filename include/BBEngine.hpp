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
#include <stdint.h>

struct KeyboardBitmask {
	unsigned char bytes[32];
};

struct TranslatableString {
	const wchar_t *english, *irish, *japanese;

};

enum BB_TOPOLOGY_MODE {
	BB_TRIANGLE = 0,
	BB_WIREFRAME = 1
};

class BBGraphicsUnit {
	public:
		ID3D11Device* device;
		ID3D11DeviceContext* context;
		IDXGIFactory* dxgiFactory;
		IDXGISwapChain* swapChain;
		IDXGIDevice* dxgiDevice;
		ID2D1Device* d2dDevice;

		ID3D11RenderTargetView* renderTarget;
		ID3D11DepthStencilView* depthStencil;

		DirectX::CommonStates* commonStates;

		ID3D11VertexShader* currentVS;
		ID3D11PixelShader* currentPS;

		ID3D11Buffer* currentVBO;
		uint8_t sizeVertex;
		uint32_t numVertices;
		BB_TOPOLOGY_MODE topology;

		ID3D11Buffer* currentEBO;
		uint32_t numIndices;

		ID3D11Buffer** currentCBOs;
		uint8_t numCBOs;

		ID3D11ShaderResourceView** currentSRVs;
		uint8_t numSRVs;

		void Draw();
};

class BBApplication {
	public:
		HWND hwnd;
		MSG msg = {};

		KeyboardBitmask keyboard = {};
		const TranslatableString title = {L"Building Builder", L"Tógálaí Túr", L"建物造り手"};

		BBGraphicsUnit* gpu;

		bool isKeyPressed(const unsigned char key);
		static LRESULT CALLBACK wndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
		void Run();
};
extern BBApplication* bb;