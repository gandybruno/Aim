/******************************************************************************

           Copyright (c) AIM GmbH 2016, 79111 Freiburg, Germany.

            All rights reserved.  No part of this software may
            be published, distributed, translated or otherwise
            reproduced by any means or for any purpose without
            the prior written consent of AIM GmbH, Freiburg.

******************************************************************************/
/*! \file Api429_bsp10_legacy.h
 *
 *  This header file contains INLINE functions
 *  that help users of BSPs before 10.0 to get their
 *  old applications running.
 *
 *  Created on: 07.03.2016
 *      Author: Markus Melcher
 */

#ifndef API429_BSP10_LEGACY_H_
#define API429_BSP10_LEGACY_H_


#include "Api429.h"
#include "Api429BoardDriver.h"
#include "Api429Update.h"

#include <string.h> // for memset
#include <stdlib.h> // for malloc








struct global_variables_for_legacy_handling
{
    AiUInt32 interrupt_mode;
    AiUInt32 mbuf_size;
    AiUInt16 tat;
    AiBoolean useSdi; /*TODO: one instance per channel*/
};



/* An array of the above struct is used to remember values, when translating old command into current ones.
 * This array is only used within this legacy header and nowhere else.
 */
AI_LIB_FUNC struct global_variables_for_legacy_handling  axGlobalVariables[MAX_API429_MODULE * API429_MAX_SERVER];


#define API429_MODULE_1   0         /* destination code first API*/
#define API429_MODULE_2   1         /* destination code second API if installed */
#define API429_MODULE_3   2         /* destination code third API if installed  */
#define API429_MODULE_4   3         /* destination code fourth API if installed */
#define API429_MODULE_5   4         /* destination code fifth API if installed */
#define API429_MODULE_6   5         /* destination code sixth API if installed */
#define API429_MODULE_7   6         /* destination code seventh API if installed */
#define API429_MODULE_8   7         /* destination code eighth API if installed */
#define API429_MODULE_9   8         
#define API429_MODULE_10  9         
#define API429_MODULE_11 10         
#define API429_MODULE_12 11         
#define API429_MODULE_13 12         
#define API429_MODULE_14 13         
#define API429_MODULE_15 14         
#define API429_MODULE_16 15         
#define API429_MODULE_17 16         
#define API429_MODULE_18 17         
#define API429_MODULE_19 18         
#define API429_MODULE_20 19         
#define API429_MODULE_21 20         
#define API429_MODULE_22 21         
#define API429_MODULE_23 22         
#define API429_MODULE_24 23         
#define API429_MODULE_25 24         
#define API429_MODULE_26 25         
#define API429_MODULE_27 26         
#define API429_MODULE_28 27         
#define API429_MODULE_29 28         
#define API429_MODULE_30 29         
#define API429_MODULE_31 30         
#define API429_MODULE_32 31         

#define MAX_API429_CHN 32

#define API_MEMTYPE_GLOBAL          0
#define API_MEMTYPE_SHARED          1
#define API_MEMTYPE_LOCAL           2
#define API_MEMTYPE_IO              3
#define API_MEMTYPE_GLOBAL_UNCACHED 4

/* function Api429GetMemLocation */
#define API429_GETMEM_XFER               1
#define API429_GETMEM_XFER_BUF           2
#define API429_GETMEM_MINFRM             3
#define API429_GETMEM_MAJFRM             4
#define API429_GETMEM_LABDESC            5
#define API429_GETMEM_RXBUF              6
#define API429_GETMEM_TXCOUNT            7
#define API429_GETMEM_CHN_DESC           8

/* function Api429ReadBSPVersion(Ex) */
#define API429_BSP_COMPATIBLE            0x00
#define API429_BSP_NOT_COMPATIBLE        0xFF

/* Api429CmdTxIni */
#define API429_TX_MODE_FRAMING           0     /* standard framing mode */
#define API429_TX_MODE_POLLUT            1     /* polluton mode */
#define API429_TX_MODE_REPLAY            0xFF     /* replay mode --> no longer used*/
#define API429_TX_MODE_PHYS_REPLAY       2     /* physical replay mode */
#define API429_TX_MODE_FRAMING_DYNTAG    3     /* standard framing mode with dyntags */


/* defines for receiver */
#define API429_RX_MODE_NORM              0     /* normal receive mode */
#define API429_RX_MODE_LOOP              1     /* loop mode */


/* defines for receiver monitor */
#define API429_TAT_REC                   0     /* continous capturing */
#define API429_MON_MODE_LOC              0     /* local monitoring */
#define API429_MON_MODE_GLB              1     /* global monitoring */
#define API429_SPT_STP                   0     /* API capture start pointer */
#define API429_SPT_CTP                   1     /* API trigger pointer */
#define API429_SPT_ETP                   2     /* API capture end pointer */


/* Api429CmdReset */
#define API429_FULL_RESET                0     /* Complete Reset */


/* Monitor Capture Mode */
#define API429_MON_CAP_STANDARD          0
#define API429_MON_CAP_RECORDING         1


/* defines for trigger */
#define API429_TRG_START      0   /* trigger on start function */
#define API429_TRG_ERR        1   /* trigger on any error */
#define API429_TRG_EXT        2   /* trigger on external input */
#define API429_TRG_ANY        3   /* trigger on first event */

#define API429_TRG_IR_DIS     0   /* disable trigger interrupt */
#define API429_TRG_IR_START   1   /* enable interrupt on START trigger */
#define API429_TRG_IR_STOP    2   /* enable interrupt on STOP trigger */
#define API429_TRG_IR_BFI     3   /* enable interrupt on buffer full */
#define API429_TRG_IR_HFI     4   /* enable interrupt on half buffer full */

#define API429_TRG_ACT_DIS    0    /* disable extended action on trigger */

/* Api429CmdTxStart */
#define API429_TX_MAJFRAME              0     /* execute major frame */
#define API429_TX_ACYCLIC               1     /* execute acyclic instruction list */
#define API429_TX_POLLUT                2     /* execute pollution mode */
#define API429_TX_REPLAY                3     /* execute replay mode */
#define API429_TX_PHYS_REPLAY           4     /* execute physical replay mode */

#define API429_TX_MAJFRAME_CYCLIC       0     /* excute major frame cyclic */
#define API429_TX_REPLAY_CYCLIC         0     /* excute replay mode cyclic */

#define API429_TX_START_IMM             0     /* start transmission immediately */
#define API429_TX_START_EXT             1     /* start transmission via ext. trigger */
#define API429_TX_START_TTG             2     /* start transmission on timetag */
#define API429_TX_START_NO_WFMFT        3     /* start transmission immediately, skipping the first 
                                               * wait-for-minor-frame-time firmware instruction */
#define API429_TX_START_PREPARE_FRAMING 4     /* do not start, but create framing (if tx channel 
                                               * was initialized with API429_TX_MODE_AUTO_FRAME */
                                               
                                               
                                               
#define API429_PXI_SET_TTSRC_EXTERNAL    2  /* obsolete, replaced by API429_PXI_SET_TTSRC_BACKPLANE */
#define API429_PXI_SET_TTSRC_INTERNAL    3  /* obsolete, replaced by API429_PXI_SET_TTSRC_FRONT */


/* fifo functions */
#define API429_FIFO_WRITE_DEFAULT          0
#define API429_FIFO_WRITE_BLOCKING         1


/* Define Receiver Monitor Capture Mode Command structure */
typedef struct
   {
   AiUInt8  mode;
   AiUInt8  padding1;
   AiUInt16  padding2;
   AiUInt16 tat;
   AiUInt16 reserved;
   AiUInt32 rec_filesize;
   } TY_API429_RCV_CAP_MODE_CMD;
   
/* Define Receiver Monitor Trigger Parameter Command structure */
typedef struct
   {
   AiUInt8 start_pat;
   AiUInt8 start_mask;
    AiUInt8 stop_pat;
   AiUInt8 stop_mask;
   } TY_API429_TRG_PAR_CMD;

   /* Define Receiver Monitor Function Block Command structure */
typedef struct
   {
   AiUInt8 fb_id;
   AiUInt8 fbi;
   AiUInt8 ir;
   AiUInt8 ulc;
   AiUInt8 uli;
   AiUInt8 llc;
   AiUInt8 lli;
   AiUInt8 fe;
   AiUInt32 trg_set;
   AiUInt32 trg_reset;
   AiUInt16 pre_cnt;
    AiUInt16 pre_rel;
   AiUInt32 mask;
   AiUInt32 ulim;
   AiUInt32 llim;
   AiUInt8  ext_trg;
    AiUInt8  trg_line;
   } TY_API429_RCV_FB_CMD;


typedef struct
{
	AiUInt32 ul_NrOfChannels;
	AiUInt32 ul_DiscreteSetup;
} TY_API429_DISCR_CONFIG_GET;

