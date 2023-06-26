/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2019 RDK Management
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

#ifndef __WAN_HAL_H__
#define __WAN_HAL_H__

#include <stdint.h>

/**
 * @defgroup WAN_HAL WAN HAL
 *
 * @defgroup WAN_HAL_TYPES  WAN HAL Data Types
 * @ingroup  WAN_HAL
 *
 * @defgroup WAN_HAL_APIS   WAN HAL APIs
 * @ingroup  WAN_HAL
 *
 **/

/**
 * @addtogroup WAN_HAL_TYPES
 * @{
 */

#define RETURN_ERROR 1
#define RETURN_OK 0

#define BUFLEN_8 8
#define BUFLEN_32 32
#define BUFLEN_64 64

typedef enum
{
    WAN_MODE_DISABLED = 1,
    WAN_MODE_DSL_ONLY = 2,
    WAN_MODE_ETH_ONLY = 3,
    WAN_MODE_AUTO = 4
} t_eWanMode;

typedef struct 
_WAN_IPV4_CFG 
{
    char ifname[64];         // interface name (erouter0)
    char subnetmask[64];     // subnet mask
    char ipaddress[64];      // ip address to assign (192.168.0.1)
    char dnsservers[256];    // new-line separated list of servers to be added
    char defaultgateway[64]; // default gateway address

} WAN_IPV4_CFG, *PWAN_IPV4_CFG;

typedef struct
_WAN_IPV6_CFG
{
    char ifname[64];         // interface name (erouter0)
    char ipaddress[128];      // ip address to assign 
    char dnsservers[512];    // new-line separated list of servers to be added
    int  preferredlifetime;  
    int  validlifetime;

} WAN_IPV6_CFG, *PWAN_IPV6_CFG;

/*
 * The WAN_QOS_QUEUE structure needed in ccsp-wanagent and wan-hal
  */
typedef  struct
_WAN_QOS_QUEUE
{
    unsigned long       InstanceNumber;
    char                Alias[64];
    unsigned long       queueKey;
    unsigned char       queueEnable;
    char                queueStatus[256];
    char                queueInterface[256];
    unsigned long       queueWeight;
    unsigned long       queuePrecedence;
    unsigned long       REDThreshold;
    char                dropAlgorithm[256];
    char                schedulerAlgorithm[256];
    signed long         shapingRate;
    unsigned long       shapingBurstSize;
    signed long         MinBitRate;
    char                QueueName[256];
    signed long         DslLatency;
    signed long         PtmPriority;
    unsigned long       QueueId;
    unsigned long       LowClassMaxThreshold;
    unsigned long       LowClassMinThreshold;
    unsigned long       HighClassMinThreshold;
    unsigned long       HighClassMaxThreshold;
    char                L2DeviceType[32];

}WAN_QOS_QUEUE,  *PWAN_QOS_QUEUE;

/* * MAPT */
typedef  struct
_WAN_MAPT_CFG
{
    char          ifName[64];
    char          brIPv6Prefix[128];
    char          ruleIPv4Prefix[128];
    char          ruleIPv6Prefix[128];
    unsigned int  psidOffset;
    unsigned int  ratio;
    char          pdIPv6Prefix[128];

} WAN_MAPT_CFG, *PWAN_MAPT_CFG;

/**
 * Structure for SELFHEAL configuration which is required in ccsp-wanagent
 * and wan hal. */
typedef struct
_SELFHEAL_CONFIG
{
    unsigned int rebootStatus;
}
SELFHEAL_CONFIG, *PSELFHEAL_CONFIG;

/** @} */  //END OF GROUP WAN_HAL_TYPES

/**
 * @addtogroup WAN_HAL_APIS
 * @{
 */

/* wan_hal_Init() function */
/**
* @description Initialise the wan features.
*
* @param None.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
*/
int wan_hal_Init();

