/******************************************************************************

           Copyright (c) AIM GmbH 2001, 79111 Freiburg, Germany.                 
                                                                             
            All rights reserved.  No part of this software may                
            be published, distributed, translated or otherwise                
            reproduced by any means or for any purpose without                
            the prior written consent of AIM GmbH, Freiburg.                  

******************************************************************************/
/*! \file Api429Tx.h
 *
 *  This header file contains function declarations
 *  related to channel transmit functionality
 *  Created on: 24.02.2016
 *      Author: Jochen Pfaadt
 */
#ifndef API429TX_H_
#define API429TX_H_


#include "Ai_cdef.h"
#include "Api429Board.h"


/**
* \defgroup transmitting Data Transmitting
  This module contains functionality related to transmitting of Arinc 429
  data .
* @{
*/



/*! \enum api429_tx_mode
 *
 * Enumeration of all available transmission modes
 */
enum api429_tx_mode
{
    API429_TX_MODE_FRAMING = 0,     /*!< Standard framing mode */
    API429_TX_MODE_LOOP,            /*!< Channel is bound with a receiver channel forming a data loop. It will re-transmit all data words the receiver gets */
    API429_TX_MODE_PHYS_REPLAY,     /*!< Replay mode */
    API429_TX_MODE_FRAMING_DYNTAG,  /*!< Standard framing mode with dyntags */
    API429_TX_MODE_FIFO,            /*!< Fifo based transmission mode */
    API429_TX_MODE_RATE_CONTROLLED  /*!< Framing mode where data word transmission is controlled by specifying cyclic transmission rates */
};

/*! \typedef TY_E_API429_TX_MODE
 * Convenience macro for \ref api429_tx_mode
 */
typedef enum api429_tx_mode TY_E_API429_TX_MODE;


/*! \enum api429_xfer_type
 *
 * Enumeration of all available transfer types
 * for use with framing/rate-oriented based transmitter channels
 */
enum api429_xfer_type
{
    API429_TX_LAB_XFER = 1,      /*!< Label Transfer */
    API429_TX_NOP_XFER,          /*!< NOP Transfer */
    API429_TX_STROBE,            /*!< Trigger Strobe */
    API429_TX_DELAY,             /*!< Delay Instruction */
    API429_TX_LAB_XFER_TT,       /*!< Label Transfer with TimeTag */
    API429_TX_EXT_TRIGGER,       /*!< Wait for external trigger */
    API429_TX_LAB_XFER_32,       /*!< 32Bit Label Transfer */
    API429_TX_LAB_XFER_TT_32,    /*!< 32Bit Label Transfer with TimeTag */
};


/*! \typedef TY_E_API429_XFER_TYPE
 * Convenience typedef for \ref api429_xfer_type
 */
typedef enum api429_xfer_type TY_E_API429_XFER_TYPE;


/*! \enum api429_xfer_error
 * Enumeration of all available error types
 * that can be injected for a transfer
 */
enum api429_xfer_error
{
    API429_XFER_ERR_DIS = 0,     /*!< No error */
    API429_XFER_ERR_BCH,         /*!< Bit count high error */
    API429_XFER_ERR_BCL,         /*!< Bit count low error */
    API429_XFER_ERR_COD,         /*!< Coding error */
    API429_XFER_ERR_PAR,         /*!< Parity error */
    API429_XFER_ERR_GAP,         /*!< Gap error */
    API429_XFER_ERR_WAIT         /*!< Error wait. Don't send frame */
};

/*! \typedef TY_E_API429_XFER_ERROR
 * Convenience macro for \ref api429_xfer_error
 */
typedef enum api429_xfer_error TY_E_API429_XFER_ERROR;


/*! \struct api429_xfer
 * This structure describes a transfer set-up
 * for framing/rate-controlled based transmit channels
 */
