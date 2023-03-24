/******************************************************************************

           Copyright (c) AIM GmbH 2001, 79111 Freiburg, Germany.                 
                                                                             
            All rights reserved.  No part of this software may                
            be published, distributed, translated or otherwise                
            reproduced by any means or for any purpose without                
            the prior written consent of AIM GmbH, Freiburg.                  

******************************************************************************/
/*! \file Api429Channel.h
 *
 *  This header file contains declarations for
 *  generic, channel related API functionality
 *
 *  Created on: 03.02.2016
 *      Author: Markus Melcher
 */

#ifndef API429CHANNEL_H_
#define API429CHANNEL_H_


#include "Ai_cdef.h"
#include "Api429.h"


/**
* \defgroup channel Channel Handling
   This module contains functionality related to generic channel handling
   independent from receiving or transmitting data
* @{
*/



/*! \enum api429_speed
 * Enumeration of all possible Arinc429 speeds
 */
enum api429_speed
{
    API429_LO_SPEED = 0,   /*!< low speed value */
    API429_HI_SPEED        /*!< high speed value */
};
/*! \typedef TY_E_API429_SPEED
 * Convenience typedef for \ref api429_speed
 */
typedef enum api429_speed TY_E_API429_SPEED;


/*! \struct api429_channel_info
 *
 * Output parameter of \ref Api429ChannelInfoGet.
 * Holds current properties of a specific channel
 * may be used for Capability and Configuration test macros (see below)
 */
struct api429_channel_info
{
    AiUInt32 config_flags;       /*!< bit-field that indicates current configuration of the channel */
    AiUInt32 capability_flags;   /*!< bit field that holds static capabilities of the channel e.g. if it's able to transmit/receive */
    enum api429_speed speed;     /*!< Current speed setting of channel. */
    AiBoolean active;            /*!< Indicates if channel is active. AiTrue if it is, AiFalse if otherwise */
};

/*! \typedef TY_API429_CHANNEL_INFO
 * Convenience typedef for \ref api429_channel_info
 */
typedef struct api429_channel_info TY_API429_CHANNEL_INFO;





/* ***************************************************************** */
/*   Flags for config_flags member of TY_API429_CHANNEL_INFO         */
/* *******************************************************************/



/*! \def API429_CHN_CFG_UNCONFIGURED
 * Value for 'config_flags' member of \ref api429_channel_info
 * that indicates a channel is not configured
 */
#define API429_CHN_CFG_UNCONFIGURED 0

/*! \def API429_CHN_CFG_RX_LABEL_FLAG
 * Flag that indicates a channel was configured for normal receive mode
 */
#define API429_CHN_CFG_RX_LABEL_FLAG (1 << 0)

/*! \def API429_CHN_CFG_RX_POLLUTION_FLAG
 * Flag that indicates a channel was configured as Loop/Pollution receiver
 */
#define API429_CHN_CFG_RX_POLLUTION_FLAG (1 << 1)

/*! \def API429_CHN_CFG_RM_LOCAL_FLAG
 * Flag that indicates a channel was configured for local monitoring mode
 */
#define API429_CHN_CFG_RM_LOCAL_FLAG (1 << 2)

/*! \def API429_CHN_CFG_RM_GLOBAL_FLAG
 * Flag that indicates a channel was configured for global monitoring mode
 */
#define API429_CHN_CFG_RM_GLOBAL_FLAG (1 << 3)

/*! \def API429_CHN_CFG_TX_FRAMING_FLAG
 * Flag that indicates a channel was configured for framing transmit mode
 */
#define API429_CHN_CFG_TX_FRAMING_FLAG (1 << 4)

/*! \def API429_CHN_CFG_TX_POLLUTION_FLAG
 * Flag that indicates a channel was configured as Loop/Pollution transmitter
 */
#define API429_CHN_CFG_TX_POLLUTION_FLAG (1 << 5)

/*! \def API429_CHN_CFG_PHYS_REPLAY_FLAG
 * Flag that indicates a channel was configured for Physical Replay
 */
#define API429_CHN_CFG_PHYS_REPLAY_FLAG (1 << 6)

/*! \def API429_CHN_CFG_TX_DYNTAG_FRAMING_FLAG
 * Flag that indicates a channel was configured for dynamic framing
 */
#define API429_CHN_CFG_TX_DYNTAG_FRAMING_FLAG (1 << 7)

/*! \def API429_CHN_CFG_TX_FIFO_FLAG
 * Flag that indicates a channel was configured as transmitter FIFO
 */
#define API429_CHN_CFG_TX_FIFO_FLAG (1 << 8)

