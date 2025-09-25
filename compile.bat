cl /EHs /I"lib/DirectXTK-main/Inc" /I"include" /std:c++17 source/*.cpp source/Graphics/*.cpp /link /libpath:"lib" d3d11.lib dxgi.lib directxtk.lib user32.lib /out:"build/BuildingBuilder.exe"
del *.obj