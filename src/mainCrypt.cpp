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
#include "fileHandler.h"
 
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
        fileLength = readBinFile(argv[2], &indata);
        outdata = new uint8_t[fileLength];
        encryptString((uint8_t*)argv[4], strlen(argv[4]), indata,
                      fileLength, outdata, fileLength);
        std::ofstream outfile(argv[3], std::ios::binary);
        for(uint64_t i = 0; i < fileLength; i++){
            outfile << outdata[i];
        }
        outfile.close();
    }else if(argv[1][0] == 'd'){
        // decrypt the given file
        fileLength = readBinFile(argv[2], &indata);
        outdata = new uint8_t[fileLength];
        assert(indata != NULL);
        assert(outdata != NULL);
        decryptString((uint8_t*)argv[4], strlen(argv[4]), indata,
                      fileLength, outdata, fileLength);
        writeBinFile(argv[3], outdata, fileLength);
    }else{
        // invalid args
        std::cerr << "Invalid arguement as to whether to encrypt or "
                  << "decrypt the given file" << std::endl;
    }

    // perform clean up
    if(indata != NULL){
        delete[] indata;
    }
    if(outdata != NULL){
        delete[] outdata;
    }
}
