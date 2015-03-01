#!/bin/bash
# @author Henry J Schmale
# @date February 28, 2015
# Test Case for Image Encrypter

EXE=./ImgCrypt
KEY="QWERTY7991"
ORIGNAL="main.cpp"
IMG_OUT="$ORIGNAL.bmp"
TEXT_OUT="$IMG_OUT.txt"

echo "ImgCrypt Test Cases"
echo "Test Data: $ORIGNAL"
echo "Test Key:  $KEY"

# Build The Program
make

# encryption test
echo "Encrypting Some data"
$EXE e $ORIGNAL $IMG_OUT $KEY

# decryption test
echo "Decrypting some data"
$EXE d $IMG_OUT $TEXT_OUT $KEY

# Data Intergretity Test
echo "Now Performing Data Intergretity Test"
diff -q $ORIGNAL $TEXT_OUT
