/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
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

/**
* @file vlan_hal.h
* @author zhicheng_qiu@cable.comcast.com
* @brief For CCSP Component:  VLAN_Provisioning_and_management
*
* @description This file gives the function prototypes used for the RDK-Broadband
* VLAN abstraction layer
*/

/**********************************************************************

    module: vlan_hal.h

        For CCSP Component:  VLAN_Provisioning_and_management

    ---------------------------------------------------------------

    description:

        This header file gives the function call prototypes and
        structure definitions used for the RDK-Broadband
        VLAN abstraction layer

    ---------------------------------------------------------------

    environment:

        This HAL layer is intended to support VLAN drivers
        through the System Calls.

    ---------------------------------------------------------------

    author:

	zhicheng_qiu@cable.comcast.com

**********************************************************************/

#ifndef __VLAN_HAL_H__
#define __VLAN_HAL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef BOOL
#define BOOL  unsigned char
#endif

#ifndef CHAR
#define CHAR  char
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef INT
#define INT   int
#endif

#ifndef UINT
#define UINT  unsigned int
#endif

#ifndef TRUE
#define TRUE     1
#endif

#ifndef FALSE
#define FALSE    0
#endif

#ifndef ENABLE
#define ENABLE   1
#endif

#ifndef RETURN_OK
#define RETURN_OK   0
#endif

#ifndef RETURN_ERR
#define RETURN_ERR   -1
#endif

/**
 * @defgroup VLAN_HAL Virtual LAN HAL
 *
 * VLAN HAL layer is intended to support VLAN drivers through the System Calls.
 *
 * @defgroup VLAN_HAL_TYPES  VLAN HAL Data Types
 * @ingroup  VLAN_HAL
 *
 * @defgroup VLAN_HAL_APIS   VLAN HAL APIs
 * @ingroup  VLAN_HAL
 *
 **/

/**
 * @addtogroup VLAN_HAL_TYPES
 * @{
 */

//defines for HAL version 1.0
#define VLAN_HAL_MAJOR_VERSION 1        /**< This is the major verion of this HAL. */
#define VLAN_HAL_MINOR_VERSION 0        /**< This is the minor verson of the HAL. */
#define VLAN_HAL_MAINTENANCE_VERSION 1  /**< This is the maintenance version of the HAL. */

//defines for charecter length for VLAN configurartion
#define VLAN_HAL_MAX_VLANGROUP_TEXT_LENGTH             32
#define VLAN_HAL_MAX_VLANID_TEXT_LENGTH                32
#define VLAN_HAL_MAX_INTERFACE_NAME_TEXT_LENGTH        32

#define VLAN_HAL_MAX_LINE_BUFFER_LENGTH                120

/**********************************************************************
                ENUMERATION DEFINITIONS
**********************************************************************/

/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/

// Structure for VLANID Maintainance
typedef struct _vlan_vlanidconfiguration
{
     char groupName[VLAN_HAL_MAX_VLANGROUP_TEXT_LENGTH];
     char vlanID[VLAN_HAL_MAX_VLANID_TEXT_LENGTH];
     struct _vlan_vlanidconfiguration *nextlink;

} vlan_vlanidconfiguration_t;

/** @} */  //END OF GROUP VLAN_HAL_TYPES

/**********************************************************************
 *
 *  VLAN HAL function prototypes
 *
***********************************************************************/

/**
 * @addtogroup VLAN_HAL_APIS
 * @{
 */

