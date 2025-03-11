//* Modifies the volume of an audio file
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//* Number of bytes in .wav header
const int HEADER_SIZE = 44;

//* Function prototype
int error_close_files(FILE *input, FILE *output);

int main(int argc, char *argv[])
{
    //* Check command-line arguments
    if (argc != 4)
    {
        perror("Usage: ./volume input.wav output.wav factor.");
        return 1;
    }

    //* Open files and determine scaling factor
    // Open input file for reading binary
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        perror("Could not open file");
        fclose(input);
        return 1;
    }
    
    // Open output file for writing binary
    FILE *output = fopen(argv[2], "ab");
    if (output == NULL)
    {
        perror("Could not open file");
        error_close_files(input, output);
    }

    // Convert factor to float for better modifying samples
    float factor = atof(argv[3]);

    //* Copy header from input file to output file
    // Pointer to buffer for header
    uint8_t *header_buffer = malloc(HEADER_SIZE);
    if (header_buffer == NULL)
    {
        perror("Could not create header_buffer for header");
        free(header_buffer);
        error_close_files(input, output);
    }

    // Read header from input file
    size_t header_read = fread(header_buffer, HEADER_SIZE, 1, input);
    if (header_read != 1)
    {
        perror("Failed to read header of input file");
        free(header_buffer);
        error_close_files(input, output);
    }

    // Write header to output file
    size_t header_write = fwrite(header_buffer, HEADER_SIZE, 1, output);
    if (header_write != 1)
    {
        perror("Failed to write header to output file");
        free(header_buffer);
        error_close_files(input, output);
    }

    // Free buffer for header
    free(header_buffer);

    //* Read samples from input file and write updated data to output file

    //* Get size of audio data for dynamic memory allocation
    // Subchunk2_size contains information of the size of the audio data
    // Subchunk2_size is located in byte 41-44 in header of wav files
    // Subchunk2_size data type is usually unsigned 4 byte int (or unsigned 32-bit int)
    uint32_t subchunk2_size;

    // Offset the fread position to read only subchunk2_size of header
    fseek(input, 40, SEEK_SET);

    // Get subchunk2_size data
    size_t successful_read = fread(&subchunk2_size, sizeof(subchunk2_size), 1, input);
    if (successful_read != 1)
    {
        perror("Failed to read subchunk2_size of input file");
        error_close_files(input, output);
    }

    // Get number of samples
    size_t sample_num = subchunk2_size / sizeof(int16_t);

    // Pointer to buffer for samples
    int16_t *sample_buffer = malloc(subchunk2_size);

    // Read samples from input file
    size_t samples_read = fread(sample_buffer, sizeof(int16_t), sample_num, input);
    if (samples_read != sample_num)
    {
        perror("Failed to read samples from input file");
        free(sample_buffer);
        error_close_files(input, output);
    }

    // Modify sample data by multiplying to inputted factor
    for (size_t i = 0; i < sample_num; i++)
    {
        sample_buffer[i] = sample_buffer[i] * factor;
    }

    // Write samples to output file
    size_t samples_write = fwrite(sample_buffer, sizeof(int16_t), sample_num, output);
    if (samples_write != sample_num)
    {
        perror("Failed to write samples to output file");
        free(sample_buffer);
        error_close_files(input, output);
    }

    // Free buffer for sample
    free(sample_buffer);

    // Close files
    fclose(input);
    fclose(output);

    return 0;
}

// Function mainly for closing files
int error_close_files(FILE *input, FILE *output)
{
    fclose(input);
    fclose(output);
    exit (1);
}
