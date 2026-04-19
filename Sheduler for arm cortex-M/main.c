#include <stdint.h>
#define SYSTICK_CTRL  (*(volatile uint32_t*)0xE000E010)
#define SYSTICK_LOAD  (*(volatile uint32_t*)0xE000E014)
#define SYSTICK_VAL   (*(volatile uint32_t*)0xE000E018)

void systick_init(void) {
    SYSTICK_LOAD = 12000 - 1;   // ~1ms for 12 MHz (QEMU lm3s811evb)
    SYSTICK_VAL  = 0;
    SYSTICK_CTRL = 7;           // ENABLE | TICKINT | CLKSOURCE
}

static inline void semi_write0(const char *s) {
    /* semihosting call — QEMU intercepts this and prints to terminal */
    __asm volatile (
        "mov r0, #4      \n"   /* SYS_WRITE0 operation */
        "mov r1, %0      \n"   /* pointer to string */
        "bkpt 0xAB       \n"   /* semihosting breakpoint */
        :
        : "r" (s)
        : "r0", "r1"
    );
}

int main(void) {
    systick_init(); 
    semi_write0("Hello from bare-metal Cortex-M!\n");
    semi_write0("Toolchain works. Ready to build scheduler.\n");
    while(1);
}
