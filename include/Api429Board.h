/******************************************************************************

           Copyright (c) AIM GmbH 2001, 79111 Freiburg, Germany.                 
                                                                             
            All rights reserved.  No part of this software may                
            be published, distributed, translated or otherwise                
            reproduced by any means or for any purpose without                
            the prior written consent of AIM GmbH, Freiburg.                  

******************************************************************************/
/*! \file Api429Board.h
 *
 *  This header file contains API declarations
 *  that are related to Arinc429 boards.
 *
 *  Created on: 26.01.2016
 *      Author: Markus Melcher
 */

#ifndef API429BOARD_H_
#define API429BOARD_H_


#include "Ai_cdef.h"
#include "Ai_def.h"


/**
* \defgroup board Board Related Functions
This module contains functionality related to AIM Arinc 429 board handling
* @{
*/




/*! \def API429_MAX_BOARDNAME_LEN
 *
 * Maximum length of board names in number of single-byte characters
 */
#define API429_MAX_BOARDNAME_LEN    32


/*! \def API429_MAX_URL_LEN
 *
 * Maximum length of server URLs in number of single byte characters
 */
#define API429_MAX_URL_LEN  128


/*! \def API429_MAX_OS_INFO_LEN
*
* Maximum length of Operating System information in number of single byte characters
*/
#define API429_MAX_OS_INFO_LEN 128


/*! \def API429_BOARD_CAP_PXI_TRG_FLAG
 *
 * Flag used in \ref api429_board_info capability flags \n
 * which indicates if a board supports PXI trigger functionality
 */
#define API429_BOARD_CAP_PXI_TRG_FLAG    (1 << 0)

/*! \def MAX_API429_BIU
 *
 * maximum number of BIU's on PCI board
 */
#define MAX_API429_BIU     2

/*! \def MAX_API429_BIU_CHN
 *
 * maximum number of channels on BIU's on PCI board
 */
#define MAX_API429_BIU_CHN 16


/*! \def API429_MAX_CHANNELS
 *
 *  Maximum number of channels for an Arinc 429 board
 */
#define API429_MAX_CHANNELS     (MAX_API429_BIU*MAX_API429_BIU_CHN)


/*! \def API429_BOARD_HAS_PXI_TRIGGER
 *
 * Takes a pointer to \ref api429_board_info and extracts the PXI trigger capability from it. \n
 * Will return AiTrue if board has PXI triggers, AiFalse if not
 */
#define API429_BOARD_HAS_PXI_TRIGGER(board_info)    \
    (board_info)->capability_flags & API429_BOARD_CAP_PXI_TRG_FLAG ? AiTrue : AiFalse


/*! \enum api429_board_id
    Enumeration of all board IDs that are supported by the API.
*/
enum api429_board_id
{
    API429_BOARD_1 = 0, /*!< First board detected by API */
    API429_BOARD_2,     /*!< Second board detected by API */
    API429_BOARD_3,     /*!< Third board detected by API */   
    API429_BOARD_4,     /*!< 4th board detected by API */    
    API429_BOARD_5,     /*!< 5th board detected by API */
    API429_BOARD_6,     /*!< 6th board detected by API */ 
    API429_BOARD_7,     /*!< 7th board detected by API */
    API429_BOARD_8,     /*!< 8th board detected by API */
    API429_BOARD_9,     /*!< 9th board detected by API */
    API429_BOARD_10,    /*!< 10th board detected by API */
    API429_BOARD_11,    /*!< 11th board detected by API */
    API429_BOARD_12,    /*!< 12th board detected by API */
    API429_BOARD_13,    /*!< 13th board detected by API */
    API429_BOARD_14,    /*!< 14th board detected by API */
    API429_BOARD_15,    /*!< 15th board detected by API */
    API429_BOARD_16,    /*!< 16th board detected by API */
    API429_BOARD_17,    /*!< 17th board detected by API */
    API429_BOARD_18,    /*!< 18th board detected by API */
    API429_BOARD_19,    /*!< 19th board detected by API */
    API429_BOARD_20,    /*!< 20th board detected by API */
    API429_BOARD_21,    /*!< 21st board detected by API */
    API429_BOARD_22,    /*!< 22nd board detected by API */
    API429_BOARD_23,    /*!< 23rd board detected by API */
    API429_BOARD_24,    /*!< 24th board detected by API */
    API429_BOARD_25,    /*!< 25th board detected by API */
    API429_BOARD_26,    /*!< 26th board detected by API */
    API429_BOARD_27,    /*!< 27th board detected by API */
    API429_BOARD_28,    /*!< 28th board detected by API */
    API429_BOARD_29,    /*!< 29th board detected by API */
    API429_BOARD_30,    /*!< 30th board detected by API */
    API429_BOARD_31,    /*!< 31st board detected by API */
    API429_BOARD_32     /*!< 32nd board detected by API */
};


