/******************************************************************************

           Copyright (c) AIM GmbH 2001, 79111 Freiburg, Germany.

            All rights reserved.  No part of this software may
            be published, distributed, translated or otherwise
            reproduced by any means or for any purpose without
            the prior written consent of AIM GmbH, Freiburg.

******************************************************************************/

/*! \file Api429Discretes.h
 *
 *  This header file contains API functions
 *  that are related to discrete I/O
 *  Created on: 10.03.2016
 */

#ifndef API429DISCRETES_H_
#define API429DISCRETES_H_


#include "Ai_cdef.h"




/**
* \defgroup discretes Discrete Handling
   This module contains functionality related to discrete I/O channel handling
   of AIM Arinc 429 boards
* @{
*/



/*! \struct api429_discr_info
 * This structure gives information about the discrete channels
 *
 */
struct api429_discr_info
{
    AiUInt32 channels; /*!<  Number of discrete channels*/
    AiUInt32 canIn; /*!< bit field that tells, which channels can be set to In */
    AiUInt32 canOut; /*!< bit field that tells, which channels can be set to Out */
};

/*! \typedef TY_API429_DISCR_INFO
 * Convenience macro for struct api429_discr_info
 */
typedef struct api429_discr_info TY_API429_DISCR_INFO;


/*! \struct api429_discrete_pps_config
 * This structure allows to control the PPS signal on a given discrete channel (AyX429 only)
 */
struct api429_discrete_pps_config
{
    AiUInt32 ul_DiscreteChannelId; /*!< Discrete to send the PPS signal to */
    AiUInt32 ul_EnaDis;            /*!< if set to '1' enable, if set to '0' disable */
};


/*! \typedef TY_API429_DISCRETE_PPS_CONFIG
 * Convenience macro for struct api429_discrete_pps_config
 */
typedef struct api429_discrete_pps_config TY_API429_DISCRETE_PPS_CONFIG;




/*! \brief Read current value from dicrete channels
 *
 * This command is used to read the current values from the discrete I/O channels
 * @param[in] board_handle handle to board to read discrete channels of
 * @param[out] pul_Value This bitfield shows the values of the corresponding discrete channels.
 *                  BIT0 corresponds to the first channel, BIT7 to the eighth.
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429DiscretesRead  ( AiUInt8 board_handle, AiUInt32 *pul_Value );


/*! \brief Write to discrete output channels
 *
 * This command is used to write to the discrete outputs.
 * @param[in] board_handle handle to board to write discrete channels on
 * @param[in] ul_Mask The mask is a bitfield used to define the discrete output channels that are
 *                modified. A logical “1” in a bit marks the discrete output to be modified.
 * @param[in] ul_Value This bitfield shows the values of the corresponding discrete channels. BIT0
                   corresponds to the first channel, BIT7 to the eighth.
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429DiscretesWrite( AiUInt8 board_handle, AiUInt32 ul_Mask, AiUInt32 ul_Value );


/*! \brief Configures discrete I/O channel
 *
 * This command is used to configure the discretes. APX429, ACX429-3U
 * and APU429 boards provide 8 discretes where each of the discretes can be
 * initialized as Input or Output.
 * @param[in] board_handle handle to board to configure discrete channels on
 * @param[in] ul_DiscreteSetup Each of the discretes can be programmed to Input or Output where 1 means Output and 0 means Input
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429DiscretesConfigSet( AiUInt8 board_handle, AiUInt32 ul_DiscreteSetup );


/*! \brief Get current configuration of discrete I/O channels
 *
 * @param[in] board_handle handle to board to get discrete I/O configuration from
 * @param[out] pul_DiscreteSetup Each bit indicates if corresponding discrete I/O channel is programmed for Output or Input where 1 means Output and 0 means Input
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429DiscretesConfigGet( AiUInt8 board_handle, AiUInt32 *pul_DiscreteSetup );


/*! \brief Get current discrete configuration
 *
 * This command is used to read the configuration of the discrete channels.
 * @param[in] board_handle handle to board to get discrete configuration of
 * @param[out] px_DiscrInfo discrete configuration will be stored here
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429DiscretesInfoGet(AiUInt8 board_handle, struct api429_discr_info *px_DiscrInfo);

/*! \brief On AyX429 generate an PPS signal on a discrete channel
 *
 * This command is used to generate a PPS signal on a given discrete channel
 * @param[in] board_handle handle to the device
 * @param[in] px_Pps setup information for the PPS signal
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429DiscretesPPSSet( AiUInt8 board_handle, struct api429_discrete_pps_config *px_Pps );



/** @} */



#endif /* API429DISCRETES_H_ */
