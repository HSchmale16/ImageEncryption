/** \file steno.h
 * \author Henry J Schmale
 * \date March 5, 2015
 *
 * Contains stenography function prototypes
 */
 
#include "steno.h"
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <CImg.h>

void writeOutToImage(const char * fname, uint8_t *data,
                     uint64_t lenData){
    using namespace cimg_library;
    int64_t sideLen = sqrt(ceil(lenData / 3.0)) + 1;
    CImg<uint8_t> img(sideLen, sideLen, 1, 3);
    img.fill(0);
    uint64_t i = 0;
    for(int32_t x = 0; x < sideLen; x++){
        for(int32_t y = 0; y < sideLen; y++){
            for(int8_t c = 0; c < 3; c++){
                if(i < lenData){
                    img(x, y, 0, c) = data[i];
                    i++;
                }else{
                    img(x, y, 0, c) = rand() % 255;
                }
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
    uint64_t SZ = img.width() * img.height() * img.spectrum();
    for(int32_t x = 0; x < img.width(); x++){
        for(int32_t y = 0; y < img.height(); y++){
            for(int8_t c = 0; c < img.spectrum(); c++){
            
            }
        }
    }
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
