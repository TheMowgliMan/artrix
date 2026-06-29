#include <bootloaders/boot_api.h>

#include <util/abort.h>

#include <util/console/log.h>

#include <flanterm.h>
#include <flanterm_backends/fb.h>

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void kmain(void) {
	bootloader_check_if_valid();
	bootloader_init();

	struct flanterm_context *ft_ctx = bootloader_get_initial_console();

	init_logging(ft_ctx);

	kprintf("%s, %d %s! \r\n", "Hello", 12, "worlds");
	
    // We're done, just hang...
    assert((1 == 1), "you have somehow escaped the operating system...");
}
