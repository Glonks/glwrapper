#pragma once

#include <glwrapper/base/Log.h>

#include <cassert>

#define GLW_ASSERT(x, ...) { if(!(x)) { GLW_ERROR(__VA_ARGS__); assert(x); } }
#define GLW_CORE_ASSERT(x, ...) { if(!(x)) { GLW_CORE_ERROR(__VA_ARGS__); assert(x); } }