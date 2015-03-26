/* Stenography
 * \author Henry J Schmale
 * \date February 25, 2015
 * \file mainSteno.cpp
 *
 * This file contains the main function to demonstrate
 * the stenography system.
 *
 * USAGE:
 * argv[0] <h|r|a> <input file> <output file> [<x> <y> <width> <height>]
 *
 * 1. <h|r|a>
 *    * h - hide, data inside of an image
 *    * r - recover, data inside of an image
 *    * a - average, determine pixel value averages in region specified
 * 
 * 2. <input file>
 *    
 *    File to read from
 *
 *    if (r) is specified then it should be an image file else a txt file
 *    
 *    \note file extensions are not currently verified.
 * 
 * 3. <output file>
 *    
 *    File to output to
 *    
 *    if (h) is specified then this should have an image file extension
 *
 * 4. [<x> <y> <width> <height>] Region in image to use
 *    
 *    data written out to the image must be able to fit into this region
 *    if specified.
 *
 *    <x>      - x posisition inside of the image  
 *    <y>      - y posisition inside of the image
 *    <width>  - +x region to fill in
 *    <height> - +y region to fill in   
 */

#include <cstdio>                      // Printf is awesome
#include <iostream>                    // For stdio I/O opps
#include "steno.h"                     // Declarations of funcs
#include "fileHandler.h"               // File Handling Subsystem

using namespace std;

// Program Entry Point
int main(int argc, char **argv){
    uint8_t *infile  = 0, 
            *outfile = 0;
    uint64_t length  = 0;
    if(argc < 4){
        cerr << "Up! You darn screwed up and didn't pass enough args to the "
                "program." << endl;
        cerr << argv[0] 
             << "<h|r|a> <infile> <outfile> [<x> <y> <width> <height>]"
             << endl;
        goto fail;
    }
    length  = readBinFile(argv[2], &infile);
    if(infile == NULL){
        cerr << "Error Loading File: " << argv[2] << endl;
        goto fail;
    }
    outfile = new uint8_t[length];
    switch(argv[1][0]){
    case 'h':                // hide
        break;
    case 'r':                // recover
        break;
    case 'a':                // average
        uint64_t sum[3] = {0};
        for(uint64_t i = 0; i < length; i++){
            uint8_t val = i % 3; // RGB Pixel Channels
            if(val == 0){
                sum[2] += infile[i];
            }else if(val == 1){
                sum[1] += infile[i];
            }else{
                sum[0] += infile[i];
            }
        }
        printf("Average Value of Message: %d, %d, %d\n",
               sum[0], sum[1], sum[2]);
        break;
    }
fail:
   delete[] infile;
   delete[] outfile;
   return 0; 
}
