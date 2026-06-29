#include <bootloaders/boot_api.h>

#ifdef LOADER_LIMINE
#include <bootloaders/limine.h>
#endif

void bootloader_init(void) {
	#ifdef LOADER_LIMINE
	limine_initialize();
	#endif
}
