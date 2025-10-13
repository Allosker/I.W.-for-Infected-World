#pragma once // Memory.h

// ===========================
// Author: Allosker
// --
// File Name: memory.h
// --
// Description: This header includes every container of the STL needed for the classes of the game. 
// Note: it also defines type alliases to reduce wirting-time.
// ===========================


// Include
// ---------------------------------------------------------------------------------------


#include <memory>

#include <optional>

#include <utility>

#include <vector>

#include <map>

#include <array>

#include <string>

#include <string_view>



// Type Alliases
// ---------------------------------------------------------------------------------------


using String = std::string;
using StringView = std::string_view;

template<typename T>
using Optional = std::optional<T>;

template<typename T, typename U>
using Pair = std::pair<T, U>;

template<typename T, typename U>
using Omap = std::map<T, U>;

template<typename T>
using Vector = std::vector<T>;

template<typename T, size_t e>
using Array = std::array<T, e>;

template<typename T>
using Uptr = std::unique_ptr<T>;

template<typename T>
using Shared_ptr = std::shared_ptr<T>;

template<typename T>
using VecPtr = std::vector<std::unique_ptr<T>>;

template<typename T>
using VecSharedPtr = std::vector<std::shared_ptr<T>>;

template<typename T>
using VecWeakPtr = std::vector<std::weak_ptr<T>>;


using u_int = unsigned int;