/*! \def API429_CHN_CFG_TX_RATE_CONTROLLED_FLAG
 * Flag that indicates a channel was configured for automatic (Rate-Oriented) framing
 */
#define API429_CHN_CFG_TX_RATE_CONTROLLED_FLAG (1 << 9)


/*! \def API429_CHN_CFG_SDI_ENABLED_FLAG
 * Flag that indicates a channel was configured with SDI sorting enabled
 */
#define API429_CHN_CFG_SDI_ENABLED_FLAG (1 << 10)

/*! \def API429_CHN_CFG_PARITY_ENABLED_FLAG
 * Flag that indicates a channel was configured with parity handling enabled
 */
#define API429_CHN_CFG_PARITY_ENABLED_FLAG (1 << 11)




/* ***************************************************************** */
/*   Configuration test macros for TY_API429_CHANNEL_INFO            */
/* *******************************************************************/


/*! \def API429_CHANNEL_IN_RX_NORMAL_MODE
 * Checks if channel if configured for normal receive mode
 */
#define API429_CHANNEL_IN_RX_NORMAL_MODE(channel) \
    ((channel)->config_flags & API429_CHN_CFG_RX_LABEL_FLAG)

/*! \def API429_CHANNEL_IN_RX_LP_MODE
 * Checks if channel is configured as loop/pollution receiver
 */
#define API429_CHANNEL_IN_RX_LP_MODE(channel) \
    ((channel)->config_flags & API429_CHN_CFG_RX_POLLUTION_FLAG)

/*! \def API429_CHANNEL_IN_RX_TX_MIXING_MODE
 * Checks if channel is configured in RX/TX mixing mode
 */
#define API429_CHANNEL_IN_RX_TX_MIXING_MODE(channel) \
    ((channel)->config_flags & API429_CHN_CFG_RX_MIXING_FLAG)

/*! \def API429_CHANNEL_IN_LOCAL_MONITORING_MODE
 * Checks if channel is configured for local monitoring
 */
#define API429_CHANNEL_IN_LOCAL_MONITORING_MODE(channel) \
    ((channel)->config_flags & API429_CHN_CFG_RM_LOCAL_FLAG)

/*! \def API429_CHANNEL_IN_GLOBAL_MONITORING_MODE
 * Checks if channel is configured for global monitoring
 */
#define API429_CHANNEL_IN_GLOBAL_MONITORING_MODE(channel) \
    ((channel)->config_flags & API429_CHN_CFG_RM_GLOBAL_FLAG)

/*! \def API429_CHANNEL_IN_TX_FRAMING_MODE
 * Checks if channel is configured for TX framing
 */
#define API429_CHANNEL_IN_TX_FRAMING_MODE(channel) \
    ((channel)->config_flags & API429_CHN_CFG_TX_FRAMING_FLAG)

/*! \def API429_CHANNEL_IN_TX_LP_MODE
 * Checks if channel is configured as loop/pollution transmitter
 */
#define API429_CHANNEL_IN_TX_LP_MODE(channel) \
    ((channel)->config_flags & API429_CHN_CFG_TX_POLLUTION_FLAG)

/*! \def API429_CHANNEL_IN_PHYS_REPLAY_MODE
 * Checks if channel is configured for physical replay mode
 */
#define API429_CHANNEL_IN_PHYS_REPLAY_MODE(channel) \
    ((channel)->config_flags & API429_CHN_CFG_PHYS_REPLAY_FLAG)

/*! \def API429_CHANNEL_IN_TX_DYNTAG_MODE
 * Checks if channel is in TX framing mode with dyntags enabled
 */
#define API429_CHANNEL_IN_TX_DYNTAG_MODE(channel) \
    ((channel)->config_flags & API429_CHN_CFG_TX_DYNTAG_FRAMING_FLAG)

/*! \def API429_CHANNEL_IN_TX_FIFO_MODE
 * Checks if channel is configured as TX FIFO
 */
#define API429_CHANNEL_IN_TX_FIFO_MODE(channel) \
    ((channel)->config_flags & API429_CHN_CFG_TX_FIFO_FLAG)


/*! \def API429_CHANNEL_IN_TX_RATE_CONTROLLED_MODE
 * Checks if channel is in rate controlled TX mode
 */
#define API429_CHANNEL_IN_TX_RATE_CONTROLLED_MODE(channel) \
    ((channel)->config_flags & API429_CHN_CFG_TX_RATE_CONTROLLED_FLAG)


/*! \def API429_CHANNEL_IN_TX_MODE
 * Checks if a channel is in any mode that is able to transmit data
 */
