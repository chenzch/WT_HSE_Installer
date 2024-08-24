/*****************************************************************************
 *
 * Copyright 2021-2022 NXP
 * All Rights Reserved
 *
 *****************************************************************************
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

__STACK_SIZE = 0x00001000;

/* Linker script to configure memory regions. */
MEMORY
{
  HSE_BINARY  (R)  : ORIGIN = 0x00400000, LENGTH = 0x00040000   /* Leave block 0 for HSE FW binary */
  HSE_BINARYB (R)  : ORIGIN = 0x00500000, LENGTH = 0x00040000
  DFLASH      (RX) : ORIGIN = 0x10000000, LENGTH = 0x2000
  SRAM        (RW) : ORIGIN = 0x20400000, LENGTH = 0x2000
  SRAM_STATUS (RW) : ORIGIN = 0x20402000, LENGTH = 0x10
}

TARGET(binary) /* specify the file format of binary file */
INPUT (..\HSE_FW_S32K312_0_2_40_0\hse_ab_swap\s32k312_hse_fw_1.13.0_2.40.0_pb230730.bin.pink)
INPUT (.\..\HSE_FW_S32K312_0_2_40_0\hse_ab_swap\s32k312_hse_fw_1.13.0_2.40.0_pb230730.bin.pink)
OUTPUT_FORMAT(default) /* restore the out file format */

/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and RAM.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler : Entry of reset handler
 *
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __ecc_table_start__
 *   __ecc_table_end__
 *   __etext
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __end__
 *   end
 *   __StackLimit
 *   __StackTop
 *   __stack
 */
ENTRY(Reset_Handler)

SECTIONS
{
	.hse_bin :
  	{
  		. = ALIGN (0x4);
  		..\HSE_FW_S32K312_0_2_40_0\hse_ab_swap\s32k312_hse_fw_1.13.0_2.40.0_pb230730.bin.pink (.data)
  		. = ALIGN (0x4);
  	} > HSE_BINARY

  	__HSE_BIN_START = ORIGIN(HSE_BINARY);

  .hse_binb :
  	{
  		. = ALIGN (0x4);
  		.\..\HSE_FW_S32K312_0_2_40_0\hse_ab_swap\s32k312_hse_fw_1.13.0_2.40.0_pb230730.bin.pink (.data)
  		. = ALIGN (0x4);
  	} > HSE_BINARYB

  .boot_header :
  {
    KEEP(*(.boot_header))
  } > DFLASH

  .text :
  {
    . = ALIGN (0x100);
    CM7_START_ADDRESS = .;
    KEEP(*(.vectors))
    *(.text*)

    KEEP(*(.init))
    KEEP(*(.fini))

    /* .ctors */
    *crtbegin.o(.ctors)
    *crtbegin?.o(.ctors)
    *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
    *(SORT(.ctors.*))
    *(.ctors)

    /* .dtors */
     *crtbegin.o(.dtors)
     *crtbegin?.o(.dtors)
     *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
     *(SORT(.dtors.*))
     *(.dtors)

    *(.rodata*)
    KEEP(*(.eh_frame*))
  } > DFLASH

  .ARM.extab :
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } > DFLASH

  __exidx_start = .;
  .ARM.exidx :
  {
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
  } > DFLASH
  __exidx_end = .;

  .ecc.table :
  {
    . = ALIGN(4);
    __ecc_table_start__ = .;

    QUAD (__data_start__)
    QUAD ((__data_end__ - __data_start__) / 8)

    QUAD (__bss_start__)
    QUAD ((__bss_end__ - __bss_start__) / 8)

    QUAD (__StackLimit)
    QUAD ((__StackTop - __StackLimit) / 8)

    __ecc_table_end__ = .;
  } > DFLASH

  .copy.table :
  {
    . = ALIGN(4);
    __copy_table_start__ = .;

    LONG (__etext)
    LONG (__data_start__)
    LONG ((__data_end__ - __data_start__) / 4)

    /* Add each additional data section here */
    /*
      LONG (__etext2)
      LONG (__data2_start__)
      LONG ((__data2_end__ - __data2_start__) / 4)
    */
    __copy_table_end__ = .;
  } > DFLASH

  .zero.table :
  {
    . = ALIGN(4);
    __zero_table_start__ = .;
    /* Add each additional bss section here */
    /*
      LONG (__bss2_start__)
      LONG ((__bss2_end__ - __bss2_start__) / 4)
    */
    __zero_table_end__ = .;
  } > DFLASH

  .sbaf_bin :
  {
      . = ALIGN (0x4);
      __SBAF_BIN_START = .;
      . = ALIGN (0x4);
  } > DFLASH

  __etext = ALIGN(8);

  /* Due ECC initialization sequence __data_start__ and __data_end__ should be aligned on 8 bytes */
  .data : AT (__etext)
  {
    . = ALIGN(8);
    __data_start__ = .;
    *(vtable)
    *(.data)
    *(.data.*)

    . = ALIGN(4);
    /* preinit data */
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP(*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);

    . = ALIGN(4);
    /* init data */
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array))
    PROVIDE_HIDDEN (__init_array_end = .);

    . = ALIGN(4);
    /* finit data */
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP(*(SORT(.fini_array.*)))
    KEEP(*(.fini_array))
    PROVIDE_HIDDEN (__fini_array_end = .);

    KEEP(*(.jcr*))
    . = ALIGN(8);
    /* All data end */
    __data_end__ = .;

  } > SRAM

  /* Due ECC initialization sequence __bss_start__ and __bss_end__ should be aligned on 8 bytes */
  .bss :
  {
    . = ALIGN(8);
    __bss_start__ = .;
    *(.bss)
    *(.bss.*)
    *(COMMON)
    . = ALIGN(8);
    __bss_end__ = .;
  } > SRAM

  /* Due ECC initialization sequence __StackLimit and __StackTop should be aligned on 8 bytes */
  .stack (ORIGIN(SRAM) + LENGTH(SRAM) - __STACK_SIZE) (COPY) :
  {
    . = ALIGN(8);
    __StackLimit = .;
    . = . + __STACK_SIZE;
    . = ALIGN(8);
    __StackTop = .;
  } > SRAM

  __SRAM_STATUS_START = ORIGIN(SRAM_STATUS);

  PROVIDE(__stack = __StackTop);
}
