/******************************************************************************

           Copyright (c) AIM GmbH 2001, 79111 Freiburg, Germany.

            All rights reserved.  No part of this software may
            be published, distributed, translated or otherwise
            reproduced by any means or for any purpose without
            the prior written consent of AIM GmbH, Freiburg.

******************************************************************************/
/*! \file Api429TxFifo.h
 *
 *  This header file contains function declarations
 *  related to FIFO based transmit functionality
 *
 *  Created on: 09.02.2016
 *      Author: Markus Melcher
 */


#ifndef API429TXFIFO_H_
#define API429TXFIFO_H_


#include "Ai_cdef.h"
#include "Api429Tx.h"


/**
* \defgroup txfifo FIFO Based Transmitting
  This module contains functionality related to transmitting of Arinc 429
  data via a FIFO based mechanism.
* @{
*/



/*! \struct api429_tx_fifo_setup
 *
 * This structure comprises settings when generating a TX FIFO
 */
struct api429_tx_fifo_setup
{
    AiUInt32 ulFifoSize;       /*!< Size of FIFO in number of entries. The default value is 1024. */
    AiUInt32 ulFifoControl;    /*!< Bitfield defines Interrupt handling. The default value is 0. If bit zero is set a notification interrupt is sent when the FIFO gets empty. */
    AiUInt32 ulDefaultGapSize; /*!< Inter message gap size, with a valid range of 4..255. The default value is 4. */
};


/*! \typedef TY_API429_TX_FIFO_SETUP
 * Convenience typedef for \ref api429_tx_fifo_setup
 */
typedef struct api429_tx_fifo_setup TY_API429_TX_FIFO_SETUP;


/*! \struct api429_tx_fifo_status
 * This structure describes the current state of a TX FIFO
 */
struct api429_tx_fifo_status
{
    AiUInt32 ulEntriesToSend;   /*!< number of entries still in fifo */
    AiUInt32 ulEntriesFree ;    /*!< number of entries before fifo will be full */
};


/*! \typedef TY_API429_TX_FIFO_STATUS
 * Convenience typedef for \ref api429_tx_fifo_status
 */
typedef struct api429_tx_fifo_status TY_API429_TX_FIFO_STATUS;


/*! \struct api429_tx_fifo_entry
 *
 * This structure describes the generic TX FIFO entry format.
 * it is filled with functions like \ref Api429TxFifoDataWordCreate
 */
struct api429_tx_fifo_entry
{
    AiUInt32 ulControl;  /*!< control word*/
    AiUInt32 ulData;     /*!< data word */
};


/*! \typedef TY_API429_TX_FIFO_ENTRY
 * Convenience typedef for \ref api429_tx_fifo_entry
 */
typedef struct api429_tx_fifo_entry TY_API429_TX_FIFO_ENTRY;


/*! \brief This function allows to reset a FIFO

    This function clears the FIFO buffer and stops the FIFO handling. The FIFO\n
    handling can be started again with the command \ref Api429ChannelStart.
    \param [in] b_Module handle to the device
    \param [in] b_Chn ID of the channel that shall be affected
    \return 
        - API_OK on success
        - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxFifoReset( AiUInt8 b_Module, AiUInt8 b_Chn );


/*! \brief This function allows to set up a TX FIFO with different values than default

    A FIFO is automatically created if \ref Api429TxInit is called with mode API429_TX_MODE_FIFO.\n
    This function allows to set up a FIFO with other parameters than default. \n
    The data that was written into the FIFO with the command \ref Api429TxFifoDataWordsWrite\n
    or \ref Api429TxFifoWrite will be sent after the command \ref Api429ChannelStart\n
    is called or immediately in case the \ref Api429ChannelStart has already been called for\n
    starting the FIFO ("Tx already active").
    \param [in] b_Module handle to the device
    \param [in] b_Chn ID of the channel that shall be affected
    \param [in] pxFifoSetup pointer to a struct containg FIFO set up information
    \return 
        - API_OK on success
        - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxFifoSetup( AiUInt8 b_Module, AiUInt8 b_Chn,  struct api429_tx_fifo_setup* pxFifoSetup );


/*! \brief This function returns the current setup of a TX FIFO

The requested channel must be setup with API429_TX_MODE_FIFO before this function can be used.
\param [in] b_Module handle to the device the channel belongs to
\param [in] b_Chn ID of the channel the TX FIFO is used on
\param [out] fifo_setup pointer to \ref api429_tx_fifo_setup where current TX FIFO setup will be stored
\return
- API_OK on success
- Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
*/
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxFifoSetupGet(AiUInt8 b_Module, AiUInt8 b_Chn, struct api429_tx_fifo_setup* fifo_setup);


