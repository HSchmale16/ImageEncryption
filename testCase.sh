#!/bin/bash
# @author Henry J Schmale
# @date February 28, 2015
# Test Case for Image Encrypter

# TEST VARS
KEY="QWERTY7991"    # Key to use for encryption
ORIGNAL="main.cpp"  # file to use as test data

# -------------------------------------
# Begin Primary Script

# File Vars
EXE=./ImgCrypt
IMG_OUT="$ORIGNAL.bmp"
TEXT_OUT="$IMG_OUT.txt"

# Pass or Fail Colorize Vars
PASS='\033[0;32m'
FAIL='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'

NDEV=/dev/null  # Null Device

echo "ImgCrypt Test Cases"
echo -e "Test Data: ${BLUE}$ORIGNAL${NC}"
echo -e "Test Key:  ${BLUE}$KEY${NC}"

# Build The Program
make >$NDEV

# encryption test
echo "Encrypting Some data"
$EXE e $ORIGNAL $IMG_OUT $KEY >$NDEV

# decryption test
echo "Decrypting some data"
$EXE d $IMG_OUT $TEXT_OUT $KEY >$NDEV

# Data Intergretity Test
echo "Now Performing Data Intergretity Test"
cmp -s filename_1 filename_2 > /dev/null
if [ $? -eq 1 ]; then
    echo -e "${PASS}PASS${NC}"
else
    echo -e "${FAIL}FAIL${NC}"
fi
