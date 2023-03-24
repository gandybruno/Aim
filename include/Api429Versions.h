/******************************************************************************

           Copyright (c) AIM GmbH 2001, 79111 Freiburg, Germany.

            All rights reserved.  No part of this software may
            be published, distributed, translated or otherwise
            reproduced by any means or for any purpose without
            the prior written consent of AIM GmbH, Freiburg.

******************************************************************************/
/*! \file Api429Versions.h
 *
 *  This header contains API functionality related
 *  to version reading
 *  Created on: 10.03.2016
 *
 */

#ifndef API429VERSIONS_H_
#define API429VERSIONS_H_


#include "Ai_cdef.h"
#include "Ai_def.h"



/**
* \defgroup versions Version Handling
  This module contains functionality related to versioning of on-board
  firmware and host software components.
* @{
*/


/*! \struct api429_version
 *
 * This struct contains the version of a given BSP component
 */
struct api429_version
{
  AiUInt32 ul_MajorVer; /*!< The major version number of the component */
  AiUInt32 ul_MinorVer; /*!< The minor version number of the component */
  AiUInt32 ul_BuildNr; /*!< The build number of the component */
  AiUInt32 ul_MajorSpecialVer; /*!< Only used in special cases */
  AiUInt32 ul_MinorSpecialVer; /*!< Only used in special cases */
};
/*! \typedef TY_API429_VERSION
 * Convenience macro for struct api429_version
 */
typedef struct api429_version TY_API429_VERSION;

/*! \struct api429_version_info
 *
 * This structure contains several components of the BSP
 */
struct api429_version_info
{
  struct api429_version x_TcpVer; /*!< Version of the time code processor */
  struct api429_version x_PciLcaVer; /*!< Version of the PCI FPGA */
  struct api429_version x_AslLcaVer; /*!< Version of the ASL FPGA (AyX429 only) */
  struct api429_version x_IoLcaBiu1Ver; /*!< Version of the ARINC 429 IO FPGA on BIU1*/
  struct api429_version x_IoLcaBiu2Ver; /*!< Version of the ARINC 429 IO FPGA on BIU2*/ 
  struct api429_version x_FirmwareBiu1Ver; /*!< Version of the firmware on BIU1*/
  struct api429_version x_FirmwareBiu2Ver; /*!< Version of the firmware on BIU2*/
  struct api429_version x_TargetSWVer; /*!< Version of the target software*/
  struct api429_version x_SysDrvVer; /*!< Version of the device driver*/
  struct api429_version x_DllVer; /*!< Version of the library*/
  struct api429_version x_VmeGeneric; /*!< Version of the generic part of VME systems*/
  struct api429_version x_MonitorVer; /*!< Version of the included monitor*/
  AiUInt32 ul_BoardSerialNr; /*!< Serial number of the board*/
};
/*! \typedef TY_API429_VERSION_INFO
 * Convenience macro for struct api429_version_info
 */
typedef struct api429_version_info TY_API429_VERSION_INFO;



/*! \brief This function reads all available versions
    A count of 0 can be used to obtain the number of available
    versions in px_VersionInfoOut. The array px_VersionInfoInOut has
    to be pre allocated by the application. The size must be big enought
    to hold count items. The array shall be cleared with memset before
    this function is called.

    \param [in]  uc_Handle            The module handle.
    \param [in]  ul_Count             Defines how many versions to read.
    \param [out] ax_Versions          The pre allocated version arry (size=count).
    \param [out] px_VersionInfoOut    Information about the available and returned versions.

    \return
    - API_OK on success
    - AI429_ERR_INVALID_MODULE_HANDLE if module handle is invalid
    - AI429_ERR_NULL_POINTER if px_VersionInfoOut is NULL or ax_Versions is NULL and ul_Count > 0
    - Appropriate other error code, which may be used as input parameter for \ref Api429LibErrorDescGet
*/
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429VersionGetAll   ( AiUInt8 uc_Handle, AiUInt32 ul_Count, struct ty_ver_info ax_Versions[], struct ty_version_out* px_VersionInfoOut );


/*! \brief This function reads a specific version
    This function returns the version in px_Version. If the version does
    not exist for the given board, it will return AI429_ERR_ID.

    \param [in]  uc_Handle          The module handle.
    \param [in]  eId                The version id to read.
    \param [out] px_Version         Pointer to store the version info.

    \return 
    - Zero if the version is valid or AI429_ERR_ID if the version does not exist. \n
    - Appropriate other error code, which may be used as input parameter for \ref Api429LibErrorDescGet
*/
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429VersionGet( AiUInt8 uc_Handle, TY_E_VERSION_ID eId, struct ty_ver_info *px_Version );


/*! \brief Legacy version read/compatibility function
 *
 * This function returns the version numbers of the board software package
 * components for the AIM board.
 * @param [in] bModule handle to board to get versions of
 * @param [out] px_VersionInfo version info is stored here
 * @param [out] puc_BspCompatibility Compatibility Status of the current BSP components relating to the library
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_DEPRECATED(AI_LIB_FUNC AiReturn AI_CALL_CONV Api429ReadBSPVersionEx( AiUInt8 bModule, struct api429_version_info* px_VersionInfo, AiUInt8* puc_BspCompatibility ) );



/** @} */




#endif /* API429VERSIONS_H_ */