#define API429_CHANNEL_IN_TX_MODE(channel) \
    API429_CHANNEL_IN_TX_FRAMING_MODE(channel) | API429_CHANNEL_IN_TX_LP_MODE(channel)  | \
    API429_CHANNEL_IN_PHYS_REPLAY_MODE(channel) | API429_CHANNEL_IN_TX_DYNTAG_MODE(channel) | \
    API429_CHANNEL_IN_TX_FIFO_MODE(channel) | API429_CHANNEL_IN_TX_RATE_CONTROLLED_MODE(channel)


/*! \def API429_CHANNEL_IN_REPLAY_MODE
 * Checks if a channel is in any supported replay mode
 */
#define API429_CHANNEL_IN_REPLAY_MODE(channel) \
    API429_CHANNEL_IN_BUFFER_REPLAY_MODE(channel) | API429_CHANNEL_IN_PHYS_REPLAY_MODE(channel)


/*! \def API429_CHANNEL_IN_RX_MODE
 * Checks if a channel is in any mode that is able to receive data
 */
#define API429_CHANNEL_IN_RX_MODE(channel) \
    API429_CHANNEL_IN_RX_NORMAL_MODE(channel) | API429_CHANNEL_IN_RX_LP_MODE(channel)

/*! \def API429_CHANNEL_IN_MONITORING_MODE
 * Checks if channel is in any of the supported monitoring modes
 */
#define API429_CHANNEL_IN_MONITORING_MODE(channel) \
    API429_CHANNEL_IN_LOCAL_MONITORING_MODE(channel) | API429_CHANNEL_IN_GLOBAL_MONITORING_MODE(channel)




/* ***************************************************************** */
/*   Flags for capability_flags member of TY_API429_CHANNEL_INFO     */
/* *******************************************************************/


/*! \def API429_CHN_CAP_RX_FLAG
 * Flag that indicates a channel is able to receive data
 */
#define API429_CHN_CAP_RX_FLAG  (1 << 0)

/*! \def API429_CHN_CAP_TX_FLAG
 * Flag that indicates a channel is able to transmit data
 */
#define API429_CHN_CAP_TX_FLAG  (1 << 1)

/*! \def API429_CHN_CAP_VAR_AMP_FLAG
 * Flag that indicates a channel is able to transmit with variable amplitude
 */
#define API429_CHN_CAP_VAR_AMP_FLAG (1 << 2)


/* ***************************************************************** */
/*   Capability test macros for TY_API429_CHANNEL_INFO               */
/* *******************************************************************/


/*! \def API429_CHANNEL_CAN_TRANSMIT
 * Test macro that indicates if channel is able to transmit data
 */
#define API429_CHANNEL_CAN_TRANSMIT(channel) \
    ((channel).capability_flags & API429_CHN_CAP_TX_FLAG)

/*! \def API429_CHANNEL_CAN_RECEIVE
 * Test macro that indicates if channel is able to receive data
 */
#define API429_CHANNEL_CAN_RECEIVE(channel) \
    ((channel).capability_flags & API429_CHN_CAP_RX_FLAG)

/*! \def API429_CHANNEL_HAS_VARIABLE_AMPLITUDE
 * Test macro that indicates if channel is able to transmit with variable amplitude
 */
#define API429_CHANNEL_HAS_VARIABLE_AMPLITUDE(channel) \
    ((channel).capability_flags & API429_CHN_CAP_VAR_AMP_FLAG)


    
    
/*************************************
 specific Interrupt function definitions
*************************************/


#define API429_CHANNEL_EVENT_TAG(channel_event) \
    (((channel_event)->ul_Lla >> 20) & 0xFF)



/*! \union api429_loglist_entry
 * Log list entry C
*/
#ifdef HOST_ENDIAN_LITTLE
union api429_loglist_entry
{
  AiUInt32 ul_All; //!< the complete llc
  struct
  {
    AiUInt32 ul_Info:24;  //!< transfer or label index
    AiUInt32 uc_IntType:8; //!< interrupt event source information
  }t; //!< struct where event source is seperated from the payload

  struct
  {
    AiUInt32 ul_Info:24;  //!< transfer or label index
    AiUInt32 uc_Biu1:1;  //!< event source is BIU 1
    AiUInt32 uc_Biu2:1;  //!< event source is BIU 2
    AiUInt32 uc_Dma:1;  //!< event source is DMA
    AiUInt32 uc_Target:1;  //!< event source is target software
    AiUInt32 uc_Cmd:1;  //!< event source is command completion interrupt
    AiUInt32 res:3;  //!< reserved
  }b; //!< struct to access every bit
};
#else
union api429_loglist_entry
{
  AiUInt32 ul_All; //!< the complete llc
  struct
  {
    AiUInt32 uc_IntType:8; //!< interrupt event source information
    AiUInt32 ul_Info:24; //!< transfer or label index
  }t; //!< struct where event source is seperated from the payload