typedef struct
{
       AiUInt32 l_StartMode;
       AiUInt32 l_Mode;
       AiUInt32 l_ModeSpec;
       AiUInt32 l_TrgLine;
       AiUInt32 l_TTDay;
       AiUInt32 l_TTHour;
       AiUInt32 l_TTMinute;
       AiUInt32 l_TTSec;
       AiUInt32 l_TTuSec;
} TY_API429_TXSTART;


#define API429_RESET_ALL                  0
#define API429_RESET_READ                 1

/* Reset Command structure */
typedef struct
{
    AiUInt8 res_ctl;
    AiUInt8 glob_speed_mod;
    AiUInt8 low_speed_sel;
    AiUInt8 tx_clock_sel;
    AiUInt32 sm;
    AiUInt32 lcen;
    AiUInt32 mbuf_size;
    AiUInt32 chn_cfg;
} TY_API429_RESET_CMD;

/* Reset Command Acknowledge structure */
typedef struct
{
    AiUInt16 chn_cnt;
    AiUInt16 padding1;
    AiUInt32 pchc;
    AiUInt32 txrx_mem_start;
    AiUInt32 txrx_mem_end;
    AiUInt32 res1;
    AiUInt32 res2;
    AiUInt32 rm_mem_start[API429_MAX_CHANNELS];
    AiUInt32 rm_mem_size[API429_MAX_CHANNELS];
} TY_API429_RESET_ACK;

typedef struct api429_device_config
{
    AiUInt32 ul_DmaEnabled;
    AiUInt32 ul_DmaMinimumSize;
    AiUInt32 ul_ReservedLW2;
    AiUInt32 ul_ReservedLW3;
    AiUInt32 ul_ReservedLW4;
    AiUInt32 ul_ReservedLW5;
    AiUInt32 ul_ReservedLW6;
    AiUInt32 ul_ReservedLW7;
    AiUInt32 ul_ReservedLW8;
} TY_API429_DEVICE_CONFIG;

typedef struct
{
    AiUInt32 ul_DiscreteChannelId; /* Discrete to send the PPS signal to */
    AiUInt32 ul_EnaDis; /* if set to '1' enable, if set to '0' disable */
} TY_API429_DISCR_PPS;


typedef struct
{
  AiUInt8  uc_Status;
  AiUInt8  uc_Padding1;
  AiUInt16 uw_Padding2;
  AiUInt32 ul_RpiCnt;
  AiUInt32 ul_EntryCnt;
  AiUInt32 ul_StartAddr;
  AiUInt32 ul_Size;
} TY_API429_REP_STATUS;


typedef struct
   {
   AiUInt8 tmod;
   AiUInt8 exti;
   AiUInt8 imod;
   AiUInt8 ext;
   AiUInt8 exto;
   AiUInt8 exta;
   AiUInt8 extad;
   AiUInt8 reserved;
   } TY_API429_RCV_TRG_MODE_CMD;


   /* Label transfer structure */
   typedef struct
     {
       AiUInt32 xfer_id;
       AiUInt8  xfer_type;
       AiUInt8  xfer_ir;
       AiUInt16 padding1;
       AiUInt16 ir_index;
       AiUInt16 buf_size;
       AiUInt8  err_type;
       AiUInt8  err_type_ext;
       AiUInt16 xfer_gap;
       AiUInt8  extTrigger;
     } TY_API429_LXFER_CMD;

   typedef struct
   {
     AiUInt32  ul_Status;
     AiUInt32  ul_FreeMem;
     AiUInt32  ul_XferDescAddr;
   } TY_API429_LXFER_OUT;


   typedef struct api429_server_info
   {
	   AiChar szNBComputerName[128]; //!< NetBios related Computer Name
	   AiChar szApplicationName[128]; //!< Application name of the ANS software (AIM Network Server), if available
	   AiChar szCompanyName[64]; //!< Reserved
	   AiChar szCopyright[64]; //!< Reserved
	   AiChar szDescription[128]; //!< Description
	   AiChar szBuiltDate[64]; //!< Reserved
	   AiUInt16 usMajorVersion; //!< Major Version of the ANS server, if available
	   AiUInt16 usMinorVersion; //!< Minor Version of the ANS server, if available
	   AiUInt uiBuiltNumber;  //!< Reserved
	   AiChar szIFUuid[128]; //!< Reserved
	   AiUInt16 usIFMajorVersion; //!< Major Version of the internal network interface
	   AiUInt16 usIFMinorVersion; //!< Minor Version of the internal network interface
	   AiUInt8 bSrvOSVersion; //!< Reserved
   } TY_API429_SERVERINFO;


#define API_IRIG_SET 0 
#define API_IRIG_CHANGE_TIMETAG_SOURCE 1

typedef struct
{
    AiUInt8 b_DayHi;
    AiUInt8 b_DayLo;
    AiUInt8 b_Hour;
    AiUInt8 b_Min;
    AiUInt8 b_Sec;
    AiUInt8 b_MsHi;
    AiUInt8 b_MsLo;
    AiUInt8 b_mode;
    AiUInt8 b_irig_src;
    AiUInt8 b_irig_sync;
} TY_API429_IRIG_TIME;


typedef void (_API_ISR_FUNC *TY_INT429_FUNC_PTR)(AiUInt8 uc_Module, AiUInt8 uc_Chn, AiUInt8 uc_Type, TY_API429_INTR_LOGLIST_ENTRY x_Info);



static AiUInt8 INLINE(Api429CmdGetIrigTime(AiUInt8 b_Module, TY_API429_IRIG_TIME *px_IrigTime))
{
    AiReturn ret = 0;
    enum api429_irig_source source;
    AiBoolean sync;
    struct api429_time irig_time;

    ret = Api429BoardTimeSourceGet(b_Module, &source, &sync);
    if (ret != 0)
        return 1;

    ret = Api429BoardTimeGet(b_Module, &irig_time);
    if (ret != 0)
        return 1;

    px_IrigTime->b_DayHi = (AiUInt8) (irig_time.day / 0x100);
    px_IrigTime->b_DayLo = irig_time.day % 0x100;
    px_IrigTime->b_Hour = (AiUInt8) irig_time.hour;
    px_IrigTime->b_Min = (AiUInt8) irig_time.minute;
    px_IrigTime->b_Sec = (AiUInt8) irig_time.second;
    px_IrigTime->b_MsHi = (AiUInt8) (irig_time.millisecond / 0x100);
    px_IrigTime->b_MsLo = (AiUInt8) (irig_time.millisecond & 0x100);

    px_IrigTime->b_mode = 0;
    px_IrigTime->b_irig_sync = (AiUInt8)sync;
    px_IrigTime->b_irig_src = (AiUInt8)source;

    return 0;
}

static AiUInt8 INLINE(Api429CmdSetIrigTime(AiUInt8 b_Module, TY_API429_IRIG_TIME *px_IrigTime))
{
    AiReturn ret = 0;
    enum api429_irig_source source;
    struct api429_time irig_time;

    switch (px_IrigTime->b_mode)
    {

    case API_IRIG_SET:
        irig_time.day = (AiUInt32) ((px_IrigTime->b_DayHi *256) + px_IrigTime->b_DayLo);
        irig_time.hour = px_IrigTime->b_Hour;
        irig_time.minute = px_IrigTime->b_Min;
        irig_time.second = px_IrigTime->b_Sec;
        irig_time.millisecond = (AiUInt32) ((px_IrigTime->b_MsHi * 256) + px_IrigTime->b_MsLo);

        ret = Api429BoardTimeSet(b_Module, &irig_time);
        return (AiUInt8) ret;

    case API_IRIG_CHANGE_TIMETAG_SOURCE:
        source = (enum api429_irig_source) px_IrigTime->b_irig_src;
        ret = Api429BoardTimeSourceSet(b_Module, source);
        return (AiUInt8) ret;

    default:
        return 1;
    }

}



