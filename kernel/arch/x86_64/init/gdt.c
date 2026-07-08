#include <init/gdt.h>

#include <util/console/log.h>

#include <memory.h>
#include <types.h>

#include <stdint.h>

const uint8_t GDT_ENTRIES = 7;
const uint8_t GDT_ENTRY_LENGTH = 8;
const uint8_t GDT_TOTAL_LENGTH = 56;

static arch_byte_t GDT[56];
struct TSS tss;

static struct GDTR gdtr;

uint8_t __attribute__((aligned(64))) df_stack[8192];
uint8_t __attribute__((aligned(64))) nmi_stack[8192];
uint8_t __attribute__((aligned(64))) miscxc_stack[8192];

extern void set_gdt(struct GDTR *gdtr);
extern void reload_sgmt(void);
extern void load_tss(uint16_t smth);

static gdt_t gen_gdt_item(uint32_t base, uint32_t limit, uint8_t access_byte, uint8_t flags) {
	gdt_t ret;
	ret.base = base;
	ret.limit = limit;
	ret.access_byte = access_byte;
	ret.flags = flags;
	return ret;
}

void enc_gdt_item(void *target, gdt_t source) {
	assert((source.limit > 0xFFFFF), "GDT limit greater than 0xFFFFF!\r\n");

	uint8_t *t = (uint8_t *)target;

	// Limit
	t[0] = source.limit & 0xFF;
	t[1] = (source.limit >> 8) & 0xFF;
	t[6] = (source.limit >> 16) & 0x0F;

	// Base
	t[2] = source.base & 0xFF;
	t[3] = (source.base >> 8) & 0xFF;
	t[4] = (source.base >> 16) & 0xFF;
	t[7] = (source.base >> 24) & 0xFF;

	// Access byte
	t[5] = source.access_byte;

	// Flags
	t[6] |= (source.flags << 4) & 0xF0;
}

void enc_tss(void *target) {
	uint8_t *t = (uint8_t *)target;

	arch_ptr_t tss_addr = (arch_ptr_t)(&tss);
	uint32_t shft_addr = tss_addr >> 32;

	enc_gdt_item(t, gen_gdt_item(tss_addr & 0xFFFFFFFF, sizeof(tss) - 1, 0x89, 0));

	memcpy(&t[8], &shft_addr, sizeof(uint32_t));
}

void init_gdt(void) {
	log_proc("GDT Init...");

	gdt_t nulld = gen_gdt_item(0, 0, 0x00, 0x0);
	enc_gdt_item(&GDT[DESC 0], nulld);

	gdt_t kerncsd = gen_gdt_item(0, 0xFFFFF, 0x9B, 0xA);
	enc_gdt_item(&GDT[DESC 1], kerncsd);

	gdt_t kerndsd = gen_gdt_item(0, 0xFFFFF, 0x93, 0xC);
	enc_gdt_item(&GDT[DESC 2], kerndsd);

	gdt_t usercsd = gen_gdt_item(0, 0xFFFFF, 0xFB, 0xA);
	enc_gdt_item(&GDT[DESC 3], usercsd);

	gdt_t userdsd = gen_gdt_item(0, 0xFFFFF, 0xF3, 0xC);
	enc_gdt_item(&GDT[DESC 4], userdsd);

	tss.ist[0] = (uint64_t)(df_stack + sizeof(df_stack));
	tss.ist[1] = (uint64_t)(miscxc_stack + sizeof(miscxc_stack));
	tss.ist[2] = (uint64_t)(nmi_stack + sizeof(nmi_stack));
  
	enc_tss(&GDT[DESC 5]);
  
	gdtr.limit = (sizeof(uint8_t) * GDT_TOTAL_LENGTH) - 1;
	gdtr.base = (uint64_t)&GDT;

	set_gdt(&gdtr);
	reload_sgmt();
	load_tss(DESC 5);

	kprintf(" [ " GREEN "OK" COLOR_RESET " ]\r\n");
}
