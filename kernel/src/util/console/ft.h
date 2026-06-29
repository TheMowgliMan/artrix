#ifndef UTIL_CONSOLE_FT_
#define UTIL_CONSOLE_FT_

#include <flanterm.h>

#include <stddef.h>

static void safe_flanterm_write(struct flanterm_context *ctx, const char *buf, size_t count) {
	if (ctx != NULL) {
		flanterm_write(ctx, buf, count);
	}
}

static void ft_putc(int c, void *ctx) {
	struct flanterm_context *ft_ctx = (struct flanterm_context *)ctx;
	char cc = (char)c;
	safe_flanterm_write(ft_ctx, &cc, sizeof(char));
}

#endif
