/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2022 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#ifndef _LPA_HAL_H_
#define _LPA_HAL_H_

/**********************************************************************
                STRUCTURE AND CONSTANT DEFINITIONS
**********************************************************************/

#define RETURN_ERROR        (-1)
#define RETURN_OK           (0)

#ifndef TRUE
#define TRUE                (1)
#endif

#ifndef FALSE
#define FALSE               (0)
#endif


typedef enum _Cellular_PreferredUICC_t
{
    CELLULAR_UICC_USIM     = 0,
    CELLULAR_UICC_ESIM,

} CellularPreferredUICC_t;

typedef enum _CellularDeviceSimStatus_t
{
   SIM_PREPARATION_PENDING = 1,
   SIM_PREPARATION_INPROGRESS,
   SIM_PREPARATION_DOWNLOADED,                                
   SIM_PREPARATION_DONE,

} CellularDeviceSimStatus_t;

/*
*  This struct is for esim profile object.
*/
typedef  struct                                     
{
    char iccid[32];
    int  profileState;
    char profileName[16];
} eSIMProfileStruct;


/**********************************************************************
                FUNCTION PROTOTYPES
**********************************************************************/
/* cellular_sim_download_progress callback  function */
/**
* @description - This callback sends to upper layer about the download progress 
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/
typedef int (*cellular_sim_download_progress_callback)( char *progress );


/* cellular_esim_download_profile_with_activationcode() function */
/**
* @description - Downloads the profile with activation code 
*
* @return The status of the operation
* @retval TRUE if modem device presents
* @retval FALSE if modem device not presents
*
*/
int cellular_esim_download_profile_with_activationcode(char* ActivationCodeStr, cellular_sim_download_progress_callback download_progress);

/*  cellular_esim_download_profile_from_smds() function */
/**
* @description - Downloads the profile from smds 
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/
int cellular_esim_download_profile_from_smds(char* smds);

/*  cellular_esim_download_profile_from_defaultsmdp() function */
/**
* @description - Downloads the profile from default SMDP 
*
* @param[in] smdp   - smdp address .
*                                              
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/
int cellular_esim_download_profile_from_defaultsmdp(char* smdp);

/*  cellular_esim_get_profile_info() function */
/**
* @description - Gets the list of MNO pfofiles on eSIM 
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/

int cellular_esim_get_profile_info(eSIMProfileStruct **profile_list, int *nb_profiles);

/*  cellular_esim_enable_profile() function */
/**
* @description - enable mno profile with matching ICCID 
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/
int cellular_esim_enable_profile(char* iccid, int iccid_size);

/*  cellular_esim_disable_profile() function */
/**
* @description - disable mno profile with matching ICCID 
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/

int cellular_esim_disable_profile(char* iccid, int iccid_size);

/*  cellular_esim_delete_profile() function */
/**
* @description - delete mno profile with matching ICCID
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/
int cellular_esim_delete_profile(char* iccid, int iccid_size);

/*  cellular_esim_lpa_init() function */
/**
* @description - init the lpa module --setup LPA SDK parameters
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/
int cellular_esim_lpa_init(void);

/*  cellular_esim_lpa_exit function */
/**
* @description - cleanup the  lpa module
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/
int cellular_esim_lpa_exit(void);

#endif //_LPA_HAL_H_
