# Homebrew CPU

This is the repo for the 8-bit CPU being built from scratch in the #homebrew-cpu channel on the [HackClub](https://www.hackclub.com) slack. 


## Modules
The entire computer is built first as a bunch of "modules" including (but not limited to) the

- [Random Access Memory (RAM)](./Modules/RAM/RAM.md)

- [Registers (A, B, Instruction)](./Modules/Registers/)

- [Arithmetic Logic Unit (ALU)](./Modules/ALU/ALU.md)

- [Control unit (This one is special)](./Modules/ControlUnit/ControlUnit.md)

Read more [here](./Modules/modules.md).

## How do instructions work?

*(Subject to change)*


Each instruction will occupy two bytes of memory. One for the opcode (what instruction it is) and another for the memory address it's operating on.

For example,

Say we had this instruction: 

```00000001 00000101```

The first byte ```00000001``` would tell us that this is instruction 1. If we also look at the second byte we see ```00000101``` which tells us that it's operating on address 5 in RAM. Say for example that we had an instruction set that looked like this:

1. LOAD_REGISTER_A

2. STORE_REGISTER_A

3. ADD_A

The opcode of 1 would tell us that this instruction is the *LOAD_REGISTER_A* instruction. What that would then tell the processor to do is look in the RAM at address 5 (the second byte from before) and store the value at that address in the A register.


## Todo

1. Build the rest of the modules
2. Build the computer 
3. Program the microinstructions
4. Debug problems that will definitely come up
5. Make a simple assembly language compiler for this machine
6. Debug more
7. Make cool stuff! 