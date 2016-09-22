/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    
    uint8_t buffer[512];
    const int BLOCK_SIZE = 512;
    
    FILE *file = fopen("card.raw", "r"); //open given raw file
    if (file == NULL)
    {
        fclose(file);
        printf("cannot open");
        return 1;
    }
    
    FILE *out = NULL;
    int counter = 0; //initialize counter    
    while (fread(buffer, BLOCK_SIZE, 1, file))
    {
        //check if file is jpg
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && (buffer[3] >= 0xe0) && (buffer[3] <= 0xef)) 
        {
            // close the file, if it is opened
            if (out != NULL)
                fclose(out);
            //create file title
            char title[8];
            sprintf(title, "%03d.jpg", counter); 
            
            //open outfile for writing
            out = fopen(title, "w");
            counter++;
        }
        
        if (out != NULL)
            fwrite(buffer, BLOCK_SIZE, 1, out); //write the buffer into file
    }
            
    if (out != NULL)
        fclose(out);
        
    fclose(file);
    
    return 0;
}