static AiReturn INLINE(Api429CmdTxStartEx( AiUInt8 b_Module, AiUInt8 b_Chn, TY_API429_TXSTART *px_TxStartIn ))
{
    AiReturn retval = 0;
    TY_API429_TIME start_time = {0};

    switch( px_TxStartIn->l_Mode )
    {
    case API429_TX_MAJFRAME:
        Api429TxRepetitionCountSet(b_Module, b_Chn, px_TxStartIn->l_ModeSpec);

        if( px_TxStartIn->l_StartMode == API429_TX_START_EXT )
        {
            retval = Api429TxStartOnTrigger(b_Module, b_Chn, px_TxStartIn->l_TrgLine);
        }
        else if( px_TxStartIn->l_StartMode == API429_TX_START_TTG )
        {
            start_time.day = px_TxStartIn->l_TTDay;
            start_time.hour = px_TxStartIn->l_TTHour;
            start_time.minute = px_TxStartIn->l_TTMinute;
            start_time.second = px_TxStartIn->l_TTSec;
            start_time.millisecond = px_TxStartIn->l_TTuSec;

            retval = Api429TxStartOnTTag(b_Module, b_Chn, &start_time);
        }
        else if( px_TxStartIn->l_StartMode == API429_TX_START_PREPARE_FRAMING )
        {
            retval = Api429TxPrepareFraming(b_Module, b_Chn);
        }
        else
        {
            retval = Api429ChannelStart(b_Module, b_Chn);
        }

        break;

    case API429_TX_ACYCLIC:
        retval = Api429TxAcycFrameSend(b_Module, b_Chn, px_TxStartIn->l_ModeSpec);
        break;

    case API429_TX_POLLUT:
    case API429_TX_PHYS_REPLAY:
        retval = Api429ChannelStart(b_Module, b_Chn);
        break;

    case API429_TX_REPLAY:
    default:
        retval = AI429_ERR_MODE;
        break;
    }

    return retval;
}

static AiUInt8 INLINE(Api429CmdTxStart( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt8 b_StartMode, AiUInt8 b_Mode, AiUInt16 w_ModeSpec, AiUInt8 b_TrgLine) )
{
    TY_API429_TXSTART x_TxStartIn;

    x_TxStartIn.l_StartMode = b_StartMode;
    x_TxStartIn.l_Mode = b_Mode;
    x_TxStartIn.l_ModeSpec = w_ModeSpec;
    x_TxStartIn.l_TrgLine = b_TrgLine;
    x_TxStartIn.l_TTDay = 0;
    x_TxStartIn.l_TTHour = 0;
    x_TxStartIn.l_TTMinute = 0;
    x_TxStartIn.l_TTSec = 0;
    x_TxStartIn.l_TTuSec = 0;

    return (AiUInt8) Api429CmdTxStartEx( b_Module, b_Chn, &x_TxStartIn );
}

static const INLINE(char* Api429GetErrorDescription ( AiReturn ul_ErrorCode))
{
    return Api429LibErrorDescGet(ul_ErrorCode);
}

static AiUInt8 INLINE(Api429Init(void))
{
    return (AiUInt8) Api429LibInit();
}


static AiUInt8 INLINE(Api429Exit(void))
{
    return (AiUInt8) Api429LibExit();
}


static short INLINE(Api429SetDllDbgLevel( AiUInt32 ul_DllDbgLevel ))
{
    return (short) Api429LibDebugLevelSet(ul_DllDbgLevel);
}


static void INLINE(Api429SetPnpCallback( void* PnPCallbackFunction ))
{
    Api429LibPnpCallbackSet((TY_429PNP_CALLBACK_FUNC_PTR) PnPCallbackFunction);
}


static AiUInt8 INLINE(Api429ConnectToServer ( const char * pszNetworkAdress, AiInt16 *w_ServerBoards))
{
    return (AiUInt8) Api429LibServerConnect(pszNetworkAdress, w_ServerBoards);
}


static AiInt16 INLINE(Api429DisconnectFromServer( const char * pszNetworkAdress ))
{
    return (AiInt16) Api429LibServerDisconnect(pszNetworkAdress);
}


static const INLINE(char* Api429GetBoardName( AiUInt8 b_Module ))
{
    return Api429BoardNameGet(b_Module);
}




static AiUInt8 INLINE(Api429CmdReset_correctChannelSetup(AiUInt8 b_Module, TY_API429_RESET_CMD  *px_Cmd))
{
    AiUInt8 ret;
    AiUInt8 chn;
    struct api429_channel_info channelInfo;

    for (chn = 0; chn < 32; chn++)
    {
        ret = (AiUInt8) Api429ChannelInfoGet(b_Module, (AiUInt8) (chn + 1), &channelInfo);
        if (ret) { continue; }

        if (!API429_CHANNEL_CAN_RECEIVE(channelInfo))
        {
            /* If channel can't be set to receive, try to set it to transmit 
             * A check for valid tx channels follows*/
            px_Cmd->chn_cfg |= (1 << chn);
        }

        if (!API429_CHANNEL_CAN_TRANSMIT(channelInfo))
        {
            /* If a channel can't be set to transmit, set the bit to zero */
            px_Cmd->chn_cfg &= ~(1 << chn);
        }
    }

    return 0;
}

static AiUInt8 INLINE(Api429CmdReset( AiUInt8 b_Module, TY_API429_RESET_CMD  *px_Cmd, TY_API429_RESET_ACK * px_Ackn ))
{
    AiReturn ret = 0;
    AiReturn retOverall = 1;
    AiUInt8 chn = 0;
    AiBoolean useSdi = AiFalse;
    struct api429_board_info boardInfo;
    struct api429_channel_info channelInfo;
    TY_API429_RM_SETUP rmsetup;
    TY_E_MEM_TYPE memType;
    AiUInt32 rmBufferStart[API429_MAX_CHANNELS];

    if (px_Cmd->mbuf_size == 0)
        px_Cmd->mbuf_size = 1024;

    if (px_Cmd == NULL)
        return AI429_ERR_NULL_POINTER;
    if (px_Ackn == NULL)
        return AI429_ERR_NULL_POINTER;


    ret = Api429BoardInfoGet(b_Module, &boardInfo);
    if (ret) { goto HANDLE_OUTPUT_PARAMETER; }

    /* for boards with a fix channel configuration, adapt it accordingly */
    ret = Api429CmdReset_correctChannelSetup( b_Module, px_Cmd);
    if (ret) { goto HANDLE_OUTPUT_PARAMETER; }

    if (px_Cmd->res_ctl == API429_RESET_ALL)
    {
        /* clear all variables used to remember board settings */
        memset(&axGlobalVariables[b_Module], 0, sizeof(struct global_variables_for_legacy_handling));

        ret = Api429BoardReset(b_Module);
        if (ret) { goto HANDLE_OUTPUT_PARAMETER; }

        /* px_Cmd->lcen is ignored. Now indivual label counters are always enabled*/

        ret = Api429BoardSpeedModifierSet(b_Module, (TY_E_API429_SPEED_MODIFIER)px_Cmd->glob_speed_mod);
        if (ret) { goto HANDLE_OUTPUT_PARAMETER; }


        ret = Api429BoardLsGradeSet(b_Module, (TY_E_API429_LOW_SPEED_GRADE)px_Cmd->low_speed_sel);
        if (ret) { goto HANDLE_OUTPUT_PARAMETER; }


        for (chn = 0; chn < boardInfo.num_channels; chn++)
        {
            if (((px_Cmd->chn_cfg >> chn) & 0x1) == 1) /* if channel shall be set to transmit */
            {
                ret = Api429TxInit(b_Module, (AiUInt8) (chn + 1), (TY_E_API429_TX_MODE)API429_TX_MODE_FRAMING, AiTrue /*parity*/);
                if (ret) { goto HANDLE_OUTPUT_PARAMETER; }
            }
            else  /* channel shall be set to receiver */
            {
                if (((px_Cmd->sm >> chn) & 0x1) == 1)
                    useSdi = AiTrue;
                else
                    useSdi = AiFalse;

                ret = Api429RxInit(b_Module, (AiUInt8) (chn + 1), useSdi, AiTrue /*parity*/);
                if (ret) { goto HANDLE_OUTPUT_PARAMETER; }

                axGlobalVariables[b_Module].useSdi = useSdi;  //remember useSdi for later calls of Api429RxInit

                memset(&rmsetup, 0, sizeof(rmsetup));
                rmsetup.size_in_entries = px_Cmd->mbuf_size;
                ret = Api429RmCreate(b_Module, (AiUInt8) (chn + 1), &rmsetup);
                if (ret) { goto HANDLE_OUTPUT_PARAMETER; }

                axGlobalVariables[b_Module].mbuf_size = px_Cmd->mbuf_size;  //remember mbuf_size for later calls of Api429RmCreate

                ret = Api429BoardMemLocationGet(b_Module, (AiUInt8)(chn + 1), API429_MEM_OBJ_RM_BUF, 0, &memType, &rmBufferStart[chn]);
            }
        }
    }



    retOverall = 0;


HANDLE_OUTPUT_PARAMETER:


    px_Ackn->chn_cnt = (AiUInt16) boardInfo.num_channels;
    px_Ackn->padding1 = 0;
    px_Ackn->pchc = 0;
    px_Ackn->txrx_mem_start = 0;
    px_Ackn->txrx_mem_end = 0;
    px_Ackn->res1 = 0;
    px_Ackn->res2 = 0;


    for( chn=0; chn<boardInfo.num_channels; chn++ )
    {
        ret = Api429ChannelInfoGet(b_Module, (AiUInt8) (chn + 1), &channelInfo);
        if (ret) { goto HANDLE_OUTPUT_PARAMETER; }

        px_Ackn->rm_mem_start[chn] = 0;
        px_Ackn->rm_mem_size[chn] = 0;

        if (API429_CHANNEL_IN_TX_MODE(&channelInfo))
        {
            px_Ackn->pchc |= 1 << chn;
        }
        else  /* channel is receiver */
        {
            if (API429_CHANNEL_IN_RX_MODE(&channelInfo))
            {
                px_Ackn->pchc &= ~(1 << chn);
                px_Ackn->rm_mem_size[chn] = axGlobalVariables[b_Module].mbuf_size * sizeof(TY_API429_RCV_STACK_ENTRY);
                px_Ackn->rm_mem_start[chn] = rmBufferStart[chn];
            }
        }
    }

    return (AiUInt8) retOverall;
}


