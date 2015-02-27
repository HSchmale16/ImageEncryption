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
#include <climits>
#include <string>

/** \brief rotates a variables bits right n pos then returns that
 * \note n is 8 bits only because no standard type in C has more than
 * 64 bits, 8 bits is more than sufficent for this purpose.
 */
template<typename TYP>
TYP rotateRight(TYP x, uint8_t n){
    return (x >> n) | (x << ((sizeof(x) * CHAR_BIT) - n));
}

template<typename TYP>
TYP rotateLeft(TYP x, uint8_t n){
    return (x << n) | (x >> ((sizeof(x) * CHAR_BIT) - n));
}

void encryptString(const uint8_t *KEY, uint16_t keyLen, uint8_t *instr,
                   uint64_t inlen, uint8_t *outstr, uint64_t outlen){
    assert(inlen <= outlen);
    uint8_t *KeyCopy = new uint8_t[keyLen];
    memcpy(KeyCopy, KEY, keyLen);
    for(uint64_t i = 0; i < inlen; i++){
        outstr[i] = instr[i] ^ KeyCopy[i % keyLen];
        if((i % keyLen) == 0){
            for(int j = 0; j < keyLen; j++){
                KeyCopy[j] = rotateRight(KeyCopy[j], 1);
            }
        }
    }
    delete[] KeyCopy;
}

void decryptString(const uint8_t *KEY, uint16_t keyLen, uint8_t *instr,
                   uint64_t inlen, uint8_t *outstr, uint64_t outlen){
    assert(inlen <= outlen);
    uint8_t *KeyCopy = new uint8_t[keyLen];
    memcpy(KeyCopy, KEY, keyLen);
    for(uint64_t i = 0; i < inlen; i++){
        outstr[i] = instr[i] ^ KeyCopy[i % keyLen];
        if((i % keyLen) == 0){
            for(int j = 0; j < keyLen; j++){
                KeyCopy[j] = rotateRight(KeyCopy[j], 1);
            }
        }
    }
    delete[] KeyCopy;
}

void writeOutToImage(const char * fname, uint8_t *data,
                     uint64_t lenData){

}

int main(int argc, char **argv){
    uint8_t *indata = 0, *outdata = 0;
    uint64_t fileLength;
    std::ifstream instr(argv[2]);

    // Do I Encrypt or Decrypt?
    if(argv[1][0] == 'e'){
        // Encrypt the given file
        if(!instr){
            std::cerr << "Failed to open file: " << argv[2] << std::endl;
            exit(1);
        }else{
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
        }
    }else if(argv[1][0] == 'd'){
        // decrypt the given file
    }else{
        // invalid arg
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