struct api429_xfer
{
    AiUInt32 xfer_id;                     /*!< Transfer Identifier. Not the label ID!!!   Each transfer must be created with an ID unique to this channel, ranging from __1__ to __1023__*/
    enum api429_xfer_type  xfer_type;     /*!< Transfer Type. See \ref api429_xfer_type */
    enum api429_xfer_error err_type;      /*!< Error type. See \ref api429_xfer_error */
    AiUInt16 xfer_gap;                    /*!< Label Transfer Gap \n
                                               <table>
                                                  <tr><th align="center">Transfer Type <th align="center"> Range <th align="center"> Description
                                                  <tr><td align="center">1,8 <td align="center"> 4..255 <td align="center"> ARINC bits
                                                  <tr><td align="center">2 <td align="center"> 0 <td align="center"> Reserved
                                                  <tr><td align="center">4 <td align="center"> 0..3 <td align="center"> Output trigger line
                                                  <tr><td align="center">7 <td align="center"> 0..255 <td align="center"> Amount of 100us steps to wait
                                                  <tr><td align="center">9 <td align="center"> 0..3 <td align="center"> Input Trigger Line
                                               </table> */
    AiUInt16 ir_index;                    /*!< Transfer Interrupt Index. Range from 1 to 1023 */
    AiUInt16 buf_size;                    /*!< Label data buffer size. Range from 1 to 1023 */
    AiUInt8  xfer_ir;                     /*!<  Interrupt settings \n
                                                   <table>
                                                     <tr><th align="center">Bit Position <th align="center"> Description
                                                     <tr><td align="center">0    <td align="center"> Interrupt on Label transfer or NOP execution
                                                     <tr><td align="center">1    <td align="center"> Interrupt when transfer interrupt index reached and on Buffer index reload
                                                   </table> */
};


/*! \typedef TY_API429_XFER
 * Convenience typedef for \ref api429_xfer
 */
typedef struct api429_xfer TY_API429_XFER;


/*! \struct api429_xfer_out
 *
 * This structure comprises output parameters
 * when transfer is created
 */
struct api429_xfer_out
{
  AiUInt32  ul_Status;          /*!< If 0: Label buffer has been allocated. If 1: Label buffer could not be allocated due to too little memory */
  AiUInt32  ul_FreeMem;         /*!< Size of the free memory available for label buffer */
  AiUInt32  ul_XferDescAddr;    /*!< Address of the transfer descriptor, relative to the start of global memory. */
};


/*! \typedef TY_API429_XFER_OUT
 * Convenience typedef for struct api429_xfer_out
 */
typedef struct api429_xfer_out TY_API429_XFER_OUT;


/*! \struct api429_lxfer_dyntag
 *
 * This structure comprises settings
 * for assigning dynamic data modification to a transfer
 */
struct api429_lxfer_dyntag
{
    AiUInt32 ul_Mode;        /*!< Specifies the function to be called.
                                  <table>
                                    <tr><th align="center">Value<th align="center">Description
                                    <tr><td align="center">0<td align="center">No dynamic operation
                                    <tr><td align="center">1<td align="center">Positive Ramp
                                    <tr><td align="center">2<td align="center">Negative ramp
                                  </table> */
    AiUInt32 ul_LowerLimit;  /*!< The lower limit of the function */
    AiUInt32 ul_UpperLimit;  /*!< The upper limit of the function */
    AiUInt32 ul_StepSize;    /*!< The value that is added to the value after each transmission */
    AiUInt32 ul_Mask;        /*!< A bit mask that specifies which bits shall be modified by the dynamic modification. */
    AiUInt32 ul_StartValue;  /*!< The initial value of the buffer. It can be overwritten using direct memory access or using the
                                  Api429TxXferBufferWrite at any time. */
};


/*! \typedef TY_API429_LXFER_DYNTAG
 * Convenience typedef for \ref api429_lxfer_dyntag
 */
typedef struct api429_lxfer_dyntag TY_API429_LXFER_DYNTAG;


/*! \struct api429_xfer_data
 *
 * This structure comprises properties
 * of a specific transfer
 */
