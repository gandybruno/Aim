/******************************************************************************

           Copyright (c) AIM GmbH 2001, 79111 Freiburg, Germany.

            All rights reserved.  No part of this software may
            be published, distributed, translated or otherwise
            reproduced by any means or for any purpose without
            the prior written consent of AIM GmbH, Freiburg.

******************************************************************************/
/*! \file Api429Vme.h
 *
 *  This header file contains function declarations
 *  related to VME functionality (also used for PCI bus handling in VxWorks)
 *  Created on: 09.02.2016
 *      Author: Markus Melcher
 */


#ifndef API429VME_H_
#define API429VME_H_



/**
* \defgroup vme VxWorks Related Functions
This module contains functionality related to AIM Arinc 429 board handling for VME.
Also used for PCI bus handling under VxWorks
* @{
*/


/*! \brief Map a board
 *
 * This command maps a board to a given VME A32 address or to a given PCI address
 * 
 * @param in    struct containing all parameters required for mapping the board
 * @param in->ul_A32Addr        physical PCI Bus or VME A32 address of the board
 * @param in->ul_A32UserAccess  virtual address, with which the board can be accessed
 * @param in->ul_Force          force mapping process - even if already mapped
 * @param in->ul_cPCI           has to be set to '1' for cPCI bus
 * @param in->px_PCI_Info       the pci info (inluding the PCI header) proivded by 
 *                                   either \ref AiPciScan or \ref AiVmeExamineSlot
 * 
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV AiVme429MapModule(struct ty_vme_map_module_in *in);

/*! \brief Unmap a board
 *
 * This command clears the mapping done with \ref AiVme429MapModule
 * 
 * @param [in] in    struct that was used to map the board
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV AiVme429UnmapModule(struct ty_vme_map_module_in *in);

/*! \brief Verify the board is handled by this driver library
 *
 * This command verifies the board can be used with \ref AiVme429MapModule
 * 
 * @param [in] in    struct that was used to map the board
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Ai429CheckModule(struct ty_vme_map_module_in *in);



/** @} */


AI_LIB_FUNC AiReturn AI_CALL_CONV AiVme429MapModuleGet(AiUInt32 ul_A16Addr, AiUInt32 isSecondBoardOnCarrier, AiUInt32 ul_A32Addr, AiUInt32 ul_A32AccessAddr);





#endif /* API429VME_H_ */
