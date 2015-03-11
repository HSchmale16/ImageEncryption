# Image Encrypter #
A set of tools to assist with hiding data inside of images.

It is an interesting concept to hide messages inside of images, and
that is why I created this project.

This project includes three build targets which cover each aspect of
the program. There is a stenography only binary, cryptography only
binary, and combined binary. There are man pages written in markdown
format for each utility in the `doc/` directory. The man pages can
be generated using `pandoc` or any other tool to convert markdown
to man page format. 

# Cryptography #
There is a limited cryptography program in place to encrypt messages
using a simple XOR rotation cipher. This can be used before placing a
message inside of an image, but not after.


