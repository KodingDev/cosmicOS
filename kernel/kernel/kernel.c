void kernel_main(void) {
    volatile char *videoMemory = (volatile char *) 0xB8000;

    int i;
    for (i = 0; i < 2000; ++i) {
        *(videoMemory + (i * 2)) = 'A';
        *(videoMemory + (i * 2) + 1) = i % 16;
    }

    *((char *) 0xb8000) = 'B';
    *((char *) 0xb8002) = 'A';
    *((char *) 0xb8004) = 'L';
    *((char *) 0xb8006) = 'L';
    *((char *) 0xb8008) = 'S';
    *((char *) 0xb800A) = ' ';
    *((char *) 0xb800C) = 'D';
    *((char *) 0xb800E) = 'A';
    *((char *) 0xb8010) = 'M';
}