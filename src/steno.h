/** \file steno.h
 * \author Henry J Schmale
 * \date March 5, 2015
 *
 * Contains stenography function prototypes
 */
 
#ifndef STENO_H_INC
#define STENO_H_INC

#include <cstdint>

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
