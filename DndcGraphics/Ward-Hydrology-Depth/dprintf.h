/* $Id: dprintf.h 83 2004-04-16 13:29:01Z skk $ */

#ifndef DPRINTF_H
#define DPRINTF_H
#include <cstdio>
#include <cstdlib>

#include <stddef.h>
#include <stdarg.h>

using namespace std;


#ifdef __cplusplus
    #include <iostream>
    #include <iomanip>
    #define OUTPUT_STREAM std::cout
    #define WIDTH 16
#endif /* __cplusplus */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


    #ifdef DEBUG
        #define dprintf( ... ) printf( __VA_ARGS__ )
        #define dfprintf( fs, ... ) fprintf( fs, __VA_ARGS__ )
        #define dvprintf( ... ) printf( "%s:%d\t", __FILE__, __LINE__ ) ; printf( __VA_ARGS__ )
        #define dvfprintf( fs, ... ) fprintf( fs, "%s:%d\t", __FILE__, __LINE__ ) ; fprintf( fs, __VA_ARGS__ )
    #else
        #define dprintf(  )
        #define dfprintf( ) 
        #define dvprintf( )
        #define dvfprintf(  )
    #endif  /* end else */

#ifdef __cplusplus
}
#endif /* end __cplusplus */

#ifdef __cplusplus
        
    #ifdef DEBUG
        //display information about a variable
        // variable debug
        #define vdebug(x) OUTPUT_STREAM << std::setiosflags(std::ios::left) \
            << __FILE__ << ":" << __LINE__ << " " << std::setw(WIDTH) \
            << #x << " " << std::setw(WIDTH) << x << std::endl;

        //display a string
        // general debug
        #define debug(x) OUTPUT_STREAM << std::setiosflags(std::ios::left) \
            << __FILE__ << ":" << __LINE__ << " " << std::setw(WIDTH)\
            << x << std::endl;

        //display information about a variable, including the function it was called in
        // variable debug with function name included
        #define fdebug(x) OUTPUT_STREAM << std::setiosflags(std::ios::left) \
            << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__  \
            << " " << std::setw(WIDTH) << #x << std::setfill(' ') \
            << std::setw(32) << x << std::endl;
    #else
        #define vdebug(x)
        #define debug(x) 
        #define fdebug(x)
    #endif        

#endif  /* _cplusplus */

/* error/warning message functions */
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    inline void error( char* fmt, ... )
    {
        std::cerr << "[error]";

        va_list ap;
        va_start(ap, fmt);
        vfprintf(stderr, fmt, ap);
        va_end(ap);
        
        std::cerr << std::endl;
    }

    inline void warning( char* fmt, ... )
    {
        std::cerr << "[warning]";

        va_list ap;
        va_start(ap, fmt);
        vfprintf(stderr, fmt, ap);
        va_end(ap);
        
        std::cerr << std::endl;
    }

    inline void fatal( char* fmt, ... )
    {
        std::cerr << "[fatal]";

        va_list ap;
        va_start(ap, fmt);
        vfprintf(stderr, fmt, ap);
        va_end(ap);
        
        std::cerr << std::endl;

        exit(1);
    }

#ifdef __cplusplus
}
#endif /* end __cplusplus */


#endif  /* DEBUG_H */
