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
        kernel/kernel/kernel.c)

target_compile_options(cosmicOS PRIVATE -g -nostdlibinc -nostdlib -ffreestanding -target x86_64-unknown-gnu -mno-red-zone -Wall -Wextra -msoft-float -mno-mmx -mno-sse -mcmodel=large -fno-pie)
target_link_options(cosmicOS PRIVATE -g -Wl,-T "${CMAKE_CURRENT_LIST_DIR}/kernel/arch/${KERNEL_ARCH}/linker.lds" -nostdlib -target x86_64-unknown-gnu -fuse-ld=lld -Wl,--no-pie -Wl,--no-dynamic-linker)
set_target_properties(cosmicOS PROPERTIES LINK_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/kernel/arch/${KERNEL_ARCH}/linker.lds")