static short INLINE(Api429Open( AiUInt8 b_Module, const char *ac_SrvName, AiUInt8 *bModuleHandle ))
{
    return (short) Api429BoardOpen((enum api429_board_id) b_Module, ac_SrvName, bModuleHandle);
}


static AiUInt8 INLINE(Api429Close( AiUInt8 b_Module ))
{
    return (AiUInt8) Api429BoardClose(b_Module);
}


static AiInt16 INLINE(Api429SetDeviceConfig( AiUInt8 b_Module, TY_API429_DEVICE_CONFIG * pxConfig ))
{
    return (AiInt16) Api429BoardDriverConfigSet(b_Module, (TY_API429_DRIVER_CONFIG*)pxConfig);
}


static AiInt16 INLINE(Api429SetDeviceConfigDefault( AiUInt8 b_Module ))
{
    return (AiInt16) Api429BoardDriverConfigSetDefault(b_Module);
}


static AiInt16 INLINE(Api429GetDeviceConfig( AiUInt8 b_Module, TY_API429_DEVICE_CONFIG * pxConfig ))
{
    return (AiInt16) Api429BoardDriverConfigGet(b_Module, (TY_API429_DRIVER_CONFIG*)pxConfig);
}


static AiUInt8 INLINE(Api429CmdBite( AiUInt8 b_Module, AiUInt8 b_Func, AiUInt8 *pb_Status, AiUInt8  *pb_Echo ))
{
    return (AiUInt8) Api429BoardSelftest(b_Module, b_Func, pb_Status, pb_Echo);
}


static AiUInt8 INLINE(Api429CmdChannelWrapControl( AiUInt8 uc_Module, AiUInt32 ul_Control ))
{
    return (AiUInt8) Api429BoardChannelCouplingSet(uc_Module, (TY_E_API429_CHANNEL_COUPLING)ul_Control);
}


static AiUInt8 INLINE(Api429CmdChannelWrapGetConnection( AiUInt8 uc_Module, AiUInt8 auc_Connection[API429_MAX_CHANNELS+1] ))
{
    return (AiUInt8) Api429BoardChannelCouplingInfo(uc_Module, auc_Connection);
}


static AiUInt8 INLINE(Api429CmdChannelWrapIsSupported( AiUInt8 uc_Module, AiUInt8 *pucResult ))
{
    return (AiUInt8) Api429BoardChannelCouplingIsSupported(uc_Module, pucResult);
}


static AiInt16 INLINE(Api429GetDriverInfo( AiUInt8 uc_Module, TY_429_API_DRIVER_INFO * pxDriverInfo ))
{
    return (AiInt16) Api429BoardDriverInfoGet(uc_Module, pxDriverInfo);
}


typedef struct
{
    AiUInt32 ul_Mode;
    AiUInt32 ul_TrgSource;
    AiUInt32 ul_TrgDest;
    AiUInt32 ul_TTClear;
} TY_API429_PXI_CON;

static AiUInt8 INLINE(Api429CmdSysPXICon( AiUInt8 uc_Module, TY_API429_PXI_CON *px_PxiCon))
{
    enum api429_pxi_mode ul_Mode = (enum api429_pxi_mode)px_PxiCon->ul_Mode;
    enum api429_pxi_trigger_line ul_TrgSource = (enum api429_pxi_trigger_line)px_PxiCon->ul_TrgSource;
    enum api429_pxi_trigger_line ul_TrgDest = (enum api429_pxi_trigger_line)px_PxiCon->ul_TrgDest;
    AiBoolean ul_TTClear = (AiBoolean)px_PxiCon->ul_TTClear;

    return (AiUInt8) Api429BoardPXITriggerConfigure(uc_Module, ul_Mode, ul_TrgSource, ul_TrgDest, ul_TTClear);
}


static AiInt16 INLINE(Api429GetServerInfo ( AiUInt8 bModule, TY_API429_SERVERINFO *pServerInfo))
{
    struct api429_remote_server server;
    AiReturn ret = API_OK;

    ret = Api429BoardServerInfoGet(bModule, &server);
    if (ret == API_OK)
    {
        strcpy(pServerInfo->szApplicationName, server.server_version.ac_Description);
        strcpy(pServerInfo->szNBComputerName, server.host_name);
        strcpy(pServerInfo->szCompanyName, "N/A");
        strcpy(pServerInfo->szCopyright, "N/A");
        strcpy(pServerInfo->szDescription, "N/A");
        strcpy(pServerInfo->szBuiltDate, "N/A");
        pServerInfo->usMajorVersion = (AiUInt16) server.server_version.ul_MajorVer;
        pServerInfo->usMinorVersion = (AiUInt16) server.server_version.ul_MinorVer;
        pServerInfo->uiBuiltNumber = 0;
        strcpy(pServerInfo->szIFUuid, "N/A");
        pServerInfo->usIFMajorVersion = (AiUInt16) server.protocol_major;
        pServerInfo->usIFMinorVersion = (AiUInt16) server.protocol_minor;
        pServerInfo->bSrvOSVersion = 0;
    }

    return (AiInt16) ret;
}


static short INLINE(Api429GetTgEmul( AiUInt8 bModule))
{
    (void) bModule;

    return 0;
}

static void INLINE(Api429SetTgEmul( AiUInt8 bModule, short mode ))
{
    (void) bModule;
    (void) mode;
}


static AiUInt8 INLINE(Api429CmdGetMemLocation( AiUInt8 uc_Module, AiUInt8 uc_Chn, AiUInt32 ul_Mode, AiUInt32 ul_Id, AiUInt32 *pul_MemType, AiUInt32 *pul_Offset))
{
    switch (ul_Mode)
    {
    case API429_GETMEM_XFER:
    case API429_GETMEM_XFER_BUF:
    case API429_GETMEM_TXCOUNT:
        ul_Id++;
    }

    return (AiUInt8) Api429BoardMemLocationGet(uc_Module, uc_Chn, (enum api429_memory_object) ul_Mode, ul_Id, (TY_E_MEM_TYPE*)pul_MemType, pul_Offset);
}


static AiUInt8 INLINE(Api429GetTimerAddr( AiUInt8 uc_Module, AiUInt32 *pul_TimerOffset, AiUInt32 *pul_MemType ))
{
    return (AiUInt8) Api429BoardMemTimerAddrGet(uc_Module, pul_TimerOffset, (TY_E_MEM_TYPE*)pul_MemType);
}


static AiUInt8 INLINE(Api429ReadMemData( AiUInt8 bModule, AiUInt8 memtype, AiUInt32 offset, AiUInt8 width, void* data_p))
{
    return (AiUInt8) Api429BoardMemRead(bModule, (TY_E_MEM_TYPE)memtype, offset, width, data_p);
}


static AiUInt8 INLINE(Api429WriteMemData( AiUInt8 bModule, AiUInt8 memtype, AiUInt32 offset, AiUInt8 width, void* data_p))
{
    return (AiUInt8) Api429BoardMemWrite(bModule, (TY_E_MEM_TYPE)memtype, offset, width, data_p);
}


static AiUInt8 INLINE(Api429ReadBlockMemData( AiUInt8 bModule, AiUInt8 memtype, AiUInt32 offset, AiUInt8 width, void* data_p, AiUInt32 size,
                                              AiUInt32 *pul_BytesRead))
{
    return (AiUInt8) Api429BoardMemBlockRead(bModule, (TY_E_MEM_TYPE)memtype, offset, width, data_p, size, pul_BytesRead);
}


static AiUInt8 INLINE(Api429WriteBlockMemData ( AiUInt8 bModule, AiUInt8 memtype, AiUInt32 offset, AiUInt8 width, void* data_p, AiUInt32 size,
                                                AiUInt32 *pul_BytesWritten))
{
    return (AiUInt8) Api429BoardMemBlockWrite(bModule, (TY_E_MEM_TYPE)memtype, offset, width, data_p, size, pul_BytesWritten);
}