/**
* @description This HAL utility is used to create an new vlan group, and assign default vlanID.
* @param[in] groupName A pointer to a constant character string (const char *).
*                      \n It represents the bridge name for the VLAN group.
*                      \n The buffer size shouldn't exceed 64 bytes.
*                      \n The values are : brlan0, brlan1, brlan2, brlan3, brlan4, brlan5, brlan7, brlan10, brlan106, brlan403, brlan112, brlan113, brebhaul.
* @param[in] default_vlanID A pointer to a constant character string (const char *).
*                      \n It represents the default VLANID to be asThe buffer size shouldn't exceed 16 bytes.igned to the VLAN group.
*                      \n The buffer size shouldn't exceed 5 bytes.
*                      \n The valid VLAN IDs range from 1 to 4094.
*
* @return The status of the operation.
* @retval RETURN_OK if successful (or) return RETURN_OK If group is already exist and has expected vlanID.
* @retval RETURN_ERR if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int vlan_hal_addGroup(const char *groupName, const char *default_vlanID);

/**
* @description This HAL utility is used to delete existing vlan group, and delete correspond interface association.
* @param[in] groupName A pointer to a constant character string (const char *).
*                      \n It represents the bridge name associated with the VLAN group to be deleted.
*                      \n The buffer size shouldn't exceed 64 bytes.
*                      \n The values are : brlan0, brlan1, brlan2, brlan3, brlan4, brlan5, brlan7, brlan10, brlan106, brlan403, brlan112, brlan113, brebhaul.
*
* @return The status of the operation.
* @retval RETURN_OK if successful (or) RETURN_OK If group is not exist.
* @retval RETURN_ERR if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int vlan_hal_delGroup(const char *groupName);

/**
* @description This HAL utility is used to add interface to existing vlan group, and assign the vlanID.
* @param[in] groupName A pointer to a constant character string (const char *). The name of the VLAN group to which the interface will be added.
*                   \n A string representing the bridge name to which the interface will be added.
*                   \n The buffer size shouldn't exceed 64 bytes.
*                   \n The values are : brlan0, brlan1, brlan2, brlan3, brlan4, brlan5, brlan7, brlan10, brlan106, brlan403, brlan112, brlan113, brebhaul.
* @param[in] ifName A pointer to a constant character string (const char *). The name of the network interface (e.g., "eth0") to be added to the VLAN group.
*                   \n It is vendor specific.
*                   \n A string representing the name of the interface that will be added to the VLAN group.
*                   \n The buffer size shouldn't exceed 64 bytes.
* @param[in] vlanID A pointer to a constant character string (const char *). The VLAN ID (as a string) to be assigned to the interface within the VLAN group. The VLAN ID should be a numerical value.
*                   \n A string representing the VLAN ID that will be assigned to the interface within the VLAN group.
*                   \n The buffer size shouldn't exceed 5 bytes.
*                   \n The valid VLAN IDs range from 1 to 4094.
*
* @return The status of the operation.
* @retval RETURN_OK if successful (or) RETURN_OK If interface is already in group, and has expected vlan ID.
* @retval RETURN_ERR if group is not exist (or) if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int vlan_hal_addInterface(const char *groupName, const char *ifName, const char *vlanID);

/**
* @description This HAL utility is used to deassociate existing interface from group.
* @param[in] groupName A pointer to a constant character string (const char *). The name of the VLAN group from which the interface will be removed.
*                   \n A string representing the bridge name from which the interface will be deassociated.
*                   \n The buffer size shouldn't exceed 64 bytes.
*                   \n The values are : brlan0, brlan1, brlan2, brlan3, brlan4, brlan5, brlan7, brlan10, brlan106, brlan403, brlan112, brlan113, brebhaul.
* @param[in] ifName A pointer to a constant character string (const char *). The name of the network interface (e.g., "eth0") to be removed from the VLAN group.
*                   \n It is vendor specific.
*                   \n A string representing the name of the interface that will be deassociated from the VLAN group.
*                   \n The buffer size shouldn't exceed 64 bytes.
* @param[in] vlanID A pointer to a constant character string (const char *). The VLAN ID (as a string) associated with the interface within the VLAN group. The VLAN ID should be a numerical value.
*                   \n A string representing the VLAN ID associated with the interface in the VLAN group.
*                   \n The buffer size shouldn't exceed 5 bytes.
*                   \n The valid VLAN IDs range from 1 to 4094.
*
* @return The status of the operation.
* @retval RETURN_OK if successful (or) RETURN_OK If interface is not exist.
* @retval RETURN_ERR if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int vlan_hal_delInterface(const char *groupName, const char *ifName, const char *vlanID);

/**
* @description This HAL utility is used to dump the particular group setting, for debug purpose.
* @param[in] groupName A pointer to a constant character string (const char *).
*                      \n A string representing the bridge name for which the settings will be dumped.
*                      \n The buffer size shouldn't exceed 64 bytes.
*                      \n The values are : brlan0, brlan1, brlan2, brlan3, brlan4, brlan5, brlan7, brlan10, brlan106, brlan403, brlan112, brlan113, brebhaul.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int vlan_hal_printGroup(const char *groupName);


/**
* @description This HAL utility is used dump all group setting, for debug purpose.
* @param None.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int vlan_hal_printAllGroup();

/**
* @description This HAL utility is used to deassociate all existing interface from group.
* @param[in] groupName A pointer to a constant character string (const char *).
*                      \n A string representing the bridge name from which all interfaces will be deassociated.
*                      \n The buffer size shouldn't exceed 64 bytes.
*                      \n The values are : brlan0, brlan1, brlan2, brlan3, brlan4, brlan5, brlan7, brlan10, brlan106, brlan403, brlan112, brlan113, brebhaul.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.
*
*/

