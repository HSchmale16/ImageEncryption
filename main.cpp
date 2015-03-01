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
    assert(KEY != NULL);
    assert(instr != NULL);
    assert(outstr != NULL);
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
        outstr[i] = instr[i] ^ KeyCopy[i % keyLen];
        if((i % keyLen) == 0){
            for(int j = 0; j < keyLen; j++){
                KeyCopy[j] = rotateRight(KeyCopy[j], 1);
            }
        }
    }
    delete[] KeyCopy;
    //std::cerr << "Finished Decrypting String" << std::endl;
}

void writeOutToImage(const char * fname, uint8_t *data,
                     uint64_t lenData){
    using namespace cimg_library;
    int64_t sideLen = sqrt(lenData / 3 + 1) + 1;
    CImg<uint8_t> img(sideLen, sideLen, 1, 3);
    img.fill(0);
    uint64_t i = 0;
    for(int32_t x = 0; x < sideLen; x++){
        for(int32_t y = 0; y < sideLen; y++){
            for(int8_t c = 0; c < 3; c++){
                if(i < lenData){
                    img(x, y, 0, c) = data[i];
                }
                i++;
            }
        }
    }
    img.save_bmp(fname);
    //std::cerr << "Finished Writting out image" << std::endl;
}

/** \brief Reads in data from image. 
 * \return The total ammount of memory allocated in
 * \param fname the name of the file read in.
 * \param readInStr - The pointer to readin to at. This ptr is allocated
 * in this function, so the param passed should be a NULL ptr.
 * \note The parameter `readInStr` should be a null pointer, as this
 * will allocate the memory for it to use.
 */
uint64_t readInFromImage(const char *fname, uint8_t **readInStr){
    using namespace cimg_library;
    assert(*readInStr == NULL);   // This should be null
    assert(fname != NULL);       // This must be a valid image file
    CImg<uint8_t> img(fname);
    uint64_t SZ = img.width() * img.height() * img.depth() * img.spectrum();
    *readInStr = new uint8_t[SZ];
    uint64_t i = 0;
    for(int32_t x = 0; x < img.width(); x++){
        for(int32_t y = 0; y < img.height(); y++){
            for(int8_t c = 0; c < img.spectrum(); c++){
                if(i < SZ){
                    (*readInStr)[i] = img(x, y, 0, c);
                    i++;
                }
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
