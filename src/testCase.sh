#!/bin/bash
# @author Henry J Schmale
# @date February 28, 2015
# Test Script for Image Encrypter Program by me
# 
# If the first arg following this script is `CleanUp` then
# only the cleanup function is ran and the script exits

# TEST VARS
KEY="QWERTY7991"           # Key to use for encryption
ORIGNAL="main.cpp"         # file to use as test data

# -------------------------------------
# Begin Primary Script
# -------------------------------------
# Clean up, this should only happen on pass
function CleanUp {
    make clean
    if [ -e $IMG_OUT ] ; then rm $IMG_OUT ; fi
    if [ -e $TEXT_OUT ] ; then rm $TEXT_OUT ; fi
}
# File Vars
EXE=./ImgCrypt             # The executable
IMG_OUT="$ORIGNAL.bmp"     # First output
TEXT_OUT="$IMG_OUT.txt"    # Final output

# Pass or Fail Colorize Vars
PASS='\033[0;32m'
FAIL='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'

NDEV=/dev/null             # Null Device

# Test for args
if [ -n $1 ] ; then
    if [ $1 = "CleanUp" ] ; then
        echo "Clean Up Arg Detected, Running Clean Up"
        CleanUp
        exit 0
    fi
fi

CleanUp
echo "ImgCrypt Test Cases"
echo -e "Test Data: ${BLUE}$ORIGNAL${NC}"
echo -e "Test Key:  ${BLUE}$KEY${NC}"

# -------------------------------------
# Build The Program
echo -n "Building Program                             ["
make >$NDEV
if [ $? -eq 0 ] ; then
    echo -e "${PASS}PASS${NC}]"
else
    echo -e "${FAIL}FAIL${NC}]"
fi

# -------------------------------------
# encryption test
echo -n "Encrypting Some data                         ["
$EXE e $ORIGNAL $IMG_OUT $KEY >$NDEV
if [ -s $IMG_OUT ] ; then
    echo -e "${PASS}PASS${NC}]"
else
    echo -e "${FAIL}FAIL${NC}]"
fi
 
# -------------------------------------
# decryption test
echo -n "Decrypting some data                         ["
$EXE d $IMG_OUT $TEXT_OUT $KEY >$NDEV
if [ -s $TEXT_OUT ] ; then
    echo -e "${PASS}PASS${NC}]"
else
    echo -e "${FAIL}FAIL${NC}]"
fi

# -------------------------------------
# Data Intergretity Test
echo -n "Now Performing Data Intergretity Test        ["
cmp -s $ORIGNAL $TEXT_OUT >/dev/null
if [ $? -eq 0 ]; then
    echo -e "${PASS}PASS${NC}]"
    echo "Running Clean up, as there is a bunch of junk files now"
    CleanUp
else
    echo -e "${FAIL}FAIL${NC}]"
fi
