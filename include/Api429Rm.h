/******************************************************************************

           Copyright (c) AIM GmbH 2001, 79111 Freiburg, Germany.                 
                                                                             
            All rights reserved.  No part of this software may                
            be published, distributed, translated or otherwise                
            reproduced by any means or for any purpose without                
            the prior written consent of AIM GmbH, Freiburg.                  

******************************************************************************/
/*! \file Api429Rm.h
 *
 *  This header file contains declarations
 *  used for API functionality related to monitoring receive data
 *  Created on: 10.02.2016
 *      Author: Markus Melcher
 */

#ifndef API429RM_H_
#define API429RM_H_


#include "Ai_cdef.h"



/**
* \defgroup monitoring Data Monitoring
  This module contains functionality related to monitoring of received Arinc 429
  bus traffic.
* @{
*/




/*! \def API429_RM_MON_DEFAULT_SIZE
 * Can be used with \ref Api429RmCreate to
 * create a monitor buffer with default size
 */
#define API429_RM_MON_DEFAULT_SIZE 4096


/*! \def API429_RM_CONTINUOUS_CAPTURE
 * Can be used as parameter 'tat_count' for \ref Api429RmCreate
 * for a continuous monitoring of data without stopping the monitor
 * after a specific number of entries has been received.
 */
#define API429_RM_CONTINUOUS_CAPTURE    0


/*! \enum api429_rm_mode
 *
 * Enumeration of all supported monitoring modes
 */
enum api429_rm_mode
{
    API429_RM_MODE_UNDEFINED = -1,//!< API429_RM_MODE_UNDEFINED
    API429_RM_MODE_LOC = 0,       //!< Can be used for channel specific monitoring. Channel uses its own monitor buffer
    API429_RM_MODE_GLB = 1        //!< Can be used for multiplexing received data of several channels into one monitor buffer
};


/*! \typedef TY_E_API429_RM_MODE
 * Convenience typedef for \ref api429_rm_mode
 */
typedef enum api429_rm_mode TY_E_API429_RM_MODE;


/*! \enum api429_rm_interrupt_mode
 * Enumeration of all possible monitor interrupt modes
 */
enum api429_rm_interrupt_mode
{
    API429_RM_IR_UNDEFINED = -1,    /*!< Undefined */
    API429_RM_IR_DIS  =   0,        /*!< No interrupts are issued */
    API429_RM_IR_START,             /*!< Interrupt is issued when monitor starts due to trigger */
    API429_RM_IR_STOP,              /*!< Interrupt is issued when monitor stops */
    API429_RM_IR_BFI,               /*!< Interrupt is issued when monitor buffer is full */
    API429_RM_IR_HFI,               /*!< Interrupt is issued when monitor buffer is half full */
    API429_RM_IR_START_HFI_BFI      /*!< Interrupt is issued when monitor starts, buffer is half full or full */
};

/*! \typedef TY_E_API429_RM_INTERRUPT_MODE
 * Convenience typedef for \ref api429_rm_interrupt_mode
 */
typedef enum api429_rm_interrupt_mode TY_E_API429_RM_INTERRUPT_MODE;


/*! \enum api429_rm_trigger_mode
 * Enumeration of all possible trigger modes
 * for a receive monitor
 */
enum api429_rm_trigger_mode
{
    API429_TRG_START = 0,   /*!< trigger on start and stop function trigger */
    API429_TRG_ERR,         /*!< trigger on any error */
    API429_TRG_EXT,         /*!< trigger on event on external input trigger line */
    API429_TRG_ANY          /*!< trigger on first enabled label received on channel */
};

/*! \typedef TY_E_API429_RM_TRIGGER_MODE
 * Convenience typedef for \ref api429_rm_trigger_mode
 */
typedef enum api429_rm_trigger_mode TY_E_API429_RM_TRIGGER_MODE;


/*! \struct api429_rm_setup
 *
 * This structure comprises all properties
 * necessary for a general monitor setup. \n
 * It is used as input parameter for \ref Api429RmCreate
 */
