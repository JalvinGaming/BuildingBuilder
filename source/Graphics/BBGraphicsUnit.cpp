// Created by JalvinGaming/Chillaxe. All code uses the MIT license.
#include <BBEngine.hpp>
BBGraphicsUnit::BBGraphicsUnit(HWND hwnd) {
	const D3D_FEATURE_LEVEL d3dlevels[] = {D3D_FEATURE_LEVEL_11_0};
	D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG, d3dlevels, 1, D3D11_SDK_VERSION, &device, NULL, &context);
	
	CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
	device->QueryInterface(IID_PPV_ARGS(&dxgiDevice));
	D2D1_CREATION_PROPERTIES d2dprops = {};
	d2dprops.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
	D2D1CreateDevice(dxgiDevice, &d2dprops, &d2dDevice);

	DXGI_SWAP_CHAIN_DESC scd = {};
	scd.BufferCount = 1;
	scd.BufferDesc.Width = 1280;
	scd.BufferDesc.Height = 720;
	scd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hwnd;
	scd.SampleDesc.Count = 1;
	scd.Windowed = true;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	dxgiFactory->CreateSwapChain(device, &scd, &swapChain);

	ID3D11Texture2D* bbt;
	swapChain->GetBuffer(0, IID_PPV_ARGS(&bbt));
	device->CreateRenderTargetView(bbt, NULL, &renderTarget);
	bbt->Release();
	D3D11_TEXTURE2D_DESC dstd = {};
	dstd.ArraySize = 1;
	dstd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	dstd.Format = DXGI_FORMAT_D32_FLOAT;
	dstd.Width = 1280;
	dstd.Height = 720;
	dstd.MipLevels = 1;
	dstd.SampleDesc.Count = 1;

	ID3D11Texture2D* dst;
	device->CreateTexture2D(&dstd, NULL, &dst);
	device->CreateDepthStencilView(dst, NULL, &depthStencil);
	dst->Release();

	commonStates = new DirectX::CommonStates(device);

	context->OMSetRenderTargets(1, &renderTarget, depthStencil);
	context->RSSetState(commonStates->CullNone());
	context->OMSetDepthStencilState(commonStates->DepthDefault(), 0);
	D3D11_VIEWPORT vp = {0, 0, 1280, 720, 0, 1};
	context->RSSetViewports(1, &vp);
}

BBGraphicsUnit::~BBGraphicsUnit() {
	delete commonStates;
	depthStencil->Release();
	renderTarget->Release();
	d2dDevice->Release();
	dxgiDevice->Release();
	swapChain->Release();
	dxgiFactory->Release();
	context->Release();
	device->Release();
}