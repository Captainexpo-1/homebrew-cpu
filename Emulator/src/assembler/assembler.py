import sys 

if len(sys.argv) < 2:
    print(f"Usage: python3 {sys.argv[0]} <input_file> [<output_file>]")
    sys.exit(1)

input_file = sys.argv[1]
output_file = sys.argv[2] if len(sys.argv) > 2 else "program.bin"

assembly_code = ""
with open(input_file, "r") as file:
    assembly_code = file.read()


opcode_mapping = {
    'nop': 0x00,
    'lda': 0x01,
    'ldb': 0x02,
    'sta': 0x03,
    'stb': 0x04,
    'add': 0x05,
    'sub': 0x06,
    'jmp': 0x07,
    'je': 0x08,
    'jl': 0x09,
    'jg': 0x0A,
    'halt': 0x0B,
    'sav': 0x0C,
    'cmp': 0x0D,
    'lda_const': 0x0E,
    'aout': 0x0F,
}

def assemble_to_binary(assembly_code):
    lines = assembly_code.strip().splitlines()
    hex_output = ""
    label_addresses = {}
    current_address = 0

    # First pass to determine label addresses
    for idx, line in enumerate(lines):
        lines[idx] = line.split(';')[0].strip()
        line = lines[idx]
        if not line:
            continue
        
        if line.endswith(':'):
            label = line[:-1]
            label_addresses[label] = current_address
        else:
            parts = line.strip().split()
            mnemonic = parts[0]
            current_address += len(parts)

    # Second pass to generate binary code
    for line in lines:
        if not line or line.endswith(':'):
            continue
        
        parts = line.strip().split()
        mnemonic = parts[0]
        arg = parts[1] if len(parts) > 1 else None

        opcode = opcode_mapping.get(mnemonic, None)
        if opcode is None:
            raise ValueError(f"Unknown mnemonic: {mnemonic}")
        this_o = bytes([opcode]).hex()
        hex_output += bytes([opcode]).hex()

        if arg:
            if arg in label_addresses:
                address = label_addresses[arg]
            else:
                address = int(arg, 16)
            this_o += bytes([address]).hex()
            hex_output += bytes([address]).hex()
    print("Labels: ",label_addresses)
    return hex_output

hex_code = assemble_to_binary(assembly_code)
print("Compiled binary:\n",hex_code)
open(output_file, "wb").write(
    bytes.fromhex(hex_code)
)