  struct
  {
    AiUInt32 res:3;  //!< reserved
    AiUInt32 uc_Cmd:1;  //!< event source is command completion interrupt
    AiUInt32 uc_Target:1;  //!< event source is target software
    AiUInt32 uc_Dma:1;  //!< event source is DMA
    AiUInt32 uc_Biu2:1;  //!< event source is BIU 2
    AiUInt32 uc_Biu1:1;  //!< event source is BIU 1
    AiUInt32 ul_Info:24; //!< transfer or label index
  }b;  //!< struct to access every bit
};
#endif

/*! \typedef TY_API429_LOGLIST_TYPE_ENTRY
 * Convenience typedef for \ref api429_loglist_entry
 */
typedef union api429_loglist_entry TY_API429_LOGLIST_TYPE_ENTRY;


/*! \struct api429_intr_loglist_entry
 * This structure describes an interrupt log list entry
 */
struct api429_intr_loglist_entry
{
   AiUInt32 ul_Lla;
   /*!< Log list entry A. Internal data that is used to calculate the channel number and the event type*/
   AiUInt32 ul_Llb;
   /*!< Log list entry B. Depending on the event source this is one of the following:
   - LDP: receive operation current label descriptor pointer (for receiver interrupts). This was used to calculate the transfer index and the TX data buffer base address in a complicated way. Please use ul_Llc and ul_Lld instead.\n
   - CMBFP: monitor operation current monitor buffer fill pointer (pointing to the next monitor buffer entry used by the monitor, for monitor interrupts).\n
   - RNBP: replay next buffer pointer, points to the next half buffer address that can be refilled. Used for replay interrupts.\n
   - CILP: transmit operation current instruction list pointer (for transmit interrupts). This was used to calculate the transfer index and the TX data buffer base address in a complicated way. Please use ul_Llc and ul_Lld instead.*/
   union api429_loglist_entry x_Llc;
   /*!< Log list entry C. \n
   - For transmit interrupts (of type API429_EVENT_TX_LABEL and API429_EVENT_TX_INDEX), the lower 24 bits of this value show the transfer index\n
   - For receive operation based interrupts (of type API429_EVENT_RX_ANY_LABEL, API429_EVENT_RX_INDEX and API429_EVENT_RX_ERROR) the lower 24 bits show the label ID.\n
   - For interrupts of type API429_EVENT_TX_HALT this value is undefined and should be ignored. */
   AiUInt32 ul_Lld;
   /*!< Log list entry D. \n
   - For transmit operation based interrupts (of type API429_EVENT_TX_LABEL and API429_EVENT_TX_INDEX) \n
     and for receive operation based interrupts (of type API429_EVENT_RX_ANY_LABEL, API429_EVENT_RX_INDEX and API429_EVENT_RX_ERROR), this value shows the data buffer base address\n
   - For interrupts of type API429_EVENT_TX_HALT this value is undefined and should be ignored. */
};

/*! \typedef TY_API429_INTR_LOGLIST_ENTRY
 * Convenience typedef for \ref api429_intr_loglist_entry
 */
typedef struct api429_intr_loglist_entry TY_API429_INTR_LOGLIST_ENTRY;


/*! \enum api429_event_type
 *
 * Enumeration of all event sources
 */
enum api429_event_type
{
    API429_EVENT_UNDEFINED     = 0,   /*!< event is of no known type */
    API429_EVENT_TX_HALT,             /*!< end of major frame reached */
    API429_EVENT_TX_SKIP,             /*!< event raised by a TX skip instruction */
    API429_EVENT_TX_LABEL,            /*!< event raised by a TX label transfer instruction */
    API429_EVENT_TX_INDEX,            /*!< tx buffer interrupt index reached */
    API429_EVENT_RX_ANY_LABEL,        /*!< rx label buffer event */
    API429_EVENT_RX_INDEX,            /*!< rx buffer interrupt index reached */
    API429_EVENT_RX_ERROR,            /*!< rx received an error */
    API429_EVENT_FUNC_BLOCK,          /*!< event raised by a function block */
    API429_EVENT_RM_TRIGGER,          /*!< rm trigger event */
    API429_EVENT_RM_BUFFER_FULL,      /*!< rm buffer end reached */
    API429_EVENT_RM_BUFFER_HALF_FULL, /*!< rm buffer middle reached */
    API429_EVENT_REPLAY_HALF_BUFFER,  /*!< replay buffer middle or end reached */
    API429_EVENT_REPLAY_STOP,         /*!< replay stopped */
    API429_EVENT_TX_FIFO              /*!< event raised by tx fifo */
};


