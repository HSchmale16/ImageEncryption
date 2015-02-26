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
#include <iostream>
#include <cassert>
#include <fstream>
#include <cstdlib>
#include <cstring>

void encryptString(uint8_t *KEY, uint16_t keyLen, uint8_t *instr,
                   uint64_t inlen, uint8_t *outstr, uint64_t outlen){
    assert(inlen <= outlen);
    for(int i = 0; i < inlen; i++){
        outstr[i] = instr[i] ^ KEY[i % keyLen];
    }
}

void decryptString(uint8_t *KEY, uint16_t keyLen, uint8_t *instr,
                   uint64_t inlen, uint8_t *outstr, uint64_t outlen){
    assert(inlen <= outlen);
    for(int i = 0; i < inlen; i++){
        outstr[i] = instr[i] ^ KEY[i % keyLen];
    }
}

int main(int argc, char **argv){
    char *indata, outdata;
    std::ifstream instr(argv[2]);
    if(!instr){
        std::cerr << "Failed to open file: " << argv[2] << std::endl;
        exit(1);
    }

    // Encrypt or decrypt
    if(argv[1][0] == 'e'){
        // Encrypt the given file
    }else if(argv[1][0] == 'd'){
        // decrypt the given file
    }else{
        // invalid arg
        std::cerr << "Invalid arguement as to wether to encrypt or "
                  << "decrypt" << std::endl;
    }
}