struct api429_rm_setup
{
    enum api429_rm_mode mode;                       /*!< Monitoring mode. See \ref api429_rm_mode */
    AiUInt32 size_in_entries;                       /*!< Size of monitor buffer in entries. \n
                                                         Use \ref API429_RM_MON_DEFAULT_SIZE for a recommended default size. \n
                                                         Attention: This size has to be specified as a multiple of 256 entries. \n
                                                         If size is 0, a default size of \ref API429_RM_MON_DEFAULT_SIZE will be used */
    AiUInt32 tat_count;                             /*!< Trace after trigger count. Number of entries that are monitored after triggering before monitor stops. \n
                                                         Use \ref API429_RM_CONTINUOUS_CAPTURE for continuous monitoring without stopping except on stop trigger signals */
    enum api429_rm_interrupt_mode interrupt_mode;   /*!< Used for configuring monitor interrupts. See \ref api429_rm_interrupt_mode */
};


/*! \typedef TY_API429_RM_SETUP
 * Convenience typedef for \ref api429_rm_setup
 */
typedef struct api429_rm_setup TY_API429_RM_SETUP;


/*! \struct api429_rm_trigger_setup
 *
 * This structure comprises all properties related to receive monitor trigger set-up. \n
 * It is used as input parameter for \ref Api429RmTriggerConfigSet
 */
struct api429_rm_trigger_setup
{
   enum api429_rm_trigger_mode mode;    /*!< trigger mode to use on a specific receive monitor. See \ref api429_rm_trigger_mode */
   AiUInt8 input_trigger_line;          /*!< ID of input trigger line to react on when using 'mode' API429_TRG_EXT. */
   AiBoolean generate_output_strobe;    /*!< If set to AiTrue, a strobe is generated on output trigger line defined
                                             by 'output_trigger_line' */
   AiUInt8 output_trigger_line;         /*!< ID of output trigger line that strobe is generated on when 'generate_output_strobe'
                                             is set to AiTrue */
};


/*! \typedef TY_API429_RM_TRIGGER_SETUP
 *  Convenience typedef for \ref api429_rm_trigger_setup
 */
typedef struct api429_rm_trigger_setup TY_API429_RM_TRIGGER_SETUP;


/*! \struct api429_rm_label_config
 *
 * This structure holds a label/SDI combination that can be enabled/disabled
 * with respect to monitoring
 */
struct api429_rm_label_config
{
    AiUInt32 label_id;  /*!< Label ID to configure for monitoring */
    AiUInt32 sdi;       /*!< SDI extension for Label ID. Only valid if SDI sorting is enabled for channel */
    AiBoolean enable;   /*!< AiTrue if Label shall be enabled for monitoring, AiFalse if disabled. */
};

/*! \typedef TY_API429_RM_LABEL_CONFIG
 * Convenience typedef for \ref api429_rm_label_config
 */
typedef struct api429_rm_label_config TY_API429_RM_LABEL_CONFIG;


/*! \struct api429_rm_function_block
 * This structure describes a monitor function block
 */
