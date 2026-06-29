#ifndef UTIL_CONSOLE_LOG_H_
#define UTIL_CONSOLE_LOG_H_

#include <util/console/nanoprintf.h>
#include <util/console/ft.h>

extern struct flanterm_context *kernel_log_ctx;

void init_logging(struct flanterm_context*);

#endif
