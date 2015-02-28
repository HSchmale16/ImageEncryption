/** A test of dynmaic memory allocation
 * \author Henry J Schmale
 * \date February 28, 2015
 */

// #include <cstdint>
#include <cassert>
#include <cstdlib>
#include <cstdio>

typedef unsigned char uint8_t;

void allocMem(uint8_t **i){
    *i = new uint8_t[1000];
    for(int j = 0; j < 1000; j++){
        printf("%d\n", (*i)[j]);
        //*i[j] = j * 2;
    }
}

int main(){
    uint8_t *i = 0;
    allocMem(&i);
    assert(i != NULL);
    delete[] i;
}
