# Questions

## What's `stdint.h`?

A C library from Microsoft that hosts common data types.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

These primitive types define the *exact size in bits* of a data type created for a program. They also define if that created data type is signed or unsigned.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

- BYTE = 1 byte
- DWORD = 4 bytes
- LONG = 4 bytes
- WORD = 2 bytes


## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

bfType indicates the file type, is two bytes and will always be **BM**.

BM represented in other ways:
* BM ASCII Chars = 'BM'
* BM in Decimal = '66 77'
* BM in Hexadecimal = '42 4D'
* BM in Binary = '01000010 01001101'

## What's the difference between `bfSize` and `biSize`?

bfSize represents the size, in bytes, of the bitmap file as a whole: both header structures and the total of all `RGBTRIPLE` structures. 

biSize represents the size, in bytes, of the header structure `BITMAPINFOHEADER`, which is always 40 bytes.

## What does it mean if `biHeight` is negative?

If biHeight is negative, the bitmap is oriented top down, and the origin point is in the top left corner, as in normal text. 

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount indicates the color depth. Discrete options are 0, 1, 4, 8, 16, 32, 64.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

fopen will return NULL if the command line arguments passed in at `argv[1]` and `argv[2]` are not formatted as file names, so `fopen` will be unable to open them and return a pointer to nothing (ie. a `NULL` pointer).

## Why is the third argument to `fread` always `1` in our code? (For example, see lines 40, 44, and 75.)

Because the program only ever needs to read one unit of memory the size of each header in order to get all of the information. A quantity value greater than one would read too large a part of the file, and also would not fit into the buffer we have created above. 

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

It will assign 3 to padding, `RGBTRIPLE` == 3, math below:
```
    pad = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
        = (4 - (3 * 3)) % 4) % 4;
        = (4 - 9 % 4) % 4;
        = (3) % 4;
    pad = 3;
```
## What does `fseek` do?

`fseek` sets a file position by changing the location of a file pointer. It takes three arguments: 
`int fseek(FILE* fp, long int offset, int from_where);`
`FILE* fp` = choose which file pointer to adjust
`long int offset` = number of bytes to adjust the position of the pointer (positive or negative values accepted)
`int from_where` = location to start adjustment from: `SEEK_CUR` sets location at current position, `SEEK_END` sets the location at the end of the file, `SEEK_SET` sets the location at the beginning of the file

Returns 0 on success and !0 on failure.

Example from `copy.c`:

`fseek(inptr, padding, SEEK_CUR);`
Pointer = `inptr`
Adjustment = value of int `padding`
Starting location = `SEEK_CUR`, the current location of the pointer

## What is `SEEK_CUR`?

Within `fseek`, sets the location to begin the adjustment to the **current** location of the pointer.
