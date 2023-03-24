/******************************************************************************

           Copyright (c) AIM GmbH 2009, 79111 Freiburg, Germany.

            All rights reserved.  No part of this software may
            be published, distributed, translated or otherwise
            reproduced by any means or for any purpose without
            the prior written consent of AIM GmbH, Freiburg.
-------------------------------------------------------------------------------

    Description:
-------------------------------------------------------------------------------
*/
 

/*! \file AiOsWindows.h

    Include file for windows operating systems specific functionality
*/


#ifndef AIOSWINDOWS_H
#define AIOSWINDOWS_H

#include <windows.h>
#include <stdio.h>
#include <io.h>
#include <string.h>
#include <stdarg.h>
#include <direct.h>
#include <Shlwapi.h> /* Used for PathIsRelative */
#include <sys/stat.h>
#include "ai_cdef.h"


#ifdef _NI_i386_
  #include <ansi_c.h>
  #define GETCHAR()    getchar()
  #define STRICMP(a,b) stricmp(a,b) 
  #define STRNCPY(dest,src,count) strncpy(dest,src,count)
  #define STRNCAT(dest,src,count) strncat( dest, src, count )
  #define VSNPRINTF(dest,count,format,args)  vsnprintf(dest, count, format, args)
#elif defined(__BORLANDC__)
  #include <conio.h>
  #include <shlobj.h>
  #define GETCHAR()    _getch()
  #define STRICMP(a,b) _stricmp(a,b) 
  #define STRNCPY(dest,src,count) strncpy(dest,src,count)
  #define STRNCAT(dest,src,count) strncat( dest, src, count )
  #define VSNPRINTF(dest,count,format,args)  vsnprintf(dest, count, format, args)
#else
  #include <conio.h>
  #include <shlobj.h>
  #define GETCHAR()    _getch()
  #define STRICMP(a,b) _stricmp(a,b) 
  #define STRNCPY(dest,src,count) strncpy_s(dest, count, src, _TRUNCATE)
  #define STRNCAT(dest,src,count) strncat_s(dest, count, src, _TRUNCATE)
  #define VSNPRINTF(dest,count,format,args) vsnprintf_s(dest, count, _TRUNCATE, format, args)
#endif


/* Macro for exporting/importing C++ classes 
   Exporting libraries have to define AI_CLASS_EXPORT.
   Importing instances need to define AI_CLASS_IMPORT
*/
#ifdef  AI_CLASS_EXPORT
  #define AI_DLL_CLASS __declspec(dllexport)
#elif defined AI_CLASS_IMPORT
  #define AI_DLL_CLASS __declspec(dllimport)
#else
  #define AI_DLL_CLASS
#endif



/*! \def AI_OS_MAX_PATH
 * Define for maximum, OS specific path length */
#define AI_OS_MAX_PATH MAX_PATH

/*! \def DIR_SEPARATOR
 * Define for OS specific path separator */
#define DIR_SEPARATOR "\\"

/*! \def DIR_SEPARATOR_CHAR
 *  Define for OS specific path separator character
 */
#define DIR_SEPARATOR_CHAR '\\'




#define STDCALL __stdcall


static _inline char AiOsGetChar()
{
    return (char)GETCHAR();
}

static _inline void AiOsSleep( int iMilliseconds )
{
    Sleep( iMilliseconds );
} 


static _inline char AiOsStringCmp( const char * sz1, const char * sz2 )
{
    return (char)( STRICMP( sz1, sz2 ) == 0 );
}

static _inline int AiOsGetFileSize( const char * szFileName, unsigned int * pulFileSize )
{
    BOOL                        fOk;
    int                         lRetVal  = 1;
    WIN32_FILE_ATTRIBUTE_DATA   fileInfo;

    if( szFileName != NULL )
    {

        fOk = GetFileAttributesEx( (const TCHAR *)szFileName, GetFileExInfoStandard, (void*)&fileInfo );

        if( fOk )
        {
            /* can't handle files > 2GB */
            if( fileInfo.nFileSizeHigh == 0 )
            {
                *pulFileSize = (unsigned int)fileInfo.nFileSizeLow;
                lRetVal      = 0;
            }
        }
    }

    return lRetVal;
}

