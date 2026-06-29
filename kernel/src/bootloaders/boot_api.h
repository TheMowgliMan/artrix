#ifndef BOOTLOADERS_BOOTLOADER_H_
#define BOOTLOADERS_BOOTLOADER_H_

#ifdef LOADER_LIMINE
#include <bootloaders/limine.h>
#else
#error "No defined bootloader to compile for!"
#endif

#include <flanterm_backends/fb.h>

static void bootloader_check_if_valid(void) {
	#ifdef LOADER_LIMINE
	limine_check_if_valid();
	#endif
}

void bootloader_init(void);

struct flanterm_context *bootloader_get_initial_console(void);

#endif