/* wan_hal_SetWanmode() function */
/**
* @description Set wanmode value.
*
* @param[in] mode The WANMODE value to be set.
*                   \n The possible values of the WANMODE are:
*                   \n WAN_MODE_DISABLED = 1,
*                   \n WAN_MODE_DSL_ONLY = 2,
*                   \n WAN_MODE_ETH_ONLY = 3,
*                   \n WAN_MODE_AUTO = 4.
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
*/
int wan_hal_SetWanmode(t_eWanMode mode);

/* wan_hal_SetWanConnectionEnable() function */
/**
* @description Set wanconnection enable value.
*
* @param[in] enable The WanConnectionEnable value to be set.
*                   \n The possible values of enable are:
*                   \n ENABLE : 1, DISABLE : 0.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
*/
int wan_hal_SetWanConnectionEnable(unsigned int enable);
/**
* @description Set SelfHeal Configuration to wanmanager.
*
* @param[in] pSelfHealConfig Pointer to structure that contains the configuration.
*                              \n And the only structure member is rebootStatus.
*                              \n The possible values for rebootStatus is 0 or 1.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
* @remark The caller is responsible for providing a valid memory location for the function argument.
*
*/
int wan_hal_SetSelfHealConfig(PSELFHEAL_CONFIG pSelfHealConfig);

/* wanmgr_hal_GetWanOEUpstreamCurrRate() function */
/**
* @description Get the current payload bandwidth of the upstream WANoE Connection.
*
* @param[out] pValue A pointer to an unsigned integer, where the current payload bandwidth of the upstream WANoE Connection to be updated.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
* @remark The caller is responsible for providing a valid memory location for the function argument.
*
*/
int wan_hal_GetWanOEUpstreamCurrRate(unsigned int *pValue);

/* wanmgr_hal_GetWanOEDownstreamCurrRate() function */
/**
* @description Get the current payload bandwidth of the downstream WANoE Connection.
*
* @param[out] pValue A pointer to an unsigned integer, where the current payload bandwidth of the downstream WANoE Connection to be updated.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
* @remark The caller is responsible for providing a valid memory location for the function argument.
*
*/
int wan_hal_GetWanOEDownstreamCurrRate(unsigned int *pValue);

/* wan_hal_SetQosConfiguration() function */
/**
* @description Sets the current QoS configuration.
* @param[in] pQueue A Pointer the structure which contains the QoS configurations to be set.
* <pre>
* The structure members are defined below:
*     InstanceNumber        - It is an unsigned long integer (8 bytes) that represents the instance number.
*     Alias                 - It is an array of characters (a string) with a size of 64. It stores an alias or name for the queue.
*     queueKey              - It is an unsigned long integer (8 bytes) representing a key for the queue.
*     queueEnable           - It is an unsigned char (1 byte) indicating whether the queue is enabled or disabled.
*     queueStatus           - It is an array of characters (a string) with a size of 256. It contains the status of the queue.
*     queueInterface        - It is an array of characters (a string) with a size of 256. It represents the associated interface for the queue.
*     queueWeight           - It is an unsigned long integer (8 bytes) representing the weight of the queue.
*     queuePrecedence       - It is an unsigned long integer (8 bytes) indicating the precedence of the queue.
*     REDThreshold          - It is an unsigned long integer (8 bytes) representing the RED (Random Early Detection) threshold for the queue.
*     dropAlgorithm         - It is an array of characters (a string) with a size of 256. It specifies the drop algorithm used by the queue.
*     schedulerAlgorithm    - It is an array of characters (a string) with a size of 256. It likely represents the scheduling algorithm used by the queue.
*     shapingRate           - It is a signed long integer (8 bytes) indicating the shaping rate for the queue.
*     shapingBurstSize      - It is an unsigned long integer (8 bytes) representing the burst size for the queue shaping.
*     MinBitRate            - It is a signed long integer (8 bytes) indicating the minimum bit rate for the queue.
*     QueueName             - It is an array of characters (a string) with a size of 256. It represents the name of the queue.
*     DslLatency            - It is a signed long integer (8 bytes) representing the DSL latency for the queue.
*     PtmPriority           - It is a signed long integer (8 bytes) indicating the Ptm priority for the queue.
*     QueueId               - It is an unsigned long integer (8 bytes) representing the ID of the queue.
*     LowClassMaxThreshold  - It is a unsigned long integer (8 bytes) representing MaxThreshold for low class of the queue.
*     LowClassMinThreshold  - It is a unsigned long integer (8 bytes) representing MinThreshold for low class of the queue.
*     HighClassMinThreshold - It is a unsigned long integer (8 bytes) representing MinThreshold for high class of the queue.
*     HighClassMaxThreshold - It is a unsigned long integer (8 bytes) representing MaxThreshold for high class of the queue.
*     L2DeviceType          - It is an array of characters (a string) with a size of 32. It indicates the type of Layer 2 device associated with the queue.
* </pre>
*
* @param[in] QueueNumberOfEntries The number of QoS profiles.
* @param[in] baseifname A pointer to the character array that will hold the Base interface name.
*                         \n The buffer size should be atleast 32 bytes.
* @param[in] wanifname A pointer to the character array that will hold the Wan interface name.
*                        \n The buffer size should be atleast 32 bytes.
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
* @remark The caller is responsible for providing a valid memory location for the function argument.
*
*/
int wan_hal_SetQoSConfiguration(PWAN_QOS_QUEUE pQueue, unsigned int QueueNumberOfEntries, const char* baseifname, const char* wanifname);

