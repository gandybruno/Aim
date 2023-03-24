/******************************************************************************

           Copyright (c) AIM GmbH 2001, 79111 Freiburg, Germany.                 
                                                                             
            All rights reserved.  No part of this software may                
            be published, distributed, translated or otherwise                
            reproduced by any means or for any purpose without                
            the prior written consent of AIM GmbH, Freiburg.                  

******************************************************************************/
/*! \file Api429Rx.h
 *
 *  This header file contains function declarations
 *  related to channel receive functionality
 *  Created on: 09.02.2016
 *      Author: Markus Melcher
 */

#ifndef API429RX_H_
#define API429RX_H_


#include "Ai_cdef.h"



/**
* \defgroup receiving Data Receiver
This module contains functionality related to receiving of Arinc 429
bus traffic.
* @{
*/




/*! \struct api429_rx_frame_response_setup
 *
 * Comprises a setup for a frame based receive response.
 */
struct api429_rx_frame_response_setup
{
    AiUInt8 tx_channel;         /*!< ID of transmit channel to send response on */
    AiUInt32 tx_acyc_frame_id;  /*!< ID of acyclic minor frame to respond */
    AiUInt32 compare_mask;      /*!< Received data word will be combined by a logical AND operation with this mask */
    AiUInt32 compare_value;     /*!< The masked receive data will be compared with this value. If matching, the respond sending will be initiated */
};

/*! \typedef TY_API429_RX_FRAME_RESPONSE_SETUP;
 * Convenience macro for \ref api429_rx_frame_response_setup
 */
typedef struct api429_rx_frame_response_setup TY_API429_RX_FRAME_RESPONSE_SETUP;



/*! \struct api429_rx_activity
 *
 * Rx Activity structure
 */
struct api429_rx_activity
{
    AiUInt32 ChannelActivity[32][8]; /*!< Contains eight long words for each channel. The eight long words are a bitfield, that shows for which labels data was received for a specific channel */
};

/*! \typedef TY_API429_RX_ACTIVITY;
 * Convenience macro for \ref api429_rx_activity
 */
typedef struct api429_rx_activity TY_API429_RX_ACTIVITY;


/*! \struct api429_rcv_pb_cmd
 *
 * Defines pollution of data in a receive/transmit loop.
 * In case of pollution, the following operations are applies to the recevied data 
 * word in this order, before sending the data.
 *    - &= and_mask
 *    - |= or_mask
 *    - ^= xor_mask
 *    - if( asc == 0 )   += addsub_val  \n
 *      else             -= addsub_val
 */
struct api429_rcv_pb_cmd
{
   AiUInt8  pb_id;          /*!< Pollution Block Identifier - each channel allows id 1 .. 24 */
   AiUInt8  asc;            /*!< Addition/ Subtraction Control. 0 = Addition. 1 = Subtraction */
   AiUInt16 padding1;       /*!< reserved */
   AiUInt32 and_mask;       /*!< AND Mask */
   AiUInt32 or_mask;        /*!< OR Mask */
   AiUInt32 xor_mask;       /*!< XOR Mask */
   AiUInt32 addsub_val;     /*!< ADD/SUB Mask */
   AiUInt16 start_delay;    /*!< Specifies how many entries are skipped before starting loop/pollution. */
   AiUInt16 duration;       /*!< Specifies how many entries are looped/polluted. */
};


/*! \typedef TY_API429_RCV_PB_CMD
 * Convenience typedef for \ref api429_rcv_pb_cmd
 */
typedef struct api429_rcv_pb_cmd TY_API429_RCV_PB_CMD;


/*! \struct api429_rx_label_setup
 *
 * This structure contains parameters for configuring
 * reception of specific labels
 */
