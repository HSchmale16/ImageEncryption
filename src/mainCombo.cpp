/** Image Encrypter
 * \author Henry J Schmale
 * \date February 25, 2015
 *
 * Encrypts a file and then creates an Image that looks like fractal artwork
 * from the encrypted data.
 * USAGE:
 * argv[0] e|d <infile> <outfile> <key>
 */

#include <cstdint>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ios>
#include <CImg.h>
#include "crypto.h"
#include "steno.h"

// Program Entry Point
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
        std::ifstream instr;
        instr.open(argv[2]);
        if(!instr){
            std::cerr << "Failed to open file: " << argv[2] << std::endl;
            exit(0);
        }
        std::string str;
        instr.seekg(0, std::ios::end);
        str.reserve(instr.tellg());
        instr.seekg(0, std::ios::beg);
        str.assign((std::istreambuf_iterator<char>(instr)),
                    std::istreambuf_iterator<char>());
        fileLength = str.length();
        indata = new uint8_t[fileLength];
        outdata = new uint8_t[fileLength];
        memcpy(indata, (void*)(str.c_str()), str.length()-1);
        encryptString((uint8_t*)argv[4], strlen(argv[4]), indata,
                      fileLength, outdata, fileLength);
        writeOutToImage(argv[3], outdata, fileLength);
        instr.close();
    }else if(argv[1][0] == 'd'){
        // decrypt the given file
        fileLength = readInFromImage(argv[2], &indata);
        outdata = new uint8_t[fileLength];
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
    if(indata != NULL){
        delete[] indata;
    }
    if(outdata != NULL){
        delete[] outdata;
    }
}

