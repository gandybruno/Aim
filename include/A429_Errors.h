/******************************************************************************

           Copyright (c) AIM GmbH 2010, 79111 Freiburg, Germany.

            All rights reserved.  No part of this software may
            be published, distributed, translated or otherwise
            reproduced by any means or for any purpose without
            the prior written consent of AIM GmbH, Freiburg.

******************************************************************************/
/*! \file civ_tsw_version.h
 *
 *  This module contains the definitions of the error codes and a
 *  human readable error description
 */

#ifndef A429_ERRORS_H
#define A429_ERRORS_H

#if defined _AIM_SYSDRV && defined _AIM_WINDOWS 
    #include <ntstatus.h>
    #include <ntstrsafe.h>
#endif

typedef struct {
   AiReturn ulNumber;
   const char* szFileName;
} TY_A429_TRANSLATE_TABLE;



/* Error identifier */
#define AI429_ERR_NONE                       0
#define AI429_ERR_UNABLE_TO_ACCESS           1
#define AI429_ERR_ACK                        2
#define AI429_ERR_ACK2                       3
#define AI429_ERR_NAK                        4
#define AI429_ERR_HOST_TO_TARGET             5
#define AI429_ERR_INVALID_DRIVER_HANDLE      6
#define AI429_ERR_IOCTL_TIMEOUT              7
#define AI429_ERR_IOCTL_ERROR                8
#define AI429_ERR_FUNCTION_NOT_IMPLEMENTED   9
#define AI429_ERR_COMMAND_SIZE               10
#define AI429_ERR_XFER_ID                    11
#define AI429_ERR_MIN_FRM_ID                 12
#define AI429_ERR_NO_MORE_MEMORY             13
#define AI429_ERR_INVALID_SIZE               14
#define AI429_ERR_INVALID_BOARD              15
#define AI429_ERR_INVALID_POLL_BLK_ID        16
#define AI429_ERR_SDI_NOT_ENABLED            17
#define AI429_ERR_INVALID_CHANNEL            18
#define AI429_ERR_MODE                       19
#define AI429_ERR_NULL_POINTER               20
#define AI429_ERR_ID                         21
#define AI429_ERR_SERVER                     22
#define AI429_ERR_INVALID_MODULE_HANDLE      23
#define AI429_ERR_INVALID_MODULE_ID          24
#define AI429_ERR_MYMON                      25
#define AI429_ERR_PARAMETER_RANGE            26
#define AI429_ERR_DYNTAG_SIZE                27
#define AI429_ERR_ACK_SIZE                   28
#define AI429_ERR_TIMEOUT                    29
#define AI429_ERR_32BIT_TRANSFER_REQUIRED    30
#define AI429_ERR_BUFFER_OVERFLOW            31
#define AI429_ERR_NET_COMMAND                32
#define AI429_ERR_INVALID_CHANNEL_CONNECTION 33
#define AI429_ERR_OLD_FIRMWARE               34
#define AI429_ERR_INVALID_RATE               35
#define AI429_ERR_CHANNEL_ACTIVE             36
#define AI429_ERR_FIX_CHANNEL                37
#define AI429_ERR_INVALID_CHANNEL_MODE       38
#define AI429_ERR_INVALID_FRAME              39
#define AI429_ERR_INTERNAL                   40
#define AI429_ERR_OLD_TARGET_SW              41


#define AI429_ERR_42                         42


#define AI429_ERR_SERVER_INCOMPATIBLE        43
#define AI429_ERR_DISCRETE_CONFIG            44





#define AI429_ERR_UNKNOWN                   -1

/* end of table */