static AiUInt8 INLINE(Api429CmdDefChnSpeed( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt8 b_Speed ))
{
    return (AiUInt8) Api429ChannelSpeedSet(b_Module, b_Chn, (enum api429_speed)b_Speed);
}


/*! \brief Internal callback for converting from Api429ChannelCallbackRegister to Api429InstIntHandler*/
AI_LIB_FUNC API429_CHANNEL_CALLBACK api429_callback_converter;

/*! \brief Internal Table used for converting from Api429ChannelCallbackRegister to Api429InstIntHandler callback format */
AI_LIB_FUNC TY_INT429_FUNC_PTR api429_callback_conversion_table[256][MAX_API429_CHN];


static short INLINE(Api429InstIntHandler(AiUInt8 b_Module, AiUInt8 uc_Chn, AiUInt8 uc_Type, TY_INT429_FUNC_PTR pf_IntFunc))
{
    api429_callback_conversion_table[b_Module][uc_Chn] = pf_IntFunc;
    return (short) Api429ChannelCallbackRegister(b_Module, uc_Chn, uc_Type, api429_callback_converter);
}


static short INLINE(Api429DelIntHandler( AiUInt8 b_Module, AiUInt8 uc_Chn, AiUInt8 uc_Type ))
{
    short ret = Api429ChannelCallbackUnregister(b_Module, uc_Chn, uc_Type);
    if (!ret)
    {
        api429_callback_conversion_table[b_Module][uc_Chn] = NULL;
    }

    return ret;
}


static AiUInt8 INLINE(Api429CmdReadDiscretes( AiUInt8 uc_Module, AiUInt32 *pul_Value ))
{
    return (AiUInt8) Api429DiscretesRead(uc_Module, pul_Value);
}


static AiUInt8 INLINE(Api429CmdWriteDiscretes ( AiUInt8 uc_Module, AiUInt32 ul_Mask, AiUInt32 ul_Value ))
{
    return (AiUInt8) Api429DiscretesWrite(uc_Module, ul_Mask, ul_Value);
}


static AiUInt8 INLINE(Api429CmdInitDiscretes( AiUInt8 uc_Module, AiUInt32 ul_DiscreteSetup ))
{
    return (AiUInt8) Api429DiscretesConfigSet(uc_Module, ul_DiscreteSetup);
}


static AiUInt8 INLINE(Api429CmdReadDiscreteConfig(AiUInt8 uc_Module, TY_API429_DISCR_CONFIG_GET *px_DiscrConfig))
{
	AiReturn ret = 0;
	TY_API429_DISCR_INFO info;

    ret = Api429DiscretesConfigGet(uc_Module, &px_DiscrConfig->ul_DiscreteSetup);
	if (ret != 0)
        return (AiUInt8) ret;

	ret = Api429DiscretesInfoGet(uc_Module, &info);
	px_DiscrConfig->ul_NrOfChannels = info.channels;

    return (AiUInt8) ret;
}


static AiUInt8 INLINE(Api429CmdDiscrPPSCntrl( AiUInt8 uc_Module, TY_API429_DISCR_PPS *px_Pps ))
{
    return (AiUInt8) Api429DiscretesPPSSet(uc_Module, (TY_API429_DISCRETE_PPS_CONFIG*)px_Pps);
}


static AiUInt8 INLINE(Api429CmdReplayIni(AiUInt8 b_Module, AiUInt8 uc_Chn, AiUInt8 uc_ClrEntryBit, AiUInt8 uc_NoRepCnt, AiUInt8 uc_CycOpr, AiUInt8 uc_RepErrors, AiUInt8 uc_RepIntMode,
                                         AiUInt8 uc_AbsLongTTag, AiUInt16 uw_DayOfYear, AiInt32 l_Min, AiInt32 l_MSec, AiUInt32 ul_FileSize))
{
    return (AiUInt8) Api429ReplayInit(b_Module, uc_Chn, uc_ClrEntryBit, uc_NoRepCnt, uc_CycOpr, uc_RepErrors, uc_RepIntMode, uc_AbsLongTTag,
                                      uw_DayOfYear, l_Min, l_MSec, ul_FileSize);
}


static AiUInt8 INLINE(Api429CmdReplayStatus(AiUInt8 b_Module, AiUInt8 uc_Chn, TY_API429_REP_STATUS *px_RepStatus))
{
    return (AiUInt8) Api429ReplayStatusGet(b_Module, uc_Chn, (TY_API429_REPLAY_STATUS*)px_RepStatus);
}


static short INLINE(Api429WriteRepData(AiUInt8 bModule, AiUInt8 uc_Chn, TY_API429_REP_STATUS *px_RepStatus, void *pv_Buf, AiUInt32 *pul_BytesWritten))
{
    return (AiUInt8) Api429ReplayDataWrite(bModule, uc_Chn, (TY_API429_REPLAY_STATUS*)px_RepStatus, pv_Buf, pul_BytesWritten);
}

static AiUInt8 INLINE(Api429CmdRmCapDef( AiUInt8 b_Module, AiUInt8 b_Chn, TY_API429_RCV_CAP_MODE_CMD *px_CapMode ))
{
    (void) b_Chn;
    //px_CapMode->mode;  /* is no longer used */
    axGlobalVariables[b_Module].tat = px_CapMode->tat;
    //px_CapMode->rec_filesize;  /* is no longer used */

    return 0;
}

static AiUInt8 INLINE(Api429CmdRmIni( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt8 mode ))
{
    TY_API429_RM_SETUP setup;

    setup.mode = (TY_E_API429_RM_MODE) mode;
    setup.interrupt_mode = (TY_E_API429_RM_INTERRUPT_MODE)axGlobalVariables[b_Module].interrupt_mode;
    setup.size_in_entries = axGlobalVariables[b_Module].mbuf_size;
    setup.tat_count = axGlobalVariables[b_Module].tat;

    return (AiUInt8) Api429RmCreate(b_Module, b_Chn, &setup);
}


static AiUInt8 INLINE(Api429CmdRmTrgDef( AiUInt8 b_Module, AiUInt8 b_Chn, TY_API429_RCV_TRG_MODE_CMD* px_TrgMode ))
{
    TY_API429_RM_TRIGGER_SETUP trigger;

    axGlobalVariables[b_Module].interrupt_mode = px_TrgMode->exti;

    trigger.mode = (TY_E_API429_RM_TRIGGER_MODE)px_TrgMode->tmod;
    trigger.input_trigger_line = px_TrgMode->exti;
    trigger.output_trigger_line = px_TrgMode->exto;
    trigger.generate_output_strobe = px_TrgMode->ext;

    return (AiUInt8) Api429RmTriggerConfigSet(b_Module, b_Chn, &trigger);
}


static AiUInt8 INLINE(Api429CmdRmLabCon( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt8 b_Label, AiUInt8 b_Sdi, AiUInt8 b_Con ))
{
    TY_API429_RM_LABEL_CONFIG label_config;
    label_config.label_id = b_Label;
    label_config.sdi = b_Sdi;
    label_config.enable = b_Con != 0 ? (AiBoolean)AiTrue : (AiBoolean) AiFalse;

    return (AiUInt8) Api429RmLabelConfigure(b_Module, b_Chn, &label_config);
}


static AiUInt8 INLINE(Api429CmdRmTrgStartDef( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt8 b_Label, AiUInt8 b_Sdi, AiUInt8 b_Con, TY_API429_TRG_CTL_CMD  *px_Ctl ))
{
    return (AiUInt8) Api429RmStartTriggerSet(b_Module, b_Chn, b_Label, b_Sdi, b_Con, px_Ctl);
}


static AiUInt8 INLINE(Api429CmdRmTrgStopDef( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt8 b_Label, AiUInt8 b_Sdi, AiUInt8 b_Con, TY_API429_TRG_CTL_CMD  *px_Ctl ))
{
    return (AiUInt8) Api429RmStopTriggerSet(b_Module, b_Chn, b_Label, b_Sdi, b_Con, px_Ctl);
}


static AiUInt8 INLINE(Api429CmdRmStart( AiUInt8 b_Module, AiUInt8 b_Chn ))
{
    return (AiUInt8) Api429RmResume(b_Module, b_Chn);
}


static AiUInt8 INLINE(Api429CmdRmHalt( AiUInt8 b_Module, AiUInt8 b_Chn ))
{
    return (AiUInt8) Api429RmSuspend(b_Module, b_Chn);
}


static AiUInt8 INLINE(Api429CmdRmStatusRead( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt8  *b_RmStatus, AiUInt16  *pw_Msw ))
{
    return (AiUInt8) Api429RmStatusGet(b_Module, b_Chn, b_RmStatus, pw_Msw);
}


