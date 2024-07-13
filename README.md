# README

## Install

Assuming it exist a bin folder within user space (~/bin) to contains executables added to path (with ~/.bashrc).

> wget https://github.com/anarticho/binject/archive/refs/heads/main.zip <br>
> unzip main.zip <br>
> make <br>
> cp ./build/binject ~/bin/binject <br>

## Description

- Arguments are coming through [-flag] [data] format as:
- [-flag] an ASCII string beginning with '-' and flag character(s).
- [data] an ASCII string to be interpreted from provided flag.
    
Flag determine the way [data] will be outputed as:
- 's' as ASCII string.
- 'x' as hexadecimal string:
    - input as ASCII.
    - hexadecimal format.
    - output big-endian (MSB first).
- 'x64' as hexadecimal string for 64-bits unigned integer:
    - input as ASCII.
    - hexadeciaml format.
    - padding. 
    - output little-endian (LSB first).

Additionaly, [num] can be appended between [-flag] and [data] to repeat the output. It shall be a strictly positive integer.

## Usage

To output the string "ABCDEFGH":
> binject -s ABCDEFGH <br>
> binject -x 4142434445464748&emsp;Big-endian. <br>
> binject -x64 48474645434241&emsp;Little-endian. <br>

To multiply the same output, -n prefix can be appended to any of format flags to repeat its output. As to output the string "AABB":
> binject -ns 2 A -nx 2 42      will output "AABB"

As it exist a lot of non-printables characters, to ensure integrity of produced bytes, a file could be used as:
> binject -s *string_arg* > *file_name*