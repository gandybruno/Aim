/******************************************************************************

           Copyright (c) AIM GmbH 2001, 79111 Freiburg, Germany.                 
                                                                             
            All rights reserved.  No part of this software may                
            be published, distributed, translated or otherwise                
            reproduced by any means or for any purpose without                
            the prior written consent of AIM GmbH, Freiburg.                  

******************************************************************************/
/*! \file Api429.h
 *
 *  This module contains the prototypes,defines and datatypes for the
 *  API429 application interface. This header must be included in the
 *  application modules.
 *
 */

#ifndef API429_H
#define API429_H

#include "Ai_cdef.h"
#include "Ai_def.h"


/**************************************
 Module Defines
**************************************/
#define MAX_API429_MODULE  32


#define API429_BIU_1    0
#define API429_BIU_2    1


/**************************************
 Client / Server Support
**************************************/
#define API429_SERVER_MASK           0xE0
#define API429_SERVER_POS               5
#define API429_MAX_SERVER               8

#define API_SERVER_REGISTERED           0
#define API_SERVER_NOT_REGISTERED       1


/* module extension codes */
#define API429_MODULE_MASK  0x1F

/* interrupt event buffer queue size (do not change - host and target have to use the same values) */
#define API429_MAX_IR_EVENT_BUF  256


#define API429_CMD_OK  0       /* command execution status OK     */
#define API429_CMD_ERR 1       /* command execution status ERROR  */

#define API429_DIS          0  /* disable value */
#define API429_ENA          1  /* enable value */

#define API429_TRUE         1  /* bool TRUE */
#define API429_FALSE        0  /* bool FALSE */



#define API429_TRG_ACT_DIS    0    /* disable extended action on trigger */


#define API429_EOS_POS        0   /* poitive offset */
#define API429_EOS_NEG        1   /* negative offset */

#define API429_HALT           1   /* channel operation HALT */
#define API429_BUSY           2   /* channel operation BUSY */
#define API429_ERR            3   /* channel operation ERROR */
#define API429_TX_HALT_LOOP   4   /* tx halt in loop/pollution mode */
#define API429_TX_BUSY_LOOP   5   /* tx busy in loop/pollution mode */
#define API429_TX_HALT_REP    6   /* tx halt in physical replay mode */
#define API429_TX_BUSY_REP    7   /* tx busy in physical replay mode */




/* for use in Api429TxXferBufferRead (mode) */
#define API_TXRXBUF_TT_UPDATE_CLEAR      1


#define API429_TX_MAX_REPLAY_SIZE        896   /* max number of ARINC words for replay reload data data block */

#define API429_XFER_TIC_EXEC             1     /* enable xfer interrupt bit */
#define API429_XFER_TIC_BUF              2     /* enable xfer interrupt bit */
#define API429_XFER_TIC_TCE              3     /* enable xfer counting */


/* defines for self test */
#define API429_BITE_ALL                  0     /* execute all selftests */
#define API429_BITE_BEN                  1     /* execute board enable test */
#define API429_BITE_INT                  2     /* execute internal selftest */
#define API429_BITE_RAM                  4     /* execute Paging Test */
#define API429_BITE_IRQ                  5     /* execute Interrupt Test */
#define API429_BITE_OK                   0     /* Selftest passed */



/* function Api429ReadBSPVersion(Ex) */
#define API429_BSP_COMPATIBLE            0x00
#define API429_BSP_NOT_COMPATIBLE        0xFF

#define API429_BSP_WRONG_TARGET_SW        0x03
#define API429_BSP_WRONG_BIU1_SW          0x04
#define API429_BSP_WRONG_BIU2_SW          0x05
#define API429_BSP_WRONG_LCA1_SW          0x06
#define API429_BSP_WRONG_LCA2_SW          0x07
#define API429_BSP_WRONG_SYS_WINDOWS      0x08
#define API429_BSP_WRONG_SYS_LINUX        0x09
#define API429_BSP_WRONG_SYS_USB_WIN      0x10
#define API429_BSP_WRONG_SYS_USB_LINUX    0x0A


typedef TY_DRIVER_INFO TY_429_API_DRIVER_INFO;


/**************************************
 Constants
**************************************/


#define API429_DBG_NONE         0x00000000
#define API429_DBG_TRACE        0x00000001
#define API429_DBG_INIT         0x00000002
#define API429_DBG_OPEN         0x00000004
#define API429_DBG_CLOSE        0x00000008
#define API429_DBG_READREC      0x00000010 /* read rep/rec area  (old style recording) */
#define API429_DBG_WRITEREP     0x00000020 /* write rep/rec area (old style recording) */
#define API429_DBG_DQUEUE       0x00000040
#define API429_DBG_INT          0x00000080
#define API429_DBG_PARAMCHK     0x00000100
#define API429_DBG_ERROR        0x40000000
#define API429_DBG_ALL          0xFFFFFFFF






/*************************************
 DLL specific DEFs
*************************************/

#define OFF 0
#define ON  1

#define API_OFF                   0
#define API_ON                    1

/* Return Value Defs */
#define API_OK                    0
#define API_ERR                   1
#define API_NOP                   2

/* BITE Expected Responses */
#define TG_BITE_OK  0


#if defined(_AIM_VME) || defined(_AIM_VMEWINDOWS)
  #include "AiVmeGeneric.h"
  #include "Api429Vme.h"
#endif

#include "A429_Errors.h"
#include "Api429Board.h"
#include "Api429Versions.h"
#include "Api429BoardMem.h"
#include "Api429Rx.h"
#include "Api429Replay.h"
#include "Api429Discretes.h"
#include "Api429Lib.h"
#include "Api429Rm.h"
#include "Api429Tx.h"
#include "Api429TxFifo.h"
#include "Api429Channel.h"


#endif

/* end: api429.h */
