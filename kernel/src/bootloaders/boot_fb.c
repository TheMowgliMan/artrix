#include <bootloaders/boot_api.h>

#ifdef LOADER_LIMINE
#include <limine.h>
#include <bootloaders/limine.h>
#endif

#include <flanterm_backends/fb.h>

struct flanterm_context *bootloader_get_initial_console(void) {
	#ifdef LOADER_LIMINE
	struct flanterm_context *ft_ctx = flanterm_fb_init(
													   NULL, NULL,
													   limine_fb->address, limine_fb->width,
													   limine_fb->height, limine_fb->pitch,
													   limine_fb->red_mask_size, limine_fb->red_mask_shift,
													   limine_fb->green_mask_size, limine_fb->green_mask_shift,
													   limine_fb->blue_mask_size, limine_fb->blue_mask_shift,
													   NULL,
													   NULL, NULL,
													   NULL, NULL,
													   NULL, NULL,
													   NULL, 0, 0, 1,
													   0, 0,
													   0,
													   0
													   );
		
	#else
	#warning "Initial console is not supported for bootloaders other than Limine!"
	return NULL;
	#endif

	return ft_ctx;
}
