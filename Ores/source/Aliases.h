#pragma once
#include <memory>

using uint = unsigned int;

template<typename T>
using uPtr = std::unique_ptr<T>;