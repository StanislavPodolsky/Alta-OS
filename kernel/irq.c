#include <arch/idt.h>
#include <arch/irq.h>

#include <sys/types.h>
#include <sys/stdlib.h>

IRQ_HANDLER(__irq_timer) {
printf("+");
}

IRQ_HANDLER(__irq_keyboard) {
	irq_process_keyboard();
}

void irq_pic_init() {
    outportb(0x20, 0x11);       /* init command */
    outportb(0x21, 0x20);       /* base */
    outportb(0x21, 4);          /* slave PIC is at IRQ2 ( 00000100 ) */
    outportb(0x21, 1);          /* cascade identity (?) */
    outportb(0xA0, 0x11);       /* init command */
    outportb(0xA1, 0x20 + 8);   /* slave's base */
    outportb(0xA1, 2);          /* slave's PIC bridge is at IRQ1 (00000010 ) */
    outportb(0xA1, 1);          /* cascade identity (?) */

/* system timer configuring */

    outportb(0x43, 0x34);
    outportb(0x40, 0x9C);
    outportb(0x40, 0x2E);
}
