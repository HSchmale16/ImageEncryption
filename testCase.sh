#!/bin/bash
# @author Henry J Schmale
# @date February 28, 2015
# Test Case for Image Encrypter

EXE=./ImgCrypt
KEY="QWERTY7991"
ORIGNAL="main.cpp"
IMG_OUT="$ORIGNAL.bmp"
TEXT_OUT="$IMG_OUT.txt"

make # Build the program

# encryption test
$EXE e $ORIGNAL $IMG_OUT $KEY

# decryption test
$EXE d $IMG_OUT $TEXT_OUT $KEY

diff -q $ORIGNAL $TEXT_OUT
