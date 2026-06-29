#include <util/console/log.h>

#include <util/console/nanoprintf.h>
#include <util/console/ft.h>

#include <flanterm.h>

struct flanterm_context *kernel_log_ctx;

void init_logging(struct flanterm_context *ctx) {
	kernel_log_ctx = ctx;
}