/* wan_hal_ConfigureIpv4() function */
/**
* @description configure IPv4 dnsservers, netmask and ip address for the required interface
*
* @param[in] pWanIpv4Cfg Pointer to the structure.
* <pre>
* The structure members are defined below:
*     ifname         -     interface name. It is a 64 byte character array.Example: erouter0.
*     subnetmask     -     subnetmask. It is a 64 byte character array.Example: 255.255.255.255.
*     ipaddress      -     ipaddress. It is a 64 byte character array.Example: 192.168.0.1.
*     dnsservers     -     list of servers to be added, separated by new-line.
*                          It is a 256 byte character array.
*     defaultgateway -     default gateway address.It is a 64 byte character array.
* </pre>
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
* @remark The caller is responsible for providing a valid memory location for the function argument.
*
*/
int wan_hal_ConfigureIpv4(PWAN_IPV4_CFG pWanIpv4Cfg);

/* wan_hal_UnConfigureIpv4() function */
/**
* @description unconfigure IPv4 dnsservers, netmask and ip address for the required interface
*
* @param[in] pWanIpv4Cfg Pointer to the structure.
* <pre>
* The structure members are defined below:
*     ifname         -     interface name. It is a 64 byte character array.Example: erouter0.
*     subnetmask     -     subnetmask. It is a 64 byte character array.Example: 255.255.255.255.
*     ipaddress      -     ipaddress. It is a 64 byte character array.Example: 192.168.0.1.
*     dnsservers     -     list of servers to be added, separated by new-line.
*                          It is a 256 byte character array.
*     defaultgateway -     default gateway address.It is a 64 byte character array.
* </pre>
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
* @remark The caller is responsible for providing a valid memory location for the function argument.
*
*/
int wan_hal_UnConfigureIpv4(PWAN_IPV4_CFG pWanIpv4Cfg);

/* wan_hal_ConfigureIpv6() function */
/**
* @description Add IPv6 address for the required interface
*
* @param[in] pWanIpv6Cfg Pointer to the structure.
* <pre>
* The structure members are defined below:
*     ifname              -     interface name. It is a 64 byte character array.Example: erouter0.
*     ipaddress           -     ipaddress. It is a 128 byte character array.
*                               Example: 2001:0db8:85a3:0000:0000:8a2e:0370:7334
*     dnsservers          -     list of servers to be added, separated by new-line.
*                               It is a 512 byte character array.
*     preferredlifetime   -     A preferred lifetime is the length of time an address is intended for full use on
*                               an interface, and must be less than or equal to the address's valid lifetime.
*                               And preferredlifetime is of int type.Example: 604800 sec.
*     validlifetime       -     The valid lifetime, which is the total time the address is available,
*                               is equal to or greater than the preferred lifetime.
*                               And validlifetime is of int type. Example: 2592000 sec.
* </pre>
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
* @remark The caller is responsible for providing a valid memory location for the function argument.
*
*/
int wan_hal_ConfigureIpv6(PWAN_IPV6_CFG pWanIpv6Cfg);

