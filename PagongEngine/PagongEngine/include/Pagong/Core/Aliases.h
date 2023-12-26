#pragma once
#include <map>
#include <memory>
#include <vector>
#include <type_traits>

namespace Pagong
{
#pragma region vector
	template<typename T>
	using TArray = std::vector<T>;

	template<typename T>
	using TUnique = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr TUnique<T> MakeUnique(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
#pragma endregion vector

#pragma region shared_pointer
	template<typename T>
	using TShared = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr TShared<T> MakeShared(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
#pragma endregion shared_pointer

	template<typename T, typename U>
	using TMap = std::map<T,U>;
}
