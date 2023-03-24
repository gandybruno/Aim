/*! \file AiOsLinux.h
 * 
 * Header file for Linux specific functionality
*/

#ifndef AIOSLINUX_H
#define AIOSLINUX_H


#define __cdecl
#define __stdcall
#define STDCALL

/* Include file for linux operating systems */
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <stdint.h>
#include <libgen.h>
#include <errno.h>
#include <stdarg.h>
#include <syslog.h>
#include "Ai_cdef.h"


/* Macro for exporting/importing C++ classes 
   No special actions needed here hence macro is empty
*/
#define AI_DLL_CLASS
 

/*! \def AI_OS_MAX_PATH
 * Define for maximum, OS specific path length */
#define AI_OS_MAX_PATH PATH_MAX

/*! \def DIR_SEPARATOR
 * Define for OS specific path separator */
#define DIR_SEPARATOR "/"

/*! \def DIR_SEPARATOR_CHAR
 * define for a directory separator character
 */
#define DIR_SEPARATOR_CHAR '/'

/*! \def AI_F_OK
 *  Checks if file exists
 */
#define AI_F_OK     F_OK

/*! \def AI_R_OK
 * Checks if file is readable
 */
#define AI_R_OK     R_OK

/*! \def AI_W_OK
 *
 * Checks if file is writable
 */
#define AI_W_OK     w_OK

/*! \def AI_X_OK
 *
 * Checks if file is executable
 */
#define AI_X_OK     X_OK

/*! \def AI_RW_OK
 *
 * Checks if file is read- and writable
 */
#define AI_RW_OK    (R_OK | W_OK)


static __inline__ char AiOsGetChar()
{
    return (char)getchar();
}


static __inline__ void AiOsSleep( int msec )
{
    usleep( msec * 1000 );
}


static __inline__ char AiOsStringCmp( const char * sz1, const char * sz2 )
{
    return (char)( strcasecmp( sz1, sz2 ) == 0 );
}


static __inline__ int AiOsGetFileSize( const char * szFileName, unsigned int * pulFileSize )
{
    struct stat xStatus;
    int         lRetVal = 1;

    if( pulFileSize != NULL )
    {
        if( stat( szFileName, &xStatus ) == 0 )
        {
            *pulFileSize = xStatus.st_size;
            lRetVal      = 0;
        }
    }

    return lRetVal;
}


static __inline__ int AiOsGetString( char * szDest, int size, char * szDefault )
{
    char* s_Result;

    s_Result = fgets( szDest, size, stdin );
    if(s_Result == NULL)
        strcpy( szDest, szDefault);

    szDest[strlen(szDest)-1]=0; // remove newline
    if( strlen(szDest) == 0 )
        strcpy( szDest, szDefault);

    return 0;
}

/*! \brief Gets the application's path for storing data
 *
 * On Linux, this just delivers path of current working directory
 * \param szAppDataPath array of characters that path is copied into
 * \param size_t maximum size path can have (size of szAppDataPath)
 * \return returns 0 on success, -1 otherwise
 */
static __inline__ int AiOsGetAppDataPath( char* szAppDataPath, size_t MaxSize)
{
    szAppDataPath = getcwd(szAppDataPath, MaxSize);
    if(szAppDataPath == NULL)
        return -1;

    if(strlen(szAppDataPath) + strlen(DIR_SEPARATOR) >= MaxSize)
        return -1;

    strcat(szAppDataPath, DIR_SEPARATOR);

    return 0;
}


/*! \brief Removes line delimiters from a string
 *
 * This function is used to remove CR and LF from end of a string
 * and replaces them by '\0'
 * \param ac_String zero-terminated string that contains line delimiters at its end
 */
static __inline__ void AiOsRemoveLineDelimiters(char* ac_String)
{
    /*Eliminate End of Line (LF+CR for Windows, LF for Linux */
    while((strlen(ac_String) > 0) &&
           ((ac_String[strlen(ac_String) - 1] == 0x0a) || (ac_String[strlen(ac_String) - 1] == 0x0d)))
    {
        ac_String[strlen(ac_String) - 1] = '\0';
    }
}