/*! \enum api429_pxi_trigger_line
 *
 * Enumeration of all possible Arinc 429 pxi trigger line (as source or destination)
 */
enum api429_pxi_trigger_line
{
    API429_TRG_PXI0 = 0,  //!< PXI Trigger Line 0
    API429_TRG_PXI1,  //!< PXI Trigger Line 1
    API429_TRG_PXI2,  //!< PXI Trigger Line 2
    API429_TRG_PXI3,  //!< PXI Trigger Line 3
    API429_TRG_PXI4,  //!< PXI Trigger Line 4
    API429_TRG_PXI5,  //!< PXI Trigger Line 5
    API429_TRG_PXI6,  //!< PXI Trigger Line 6
    API429_TRG_PXI7,  //!< PXI Trigger Line 7
    API429_TRG_PBI429  //!< Onboard Trigger
};


/*! \enum api429_pxi_mode
 *
 * Enumeration of all possible Arinc 429 pxi trigger sources
 */
enum api429_pxi_mode
{
    API429_PXI_SET_TRG = 0,  //!< Define a new Trigger combination using trigger source and destination given in parameters 'ul_TrgSource' and 'ul_TrgDest'
    API429_PXI_CLR_TRG,  //!< Clear all previously defined trigger combinations
    API429_PXI_SET_TTSRC_BACKPLANE,  //!< The external 10MHz PXI-Reference Clock from the PXI-Rack Backplane is used for Time Tagging
    API429_PXI_SET_TTSRC_FRONT  //!< The external 1KHz analog IRIG-B input signal via Frontpanel-I/O is used for Time Tagging.
};


/*! \struct api429_time
 *
 * This structure describes a specific time point,
 * as it can be handled by Arinc 429 boards
 */
struct api429_time
{
    AiUInt32 day;           /*!< Day of year. Starting with 1 */
    AiUInt32 hour;          /*!< Hour */
    AiUInt32 minute;        /*!< Minute */
    AiUInt32 second;        /*!< Second */
    AiUInt32 millisecond;   /*!< Milliseconds */
};


/*! \typedef TY_API429_TIME
 * Convenience typedef for \ref api429_time
 */
typedef struct api429_time TY_API429_TIME;





/*! \struct api429_board_info
 *
 * This struct is used as output parameter in \ref Api429BoardInfoGet
 */
struct api429_board_info
{
    AiUInt32 serial;                            /*!< serial number of board */
    AiUInt32 num_channels;                      /*!< number of Arinc429 channels the board offers */
    AiUInt32 num_trigger_out;                   /*!< number of output trigger lines the board offers */
    AiUInt32 num_trigger_in;                    /*!< number of input trigger lines the board offers */
    AiUInt32 capability_flags;                  /*!< Special board capability flags. Bit0 indicates if a board has PXI trigger lines */
	AiChar name[API429_MAX_BOARDNAME_LEN + 1];  /*!< Name of the board */
	AiChar server_url[API429_MAX_URL_LEN + 1];  /*!< Server address the board is located on. 'local' for local boards */
};

/*! \struct api429_remote_server
 *
 * struct containing information of a remote server for AIM Arinc 429 devices
 */
struct api429_remote_server
{
    AiChar host_name[API429_MAX_URL_LEN + 1];    /*!< Name of the remote server*/
    AiChar os_info[API429_MAX_OS_INFO_LEN + 1];  /*!< Description of the server's operating system */
    TY_VER_INFO server_version;                  /*!< Version of the server application. */
    AiUInt32 protocol_major;                     /*!< Major number of network protocol used for communication between remote server and local host */
    AiUInt32 protocol_minor;                     /*!< Minor number of network protocol used for communication between remote server and local host */
};


/*! \typedef TY_API429_BOARD_INFO
 * Convenience typedef for \ref api429_board_info
 */
typedef struct api429_board_info TY_API429_BOARD_INFO;