static AiUInt8 INLINE(Api429CmdRmStkPtrRead( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt32  *pl_Stp, AiUInt32  *pl_Ctp, AiUInt32  *pl_Etp ))
{
    return (AiUInt8) Api429RmStackPointersGet(b_Module, b_Chn, pl_Stp, pl_Ctp, pl_Etp);
}


static AiUInt8 INLINE(Api429CmdRmDataRead( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt16 uw_EntriesToRead, AiUInt16 *puw_Count,
                                           TY_API429_RCV_STACK_ENTRY *px_SData ))
{
    return (AiUInt8) Api429RmDataRead(b_Module, b_Chn, uw_EntriesToRead, puw_Count, px_SData);
}


static AiUInt8 INLINE(Api429CmdRmDataReadEx( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt16 uw_EntriesToRead, AiUInt16 *puw_Count,
                                                    TY_API429_RCV_STACK_ENTRY_EX *px_SData ))
{
    return (AiUInt8) Api429RmDataReadWithDayOfYear(b_Module, b_Chn, uw_EntriesToRead, puw_Count, px_SData);
}


static AiUInt8 INLINE(Api429CmdRxIni( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt8 b_Mode, AiUInt8 b_ModeExt, AiUInt8 b_Parity ))
{
    AiReturn ret = 0;
    AiBoolean useSdi = axGlobalVariables[b_Module].useSdi;  //use value set in Api429CmdReset

	// handle special mode
	if ((b_Mode == 0) && (b_ModeExt == 1))
		useSdi = AiFalse;

    ret = Api429RxInit(b_Module, b_Chn, useSdi, (AiBoolean) !b_Parity);
    if (ret != 0)
        return (AiUInt8) ret;

    if (b_Mode == 1) // if loop/pollution mode
    {
        ret = Api429RxDataLoopAssign(b_Module, b_Chn, b_ModeExt);
    }

    return (AiUInt8) ret;
}


static AiUInt8 INLINE(Api429RxReadActivity( AiUInt8 b_Module, TY_API429_RX_ACTIVITY *pxActivity))
{
    return (AiUInt8) Api429RxActivityGet(b_Module, pxActivity);
}


static AiUInt8 INLINE(Api429CmdRxLabCon( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt8 b_Label, AiUInt8 b_Sdi, AiUInt8 b_Con, AiUInt8 b_IrCon,
                                         AiUInt16 w_IrIndex, AiUInt16 w_BufSize, AiUInt8 *puc_Status, AiUInt32 *pul_FreeMem ))
{
    TY_API429_RX_LABEL_SETUP label_setup;

    label_setup.label = b_Label;
    label_setup.sdi = b_Sdi;
    label_setup.con = b_Con;
    label_setup.irCon = b_IrCon;
    label_setup.irIndex = w_IrIndex;
    label_setup.bufSize = w_BufSize;

    return (AiUInt8) Api429RxLabelConfigure(b_Module, b_Chn, &label_setup, puc_Status, pul_FreeMem);
}


static AiUInt8 INLINE(Api429CmdRxLabDataCon( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt8 b_Label, AiUInt8 b_Sdi, AiUInt16 w_BufSize, TY_API429_RX_BUF_ENTRY  *px_LData, AiUInt8 b_Clear ))
{
    return (AiUInt8) Api429RxLabelBufferWrite(b_Module, b_Chn, b_Label, b_Sdi, w_BufSize, px_LData, b_Clear);
}


static AiUInt8 INLINE(Api429CmdRxStatusRead( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt8  *b_RxStatus, AiUInt32  *px_MsgCnt, AiUInt32  *px_ErrCnt ))
{
    return (AiUInt8) Api429RxStatusGet(b_Module, b_Chn, b_RxStatus, px_MsgCnt, px_ErrCnt);
}


static AiUInt8 INLINE(Api429CmdRxLabRead( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt8 b_Label, AiUInt8 b_Sdi, AiUInt8 b_LabCntIni, AiUInt16  *pw_LabIx,
                                          AiUInt32  *px_LabCnt, AiUInt32  *px_LabErr ))
{
    return (AiUInt8) Api429RxLabelStatusGet(b_Module, b_Chn, b_Label, b_Sdi, b_LabCntIni, pw_LabIx, px_LabCnt, px_LabErr);
}


static AiUInt8 INLINE(Api429CmdRxLabDataRead( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt8 b_Label, AiUInt8 b_Sdi, AiUInt16 w_BufSize,
                                              TY_API429_RX_BUF_CTL  *px_Info, TY_API429_RX_BUF_ENTRY  *px_LData ))
{
    return (AiUInt8) Api429RxLabelBufferRead(b_Module, b_Chn, b_Label, b_Sdi, w_BufSize, px_Info, px_LData);
}


static AiUInt8 INLINE(Api429CmdRxGetBufAddress( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt8 b_Label, AiUInt8 b_Sdi, AiUInt32  *px_Addr, AiUInt16  *w_Size ))
{
    return (AiUInt8) Api429RxLabelBufferOffsetGet(b_Module, b_Chn, b_Label, b_Sdi, px_Addr, w_Size);
}


static AiUInt8 INLINE(Api429CmdRxPollBlkDef( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt8 b_Label, AiUInt8 b_Sdi, AiUInt8 b_Con, TY_API429_RCV_PB_CMD  *px_PollBlk))
{
    return (AiUInt8) Api429RxPollutionConfigure(b_Module, b_Chn, b_Label, b_Sdi, b_Con, px_PollBlk);
}


static AiUInt8 INLINE(Api429CmdRxStart( AiUInt8 b_Module, AiUInt8 b_Chn))
{
    return (AiUInt8) Api429ChannelStart(b_Module, b_Chn);
}


static AiUInt8 INLINE(Api429CmdRxHalt( AiUInt8 b_Module, AiUInt8 b_Chn))
{
    return (AiUInt8) Api429ChannelHalt(b_Module, b_Chn);
}


static AiUInt8 INLINE(Api429CmdTxIni( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt8 b_Mode, AiUInt8 b_Parity ))
{
    return (AiUInt8) Api429TxInit(b_Module, b_Chn, (TY_E_API429_TX_MODE)b_Mode, (AiBoolean) !b_Parity);
}


static AiUInt8 INLINE(Api429CmdTxAmpIniEx( AiUInt8 b_Module, AiUInt8 b_Chn, AiFloat fAmplitude, AiFloat *pfCalcAmpl ))
{
    return (AiUInt8) Api429TxAmplitudeSet(b_Module, b_Chn, fAmplitude, pfCalcAmpl);
}


static AiUInt8 INLINE(Api429CmdTxStatusRead( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt8  *pb_TxStatus, AiUInt32  *pl_GlbCnt, AiUInt16  *pw_RelFlag ))
{
    (void) pw_RelFlag;
    return (AiUInt8) Api429TxStatusGet(b_Module, b_Chn, pb_TxStatus, pl_GlbCnt);
}


static AiUInt8 INLINE(Api429CmdTxFrmTimeIniEx ( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt16 w_Ftm ))
{
    return (AiUInt8) Api429TxFrameTimeSet(b_Module, b_Chn, w_Ftm);
}


static AiUInt8 INLINE(Api429CmdTxXferDefEx(AiUInt8 b_Module, AiUInt8 b_Chn, TY_API429_LXFER_CMD *px_Xfer, TY_API429_LXFER_OUT *px_XferInfo ))
{
    TY_API429_XFER xfer;
    TY_API429_XFER_OUT info;
    AiReturn ret;

    xfer.xfer_id = px_Xfer->xfer_id + 1;  // The transfer ID 0 is no more allowed. Hence shift all IDs one up to keep applications using ID 0 working
    xfer.xfer_type = (TY_E_API429_XFER_TYPE)px_Xfer->xfer_type;
    xfer.xfer_ir = px_Xfer->xfer_ir;
    xfer.ir_index = px_Xfer->ir_index;
    xfer.buf_size = px_Xfer->buf_size;
    xfer.err_type = (TY_E_API429_XFER_ERROR)px_Xfer->err_type;
    xfer.xfer_gap = px_Xfer->xfer_gap;

    ret = Api429TxXferCreate(b_Module, b_Chn, &xfer, &info);

    px_XferInfo->ul_Status = info.ul_Status;
    px_XferInfo->ul_FreeMem = info.ul_FreeMem;
    px_XferInfo->ul_XferDescAddr = info.ul_XferDescAddr;

    return (AiUInt8) ret;
}


