#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

bool jpeg_begins(int n, BYTE buffer[n]);

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // open raw file
    FILE  *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }

    // placeholder to file pointer
    FILE *outfile = NULL;

    // buffer is 512 bytes due to FAT file system
    BYTE *buffer = malloc(sizeof(BYTE) * 512);
    int filecount = -1;

    while (1)
    {
        // read 512 bytes
        fread(buffer, sizeof(buffer), 1, file);

        // break from loop if reached end of file
        if (feof(file))
        {
            break;
        }

        // check if beginning of jpeg file
        if (jpeg_begins(sizeof(buffer), buffer))
        {
            // close previous file, if any
            if (outfile != NULL)
            {
                fclose(outfile);
            }

            // open new output file
            filecount++;
            char outfilename[8]; // ###.jpg
            sprintf(outfilename, "%03d.jpg", filecount);
            outfile = fopen(outfilename, "w");
        }

        // write buffer to output file
        if (outfile != NULL)
        {
            fwrite(buffer, sizeof(buffer), 1, outfile);
        }

    }

    // free memory
    free(buffer);
    // close last output file
    fclose(outfile);
    // close raw file
    fclose(file);

    return 0;

}

// Returns true if buffer content indicates beginning of a jpeg file.
// @param n         length of buffer
// @param buffer    buffer of bytes of length n
// @returns         boolean
bool jpeg_begins(int n, BYTE buffer[n])
{
    // Check first four bytes
    if (buffer[0] == 0xff &&
        buffer[1] == 0xd8 &&
        buffer[2] == 0xff &&
        (buffer[3] & 0xf0) == 0xe0)
    {
        return true;
    }
    return false;
}