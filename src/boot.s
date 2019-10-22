.section ".text.boot"

.global _start

_start:
    @ bl blink_led

	// put all cores except 0 in a holding pen
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
    b       temp2


temp1:
    stmia r4!, {r5-r8}

temp2:
    cmp r4, r9
    blo temp1

    @ ldr r3, =kernel_main
    bl  kernel_main


// halt holding pen
halt:
    wfe
    b halt



//==================================================

// cmall routine to blink LED for early boot debug... this is poorly written doesn't preserve registers
blink_led:
	// turn on LED
    ldr r0,=0x20200000 
    mov r1,#1
    lsl r1,#18  //set GPIO16 as output
    str r1,[r0,#4]
    mov r1,#1
    lsl r1,#16
    str r1,[r0,#40] //set bit 16 of GPIO clear reg

    mov r6, #10
    mov r3, #1  
    mov r4, #0

blink_loop:

    //wait
    mov r2, #1
    lsl r2, #20
wait1:
    sub r2, r2, #1
    cmp r2, r4
    bne     wait1

    //turn LED off
    mov r1,#1
    lsl r1,#16
    str r1,[r0,#28] //set bit 16 of GPIO set reg
 
 
    //wait
    mov r2, #1
    lsl r2, #20
wait2:
    sub r2, r2, #1
    cmp r2, r4
    bne     wait2

    //sub 1 from num blinks counter, if not 0, start blink loop again
    sub r6, r6, #1
    cmp r6, r4
    bne blink_loop


   //wait a little longer, then turn LED back on
    mov r2, #1
    lsl r2, #23
wait3:
    sub r2, r2, #1
    cmp r2, r4
    bne     wait3

    // turn LED back on before continuing
    mov r1,#1
    lsl r1,#16
    str r1,[r0,#40] //set bit 16 of GPIO clear reg

    mov pc, lr
    