struct api429_rm_function_block
{
   AiUInt8 fb_id;           /*!< ID of function block */
   AiUInt8 fbi;             /*!< Enable/Disable issue of interrupt when function block result is TRUE */
   AiUInt8 ir;              /*!< if 0: Verify masked bits of a label for not in range. \n if 1: Verify masked bits of a label for in range */
   AiUInt8 ulc;             /*!< Upper Limit Control. 0 means __Always__, 1 means __Equal__, 2 means __Greater than__, 3 means __Less than__ */
   AiUInt8 uli;             /*!< Upper Limit Control Invert. If 'uli' is set to one, the 'upper limit check (ulc)' will be logically inverted. */
   AiUInt8 llc;             /*!< Lower Limit Control. See __ulc__ */
   AiUInt8 lli;             /*!< Lower Limit Control Invert If 'lli' is set to one, the 'lower limit check (llc)' will be logically inverted */
   AiUInt8 fe;              /*!< Filtering disabled/enabled. When 0, Filtering is disabled. When 1 and the result of the function block operation is "TRUE", the label will be stored in the monitor. */
   AiUInt32 trg_set;        /*!< If the result of the function block operation is "TRUE" these bits indicate which bit positions have to be SET in the monitor function trigger status register. */
   AiUInt32 trg_reset;      /*!< If the result of the function block operation is "TRUE" these bits indicate which bit positions have to be RESET in the monitor function trigger status register. */
   AiUInt16 pre_cnt;        /*!< Pre Qualify Counter.
                                 Each time the examined label matches the condition defined in the function definition word the pre qualify counter will be decremented by one. If the counter reaches zero the function
                                 block operation is TRUE. The pre qualify counter should be initialized to 1. */
   AiUInt16 pre_rel;        /*!< Pre Qualify Counter Register Reinitialization.
                                 This field sets the pre qualify counter register reinitialization value for the pre qualify
                                 counter. This value will be loaded into the pre qualify counter location each time the pre
                                 qualify counter has been decremented to zero. The pre qualify counter reg should be
                                 initialized to 1. */
   AiUInt32 mask;           /*!< Mask of label data */
   AiUInt32 ulim;           /*!< Upper Limit */
   AiUInt32 llim;           /*!< Lower Limit */
   AiUInt8  ext_trg;        /*!< Trigger Output disabled/enabled */
   AiUInt8  trg_line;       /*!< External Trigger Output Select */
};


/*! \typedef TY_API429_RM_FUNCTION_BLOCK
 * Convenience typedef for \ref api429_rm_function_block
 */
typedef struct api429_rm_function_block TY_API429_RM_FUNCTION_BLOCK;


/*! \struct api429_rm_activity_trigger_def
 * This structure describes an activity trigger
 */
struct api429_rm_activity_trigger_def
{
   AiUInt8 start_pat;    /*!< start trigger pattern*/
   AiUInt8 start_mask;   /*!< start trigger mask*/
   AiUInt8 stop_pat;     /*!< stop trigger pattern*/
   AiUInt8 stop_mask;    /*!< stop trigger mask*/
};

/*! \typedef TY_API429_RM_ACTIVITY_TRIGGER_DEF
 * Convenience typedef for \ref api429_rm_activity_trigger_def
 */
typedef struct api429_rm_activity_trigger_def TY_API429_RM_ACTIVITY_TRIGGER_DEF;


/*! \struct api429_trg_ctl_cmd
 * This structure allows to set the trigger
 */
struct api429_trg_ctl_cmd
{
    AiUInt8 low_func;         /*!< reserved for later extension should be set to 0 */
    AiUInt8 up_func;          /*!< Upper Limit Start Trigger Function Mode. 0 means __Equal__, 1 means __Not equal__, 2 means __Less than__, 3 means __Greater than__ */
    AiUInt16  padding1;       /*!< reserved */
    AiUInt32 mask;            /*!< Monitor Trigger Mask */
    AiUInt32 low_limit;       /*!< Monitor Trigger Lower Limit */
    AiUInt32 up_limit;        /*!< Monitor Trigger Upper Limit */
};

/*! \typedef TY_API429_TRG_CTL_CMD
 * Convenience typedef for \ref api429_trg_ctl_cmd
 */
typedef struct api429_trg_ctl_cmd TY_API429_TRG_CTL_CMD;



/*! \union api429_tm_tag
* time tag word of a receiver monitor buffer entry
*/
#ifdef HOST_ENDIAN_LITTLE
union api429_tm_tag
{
    AiUInt32 all; //!< the complete tm_tag
    struct
    {
        AiUInt32 microseconds : 20;  //!< microseconds of time tag
        AiUInt32 seconds : 6;  //!< seconds of time tag
        AiUInt32 minutes : 6;  //!< minutes of time tag
    }b; //!< struct to access every bit
};
#else
union api429_tm_tag
{
    AiUInt32 all; //!< the complete tm_tag
    struct
    {
        AiUInt32 minutes : 6;  //!< minutes of time tag
        AiUInt32 seconds : 6;  //!< seconds of time tag
        AiUInt32 microseconds : 20;  //!< microseconds of time tag
    }b;  //!< struct to access every bit
};
#endif

