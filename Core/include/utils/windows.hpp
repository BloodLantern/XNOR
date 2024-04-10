#pragma once

/// @file windows.hpp
/// @brief A way to include the @c <Windows.h> header without some of its problematic macros.

#undef APIENTRY
// ReSharper disable once CppInconsistentNaming
#define XMLDocument XMLDocument_dont_care
#include <Windows.h>
#undef XMLDocument

#undef min
#undef max
#undef MessageBox