struct api429_rx_label_setup
{
    AiUInt32 label;     /*!< Label Number */
    AiUInt32 sdi;       /*!< SDI Number. When set to __4__, all received data will be stored in one buffer.
                             The latest received data will be stored in the buffer. 
                             This value is ignored if sdi sorting is disabled in \ref Api429RxInit by setting sdi_enabled to AiFalse */
    AiUInt32 con;       /*!< 0 = disable reception of label. 1 = enable reception of label */
    AiUInt32 irCon;     /*!< Label Interrupt Control. \n
                             Bit-field that allows to enable/disable generation of interrupts on various label events. \n
                             Setting a bit to _1_ will enable, setting to _0_ disable interrupt generation on the corresponding event.
                             <table>
                               <tr><th align="center">Bit Position <th align="center"> Description
                               <tr><td align="center">0    <td align="center">  Interrupt when an error is received on a label
                               <tr><td align="center">1    <td align="center">  Interrupt each time a label is received
                               <tr><td align="center">2    <td align="center">  Interrupt when the buffer index passes the Buffer Interrupt Index (irIndex)
                            </table> */
    AiUInt32 irIndex;   /*!< Buffer Interrupt Index. Valid from 1 to 1023, must be a valid buffer index (irIndex <= bufSize) */
    AiUInt32 bufSize;   /*!< Label Receive Buffer Size. Valid from 1 to 1023 */
};


/*! \typedef TY_API429_RX_LABEL_SETUP
 * Convenience typedef for \ref api429_rx_label_setup
 */
typedef struct api429_rx_label_setup TY_API429_RX_LABEL_SETUP;


/*! \struct api429_rx_buf_entry
 * This structures describes one label receive buffer entry
 */
struct api429_rx_buf_entry
{
    AiUInt32 lab_data;      /*!< Arinc 429 data word. The lowest byte of each data word is the label id. To meet the ARINC 429 specification the label id is automatically transferred in reverse bit order. */
};


/*! \typedef TY_API429_RX_BUF_ENTRY
 * Convenience macro for \ref api429_rx_buf_entry
 */
typedef struct api429_rx_buf_entry TY_API429_RX_BUF_ENTRY;


/*! \struct api429_rx_buf_ctl
 *
 * This structures describes a buffer header for label
 * receive buffers
 */
struct api429_rx_buf_ctl
{
   AiUInt16 ixw;         /*!< Interrupt Index. Only important, if bit 2 of b_IrCon of \ref Api429RxLabelConfigure was set. */
   AiUInt16 inr;         /*!< Index Reload */
   AiUInt16 ci;          /*!< Current Index. Changes when a label was received */
};


/*! \typedef TY_API429_RX_BUF_CTL
 * Convenience typedef for \ref api429_rx_buf_ctl
 */
typedef struct api429_rx_buf_ctl TY_API429_RX_BUF_CTL;





