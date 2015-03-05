/** \file crypto.h
 * \author Henry J Schmale
 * \date March 5, 2015
 *
 * Contains Crypto Function Prototypes and various inline functions
 * used for encryption.
 */
 
#ifndef CRYPTO_H_INC
#define CRYPTO_H_INC

#include <cstdint>
#include <climits>
 
/** \brief rotates a variables bits right n pos then returns that
 * \note n is 8 bits only because no standard type in C has more than
 * 64 bits, 8 bits is more than sufficent for this purpose.
 * \return x rotated right n posistions
 */
template<typename TYP>
TYP rotateRight(TYP x, uint8_t n){
    return (x >> n) | (x << ((sizeof(x) * CHAR_BIT) - n));
}

/** \brief rotates a variables bits left n pos then returns the new value
 * \note n is 8 bits only because no standard type in C has more than
 * 64 bits, 8 bits is more than sufficent for this purpose.
 * \return x rotated right n posistions
 */
template<typename TYP>
TYP rotateLeft(TYP x, uint8_t n){
    return (x << n) | (x >> ((sizeof(x) * CHAR_BIT) - n));
}

void encryptString(const uint8_t *KEY, uint16_t keyLen, uint8_t *instr,
                   uint64_t inlen, uint8_t *outstr, uint64_t outlen);

void decryptString(const uint8_t *KEY, uint16_t keyLen, uint8_t *instr,
                   uint64_t inlen, uint8_t *outstr, uint64_t outlen);
                   
#endif // CRYPTO_H_INC