int vlan_hal_delete_all_Interfaces(const char *groupName);

/**
* @description This HAL utility is used identify given bridge available in linux bridge.
* @param[in] br_name It is a pointer to a character array (string) named br_name.
*              \n A string representing the name of the bridge that will be checked for availability in the Linux bridge.
*              \n The buffer size shouldn't exceed 64 bytes.
*              \n The values are : brlan0, brlan1, brlan2, brlan3, brlan4, brlan5, brlan7, brlan10, brlan106, brlan403, brlan112, brlan113, brebhaul.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.
*
*/

int _is_this_group_available_in_linux_bridge(char * br_name);

/**
* @description This HAL utility is used identify given interface available in anyone of linux bridge.
* @param[in] if_name It is a pointer to a character array (string) named if_name. The name of the network interface to be checked.
*                 \n A string representing the name of the interface that will be checked for availability in any Linux bridge.
*                 \n The buffer size shouldn't exceed 64 bytes.
*                 \n It is vendor specific.
*
* @param[in] vlanID It is a pointer to a character array (string) named vlanID.
*                   \n A string representing the VLAN ID associated with the interface.
*                   \n The buffer size shouldn't exceed 5 bytes.
*                   \n The valid VLAN IDs range from 1 to 4094.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.
*
*/

int _is_this_interface_available_in_linux_bridge(char * if_name, char *vlanID);

/**
* @description This HAL utility is used identify given interface available in given linux bridge.
* @param[in] if_name It is a pointer to a character array (string) named if_name.
*                 \n A string representing the name of the interface that will be checked for availability in given bridge.
*                 \n The buffer size shouldn't exceed 64 bytes.
*                 \n It is vendor specific.
* @param[in] br_name It is a pointer to a character array (string) named br_name.
*                 \n A string representing the name of the bridge from which availability of interface is checked.
*                 \n The buffer size shouldn't exceed 64 bytes.
*                 \n The values are : brlan0, brlan1, brlan2, brlan3, brlan4, brlan5, brlan7, brlan10, brlan106, brlan403, brlan112, brlan113, brebhaul.
* @param[in] vlanID It is a pointer to a character array (string) named vlanID.
*                 \n A string representing the VLAN ID associated with the interface.
*                 \n The buffer size shouldn't exceed 5 bytes.
*                 \n The valid VLAN IDs range from 1 to 4094.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.
*
*/

int _is_this_interface_available_in_given_linux_bridge(char * if_name, char * br_name,char *vlanID);

/**
* @description This HAL utility is used get the buffer from shell output.
* @param[in] cmd A string representing the Linux shell command that will be executed to obtain the desired output. It will execute and get the buffer from shell output based on given command.
* @param[out] out A character array (string) where the output of the input cmd will be copied.
* @param[out] len length of the output string.
*                 \n The maximum output length is 120.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.
*
*/

void _get_shell_outputbuffer(char * cmd, char * out, int len);

/**
* @description This HAL utility is used get the buffer from shell output.
* @param[in] fp It is a pointer to a FILE object.
* @param[out] out A character array (string) where the output of the input cmd will be copied.
* @param[out] len length of the output string.
*                 \n The maximum output length is 120.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.
*
*/

void _get_shell_outputbuffer_res(FILE *fp, char * out, int len);

