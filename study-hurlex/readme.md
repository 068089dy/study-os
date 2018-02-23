[教程](http://wiki.0xffffff.org/posts/hurlex-3.html#fnref:14)
make过程
### 编译汇编文件 boot/boot.s ...
nasm -f elf -g -F stabs boot/boot.s
### 编译代码文件 init/entry.c ...
gcc -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -I include init/entry.c -o init/entry.o
### 链接：
ld -T scripts/kernel.ld -m elf_i386 -nostdlib  ./boot/boot.o  ./init/entry.o -o hx_kernel
### 更新镜像:
sudo mount floppy.img /mnt/kernel
sudo cp hx_kernel /mnt/kernel sleep 1
sudo umount /mnt/kernel
### 启动
qemu -fda floppy.img -boot a

###
sudo losetup -f  #查找空闲的环回设备
sudo losetup /dev/loop0 fd.img
sudo mkfs.fat /dev/loop0 #格式化
sudo mkdir /mnt/kernel
sudo mount -o loop /dev/loop0 /mnt/kernel   #挂载环回设备到/mnt
sudo mkdir -p /mnt/boot/grub    #创建购入表文件夹
wget ftp://alpha.gnu.org/gnu/grub/grub-0.97-i386-pc.tar.gz  #下载grub
解压后进入./grub-0.97-i386-pc/boot/grub
sudo cp stage1 stage2 fat_stage1_5 /mnt/boot/grub/
umount /mnt
sudo losetup -d /dev/loop0  #断开关联




sudo grub-install --target=i386-pc --recheck --boot-directory=/mnt/usb /dev/sdc
