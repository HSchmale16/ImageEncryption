/** \file steno.h
 * \author Henry J Schmale
 * \date March 5, 2015
 *
 * Contains stenography function prototypes
 */
 
#ifndef STENO_H_INC
#define STENO_H_INC

#include <cstdint>
#include <cassert>

struct rgbPX{
    uint8_t *m_c;
    
    static const int RED   = 0; //!< Array Index of red componet
    static const int GREEN = 1; //!< Array Index of green componet
    static const int BLUE  = 2; //!< Array Index of blue componet

    // default ctor
    rgbPX(){ m_c = new uint8_t[3]; }

    rgbPX(uint8_t r, uint8_t g, uint8_t b)
        :rgbPX(){
        m_c[0] = r;
        m_c[1] = g;
        m_c[2] = b;
    }

    ~rgbPX(){
        delete[] m_c;
    }

    void operator()(uint8_t r, uint8_t g, uint8_t b){
        m_c[0] = r;
        m_c[1] = g;
        m_c[2] = b;
    }

    uint8_t& operator[](const int i){
        assert((i >= 0) && (i < 3));
        return m_c[i];
    }
};

void writeOutToImage(const char * fname, uint8_t *data, uint64_t lenData);

/** \brief Reads in data from image. 
 * \return The total ammount of memory allocated in
 * \param fname the name of the file read in.
 * \param readInStr - The pointer to readin to at. This ptr is allocated
 * in this function, so the param passed should be a NULL ptr.
 * \note The parameter `readInStr` should be a null pointer, as this
 * will allocate the memory for it to use.
 */
uint64_t readInFromImage(const char *fname, uint8_t **readInStr);

#endif // STENO_H_INC
