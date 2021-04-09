// Set the code to 32 bit
.code32

// The following definitions are of page tables
// The page table defines the mappings from a virtual address to a physical address
// Every time there's a memory access, the CPU checks the tables and finds out where the real destination should be
.section .bss
.align 4096
page_table_l4:
    .skip 4096
page_table_l3:
    .skip 4096
page_table_l2:
    .skip 4096

// Move to the text section with our code
.section .text

// Make the setup and enable paging functions globally available
.global setup_paging
.global enable_paging

setup_paging:
    mov $page_table_l3, %eax   // Take the address of the level 3 page table and move it into the EAX register
                               // The first 12 bits of every entry is always going to be 0 (log2 4096 = 12)
    or $0b11, %eax             // Enable the present and writable flags
    mov %eax, (page_table_l4)  // Take the address in EAX (which has some added flags) and put it as the first entry in our l4 table

    // Repeat the prior code for a different table.
    mov $page_table_l2, %eax
    or $0b11, %eax
    mov %eax, (page_table_l3)

    // Allocate 1gb in the l2 page table
    mov $0, %ecx  // Set the counter value to 0

.loop:
    // Map a 2mb page
    mov $0x200000, %eax                    // store the value of 2MiB in the eax register
    mul %ecx                              // get the correct address
    or $0b10000011, %eax                   // enable the "huge page" flag
    mov %eax, page_table_l2(,%ecx,8)   // put this entry in the l2 table, with the offset of the index of the entry

    inc %ecx                              // increment this counter
    cmp $512, %ecx                         // check if the whole table has been mapped
    jne .loop                            // if not, continue looping
    ret

enable_paging:
    // Pass the page table location to the cpu
    mov $page_table_l4, %eax  // pass the page table location to EAX
    mov %eax, %cr3            // copy this value into the CR3 register

    // Enable the physical address extension
    mov %cr4, %eax           // Copy the CR4 register to EAX
    or $(1 << 5), %eax       // Enable the 5th bit which is the PAE flag
    mov %eax, %cr4           // Enable the PAE flag in the CR4 register

    // Enable long mode
    mov $0xC0000080, %ecx    // Put the magic value in to the ECX register
    rdmsr                    // Read model specific register, this will load the value of the EFER register into EAX
    or $(1 << 8), %eax       // Enable long mode flag
    wrmsr                    // Write EAX back into the EFER register

    // Enable paging
    mov %cr0, %eax            // Copy the CR0 register to EAX
    or $(1 << 31), %eax       // Enable the 'paging bit'
    mov %eax, %cr0            // Write eax to CR0
    ret