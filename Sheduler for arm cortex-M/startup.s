.syntax unified
.cpu cortex-m3
.thumb

.global _start
.global Reset_Handler

.section .vectors, "a"
vector_table:
    .word _stack_top          /* initial stack pointer */
    .word Reset_Handler       /* reset handler */
    .word 0                   /* NMI */
    .word HardFault_Handler   /* hard fault */
    .word 0,0,0,0,0,0,0       /* reserved */
    .word SVC_Handler         /* SVC */
    .word 0,0                 /* reserved */
    .word PendSV_Handler      /* PendSV — your context switch lives here */
    .word SysTick_Handler     /* SysTick — your scheduler tick */
 
.section .text

.type Reset_Handler, %function
Reset_Handler:
    ldr sp, =_stack_top
    bl  main
    b   .

.type HardFault_Handler, %function
HardFault_Handler:
    b .

.weak SVC_Handler
.type SVC_Handler, %function
SVC_Handler:
    b .

.weak PendSV_Handler
.type PendSV_Handler, %function
PendSV_Handler:
    b .

.weak SysTick_Handler
.type SysTick_Handler, %function
SysTick_Handler:
    bx lr
