/** Image Encrypter - Encrypter Exe Main File
 * \author Henry J Schmale
 * \date March 5, 2015
 * \file mainCrypt.cpp
 *
 * This file contains the main function to demonstrate the
 * cryptography system.
 */
 
#include <cstdint>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ios>
#include "crypto.h"
 
int main(int argc, char **argv){
    if(argc < 4){
        std::cerr << "Too few args passed to program" << std::endl;
        exit(0);
    }
    
    uint8_t *indata = NULL,
            *outdata = NULL;
    uint64_t fileLength = 0;
    
    // Do I Encrypt or Decrypt?
    if(argv[1][0] == 'e'){
        // Encrypt the given file 
        std::fstream infile(argv[2], 
                            std::ios::in | std::ios::binary | std::ios::ate);
        if(infile.is_open()){
            fileLength = infile.tellg();
            indata = new uint8_t[fileLength];
            outdata = new uint8_t[fileLength];
            infile.seekg(0, std::ios::beg);
            if(!infile.read((char*)indata, fileLength)){
               std::cerr << "Failed to read file: " << argv[2] 
                         << std::endl;
               /** gotos are typically bad practice, but here it's
                * nessary as break can't break out of a nested if statement
                */
               goto fail;
            }
            infile.close();
        }
        encryptString((uint8_t*)argv[4], strlen(argv[4]), indata,
                      fileLength, outdata, fileLength);
        std::ofstream outfile(argv[3], std::ios::binary);
        for(uint64_t i = 0; i < fileLength; i++){
            outfile << outdata[i];
        }
        outfile.close();
        infile.close();
    }else if(argv[1][0] == 'd'){
        // decrypt the given file
        std::fstream infile(argv[2], 
                            std::ios::in | std::ios::binary | std::ios::ate);
        if(infile.is_open()){
            fileLength = infile.tellg();
            indata = new uint8_t[fileLength];
            outdata = new uint8_t[fileLength];
            infile.seekg(0, std::ios::beg);
            if(!infile.read((char*)indata, fileLength)){
               std::cerr << "Failed to read file: " << argv[2] 
                         << std::endl;
               /** gotos are typically bad practice, but here it's
                * nessary as break can't break out of a nested if statement
                */
               goto fail;
            }
            infile.close();
        }
        assert(indata != NULL);
        assert(outdata != NULL);
        decryptString((uint8_t*)argv[4], strlen(argv[4]), indata,
                      fileLength, outdata, fileLength);
        std::ofstream outfile;
        outfile.open(argv[3], std::ios::binary);
        for(uint64_t i = 0; i < fileLength; i++){
            outfile << outdata[i];
        }
        outfile.close();
    }else{
        // invalid args
        std::cerr << "Invalid arguement as to whether to encrypt or "
                  << "decrypt the given file" << std::endl;
    }

    // perform clean up
fail:
    if(indata != NULL){
        delete[] indata;
    }
    if(outdata != NULL){
        delete[] outdata;
    }
}
