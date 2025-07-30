ENTRY(_start)

SECTIONS {
    . = 0x80000;

    .text : {
        *(.text*)
    }

    .bss : {
        *(.bss*)
    }

    .data : {
        *(.data*)
    }

    . = ALIGN(16);
    .stack : {
        *(.stack*)
        . = . + 0x1000; /* 4KB stack */
    }
    __stack_top__ = .;
}

