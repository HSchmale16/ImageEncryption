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
#include <cstdlib>
#include <cmath>

typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

const uint32_t MIN_MESG_LEN = 255; //!< Minimum Mesg Length

struct imgDims{
    uint64_t m_width;
    uint64_t m_height;

    imgDims(){
        m_width = 0;
        m_height = 0;
    }

    imgDims(uint64_t x){
        m_width = x;
        m_height = x;
    };
};

uint32_t calcTests(uint64_t x){
    return round(0.25 * sqrt(x));
}

imgDims calcDims(uint64_t area){
    if(area < MIN_MESG_LEN){
        printf("The given mesg length is too short.\n");
        exit(0);
    } 
    uint64_t factor1 = 0;     // a factor that works used to calc factor2
    uint32_t workFactors = 0; // factors that work
    imgDims dims;
    if(uint64_t(sqrt(area) * sqrt(area)) == area){
        dims.m_width = sqrt(area);
        dims.m_height = sqrt(area);
        goto testValues;
    }

    // brute force test
    for(uint64_t i = 2; i < (area * .75); i++){
        if(area % i == 0){
            workFactors++;
            factor1 = i;
            if((((double)(area % factor1)/(double)(factor1)) > .999)
              && (area % factor1 == 0)){
                printf("Found a better set\n");
                break;
            }
        }
        // fail condition
        if((i == (area - 1)) && (factor1 == 0)){
            printf("The mesg length is prime, this will never do!\n");
            exit(0);
        }
    }
    dims.m_width  = area / factor1;
    dims.m_height = factor1;
    
testValues:
    // check sum
    if((dims.m_width * dims.m_height) != area){
        printf("The calculated width and height does not multiply to area\n");
        exit(0);
    }
    return dims; 
}

int main(){
    using namespace std;
    uint64_t i;
    cin >> i;
    imgDims d = calcDims(i);
    cout << d.m_width << ", " << d.m_height << std::endl;
}
