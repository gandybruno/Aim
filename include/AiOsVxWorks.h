/******************************************************************************

           Copyright (c) AIM GmbH 2009, 79111 Freiburg, Germany.                 
                                                                             
            All rights reserved.  No part of this software may                
            be published, distributed, translated or otherwise                
            reproduced by any means or for any purpose without                
            the prior written consent of AIM GmbH, Freiburg.                  

******************************************************************************/
/*! \file AiOsVxWorks.h
 *
 *  Include file for operating system specific functions and headers
 */

/* Include file for VxWorks operating systems */
#ifndef AIOSVXWORKS_H
#define AIOSVXWORKS_H

#include <vxWorks.h>
#include <version.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <taskLib.h>
#ifndef __RTP__
#include <intLib.h>
#endif
#include <sysLib.h>
#include <strings.h>
#include <ioLib.h>

#include "Ai_cdef.h"

/*! \def AI_OS_MAX_PATH
 * Define for maximum, OS specific path length
 * This is strongly dependend on which file system is being used and how it is configured
 * For now we assume that a maximum path of 255 characters is allowed. */
#define AI_OS_MAX_PATH 255

/* there is no stdcall for VxWorks, so the define is empty */
#define STDCALL


/*! \def DIR_SEPARATOR_CHAR
 * define for a directory separator character
 */
#define DIR_SEPARATOR_CHAR '/'


/*! \def AI_F_OK
 *  Checks if file exists
 */
#define AI_F_OK     0


static __inline__ char AiOsGetChar()
{
    return (char)getchar();
}

static __inline__ void AiOsSleep( int iMilliseconds )
{
    /*taskDelay( iMilliseconds/15 );*/
    taskDelay(sysClkRateGet()* iMilliseconds /1000);
} 


static __inline__ char AiOsStringCmp( const char * sz1, const char * sz2 )
{
    return (char)( strcmp( sz1, sz2 ) == 0 );
}

static __inline__ int AiOsGetFileSize( const char * szFileName, unsigned int * pulFileSize )
{
    FILE   * pFile            = 0;

    /* -- prepare input file --- */
    pFile = fopen( szFileName, "rb" );

    fseek( pFile , 0 , SEEK_END );
    *pulFileSize = (unsigned int) ftell( pFile );
    rewind (pFile);

    /* -- close file --- */
    if( pFile )
    	fclose( pFile );

    return 0;
}

/* Get string from STDIN */
static __inline__ int AiOsGetString( char * szDest, int size, char * szDefault )
{
    fgets( szDest, size, stdin );
    szDest[strlen(szDest)-1]=0; /* remove newline */
    if( strlen(szDest) == 0 )
        strcpy( szDest, szDefault );

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
     strcpy( szAppDataPath, "./" );
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
	if (!dest)
	{
		return -1;
	}

	if (!source)
	{
		dest[0] = '\0';
		return -1;
	}

	/* source string does not fit into destination buffer and
	* must not be truncated, so return error
	*/
	if (strlen(source) >= destSize && !truncate)
	{
		dest[0] = '\0';
		return -1;
	}

    strncpy(dest, source, destSize);

	/* Ensure, that the destination string is zero terminated.
	* Keep in mind that the string can be truncated when strlen(source) >= maxLength and truncated parameter is true
	*/
	if (destSize > 0)
	{
		dest[destSize - 1] = '\0';
	}

	return 0;
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
  char *pc_LastDelimiter1;
  char *pc_LastDelimiter2;

  /* In Windows we have two valid file separators
   * Get the location of both file separators if available */
  pc_LastDelimiter1 = strrchr(ac_Filepath, '\\');
  pc_LastDelimiter2 = strrchr(ac_Filepath, '/');

  /* if no file separator is found, return ".\\" */
  if( (pc_LastDelimiter1 == NULL) &&
      (pc_LastDelimiter2 == NULL) )
  {
    strcpy(ac_Filepath, ".\\");
    return 0;
  }


  /* Truncate string at the last file separator */
  if( pc_LastDelimiter1 > pc_LastDelimiter2 )
  {
    pc_LastDelimiter1++;
    *pc_LastDelimiter1 = 0;
  }
  else
  {
    pc_LastDelimiter2++;
    *pc_LastDelimiter2 = 0;
  }

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
     strcpy( szTempPath, "./" );
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
        return -1;
    }

    if(!format)
    {
        dest[0] = '\0';
        return -1;
    }

    va_start(args, format);

    ret = vsnprintf(dest, destSize, format, args);
    if((ret < 0) && (!truncate))
       return -1;

    va_end(args);

    return (int)strlen(dest);
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
#if defined VXWORKS_VERSION    
	strncpy( dest, VXWORKS_VERSION, destSize);
#else
    strncpy( dest, "unknown", destSize);
#endif

    return 0;
}

static __inline__ char* AiOsBasename (char* name)
{
	return name;
}

static __inline__ STATUS AiOsAccess (const AiChar *pDevName, int status)
{
	int fd;
	
	/* check the device */
	fd = open(pDevName, O_RDONLY, 0);
	if(fd == ERROR)
	{
		printf("%s device is not found.\n", pDevName);
		return ERROR;
	}
	close(fd);
	return OK;
}



/*! \brief Make an case insensitive string compare
 *
 * This function compares two strings (like strcmp), ignoring the case . \n
 */
#define AiOsStrCaseCmp(x,y)   strcasecmp(x,y)





/********************************************/
/* DIRECT MEMORY ACCESS (Without swapping)  */
/********************************************/

#define READABSMEMUINT32( module, Dst, SrcAddr ) \
    { Dst = *((AiUInt32*)(SrcAddr)); }
#define WRITEABSMEMUINT32( module, DstAddr, Src ) \
    { *((AiUInt32*)(DstAddr)) = Src; }

#define READABSBLOCKMEMDATA( module, DstPtr, SrcAddr, Size, Width ) \
    AiBlockSlvMemData( (AiUInt8*)(SrcAddr), (AiUInt8*)DstPtr, Size, Width)
#define WRITEABSBLOCKMEMDATA( module, DstAddr, Src, Size, Width ) \
    AiBlockSlvMemData( (AiUInt8*)Src, (AiUInt8*)(DstAddr), Size, Width)


#endif /* AIOSVXWORKS_H */

