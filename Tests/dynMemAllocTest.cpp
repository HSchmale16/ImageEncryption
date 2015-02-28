/** A test of dynmaic memory allocation
 * \author Henry J Schmale
 * \date February 28, 2015
 */

// #include <cstdint>
#include <cassert>

typedef unsigned char uint8_t;

void allocMem(uint8_t **i){
    *i = new uint8_t[10];
}

int main(){
    uint8_t *i = 0;
    allocMem(&i);
    assert(i != 0);
    delete[] i;
}
