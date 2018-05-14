//
// trace.h
// Description - custom logging and dumping of debug messages
//
// History -
// 20180513 Clayton Fan   Created
//
// A set of functions to log and dump and list of messages,
// last in first out.
//
// The messages are intended to be logged at various location in a program,
// and then dumped at the signal handler sig_handler() on a signal such as
// SIGSEGV.
//
// A simpler version would be logging many times, traceLog() logs and save
// only the most recent message, and traceDump() displays othat message.
// This version saves and dumps a maximum of the most recent TRACE_MAX messages
// logged.
//
// intended usage -
//
//  #include <stdio.h>
//  #include <stdlib.h>
//  #include <signal.h>
//  #include "trace.h"
//
//  void sig_handler(int signo)
//  {
//      if( signo ==  SIGSEGV ) {
//          traceDump("Signal SIGSEGV");
//      }
//      // may handle other signo's
//      exit( signo );
//  }
//
//  int main(int argc, char **argv)
//  {
//      traceInit( "Prgram Test", &printf, 0 );
//      signal( SIGSEGV, sig_handler );
//      //
//      // and possibly other signals
//      //
//      // . . . main() logic . . .
//      return( 0 );
//  }
//
#ifndef MUWAVE_TRACE_H
#define MUWAVE_TRACE_H

#define TRACE_TAG_DEFAULT ("Dumping. . .")
#define TRACE_TAG_SIZE     15
#define TRACE_MSG_SIZE    255
#define TRACE_MAX          16

// public traceInit()
// Description -
//     Set parameters to initiate the trace functions
//     If this function is not called, defaults will be assigned
// input -
//     tag         - character string of maximum size TRACE_TAG_SIZE to be
//                   prepended to log dump header
//                   default is TRACE_TAG_DEFAULT
//     print_func  - print function provided by user
//                   default is the standard printf();
//     max_size    - the maximize number of most recent messages to be
//                   saved and then dumped
//                   if <= 0 or > TRACE_MAX, defaults to TRACE_MAX
//
void traceInit( char *tag, int (*print_func)(), int max_size );

// public traceDump()
// Description -
//     Dump all messages. The number of messages listed may be <= TRACE_MAX.
// Input -
//     desc - an optional descriptive message of maximum length
//            TRACE_HEAD_SIZE displayed before the dump
//
void traceDump( char *desc );

// public traceShow()
// Description -
//     Dump the specified number of most recent messages.
//     The number of messages dumped may be the specified number.
// Input -
//     num  - number of messages to be dumped
//     desc - an optional descriptive message of maximum length
//            TRACE_HEAD_SIZE displayed before the dump
//
void traceShow( int num, char *desc );

// public traceLog()
// Description -
//     Log a trace message
//     If the number of character exceeds MAX_MSG_SIZE, the message
//     will be truncated. However do NOT format the string to more than
//     511 characters
//     If the input string is (format) is allocated memeory, it may be
//     immediately freed after return from traceLog()
// Input -
//      format   - format string in the form of printf()
//      . . .    - a list of parameters in the form of printf()
// Return -
//     Number of characters logged
//
int traceLog( char *format, ... );

#endif //MUWAVE_TRACE_H
