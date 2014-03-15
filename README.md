met
===

Mips emulator tests

A set of tests for testing mips emulators, i used qemu as a reference, you can run these tests against
qemu by passing the 4kc processor flag and -nographic option.

You will need a working toolchain to build the tests, you can run the tests with something like

python ./met.py run -s "../cmips/emu {KERNEL}"
