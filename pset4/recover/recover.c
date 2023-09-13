#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
 
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        // if the wrong number of arguements is supplied...
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    // open the file
    // and declare the future output file. This ensures it can be accessed throughout main(). 
    // and declare the buffer that will hold the block of data. 
    FILE *file = fopen(argv[1], "r");
    
    FILE *img;
    
    BYTE buffer[512];
    
    int number_found = 0;
    
    while (fread(buffer, sizeof(BYTE), 512, file) == 512)
    {
    
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // found a jpeg
            number_found++;
            char filename[] = "###.jpg";
            sprintf(filename, "%03i.jpg", number_found - 1);
            
            if (number_found == 1)
            {
                ;  // do nothing, no file to close
            }
            else
            {
                fclose(img);
            }
            img = fopen(filename, "w");
            
            fwrite(buffer, sizeof(BYTE), 512, img);
        }
        else  // if it's not the start of a jpeg....
        {
            if (number_found > 0)
            {
                // fwrite to the jpeg
                fwrite(buffer, sizeof(BYTE), 512, img);
            }
        }
    }
    fclose(img);
}