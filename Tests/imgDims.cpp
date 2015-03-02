/** \file imgDims.cpp
 * \author Henry J Schmale
 * \date March 1, 2015
 *
 * A test of image dimensioning algorithims
 * 
 * \note this probably won't work for small mesg lengthes where
 * length < 255.
 */

#include <iostream>
#include <cstdio>
#include <cstdlb>

typedef unsigned int uint32_t;


const uint32_t MIN_MESG_LEN = 255; //!< Minimum Mesg Length

struct imgDims{
    uint32_t m_width;
    uint32_t m_height;

    imgDims(){
        m_width = 0;
        m_height = 0;
    }
}


imgDims calcDims(uint32_t area){
    if(area < 
    imgDims dims;
    uint32_t workFactors = 0; // factors that work
    uint32_t factor1 = 0;     // a factor that works used to calc factor2
    for(uint32_t i = 2; i < area; i++){
        if(area % i == 0){
            workFactors++;
            factor1 = i;
            if(workFactors > 5){
                break;
            }
        }
        if((i == (area - 1)) && (factor1 == 0){
            printf("The mesg length is prime, this will never do");
            exit(0);
        }
    }
     
    return dims; 
}

int main(){

}
