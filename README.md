# trace
A small C-library intended to used for debugging signal errors, such as SIGSEGV.

You may customize to you liking.

A set of functions to log and dump and list of messages,
last in first out.

The messages are intended to be logged at various location in a program,
and then dumped at the signal handler sig_handler() on a signal such as
SIGSEGV.

A simpler version would be logging many times, traceLog() logs and save
only the most recent message, and traceDump() displays othat message.
This version saves and dumps a maximum of the most recent TRACE_MAX messages
logged.

intended usage -

#include <stdio.h>

#include <stdlib.h>

#include <signal.h>

#include "trace.h"

void sig_handler(int signo)
{
    if( signo ==  SIGSEGV ) {
        traceDump("Signal SIGSEGV");
    }   
    // may handle other signals
    exit( signo );
    
}

int main(int argc, char **argv)
{
    traceInit( "Prgram Test", &printf, 0 );
    signal( SIGSEGV, sig_handler );
      //
      // and possibly other signals
      //
      // . . . main() logic . . .
      return( 0 );
  }


For example, in Android NDK development, I find the it is difficult to get a trace dump on signal error. The android log may
have missing and out-of-order messages. This is a quick and easy solution to that. The messages can be logged any in the program.  



