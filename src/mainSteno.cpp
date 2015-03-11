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

#include "steno.h"
#include "fileHandler.h"

// Program Entry Point
int main(int argc, char **argv){
    uint8_t *infile  = 0, 
            *outfile = 0;
    uint64_t length  = 0;
    switch(argv[1][0]){
    case 'h':                // hide
        
        break;
    case 'r':                // recover
        break;
    case 'a':                // average
        break;
    }
}
