# Image Encrypter #
Encrypts a file and hides it inside of an image. Encryption is handled
by simple xor shift cipher.

ImageEncrypt \<e\|d\> \<infile\> \<outfile\> \<key\>

## First Param ##
e - Encrypt the given file  
d - Decrypt the given file  

* \<infile\> The file to read in to encrypt/decrypt
* \<outfile\> The file to write out to. This file should have an image
  file extension.
* \<key\> The key to use in encrypting the file