struct api429_xfer_data
{
  AiUInt32  ul_XferData;   /*!< Transfer data word */
  AiUInt32  ul_XferTTHigh; /*!< Time tag high word of the current sent TX label transfer TODO: Document it */
  AiUInt32  ul_XferTTLow;  /*!< Time tag low word of the current sent TX label transfer TODO: Document it */
};


/*! \typedef TY_API429_XFER_DATA
 * Convenience typedef for \ref api429_xfer_data
 */
typedef struct api429_xfer_data TY_API429_XFER_DATA;


/*! \struct api429_xfer_info
 * Comprises information about send status of a transfer
 */
struct api429_xfer_info
{
  AiUInt32  ul_XferIx;      /*!< Current Label transmit buffer index */
  AiUInt32  ul_XferCnt;     /*!< Number of times the transfer was sent */
  AiUInt32  ul_XferData;    /*!< Last sent data word */
  AiUInt32  ul_XferTTHigh;  /*!< Time tag high word of the current sent TX label transfer */
  AiUInt32  ul_XferTTLow;   /*!< Time tag low word of the current sent TX label transfer */
};


/*! \typedef TY_API429_XFER_INFO
 * Convenience typedef for \ref api429_xfer_info
 */
typedef struct api429_xfer_info TY_API429_XFER_INFO;


/*! \struct api429_xfer_data_read_input
 *
 * This structure comprises the input parameters for \ref Api429TxXferBufferRead
 */
struct api429_xfer_data_read_input
{
  AiUInt32  ul_XferId;      /*!< ID of transfer to read data from */
  AiUInt32  ul_BufStart;    /*!< Buffer index to start reading from */
  AiUInt32  ul_BufSize;     /*!< Amount of data words to read from label transmit buffer. */
  AiUInt32  ul_Mode;        /*!< If 0: no action. If API_TXRXBUF_TT_UPDATE_CLEAR : Clear update flag in TT High word after reading the data */
};


/*! \typedef TY_API429_XFER_DATA_READ_INPUT
 * Convenience typedef for \ref api429_xfer_data_read_input
 */
typedef struct api429_xfer_data_read_input TY_API429_XFER_DATA_READ_INPUT;


/*! \struct api429_mframe_in
 * Comprises the input parameters for
 * the \ref Api429TxMinorFrameCreate function
 */
struct api429_mframe_in
{
  AiUInt32  ul_FrmId;       /*!< Frame Identifier. Ranges from 0..1203 */
  AiUInt32  ul_XferCnt;     /*!< Amount of transfers in frame. Ranges from 1..2000 */
  AiUInt32  *pul_Xfers;     /*!< Transfer Identifiers of the Transfers called within the minor frame (up to 2000, see 'ul_XferCnt') */
};


/*! \typedef TY_API429_MFRAME_IN
 * Convenience typedef for \ref api429_mframe_in
 */
typedef struct api429_mframe_in TY_API429_MFRAME_IN;


/*! \struct api429_mframe_out
 * Comprises the output parameters for
 * the \ref Api429TxMinorFrameCreate function
 */
struct api429_mframe_out
{
  AiUInt32  ul_MFrameAddr; /*!< Byte offset of the minor frame in global memory */
};


/*! \typedef TY_API429_MFRAME_OUT
 * Convenience typedef \ref api429_mframe_out
 */
typedef struct api429_mframe_out TY_API429_MFRAME_OUT;



