cmake_minimum_required(VERSION 3.17)
project(cosmicOS NONE)

enable_language(C CXX ASM)
set(CMAKE_CXX_STANDARD 20)
set(KERNEL_ARCH amd64)

set_property(SOURCE
        ${CMAKE_CURRENT_LIST_DIR}/kernel/arch/${KERNEL_ARCH}/boot.S
        ${CMAKE_CURRENT_LIST_DIR}/kernel/arch/${KERNEL_ARCH}/cpuid.S
        ${CMAKE_CURRENT_LIST_DIR}/kernel/arch/${KERNEL_ARCH}/main.S
        ${CMAKE_CURRENT_LIST_DIR}/kernel/arch/${KERNEL_ARCH}/paging.S
        PROPERTY LANGUAGE ASM)
add_executable(cosmicOS
        ${CMAKE_CURRENT_LIST_DIR}/kernel/arch/${KERNEL_ARCH}/boot.S
        ${CMAKE_CURRENT_LIST_DIR}/kernel/arch/${KERNEL_ARCH}/cpuid.S
        ${CMAKE_CURRENT_LIST_DIR}/kernel/arch/${KERNEL_ARCH}/main.S
        ${CMAKE_CURRENT_LIST_DIR}/kernel/arch/${KERNEL_ARCH}/paging.S
        kernel/kernel/io/output/Display.cpp
        kernel/kernel/io/output/Display.h
        kernel/kernel/setup/interrupts/IDT.cpp
        kernel/kernel/setup/interrupts/IDT.h
        kernel/kernel/io/output/IO.cpp
        kernel/kernel/io/output/IO.h
        kernel/kernel/asm/asm.h
        kernel/kernel/kernel.cpp kernel/kernel/setup/pic/PIC.cpp kernel/kernel/setup/pic/PIC.h)

target_compile_options(cosmicOS PRIVATE -g -nostdlibinc -nostdlib -ffreestanding -target x86_64-unknown-gnu -mno-red-zone -Wall -Wextra -msoft-float -mno-mmx -mno-sse -mcmodel=large -fno-pie)
target_link_options(cosmicOS PRIVATE -g -Wl,-T "${CMAKE_CURRENT_LIST_DIR}/kernel/arch/${KERNEL_ARCH}/linker.lds" -nostdlib -target x86_64-unknown-gnu -fuse-ld=lld -Wunused-parameter,-Wl,--no-pie -Wl,--no-dynamic-linker)
set_target_properties(cosmicOS PROPERTIES LINK_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/kernel/arch/${KERNEL_ARCH}/linker.lds")