/*! \enum api429_low_speed_grade
 *
 * Enumeration of all possible Arinc 429 low-speed gradations.
 * Used as input parameter for \ref Api429BoardLsGradeSet
 */
enum api429_low_speed_grade
{
    API429_LS_GRADE_12_50 = 0,  //!< Default Arinc 429 Low-speed grade of 12,5 kBit/s
    API429_LS_GRADE_13_33       //!< Intermediate Arinc 429 Low-Speed grade of 13,33 kBit/s
};

/*! \typedef TY_E_API429_LOW_SPEED_GRADE
 * Convenience typedef for \ref api429_low_speed_grade
 */
typedef enum api429_low_speed_grade TY_E_API429_LOW_SPEED_GRADE;


/*! \enum api429_speed_modifier
 *
 * Enumeration of all supported Arinc 429 bus speed modifications.
 * Used as input parameter in \ref Api429BoardSpeedModifierSet.
 */
enum api429_speed_modifier
{
    API429_SPEED_MOD_NORMAL = 0,   //!< Normal Arinc 429 bus speed
    API429_SPEED_MOD_INC_9_1 = 1,  //!< Increases bus speed by 9.1%
    API429_SPEED_MOD_DEC_7_7 = 2,  //!< Decreases bus speed by 7.7%
    API429_SPEED_MOD_INC_20 = 3    //!< Increases bus speed by 20%
};

/*! \typedef TY_E_API429_SPEED_MODIFIER
 * Convenience macro for \ref api429_speed_modifier
 */
typedef enum api429_speed_modifier TY_E_API429_SPEED_MODIFIER;


/*! \def API429_LS_GRADE_DEFAULT
 *
 * Default low-speed graduation of a board
 */
#define API429_LS_GRADE_DEFAULT API429_LS_GRADE_12_50


/*! \enum api429_irig_source
 *
 * Enumeration of all supported irig source values
 * Used in \ref Api429BoardTimeSourceGet and \ref Api429BoardTimeSourceSet.
 */
enum api429_irig_source
{
    API429_IRIG_ONBOARD = 0,   //!< use the IRIG time that was generated onboard
    API429_IRIG_EXTERN = 1  //!< use the IRIG signal of an external IRIG time generator
};

/*! \typedef TY_E_API429_IRIG_SOURCE
 * Convenience macro for \ref api429_speed_modifier
 */
typedef enum api429_irig_source TY_E_API429_IRIG_SOURCE;


/*! \enum api429_channel_coupling
 * Enumeration of channel coupling modes
 */
enum api429_channel_coupling
{
    API429_CHANNEL_COUPLING_EXT = 0,    //!< All channels will send/receive physically to/from bus
    API429_CHANNEL_COUPLING_DUAL,       //!< All channels will send/receive physically to/from bus and the send data is also internally looped to its peer channel
    API429_CHANNEL_COUPLING_INT         //!< All channels are physically disconnected from bus. Sent data is internally looped to the peer channel
};


/*! \typedef TY_E_API429_CHANNEL_COUPLING
 * Convenience macro for \ref api429_channel_coupling
 */
typedef enum api429_channel_coupling TY_E_API429_CHANNEL_COUPLING;