/* wan_hal_UnConfigureIpv4() function */
/**
* @description Delete IPv6 address for the required interface
*
* @param[in] pWanIpv6Cfg Pointer to the structure.
* <pre>
* The structure members are defined below:
*     ifname              -     interface name. It is a 64 byte character array.Example: erouter0.
*     ipaddress           -     ipaddress. It is a 128 byte character array.
*                               Example: 2001:0db8:85a3:0000:0000:8a2e:0370:7334
*     dnsservers          -     list of servers to be added, separated by new-line.
*                               It is a 512 byte character array.
*     preferredlifetime   -     A preferred lifetime is the length of time an address is intended for full use on
*                               an interface, and must be less than or equal to the address's valid lifetime.
*                               And preferredlifetime is of int type.Example: 604800 sec.
*     validlifetime       -     The valid lifetime, which is the total time the address is available,
*                               is equal to or greater than the preferred lifetime.
*                               And validlifetime is of int type. Example: 2592000 sec.
* </pre>
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
* @remark The caller is responsible for providing a valid memory location for the function argument.
*
*/
int wan_hal_UnConfigureIpv6(PWAN_IPV6_CFG pWanIpv6Cfg);

/* wan_hal_EnableMapt() function */
/**
* @description Enable MAPT for the required interface
*
* @param[in] pMAPTCfg Pointer to the structure.
* <pre>
* The structure members are defined below:
*     ifname              -     interface name. It is a 64 byte character array.Example: erouter0.
*     brIPv6Prefix        -     Is an array of characters (a string) with a size of 128. It stores an IPv6 prefix for bridging.
*     ruleIPv4Prefix      -     Is an array of characters (a string) with a size of 128. It holds an IPv4 prefix for some rule.
*     ruleIPv6Prefix      -     Is an array of characters (a string) with a size of 128. It contains an IPv6 prefix for a rule.
*     psidOffset          -     Is an unsigned integer (4 bytes) that represents the offset value for a Port Set Identifier (PSID).
*     ratio               -     Is an unsigned integer (4 bytes) representing a ratio.
*     pdIPv6Prefix        -     Is an array of characters (a string) with a size of 128. It stores an IPv6 prefix for prefix delegation.
* </pre>
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
* @remark The caller is responsible for providing a valid memory location for the function argument.
*
*/
int wan_hal_EnableMapt( PWAN_MAPT_CFG pMAPTCfg );

/* wan_hal_DisableMapt() function */
/**
* @description Disable MAPT for the required interface
*
* @param[in] ifName It is a pointer to a constant character array (string) named ifName.
*                  \n This parameter represents the name of the interface on which the MAP-T feature is to be disabled.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
* @remark The caller is responsible for providing a valid memory location for the function argument.
*
*/
int wan_hal_DisableMapt(const char* ifName);

/**
 * @description Set/Reset WanOE mode based on the enable flag. If it is
 * true, update the boardparam to set WAN_ETH_MODE in the CPE. Else disabled
 * the WAN_ETH_MODE and reclaim ethernet port.
 * @param[in] enable It is an unsigned char type named enable, used to control the enabling or disabling of the WAN OE mode.
 *                 \n The use of the const qualifier indicates that the parameter value will not be modified within the function.
 */
int wan_hal_enableWanOEMode(const unsigned char enable);

/**
 * @description Get authentication information like ADSL username and password.
 * @param[out] autInfo to hold the authentication data.
 *          \n It is a pointer to a character array (string) named authInfo.
 *          \n This parameter is used to pass a buffer or memory location where the authentication information will be stored.
 * @retval RETURN_OK if successful else RETURN_ERR.
 * @remark The caller is responsible for providing a valid memory location for the function argument.
 */
int wan_hal_getAuthInfo(char *authInfo);

/** @} */  //END OF GROUP WAN_HAL_APIS
#endif /* __WAN_HAL_H__ */
