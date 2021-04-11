cmake_minimum_required(VERSION 3.17)
project(cosmicOS NONE)

enable_language(C CXX ASM)
set(CMAKE_CXX_STANDARD 20)
set(KERNEL_ARCH amd64)

add_executable(cosmicOS
        src/arch/${KERNEL_ARCH}/boot.S
        src/arch/${KERNEL_ARCH}/cpuid.S
        src/arch/${KERNEL_ARCH}/main.S
        src/arch/${KERNEL_ARCH}/paging.S
        src/kernel/io/output/Display.cpp
        src/kernel/io/output/Display.h
        src/kernel/boot/interrupts/IDT.cpp
        src/kernel/boot/interrupts/IDT.h
        src/kernel/io/output/IO.cpp
        src/kernel/io/output/IO.h
        src/kernel/asm/asm.h
        src/kernel/boot/pic/PIC.cpp
        src/kernel/boot/pic/PIC.h
        src/kernel/util/timer/Timer.cpp
        src/kernel/util/timer/Timer.h
        src/kernel/util/std/String.h
        src/kernel/boot/panic/Panic.cpp
        src/kernel/boot/panic/Panic.h
        src/kernel/kernel.cpp)

target_compile_options(cosmicOS PRIVATE -g -nostdlibinc -nostdlib -ffreestanding -target x86_64-unknown-gnu -mno-red-zone -Wall -Wextra -msoft-float -mno-mmx -mno-sse -mcmodel=large -fno-pie)
target_link_options(cosmicOS PRIVATE -g -Wl,-T "${CMAKE_CURRENT_LIST_DIR}/src/arch/${KERNEL_ARCH}/linker.lds" -nostdlib -target x86_64-unknown-gnu -fuse-ld=lld -Wunused-parameter,-Wunknown-pragmas,-Wl,--no-pie -Wl,--no-dynamic-linker)
set_target_properties(cosmicOS PROPERTIES LINK_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/arch/${KERNEL_ARCH}/linker.lds")