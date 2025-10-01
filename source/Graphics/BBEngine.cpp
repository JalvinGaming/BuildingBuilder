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
	gpu = new BBGraphicsUnit();
	WNDCLASSEXW wc = {};
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.lpszClassName = L"BuildingBuilderWC";
	wc.lpfnWndProc = wndProc;
	wc.hInstance = GetModuleHandleW(NULL);
	RegisterClassExW(&wc);
	RECT wr = {0, 0, 1280, 720};
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, false);
	hwnd = CreateWindowExW(0, L"BuildingBuilderWC", title.english, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, wr.bottom - wr.top, wr.right - wr.left, NULL, NULL, GetModuleHandleW(NULL), NULL);
	ShowWindow(hwnd, 1);

	const D3D_FEATURE_LEVEL d3dlevels[] = {D3D_FEATURE_LEVEL_11_0};
	D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG, d3dlevels, 1, D3D11_SDK_VERSION, &gpu->device, NULL, &gpu->context);
	
	CreateDXGIFactory(IID_PPV_ARGS(&gpu->dxgiFactory));
	gpu->device->QueryInterface(IID_PPV_ARGS(&gpu->dxgiDevice));
	D2D1_CREATION_PROPERTIES d2dprops = {};
	d2dprops.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
	D2D1CreateDevice(gpu->dxgiDevice, &d2dprops, &gpu->d2dDevice);

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

	gpu->dxgiFactory->CreateSwapChain(gpu->device, &scd, &gpu->swapChain);

	ID3D11Texture2D* bbt;
	gpu->swapChain->GetBuffer(0, IID_PPV_ARGS(&bbt));
	gpu->device->CreateRenderTargetView(bbt, NULL, &gpu->renderTarget);
	bbt->Release();
	D3D11_TEXTURE2D_DESC dstd = {};
	dstd.ArraySize = 1;
	dstd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	dstd.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	dstd.Format = DXGI_FORMAT_D16_UNORM;
	dstd.Width = 1280;
	dstd.Height = 720;
	dstd.Usage = D3D11_USAGE_DYNAMIC;
	dstd.MipLevels = 1;
	dstd.SampleDesc.Count = 1;

	ID3D11Texture2D* dst;
	gpu->device->CreateTexture2D(&dstd, NULL, &dst);
	gpu->device->CreateDepthStencilView(dst, NULL, &gpu->depthStencil);
	dst->Release();

	gpu->commonStates = new DirectX::CommonStates(gpu->device);

	gpu->context->OMSetRenderTargets(1, &gpu->renderTarget, gpu->depthStencil);
	gpu->context->RSSetState(gpu->commonStates->CullNone());
	gpu->context->OMSetDepthStencilState(gpu->commonStates->DepthDefault(), 0);
	D3D11_VIEWPORT vp = {0, 0, 1280, 720, 0, 1};
	gpu->context->RSSetViewports(1, &vp);

	while (msg.message != WM_QUIT) {
		while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}
	DestroyWindow(hwnd);
	UnregisterClassW(L"BuildingBuilderWC", GetModuleHandleW(NULL));
}