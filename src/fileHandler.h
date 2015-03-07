/** The file handler library
 * \author Henry J Schmale
 * \date March 6, 2015
 */

#ifndef FILE_HANDLER_H_INC
#define FILE_HANDLER_H_INC

#include <cstdint>

/** \brief reads in the entirety of a binary file into a byte array
 * \return number of bytes read in to memory
 * \param fname Name of file to open and read in
 * \param loc Location to write bytes read in, should be a NULL ptr
 *        as memory is allocated to it in this function.
 */
uint64_t readBinFile(const char* fname,
                     uint8_t** loc);

#endif // FILE_HANDLER_H_INC