static AiUInt8 INLINE(Api429CmdTxXferDef(AiUInt8 b_Module, AiUInt8 b_Chn, TY_API429_LXFER_CMD *px_Xfer, AiUInt8 *b_Status, AiUInt32* pl_FreeMem))
{
    TY_API429_XFER xfer;
    TY_API429_XFER_OUT info;
    AiReturn ret;

    xfer.xfer_id = px_Xfer->xfer_id + 1;  // The transfer ID 0 is no more allowed. Hence shift all IDs one up to keep applications using ID 0 working
    xfer.xfer_type = (TY_E_API429_XFER_TYPE)px_Xfer->xfer_type;
    xfer.xfer_ir = px_Xfer->xfer_ir;
    xfer.ir_index = px_Xfer->ir_index;
    xfer.buf_size = px_Xfer->buf_size;
    xfer.err_type = (TY_E_API429_XFER_ERROR)px_Xfer->err_type;
    xfer.xfer_gap = px_Xfer->xfer_gap;

    ret = Api429TxXferCreate(b_Module, b_Chn, &xfer, &info);

    *b_Status = (AiUInt8) info.ul_Status;
    *pl_FreeMem = info.ul_FreeMem;

    return (AiUInt8) ret;
}


static AiUInt8 INLINE(Api429CmdTxXferDyntagDef( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt32 ul_XferId, TY_API429_LXFER_DYNTAG *px_Dyntag ))
{
    // The transfer ID 0 is no more allowed. Hence shift all IDs one up to keep applications using ID 0 working
    return (AiUInt8) Api429TxXferDyntagAssign(b_Module, b_Chn, ul_XferId + 1, px_Dyntag);
}


static AiUInt8 INLINE(Api429CmdTxXferDataDef( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt32 ul_XferId, AiUInt8 b_XferMode,
                                              AiUInt16 w_BufStart, AiUInt16 w_BufSize, AiUInt32  *pl_LData ))
{
    (void)b_XferMode;

    // The transfer ID 0 is no more allowed. Hence shift all IDs one up to keep applications using ID 0 working
    return (AiUInt8) Api429TxXferBufferWrite(b_Module, b_Chn, ul_XferId + 1, w_BufStart, w_BufSize, pl_LData);
}


static AiUInt8 INLINE(Api429CmdTxXferDataRead ( AiUInt8 b_Module, AiUInt8 b_Chn, TY_API429_XFER_DATA_READ_INPUT *px_XferDataInput,
                                                TY_API429_XFER_DATA *px_XferData ))
{
   
    TY_API429_XFER_DATA_READ_INPUT copy;

    // The transfer ID 0 is no more allowed. Hence shift all IDs one up to keep applications using ID 0 working
    memcpy(&copy, px_XferDataInput, sizeof(copy));
    copy.ul_XferId += 1;
    return (AiUInt8) Api429TxXferBufferRead(b_Module, b_Chn, &copy, px_XferData);
}


static AiUInt8 INLINE(Api429CmdTxMinFrameInstEx( AiUInt8 b_Module, AiUInt8 b_Chn, TY_API429_MFRAME_IN *px_MFrame, TY_API429_MFRAME_OUT *px_MFrameInfo))
{
    struct api429_mframe_in copy;
    AiUInt32 i;
    AiReturn ret;

    copy.ul_FrmId = px_MFrame->ul_FrmId;
    copy.ul_XferCnt = px_MFrame->ul_XferCnt;

    copy.pul_Xfers = (AiUInt32*) malloc(sizeof(AiUInt32) * px_MFrame->ul_XferCnt);
    if (!copy.pul_Xfers)
    {
        return AI429_ERR_NO_MORE_MEMORY;
    }

    // The transfer ID 0 is no more allowed. Hence shift all IDs one up to keep applications using ID 0 working
    for (i = 0; i < px_MFrame->ul_XferCnt; i++)
    {
        copy.pul_Xfers[i] = px_MFrame->pul_Xfers[i] + 1;
    }

    ret = Api429TxMinorFrameCreate(b_Module, b_Chn, &copy, px_MFrameInfo);

    free(copy.pul_Xfers);

    return (AiUInt8) ret;
}

static AiUInt8 INLINE(Api429CmdTxMinFrameInst( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt32 ul_FrmId, AiUInt32 ul_XferCnt, AiUInt32 *pul_Xfers ))
{
	TY_API429_MFRAME_IN x_MFrame;
	TY_API429_MFRAME_OUT x_MFrameInfo;

	x_MFrame.ul_FrmId = ul_FrmId;
	x_MFrame.ul_XferCnt = ul_XferCnt;
	x_MFrame.pul_Xfers = pul_Xfers;
	
	return Api429CmdTxMinFrameInstEx( b_Module, b_Chn, &x_MFrame, &x_MFrameInfo);
}


static AiUInt8 INLINE(Api429CmdTxMajFrameInst ( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt32 ul_FrmCnt, AiUInt32 *pul_Frames ))
{
    return (AiUInt8) Api429TxMajorFrameCreate(b_Module, b_Chn, ul_FrmCnt, pul_Frames);
}


static AiUInt8 INLINE(Api429CmdTxXferDel( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt32 ul_XferId ))
{
    // The transfer ID 0 is no more allowed. Hence shift all IDs one up to keep applications using ID 0 working
    return (AiUInt8) Api429TxXferDelete(b_Module, b_Chn, ul_XferId + 1);
}


static AiUInt8 INLINE(Api429CmdTxXferEnaDis( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt8 b_Mode, AiUInt32 ul_XferId ))
{
    // The transfer ID 0 is no more allowed. Hence shift all IDs one up to keep applications using ID 0 working
    return (AiUInt8)Api429TxXferSkip(b_Module, b_Chn, b_Mode == 0 ? (AiBoolean) AiTrue : (AiBoolean) AiFalse, ul_XferId + 1);
}


static AiUInt8 INLINE(Api429CmdTxMinFrmDel( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt32 ul_FrmId ))
{
    return (AiUInt8) Api429TxMinorFrameDelete(b_Module, b_Chn, ul_FrmId);
}


static AiUInt8 INLINE(Api429CmdTxMajFrmDel( AiUInt8 b_Module, AiUInt8 b_Chn ))
{
    return (AiUInt8) Api429TxMajorFrameDelete(b_Module, b_Chn);
}


static AiUInt8 INLINE(Api429CmdTxXferReadEx( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt32 b_XferId, TY_API429_XFER_INFO  *px_XferInfo ))
{
    // The transfer ID 0 is no more allowed. Hence shift all IDs one up to keep applications using ID 0 working
    return (AiUInt8) Api429TxXferStatusGet(b_Module, b_Chn, b_XferId + 1, px_XferInfo);
}


static AiUInt8 INLINE(Api429CmdTxGetBufAddress( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt32 ul_XferId, AiUInt32 *pl_Addr, AiUInt16 *pw_Size ))
{
    // The transfer ID 0 is no more allowed. Hence shift all IDs one up to keep applications using ID 0 working
    return (AiUInt8) Api429TxXferBufferOffsetGet(b_Module, b_Chn, ul_XferId + 1, pl_Addr, pw_Size);
}


static AiUInt8 INLINE(Api429CmdTxHalt( AiUInt8 b_Module, AiUInt8 b_Chn))
{
    return (AiUInt8) Api429ChannelHalt(b_Module, b_Chn);
}


static AiUInt8 INLINE(Api429CmdRmTrgParamDef( AiUInt8 b_Module, AiUInt8 b_Chn, TY_API429_TRG_PAR_CMD *px_Para ))
{
	AiReturn retval = 0;
	TY_API429_RM_ACTIVITY_TRIGGER_DEF  x_Para;

	x_Para.start_mask = px_Para->start_mask;
	x_Para.start_pat = px_Para->start_pat;
	x_Para.stop_mask = px_Para->stop_mask;
	x_Para.stop_pat = px_Para->stop_pat;

	retval = Api429RmTriggerPatternSet( b_Module, b_Chn, &x_Para);

	return (AiUInt8) retval;
}


static AiUInt8 INLINE(Api429CmdRmFuncBlkDef( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt8 b_Label, AiUInt8 b_Sdi, AiUInt8 b_Con, TY_API429_RCV_FB_CMD *px_FuncBlk ))
{
    TY_API429_RM_FUNCTION_BLOCK  x_FuncBlk;
    memset(&x_FuncBlk, 0, sizeof(x_FuncBlk));

    x_FuncBlk.fb_id = px_FuncBlk->fb_id;
    x_FuncBlk.fbi = px_FuncBlk->fbi;
    x_FuncBlk.ir = px_FuncBlk->ir;
    x_FuncBlk.ulc = px_FuncBlk->ulc;
    x_FuncBlk.uli = px_FuncBlk->uli;
    x_FuncBlk.llc = px_FuncBlk->llc;
    x_FuncBlk.lli = px_FuncBlk->lli;
    x_FuncBlk.fe = px_FuncBlk->fe;
    x_FuncBlk.trg_set = px_FuncBlk->trg_set;
    x_FuncBlk.trg_reset = px_FuncBlk->trg_reset;
    x_FuncBlk.pre_cnt = px_FuncBlk->pre_cnt;
    x_FuncBlk.pre_rel = px_FuncBlk->pre_rel;
    x_FuncBlk.mask = px_FuncBlk->mask;
    x_FuncBlk.ulim = px_FuncBlk->ulim;
    x_FuncBlk.llim = px_FuncBlk->llim;
    x_FuncBlk.ext_trg = px_FuncBlk->ext_trg;
    x_FuncBlk.trg_line = px_FuncBlk->trg_line;

    return (AiUInt8) Api429RmFuncBlockConfigure(b_Module, b_Chn, b_Label, b_Sdi, b_Con, &x_FuncBlk);
}