#define DEFINE_ERROR_TABLE \
static const TY_A429_TRANSLATE_TABLE ax_A429TargetErrorDescription[] = { \
            {AI429_ERR_NONE                         ,"No error"}, \
            {AI429_ERR_UNABLE_TO_ACCESS             ,"Unable to access board"}, \
            {AI429_ERR_ACK                          ,"Target incorrectly returned ACK without data"}, \
            {AI429_ERR_ACK2                         ,"Target incorrectly returned ACK2 with data"}, \
            {AI429_ERR_NAK                          ,"Target reports generic error"}, \
            {AI429_ERR_HOST_TO_TARGET               ,"Host to target communication error"}, \
            {AI429_ERR_INVALID_DRIVER_HANDLE        ,"IOCTL error invalid driver handle"}, \
            {AI429_ERR_IOCTL_TIMEOUT                ,"IOCTL timeout"}, \
            {AI429_ERR_IOCTL_ERROR                  ,"IOCTL driver error"}, \
            {AI429_ERR_FUNCTION_NOT_IMPLEMENTED     ,"Function is not implemented"}, \
            {AI429_ERR_COMMAND_SIZE                 ,"Host to target command has invalid size"}, \
            {AI429_ERR_XFER_ID                      ,"Invalid Xfer ID"}, \
            {AI429_ERR_MIN_FRM_ID                   ,"Invalid minor frame ID"}, \
            {AI429_ERR_NO_MORE_MEMORY               ,"Not enough onboard memory available"}, \
            {AI429_ERR_INVALID_SIZE                 ,"Invalid size"}, \
            {AI429_ERR_INVALID_BOARD                ,"Board does not support this command"}, \
            {AI429_ERR_INVALID_POLL_BLK_ID          ,"Invalid pollution block ID"}, \
            {AI429_ERR_SDI_NOT_ENABLED              ,"SDI for this channel not enabled in the Api429CmdReset command, or out of range"}, \
            {AI429_ERR_INVALID_CHANNEL              ,"Invalid Channel"}, \
            {AI429_ERR_MODE                         ,"Invalid mode"}, \
            {AI429_ERR_NULL_POINTER                 ,"Null pointer used as parameter"}, \
            {AI429_ERR_ID                           ,"Invalid ID"}, \
            {AI429_ERR_SERVER                       ,"Unable to connect to server"}, \
            {AI429_ERR_INVALID_MODULE_HANDLE        ,"Module handle is invalid"}, \
            {AI429_ERR_INVALID_MODULE_ID            ,"Invalid module number"}, \
            {AI429_ERR_MYMON                        ,"MyMon Error"}, \
            {AI429_ERR_PARAMETER_RANGE              ,"A Parameter is out of range"}, \
            {AI429_ERR_DYNTAG_SIZE                  ,"On channels configured for Dyntags the buffer size has to be '1'"}, \
            {AI429_ERR_ACK_SIZE                     ,"Host to target acknowledge has invalid size"}, \
            {AI429_ERR_TIMEOUT                      ,"Timeout within the target software"}, \
            {AI429_ERR_32BIT_TRANSFER_REQUIRED      ,"Buffer is out of range. 32Bit Label Transfer required"}, \
            {AI429_ERR_BUFFER_OVERFLOW              ,"Buffer is too small"}, \
            {AI429_ERR_NET_COMMAND                  ,"Network command failure"}, \
            {AI429_ERR_INVALID_CHANNEL_CONNECTION   ,"Channels can not be connected due to hardware constraints"}, \
            {AI429_ERR_OLD_FIRMWARE                 ,"Firmware requires update"}, \
            {AI429_ERR_INVALID_RATE                 ,"Unable to create framing with the given rates"}, \
            {AI429_ERR_CHANNEL_ACTIVE               ,"The channel is still active"}, \
            {AI429_ERR_FIX_CHANNEL                  ,"The channel configuration is fix and cannot be changed"}, \
            {AI429_ERR_INVALID_CHANNEL_MODE         ,"The channel set-up does not match expected mode"}, \
            {AI429_ERR_INVALID_FRAME                ,"Framing error"}, \
            {AI429_ERR_INTERNAL                     ,"Internal error"}, \
            {AI429_ERR_OLD_TARGET_SW                ,"Target requires update"}, \
            {AI429_ERR_42                           ,"Answer to the Ultimate Question of Life, The Universe, and Everything"}, \
            {AI429_ERR_SERVER_INCOMPATIBLE          ,"Connection to incompatible remote server failed"}, \
            {AI429_ERR_DISCRETE_CONFIG              ,"The operation can not be applied due to mismatching discrete channel configuration"}, \
\
\
            {AI429_ERR_UNKNOWN                      ,"Unknown error" } \
};




/************************************/
/* define to set NAK info           */
/************************************/


#define SET_NAK_INFO(x)  \
  do { \
    p_api_dev->ulNakInfo = x; \
  } while(0);
    


#endif

/* EOF */
