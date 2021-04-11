// When this runs, code should be running in 32bit
.code32

.global check_cpuid
.global check_long_mode

/* To detect whether CPUID is a supported instruction, you can check if the ID bit in the
   flags register can be flipped */
check_cpuid:
    pushfd            // Push the flags register onto the stack
    pop %eax          // Pop the flags register off the stack onto EAX
    mov %eax, %ecx    // Copy the EAX register to the ECX register for later
    xor %eax, 1 << 21 // Flip the ID bit of the CPU flags
    push %eax         // Push the resulting EAX register with the flipped ID to the EAX register
    popfd             // Set the flags register to what was in EAX

    pushfd            // Read the FLAGS register (with a flipped bit if CPUID is supported)
    pop %eax          // Copy the FLAGS register to EAX
    push %ecx         // Restore the FLAGS from the older version in ECX
    popfd

    cmp %eax, %ecx   // Compare the EAX and ECX register.
    je .no_cpuid     // If they are not equal, the bit wasn't flipped and CPUID isn't supported
    ret              // Return out of our function

// Define the boundaries of the function
.size check_cpuid, . - check_cpuid

check_long_mode:
    mov 0x80000000, %eax  // Store "0x80000000" in the EAX register
    cpuid                // Get the result of CPUID since we know it can be run now
    cmp %eax, 0x80000001  // Compare what is in the A register with the CPUID result
    jb .no_long_mode     // If the CPUID result is less than 0x80000001, long mode is unsupported.

    mov 0x80000001, %eax // Store "0x80000000" in the EAX register
    cpuid                // Now use the CPUID result again
    test %edx, 1 << 29    // Test if the long mode bit, bit 29, is set in the D register
    jz .no_long_mode     // If the long mode bit is not set, it is unsupported
    ret

// Define the boundaries of the function
.size check_long_mode, . - check_long_mode

.no_cpuid:
    ret

.size no_cpuid, . - no_cpuid

.no_long_mode:
    ret

.size no_long_mode, . - no_long_mode