/*! \brief Initialize specific channel for data transmission
 *
 * This command initializes the transmitter mode of the selected Arinc 429 transmitter
 * channel. The transmitter operation is halted, the high and low priority stack pointer
 * are initialized and the channel amplitude and the minor frame time are set to the
 * following default values:
 * -Amplitude : 10 Volts (line to line)
 * -Minor Frame Time : 100ms
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] channel_id ID of channel to initialize
 * @param [in] mode See \ref api429_tx_mode
 * @param [in] auto_parity If AiTrue, parity bit will automatically be generated for transmitted data word. (Not applicable in __Replay__ or __Loop__ mode)
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxInit( AiUInt8 board_handle, AiUInt8 channel_id, enum api429_tx_mode mode, AiBoolean auto_parity );


/*! \brief Set transmission amplitude
 *
 * This command defines the output amplitude of the selected Arinc 429 transmitter
 * channel via a D/A converter.
 *
 * The transmitter output amplitude can be changed on the lower 8 channels of
 * an APX, APXX, ACX429, ACXX, ACE and APE429.
 * For other modules (and all modules with 32 channels) this function has no effect!
 * Please have a look into the corresponding data sheet for details.
 *
 * Note: After a \ref Api429BoardReset command or the \ref Api429TxInit command the
 * related D/A converter is loaded to an output voltage of 9.0 Volt (line to line).
 *
 * Note: for APX429 and ACX429-3U boards there might be a short delay, before the
 * output amplitude is adjusted
 *
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] b_Chn ID of channel to set amplitude for
 * @param [in] fAmplitude Amplitude Control. The internal D/A converter will be set, so that the output
 *                   amplitude comes as near as possible to this value.
 *                   The typical range is 0V .. 11V. Please refer to the Hardware Manual for details.
 * @param [out] pfCalcAmpl mirrors the input parameter fAmplitude. It was used before to show the digitization error. But it gave a false
 *                   impression of accuracy, which neglected the variation of the components and the variation of the supply voltage. This
 *                   parameter is no longer needed, but for compatibility reasons it is still kept.
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxAmplitudeSet( AiUInt8 board_handle, AiUInt8 b_Chn, AiFloat fAmplitude, AiFloat *pfCalcAmpl );



/*! \brief Get Status of a transmitter channel
 *
 * This function is utilized to read the execution status of the selected Arinc 429
 * transmitter channel.
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] b_Chn ID of channel to get status of
 * @param [out] pb_TxStatus Either API429_HALT or API429_BUSY
 * @param [out] pl_GlbCnt Global transfer count
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxStatusGet( AiUInt8 board_handle, AiUInt8 b_Chn, AiUInt8  *pb_TxStatus, AiUInt32  *pl_GlbCnt);


/*! \brief This function starts a transmit channel on at a given point of time

    This function starts the execution of the label transfers on the selected 
    Arinc 429 transmitter channel at a given point of time. Every 500us the 
    current IRIG Time is compared with the values provided by this command.
    If it has passed the given time tag, it starts the transmit channel.
    Note: This command is only supported for AyX429 boards
    \param [in] board_handle handle to the device
    \param [in] channel ID of the channel that shall be affected
    \param [in] start_ttag the point of time the transmission shall start.
    \return 
        - API_OK on success
        - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
*/
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxStartOnTTag( AiUInt8 board_handle, AiUInt8 channel, struct api429_time *start_ttag);


/*! \brief This function starts a transmit channel on at a given point of time

    This function starts the execution of the label transfers on the selected Arinc 429
    transmitter channel when a strobe is detected at the given trigger line
    \param [in] board_handle handle to the device
    \param [in] channel ID of the channel that shall be affected
    \param [in] trigger_line ID of the trigger input line (0..3)
    \return 
        - API_OK on success
        - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
*/
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxStartOnTrigger(AiUInt8 board_handle, AiUInt8 channel, AiUInt32 trigger_line);