/**
* @description This HAL utility is used store the VLAN ID, Group Name configuration.
* @param[in] groupName It is a pointer to a character array (string) named groupName.
*                      \n It represents the bridge name or group name that needs to be added to VLAN configuration entry.
*                      \n The buffer size shouldn't exceed 64 bytes.
*                      \n The values are : brlan0, brlan1, brlan2, brlan3, brlan4, brlan5, brlan7, brlan10, brlan106, brlan403, brlan112, brlan113, brebhaul.
* @param[in] vlanID It is a pointer to a character array (string) named vlanID.
*                 \n It represents the vlanID that needs to be added to VLAN configuration entry.
*                 \n The buffer size shouldn't exceed 5 bytes.
*                 \n The valid VLAN IDs range from 1 to 4094.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.
*
*/

int insert_VLAN_ConfigEntry(char *groupName, char *vlanID);

/**
* @description This HAL utility is used delete the VLAN ID, Group Name configuration
* @param[in] groupName It is a pointer to a character array (string) named groupName.
*                      \n It represents the bridge name or group name that needs to be deleted from VLAN configuration entry.
*                      \n The buffer size shouldn't exceed 64 bytes.
*                      \n The values are : brlan0, brlan1, brlan2, brlan3, brlan4, brlan5, brlan7, brlan10, brlan106, brlan403, brlan112, brlan113, brebhaul.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.
*
*/

int delete_VLAN_ConfigEntry(char *groupName);


/**
* @description This HAL utility is used get the VLAN ID for corresponding Group Name from link
* @param[in] groupName A pointer to a constant character string (const char *).
*                      \n It represents the bridge name or group name that needs to be deleted from VLAN configuration entry.
*                      \n The buffer size shouldn't exceed 64 bytes.
*                      \n The values are : brlan0, brlan1, brlan2, brlan3, brlan4, brlan5, brlan7, brlan10, brlan106, brlan403, brlan112, brlan113, brebhaul.
* @param[out] vlanID It is a pointer to a character array (string) named vlanID.
*                 \n It represents the vlanID that will get update in the function .
*                 \n The buffer size should be atleast 5 bytes.
*                 \n The valid VLAN IDs range from 1 to 4094.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.
*
*/

int get_vlanId_for_GroupName(const char *groupName, char *vlanID);

/**
* @description This HAL utility is used to print all the VLAN ID configuration.
* @param None.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.
*
*/

int print_all_vlanId_Configuration(void);

/** @} */  //END OF GROUP VLAN_HAL_APIS

/*
Example usage on Puma6 platfom:
        Private network group (vlan100)
                brlan0      eth_1(external swith port 1), eth_2(port 2), eth_3(port 3),  MoCA.100 (MoCA vlan100),  ath0(2.4G vlan100), ath1 (5G vlan100)

vlan_hal_addGroup("brlan0", "100");                //brctl addbr brlan0
vlan_hal_addInterface("brlan0", "l2sd0", NULL);    //vconfig add l2sd0 100; brctl addif brlan0 l2sd0.100


        Xfinity Home VLAN (vlan101)
                brlan1      eth_4(port 4),  MoCA.101(MoCA vlan101), ath2(2.4G vlan101), ath3 (5G vlan101)

vlan_hal_addGroup("brlan1", "101");                //brctl addbr brlan1
vlan_hal_addInterface("brlan1", "l2sd0", NULL);    //vconfig add l2sd0 100; brctl addif brlan1 l2sd0.101


        Xfinity Wifi VLAN 2.4G (vlan102)
                brlan2     gretap0.102 (GRE vlan102),  MoCA.102(MoCA vlan102), ath4(2.4G vlan102)

vlan_hal_addGroup("brlan2", "102");                //brctl addbr brlan2
vlan_hal_addInterface("brlan2", "l2sd0", NULL);    //vconfig add l2sd0 102; brctl addif brlan1 l2sd0.102
vlan_hal_addInterface("brlan2", "gretap0", NULL);  //vconfig add gretap0 102; brctl addif brlan1 gretap0.102


        Xfinity Wifi VLAN 5G (vlan103)
                brlan3     gretap0.103 (GRE vlan103),  MoCA.103(MoCA vlan103), ath5(2.4G vlan103)

vlan_hal_addGroup("brlan3", "103");                //brctl addbr brlan3
vlan_hal_addInterface("brlan3", "l2sd0", NULL);    //vconfig add l2sd0 103; brctl addif brlan1 l2sd0.103
vlan_hal_addInterface("brlan3", "gretap0", NULL);  //vconfig add gretap0 103; brctl addif brlan1 gretap0.103

*/
#endif /*__VLAN_HAL_H__*/
