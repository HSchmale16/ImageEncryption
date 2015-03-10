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

rgbPX calcArray_rgbPxAvg(uint8_t *str, uint64_t sz){
    rgbPX px;
    uint64_t r = 0, g = 0, b = 0;
    for(uint64_t i = 0; i < sz; i++){
        if(i % 3 == 0){
            b += str[i];
            continue;
        }else if(i % 2 == 0){
            g += str[i];
            continue;
        }else{
            r += str[i];
            continue;
        }
    }
    px[rgbPX::RED]   = r / (sz / 3);
    px[rgbPX::GREEN] = g / (sz / 3);
    px[rgbPX::BLUE]  = b / (sz / 3);
    return px;
}

void writeOutToImage(const char *fname, uint8_t *data,
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

void writeOutToImage(const char *fname, uint8_t *data, uint64_t lenData,
                     uint32_t x, uint32_t y, uint32_t width,
                     uint32_t height){
    using namespace cimg_library;
    assert(fname != NULL);
    assert(data  != NULL);
    CImg<uint8_t> img(fname);
}

uint64_t readInFromImage(const char *fname, uint8_t **readInStr){
    using namespace cimg_library;
    assert(*readInStr == NULL);   // This should be null
    assert(fname != NULL);        // This must be a valid image file
    CImg<uint8_t> img(fname);
    uint64_t SZ = img.width() * img.height() * img.spectrum();
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

uint64_t readInFromImage(const char *fname, uint8_t **readInStr,
                         uint32_t x, uint32_t y, uint32_t width,
                         uint32_t height){
    using namespace cimg_library;
    assert(*readInStr == NULL);
    assert(fname      != NULL);
    assert(width      != 0);
    assert(height     != 0);
    CImg<uint8_t> img(fname);
    uint64_t SZ = width * height * img.spectrum();
    uint64_t i = 0;
    *readInStr = new uint8_t[SZ];
    for(int32_t x1 = x; x1 < (x + width); x1++){
        for(int32_t y1 = y; y1 < (y + height); y1++){
            for(int32_t c = 0; c < img.spectrum(); c++){
                if(i < SZ){
                    (*readInStr)[i] = img(x1, y1, 0, c);
                    i++;
                }
            }
        }
    }
    return i;
}
