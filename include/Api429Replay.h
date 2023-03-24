/*! \file Api429Replay.h
 *
 *  This header file contains API functionality
 *  related to replay
 *  Created on: 10.03.2016
 */

#ifndef API429REPLAY_H_
#define API429REPLAY_H_


#include "Ai_cdef.h"


/**
* \defgroup replay Data Replay
   This module contains functionality related to replaying received Arinc 429
   data.
* @{
*/



/*! \struct api429_replay_status
 *
 *  This structure holds current status of a replay transmission
 */
struct api429_replay_status
{
  AiUInt8  uc_Status;       /*!< API429_HALT or API429_BUSY */
  AiUInt8  uc_Padding1;     /*!< reserved */
  AiUInt16 uw_Padding2;     /*!< reserved */
  AiUInt32 ul_RpiCnt;       /*!< Actual value of the Half Buffer Transmitted Interrupt counter (incremented each time a Half
                                 Buffer Transmitted Interrupt occurs)
                                 When the 'ul_RpiCnt' value is incremented, new replay data should be reloaded using \ref Api429ReplayDataWrite'. */
  AiUInt32 ul_EntryCnt;     /*!< Initial value calculated from the file size (refer to \ref Api429ReplayInit, parameter
                                 'ul_FileSize') and decremented when replay is started. */
  AiUInt32 ul_StartAddr;    /*!< Start Address of the the next half Replay buffer that can be written to (the half buffer that is
                                 currently not being sent) in the Global RAM area to where the user can copy the replay
                                 buffer entries from the Shared RAM area. */
  AiUInt32 ul_Size;         /*!< Size of a half Replay buffer (in bytes).*/
};


/*! \typedef TY_API429_REPLAY_STATUS
 * Convenience typedef for \ref api429_replay_status
 */
typedef struct api429_replay_status TY_API429_REPLAY_STATUS;




/*! \brief Initialize Replay on a specific channel
 *
 * This function is used to initialize the physical replay mode of the AIM board.
 *
 * @param [in] board_handle handle to the board the channel belongs to
 * @param [in] uc_Chn ID of channel to initialize Replay on
 * @param [in] uc_ClrEntryBit Clear Entry Bit
 * @param [in] uc_NoRepCnt No Replay Count
 * @param [in] uc_CycOpr Cyclic Operation
 * @param [in] uc_RepErrors Replay Errors
 * @param [in] uc_RepIntMode Replay Interrupt Control
 * @param [in] uc_AbsLongTTag Absolute Long Time Tag Replay
 * @param [in] uw_DayOfYear Specifies the original start day of the recorded buffer. This
                       is necessary because the time tag information in the
                       recording file specifies only the hour of a day.
 * @param [in] l_Min Absolute minute offset. Only required if “uc_AbsLongTTag” is set to one. \n
 *              Specify the offset between the recorded replay time and the
                actual IRIG time of the system at which the replay process
                shall start. The value is specified as a two's complement
                integer value with a possible range of one year in minutes
                (±525600, if no leap year)
 * @param [in] l_MSec Absolute microsecond offset. Only required if “uc_AbsLongTTag” is set to one.
 *               Specify the offset between the recorded replay time and the
                 actual IRIG time of the system at which the replay process
                 shall start. The value is specified as a two's complement
                 integer value with a possible range of one minute in
                 microseconds (±59 999 999).
 * @param [in] ul_FileSize Replay file size in bytes
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429ReplayInit( AiUInt8 board_handle, AiUInt8 uc_Chn, AiUInt8 uc_ClrEntryBit, AiUInt8 uc_NoRepCnt,
                                                     AiUInt8 uc_CycOpr, AiUInt8 uc_RepErrors, AiUInt8 uc_RepIntMode, AiUInt8 uc_AbsLongTTag,
                                                     AiUInt16 uw_DayOfYear, AiInt32 l_Min, AiInt32 l_MSec, AiUInt32 ul_FileSize);


/*! \brief Get Replay Status of a specific channel
 *
 * This function is used to read the replay status information. The initial value of
 * parameter 'ul_RpiCnt' indicates the amount of half buffer transmitted interrupts
 * required for writing the requested replay file size (refer to parameter 'ul_FileSize' of
 * library function Api429ReplayInit).
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] uc_Chn ID of channel to get replay status of
 * @param [out] px_RepStatus Replay status structure
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429ReplayStatusGet( AiUInt8 board_handle, AiUInt8 uc_Chn, struct api429_replay_status* px_RepStatus);


/*! \brief Write Replay data for a specific channel
 *
 * This function writes and copies replay data and allows an easy implementation of
 * an ARINC replay task.
 * @param [in] board_handle handle to board the channel belongs to
 * @param [in] uc_Chn ID of channel to write replay data for
 * @param [in] px_RepStatus Replay Status
 * @param [in] pv_Buf Pointer to application buffer area (replay data)
 * @param [out] pul_BytesWritten Amount of bytes written
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429ReplayDataWrite(AiUInt8 board_handle, AiUInt8 uc_Chn, struct api429_replay_status* px_RepStatus, void *pv_Buf,
                                                         AiUInt32 *pul_BytesWritten);



/** @} */



#endif /* API429REPLAY_H_ */
