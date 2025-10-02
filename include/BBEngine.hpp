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

struct BBKeyboardBitmask {
	unsigned char bytes[32];
};

struct BBTranslatableString {
	const wchar_t *english, *irish, *japanese;
};

struct BBVertex {
	// Position.
	float x, y, z;
	// Normal.
	float r, h, w;
	// Texture coordinates.
	float  u, v;
};

enum BB_TOPOLOGY_MODE {
	BB_TRIANGLE = 0,
	BB_WIREFRAME = 1
};

struct BBVec3 {
	float x, y, z;
};
struct BBVec2 {
	float x, y;
};
struct BBVec4 {
	float x, y, z, w;
};

class BBShaderProgram {
	public:
		ID3D11VertexShader* vertexShader;
		ID3D11PixelShader* pixelShader;

		BBShaderProgram(const wchar_t* vsCode, const wchar_t* psCode);
};

// Creates a default shader for 2D objects.
BBShaderProgram* BBShaderObject2D();
// Creates a default shader for 3D objects, using Blinn-Phong lighting.
BBShaderProgram* BBShaderObject3D();

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

		BBShaderProgram* currentShader;

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

		BBGraphicsUnit(HWND hwnd);

		~BBGraphicsUnit();

		void Draw();
};

class BBObject2D {
	public:
		ID3D11Buffer* vbo;
		ID3D11Buffer* ebo;
		ID3D11ShaderResourceView* texture;
		ID3D11Buffer* cbo;
		// Position, in meters.
		BBVec2 position;
		// Rotation, in degrees.
		float rotation;
		// Size, in meters.
		BBVec2 size;
		// 255 is reserved for UI elements. If 255 is specified, then the object will appear regardless of the floor you're on, and track the camera. If 254 is specified, then the object will appear no matter what floor you are on, and will not track the camera.
		uint8_t floor;
		BBObject2D(const wchar_t* textureFileName, const BBVec2 size, const BBVec2 position, const float rotation, const uint8_t floor);
		void Draw();
};

class BBObject3D {
	public:
		ID3D11Buffer* vbo;
		ID3D11Buffer* ebo;
		ID3D11ShaderResourceView* texture;
		ID3D11Buffer* cbo;
		// Position, in meters.
		BBVec3 position;
		// Rotation, in degrees, according to Euler format.
		BBVec3 rotation;
		// 255 is reserved for UI elements. If 254 is specified, then the object is duplicated across all floors.
		uint8_t floor;
		BBObject3D(const wchar_t* textureFileName, const BBVertex* vertices, const uint32_t numVertices, const uint32_t* indices, const uint32_t numIndices, const BBVec3 size, const BBVec3 position, const BBVec3 rotation, const uint8_t floor);
		void Draw();
};

class BBApplication {
	public:
		HWND hwnd;
		MSG msg = {};

		BBKeyboardBitmask keyboard = {};
		const BBTranslatableString title = {L"Building Builder", L"Tógálaí Túr", L"建物造り手"};

		BBGraphicsUnit* gpu;

		bool isKeyPressed(const unsigned char key);
		static LRESULT CALLBACK wndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
		void Run();
};

extern BBApplication* bb;