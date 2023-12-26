#pragma once

#if _WIN64
#include <DirectXMath.h>

namespace Pagong::Math
{
	constexpr float pi = 3.141592653589793238462643383279502884197f;
	constexpr float epsilon = 1e-5f;

	using vec2 = DirectX::XMFLOAT2;
	using vec3 = DirectX::XMFLOAT3;
	using vec4 = DirectX::XMFLOAT4;
	using ivec2 = DirectX::XMINT2;
	using ivec3 = DirectX::XMINT3;
	using ivec4  = DirectX::XMINT4;
	using uivec2 = DirectX::XMUINT2;
	using uivec3 = DirectX::XMUINT3;
	using uivec4 = DirectX::XMUINT4;
	using mat3x3 = DirectX::XMFLOAT3X3;
	using mat4x4 = DirectX::XMFLOAT4X4;
}
#endif
