#include <archinit.h>

#include <init/gdt.h>

#include <util/console/log.h>

void early_cpu_setup(void) {
	log_proc("Doing early CPU setup...\r\n");
	
	init_gdt();

	log_success("Early CPU setup complete!\r\n");
}
