#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
int FATSIZE = 512;

int main(int argc, char *argv[])
{
    //Check that input is only 1 argument
    if (argc != 2)
    {
        printf("Only accepts 1 argument\n");
        return 1;
    }

    //Create the file, open it and return an error if not possible
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("File not found.\n");
        return 1;
    }

    //Set up for intake
    int currentJPEG = 0;
    FILE *outputFile = NULL;

    //While not at the end of the file
    while (1)
    {
        //Create an array to store data
        BYTE *buffer = malloc(FATSIZE);

        //Read in file data, close file if finished

        if (fread(buffer, 1, FATSIZE, file) != FATSIZE)
        {
            printf("Successfully reached end of file.\n");
            free(buffer);
            fclose(file);
            fclose(outputFile);
            return 0;
        }

        //Create the filename of the current jpeg being written to
        char filename[8];
        sprintf(filename, "%03i.jpg", currentJPEG);

        //If it's the start of a jpeg file, then close the current file and open another one, increment jpeg counter
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if first file then open a new file named 001.jpg
            if (outputFile == NULL)
            {
                outputFile = fopen(filename, "w");
            }
            // else close existing file and open new one
            else
            {
                fclose(outputFile);
                currentJPEG++;
                sprintf(filename, "%03i.jpg", currentJPEG);
                outputFile = fopen(filename, "w");
            }
        }

        //Deposit the information from the FAT block into the currently open JPEG file
        if (outputFile != NULL)
        {
            fwrite(buffer, 1, FATSIZE, outputFile);
        }

        //Free up memory used for the scan
        free(buffer);
    }

    //Close all files
    fclose(file);
    fclose(outputFile);
    printf("Did not find end of file.\n");
    return 1;
}
