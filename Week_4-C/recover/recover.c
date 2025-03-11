//* RECOVERY.C
/**
 * recover.c -> JPEG Recovery Tool
 * Version:     1.1
 * Creation:    January 29, 2025
 *
 * Creator:     Amjko
 *
 * Purpose: Recovers deleted JPEG files from a camera's memory card
 *          by scanning for JPEG signatures in the raw data.
 * 
 * Problem Source: https://cs50.harvard.edu/x/2025/psets/4/recover/
 *
 * Familiarized used terms in comments:
 * BLOCK -> 512B FAT file system of cameras' memory card.
 *          Similar to a grid of memory, each square
 *          containing 512 bytes of memory.
 *
 * file.raw -> Refers to the memory card, using a .raw
 *             file to access the data of the card.
 *
 * JPEG Signatures -> JPEG files contain signatures at
 *                    the beginning represented as
 *                    hexadecimal values, which are:
 *                    0xff, 0xd8, 0xff, <0xe0 -> 0xef>
 *
 * JPEG -> Refers to the .jpeg image in which every JPEG
 *         file contains JPEG signatures, followed by
 *         the data of the image (the pixels shown).
 *
 *
 * How it works:
 *   -> It checks each BLOCK for JPEGs' signatures at the beginning of
 *      the BLOCK, for JPEG signatures are block-aligned. After it has
 *      found a JPEG signature (series of hexadecimals), it will create
 *      a .jpeg file for writing the data of the pixels. Since JPEG
 *      signatures are block-aligned, to know if a .jpeg image has
 *      ended, is if it has found a new JPEG signature.
 *      All of the .jpeg files created will contain a counter (represent
 *      the ith index of .jpeg file created) as their file name.
 */

#include <sys/stat.h>
#include <errno.h>
#include <math.h>
#include "LOG.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Definitions
 * ----------
 * @BLOCK:     FAT file system of 512 bytes per block
 * @jpeg_char: An integer for amount of characters in JPEG file names
 */
#define BLOCK 512
#define jpeg_char 8

/**
 * Directory
 * --------
 * Directory for where recovered images will be stored
 * 
 * Note: "recovered_images" is the default directory name
 *       Switch the commented defined RECOVERY_DIR for
 *       a custom directory name
 */
#define RECOVERY_DIR "recovered_images"
// #define RECOVERY_DIR "custom_directory"

/**
 * Error Macro
 * ----------
 * Automatically includes line number in stderr prints
 * 
 * @param msg:   Message to error and log
 * @param err:   Error number 
 * 
 * Usage: error("Failed operation", errno/EINVAL/...)
 */
#define error(msg, err) error_message(msg, err, __LINE__)

/**
 * Global Variables
 * --------------
 * @jpeg_num:    Index for JPEG file names
 * @EXIT_STATUS: Exit status (number) of the program
 * @name_length: Length of the JPEG files name to be malloc'ed
 * @fat_block:   Buffer for storing a BLOCK (512 B)
 * @memory_card: Variable for opening .raw file
 * @jpeg_file:   Variable for creating JPEG files
 */
int jpeg_num = 0;
int EXIT_STATUS = 0;
size_t name_length = 0;
unsigned char *fat_block = NULL;
FILE *memory_card = NULL;
FILE *jpeg_file = NULL;

/**
 * Function Prototypes
 * ------------------
 * @error_message() -> For printing and logging errors
 * @get_nameJPEG()  -> To convert jpeg_num into a string
 * @match_sigJPEG() -> Check if first four bytes matches JPEGs' signatures
 */
void error_message(const char *msg, int err, int line);
char *get_nameJPEG(int index);
bool match_sigJPEG(unsigned char *buffer);

/**
 * main() -> Starts the JPEG recovery program
 * 
 * @param argc: Amount of command-line arguments
 * @param argv: Array storing command-line arguments as elements
 * 
 * Usage: ./recover [file_name.raw]
 * 
 * Return: EXIT_STATUS int will be returned
 *         EXIT_STATUS will be nonzero if an error occurred
 * 
 * Note: Automatically replaces previous "program.log" log file
 *       Does not contain the following features:
 *       - Recovery from corrupted blocks 
 *       - Ability to skip bad sectors
 */