/*! \union api429_brw
* buffer report word of a receiver monitor buffer entry
*/
#ifdef HOST_ENDIAN_LITTLE
union api429_brw
{
    AiUInt32 all; //!< the complete brw
    struct
    {
        AiUInt32 hours : 8;  //!< hours of time tag
        AiUInt32 speed : 1;  //!< set to one if channel is set to high speed
        AiUInt32 lss : 1;  //!< the low speed selector
        AiUInt32 gsm : 2;  //!< global speed modifier
        AiUInt32 channel : 4;  //!< channel this entry was received from
        AiUInt32 udf : 1;  //!< update flag
        AiUInt32 e_type : 5;  /*!< error type
                                 <table>
                                   <tr><th align = "center">Binary value  <th align = "center"> Description
                                   <tr><td align = "center">00000b <td align = "center"> No error detected
                                   <tr><td align = "center">00011b <td align = "center"> Bitcount high / low error
                                   <tr><td align="center">00101b <td align="center"> Coding error
                                   <tr><td align="center">01001b <td align="center"> Gap error
                                   <tr><td align="center">10001b <td align="center"> Parity error
                                 </table>*/
        AiUInt32 biu : 2;  //!< set to one, if received on BIU2.
        AiUInt32 gap :8;  //!< gap time
    }b; //!< struct to access every bit
};
#else
union api429_brw
{
    AiUInt32 all; //!< the complete brw
    struct
    {
        AiUInt32 gap :8;  //!< gap time
        AiUInt32 biu : 2;  //!< set to one, if received on BIU2.
        AiUInt32 e_type : 5;  /*!< error type
                                <table>
                                  <tr><th align="center">Binary value  <th align="center"> Description
                                  <tr><td align="center">00000b <td align="center"> No error detected
                                  <tr><td align="center">00011b <td align="center"> Bitcount high/low error
                                  <tr><td align="center">00101b <td align="center"> Coding error
                                  <tr><td align="center">01001b <td align="center"> Gap error
                                  <tr><td align="center">10001b <td align="center"> Parity error
                                </table>*/
        AiUInt32 udf : 1;  //!< update flag
        AiUInt32 channel : 4;  //!< channel this entry was received from
        AiUInt32 gsm : 2;  //!< global speed modifier
        AiUInt32 lss : 1;  //!< the low speed selector
        AiUInt32 speed : 1;  //!< set to one if channel is set to high speed
        AiUInt32 hours : 8;  //!< hours of time tag
    }b;  //!< struct to access every bit
};
#endif

/*! \struct api429_rcv_stack_entry
 *
 *  This structure describes a monitor entry
 */
struct api429_rcv_stack_entry
{
    AiUInt32 ldata;   /*!< Label data */
    union api429_tm_tag tm_tag;  /*!< 32 bit Timetag */
    union api429_brw brw;     /*!< Buffer Report Word */
};


/*! \typedef TY_API429_RCV_STACK_ENTRY
 * Convenience typedef for \ref api429_rcv_stack_entry
 */
typedef struct api429_rcv_stack_entry TY_API429_RCV_STACK_ENTRY;


/*! \struct api429_rcv_stack_entry_ex
 *
 * This structure describes an extended monitor entry
 * that contains day of year.
 *
 */
struct api429_rcv_stack_entry_ex
{
    AiUInt32 ldata;         /*!< Label data */
    union api429_tm_tag tm_tag;  /*!< 32 bit Timetag */
    union api429_brw brw;     /*!< Buffer Report Word */
    AiUInt32 day_of_year;   /*!< The day of the year. */
};


/*! \typedef TY_API429_RCV_STACK_ENTRY_EX
 * Convenience typedef for \ref api429_rcv_stack_entry_ex
 */
