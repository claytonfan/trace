// trace.c
// Description - see trace.h
//
// An alternative is to use a linked list of traceMessges,
// especially for a long list of messages (large TARCE_MAX).
// However, if the trace is dumped because of system error
// such as SIGSEGV, it is possible the the allocated memeory
// in the linked list is corrupted.
//
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "trace.h"

static int  (*tracePrint)( char * ) = 0;
static int    traceMax   = TRACE_MAX;
static int    traceCurrent = 0; // points to current message slot to be filled
static int    traceCount   = 0;
static char   traceTag[TRACE_TAG_SIZE+1] = TRACE_TAG_DEFAULT;
static char   traceMessages[TRACE_MAX][TRACE_MSG_SIZE+1] = { "none" };
//
static int    tracePrintMessages( int, char * );
//
// public traceInit()
// Description - see trace.h
//
void traceInit( char *tag, int (*print_func)(), int max_size ) {
    strncpy( traceTag, tag, TRACE_TAG_SIZE );
    if( print_func != 0 ) tracePrint = print_func;
    if( max_size <= 0 || max_size > TRACE_MAX ) {
        traceMax = TRACE_MAX;
    }
    else {
        traceMax = max_size;
    }
    traceCurrent = 0;
    traceCount   = 0;
}
//
// public traceDump()
// Description - see trace.h
//
void traceDump( char *desc )
{
    (void )tracePrintMessages( traceMax, desc );
}
// public traceShow()
// Description - see trace.h
//
void traceShow( int num, char *desc ) {
    (void )tracePrintMessages( num, desc );
}
//
// public traceLog
// Description - see trace.h
//
int traceLog( char *format, ... )
{
    int len = 0;
    char buffer[512];
    va_list  args;
    va_start( args, format );
    len = vsprintf( buffer, format, args );
    va_end( args );
    strncpy( traceMessages[traceCurrent++], buffer, TRACE_MSG_SIZE );
    // Count messages until the list fills up
    if( traceCount < traceMax ) traceCount++;
    // If this is at bottom of list, next message is at the top
    if( traceCurrent >= traceMax ) traceCurrent = 0;
    return( (int )strlen( buffer ) );
}
//
// private tracePrintMessages
// Description - display the specified num of the most recent messages
// Input -
//     maxnum     - num of messages to display
// Return -
//     Number of messages display. It may be less than the maximum
//     allowable messages.
//
int tracePrintMessages( int num, char *desc ) {
    int  i = 0;
    char str[256] = "";
    //
    // Start dumping from previous. If at top the last message is at end.
    //
    int  mpointer = traceCurrent ? traceCurrent-1 : traceMax-1;

    if( !num ) num = traceCount;
    if( !tracePrint ) {
        printf( "Note. Trace dump print function not specified. %s\n",
                "Function printf() is used" );
        tracePrint = &printf;
    }
    sprintf( str, "%s\n",  desc );
    (void )(*tracePrint)( str );
    sprintf( str, "%s - trace dump of %d messages:\n",
             traceTag, traceCount );
    (void )(*tracePrint)( str );
    for( i=0; i < traceCount && i < num && i < TRACE_MAX; i++ ) {
        (void )(*tracePrint)(traceMessages[mpointer--]);
        if( mpointer < 0 ) mpointer = traceMax-1;
    }
    return( i );
}