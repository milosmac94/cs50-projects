// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{

    int n = atoi(argv[1]);

    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize factor infile outfile\n");
        return 1;
    }

    if (n > 100 || n < 0)
    {
        fprintf(stderr, "Resizing factor must be a positive integer less than or equal to 100\n");
        return 2;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine padding for original image
    int smallPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // save small width and height and increase width and height
    int smallWidth = bi.biWidth;
    int smallHeight = bi.biHeight;

    bi.biWidth *= n;
    bi.biHeight *= n;

    // determine padding for resized image
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // increase image size and bitmap file size
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // temporary storage
    RGBTRIPLE triple;

    // iterate over infile's scanlines
    for (int i = 0; i < abs(smallHeight); i++)
    {
        // iterate n-1 times to scale vertically with rewind
        for (int j = 0; j < n-1; j++)
        {
            // iterate through scanline horizontally
            for (int k = 0; k < smallWidth; k++)
            {
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write multiplied RGB triple to outfile scanline
                for (int l = 0; l < n; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // add padding, if any, to outfile
            for (int m = 0; m < padding; m++)
            {
                fputc(0x00, outptr);
            }

            // rewind the inpointer to the beginning to copy scanline to new row
            fseek(inptr, -(smallWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
        }

        // copy vertical scanline n-th time without rewinding to move to next scanline in infile
        for (int o = 0; o < smallWidth; o++)
        {
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write multiplied RGB triple to outfile scanline
            for (int p = 0; p < n; p++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }
        // add padding, if any, to outfile
        for (int m = 0; m < padding; m++)
        {
            fputc(0x00, outptr);
        }

        //skip over infile padding
        fseek(inptr, smallPadding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
