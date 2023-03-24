/******************************************************************************

           Copyright (c) AIM GmbH 2001, 79111 Freiburg, Germany.

            All rights reserved.  No part of this software may
            be published, distributed, translated or otherwise
            reproduced by any means or for any purpose without
            the prior written consent of AIM GmbH, Freiburg.

******************************************************************************/
/*! \file Api429BoardDriver.h
 *
 *
 *  This header contains API functions
 *  that can be used to tweak the board drivers
 *  Created on: 16.03.2016
 */

#ifndef API429BOARDDRIVER_H_
#define API429BOARDDRIVER_H_



/*! \struct api429_driver_config
*
* This struct contains configuration information of the driver
*/
typedef struct api429_driver_config {
    AiUInt32 ul_DmaEnabled;     /*!< 0: disable DMA, 1: use DMA */
    AiUInt32 ul_DmaMinimumSize; /*!< lower memory size limit for DMA transfer. DMA will not issued, if the requested memory block is lower than this value */
    AiUInt32 ul_ReservedLW2;
    AiUInt32 ul_ReservedLW3;
    AiUInt32 ul_ReservedLW4;
    AiUInt32 ul_ReservedLW5;
    AiUInt32 ul_ReservedLW6;
    AiUInt32 ul_ReservedLW7;
    AiUInt32 ul_ReservedLW8;
} TY_API429_DRIVER_CONFIG;



/*! \brief Set device properties related to performance tweaking
 *
 * @param[in] board_handle handle to device to set properties for
 * @param[in] pxConfig pointer to \ref TY_API429_DRIVER_CONFIG that holds properties to set
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardDriverConfigSet( AiUInt8 board_handle, struct api429_driver_config * pxConfig );


/*! \brief Set default device properties related to performance tweaking
 *
 * @param[in] board_handle handle to device to set default properties for
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardDriverConfigSetDefault( AiUInt8 board_handle );


/*! \brief Set default device properties related to performance tweaking
 *
 * @param[in] board_handle handle to device to get default properties for
 * @param[out] pxConfig pointer to \ref TY_API429_DRIVER_CONFIG where current properties will be stored
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardDriverConfigGet( AiUInt8 board_handle, struct api429_driver_config * pxConfig );


/*! \brief Function to get some information from the driver
 *
 *  Function to get some basic information from the driver, without accessing the target software.
 * @param [in] board_handle handle to board to get driver info for
 * @param [out] pxDriverInfo - Pointer to the structure that shall hold the information
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429BoardDriverInfoGet( AiUInt8 board_handle, struct ty_driver_info * pxDriverInfo );



#endif /* API429BOARDDRIVER_H_ */
