#ifndef UTIL_CONSOLE_NANOPRINTF_H_
#define UTIL_CONSOLE_NANOPRINTF_H_

#include <util/abort.h>

#include <util/console/ft.h>

#define NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS 0
#define NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_SMALL_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_WRITEBACK_FORMAT_SPECIFIERS 0
#define NANOPRINTF_VISIBILITY_STATIC

#define NANOPRINTF_IMPLEMENTATION

#include <nanoprintf.h>

#define COLOR_RESET "\033[0m"
#define COL_ "\033[0;"
#define BLACK COL_ "30m"
#define RED COL_ "31m"
#define YELLOW COL_ "33m"

#define GL_INT_2(x) #x
#define GL_INT_1(x) GL_INT_2(x)
#define GET_LINE GL_INT_1(__LINE__)

#define PASS_ARGS(...) __VA_ARGS__
#define assert(cond, fmt, ...) \
	if (cond) { \
		kprintf("[" RED " FAIL " COLOR_RESET "] In %s, line %s:\r\n\tassertion failed: " fmt, __FILE__, GET_LINE __VA_OPT__(,) PASS_ARGS(__VA_ARGS__)); \
		abort_hcf(); \
	}
#define warn_if(cond, fmt, ...) \
	if (cond) \
		kprintf("[" YELLOW " WARN " COLOR_RESET "] Warning: " fmt __VA_OPT__(,) PASS_ARGS(__VA_ARGS__))

#define kprintf(...) npf_pprintf(&ft_putc, kernel_log_ctx, __VA_ARGS__) // My first ever macro-as-function lol

#endif
