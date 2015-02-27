# Image Encrypter #
Encrypts a file and hides it inside of an image. Encryption is handled
by simple xor shift cipher.

ImageEncrypt \<e\|d\> \<infile\> \<outfile\> \<key\>

## Parameters ##
e - Encrypt the given file  
d - Decrypt the given file  

* \<infile\> The file to read in to encrypt/decrypt
* \<outfile\> The file to write out to. This file should have an image
  file extension, and the extension should denote a lossless image
  format, such as PNG or BMP.
* \<key\> The key to use in encrypting the file, the encryption is as
  secure as the length of the key.

## Notes ##
* The eventual goal of this program is to hide the data in a fractal like
  form.
* This is a really simple xor shift cipher.
* The generated image looks like random line noise, it would be better if
  it looked like artwork that is kind of fractal based or a set of
  concentric circles. 
