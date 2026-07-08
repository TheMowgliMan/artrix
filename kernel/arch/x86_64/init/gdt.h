#ifndef ARCH_X86_64_INIT_GDT_H_
#define ARCH_X86_64_INIT_GDT_H_

#include <stdint.h>

#define DESC GDT_ENTRY_LENGTH *

typedef struct GDTItem {
	uint32_t base;
	uint32_t limit;

	uint8_t access_byte;
	uint8_t flags;
} gdt_t;

struct __attribute__((packed)) GDTR {
	uint16_t limit;
	uint64_t base;
};

struct __attribute__((packed)) TSS {
	uint32_t reserved0;
    uint64_t rsp0;
    uint64_t rsp1;
    uint64_t rsp2;
    uint64_t reserved1;
    uint64_t ist [7];
    uint64_t reserved2;
    uint16_t reserved3, io_map_base;
};

void enc_gdt_item(void*, gdt_t);
void init_gdt(void);

#endif
