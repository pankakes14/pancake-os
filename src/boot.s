.section ".text.boot"

.global _start

_start:

	// turn on LED
    ldr r0,=0x20200000 
    mov r1,#1
    lsl r1,#18  //set GPIO16 as output
    str r1,[r0,#4]
    mov r1,#1
    lsl r1,#16
    str r1,[r0,#40] //set bit 16 of GPIO clear reg
 
	@ // put all cores except 0 in a holding pen
    @ mrc p15, #0, r1, c0, c0, #5
    @ and r1, r1, #3
    @ cmp r1, #0
    @ bne halt
   
    // set stack pointer to 0x8000 since entry address is 0x8000, we can safely grow down from here in sram
    mov sp, #0x8000

    // clear bss section?
    ldr r4, =__bss_start
    ldr r9, =__bss_end
    mov r5, #0
    mov r6, #0
    mov r7, #0
    mov r8, #0
    b       2

1:
    stmia r4!, {r5-r8}

2:
    cmp r4, r9
    blo 1

    ldr r3, =kernel_main
    blx r3

halt:
    wfe
    b halt