/* Get string from STDIN */
static _inline int AiOsGetString( char * szDest, int size, char * szDefault )
{

     fgets( szDest, size, stdin );
    szDest[strlen(szDest)-1]=0; // remove newline
    if( strlen(szDest) == 0 )
        STRNCPY(szDest, szDefault,size);
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
static _inline int AiOsGetTempPath( char* szTempPath, size_t MaxSize )
{
    DWORD dwRetVal = 0;

    dwRetVal = GetTempPathA( (DWORD) MaxSize, szTempPath );

    if( (dwRetVal > MaxSize) || (dwRetVal == 0) )
    {
        szTempPath[0] = 0;
        return -1;
    }

     return 0;
}

/*! \brief Gets the application's path for storing data
 *
 * Gets the path of the directory the application shall write into
 * \param szAppDataPath array of characters that path is copied into
 * \param MaxSize maximum size path can have (size of szAppDataPath)
 * \return returns 0 on success, -1 otherwise
 */
static _inline int AiOsGetAppDataPath( char* szAppDataPath, size_t MaxSize )
{
#ifndef _NI_i386_
    char szTempPath[MAX_PATH];
    szAppDataPath[0] = 0;

    if( !SUCCEEDED( SHGetFolderPathA( NULL, CSIDL_APPDATA, NULL, 0, szTempPath)) )
        return -1;

    if(strlen(szTempPath) + strlen(DIR_SEPARATOR) >= MaxSize)
        return -1;

    STRNCPY(szAppDataPath, szTempPath,MAX_PATH);
    STRNCAT(szAppDataPath, DIR_SEPARATOR, MaxSize);

    return 0;
#else
    return -1;
#endif
}


/*! \brief Removes line delimiters from a string
 *
 * This function is used to remove CR and LF from end of a string
 * and replaces them by '\0'
 * \param ac_String zero-terminated string that contains line delimiters at its end
 */
static _inline void AiOsRemoveLineDelimiters(char* ac_String)
{
    /*Eliminate End of Line (LF+CR for Windows, LF for Linux */
    while( (strlen(ac_String) > 0) &&
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
static _inline int AiOsStrncpy(char* dest, const char* source, size_t destSize, AiBoolean truncate)
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

    STRNCPY(dest, source, destSize);

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
 * is in the current working directory, or an empty string is provided, ".\\" is returned.
 * \param ac_Filepath zero-terminated string that contains a file path
 * \param MaxSize maximum size of \ref ac_Filepath in bytes
 * \return returns 0 in case of success, -1 otherwise.
 */
static _inline int AiOsDirname(char *ac_Filepath, size_t MaxSize)
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
	  return AiOsStrncpy(ac_Filepath, ".\\", MaxSize, AiFalse);
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
static _inline int AiOsSnprintf(char* dest, size_t destSize, AiBoolean truncate, const char* format, ...)
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

    ret = VSNPRINTF(dest, destSize, format, args);
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
static _inline int AiOsGetOsVersion(char* dest, size_t destSize)
{
    OSVERSIONINFO osVersionInfo;

    ZeroMemory(&osVersionInfo, sizeof(OSVERSIONINFO));
    osVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

//#pragma warning( push )
//#pragma warning( disable:4996 )
    /*GetVersionEx is deprecated but there is no working replacement yet. */
    GetVersionEx(&osVersionInfo);
//#pragma warning( pop )


    return sprintf_s( dest, destSize, "Windows (Ver %d.%d.%d - %s)", osVersionInfo.dwMajorVersion, osVersionInfo.dwMinorVersion, osVersionInfo.dwBuildNumber, osVersionInfo.szCSDVersion);
}

#define AI_F_OK     0
#define AI_R_OK     (1 << 1) 
#define AI_W_OK     (1 << 2) 
#define AI_X_OK     // Not Supported for Windows
#define AI_RW_OK     (3 << 1)

static _inline int AiOsAccess(const char *pathname, int mode)
{
errno_t rRet; 

    rRet =_access_s( pathname, mode);
    return (int)rRet;
}


/*! \brief Extracts a file name from a file path

This function takes a path to specific file and extracts the file
name from it.
\param path path to file to extract file name of
\return returns pointer to file name on success, NULL on error */
static _inline char* AiOsBasename(char* path)
{
    char* basename = NULL;
    size_t pos = 0;

    if(!path)
    {
        return NULL;
    }

    for(pos = strlen(path); pos > 0 && path[pos - 1] != DIR_SEPARATOR_CHAR; pos--);

    basename = &path[pos];

    return basename;
}


/*! \brief Make an case insensitive string compare
 *
 * This function compares two strings (like strcmp), ignoring the case . \n
 */
#define AiOsStrCaseCmp(x,y)   _stricmp(x,y)


static _inline char* AiOsGetCwd( char* path, size_t MaxSize )
{
    return _getcwd(path, (int)MaxSize);
}


/*! \brief Check if a file path is relative or absolute
*
* This function checks if a given path to a file is either relative or
* or absolute. \n
* Attention: Applications using this function must add Shlwapi.lib to their
* link dependendencies.
* @param path file path to check as zero-terminated ASCII string
* @return AiTrue if path is relative, AiFalse if path is either absolute or not valid
*/
static _inline AiBoolean AiOsIsPathRelative(const char* path)
{
	if (!path || !strlen(path))
	{
		return AiFalse;
	}

	return (AiBoolean) PathIsRelativeA(path);
}


/*! \brief Check if a file  exists
*
* This function checks if file specified by given path exists.
* @param path file path to check as zero-terminated ASCII string
* @return AiTrue if file exists, AiFalse not
*/
static _inline AiBoolean AiOsFileExists(const char* path)
{
    struct _stat s;

	if (!path)
	{
		return AiFalse;
	}

	return _stat(path, &s) == 0 ? AiTrue : AiFalse;
}


#endif /* AIOSWINDOWS_H */

