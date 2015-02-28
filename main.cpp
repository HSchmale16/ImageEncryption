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
#include <CImg.h>

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
    using namespace cimg_library;
    uint64_t sideLen = sqrt(lenData / 3 + 1)  + 1;
    CImg<uint8_t> img(sideLen, sideLen, 1, 3);
    img.fill(0);
    uint64_t i = 0;
    for(uint32_t x = 0; x < sideLen; x++){
        for(uint32_t y = 0; y < sideLen; y++){
            for(uint8_t c = 0; c < 3; c++){
                if(i < lenData){
                    img(x, y, 0, c) = data[i];
                }
                i++;
            }
        }
    }
    img.save_bmp(fname);
}

/** \brief Reads in data from image. 
 * \return number of chars written.
 * \param fname the name of the file read in.
 * \param readInStr - The pointer to readin to at. This ptr is allocated
 * in thins function so it should be a NULL ptr.
 * \note The parameter `readInStr` should be a null pointer, as this
 * will allocate the memory for it to use.
 */
uint64_t readInFromImage(const char *fname, uint8_t* readInStr){
    using namespace cimg_library;
    assert(readInStr == NULL);
    uint64_t i = 0;
    CImg<uint8_t> img(fname);
    uint64_t SZ = img.width() * img.height() * img.spectrum();
    std::cerr << SZ << std::endl;
    readInStr = new uint8_t[SZ];
    for(int32_t x = 0; x < img.width(); i++){
        for(int32_t y = 0; y < img.height(); y++){
            for(uint8_t c = 0; c < img.spectrum(); c++){
                if(i < SZ){
                    readInStr[i] = img(x, y, 0, c);
                }else{
                    return i;
                }
                i++;
            }
        }
    }
    return i;
}

// Program Entry Point
int main(int argc, char **argv){
    if(argc < 4){
        std::cerr << "Too few args passed to program" << std::endl;
        exit(0);
    }
    
    uint8_t *indata = 0, *outdata = 0;
    uint64_t fileLength;
    std::ifstream instr;
    
    // Do I Encrypt or Decrypt?
    if(argv[1][0] == 'e'){
        // Encrypt the given file
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
        fileLength = readInFromImage(argv[2], indata);
        outdata = new uint8_t[fileLength];
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