/*! \brief Get properties of a specific device
 *
 * This function can be used to get some static properties of a specific device
 * @param[in] board_handle handle of the board to get properties of
 * @param[out] board_info pointer to \ref api429_board_info where properties will be stored
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardInfoGet(AiUInt8 board_handle, struct api429_board_info* board_info);


/*! \brief Set Arinc 429 low speed graduation for a specific board
 *
 * This function can be used to switch a board between the Arinc429 low speed graduations of 12,5 kBit/s and 13,33 kBit/s. \n
 * This setting will only have an effect with channels that are configured for low-speed transmission or reception.
 * This function affects the whole board and should not be used when a channel is active
 * @param[in] board_handle handle to the board to set low speed grade for
 * @param[in] low_speed_grade the Arinc 429 low speed grade to set. See \ref api429_low_speed_grade
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardLsGradeSet(AiUInt8 board_handle, enum api429_low_speed_grade low_speed_grade);


/*! \brief Set Arinc 429 speed modification value for a specific boards
 *
 * This function allows to adjust the bus speed on all transmit or receive channels of a board by
 * a specific factor. \n
 * This function affects the whole board and should not be used when a channel is active
 * The bus speed is no more Arinc 429 compliant after calling this function, unless setting it to \ref API429_SPEED_MOD_NORMAL.
 * @param[in] board_handle handle to board to modify bus speed for
 * @param[in] speed_modifier Arinc 429 bus speed modifier to set. See \ref api429_speed_modifier
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardSpeedModifierSet(AiUInt8 board_handle, enum api429_speed_modifier speed_modifier);


/*! \brief Set onboard IRIG time
 *
 * This function allows to set the time of the onboard IRIG timecode encoder. 
 * The IRIG timecode encoder needs up to three seconds before changing the time
 * @param[in] board_handle handle to board to modify bus speed for
 * @param[in] irig_time the time the IRIG timecode encoder shall be set to. See \ref api429_time
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardTimeSet( AiUInt8 board_handle, struct api429_time *irig_time);


/*! \brief Get IRIG time
 *
 * This function allows to read the time of the onboard IRIG timecode decoder. 
 * @param[in] board_handle handle to board to modify bus speed for
 * @param[out] irig_time current point of time, as provide by the IRIG timecode decoder. See \ref api429_time
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardTimeGet( AiUInt8 board_handle, struct api429_time *irig_time);


/*! \brief Set IRIG time source
 *
 * This function allows to set the source of the IRIG signal. 
 * @param[in] board_handle handle to board to modify bus speed for
 * @param[in] new_source the source the IRIG timecode decoder shall receive its signal from. See \ref api429_irig_source
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardTimeSourceSet( AiUInt8 board_handle, enum api429_irig_source new_source);


/*! \brief Get IRIG time source
 *
 * This function provides the source of the IRIG signal and some status information
 * @param[in] board_handle handle to board to modify bus speed for
 * @param[out] source the source the IRIG timecode decoder receives its signal from. See \ref api429_irig_source
 * @param in_sync information whether or not an IRIG signal is detected. This value is AiFalse if no valid IRIG signal can be read.
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardTimeSourceGet( AiUInt8 board_handle, enum api429_irig_source *source, AiBoolean* in_sync);


/*! \brief Get name of specific board
 *
 * Returns a human readable name for a specific hardware module.
 * @param[in] board_handle handle to board to get name of
 * @return
 * - pointer to zero-terminated ASCII string that contains board name
 * - NULL on error
 */
AI_LIB_FUNC const char* AI_CALL_CONV Api429BoardNameGet( AiUInt8 board_handle );