/*! \brief Returns the parent directory path of a given file path
 *
 * This function is used to return the parent directory of a given file.
 * It returns the directory path with a file delimiter at its end. If the file
 * is in the current working directory, or an empty string is provided, "./" is returned.
 * \param ac_Filepath zero-terminated string that contains a file path
 * \param MaxSize maximum size of \ref ac_Filepath in bytes
 * \return returns 0 in case of success, -1 otherwise.
 */
static __inline__ int AiOsDirname(char* ac_Filepath, size_t MaxSize)
{
    char* DirectoryPath;
    int Length;

    if(ac_Filepath == NULL)
        return -1;

    DirectoryPath = dirname(ac_Filepath);

    /* Check if dirname allocated new string.
     * Then we have to copy it into the output string */
    if(DirectoryPath != ac_Filepath)
    {
        Length = strlen(DirectoryPath);

        /* We need space for separator plus trailing zero in the output string */
        if(Length + sizeof(DIR_SEPARATOR_CHAR) + 1 > MaxSize)
            return -1;

        strncpy(ac_Filepath, DirectoryPath, MaxSize);
    }

    Length = strlen(ac_Filepath);

    /* We need space for separator plus trailing zero in the output string */
    if(Length + sizeof(DIR_SEPARATOR_CHAR) + 1 > MaxSize)
        return -1;

    ac_Filepath[Length] = DIR_SEPARATOR_CHAR;
    ac_Filepath[Length + 1] = '\0';

    return 0;
}


/*! \brief Gets the path for storing temporary data
 *
 * Gets the path of the directory the application shall write temporary
 * data into.
 * \param szTempPath array of characters that path is copied into
 * \param MaxSize maximum size path can have (size of szAppDataPath)
 * \return returns 0 on success, -1 otherwise
 */
static __inline__ int AiOsGetTempPath( char* szTempPath, size_t MaxSize )
{
    char* p_tempdir = NULL;
    int chars_copied = 0;

    memset(szTempPath, 0, MaxSize);

    p_tempdir = getenv("TMPDIR");
    if(p_tempdir)
    {
        chars_copied = snprintf(szTempPath, MaxSize - 1, "%s", p_tempdir);

        /* we have to add a '/' at the end of the string, so comparison is against MaxSize -1 */
        if(chars_copied <= 0 || (size_t) chars_copied >= MaxSize - 1)
        {
            return -1;
        }
    }
    else
    {
        chars_copied = snprintf(szTempPath, MaxSize - 1, "%s", P_tmpdir);

        /* we have to add a '/' at the end of the string, so comparison is against MaxSize -1 */
        if(chars_copied <= 0 || (size_t) chars_copied >= MaxSize - 1)
        {
            return -1;
        }
    }

    szTempPath[chars_copied] = DIR_SEPARATOR_CHAR;

    return 0;
}


/*! \brief Get the name and version of the operating system
 *
 * This function prints into a formatted string to a buffer, which contains information about the operating system used. \n
 * @param dest buffer the formatted string is printed into
 * @param destSize size of the destination buffer in bytes
 * @return returns number of characters printed (excluding terminating null-byte) on success, negative error code otherwise
 */
static __inline__ int AiOsGetOsVersion(char* dest, size_t destSize)
{
    struct utsname osInfo;

    uname( &osInfo );

    return snprintf( dest, destSize, "%s %s %s %s %s", osInfo.sysname, osInfo.nodename, osInfo.release, osInfo.version, osInfo.machine );
}
/*! Save copy function for zero-terminated ASCII strings
 *
 * This function copies a string while ensuring that the destination buffer is not exceeded
 * and the resulting string is zero-terminated. \n
 * If length of source string is equal or greater than the size of the destination buffer, \n
 * the function returns an error unless \truncate parameter is set to true. \n
 * In this case, the resulting string will be truncated and the function returns no error.
 * @param dest buffer where string will be copied into
 * @param source string that shall be copied (must be zero-terminated
 * @param destSize size of destination buffer in bytes
 * @param truncate signifies if truncation of string is allowed
 * @return returns 0 on success, !0 otherwise
 */
