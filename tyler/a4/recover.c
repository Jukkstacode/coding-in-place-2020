#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCKLEN 512
typedef uint8_t BYTE;
typedef uint32_t SIGNATURE;

void byteShift(BYTE bytes[4]);

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: recover infile\n");
        return 1;
    }
    
    // Remember filename
    char *infile = argv[1];
    
    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }
    
    fseek(inptr, 0L, SEEK_END);
    uint64_t size = ftell(inptr);
    fseek(inptr, 0L, SEEK_SET);
    // printf("file length: %lu\n", size);
    
    // BYTE  = calloc(height, width * sizeof(RGBTRIPLE));
    BYTE block[BLOCKLEN];
    BYTE bytes[4] = { 0, 0, 0, 0};
    SIGNATURE sig = (bytes[0]<<24) | (bytes[1]<<16)| (bytes[2]<<8) | bytes[3];
    SIGNATURE tail;
    int fileCount = 0;
    int count = 0;
    bool haveSig = false;
    bool fileOpen = false;
    FILE *outptr;
    
    while (count < size + 1)
    {
        if (!haveSig)
        {
            while ((sig < 0xffd8ffe0 || sig > 0xffd8ffe9) && count < size + 1)
            {
                byteShift(bytes);
                fread(&bytes[3], sizeof(BYTE), 1, inptr);
                sig = (bytes[0]<<24) | (bytes[1]<<16)| (bytes[2]<<8) | bytes[3];
                count++;
            }
            
            bytes[0] = bytes[1] = bytes[2] = bytes[3] = 0;
            
            if ( sig >= 0xffd8ffe0 && sig <= 0xffd8ffe9 )
            {
                fseek(inptr, -4, SEEK_CUR);
                count-=4;
                haveSig = true;
                // printf("got it: %u: 0x%.8x, count: %d\n", sig, sig, count);
            }
            // fread(block, sizeof(BYTE), BLOCKLEN, inptr);
            fread(block, sizeof(BYTE), BLOCKLEN, inptr);
            count+=BLOCKLEN;
        }
        else
        {
            if (fileOpen)
            {
                do
                {
                    fwrite(block, sizeof(BYTE), BLOCKLEN, outptr);
                    fread(block, sizeof(BYTE), BLOCKLEN, inptr);
                    count+=BLOCKLEN;
                    sig = (block[0]<<24) | (block[1]<<16)| (block[2]<<8) | block[3];
                    tail = (block[BLOCKLEN-4]<<24) | (block[BLOCKLEN-3]<<16)| (block[BLOCKLEN-2]<<8) | block[BLOCKLEN-1];
                }
                // while ((sig < 0xffd8ffe0 || sig > 0xffd8ffe9 || sig == 0 || tail == 0) && count < size - BLOCKLEN);
                while ((sig < 0xffd8ffe0 || sig > 0xffd8ffe9) && count < size + 1);
                // printf("file %d closing, count: %d\n", fileCount-1, count);
                // printf("head: 0x%.8x, tail: 0x%.8x\n", sig, tail);
                fclose(outptr);
                fileOpen = false;
                if (sig < 0xffd8ffe0 || sig > 0xffd8ffe9)
                {
                    // printf("Here, count: %d\n", count);
                    fseek(inptr, -1*BLOCKLEN, SEEK_CUR);
                    count-=BLOCKLEN;
                    haveSig = false;
                }
            }
            else
            {
                // printf("file %d opening, count: %d\n", fileCount, count);
                char fName[8];
                sprintf(fName, "%.3d.jpg",fileCount);
                // printf("Opening: %s\n", fName);
                outptr = fopen(fName, "w");
                if (outptr == NULL)
                {
                    fclose(inptr);
                    fprintf(stderr, "Could not create %s.\n", fName);
                    return 1;
                }
                fileCount++;
                fileOpen = true;
            }
        }
    }
    
    if (fileOpen)
    {
        fclose(outptr);
    }
    
    
    // int count = 0;
    // while (sig < 0xffd8ffe0 || sig > 0xffd8ffe9)
    // {
    //     byteShift(bytes);
    //     fread(&bytes[3], sizeof(BYTE), 1, inptr);
    //     sig = (bytes[0]<<24) | (bytes[1]<<16)| (bytes[2]<<8) | bytes[3];
    //     count++;
    // }
    // printf("%d: 0x%.8x, count: %d\n", sig, sig, count);
    
    // fseek(inptr, -4, SEEK_CUR);
    
    // fread(block, sizeof(BYTE), BLOCKLEN, inptr);
    
    // // printf("0x%.2x%.2x%.2x%.2x, 0x%.2x\n", block[0], block[1], block[2], block[3], block[BLOCKLEN-1]);
    // // Open output file
    // FILE *outptr = fopen("000.jpg", "w");
    // if (outptr == NULL)
    // {
    //     fclose(inptr);
    //     fprintf(stderr, "Could not create %s.\n", "000.jpg");
    //     return 5;
    // }
    
    // SIGNATURE tail;
    
    // do
    // {
    //     fwrite(block, sizeof(BYTE), BLOCKLEN, outptr);
    //     fread(block, sizeof(BYTE), BLOCKLEN, inptr);
    //     sig = (block[0]<<24) | (block[1]<<16)| (block[2]<<8) | block[3];
    //     tail = (block[BLOCKLEN-4]<<24) | (block[BLOCKLEN-3]<<16)| (block[BLOCKLEN-2]<<8) | block[BLOCKLEN-1];
    // }
    // while ((sig < 0xffd8ffe0 || sig > 0xffd8ffe9 || sig == 0 || tail == 0));
    
    // printf("head: 0x%.8x, tail: 0x%.8x\n", sig, tail);
    
    
    
    // for (int i = 0; i < 40; i++)
    // {
    //     fread(&b1, sizeof(BYTE), 1, inptr);
    //     printf("%.3d: 0x%.2x\n", b1, b1);
    // }
    fclose(inptr);
}

void byteShift(BYTE bytes[4])
{
    for (int i = 0; i < 3; i++)
    {
        bytes[i] = bytes[i + 1];
    }
}