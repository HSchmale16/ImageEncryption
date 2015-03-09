/** \file steno.h
 * \author Henry J Schmale
 * \date March 5, 2015
 *
 * Contains stenography function prototypes and struct declarations
 */
 
#ifndef STENO_H_INC
#define STENO_H_INC

#include <cstdint>
#include <cassert>

/** \brief An RGB Pixel Struct for 24 bit color
 */
struct rgbPX{
    uint8_t *m_c; //!< Array to hold componet values
    
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


/** \brief calculates RGB Pixel value averages for a given data set.
 * \param str     The data set to use
 * \param sz      The length of data set.
 */
rgbPX calcArray_rgbPxAvg(uint8_t *str, uint64_t sz);

/** \brief writes out to an image file the data specified
 * \param fname   Name of file to write out to
 * \param data    The data write out to the file
 * \param lenData the length of the data ptr to write out
 */
void writeOutToImage(const char *fname, uint8_t *data, uint64_t lenData);

/** \brief writes out pixel data to a specific part of an image.
 * \param fname   Name of file to write out
 * \param data    The data to write out
 * \param lenData Data Length
 * \param x       x posisition
 * \param y       y posisition
 * \param width   width of section to write to
 * \param height  height of section to write to
 */
void writeOutToImage(const char *fname, uint8_t *data, uint64_t lenData,
                     uint32_t x, uint32_t y, uint32_t width,
                     uint32_t height);

/** \brief Reads in data from image. 
 * \return The total ammount of memory allocated to readInStr
 * \param fname the name of the file read in.
 * \param readInStr - The pointer to readin to at. This ptr is allocated
 * in this function, so the param passed should be a NULL ptr.
 * \note The parameter `readInStr` should be a null pointer, as this
 * will allocate the memory for it to use.
 */
uint64_t readInFromImage(const char *fname, uint8_t **readInStr);

/** \brief Reads data in to a cstring from an image file with bounds specified
 * \return The total amount of memory allocated to readInStr
 * \param fname     The file name to open
 * \param readInStr Where to put the read in data, should be a NULL ptr
 * \param x         X-axis posisition
 * \param y         Y-axis posisition
 * \param width     Width of the bounded area
 * \param height    Height of the bounded area
 */
uint64_t readInFromImage(const char *fname, uint8_t **readInStr,
                        uint32_t x, uint32_t y, uint32_t width,
                        uint32_t height);

#endif // STENO_H_INC