/*! This function provides some basic information about the FIFO buffer.
    \param [in] b_Module handle to the device
    \param [in] b_Chn channel that shall be affected
    \param [out] pxFifoStatus pointer to a struct containg FIFO status information
    \return 
        - API_OK on success
        - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxFifoStatusGet( AiUInt8 b_Module, AiUInt8 b_Chn, struct api429_tx_fifo_status* pxFifoStatus );


/*! \brief This function is used to write label transfer instructions to the FIFO

    This function writes label transfer instructions into the FIFO buffer. If the\n
    TX channel is started with \ref Api429ChannelStart before or after a call of this \n
    function, all FIFO buffer entries will be sent as soon as possible in accordance\n
    with the given default interlabel gap. It is recommended to Setup the FIFO and\n
    Start the TX channel only once to arm the FIFO so that data written to the FIFO\n
    via this function will be sent with minimum latency.
    \param [in] module_handle handle to the device
    \param [in] channel_id ID of the channel that shall be affected
    \param [in] num_words number of data words to send via FIFO
    \param [in] words array containing the arinc 429 data words that shall be sent via FIFO
    \param [in] block if set to \ref AiTrue, function call will block until all entries were written to FIFO. \n
                      If set to \ref AiFalse, function will just send the number of words that currently fit into FIFO.
    \param [out] words_written number of data words that were really written
    \return 
        - API_OK on success
        - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxFifoDataWordsWrite( AiUInt8 module_handle, AiUInt8 channel_id, AiUInt32 num_words, AiUInt32* words, AiBoolean block,
                                                              AiUInt32* words_written);


/*! \brief This function is used to write instructions to the FIFO

    This function writes instructions into the FIFO buffer. If the TX channel is \n
    started with \ref Api429ChannelStart before or after a call of this function, all \n
    FIFO buffer entries will be sent as soon as possible in accordance with the \n
    given interlabel gap (see layout of the FIFO entry). It is recommended to Setup\n
    the FIFO and Start the TX channel only once to arm the FIFO so that data written\n
    to the FIFO via this function will be sent with minimum latency.
    \param [in] module_handle handle to the device
    \param [in] channel_id ID of the channel that shall be affected
    \param [in] num_entries number of entries to write to FIFO
    \param [in] entries array containing FIFO entries
    \param [in] block block if set to \ref AiTrue, function call will block until all entries were written to FIFO. \n
                      If set to \ref AiFalse, function will just send the number of entries that currently fit into FIFO.
    \param [out] entries_written number of entries that were really written
    \return 
        - API_OK on success
        - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxFifoWrite( AiUInt8 module_handle, AiUInt8 channel_id, AiUInt32 num_entries, struct api429_tx_fifo_entry* entries,
                                                     AiBoolean block, AiUInt32 *entries_written );


/*! \brief Prepares a FIFO entry for sending one Arinc 429 data word
 *
 * This function can be used to set-up a specific FIFO entry for sending
 * of an Arinc429 data word. \n
 * The entry can be sent with \ref Api429TxFifoWrite afterwards. \n
 * @param [out] entry pointer to the TX FIFO entry to prepare
 * @param [in] data the actual data that will be sent on the bus.
 * @param [in] gap Gap time that will be inserted before sending of next word measured in Arinc 429 bits. The valid range for this parameter is 4..255.\n
 *            Note: values between 0 and 4 will result in a gap time of 4 bits to prevent violation of Arinc 429 specification
 * @param [in] error specifies an optional error type to inject with the word. See \ref api429_xfer_error
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxFifoDataWordCreate(struct api429_tx_fifo_entry* entry, AiUInt32 data, AiUInt32 gap,
                                                              enum api429_xfer_error error);


/*! \brief Prepares a FIFO entry for delaying the processing of a FIFO
 *
 * This function can be used to prepare a 'wait' FIFO entry. \n
 * The entry can be sent with \ref Api429TxFifoWrite afterwards. \n
 * When put into a TX FIFO it will delay processing of the FIFO for the specified amount of time.
 * @param [out] entry pointer to FIFO entry to prepare
 * @param [in] time_100_usec time to delay processing in 100 microsecond steps
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxFifoDelayCreate(struct api429_tx_fifo_entry* entry, AiUInt32 time_100_usec);


/*! \brief Prepares a FIFO entry for generating send notifications
 *
 * This function can be used to prepare an 'interrupt' FIFO entry. \n
 * The entry can be sent with \ref Api429TxFifoWrite afterwards. \n
 * When put into a TX FIFO it will issue an interrupt based notification that
 * can be monitored using \ref Api429ChannelCallbackRegister
 * @param [out] entry pointer to FIFO entry to prepare
 * @param [in] tag user definable identifier for the interrupt. May range from 0 to 255. Will be encoded in \ref api429_intr_loglist_entry
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxFifoInterruptCreate(struct api429_tx_fifo_entry* entry, AiUInt32 tag);


/*! \brief Prepares a FIFO entry for generating a pulse on an output trigger line
 *
 * This function can be used to prepare an 'output trigger' FIFO entry. \n
 * The entry can be sent with \ref Api429TxFifoWrite afterwards. \n
 * When put into a TX FIFO it will issue a pulse on the specified trigger line
 * @param [out] entry pointer to FIFO entry to prepare
 * @param [in] trigger_line output trigger line (0..3) to send pulse on
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxFifoTriggerPulseCreate(struct api429_tx_fifo_entry* entry, AiUInt32 trigger_line);


/*! \brief Prepares a FIFO entry for suspend FIFO processing until input trigger detected
 *
 * This function can be used to prepare a 'wait for input trigger' FIFO entry. \n
 * The entry can be sent with \ref Api429TxFifoWrite afterwards. \n
 * When put into a TX FIFO it will suspend FIFO processing until trigger on specified input line is detected
 * @param [out] entry pointer to FIFO entry to prepare
 * @param [in] input_trigger_line input trigger line (0..3) to wait for trigger event
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429TxFifoTriggerWaitCreate(struct api429_tx_fifo_entry* entry, AiUInt32 input_trigger_line);


/** @} */



#endif /* API429TXFIFO_H_ */
