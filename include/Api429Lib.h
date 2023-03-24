/******************************************************************************

           Copyright (c) AIM GmbH 2001, 79111 Freiburg, Germany.

            All rights reserved.  No part of this software may
            be published, distributed, translated or otherwise
            reproduced by any means or for any purpose without
            the prior written consent of AIM GmbH, Freiburg.

******************************************************************************/

/*! \file Api429Lib.h
 *
 * This header file contains API functions related to library
 * handling
 *
 *  Created on: 10.03.2016
 */

#ifndef API429LIB_H_
#define API429LIB_H_


#include "Ai_cdef.h"



/**
* \defgroup lib Library Administration Functions
  This module contains functionality related to library handling
* @{
*/



/*! \enum api429_pnp_event
 * Enumeration for all possible events
 * related to Plug 'n' Play device events
 */
enum api429_pnp_event
{
    API429_DEVICE_CONNECTED = 0, //!< Plug 'n' Play device connected
    API429_DEVICE_DISCONNECTED   //!< Plug 'n' Play device disconnected
};


/*! \typedef TY_E_API429_PNP_EVENT
 * Convenience typedef for \ref api429_pnp_event
 */
typedef enum api429_pnp_event TY_E_API429_PNP_EVENT;


/*! \typedef TY_429PNP_CALLBACK_FUNC_PTR
 *
 * Callback function that handles library Plug 'n' Play device events.
 * @param [out] module_id ID of module that caused the event
 * @param [out] event_type Event that caused callback invocation. See \ref api429_pnp_event
 */
typedef void  (AI_CALL_CONV *TY_429PNP_CALLBACK_FUNC_PTR)(AiUInt32 module_id, enum api429_pnp_event event_type );




/*! \brief Convert API error code to human readable description
 *
 * @param [in] ul_ErrorCode code to convert
 * @return
 * - pointer to zero-terminated ASCII string that contains error description on success
 * - NULL on failure
 */
AI_LIB_FUNC const char* AI_CALL_CONV Api429LibErrorDescGet ( AiReturn ul_ErrorCode);


/*! \brief Initialization function for library
 *
 * This function initializes the entire application interface and must be called first in an
 * application program before any other function is applied.
 * @return
 * - Number of local AIM Arinc 429 boards
 */
AI_LIB_FUNC AiInt AI_CALL_CONV Api429LibInit(void);


/*! \brief Clean-up function for library
 * This function cleans up the application interface initialization done in Api429Init and
 * should be called in an application program after any other function has finished.
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429LibExit(void);


/*! \brief Set library debug level
 *
 * This function is for internal use (debugging purposes).
 * @param [in] ul_DllDbgLevel level to set
 *
 * __Debug Levels:__
 * Constant         | Description
 * ---------        |-------------
 * API429_DBG_NONE  | Disable additional debug information (default)
 * API429_DBG_TRACE | No longer supported
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429LibDebugLevelSet( AiUInt32 ul_DllDbgLevel );


/*! \brief Register handler for Plug N' Play device events
 *
 * This function provides mechanism to notify PnP device changes. For example
 * adding or removing an APU429 at runtime.
 * @param [in] PnPCallbackFunction pointer to a handler function that shall be called when a device
 * was added to or removed from the system. See \ref TY_429PNP_CALLBACK_FUNC_PTR
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429LibPnpCallbackSet( TY_429PNP_CALLBACK_FUNC_PTR PnPCallbackFunction );


/*! \brief Establish connection to remote server
 *
 * Establishes a network connection to a specified server PC where the ANS software
 * (AIM Network Server) or an Ethernet based Arinc 429 device (e.g. ANET429) is running.
 * @param [in] pszNetworkAdress Name of the PC, where the ANS Server is running.
 * Name of the PC, where the ANS Server (AIM Network Server) is running (e.g. “SW-PC-06” or “192.168.0.119”)
 * @param [out] w_ServerBoards Number of AIM boards installed on server PC
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429LibServerConnect ( const char * pszNetworkAdress, AiInt16 *w_ServerBoards);


/*! \brief Disconnect from server
 *
 * Disconnects a previously established network connection from a specified server
 * PC where the ANS software (AIM Network Server) is running.
 * @param [in] pszNetworkAdress Name of the PC, where the ANS Server (AIM Network Server) is running (e.g. “SW-PC-06” or “192.168.0.119”)
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
 AI_LIB_FUNC AiReturn AI_CALL_CONV Api429LibServerDisconnect( const char * pszNetworkAdress );


 /** @} */


#endif /* API429LIB_H_ */
