#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Only two words
    if (argc != 2)
    {
        return 1;
    }
    // Open file
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return 1;
    }
    // File is not empty
    if (file == NULL)
    {
        return 2;
    }

    // create new data type
    typedef uint8_t BYTE;
    // Array of bytes - 512Bytes chunk
    BYTE buffer[512];
    char filename[8];
    FILE *img;

    int count = 0;
    // Loop whith condition, which already open every 512B chunk
    while (fread(buffer, 512, 1, file) == 1)
    {
        // Checking first 4 bytes of chunk, if chunk is begining of new jpeg file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // create new jpg file
            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "w");
            //write to jpg file
            fwrite(buffer, 512, 1, img);
            count++;
        }
        // No the begining of jpg
        else
        {
            // check if at least one jpg is created
            if (count > 0)
            {
                fwrite(buffer, 512, 1, img);
            }
        }
    }
    // Close file
    fclose(file);
}