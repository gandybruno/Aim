/******************************************************************************

           Copyright (c) AIM GmbH 2001, 79111 Freiburg, Germany.

            All rights reserved.  No part of this software may
            be published, distributed, translated or otherwise
            reproduced by any means or for any purpose without
            the prior written consent of AIM GmbH, Freiburg.

******************************************************************************/
/*! \file Api429Update.h
 *
 *  This header file contains functions related
 *  to on-board update functionality
 *
 *  Created on: 10.03.2016
 */

#ifndef API429UPDATE_H_
#define API429UPDATE_H_


#include "Ai_cdef.h"


typedef struct
{
       AiUInt8 lca_id;
       AiUInt8 padding1;
       AiUInt16 padding2;
       AiUInt16 asp_drv_id;
       AiUInt16 asp_mon_id;
       AiUInt16 asp_bite_id;
       AiUInt16 api_fw_id;
       AiUInt32 lca_chks;
       AiUInt32 glb_mem_size;
       AiUInt32 glb_mem_addr;
       AiUInt32 loc_dram_size;
       AiUInt32 loc_dram_addr;
       AiUInt32 shared_dram_size;
       AiUInt32 shared_dram_addr;
       AiUInt32 flash_ram_size;
       AiUInt32 flash_ram_addr;
       AiUInt32 board_type;
       AiUInt32 board_config;
       AiUInt32 board_serial;
       AiUInt32 chn_cnt;
       AiUInt32 pci[16];
} TY_API429_INI_INFO;


/* function Api429CmdUtility() */
#define API429_UTIL_CMD_WRITE_NOVRAM     0
#define API429_UTIL_CMD_READ_NOVRAM      1





/* -- ESmart Update definitions -- */


/*! \def API429_FILE_FLAG_OVERWRITE
 * File can be overwritten
 */
#define API429_FILE_FLAG_OVERWRITE    (1 << 0 )


/*! \def API429_FILE_FLAG_APPEND
 * File can be appended
 */
#define API429_FILE_FLAG_APPEND       (1 << 1 )


/*! \struct api429_file_upload_in
 * This structure holds the input parameters for
 * the \ref AiFcCmdFileUpload API function
 */
typedef struct api429_file_upload_in
{
    const AiChar* pc_DestFilePath;      /*!< path to destination file on host where uploaded file will be stored */
    const AiChar* pc_SourceFileName;    /*!< Name of the file on the embedded device to upload */
    AiUInt32 ul_Flags;                  /*!< File flags for the destination file e.g. \ref API429_FILE_FLAG_OVERWRITE to allow overwriting */
} TY_API429_FILE_UPLOAD_IN;



/*! \enum api429_e_update_status
 *
 * Enumeration of all possible update states
 * when using Api429CmdUpdateStatus
 */
typedef enum api429_e_update_status
{
    API429_UPDATE_DEV_CON_FAILURE = -1, /*!< Update related connection to board is broken. No update possible any more */
    API429_UPDATE_IDLE,                 /*!< Device is ready for updating */
    API429_UPDATE_START_REQUESTED,      /*!< Device update has been requested but has not started yet */
    API429_UPDATE_IN_PROGRESS,          /*!< Device update is currently in progress */
    API429_UPDATE_FAILED,               /*!< Device update procedure failed */
    API429_UPDATE_FINISHED              /*!< Device update procedure successfully finished */
} TY_API429_E_UPDATE_STATUS;




/*! \struct a429_packet_update_status_out
 *
 * This structure holds the output parameters for
 * the Api429FcCmdUpdateStatus function
 */
typedef struct a429_packet_update_status_out
{
    enum api429_e_update_status e_Status;            /*!< Current update procedure status. See \ref api429_e_update_status */
    AiUInt32                    ul_ComponentsDone;   /*!< Number of components that have been updated so far. Only valid when
                                                          update procedure is in progress, finished or failed */
    AiUInt32                    ul_TotalComponents;  /*!< Total number of components that have to be updated.
                                                          Only valid when update procedure is in progress, finished or failed */
} TY_API429_PACKET_UPDATE_STATUS_OUT;