static AiUInt8 INLINE(Api429CmdTxFifoReset( AiUInt8 b_Module, AiUInt8 b_Chn ))
{
    return (AiUInt8) Api429TxFifoReset(b_Module, b_Chn);
}


static AiUInt8 INLINE(Api429CmdTxFifoSetup( AiUInt8 b_Module, AiUInt8 b_Chn,  TY_API429_TX_FIFO_SETUP *pxFifoSetup ))
{
    return (AiUInt8) Api429TxFifoSetup(b_Module, b_Chn, pxFifoSetup);
}


static AiUInt8 INLINE(Api429CmdTxFifoStatus( AiUInt8 b_Module, AiUInt8 b_Chn, TY_API429_TX_FIFO_STATUS *pxFifoStatus ))
{
    return (AiUInt8) Api429TxFifoStatusGet(b_Module, b_Chn, pxFifoStatus);
}


static AiUInt8 INLINE(Api429CmdTxFifoWriteLabels( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt32 ulMode, AiUInt32 ulCount, AiUInt32 *pulLabels,
                                                  AiUInt32 *pulEntriesWritten ))
{
    return (AiUInt8)Api429TxFifoDataWordsWrite(b_Module, b_Chn, ulCount, pulLabels, ulMode == API429_FIFO_WRITE_BLOCKING ? (AiBoolean) AiTrue : (AiBoolean) AiFalse, pulEntriesWritten);
}


static AiUInt8 INLINE(Api429CmdTxFifoWriteInstructions( AiUInt8 b_Module, AiUInt8 b_Chn, AiUInt32 ulMode, AiUInt32 ulCount,
                                                        TY_API429_TX_FIFO_ENTRY *pxFifoEntries, AiUInt32 *pulEntriesWritten ))
{
    return (AiUInt8)Api429TxFifoWrite(b_Module, b_Chn, ulCount, pxFifoEntries, ulMode == API429_FIFO_WRITE_BLOCKING ? (AiBoolean) AiTrue : (AiBoolean) AiFalse, pulEntriesWritten);
}


/* API Memory Commands */
static AiUInt8 AI_INLINE Api429CmdRamWrite( AiUInt8 b_Module, AiUInt8 b_WCount, AiUInt32 l_StartAddr, AiUInt32  *pl_WData )
{
    return (AiUInt8) Api429BoardMemBlockWrite(b_Module, AI_MEMTYPE_GLOBAL, l_StartAddr, 4, pl_WData, b_WCount, NULL);
}


static AiUInt8 AI_INLINE Api429CmdRamRead( AiUInt8 b_Module, AiUInt8 b_WCount, AiUInt32 l_StartAddr, AiUInt32  *pl_WData )
{
    return (AiUInt8) Api429BoardMemBlockRead(b_Module, AI_MEMTYPE_GLOBAL, l_StartAddr, 4, pl_WData, b_WCount, NULL);
}


static AiUInt8 AI_INLINE Api429ReadBiuData( AiUInt8 bModule, AiUInt32 offset, AiUInt8 width, void* data_p)
{
    return (AiUInt8) Api429BoardMemRead(bModule, AI_MEMTYPE_GLOBAL, offset, width, data_p);
}


static AiUInt8 AI_INLINE Api429WriteBiuData( AiUInt8 bModule, AiUInt32 offset, AiUInt8 width, void* data_p)
{
    return (AiUInt8) Api429BoardMemWrite(bModule, AI_MEMTYPE_GLOBAL, offset, width, data_p);
}


static AiUInt8 AI_INLINE Api429ReadBlockBiuData( AiUInt8 bModule, AiUInt32 offset, AiUInt8 width, void* data_p, AiUInt32 size)
{
    return (AiUInt8) Api429BoardMemBlockRead(bModule, AI_MEMTYPE_GLOBAL, offset, width, data_p, size, NULL);
}


static AiUInt8 AI_INLINE Api429WriteBlockBiuData( AiUInt8 bModule, AiUInt32 offset, AiUInt8 width, void* data_p, AiUInt32 size)
{
    return (AiUInt8) Api429BoardMemBlockWrite(bModule, AI_MEMTYPE_GLOBAL, offset, width, data_p, size, NULL);
}


static AiUInt8 AI_INLINE Api429CmdMemAlloc(AiUInt8 bModule, AiUInt32 ulMemType, AiUInt32 ulSize, AiUInt32 ulTag, AiUInt32 *pulOffset)
{
    return (AiUInt8) Api429BoardMemAlloc(bModule, (TY_E_MEM_TYPE) ulMemType, ulSize, ulTag, pulOffset);
}


static AiUInt8 AI_INLINE Api429CmdMemFree(AiUInt8 b_Module, AiUInt32 ulMemType, AiUInt32 ulOffset)
{
    return (AiUInt8) Api429BoardMemFree(b_Module, (TY_E_MEM_TYPE) ulMemType, ulOffset);
}


static short AI_INLINE Api429ReadBSPVersion(AiUInt8 bModule,
                                       AiUInt32 *pul_FirmwareVer, AiUInt32 *pul_TargetVer,
                                       AiUInt32 *pul_LcaVer1, AiUInt32 *pul_LcaVer2,
                                       AiUInt32 *pul_LcaCheckSum,
                                       AiUInt32 *pul_SysDrvVer, AiUInt32 *pul_DllVer,
                                       AiUInt32 *pul_BoardSerialNr,
                                       AiUInt8  *puc_BspCompatibility )
{
  short w_Api429Status;
  TY_API429_VERSION_INFO x_VersionInfo;

  if( (NULL == pul_FirmwareVer) || (NULL == pul_TargetVer) || (NULL == pul_LcaVer1) ||
      (NULL == pul_LcaVer2) || (NULL == pul_LcaCheckSum) || (NULL == pul_SysDrvVer) ||
      (NULL == pul_DllVer) || (NULL == pul_BoardSerialNr) || (NULL == puc_BspCompatibility) )
    return AI429_ERR_NULL_POINTER;

  w_Api429Status = Api429ReadBSPVersionEx(bModule, &x_VersionInfo, puc_BspCompatibility);

  /* All values as described in the reference manual */
  *pul_FirmwareVer   = 0;
  *pul_TargetVer     = x_VersionInfo.x_TargetSWVer.ul_MajorVer/10 * 0x1000 +
                       x_VersionInfo.x_TargetSWVer.ul_MajorVer%10 * 0x100 +
                       x_VersionInfo.x_TargetSWVer.ul_MinorVer/10 *  0x10 +
                       x_VersionInfo.x_TargetSWVer.ul_MinorVer%10         +
                       x_VersionInfo.x_TargetSWVer.ul_MajorSpecialVer    * 0x1000000 +
                       x_VersionInfo.x_TargetSWVer.ul_MinorSpecialVer/10 *  0x100000 +
                       x_VersionInfo.x_TargetSWVer.ul_MinorSpecialVer%10 *   0x10000 ;
  *pul_LcaVer1       = 0;
  *pul_LcaVer2       = 0;
  *pul_LcaCheckSum   = 0;
  *pul_SysDrvVer     = x_VersionInfo.x_SysDrvVer.ul_MajorVer/10 * 0x1000 +
                       x_VersionInfo.x_SysDrvVer.ul_MajorVer%10 * 0x100 +
                       x_VersionInfo.x_SysDrvVer.ul_MinorVer/10 * 0x10 +
                       x_VersionInfo.x_SysDrvVer.ul_MinorVer%10;
  *pul_DllVer        = x_VersionInfo.x_DllVer.ul_MajorVer/10 * 0x1000 +
                       x_VersionInfo.x_DllVer.ul_MajorVer%10 * 0x100 +
                       x_VersionInfo.x_DllVer.ul_MinorVer/10 * 0x10 +
                       x_VersionInfo.x_DllVer.ul_MinorVer%10;
  *pul_BoardSerialNr = x_VersionInfo.ul_BoardSerialNr;

  return w_Api429Status;
}

#endif /* API429_BSP10_LEGACY_H_ */
