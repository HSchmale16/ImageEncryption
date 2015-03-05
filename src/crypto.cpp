/** \file crypto.cpp
 * \author Henry J Schmale
 * \date March 5, 2015
 *
 * Contains Crypto Function Implementations
 */

#include "crypto.h"
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

void encryptString(const uint8_t *KEY, uint16_t keyLen, uint8_t *instr,
                   uint64_t inlen, uint8_t *outstr, uint64_t outlen){
    assert(inlen <= outlen);
    assert(KEY != NULL);
    assert(instr != NULL);
    assert(outstr != NULL);
    uint8_t *KeyCopy = new uint8_t[keyLen];
    memcpy(KeyCopy, KEY, keyLen);
    for(uint64_t i = 0; i < inlen; i++){
        outstr[i] = instr[i] ^ KeyCopy[i % keyLen];
        outstr[i] = rotateRight(outstr[i], 1);
        if((i % keyLen) == 0){
            for(int j = 0; j < keyLen; j++){
                KeyCopy[j] = rotateRight(KeyCopy[j], 1);
            }
        }
    }
    // Secure Memory
    for(uint16_t i = 0; i < keyLen; i++){
        KeyCopy[i] = 0; // overwrite the key copy
    }
    delete[] KeyCopy;
    //std::cerr << "Finished Encrypting String" << std::endl;
}

void decryptString(const uint8_t *KEY, uint16_t keyLen, uint8_t *instr,
                   uint64_t inlen, uint8_t *outstr, uint64_t outlen){
    assert(inlen <= outlen);
    assert(KEY != NULL);
    assert(instr != NULL);
    assert(outstr != NULL);
    uint8_t *KeyCopy = new uint8_t[keyLen];
    memcpy(KeyCopy, KEY, keyLen);
    for(uint64_t i = 0; i < inlen; i++){
        outstr[i] = rotateLeft(instr[i], 1);
        outstr[i] = outstr[i] ^ KeyCopy[i % keyLen];
        if((i % keyLen) == 0){
            for(int j = 0; j < keyLen; j++){
                KeyCopy[j] = rotateRight(KeyCopy[j], 1);
            }
        }
    }
    // Secure Memory
    for(uint16_t i = 0; i < keyLen; i++){
        KeyCopy[i] = 0; // overwrite the key copy
    }
    delete[] KeyCopy;
    //std::cerr << "Finished Decrypting String" << std::endl;
}
