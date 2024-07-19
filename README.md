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
    - output big-endian (MSB first).
- `-x64` as hexadecimal string for 64-bits unigned integer:
    - input as ASCII.
    - hexadeciaml format.
    - padding. 
    - output little-endian (LSB first).
- `-if` as input file name to read from:
    - shall have ".bin" extension.

Additionaly, [n] suffix can be appended to previous flags to repeat the output. It shall be a strictly positive integer.

### Examples
To output the string "ABCDEFGH":
> binject -s ABCDEFGH <br>
> binject -x 4142434445464748&emsp;Big-endian. <br>
> binject -x64 48474645434241&emsp;Little-endian. <br>

To multiply the same output, -n prefix can be appended to any of format flags to repeat its output. As to output the string "AABB":
> binject -ns 2 A -nx 2 42      will output "AABB"

## Enhanced features
Enhanced features are available through following flags, and shall always preceed [data] flags.

### Output file
Some characters are **non-printables** (control, null etc..), or handled by the terminal as **UTF-8** (>0x80); in this case: 
- `-of` as output file name to write on:
    - shall have ".bin" extension. 
    - overwritten if already exists.

It allows user to append non-printable characters using `-x` or `-x64` flags to be stored within a binary file. Produced file can be used for both:
- input file within a new **binject** command using `-if` flag.
- binary injection for executable.

As for an example:
> binject -of *file_name.bin* -x 0001028082DFFF