/*! \brief Creates an acyclic frame
 *
 * This function searches for an unused minor frame ID, returns it and defines
 * the sequence of label transfers identified by their transfer identifiers 
 * within a frame that may be used for an acyclic. Several acyclic frames may 
 * be used in parallel.
 * @param [in] board_handle handle to the device the channel belongs to
 * @param [in] ucChannel ID of the channel to initialize
 * @param [in] ulXferCnt number of transfers that shall be sent with this frame
 * @param [in] pulXfers array containing a list of transfers that shall be sent with this frame
 * @param [out] pulFrameId ID of acyclic frame that was created with this command
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxAcycFrameCreate(AiUInt8 board_handle, AiUInt8 ucChannel, AiUInt32 ulXferCnt, AiUInt32 *pulXfers, AiUInt32 *pulFrameId);

/*! \brief Deletes an acyclic frame
 *
 * This function removes an acyclic frame that was previously created with 
 * the command \ref Api429TxAcycFrameCreate.
 * @param [in] board_handle handle to the device the channel belongs to
 * @param [in] ucChannel ID of the channel to initialize
 * @param [in] ulFrameId ID of acyclic frame
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxAcycFrameDelete(AiUInt8 board_handle, AiUInt8 ucChannel, AiUInt32 ulFrameId);


/*! \brief Sends an acyclic frame
 *
 * This function causes the board to immediately send an acyclic frame
 * (created with the command \ref Api429TxAcycFrameCreate). If an ARINC 429 word
 * is currently being sent, the acyclic frame is sent directly after it. This
 * may interrupt the current minor frame.
 * To ensure the acyclic frames do not disturb the standard framing, please 
 * make sure the minor frame time is high enough. 
 * This function returns immediately and does not wait for the acyclic frame
 * to finish. It is not recommended to issue this command to the board before
 * the previous acyclic frame was completely sent.
 * @param [in] board_handle handle to the device the channel belongs to
 * @param [in] ucChannel ID of the channel to initialize
 * @param [in] ulFrameId ID of acyclic frame
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxAcycFrameSend( AiUInt8 board_handle, AiUInt8 ucChannel, AiUInt32 ulFrameId );


/*! \brief Defines how many times the major frame shall be sent
 *
 * This command defines the number of times the major frame shall be sent. By
 * setting the parameter count to zero, the major frame is sent indefinitely,
 * until explicitely stopped. This is the default value with which the channel
 * is initialized.
 * @param [in] board_handle handle to the device the channel belongs to
 * @param [in] channel ID of the channel to initialize
 * @param [in] count Number of times a major frame shall be sent. If set to 0 the major frame is sent until stopped. Valid range is 0..65535
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxRepetitionCountSet( AiUInt8 board_handle, AiUInt8 channel, AiUInt32 count );



/*! \brief This function adds a transfer to the framing

    This function adds a transfer which was set up with \ref Api429TxXferCreate to \n
    a list from which a framing is automatically generated when starting the TX \n
    channel with \ref Api429ChannelStart.
    \param [in] board_handle handle to the device
    \param [in] ucChannel channel for which this frame shall be created
    \param [in] ulXferId ID of the transfer that shall be added to the framing
    \param [in] ulRateInMs rate with which this transfer shall appear in the framing
    \return 
        - API_OK on success
        - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
*/
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxXferRateAdd( AiUInt8 board_handle, AiUInt8 ucChannel, AiUInt32 ulXferId, AiUInt32 ulRateInMs );



/*! \brief This function removes a transfer from the framing

    This function removes a transfer from the internal list that is used to automatically \n
    create the framing when calling \ref Api429ChannelStart.
    \param [in] board_handle handle to the device
    \param [in] ucChannel channel for which this frame shall be created
    \param [in] ulXferId ID of the transfer that shall be added to the framing
    \return 
        - API_OK on success
        - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
*/
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxXferRateRemove( AiUInt8 board_handle, AiUInt8 ucChannel, AiUInt32 ulXferId );

/*! \brief This function shows the actual rate of a transfer

    This function shows the rate that is really used in the automatically generated framing \n
    for a given transfer. If the rate paremeters of some \ref Api429TxXferRateAdd commands are \n
    unfavourable, it may result in some rounding deviations.
    \param [in] board_handle handle to the device
    \param [in] ucChannel channel for which this frame shall be created
    \param [in] ulXferId ID of the transfer that shall be added to the framing
    \param [out] pulRateInMs rate with which this transfer really appears in the framing
    \return 
        - API_OK on success
        - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
*/
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxXferRateShow( AiUInt8 board_handle, AiUInt8 ucChannel, AiUInt32 ulXferId, AiUInt32 *pulRateInMs );



