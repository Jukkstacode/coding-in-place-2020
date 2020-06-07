#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

typedef uint8_t BYTE;


int main(int argc, char *argv[])
{
    //check if the user used the command line arguments correctly
    if (argc != 2)
    {
        printf("Error: Enter command ./ [file]\n");
        return 1;
    }

    //check if the file is there
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not find file\n");
        return 1;
    }

    //create the buffer that the data stream will be read into
    BYTE buffer[512];

    //create a bool to track whether you've found a jpeg
    bool jpeg_found = false;

    //Initialize the output file
    FILE *output = NULL;

    //counter for filename increments
    int count = 0;

    //read the contents of the file into the buffer 512 bytes wide
    //exits the while loop once the end of the file is reached (all zeros)
    while (fread(buffer, 512, 1, input))
    {
        //every time it finds a new jpeg header it creates a new file to see if the first four bytes are jpeg bytes
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //set jpeg found to true once found
            if (!jpeg_found)
            {
                jpeg_found = true;
            }
            else
            {
                fclose(output);
            }
            //create an array for the new filename
            char filename[8];
            
            //store the incremented file name in the character array the filename using sprintf
            sprintf(filename, "%03i.jpg",count);
            
            //increment the count for the next photo
            count++;
            
            //open an empty file
            output = fopen(filename, "w");
            
            //start writing the data into the file block by block
            fwrite(buffer, 512, 1, output);
        }
        else if (jpeg_found)
        {
            //keep writing the file
            fwrite(buffer, 512, 1, output);
        }
    }
    fclose(output);
    fclose(input);
}