/*! \brief Used for updating APX boards
 *
 * This command is used to load a R4000 executable program (S-Record format) to a
 * fixed ASP Shared Memory area via the ASP Driver Software. The S-Record ASCII
 * characters are converted from the ASP Driver Software into an executable format.
 * @param b_Module handle to board to update
 * @param b_Mode
 * - 0: Initialize download function
 * - 1: Download 'b_Cnt' S-Record characters
 * - 2: Start downloaded program from 'OFFSET' address
 * @param b_Cnt Amount of characters to download
 * @param l_Offset Address to start from
 * @param pb_SRec Array of Characters / Line from S-Record file
 * @param pb_ST Checksum Status
 * @param pl_FSize Downloaded Data Bytes.
 *
 * __Checksum Status:__
 *
 * Value | Description
 * ----- | ------------
 * 0     | Checksum ok
 * 1     | No S-Record string
 * 2     | Wrong S-Record type
 * 3     | Checksum error
 * 4     | Addressing error
 * 5     | Incorrect SREC mark detected
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429CmdLoadSRec( AiUInt8 b_Module, AiUInt8 b_Mode, AiUInt8 b_Cnt, AiUInt32 l_Offset, AiUInt8 *pb_SRec,
                                                      AiUInt8 *pb_ST, AiUInt32 *pl_FSize );


/*! \brief Program on-board Flash
 *
 * This command is used to perform in-circuit programming of the onboard Flash-
 * Prom devices for update purposes (ASP Driver Software, BIU Firmware)
 * @param b_Module handle to board to program Flash on
 * @param l_SrcAddr Source RAM Address
 * @param l_Sector Sector tp program
 * @param l_Size Number of Bytes to be programmed
 * @param pb_ST Programming Status
 *
 * __Sectors:__
 * Value    | Description
 * ---------|-------------
 * 0.253    | Flash-PROM Sector
 * 254      | Flash TCP
 * 255      | Flash ASL LCA
 *
 * __Programming Status:__
 * Value    | Description
 * ---------|-------------
 * 0        | Programming successful
 * 1        | Flash erase error
 * 2        | Flash programming error
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429CmdProgFlash( AiUInt8 b_Module, AiUInt32 l_SrcAddr, AiUInt32 l_Sector, AiUInt32 l_Size, AiUInt8 *pb_ST );


/*! \brief Copies a file from target device to host
 *
 *  This function can be used to copy files from the embedded device system to the host.
 *  \param ul_BoardHandle handle to board that file will be transferred from.
 *  \param px_UploadIn pointer to structure with the input parameters
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429FileUpload( AiUInt8 module, struct api429_file_upload_in* px_UploadIn);

/*! \brief Returns current device update process status
 *
 * This function returns the current state of a device update
 * procedure.
 * \param ul_BoardHandle handle to board to get update procedure status from
 * \param px_UpdateStatus pointer to structure that will receive the update process status
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429UpdateStatus( AiUInt8 module, struct a429_packet_update_status_out* px_UpdateStatus);

/*! \brief Start device update procedure
 *
 * This function starts the update procedure with a previously downloaded file.
 * \param ul_BoardHandle handle to board where the update procedure shall be started
 * \param updatePackageName name of the update package, that has been previously downloaded to device
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429UpdateStart( AiUInt8 module, const AiChar* updatePackageName);


/*! \brief Copies a file from host to target device
 *
 *  This function can be used to copy files from the host onto the embedded device system.
 *  \param ul_BoardHandle handle to board that file will be transferred to.
 *  \param sz_FilePath the path to the file to download. The file will be stored with basename on the embedded device
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429FileDownload( AiUInt8 module, const char* sz_FilePath);


/*! \brief Internal function for e.g. reading/writing NOVRAM
 *
 * @param b_Module
 * @param uc_InCnt
 * @param puc_OutCnt
 * @param aul_InLongs
 * @param aul_OutLongs
 * @return
 * - API_OK on success
 * - Appropriate error code, which may be used as input parameter for \ref Api429LibErrorDescGet
 */
AI_LIB_FUNC AiReturn AI_CALL_CONV Api429CmdUtility( AiUInt8 b_Module, AiUInt8 uc_InCnt, AiUInt8 *puc_OutCnt, AiUInt32 *aul_InLongs, AiUInt32 *aul_OutLongs );



AI_LIB_FUNC AiReturn AI_CALL_CONV Api429CmdIni(AiUInt8 b_Module, TY_API429_INI_INFO *px_IniPar );



#endif /* API429UPDATE_H_ */
