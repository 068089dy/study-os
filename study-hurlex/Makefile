#!Makefile

C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
S_SOURCES = $(shell find . -name "*.s")
S_OBJECTS = $(patsubst %.s, %.o, $(S_SOURCES))

CC = gcc
LD = ld
ASM = nasm


	# -m32 是生成32位代码，这样的话我们的开发环境也可以使用64位的Linux系统。
	# -ggdb 和-gstabs+ 是添加相关的调试信息，调试对后期的排错很重要。
	# -nostdinc 是不包含C语言的标准库里的头文件.
	# -fno-builtin 是要求gcc不主动使用自己的内建函数，除非显式声明。
	# -fno-stack-protector 是不使用栈保护等检测。

C_FLAGS = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -I include


	# -T scripts/kernel.ld 是使用我们自己的链接器脚本。
	# -m elf_i386 是生成i386平台下的ELF格式的可执行文件，这是Linux下的可执行文件格式。
	# -nostdlib 是不链接C语言的标准库，原因上文已经交代过了。

LD_FLAGS = -T scripts/kernel.ld -m elf_i386 -nostdlib
ASM_FLAGS = -f elf -g -F stabs

all: $(S_OBJECTS) $(C_OBJECTS) link update_image

.c.o:
	@echo 编译代码文件 $< ...
	$(CC) $(C_FLAGS) $< -o $@

.s.o:
	@echo 编译汇编文件 $< ...
	$(ASM) $(ASM_FLAGS) $<

link:
	@echo 链接内核文件...
	$(LD) $(LD_FLAGS) $(S_OBJECTS) $(C_OBJECTS) -o hx_kernel

.PHONY:clean
clean:
	rm $(S_OBJECTS) $(C_OBJECTS) hx_kernel

.PHONY:update_image
update_image:
	sudo mount floppy.img /mnt/
	sudo cp hx_kernel /mnt/hx_kernel
	sudo umount /mnt/

.PHONY:mount_image
mount_image:
	sudo mount floppy.img ./kernel

.PHONY:umount_image
umount_image:
	sudo umount /mnt/kernel

.PHONY:run
run:
	qemu -fda floppy.img -boot a

.PHONY:bochs
bochs:
	bochs -f tools/bochsrc.txt

.PHONY:debug
debug:
	qemu -S -s -fda floppy.img -boot a & sleep 1
	gdb -tui -x scripts/gdbinit