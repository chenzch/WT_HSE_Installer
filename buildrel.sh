#!/bin/bash

for i in Debug_*; do
    arm-none-eabi-objcopy -O ihex $i/WT_HSE_Installer.elf release/${i/Debug_/}.hex
    arm-none-eabi-objcopy -O srec $i/WT_HSE_Installer.elf release/${i/Debug_/}.srec
done