/*! \brief Basic initialization of a channel for receiving data
 *
 * This function will initialize an Arinc429 channel for data reception. \n
 * Any previous configuration of the specified channel is cleared. \n
 * After running this command, the channel will be in a halted state
 * with reception of any labels disabled and no monitor assigned.
 * @param [in] board_handle handle to the device the channel belongs to
 * @param [in] b_Chn ID of the channel to initialize
 * @param [in] sdi_enabled if set to AiTrue, the SDI field is taken into account to determine received labels
 * @param [in] parity_check_enabled if set to AiTrue, the parity bit of received labels is used to indicate parity errors \n
 *                             if set to AiFalse, the parity bit will be untouched and returned as received on bus
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RxInit( AiUInt8 board_handle, AiUInt8 b_Chn, AiBoolean sdi_enabled, AiBoolean parity_check_enabled );


/*! \brief Set up a data forwarding for a receive channel
 *
 * This function can be applied to receive channels that have been initialized with
 * \ref Api429RxInit. \n
 * After calling this function, all data received for enabled labels will be forwarded
 * to the specified transmitter channel and sent on this channel at once. \n
 * Attention: The specified transmitter channel is not checked for being correctly
 * configured. \n
 * The transmitter must be configured in loop/pollution mode and must match the speed of the receiver channel. \n
 * Receiver and Transmitter channel must be both either located on the lower 16 or on the upper 16 channels
 * of the channel set the device provides in order to get a valid data loop.
 * @param [in] board_handle handle to the device the channels belong to
 * @param [in] channel the receive channel that shall forward the data
 * @param [in] transmitter_channel the transmitter channel that will send the forwarded data
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RxDataLoopAssign( AiUInt8 board_handle, AiUInt8 channel, AiUInt8 transmitter_channel);


/*! \brief Assign an automatic frame response on reception of a label
 *
 *  This function can be used to initiate sending of a response when a specific label is received. \n
 *  The channel on which the response frame shall be transmitted has to be initialized in a frame based mode before with
 *  \ref Api429TxInit. \n
 *  Also the frame to be responded must be set-up with \ref Api429TxAcycFrameCreate before calling this function
 *  with the specified frame ID.
 * @param [in] board_handle handle to the module to use
 * @param [in] receive_channel the receive channel to react on reception
 * @param [in] label the label on which reception a response shall be initiated
 * @param [in] sdi the SDI that may extend the specified label. Only valid if SDI sorting has been enabled using \ref Api429RxInit
 * @param [in] p_Setup pointer to response set-up data. See \ref api429_rx_frame_response_setup
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RxFrameResponseAssign(AiUInt8 board_handle, AiUInt8 receive_channel, AiUInt8 label, AiUInt8 sdi,
                                                               struct api429_rx_frame_response_setup* p_Setup );


/*! \brief Release an automatic frame response on reception of a label
 *
 * This function can be used to release a frame response previously set-up with \ref Api429RxFrameResponseAssign.
 * @param [in] board_handle handle to the module to use
 * @param [in] receive_channel the receive channel to release response from
 * @param [in] label the label to release response from
 * @param [in] sdi the SDI that may extend the specified label. Only valid if SDI sorting has been enabled using \ref Api429RxInit
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RxFrameResponseRelease(AiUInt8 board_handle, AiUInt8 receive_channel, AiUInt8 label, AiUInt8 sdi);


/*! \brief Get overview of received label activity
 *
 * This function reads the activity information of the RX labels for each channel.
 * Each time a label is received the corresponding bit of the activity bit field is set.
 * The activity bit field is reset, when stopping and restarting the RX channel.
 * @param [in] board_handle handle to board to read receive activity from
 * @param [out] pxActivity receive activity will be stored here
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RxActivityGet( AiUInt8 board_handle, struct api429_rx_activity *pxActivity);


/*! \brief Used to define data modifications in a receiver/transmitter data loop
 *
 * @param [in] board_handle handle to board
 * @param [in] b_Chn ID of receiver channel in a data loop set-up
 * @param [in] b_Label ID of label to install modification for
 * @param [in] b_Sdi SDI extension of label
 * @param [in] b_Con enable/disable modification
 * @param [in] px_PollBlk See \ref api429_rcv_pb_cmd
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RxPollutionConfigure( AiUInt8 board_handle, AiUInt8 b_Chn, AiUInt8 b_Label, AiUInt8 b_Sdi, AiUInt8 b_Con,
                                                               struct api429_rcv_pb_cmd  *px_PollBlk );


/*! \brief Configure reception of specific labels
 *
 * This function controls the specified receiver label handling on the selected Arinc
 * 429 receiver channel and allocates/releases a receive data buffer.
 * This function clears the Loop/Pollution blocks and the function blocks in the target
 * software.
 * @param [in] board_handle handle to board
 * @param [in] b_Chn ID of channel to configure label on
 * @param [in] label_setup See \ref api429_rx_label_setup
 * @param [out] puc_Status if 1, label buffer could not be allocated due to too little memory
 * @param [out] pul_FreeMem Size of the free memory available for label buffer
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RxLabelConfigure( AiUInt8 board_handle, AiUInt8 b_Chn, struct api429_rx_label_setup * label_setup,
                                                           AiUInt8 *puc_Status, AiUInt32 *pul_FreeMem );


/*! \brief Configure reception of multiple labels
 *
 * This function controls the specified receiver label handling on the selected Arinc
 * 429 receiver channel and allocates/releases a receive data buffer.
 * This function clears the Loop/Pollution blocks and the function blocks in the target
 * software.
 * @param [in] board_handle handle to board
 * @param [in] b_Chn ID of channel to configure label on
 * @param [in] ulCount number of labels to configure
 * @param [in] pxSetup Array of \ref api429_rx_label_setup instances. Must hold at least __ulCount__ entries
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RxMultiLabelConfigure(AiUInt8 board_handle, AiUInt8 b_Chn, AiUInt32 ulCount, struct api429_rx_label_setup  *pxSetup );


/*! \brief Writes data to a receive label buffer
 *
 * This function is utilized to fill the specified receiver label data buffer on the selected
 * Arinc 429 receiver channel with default data. This command can be used to clear
 * the data buffer after the receiver was stopped.
 * @param [in] board_handle handle to board the receive channel belongs to
 * @param [in] b_Chn ID of receive channel
 * @param [in] b_Label ID of label for which buffer shall be written
 * @param [in] b_Sdi SDI extension of label
 * @param [in] w_BufSize Amount of receive buffer entries to write to label receive buffer
 * @param [in] px_LData Array of pointer to Label Receive Buffer Data structure
 * @param [in] b_Clear if set to AiTrue, all data in the buffer will be cleared instead of using __px_LData__
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RxLabelBufferWrite( AiUInt8 board_handle, AiUInt8 b_Chn, AiUInt8 b_Label, AiUInt8 b_Sdi, AiUInt16 w_BufSize,
                                                             struct api429_rx_buf_entry  *px_LData, AiUInt8 b_Clear );


/*! \brief Get status of channel in receive mode
 *
 * This function is utilized to get the execution status of the selected Arinc 429
 * receiver channel and the global receive channel message/error count information.
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] b_Chn ID of receive channel to get status of
 * @param [out] b_RxStatus either API429_HALT or API429_BUSY
 * @param [out] px_MsgCnt Total number of received labels on the channel
 * @param [out] px_ErrCnt Total number of erroneous labels received on the channel
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RxStatusGet( AiUInt8 board_handle, AiUInt8 b_Chn, AiUInt8  *b_RxStatus, AiUInt32  *px_MsgCnt, AiUInt32  *px_ErrCnt );


/*! \brief Get receive status of a specific label on a specific channel
 *
 * This function is utilized to read the execution status of a specific label on the
 * selected Arinc 429 receiver channel.
 * @param [in] board_handle handle to board the receive channel belongs to
 * @param [in] b_Chn ID of receive channel
 * @param [in] b_Label ID of label to read status of
 * @param [in] b_Sdi SDI extension for label
 * @param [in] b_LabCntIni if set to 1, reset counters to zero after function returns
 * @param [out] pw_LabIx Receive Buffer Fill Index.
 * @param [out] px_LabCnt Number of times the label was received
 * @param [out] px_LabErr Number of times the label was erroneously detected
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RxLabelStatusGet( AiUInt8 board_handle, AiUInt8 b_Chn, AiUInt8 b_Label, AiUInt8 b_Sdi, AiUInt8 b_LabCntIni,
                                                           AiUInt16  *pw_LabIx, AiUInt32  *px_LabCnt, AiUInt32  *px_LabErr );


/*! \brief Read data from a specific label's receive buffer
 *
 * @param [in] board_handle handle to board the receive channel belongs to
 * @param [in] b_Chn ID of receive channel
 * @param [in] b_Label ID of label to read receive buffer data of
 * @param [in] b_Sdi SDI extension for label
 * @param [in] w_BufSize Label Receive Buffer Size It should correspond to "label receive buffer size" in the \ref Api429RxLabelConfigure function.
 * @param [out] px_Info Index information about the buffer. See \ref api429_rx_buf_ctl
 * @param [out] px_LData Array of data. See \ref api429_rx_buf_entry
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RxLabelBufferRead( AiUInt8 board_handle, AiUInt8 b_Chn, AiUInt8 b_Label, AiUInt8 b_Sdi, AiUInt16 w_BufSize,
                                                            struct api429_rx_buf_ctl  *px_Info, struct api429_rx_buf_entry  *px_LData );


/*! \brief Get offset of specific label receive buffer
 *
 * This function is utilized to return the offset of a specified label receiver buffer
 * in global memory.
 * @param [in] board_handle handle to board the receive channel belongs to
 * @param [in] b_Chn ID of receive channel
 * @param [in] b_Label ID of label to get receive buffer offset of
 * @param [in] b_Sdi SDI extension for label
 * @param [out] offset It is returned as a relative offset based on the start of the Global Memory.
 *               The offset points to the data buffer header (refer to the Hardware Manual of the Data Buffer Structure, if this command is used).
 * @param [out] w_Size Label Receiver Buffer Size
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429RxLabelBufferOffsetGet(AiUInt8 board_handle, AiUInt8 b_Chn, AiUInt8 b_Label, AiUInt8 b_Sdi,
                                                                AiUInt32* offset, AiUInt16* w_Size );



/** @} */



#endif /* API429RX_H_ */
