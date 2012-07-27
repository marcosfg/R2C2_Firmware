/* Copyright (c) 2012 Bob Cousins bobcousins42@googlemail.com       */
/* All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef	_GCODE_TASK_H
#define	_GCODE_TASK_H

#include "FreeRTOS.h"
#include "queue.h"

//#include "gcode_parse.h"
#include "lw_io.h"

#define MAX_LINE 120

typedef struct
{
  char    data [MAX_LINE];
  int     len;

//  uint8_t seen_lf :1;
} tLineBuffer;

typedef enum {
  PR_RESEND,    // bad checksum     (rs ... response )
  PR_ERROR,     // invalid command  (E: ... response)
  PR_OK,        // valid, done      (ok ...)
  PR_OK_QUEUED, // valid, queued    (ok ...)
  PR_BUSY,      // valid, queue full (would block)  (busy)

  PR_READY      // queue no longer full
  } eParseResult;

// GCode input message
// This message is sent to gcode_task to process a line of GCode
typedef volatile struct 
{
    // The GCode line
    tLineBuffer *pLineBuf;

    bool in_use;

    // the file handle of the source control interface
    // gcode_task will write output to this file via lw_io
    // if NULL, no output generated
    LW_FILE *out_file;

    eParseResult result;

} tGcodeInputMsg;

extern xQueueHandle GcodeRxQueue;

void GcodeTask( void *pvParameters );



#endif