/*! \typedef API429_CHANNEL_CALLBACK
 * prototype of the function that should be used for the event callback
 * @param module handle to the device
 * @param channel ID of the channel to initialize
 * @param type type of the event. See \ref api429_event_type
 * @param info additional information about the source of this event. See \ref api429_intr_loglist_entry \n
 * __Note:__ This pointer is only valid during event callback processing. It must not be accessed after callback finished.
 */
typedef void  (AI_CALL_CONV *API429_CHANNEL_CALLBACK)(AiUInt8 module,
                                 AiUInt8 channel,
                                 enum api429_event_type type,
                                 struct api429_intr_loglist_entry* info );



/* If legacy header is not used, make the callback type available with its 'old' name */
#if !defined API429_BSP10_LEGACY_H_
    typedef API429_CHANNEL_CALLBACK TY_INT429_FUNC_PTR;
#endif






/*! \brief Get information about a specific channel
 *
 * This function will return information about a specific channel of a specific device. \n
 * It contains the some dynamic properties as current configuration etc. and also some static \n
 * capabilities the channel offers e.g. if it is able to transmit or receive data
 * @param [in] board_handle module handle of the device the channel belongs to
 * @param [in] channel_id ID of channel to query for information
 * @param [out] pxInfo pointer to \ref api429_channel_info where information will be stored
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429ChannelInfoGet( AiUInt8 board_handle, AiUInt8 channel_id, struct api429_channel_info *pxInfo );


/*! \brief Clear configuration of a channel
 *
 * This function will release a specific channel. \n
 * The channel will be halted and all of its used resources freed. \n
 * After successful return of this function the channel is stopped and in an uninitialized state. \n
 * The channel must be initialized before it can be started again using either \ref Api429RxInit or \ref Api429TxInit.
 * @param [in] board_handle handle of the module the channel belongs to
 * @param [in] channel_id ID of the channel to clear
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429ChannelClear( AiUInt8 board_handle, AiUInt8 channel_id);


/*! \brief Start a channel
 *
 * This function will start a specific channel, if it was initialized before using 
 * either \ref Api429RxInit or \ref Api429TxInit.
 * @param [in] board_handle handle of the module the channel belongs to
 * @param [in] channel_id ID of the channel to be started
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429ChannelStart( AiUInt8 board_handle, AiUInt8 channel_id);


/*! \brief Halt a channel
 *
 * This function will halt a specific channel. In will stop sending or receiving any data.
 * @param [in] board_handle handle of the module the channel belongs to
 * @param [in] channel_id ID of the channel to be halted
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429ChannelHalt( AiUInt8 board_handle, AiUInt8 channel_id);


/*! \brief Set channel speed
 *
 * This function can be used to set the transmit/receive speed of a specific
 * channel to either Arinc 429 High Speed or Low Speed. \n
 * Channel must be initialized for transmission or receiving with either \ref Api429TxInit or \ref Api429RxInit
 * before calling this function.
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] b_Chn ID of channel to set speed for
 * @param [in] speed Speed to set. See \ref api429_speed
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429ChannelSpeedSet( AiUInt8 board_handle, AiUInt8 b_Chn, enum api429_speed speed );


/*! \brief Registers an event notification handler
 *
 * This function is used to register an event notification handler for
 * a specific channel.\n
 * If an event handler function that handles several channels is needed, it is
 * necessary to call this function for all required channels, each with the same given
 * handler function.
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] uc_Chn ID of channel to install event handler for
 * @param [in] uc_Type Reserved
 * @param [in] pf_IntFunc function pointer to handler
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429ChannelCallbackRegister(AiUInt8 board_handle, AiUInt8 uc_Chn, AiUInt8 uc_Type, API429_CHANNEL_CALLBACK pf_IntFunc);


/*! \brief Unregisters an event notification handler
 *
 * This function will unregister an event notification handler that has previously been installed
 * using \ref Api429ChannelCallbackRegister.
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] uc_Chn ID of channel to unregister notification from
 * @param [in] uc_Type Reserved
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429ChannelCallbackUnregister( AiUInt8 board_handle, AiUInt8 uc_Chn, AiUInt8 uc_Type );



/** @} */




#endif /* API429CHANNEL_H_ */