/*! \brief This function calculates the framing

    This function calculates a framing with the given transfers and rates, so that
    the channel can be started later without any delay. Calling this function is optional.
    \param [in] board_handle handle to the device
    \param [in] channel channel for which this frame shall be created
    \return 
        - API_OK on success
        - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
*/
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxPrepareFraming( AiUInt8 board_handle, AiUInt8 channel );


/*! \brief Set minor frame time for framing based transmit channel
 *
 * This command defines the minor frame time of the selected Arinc 429 transmitter
 * channel in 1ms steps.
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] b_Chn ID of channel to set frame time for
 * @param [in] w_Ftm Minor Frame Time in 1ms steps. Ranges from 1..65535
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxFrameTimeSet ( AiUInt8 board_handle, AiUInt8 b_Chn, AiUInt16 w_Ftm );


/*! \brief Create a transfer instruction for framing based transmitter channels
 *
 * This function defines a complete transmitter label transfer including error injection
 * specification to be executed on the selected Arinc 429 transmitter channel. When
 * executing this instruction a data buffer specified by "buf_size" is allocated within the
 * on-board memory. The data buffer contents may be defined with the
 * \ref Api429TxXferBufferWrite command.
 * Whenever a transfer is called (for example within a minor frame) a single ARINC429 data word of the buffer is being sent.
 * The allocated buffer can be freed using the \ref Api429TxXferDelete command.
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] b_Chn ID of transmitter channel to create transfer for
 * @param [in] px_Xfer See \ref api429_xfer
 * @param [out] px_XferInfo See \ref api429_xfer_out
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxXferCreate( AiUInt8 board_handle, AiUInt8 b_Chn, struct api429_xfer *px_Xfer, struct api429_xfer_out *px_XferInfo );


/*! \brief Assign automatic, dynamic data modification to transfers
 *
 * This function defines dynamic data modification for a given label transfer, that was already set up
 * with the \ref Api429TxXferCreate command. This command requires that the
 * channel was set up with \ref Api429TxInit with mode \ref API429_TX_MODE_FRAMING_DYNTAG.
 * After each transmission the buffer entry is modified according to the function
 * specified with the parameter ul_Mode.
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] b_Chn ID of channel the transfer was set up for
 * @param [in] ul_XferId ID of transfer to assign dynamic data modification for
 * @param [in] px_Dyntag See \ref api429_lxfer_dyntag
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxXferDyntagAssign( AiUInt8 board_handle, AiUInt8 b_Chn, AiUInt32 ul_XferId, struct api429_lxfer_dyntag *px_Dyntag );


/*! \brief Write data to a transfer buffer
 *
 * This function is utilized to fill the specified label transfer data buffer on the selected
 * Arinc 429 transmitter channel with data information.
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] b_Chn ID of channel the transfer was created for
 * @param [in] ul_XferId ID of transfer to which buffer shall be written
 * @param [in] w_BufStart Buffer index to start writing to. Ranges from 1..1023
 * @param [in] w_BufSize Amount of 32 bit label data words to write to transmit buffer.
 * @param [in] pl_LData Array of data words to write. The lowest byte of each data word is the label id. To meet the ARINC 429 specification the label id is automatically transferred in reverse bit order.
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxXferBufferWrite( AiUInt8 board_handle, AiUInt8 b_Chn, AiUInt32 ul_XferId,
                                                            AiUInt16 w_BufStart, AiUInt16 w_BufSize, AiUInt32  *pl_LData );


/*! \brief Read data from a transfer buffer
 *
 * This function is utilized to read the send label transfer data buffer on the selected
 * Arinc 429 transmitter channel.
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] b_Chn ID of channel the transfer was et-up on
 * @param [in] px_XferDataInput See \ref api429_xfer_data_read_input
 * @param [out] px_XferData See \ref api429_xfer_data
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxXferBufferRead( AiUInt8 board_handle, AiUInt8 b_Chn,
                                                           struct api429_xfer_data_read_input *px_XferDataInput, struct api429_xfer_data *px_XferData );


/*! \brief Create a minor frame on framing based transmit channels
 *
 * This function defines the sequence of label transfers identified by their transfer
 * identifiers within a minor frame specified by a frame identifier on the selected Arinc
 * 429 transmitter channel.
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] b_Chn ID of transmit channel
 * @param [in] px_MFrame See \ref api429_mframe_in
 * @param [out] px_MFrameInfo See \ref api429_mframe_out
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxMinorFrameCreate( AiUInt8 board_handle, AiUInt8 b_Chn,
                                                             struct api429_mframe_in *px_MFrame,
                                                             struct api429_mframe_out *px_MFrameInfo);


/*! \brief Create a major frame on framing based transmit channel
 *
 * This function defines the sequence of label transfer minor frames identified by their
 * frame identifiers within the major frame on the selected A429 transmitter channel.
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] b_Chn ID of channel to install major frame on
 * @param [in] ul_FrmCnt Amount of minor frames in major frame. Ranges from 1..2000
 * @param [in] pul_Frames Minor frame identifiers to add to major frame (up to 2000, see 'ul_FrmCnt')
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxMajorFrameCreate ( AiUInt8 board_handle, AiUInt8 b_Chn, AiUInt32 ul_FrmCnt, AiUInt32 *pul_Frames );


/*! \brief Delete a transfer instruction
 *
 * This function deletes the transmitter label transfer identified by its transfer identifier
 * on the selected Arinc 429 channel
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] b_Chn ID of channel the transfer was created on
 * @param [in] ul_XferId ID of transfer to delete
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxXferDelete( AiUInt8 board_handle, AiUInt8 b_Chn, AiUInt32 ul_XferId );


/*! \brief Allows to skip transmission of specific transfers on-th-fly
 *
 * This function enables/disables a label transfer identified by its transfer identifier.
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] b_Chn ID of channel the transfer was set-up on
 * @param [in] skip If AiTrue, transfer is skipped, if AiFalse it will sent
 * @param [in] ul_XferId ID of transfer to skip
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxXferSkip( AiUInt8 board_handle, AiUInt8 b_Chn, AiBoolean skip, AiUInt32 ul_XferId );


/*! \brief Deletes a minor frame from framing based transmit channel
 *
 * This function deletes the transmitter label transfer minor frame specified by its
 * frame identifier on the selected Arinc 429 channel.
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] b_Chn ID of transmit channel to delete minor frame from
 * @param [in] ul_FrmId ID of frame to delete
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxMinorFrameDelete( AiUInt8 board_handle, AiUInt8 b_Chn, AiUInt32 ul_FrmId );


/*! \brief Deletes a major frame from framing based transmit channel
 *
 * This function resets the minor frame sequence within the major frame on the
 * selected Arinc 429 transmitter channel.
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] b_Chn ID of transmit channel to delete major frame from
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxMajorFrameDelete( AiUInt8 board_handle, AiUInt8 b_Chn );


/*! \brief Get transmission status of a specific transfer
 *
 * This function is utilized to get the status of a specific label transfer on the selected
 * Arinc 429 transmitter channel including time tag information (if setup with
 * \ref Api429TxXferCreate)
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] b_Chn ID of channel the transfer was set-up for
 * @param [in] b_XferId ID of transfer to get status of
 * @param [out] px_XferInfo See \ref api429_xfer_info
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxXferStatusGet( AiUInt8 board_handle, AiUInt8 b_Chn, AiUInt32 b_XferId, struct api429_xfer_info  *px_XferInfo );


/*! \brief Get base offset of transfer buffer
 *
 * This function is utilized to return the base offset of a specified label transmitter
 * identified buffer and a specified channel.
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] b_Chn ID of channel the transfer was set-up on
 * @param [in] ul_XferId ID of transfer to get buffer offset of
 * @param [out] pl_Addr Transmit Buffer offset
 * @param [out] pw_Size Transmit Buffer Size
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxXferBufferOffsetGet( AiUInt8 board_handle, AiUInt8 b_Chn, AiUInt32 ul_XferId, AiUInt32 *pl_Addr, AiUInt16 *pw_Size );



/** @} */




#endif
