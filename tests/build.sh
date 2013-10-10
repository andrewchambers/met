set -e
#argument one is the toolchain path
#argument two is source file

BASE=`basename $2 .c`
$1/mips-baremetal-elf-gcc -march=r4000 -msoft-float -DCURTEST=\"$BASE\" -I./support/ -nostartfiles $2 ./support/*.c ./support/*.S -o $BASE
$1/mips-baremetal-elf-objcopy -Osrec $BASE $BASE.srec
