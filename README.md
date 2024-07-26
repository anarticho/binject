# README

## Install
Assuming it exist a bin folder within user space (~/bin) to contains executables added to path (with ~/.bashrc).

> wget https://github.com/anarticho/binject/archive/refs/heads/main.zip <br>
> unzip main.zip <br>
> make <br>
> make to_bin <br>

## Usage
- Arguments are coming through [-flag] [data] format as:
- [-flag] an ASCII string beginning with `-` and flag character(s).
- [data] an ASCII string to be interpreted from provided flag.
    
Flag determine the way [data] will be outputed as:
- `-s` as ASCII string.
- `-x` as hexadecimal string:
    - input as ASCII.
    - hexadecimal format.
- `-a` as memory address (depends on architecture):
    - input as ASCII.
    - hexadeciaml format.
    - padding. 
    - output little-endian (LSB first).
- `-if` as input file name to read from:
    - shall have ".bin" extension.

[n] suffix can be appended to previous flags to repeat the output. It shall be a strictly positive integer.

Additionaly, there is some flags for enhanced features as:
- `-of` with parameters as:
    - `[fname]` as ASCII string for output file name, shall have ".bin" extension.
- `-bd` with parameters as:
    - `[bchar]` as ASCII string for the file containing bad characters, shall have ".bin" extension.
    - `[param]` as ASCII string for the file containing bytes to be escaped, shall have ".bin" extension.
    - `[maddr]` as ASCII string into hexadecimal format for memory address.
    - Generate 3 types of outputs (besides console's one):
        - `xvl.bin` the binary file to contain the computed value for XOR operation.
        - `esc.bin` the binary file to contain the escaped bytes.
        - `offset` directory with all the bad characters offset, based on `maddr`.

### Examples
To output the string "ABCDEFGH":
> binject -s ABCDEFGH <br>
> binject -x 4142434445464748&emsp;Big-endian. <br>
> binject -a 48474645434241&emsp;Little-endian. <br>

To multiply the same output, -n prefix can be appended to any of format flags to repeat its output. As to output the string "AABB":
> binject -ns 2 A -nx 2 42      will output "AABB"

## Enhanced features
Enhanced features are available through following flags, and shall always preceed [data] flags.

### Output file
Some characters are **non-printables** (control, null etc..), or handled by the terminal as **UTF-8** (>0x80); in this case: 
- `-of` as output file name to write on:
    - shall have ".bin" extension. 
    - overwritten if already exists.

It allows user to append non-printable characters using `-x` or `-a` flags to be stored within a binary file. Produced file can be used for both:
- input file within a new **binject** command using `-if` flag.
- binary injection for executable.

As for an example:
> binject -of *file_name.bin* -x 0001028082DFFF

### Bad characters
Some executables completely escape some characters, it is called the **badchars**. To handle them, there is the following mechanism:
- PARAM to be load at MADDR on memory, 
- BADCHARS to be escaped with OFFSETs,
- ESCAPE, as XOR with unique computed XVAL _(\*)_,
- LOAD modified PARAM at MADDR,
- XOR at OFFSETs with XVAL,
- **badchars** are on memory !

_(\*)_ The XVAL computed value shall not result to a BADCHAR if applied to one of them.

First, there is the `-cb` flag to check a ROP chain, and identify the **badchar** from a complete **binject** sequence of flags.

Also, the `-bd` allow to generate files to be used within a ROP chain, as for:
- computed XVAL, 
- ESCAPE to contain the PARAM's bytes, escaped with XVAL, 
- set of OFFSETs, to be used within **binject** built ROP chain.

