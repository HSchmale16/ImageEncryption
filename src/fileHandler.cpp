/** The file handler library implementation
 * \author Henry J Schmale
 * \date March 6, 2015
 */

#include "fileHandler.h"
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <ios>

using namespace std;

uint64_t readBinFile(const char* fname, uint8_t** data){
    assert(fname != NULL);
    assert(*data  == NULL);
    fstream infile(fname,
                   ios::in | ios::binary | ios::ate);
    uint64_t fileSZ;
    if(infile.is_open()){
        fileSZ = infile.tellg();
        *data = new uint8_t[fileSZ];
        infile.seekg(0, ios::beg);
        if(!infile.read((char*)*data, fileSZ)){
            // FAIL
            delete[] *data;
        }
    }
    infile.close();
    return fileSZ;        
}

void writeBinFile(const char* fname, uint8_t* data, uint64_t length){
    assert(fname != NULL);
    assert(data  != NULL);
    fstream outfile(fname, ios::out | ios::binary);
    if(outfile.is_open()){
        for(uint64_t i = 0; i < length; i++){
            outfile << data[i];
        }
    }
    outfile.close();
}