static __inline__ int AiOsStrncpy(char* dest, const char* source, size_t destSize, AiBoolean truncate)
{
    if(!dest)
    {
        return -EINVAL;
    }

    if(!source)
    {
        dest[0] = '\0';
        return -EINVAL;
    }

    /* source string does not fit into destination buffer and
     * must not be truncated, so return error
     */
    if(strlen(source) >= destSize && !truncate)
    {
        dest[0] = '\0';
        return -EINVAL;
    }

    strncpy(dest, source, destSize);

    /* Ensure, that the destination string is zero terminated.
     * Keep in mind that the string can be truncated when strlen(source) >= maxLength and truncated parameter is true
     */
    if(destSize > 0)
    {
        dest[destSize - 1] = '\0';
    }

    return 0;
}


/*! \brief Save version of sprintf function
 *
 * This function prints a formatted string to a buffer, ensuring that the destination buffer is not exceeded
 * and the resulting string is zero-terminated. \n
 * If formatted string does not fit into the destination buffer and truncate parameter is set to false,
 * the function returns an error.
 * @param dest buffer the formatted string is printed into
 * @param destSize size of the destination buffer in bytes
 * @param truncate signifies if string can be truncated without returning an error
 * @param format format string
 * @return returns number of characters printed (excluding terminating null-byte) on success, negative error code otherwise
 */
static __inline__ int AiOsSnprintf(char* dest, size_t destSize, AiBoolean truncate, const char* format, ...)
{
    int ret = 0;
    va_list args;

    if(!dest)
    {
        return -EINVAL;
    }

    if(!format)
    {
        dest[0] = '\0';
        return -EINVAL;
    }

    va_start(args, format);

    ret = vsnprintf(dest, destSize, format, args);
    if(ret < 0)
    {
        va_end(args);
        return -1;
    }

    va_end(args);

    if((size_t) ret >= destSize && !truncate)
    {
        return -1;
    }

    return strlen(dest);
}




/*! \brief Checks a file for specific access rights
 *
 * @param pathname path to file to check for
 * @param mode access rights to check
 * @return returns 0 if access right check succeeds, -1 otherwise
 */
static __inline__ int AiOsAccess(const char *pathname, int mode)
{
    return access(pathname, mode);
}


/*! \brief Extracts a file name from a file path
 *
 * This function takes a path to specific file and extracts the file
 * name from it.
 * @param filePath file path to extract file name from
 * @return returns pointer to file name on success, NULL on error
 */
static __inline__ char* AiOsBasename( char* filePath)
{
    return basename(filePath);
}



/*! \brief Get current working directory
 * 
 * This function prints the current working directory to the given buffer
 * @param path buffer to write the current working directory into
 * @param max_size size of path buffer in bytes
 * @return pointer to path on success, NULL on failure
 */
static __inline__ char* AiOsGetCwd(char* path, size_t max_size)
{   
    return getcwd(path, max_size);
}


/*! \brief Check if a file path is relative or absolute
 * 
 * This function checks if a given path to a file is either relative or
 * or absolute.
 * @param path file path to check as zero-terminated ASCII string
 * @return AiTrue if path is relative, AiFalse if path is either absolute or not valid
 */
static __inline__ AiBoolean AiOsIsPathRelative(const char* path)
{
    if(!path || !strlen(path))
    {
        return AiFalse;
    }

    return path[0] != '/';
}


/*! \brief Make an case insensitive string compare
 *
 * This function compares two strings (like strcmp), ignoring the case . \n
 */
#define AiOsStrCaseCmp(x,y)   strcasecmp(x,y)


/*! \brief Check if a file  exists
 * 
 * This function checks if file specified by given path exists.
 * @param path file path to check as zero-terminated ASCII string
 * @return AiTrue if file exists, AiFalse not
 */
static __inline__ AiBoolean AiOsFileExists(const char* path)
{
    if(!path)
    {
        return AiFalse;
    }

    struct stat s;

    return stat(path, &s) == 0 ? AiTrue : AiFalse;
}



#endif /* AIOSLINUX_H */