int main(int argc, char *argv[1])
{
    /**
     * Delete previous log_file if exists
     * 
     * It will only delete the previous log file if both the previous
     * and current log file used is the default LOG_FILE
     * Meaning LOG_FILE was not defined before inclusion of "LOG.h"
     */
    FILE *log_exist = fopen(LOG_FILE, "r");
    if (log_exist)
    {
        size_t delete_log = remove(LOG_FILE);
        if (delete_log != 0)
        {
            error("Failed to delete previous log file", errno);
            LOG(LOG_WARNING, "Failed to delete previous log file");
            LOG(LOG_WARNING, "Logging to previous log file...");
        }

        fclose(log_exist);
    }

    LOG(LOG_INFO, "Program started");

    /**
     * Command-line argument validity check
     * 
     * Only accept one command-line argument after "./recover"
     * Correct usage:   ./recover [file_name.raw]
     * Incorrect usage: ./recover
     *                  ./recover [x] [y] [z]...
     */
    if (argc > 2)
    {
        error("Usage: ./recover file_name.raw", EINVAL);\
        LOG(LOG_WARNING, "Continuing with incorrect number of arguments...");
    }
    else if (argc < 2)
    {
        error("Usage: ./recover file_name.raw", EINVAL);
        LOG(LOG_ERROR, "No additional argument detect");
        goto cleanup;
    }
    else
    {
        LOG(LOG_INFO, "Valid command-line argument");
    }

    // Check for file permissions
    char *file_name = argv[1];
    if (access(file_name, R_OK) != 0)
    {
        error("Access denied to read memory card", errno);
        LOG(LOG_ERROR, "Access denied to read memory card");
        goto cleanup;
    }

    // Open .raw file for reading binary
    memory_card = fopen(file_name, "rb");
    if (!memory_card || strstr(file_name, ".raw") == NULL)
    {
        error("Could not open the memory card", errno);
        LOG(LOG_ERROR, "Could not open the memory card");
        goto cleanup;
    }
    LOG(LOG_INFO, "Memory card successfully opened for reading binary");

    /**
     * Check if memory card's file size is multiple of 512
     * 
     * This check may not be as important but it is to ensure
     * all JPEG files are block-aligned, and does not cut off
     * prematurely at the end
     */
    int fseek_success = fseek(memory_card, 0, SEEK_END);
    if (fseek_success != 0)
    {
        error("Could not seek to end of file", EINVAL);
        LOG(LOG_WARNING, "Could not seek to end of file");
        LOG(LOG_WARNING, "Continuing without file size checked...");
    }
    else
    {
        long file_size = ftell(memory_card);
        if (file_size == -1L)
        {
            error("Could not check file size properly", EINVAL);
            LOG(LOG_WARNING, "Could not check file size properly");
            LOG(LOG_WARNING, "Continuing without file size checked...");
        }
        else
        {
            rewind(memory_card);
            if (file_size % BLOCK != 0)
            {
                error("Invalid file size", EINVAL);
                LOG(LOG_ERROR, "Invalid file size");
                goto cleanup;
            }
        }
    }
    rewind(memory_card);
    LOG(LOG_INFO, "File is of multiple of 512 Bytes");

    // Dynamically allocate BLOCK (512 B) of memory to buffer
    fat_block = malloc(BLOCK);
    if (!fat_block)
    {
        error("Could not allocate 512B of memory", errno);
        LOG(LOG_ERROR, "Could not allocate 512B of memory");
        goto cleanup;
    }
    LOG(LOG_INFO, "512B of memory successfully allocated");
    
    /**
     * Calculate JPEG file name sizes
     * 
     * @dir_length:  Length of the directory name
     * @name_length: Total length of directory name + jpeg name
     * "+1":         Add space for '/'
     */
    size_t dir_length = strlen(RECOVERY_DIR);
    name_length = dir_length + jpeg_char + 1;
    LOG(LOG_INFO, "Successfully calculated jpeg name length");

    /**
     * Create a directory for recovered JPEG images
     * 
     * Note: 0777 gives read/write/execute permissions
     */
    int dir_success = mkdir(RECOVERY_DIR, 0777);
    if (dir_success != 0)
    {
        error("Could not create directory for recovered images", errno);
        LOG(LOG_WARNING, "Continuing without directory created...");
    }
    else
        LOG(LOG_INFO, "Directory successfully created");

    // Check if directory is accessible
    if (access(RECOVERY_DIR, F_OK) != 0)
    {
        error("Recovery directory does not exist", errno);
        LOG(LOG_WARNING, "Continuing without directory...");
    }
    else
        LOG(LOG_INFO, "Directory successfully accessed");

    // Start reading memory card's data for any recoverable JPEG files
    while (true)
    {
        /**
         * Read a BLOCK of data from memory card
         * 
         * Also check if reading past memory card reaches EOF
         */
        size_t fread_BLOCK = fread(fat_block, BLOCK, 1, memory_card);
        if (fread_BLOCK != 1)
        {
            if (ferror(memory_card))
            {
                error("Failed to read data from memory card", errno);
                LOG(LOG_ERROR, "Failed to read data from memory card");
                goto cleanup;
            }
            else if (feof(memory_card))
            {
                fprintf(stdout, "End of file reached, exiting...\n");
                LOG(LOG_INFO, "End of file reached, exiting...");
                EXIT_STATUS = 0;
                goto cleanup;
            }
        }

        /**
         * Create a jpeg file if a jpeg signature is matched
         */
        if (match_sigJPEG(fat_block))
        {
            // Close previous jpeg file if exists
            if (jpeg_file != NULL)
            {
                fclose(jpeg_file);
            }

            // Convert ith jpeg index into a jpeg name
            char *jpeg_index = get_nameJPEG(jpeg_num);
            if (jpeg_index == NULL)
            {
                error("Failed to get a JPEG name", errno);
                LOG(LOG_ERROR, "Failed to get a JPEG name");
                goto cleanup;
            }
            jpeg_num++;

            // Open jpeg file
            jpeg_file = fopen(jpeg_index, "wb");
            if (!jpeg_file)
            {
                error("Could not create JPEG file", errno);
                LOG(LOG_ERROR, "Could not create JPEG file");
                goto cleanup;
            }

            free(jpeg_index);
        }

        // Write data from memory card to jpeg file if exists
        if (jpeg_file != NULL)
        {
            if (fwrite(fat_block, BLOCK, 1, jpeg_file) != 1)
            {
                error("Failed to write data into JPEG file", errno);
                LOG(LOG_ERROR, "Failed to write data into JPEG file");
                goto cleanup;
            }
        }
    }

    EXIT_STATUS = 0;
    goto cleanup;

// Cleanup frees allocated memory, closes all files, then exits program
cleanup:
    if (fat_block)
    {
        free(fat_block);
    }
    if (memory_card)
    {
        fclose(memory_card);
    }
    if (jpeg_file)
    {
        fclose(jpeg_file);
    }
    if (EXIT_STATUS == 0)
    {
        fprintf(stdout, "Program ran successfully\n");
        LOG(LOG_INFO, "Program ran successfully");
    }
    return EXIT_STATUS;
}

