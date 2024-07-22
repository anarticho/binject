#!/bin/bash

# shall be executed from ../

VCF="tst/tst.bin"
T1F="tst/tst1.bin"
T2F="tst/tst2.bin"
T3F="tst/tst3.bin"

BAD="tst/bad.bin"
PRM="tst/prm.bin"

XVL="xvl.bin"
ESC="esc.bin"

# Execute binject with first set of parameters
build/binject -of $T1F -s ABCD -x 45464748 -ns 4 I -nx 4 4A -a 12 -na 2 ACAB1312DEADBEEF

# Check if tst1.bin matches _vec.bin
printf "[*] > binject -of tst1.bin -s ABCD -x 45464748 -ns 4 I -nx 4 4A -a 12 -na 2 ACAB1312DEADBEEF\n"
if cmp -s $VCF $T1F
then : 
    printf "[*] > OK\n[*]\n"
    # Execute binary with second set of parameters
    build/binject -if $T1F > $T2F  
    printf "[*] > binject -if tst1.bin > tst2.bin\n"  
    if cmp -s $VCF $T2F
    then : 
        printf "[*] > OK\n[*]\n"
        # Execute -bd flag
        build/binject -bd $BAD $PRM > /dev/null
        printf "[*] > binject -bd bad.bin prm.bin\n"
        if cmp -s $ESC $T3F
        then :
            printf "[*] > OK\n[*]\n"
            printf "[*] Check succeed\n"
        else :
            printf "[*] > FAIL\n[*]\n"
        fi
    else :
        printf "[*] > FAIL\n[*]\n"
    fi
else :
    printf "[*] > FAIL\n[*]\n"
fi
rm -f $T1F
rm -f $T2F
rm -f $XVL
rm -f $ESC