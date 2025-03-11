//* LOG.H
/**
 * LOG.h - Simple Logging System for C Programs
 * Version:     1.0
 * Created:     02-03-2025
 * 
 * Creator:     Amjko2234
 * 
 * Purpose: Provides a simple but flexible logging system for C programs
 *          to track program execution, errors, and debugging information.
 * 
 * Features:
 * -> Four logging levels (INFO, WARNING, ERROR, DEBUG)
 * -> Automatic timestamp for each log entry
 * -> File and line number tracking
 * -> Append-mode logging (preserves log history)
 * 
 * Usage:
 * -> LOG(LOG_INFO, "Program started");
 *    LOG(LOG_ERROR, "Failed to open file");
 *     
 * Note: Define LOG_FILE before including this header to customize
 *       the log file path. Default is "program.log"
 */

#ifndef LOG_H 
#define LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * Log File Configuration
 * ---------------------
 * Default log file name is "program.log"
 * Override by defining LOG_FILE before including this header:
 * #define LOG_FILE "custom.log"
 * #include "LOG.h"
 */
#ifndef LOG_FILE
#define LOG_FILE "program.log"
#endif

/**
 * Log Levels
 * ----------
 * INFO:    General information about program execution
 * WARNING: Potential problems that don't stop execution
 * ERROR:   Serious problems that may cause program failure
 * DEBUG:   Detailed information for debugging purposes
 */
#define LOG_INFO    "INFO"
#define LOG_WARNING "WARNING"
#define LOG_ERROR   "ERROR"
#define LOG_DEBUG   "DEBUG"

/**
 * Log Macro
 * ---------
 * Automatically includes file name and line number in log entries
 * 
 * @param level: Log level (LOG_INFO, LOG_WARNING, LOG_ERROR, LOG_DEBUG)
 * @param msg:   Message to log
 * 
 * Usage: LOG(LOG_INFO, "Operation completed successfully");
 */
#define LOG(level, msg) log_message(level, msg, __FILE__, __LINE__)

/**
 * log_message() -> Internal function to handle log writing
 * 
 * @param level: Logging level (INFO, WARNING, ERROR, DEBUG)
 * @param msg:   Message to be logged
 * @param file:  Source file where log was called
 * @param line:  Line number where log was called
 * 
 * Format: [TIMESTAMP] [LEVEL] (file:line) message
 * 
 * Returns: void
 * Note: Automatically opens and closes log file for each entry
 *       to prevent file handle leaks on program crashes
 */
void log_message(const char *level, const char *msg, const char *file, int line)
{
    // Create/open log file in append mode
    FILE *log_file = fopen(LOG_FILE, "a");
    if (!log_file)
    {
        perror("Failed to open log file");
        return;
    }

    // Get current timestamp
    time_t now = time(NULL);
    char *timestamp = ctime(&now);
    
    // Remove newline from timestamp
    timestamp[strcspn(timestamp, "\n")] = 0;

    // Write formatted log entry
    fprintf(log_file, "[%s] [%s] (%s:%d) %s\n",
            timestamp,  // [YYYY-MM-DD HH:MM:SS]
            level,      // [INFO/WARNING/ERROR/DEBUG]
            file,       // Source file
            line,       // Line number
            msg);       // Log message

    fclose(log_file);
}

#endif /* LOG_H */