/**
 * error_message() -> Handles and logs error messages
 * @msg:   Error message to display
 * @level: Log level (LOG_INFO, LOG_WARNING, LOG_ERROR, LOG_DEBUG)
 * @err:   System error number (errno)
 * @line:  Line number where error occurred
 *
 * Prints error message to stderr and logs it if err is non-zero.
 * Used for consistent error handling throughout the program.
 */
void error_message(const char *msg, int err, int line)
{
    // Checks if err contains a nonzero value
    if (err)
    {
        fprintf(stderr, "Error encountered: %s\n", msg);
        fprintf(stderr, "Program error %i on line %i\n", err, line);
        EXIT_STATUS = err;
    }
}

/**
 * match_sigJPEG() -> Checks if a buffer contains a valid JPEG signature
 * @buffer: Pointer to memory block to check
 *
 * Returns: true if valid JPEG signature found, false otherwise
 *
 * Note: JPEG signatures must be block-aligned and contain the sequence:
 *       0xff 0xd8 0xff [0xe0-0xef]
 */
bool match_sigJPEG(unsigned char *buffer)
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef)
    {
        return true;
    }

    return false;
}

/**
 * get_nameJPEG -> Generates sequential JPEG filenames
 * @index:         Current JPEG file number (1-999)
 *
 * Returns: Dynamically allocated string with format "###.jpeg"
 *          where ### is the zero-padded index number
 *
 *          Returns "NULL" on error or invalid index
 *
 * Note: Caller must free the returned string when done.
 */
char *get_nameJPEG(int index)
{
    // Maximum and minimum count of JPEGs
    if (index > 999 || index < 0)
    {
        LOG(LOG_ERROR, "Invalid number of JPEGs");
        return NULL;
    }

    /**
     * Get the length (num of digit places) of the index
     *
     * @abs:   Gets the absolute value
     * @log:   Get the common logarithm
     * @floor: Rounds down the float
     * "+ 1":  Ensure to get the accurate length
     * 
     * Note: When index is 0, automatically assign 1 to
     *       index length
     */
    int index_length;
    if (index == 0)
        index_length = 1;
    else
        index_length = floor(log10(abs(index))) + 1;

    // Ensure the index_length was computed correctly
    if (index_length > 4 || index_length < 0)
    {
        LOG(LOG_ERROR, "Something went wrong with computing index length");
        return NULL;
    }

    // Allocate local variable instead of using global
    char *name = malloc(name_length);
    if (!name)
    {
        LOG(LOG_ERROR, "Failed to allocate space for JPEG name");
        return NULL;
    }

    // Use local variable
    if (index_length == 1)
        sprintf(name, "%s/00%d.jpg", RECOVERY_DIR, index);
    else if (index_length == 2)
        sprintf(name, "%s/0%d.jpg", RECOVERY_DIR, index);
    else if (index_length == 3)
        sprintf(name, "%s/%d.jpg", RECOVERY_DIR, index);

    return name;
}