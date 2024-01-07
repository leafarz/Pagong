#pragma once

#ifdef _WIN64
	#define _WIN32_LEAN_AND_MEAN
	#define NOMINMAX
	#include <Windows.h>
	#undef CreateWindow

	#include <d3d12.h>
	#include <dxgi1_6.h>
	#include "d3dx12.h"
	#include <D3Dcompiler.h>
	using Microsoft::WRL::ComPtr;

	#ifdef _DEBUG
		#include <d3d12sdklayers.h>
		#include <dxgidebug.h>
	#endif

	#pragma comment(lib, "dxgi.lib")
	#pragma comment(lib, "dxguid.lib")
	#pragma comment(lib, "d3d12.lib")
	#pragma comment(lib, "d3dcompiler.lib")
#endif


#include <memory>
#include <string>

#include "Pagong/Core/Core.h"
