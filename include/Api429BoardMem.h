/******************************************************************************

           Copyright (c) AIM GmbH 2001, 79111 Freiburg, Germany.

            All rights reserved.  No part of this software may
            be published, distributed, translated or otherwise
            reproduced by any means or for any purpose without
            the prior written consent of AIM GmbH, Freiburg.

******************************************************************************/

/*! \file Api429BoardMem.h
 *
 *  This header file contains API functionality
 *  for handling on-board memory
 *  Created on: 10.03.2016
 */

#ifndef API429BOARDMEM_H_
#define API429BOARDMEM_H_


#include "Ai_cdef.h"
#include "Ai_def.h"


/**
* \defgroup board_mem Raw Board Memory Access
This module contains functionality related to raw access to AIM Arinc 429 board memory
* @{
*/




/*! \enum api429_memory_object
 *
 *  Enumeration of all possible memory object types
 */
enum api429_memory_object
{
    API429_MEM_OBJ_XFER  = 1, //!< Transfer object
    API429_MEM_OBJ_XFER_BUF,  //!< Transfer buffer object
    API429_MEM_OBJ_MINFRM,    //!< Minor Frame object
    API429_MEM_OBJ_MAJFRM,    //!< Major frame object
    API429_MEM_OBJ_LABDESC,   //!< Label descriptor object
    API429_MEM_OBJ_RXBUF,     //!< Receive buffer object
    API429_MEM_OBJ_TXCOUNT,   //!< Transfer counter object
    API429_MEM_OBJ_CHN_DESC,  //!< Channel descriptor
    API429_MEM_OBJ_RM_BUF     //!< RM buffer
};


/*! \typedef TY_E_API429_MEMORY_OBJECT
 *
 * Convenience macro for \ref api429_memory_object
 */
typedef enum api429_memory_object TY_E_API429_MEMORY_OBJECT;




/*! \brief Get offset of specific on-board data types
 *
 * @param [in] board_handle handle to board
 * @param [in] uc_Chn ID of channel the memory object is assigned to
 * @param [in] object_type memory object type to get location of
 * @param [in] id The ID of the Xfer/Minor frame/Label/etc. (Not used for all object_types)
 * @param [out] pul_MemType memory type of requested object is stored here
 * @param [out] pul_Offset offset in bytes of requested memory object is stored here
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardMemLocationGet ( AiUInt8 board_handle, AiUInt8 uc_Chn, enum api429_memory_object object_type,
                                                               AiUInt32 id, enum ty_e_mem_type* pul_MemType, AiUInt32 *pul_Offset);


/*! \brief Get location of Irig time registers
 *
 * @param [in] board_handle handle of board
 * @param [out] pul_TimerOffset offset of time registers is stored here
 * @param [out] pul_MemType memory type where irig time registers are located
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardMemTimerAddrGet( AiUInt8 board_handle, AiUInt32 *pul_TimerOffset, enum ty_e_mem_type* pul_MemType );




/*! \brief Read board memory
 *
 * This function is used to read a byte/word/longword from the AIM board memory in
 * avoidance of AIM board command and acknowledge interface access. This is
 * necessary to access the AIM board memory in case of interrupt. The function does
 * a direct access to the AIM board memory with the specified offset address.
 * @param [in] board_handle handle to board to read from
 * @param [in] memtype Memory Type to be accessed
 * @param [in] offset Byte offset address relative to the start of a specific onboard memory described
                 in parameter ‘memtype’.
 * @param [in] width Data width of access. This is important if data is read from a source with different
                endianess e.g. if reading at a MVME5100 from the global memory of an
                AMCX429 board)
 * @param [out] data_p Data to read to. This pointer should match to the data size given in the parameter
                 ‘width’.
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardMemRead( AiUInt8 board_handle, enum ty_e_mem_type memtype, AiUInt32 offset, AiUInt8 width, void* data_p);


/*! \brief Write board memory
 *
 * This function is used to write a byte/word/longword to the AIM board memory in
 * avoidance of AIM board command and acknowledge interface access. This is
 * necessary to access the AIM board memory in case of interrupt. The function does
 * a direct access to the AIM board memory with the specified offset address.
 * @param [in] board_handle handle to the board to write to
 * @param [in] memtype Memory Type to be accessed
 * @param [in] offset Byte offset address relative to the start of a specific onboard memory described
                 in parameter ‘memtype’.
 * @param [in] width Data width of access. This is important if data is read from a source with different
                endianess e.g. if reading at a MVME5100 from the global memory of an
                AMCX429 board)
 * @param [in] data_p Data to write from. This pointer should match to the data size given in the
                 parameter ‘width’.
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardMemWrite( AiUInt8 board_handle, enum ty_e_mem_type memtype, AiUInt32 offset, AiUInt8 width, void* data_p);


/*! \brief Read block of board memory
 *
 * This function is used to read a data block from the AIM board memory in avoidance
 * of AIM board command and acknowledge interface access. This is necessary to
 * access the AIM board memory in case of interrupt. The function does a direct
 * access to the AIM board memory with the specified offset address.
 * @param [in] board_handle handle to the board to read from
 * @param [in] memtype Memory Type to be accessed
 * @param [in] offset Byte offset address relative to the start of a specific onboard memory described
                 in parameter ‘memtype’.
 * @param [in] width Data width of access. This is important if data is read from a source with different
                endianess e.g. if reading at a MVME5100 from the global memory of an
                AMCX429 board)
 * @param [out] data_p Data to read to. This pointer should match to the data size given in the parameter
                 ‘width’.
 * @param [in] size Amount of data block elements.
 * @param [out] pul_BytesRead Amount of bytes actually read.
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardMemBlockRead  ( AiUInt8 board_handle, enum ty_e_mem_type memtype, AiUInt32 offset, AiUInt8 width, void* data_p,
                                                              AiUInt32 size, AiUInt32 *pul_BytesRead);


/*! \brief Write block of board memory
 *
 * This function is used to write a data block to the AIM board memory in avoidance of
 * AIM board command and acknowledge interface access. This is necessary to
 * access the AIM board memory in case of interrupt. The function does a direct
 * access to the AIM board memory with the specified offset address.
 * @param [in] board_handle handle to board to write to
 * @param [in] memtype Memory Type to be accessed
 * @param [in] offset Byte offset address relative to the start of a specific onboard memory described
 *               in parameter ‘memtype’.
 * @param [in] width Data width of access. This is important if data is read from a source with different
                endianess e.g. if reading at a MVME5100 from the global memory of an
                AMCX429 board)
 * @param [in] data_p Data to write from. This pointer should match to the data size given in the
                 parameter ‘width’.
 * @param [in] size Amount of data block elements.
 * @param [out] pul_BytesWritten
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardMemBlockWrite ( AiUInt8 board_handle, enum ty_e_mem_type memtype, AiUInt32 offset, AiUInt8 width, void* data_p,
                                                              AiUInt32 size, AiUInt32 *pul_BytesWritten);


AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardMemAlloc(AiUInt8 board_handle, enum ty_e_mem_type mem_type, AiUInt32 ulSize, AiUInt32 ulTag, AiUInt32 *pulOffset);
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardMemFree(AiUInt8 board_handle, enum ty_e_mem_type mem_type, AiUInt32 ulOffset);

AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardMemSizeGet( AiUInt8 board_handle, enum ty_e_mem_type mem_type, AiSize* size);



/** @} */



#endif /* API429BOARDMEM_H_ */
