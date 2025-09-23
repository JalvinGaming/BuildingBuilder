main:
	cl source/**.cpp d3d11.lib dxgi.lib directxtk.lib /EHsc /I"lib/DirectXTK-main/Inc" /I"include" /std:c++17 /link /libpath:"lib" /out:"build/BuildingBuilder.exe"
	del main.obj