# Emulator

This is a simple emulator for the homebrew computer project.

## Prerequisites

- CMake
- Python 3.x

## Usage

To run the emulator, you must have cmake installed. Then, run the following commands:

```bash
mkdir build
cd build
cmake ..
make # or other build command

./bin/CPUEmulator
```

## Features

- [x] 8-bit CPU emulation
- [x] A massive 256 bytes of RAM
- [x] 8-bit ALU
- [x] 2x 8-bit registers
- [x] 8-bit program counter

## Instruction set

*the instruction set is subject to change*

| Instruction | Opcode | Description |
|-------------|--------|-------------|
| NOP         | 0x00   | No operation |
| LDA         | 0x01   | Load A register from memory |
| LDB         | 0x02   | Load B register from memory |
| STA         | 0x03   | Store A register to memory |
| STB         | 0x04   | Store B register to memory |
| ADD         | 0x05   | Adds the A and B registers |
| SUB         | 0x06   | Subtracts the A and B registers |
| JMP         | 0x07   | Jump to address |
| JE          | 0x08   | Jump if equal |
| JL          | 0x09   | Jump if less than |
| JG          | 0x0A   | Jump if greater than |
| HALT        | 0x0B   | Halt the CPU |
| SAV         | 0x0C   | Set the B register to the A register |
| CMP         | 0x0D   | Compare A and B registers |
| LDA_CONST   | 0x0E   | Load A register with a constant |
| AOUT        | 0x0F   | Output the value of the A register |

## Examples

You can find some example programs in the examples directory as well as their equivalent C programs. To run them, use the following commands:

```bash
# Assuming you are in the build directory and have already built the emulator to ./bin/CPUEmulator

python3 ../src/assembler/assembler.py ../examples/multiplication/multiply.asm ./multiply.bin

./bin/CPUEmulator ./multiply.bin
```

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request.
