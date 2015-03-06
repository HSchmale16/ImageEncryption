#!/bin/bash
# @author Henry J Schmale
# @date February 28, 2015
# Test Script for Image Encrypter Program by me

# NOTE: THE SUCCESS/FAIL BRACKET STARTS at col50

# make test file
# TEST VARS
key="QWERTY7991"                   # Key to use for encryption
testdata="test.txt"                # file to use as test data, this should be new file

# -------------------------------------
# Private Script Variables
# -------------------------------------
ecryTxtOut="$testdata.ecry"        # output file for encrpytion test
dcryTxtOut="$ecryTxtOut.dcry"      # output file for decryption test
imgOut="$testdata.png"             # image file for steno test
imgTxtOut="$imgOut.txt"            # output file for undoing steno test

cryptoExe=./Crypt                  # Cyptography EXE
stenoExe=./Steno                   # Stenography EXE   

# Pass or Fail Colorize Vars
PASS='\033[0;32m'
FAIL='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'

NDEV=/dev/null                     # Null Device

# -------------------------------------
# Script Functions
# -------------------------------------
# Clean Up
# Removes all generated files
function CleanUp {
rm -f $testdata
rm -f $ecryTxtOut
rm -f $dcryTxtOut
rm -f $imgOut
rm -f $imgTxtOut
rm -rf *.o
}

# Data Intergretity Test
# accepts 1 param, the file to diff against original
function diffTestData {
echo -n "Diff against original                   ["
cmp -s $testdata $1 >/dev/null
if [ $? -eq 0 ]; then    
    echo -e "${PASS}PASS${NC}]"
    echo "Running Clean up, as there is a bunch of junk files now"
    CleanUp
else
    echo -e "${FAIL}FAIL${NC}]"
fi
} # end diffTestData


# -------------------------------------
# Begin Primary Script
# -------------------------------------

# make test data set & calc size of in bytes
cat $(find . -regex '\./.*\.[cph]*')  > $testdata
dataSZ=$(wc -c $testdata | awk '{print $1 " Bytes"}')

# Output test params
echo "ImgCrypt Test Cases"
echo -e "Test Data: ${BLUE}$testdata${NC}"
echo -e "Test Size: ${BLUE}$dataSZ${NC}"
echo -e "Test Key:  ${BLUE}$key${NC}"

# -------------------------------------
# Build The Program
echo -n "Program Compiled Successfully           ["
make >$NDEV
if [ $? -eq 0 ] ; then
    echo -e "${PASS}PASS${NC}]"
else
    echo -e "${FAIL}FAIL${NC}]"
    exit
fi

# -------------------------------------
# Encryption Test
# this tests if there is an file output from the encrypt command