/*! \brief Resets whole board to power-up initial state
 *
 * This function can be used to reset a specific device to its
 * @param[in] board_handle handle to device to reset
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardReset( AiUInt8 board_handle);


/*! \brief Open access to a specific board
 *
 * This function is used to open a specific board. \n
 * A board must be opened before it can be used hence this function must be called
 * first to get a valid device handle that can be used in subsequent calls to this device.
 * @param[in] board_id ID of the device to open. See \ref api429_board_id
 *                 
 * @param[in] ac_SrvName zero-terminated ASCII string of the server the device is hosted on. \n
 *                   Must be 'local' when using devices on local systems
 * @param[out] handle handle to the opened device is stored here on success. Must be used for all subsequent calls to this device.
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardOpen(enum api429_board_id board_id, const char *ac_SrvName, AiUInt8* handle);


/*! \brief Close access to device
 *
 * This function is used to close a connection to a device.
 * @param[in] board_handle handle to board to close
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardClose( AiUInt8 board_handle );


/*! \brief Perform board self-test
 *
 * @param[in] board_handle Handle to board to perform self-test on
 * @param[in] b_Func Can be used to select specific functions to test
 *               - 0 Execute all test
 *               - 1 Board Enable Test
 *               - 2 Internal Firmware Selftest
 *               - 3 Interrupt Test
 *               - 4 API Global RAM Test
 * @param[out] pb_Status status variable is stored here
 * @param[out] pb_Echo echo variable is stored here
 *
 * <table>
 * <tr><th align="center">Status <th align="center"> Echo <th align="center"> Description
 * <tr><td align="center">0    <td align="center">  0   <td align="center"> Selftest passed
 * <tr><td align="center">  1  <td align="center" colspan="2"> Board Enable Test Error
 * <tr><td align="center">  2  <td align="center" colspan="2"> Internal Firmware Selftest Error
 * <tr><td><td align="center">  1   <td align="center"> Disable Board Failed
 * <tr><td><td align="center">  2   <td align="center"> Enable Board Failed
 * <tr><td><td align="center">  3   <td align="center"> Selftest Start Failed
 * <tr><td><td align="center">  4   <td align="center"> RAM Test Failed
 * <tr><td><td align="center">  5   <td align="center"> Encoder / Decoder Failure
 * <tr><td><td align="center">  6   <td align="center"> Processor Failure
 * <tr><td><td align="center">  7   <td align="center"> Other Failure
 * </table>
 *
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardSelftest( AiUInt8 board_handle, AiUInt8 b_Func, AiUInt8 *pb_Status, AiUInt8  *pb_Echo );


/*! \brief Function to control the channel coupling

    Function to enable or disable the internal channel coupling. It is also possible to send data to the front connector and
    also internally couple the channel at the same time.
    This functionality is known as channel loop in the firmware. This command was named channel
    coupling, to avoid confusion with the loop/pollution mode.
    \param[in] board_handle Handle to board
    \param[in] coupling coupling mode to set
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardChannelCouplingSet( AiUInt8 board_handle, enum api429_channel_coupling coupling);


/*! \brief Function to get information about the fixed internal channel coupling

    Function to learn how the channels are connected with each other, if the internal channel coupling is used.
    This functionality is known as channel loop in the firmware. This command was named channel
    wrap, to avoid confusion with the loop/pollution mode.
    \param [in] board_handle Handle to board
    \param [out] auc_Connection - array that tells the destination of a channel wrap. A value of zero means that this channel is
                                  not connected. auc_Connection[0] is not used for a channel.
                                  Example: if channel 1 is connected to channel 5, then auc_Connection[1] would be 5 and
                                  auc_Connection[5] would be 1.
    \return 
        - API_OK on success
        - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardChannelCouplingInfo( AiUInt8 board_handle, AiUInt8 auc_Connection[API429_MAX_CHANNELS+1] );



/*! \brief Function to get information if internal coupling is supported

    Function to learn if internal channel coupling is supported.
    \param [in] board_handle Handle to board
    \param [out] is_supported - AiTrue if channel coupling is supported by the hardware, else "0"
    \return 
        - API_OK on success
        - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardChannelCouplingIsSupported( AiUInt8 board_handle, AiBoolean* is_supported );



/*! \brief Configure PXI trigger
 *
 * This function is used to combine PXI specific trigger lines with the trigger lines of
 * AIM boards. \n
 * It also provides support to switch the IRIG TT source.
 * @param[in] board_handle handle to board to configure PXI triggers on
 * @param[in] ul_Mode mode 
 * @param[in] ul_TrgSource trigger source
 * @param[in] ul_TrgDest trigger destination
 * @param[in] ul_TTClear Allow to clear time tag with external pulse on PXI TRIGGER INPUT 0 or PXI STAR TRIGGER. Only for mode API429_PXI_SET_TTSRC_BACKPLANE and API429_PXI_SET_TTSRC_FRONT. If enabled the PXI Trigger Line 0 cannot be used as trigger source or destination.
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardPXITriggerConfigure( AiUInt8 board_handle, enum api429_pxi_mode ul_Mode, enum api429_pxi_trigger_line ul_TrgSource, enum api429_pxi_trigger_line ul_TrgDest, AiBoolean ul_TTClear);


/*! \brief Request extended information from a host
 *
 * This function will request extended information about the host
 * system a specific board is situated on
 * @param[in] board_handle handle to board to request host information for
 * @param[out] server_info server information is stored here. See \ref api429_remote_server
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardServerInfoGet(AiUInt8 board_handle, struct api429_remote_server* server_info);



// @cond ANS
/*! Apply a command to the target software (old style)
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardLegacyTargetCommand(AiUInt8 board_handle, AiUInt8 b_Biu, AiUInt32 ul_Cmd, short w_Expect,
                                                                  AiUInt8 *pb_OutByte, short w_OutByteSize, AiUInt16 *pw_OutWord, short w_OutWordSize,
                                                                  AiUInt8 *pb_InByte, short *pw_InByteSize, AiUInt16 *pw_InWord, short *pw_InWordSize,
                                                                  AiUInt32 *pl_InLWord, short *pw_InLWordSize );

/*! Apply a command to the target software (struct based)
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardTargetCommand( AiUInt8 board_handle, void* pTargetCommand, AiUInt32 commandSize, void* pReturnData, AiUInt32* returnSize );
// @endcond


/** @} */


#endif /* API429BOARD_H_ */
