#ifdef LOADER_LIMINE
#include <limine.h>

#include <util/abort.h>

#include <stddef.h>
#include <stdbool.h>

// Set the base revision to 6, this is recommended as this is the latest
// base revision described by the Limine boot protocol specification.
// See specification for further info.

__attribute__((used, section(".limine_requests")))
static volatile uint64_t limine_base_revision[] = LIMINE_BASE_REVISION(6);

// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent, _and_ they should be accessed at least
// once or marked as used with the "used" attribute as done here.

__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0
};

// Finally, define the start and end markers for the Limine requests.
// These can also be moved anywhere, to any .c file, as seen fit.

__attribute__((used, section(".limine_requests_start")))
static volatile uint64_t limine_requests_start_marker[] = LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile uint64_t limine_requests_end_marker[] = LIMINE_REQUESTS_END_MARKER;

struct limine_framebuffer_response *limine_fb_response;
struct limine_framebuffer *limine_fb;

void limine_check_if_valid(void) {
	// Ensure the bootloader actually understands our base revision (see spec).
    if (LIMINE_BASE_REVISION_SUPPORTED(limine_base_revision) == false) {
        abort_hcf();
    }
}

void limine_initialize(void) {
	/* Set the responses from the used bootloader API */
	limine_fb_response = framebuffer_request.response;
	
	// Ensure we got a framebuffer.
	limine_fb = NULL;
    if (limine_fb_response == NULL || limine_fb_response->framebuffer_count < 1) {
        ; // TODO: mark headless mode
    } else {
		limine_fb = limine_fb_response->framebuffers[0];
	}
}

#endif