typedef struct api429_rcv_stack_entry_ex TY_API429_RCV_STACK_ENTRY_EX;




/*! \brief Initializes receive monitoring for a channel
 *
 * This function can be used to enable receive monitoring for a channel. \n
 * Data received on a channel can be monitored to a channel specific buffer which is called 'local' monitoring with \ref API429_RM_MODE_LOC\n
 * \n
 * The function also supports multiplexing of data streams received on several channels into a single buffer which
 * is called 'global' monitoring. \n
 * The last call to this function with \ref API429_RM_MODE_GLB will determine the properties of the monitoring buffer \n
 * used for global monitoring. The settings of all previous calls with \ref API429_RM_MODE_GLB will be overwritten. \n
 * Calling this function will overwrite all settings of a previously created monitor for the channel,
 * hence it will fail when channel is currently active.
 * @param [in] board_handle the handle of the module the channel belongs to
 * @param [in] channel_id ID of channel to initialize receive monitor on
 * @param [in] setup Monitor setup properties. See \ref api429_rm_setup
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RmCreate( AiUInt8 board_handle, AiUInt8 channel_id, const struct api429_rm_setup* setup);


/*! \brief Get information about a receive monitor instance on a specific Arinc4 429 receive channel
 *
 * Will retrieve information about the general monitor set-up on a specific channel. \n
 * The channel must be configured for receiving and monitoring before calling this function,
 * otherwise an error will be returned.
 * @param [in] board_handle the handle of the module the channel belongs to
 * @param [in] channel_id ID of the channel to get monitor info of
 * @param [out] monitor_setup pointer to \ref api429_rm_setup where info will be stored
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RmInfoGet(AiUInt8 board_handle, AiUInt8 channel_id,
                                                    struct api429_rm_setup* monitor_setup);


/*! \brief Defines general trigger set-up for receive monitor
 *
 * This function is used to define general trigger set-up of a monitor on
 * a specific receive channel. \n
 * It is used to configure internal, external as well as software defined monitor start and stop triggers. \n
 * For setting up software defined trigger conditions, additional configuration is necessary using the functions
 * \ref Api429RmTriggerPatternSet, \ref Api429RmStartTriggerSet or \ref Api429RmStopTriggerSet.
 * @param [in] board_handle handle of the module the receive channel belongs to
 * @param [in] channel ID of receive channel to set-up monitor triggers for
 * @param [in] trigger_setup pointer to trigger set-up structure
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RmTriggerConfigSet( AiUInt8 board_handle, AiUInt8 channel,
                                                             const struct api429_rm_trigger_setup* trigger_setup);


/*! \brief Configures monitoring of Labels
 *
 * This function can be used to either enable or disable specific label/SDI combinations
 * for monitoring.
 * @param [in] board_handle handle to board the receive channel belongs to
 * @param [in] b_Chn receive channel that is enabled for monitoring
 * @param [in] label_config See \ref api429_rm_label_config
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RmLabelConfigure( AiUInt8 board_handle, AiUInt8 b_Chn, const struct api429_rm_label_config* label_config);


/*! \brief Configures monitoring of multiple Labels
 *
 * This function can be used to either enable or disable multiple label/SDI combinations
 * for monitoring.
 * @param [in] board_handle handle to board the receive channel belongs to
 * @param [in] b_Chn receive channel that is enabled for monitoring
 * @param [in] ulCount number of labels to configure
 * @param [in] pxSetup pointer to array of \ref api429_rm_label_config instances. Must hold at least ulCount entries.
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RmMultiLabelConfigure(AiUInt8 board_handle, AiUInt8 b_Chn, AiUInt32 ulCount, struct api429_rm_label_config* pxSetup );


/*! \brief Configures a monitor function block
 *
 * @param [in] board_handle handle to board the monitor channel belongs to
 * @param [in] b_Chn ID of monitoring channel
 * @param [in] b_Label ID of label
 * @param [in] b_Sdi SDI extension of label
 * @param [in] b_Con enable/disable function block
 * @param [in] px_FuncBlk pointer to function block definition
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RmFuncBlockConfigure   ( AiUInt8 board_handle, AiUInt8 b_Chn, AiUInt8 b_Label, AiUInt8 b_Sdi, AiUInt8 b_Con, struct api429_rm_function_block  *px_FuncBlk );


/*! \brief This function is utilized to set the start/stop trigger pattern
 *
 * @param [in] board_handle
 * @param [in] b_Chn
 * @param [in] px_Para
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */

AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RmTriggerPatternSet  ( AiUInt8 board_handle, AiUInt8 b_Chn, struct api429_rm_activity_trigger_def  *px_Para );


/*! \brief Set a monitor start trigger
 *
 * @param [in] board_handle handle to boar the monitor channel belongs to
 * @param [in] b_Chn ID of monitor channel
 * @param [in] b_Label ID of label to set trigger for
 * @param [in] b_Sdi SDI extension for label
 * @param [in] b_Con enable/disable start trigger
 * @param [in] px_Ctl See \ref api429_trg_ctl_cmd
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RmStartTriggerSet(AiUInt8 board_handle, AiUInt8 b_Chn, AiUInt8 b_Label, AiUInt8 b_Sdi, AiUInt8 b_Con,
                                                           struct api429_trg_ctl_cmd  *px_Ctl );


/*! \brief Set a monitor stop trigger
 *
 * This function defines the monitor stop trigger condition.
 * @param [in] board_handle handle to boar the monitor channel belongs to
 * @param [in] b_Chn ID of monitor channel
 * @param [in] b_Label ID of label to set trigger for
 * @param [in] b_Sdi SDI extension for label
 * @param [in] b_Con enable/disable stop trigger
 * @param [in] px_Ctl See \ref api429_trg_ctl_cmd
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RmStopTriggerSet(AiUInt8 board_handle, AiUInt8 b_Chn, AiUInt8 b_Label, AiUInt8 b_Sdi, AiUInt8 b_Con,
                                                          struct api429_trg_ctl_cmd  *px_Ctl );


/*! \brief Resume monitoring on a channel
 *
 * This function will resume monitoring on a channel that has been previously
 * suspended using \ref Api429RmSuspend. \n
 * Will return an error when monitoring is not initialized for the given channel. \n
 * When calling this function on an active monitoring, the function will have not effect and return successful execution.
 * @param [in] board_handle handle to the module the channel belongs to
 * @param [in] channel ID of the channel to resume monitoring on
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RmResume(AiUInt8 board_handle, AiUInt8 channel);


/*! \brief Suspend monitoring on a channel
 *
 * This function will suspend monitoring on a channel. No more receive data will be monitored after calling this function. \n
 * Monitoring can be resumed afterwards by calling \ref Api429RmResume.\n
 * When calling this function before activating the channel using \ref Api429ChannelStart, the monitor will be in a suspended state. \n
 * Will return an error when monitoring is not initialized for the given channel. \n
 * When calling this function on an already suspended monitoring, the function will have not effect and return successful execution.
 * @param [in] board_handle handle to the module the channel belongs to
 * @param [in] channel ID of the channel to suspend monitoring on
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RmSuspend( AiUInt8 board_handle, AiUInt8 channel);


/*! \brief Get a channel's current data monitoring status
 *
 * This function is utilized to retrieve information about the data monitoring status on the specified Arinc 429 receiver channel.\n
 * Several monitor properties are encoded in the _status_ output parameter of this function:
 * <table>
 * <tr><th align="center">status bit  <th align="center"> Description
 * <tr><td>ERT (bit 5) <td> error trigger detected
 * <tr><td>CT (bit 6)  <td> complex function trigger detected
 * <tr><td>MS (bit 7)  <td> monitor has stopped
 * <tr><td>MT (bit 8)  <td> monitor has triggered
 * <tr><td>MODE (bit 10..12)   <td> 0: no monitoring\n 1: local monitoring\n 2: global monitoring
 * </table>
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] channel_id ID of channel
 * @param [out] monitoring_activity General state of data monitoring on the specified channel.
                                     - API429_HALT if channel was not started or monitoring has been suspended
                                     - API429_BUSY if data monitoring is active.
 * @param [out] status Detailed information about data monitoring status of the specified channel.
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RmStatusGet(AiUInt8 board_handle, AiUInt8 channel_id, AiUInt8* monitoring_activity, AiUInt16* status);


/*! \brief Get current position of monitor stack pointers
 *
 * This function is utilized to read the monitor stack pointers on the selected Arinc 429
 * receiver channel. Using these pointers the monitored data can be read directly from
 * the board. The start of the receiver monitor buffer can be found with \ref Api429BoardMemLocationGet
 * Please have a look into the Programmer’s Guide for details.
 * For reading the monitor data, please consider using \ref Api429RmDataRead
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] b_Chn ID of monitor channel
 * @param [out] pl_Stp Capture Start Pointer. Shows the offset of the first received message, relative to the start global memory. Only valid after monitoring has started.
 * @param [out] pl_Ctp Trigger Pointer. Shows the offset of the received message that triggered the monitoring, relative to the start global memory. Only valid after monitoring has started.
 * @param [out] pl_Etp Capture End Pointer. Shows where the firmware will write the next monitoring entry to (Monitor Buffer Fill Pointer). 
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RmStackPointersGet( AiUInt8 board_handle, AiUInt8 b_Chn, AiUInt32  *pl_Stp, AiUInt32  *pl_Ctp, AiUInt32  *pl_Etp );


/*! \brief Read Monitor data
 *
 * This function is utilized to read the new stack entries from the monitor stack of the
 * selected Arinc 429 receiver channel since the last call of the function. If more
 * entries than specified in uw_EntriesToRead are on the stack, the oldest entries will
 * be read. A stack entry consists of three 32-bit words.
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] b_Chn ID of monitor channel
 * @param [in] uw_EntriesToRead Maximum number of entries to be read.
 * @param [out] puw_Count The amount of entries really read. If *puw_count is as high as
 * uw_EntriesToRead, there might be some entries left in the monitor stack. In this
 * case it’s recommended to call this function again to read the rest of data.
 * @param [out] px_SData Array of pointer to Stack Entry Data structure
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RmDataRead( AiUInt8 board_handle, AiUInt8 b_Chn, AiUInt16 uw_EntriesToRead, AiUInt16 *puw_Count,
                                                     struct api429_rcv_stack_entry *px_SData );


/*! \brief Read monitor data and add the day of year
 *
 * This function is utilized to read the new stack entries from the monitor stack of the
 * selected Arinc 429 receiver channel since the last call of the function. If more
 * entries than specified in uw_EntriesToRead are on the stack, the oldest entries will
 * be read.
 * This function internally calls \ref Api429RmDataRead to get the three 32-bit words
 * that are part of the receiver monitor buffer entry and adds the day of year that is
 * read from the IRIG source.\n
 * This command may show incorrect data if called less than once per 24 hours.\n
 * The day of year information is added when the data is read from the receiver monitor
 * buffer and not when the data is received.\n
 * Changing the onboard time might cause the next call of this function to fail\n
 * It is better to use \ref Api429RmDataRead instead.
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] b_Chn ID of monitor channel
 * @param [in] uw_EntriesToRead Maximum number of entries to be read.
 * @param [out] puw_Count The amount of entries really read. If *puw_count is as high as
 * uw_EntriesToRead, there might be some entries left in the monitor stack. In this
 * case it’s recommended to call this function again to read the rest of data.
 * @param [out] px_SData See \ref api429_rcv_stack_entry_ex
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RmDataReadWithDayOfYear( AiUInt8 board_handle, AiUInt8 b_Chn, AiUInt16 uw_EntriesToRead, AiUInt16 *puw_Count,
                                                       struct api429_rcv_stack_entry_ex *px_SData );



/** @} */



#endif /* API429RM_H_ */
