// program recovers JPEG files from .raw file

#define FAT_BLOCK 512

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover file.ext\n");
        return 1;
    }

    // open input file and verify it exists
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    // allocate memory for a temporary buffer
    unsigned char buffer[FAT_BLOCK];

    // declare counter to count JPEGs
    int counter = 0;

    //declare filename char array
    char filename[8];

    // read 512 bytes from the card and check if EOF
    while (fread(&buffer, 1, FAT_BLOCK, inptr))
    {
        // detect beginning of JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // give JPEG a name, per convention
            sprintf(filename, "%03i.jpg", counter);

            //open the JPEG for writing
            FILE *img = fopen(filename, "w");

            // increase counter when JPEG found
            counter++;

            // write buffer blocks into JPEG file until new JPEG header is found
            do
            {
                fwrite(&buffer, 1, FAT_BLOCK, img);

                // check if EOF to prevent infinite do-while loop on last JPEG
                if (fread(&buffer, 1, FAT_BLOCK, inptr) < 512)
                    break;
            }
            while ((buffer[0] != 0xff || buffer[1] != 0xd8 || buffer[2] != 0xff || (buffer[3] & 0xf0) != 0xe0));

            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                // return input file pointer backwards one block to avoid skipping over beginning of next JPEG
                fseek (inptr, -(FAT_BLOCK), SEEK_CUR);
            }

            // close current JPEG
            fclose(img);
        }

    }

    // close card.raw
    fclose(inptr);

    // success
    return 0;
}