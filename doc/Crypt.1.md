% CRYPT(1) Cryptograhy tool of ImageCrypt Toolkit
% Henry J Schmale
% March 11, 2015

# NAME

Crypt - cryptography tool in the ImageCrypt Toolkit

# SYNOPSIS

Crypt [*e|d*] [*input-file*] [*output-file*] [*key*]

# DESCRIPTION

A basic XOR rotate cipher using an n-bit key. It can encrypt and
decrypt any file, and is completely portable so long as endianess
of the destination system is the same as the current system.

To encrpyt a file using a given key use the `e` option:

    Crypt e SecretMessage.txt encrypted.txt QWop123ADSF

To decrypt a file, the user must know the key it was originally
encrypted with and use the `d` option.

    Crypt d encrypted.txt SecretMessage.txt QWop123ADSF

In the above examples the key was `QWop123ADSF`, this key needs
to be known in order to decrypt the message. Addionally, this key
can be of N-length. Preferably greater than 1.
