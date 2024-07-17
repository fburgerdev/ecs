#pragma once

#if defined(BEAVER_LOGGING)
#include "beaver/beaver.hpp"
#else
#define LOG_TRACE(...)
#define LOG_DEBUG(...)
#define LOG_INFO(...)
#define LOG_WARN(...)
#define LOG_ERROR(...)
#define LOG_FATAL(...)
#define ASSERT(...)
#define ASSERT_MSG(...)
#endif