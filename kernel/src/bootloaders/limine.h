#ifndef BOOTLOADERS_LIMINE_H_
#define BOOTLOADERS_LIMINE_H_

#include <limine.h>

extern struct limine_framebuffer_response *limine_fb_response;

extern struct limine_framebuffer *limine_fb;

void limine_check_if_valid(void);
void limine_initialize(void);

#endif
