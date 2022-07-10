#ifndef __HAVE_INTERRUPTS_H
#define __HAVE_INTERRUPTS_H

void install_idt(void);
void enable_interrupts(void);
void disable_interrupts(void);

#endif
