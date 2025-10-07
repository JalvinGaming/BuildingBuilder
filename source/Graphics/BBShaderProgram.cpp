#include <BBEngine.hpp>
#include <d3dcompiler.h>

BBShaderProgram::BBShaderProgram(const wchar_t* vsCode, const wchar_t* psCode) {
	ID3DBlob* vsBlob;
	ID3DBlob* vsDebugBlob;
	char* vsCodeBuffer = (char*)malloc(wcslen(vsCode) * sizeof(char) + sizeof(char));
	WideCharToMultiByte(CP_ACP, WC_ERR_INVALID_CHARS, vsCode, -1, vsCodeBuffer, wcslen(vsCode) * sizeof(char) + sizeof(char), NULL, NULL);
	D3DCompile(vsCodeBuffer, strlen(vsCodeBuffer), NULL, NULL, NULL, "main", "vs_5_0", D3DCOMPILE_DEBUG, NULL, &vsBlob, &vsDebugBlob);
	free(vsCodeBuffer);
	bb->gpu->device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), NULL, &vertexShader);
	vsBlob->Release();
	vsDebugBlob->Release();

	ID3DBlob* psBlob;
	ID3DBlob* psDebugBlob;
	char* psCodeBuffer = (char*)malloc(wcslen(psCode) * sizeof(char) + sizeof(char));
	WideCharToMultiByte(CP_ACP, WC_ERR_INVALID_CHARS, psCode, -1, psCodeBuffer, wcslen(psCode) * sizeof(char) + sizeof(char), NULL, NULL);
	D3DCompile(psCodeBuffer, strlen(psCodeBuffer), NULL, NULL, NULL, "main", "ps_5_0", D3DCOMPILE_DEBUG, NULL, &psBlob, &psDebugBlob);
	free(psCodeBuffer);
	bb->gpu->device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), NULL, &pixelShader);
	psBlob->Release();
	psDebugBlob->Release();
	
}