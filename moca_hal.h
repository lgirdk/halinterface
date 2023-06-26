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

/**********************************************************************
   Copyright [2014] [Cisco Systems, Inc.]
 
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
 
       http://www.apache.org/licenses/LICENSE-2.0
 
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
**********************************************************************/

/**********************************************************************

    module: moca_hal.h

        For CCSP Component:  MoCA_Provisioning_and_management

    ---------------------------------------------------------------

    description:

        This header file gives the function call prototypes and 
        structure definitions used for the RDK-Broadband 
        MoCA hardware abstraction layer
        
    ---------------------------------------------------------------

    environment:

        This HAL layer is intended to support MoCA drivers 
        through an open API.  The current implementation created
        below this HAL supports MoCA.
        Changes may be needed to support other MoCA enviornments.

    ---------------------------------------------------------------

    author:

        Cisco

**********************************************************************/

#ifndef __MOCA_HAL_H__
#define __MOCA_HAL_H__


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

#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS     0
#endif

#ifndef STATUS_FAILURE
#define STATUS_FAILURE     -1
#endif

#ifndef STATUS_NOT_AVAILABLE
#define STATUS_NOT_AVAILABLE     -2
#endif

/**
* @defgroup MOCA_HAL MoCA HAL
*
* MoCA HAL is an abstraction layer, mainly for interacting with MoCA driver.
*
* @defgroup MOCA_HAL_TYPES  MOCA HAL Data Types
* @ingroup  MOCA_HAL
*
* @defgroup MOCA_HAL_APIS   MOCA HAL  APIs
* @ingroup  MOCA_HAL
*
**/

/**
 * @addtogroup MOCA_HAL_TYPES
 * @{
 */

#define kMoca_MaxCpeList		256
#define kMoca_MaxMocaNodes              16
#define MAC_PADDING			12 /**< RDKB expects 6 byte MAC, padding required for platforms handling as 18 bytes MAC */

#define STATUS_INPROGRESS   -1 /**< If ACA process already running */
#define STATUS_NO_NODE      -2 /**< If specified NODE not exist */
#define STATUS_INVALID_PROBE    -3 /**< If HAL API called with invalid probe TYPE */
#define STATUS_INVALID_CHAN     -4 /**< If HAL API called with invalid channel */

/**********************************************************************
                ENUMERATION DEFINITIONS
**********************************************************************/
#ifndef MOCA_VAR
typedef enum 
{
    IF_STATUS_Up               = 1,
    IF_STATUS_Down,
    IF_STATUS_Unknown,
    IF_STATUS_Dormant,
    IF_STATUS_NotPresent,
    IF_STATUS_LowerLayerDown,
    IF_STATUS_Error
} moca_if_status_t;
#endif

typedef enum
{
    PROBE_QUITE = 0,
    PROBE_EVM
}PROBE_TYPE;

#if 0
typedef enum
{
    STAT_SUCCESS =0,
    STAT_FAIL_BADCHANNEL,
    STAT_FAIL_NOEVMPROBE,
    STAT_FAIL,
    STAT_INPROGRESS
}ACA_STATUS;
#endif
/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/
typedef struct {
    ULONG                           InstanceNumber; /**< Instance Number when Multiple MoCA interfaces exist. 0 - In the case of only one interface. */
    CHAR                            Alias[64]; /**< Set the Alias Name for the interface */
    BOOL                            bEnabled; /**< Enable/Disable the interface. */
    BOOL                            bPreferredNC; /**< Enable/Disable the Node's preference to be Network Coordinator */
    BOOL                            PrivacyEnabledSetting; /**< Enable/Disable Link Privacy. A Password is required when Privacy is enabled */
    UCHAR                           FreqCurrentMaskSetting[128]; /**< Set of Frequencies that should be used for forming network (bitmask) */
    CHAR                            KeyPassphrase[18]; /**< Privacy Password. This field is valid only if the Link Privacy is enabled. */
    INT                             TxPowerLimit; /**< Maximum Transmission Power allowed */
    ULONG                           AutoPowerControlPhyRate; /**< AutoPowerControlPhyRate: PowerCtrlPhyTarget Used as a reference to achieve the PHY rate by adjusting  power. */
    ULONG                           BeaconPowerLimit; /**< Maximum Transmission Power Allowed when transmitting Beacons */
    ULONG                           MaxIngressBWThreshold; /**< Maximum Ingress Bandwidth Thresholds */
    ULONG                           MaxEgressBWThreshold; /**< Maximum Egress Bandwidth Thresholds */
    BOOL                            Reset; /**< Reset MoCA Configuration Parameters to Defaults */
    BOOL                            MixedMode; /**< Enable/Disable the Node to operate in mixed mode (1.0/1.1/2.0 versions).
                i.e Enable backward compatibility on the MoCA Protocol Versions. */
    BOOL                            ChannelScanning; /**< Enable/Disable the Node to operate in single frequency mode or scanning mode. */
    BOOL                            AutoPowerControlEnable; /**< Enable/Disable adjusting Power to achieve the Target PHY rate */
    BOOL                            EnableTabooBit; /**< Enable/Disable the Node to support Taboo Mask */
    UCHAR                           NodeTabooMask[128]; /**< Set of Frequencis to Avoid (bitmask) */
    UCHAR                           ChannelScanMask[128]; /**< Set of Frequencies to Scan for Beacons to form network (bitmask).
                Very often, this is same as FreqCurrentMaskSetting. */
} moca_cfg_t;

typedef struct {
	/**< Interface Name (for example: moca0) */
    CHAR                            Name[64];           /**< Uniquely identifying the entry */
    UCHAR                           MacAddress[6 + MAC_PADDING]; /**< MAC Address of the Local Node */
    CHAR                            FirmwareVersion[64]; /**< Firmware Version of the MoCA Firmware */
    ULONG                           MaxBitRate; /**< Maximum PHY Rate that the Node can support */
    CHAR                            HighestVersion[64]; /**< Highest Version of the MoCA Protocol that the Local Node Supports */
    UCHAR                           FreqCapabilityMask[8]; /**< Frequencies that the Local Node supports (bitmask) */
    UCHAR                           NetworkTabooMask[128]; /**< Frequencies that the Local Node does not support (bitmask) */
    ULONG                           TxBcastPowerReduction; /**< Beacon Backoff in dB */
    BOOL                            QAM256Capable; /**< Local Node is QAM-256 Capable or Not */
    BOOL                           PacketAggregationCapability; /**< Local Node can aggregate Ethernet Packets for MoCA PDU transfers */
} moca_static_info_t;

#ifndef MOCA_VAR
typedef struct {
	/**< Current Status of the LoCAL Interface (Up/Down etc.) */
    moca_if_status_t                Status;
    ULONG                           LastChange; /**< Last Link Status Change (Up/Down/ etc.) */
    ULONG                           MaxIngressBW; /**< Maximum Ingress Bandwidth reached */
    ULONG                           MaxEgressBW; /**< Maximum Egress Bandwidth reached */
    CHAR                            CurrentVersion[64]; /**< Current Operating MoCA Protocol Version Valid Values: 1.0, 1.1, 2.0 */
    ULONG                           NetworkCoordinator; /**< Node ID of the Network Coordinator.
                Valid Values: 0-7 (Protocol: 1.0)
                Valid Values: 0-15 (Protocol: 1.1, 2.0) */
    ULONG                           NodeID; /**< Node ID of the Local Node.
                Valid Values: 0-7 (Protocol: 1.0)
                Valid Values: 0-15 (Protocol: 1.1, 2.0) */
    ULONG                           BackupNC; /**< Node ID of the Backup Network Coordinator
                Valid Values: 0-7 (Protocol: 1.0)
                Valid Values: 0-15 (Protocol: 1.1, 2.0) */
    BOOL                            PrivacyEnabled; /**< If Privacy is enabled on the network */
    UCHAR                           FreqCurrentMask[8]; /**< This should be same as the Configured Frequencies that the Node can operate */
    ULONG                           CurrentOperFreq; /**< The Current Frequency on which the Node formed the Network */
    ULONG                           LastOperFreq; /**< The Last Operating Frequency on which the Node formed the Network earlier */
    ULONG                           TxBcastRate; /**< Transmission Broadcast Rate */
    BOOL                            MaxIngressBWThresholdReached; /**< Flag Indicating that the Ingress Bandwidth reached the Maximum Threshold Set */
    BOOL                            MaxEgressBWThresholdReached; /**< Flag Indicating that the Egress Bandwidth reached the Maximum Threshold Set */
    ULONG                           NumberOfConnectedClients; /**< Number of Nodes on the MoCA Network
                - Cannot exceed the maximum supported by MoCA Protocol. */
    CHAR                            NetworkCoordinatorMACAddress[18]; /**< Network Coordinator MAC Address */
    ULONG                           LinkUpTime; /**< Indicate  the length of time this node has been connected to the MoCA network with at least one other node */


} moca_dynamic_info_t;
#endif

typedef struct {
    ULONG                           BytesSent; /**< Number of Bytes Sent & Received */
    ULONG                           BytesReceived; /**< Number of Bytes Sent & Received */

    ULONG                           PacketsSent; /**< Number of Packets Sent & Received */
    ULONG                           PacketsReceived; /**< Number of Packets Sent & Received */

    ULONG                           ErrorsSent; /**< Number of Errors in Sent & Received Packets */
    ULONG                           ErrorsReceived; /**< Number of Errors in Sent & Received Packets */

    ULONG                           UnicastPacketsSent; /**< Number of Unicast Packets Sent */
    ULONG                           UnicastPacketsReceived; /**< Number of Unicast Packets Received */

    ULONG                           DiscardPacketsSent; /**< Number of Packets Discard (Tx side) */
    ULONG                           DiscardPacketsReceived; /**< Number of Packets Discard (Rx side) */

    ULONG                           MulticastPacketsSent; /**< Number of Multicast Packets Sent */
    ULONG                           MulticastPacketsReceived; /**< Number of Multicast Packets Received */

    ULONG                           BroadcastPacketsSent; /**< Number of Broadcast Packets Sent */
    ULONG                           BroadcastPacketsReceived; /**< Number of Broadcast Packets Received */

    ULONG                           UnknownProtoPacketsReceived; /**< Number of Unknown Protocol Packets Received */

    ULONG                           ExtAggrAverageTx; /**< Aggregate Averages of Packet Counts (Tx) */
    ULONG                           ExtAggrAverageRx; /**< Aggregate Averages of Packet Counts (Rx) */
} moca_stats_t;


typedef struct {
    ULONG                           Map; /**< Number of MAP packets */
    ULONG                           Rsrv; /**< Number of Reservation Request Packets */
    ULONG                           Lc; /**< Number of Link Control Packets */
    ULONG                           Adm; /**< Number of Admission Request Packets */
    ULONG                           Probe; /**< Number of Probes */
    ULONG                           Async; /**< Number of Beacons */
} moca_mac_counters_t;

typedef struct {
    ULONG                           Tx; /**< Aggregate Tx Payload Data Units (Not MoCA Control Packets). */
    ULONG                           Rx; /**< Aggregate Rx Payload Data Units (Not MoCA Control Packets). */
} moca_aggregate_counters_t;

typedef struct {
    CHAR                            mac_addr[6]; /**< MAC Address of the Node */
} moca_cpe_t;

typedef struct {
	/**< This Data Structure corresponds to information of 
		the associated device on the network. The term 
		'this Node' pertains to that particulard device for
		which the information in this data structure is 
		valid */ 

    UCHAR                           MACAddress[6 + MAC_PADDING]; /**< MAC Address of the Associated Device */
    ULONG                           NodeID; /**< Node ID of the Associated Device */
    BOOL                            PreferredNC; /**< Whether this Node is a Preferred NC. */
    CHAR                            HighestVersion[64]; /**< Highest MoCA Protocol Version that this Node supports */
    ULONG                           PHYTxRate; /**< Tx PHY Rate of this Node */
    ULONG                           PHYRxRate; /**< Rx PHY Rate of this Node */
    ULONG                           TxPowerControlReduction; /**< Tx Power Reduced by this Node */
    INT                             RxPowerLevel; /**< Rx Power Level read by this Node */
    ULONG                           TxBcastRate; /**< Tx Broadcast PHY Rate */
    INT                             RxBcastPowerLevel; /**< Rx Broadcast Power Level read by this Node */
    ULONG                           TxPackets; /**< Number of Transmitted Packets from this Node */
    ULONG                           RxPackets; /**< Number of Recieved Packets by this Node */
    ULONG                           RxErroredAndMissedPackets; /**< Number of (Rx) Error or Missed Packets by this Node */
    BOOL                            QAM256Capable; /**< Flag if this Node is capable of QAM-256 */
    BOOL                            PacketAggregationCapability; /**< Flag if this Node is capable of Packet Aggregation */
    ULONG                           RxSNR; /**< Receive Signal to Noise Ration */
    BOOL                            Active; /**< Flag if this Node is Active */
    ULONG                           RxBcastRate; /**< Recevie Broadcast PHY Rate */
    ULONG                           NumberOfClients; /**< Number of Clients connected to this Node */
} moca_associated_device_t;

#ifndef MOCA_VAR
typedef struct {
    /**< This data structure represents teh MoCA mesh PHY rate table.
       This table contains the unicast transmit PHY rate between all
       pair of nodes in the MoCA Network.*/
    
    ULONG                           RxNodeID; /**< The node ID of the receive MoCA node is used as one of the
    index to order the mesh PHY rate table. */

    ULONG                           TxNodeID; /**< The node ID of the transmit MoCA node is used as one of the
    index to order the mesh PHY rate table. */

    ULONG                           TxRate; /**< Indicate the transmit PHY rate in Mbps from the MoCA node
    identified by 'mocaMeshTxNodeIndex' to the MoCA node identified by 'mocaMeshRxNodeIndex'. */

    ULONG                           TxRateNper; /**< Only for MoCA 2.x */
    ULONG                           TxRateVlper; /**< Only for MoCA 2.x */

} moca_mesh_table_t;
#endif

typedef struct {
    /**< This Data Structure respresents the MoCA interface flow statistics
       table.  This table provides statistics of ingress PQoS flow in the
       MoCA interface. */ 

    ULONG                           FlowID; /**< Indicate the flow ID of a PQoS flow. */
    ULONG                           IngressNodeID; /**< Indicate the flow ID of a Ingress PQoS flow. */
    ULONG                           EgressNodeID; /**< Indicate the flow ID of a Egress PQoS flow. */
    ULONG                           FlowTimeLeft; /**< Indicate the LEASE_TIME_LEFT of the PQoS flow identified by
    'mocaIfFlowID' in which this MoCA interface is an ingress node for this PQoS flow. */
    char                            DestinationMACAddress[18]; /**< Indicate the Destination Address (DA) of Ethernet packets of
    the PQoS Flow for which this node is the ingress node */
    ULONG                           PacketSize; /**< Indicate the number of MoCA aggregation MoCA frames. */
    ULONG                           PeakDataRate; /**< Indicate the T_PEAK_DATA_RATE of the PQoS flow identified by
    'mocaIfFlowID' in which this MoCA interface is an ingress node for the PQoS flow. */
    ULONG                           BurstSize; /**< Indicate the T_BURST_SIZE of the PQoS flow identified by
    'mocaIfFlowID' in which this MoCA interface is an ingress node for this PQoS flow. */
    ULONG                           FlowTag; /**< Indicate the FLOW_TAG of the PQoS flow identified by 'mocaIfFlowID' in which this MoCA interface is an ingress node
    for this PQoS flow. The FLOW_TAG carries application specific content of this PQoS flow. */
    ULONG                           LeaseTime; /**< Indicate the T_LEASE_TIME of the PQoS flow identified by
    'mocaIfFlowID' in which this MoCA interface is an ingress node for this PQoS flow. */
} moca_flow_table_t;

typedef INT ( * moca_associatedDevice_callback)(ULONG ifIndex, moca_associated_device_t *moca_dev); //This call back will be invoked when new MoCA client is Actived or Inactived.moca_associated_device_t.Active is used to indicate activation/inactivation

typedef struct moca_assoc_pnc_info {
    ULONG   mocaNodeIndex; /**< The index of this node */
    BOOL        mocaNodePreferredNC; /**< Whether this Node is a Preferred NC. */
    ULONG    mocaNodeMocaversion; /**< The MoCA version of this node */
}moca_assoc_pnc_info_t;


typedef struct{
    INT TxNode; /**< The NODE ID of Transmit MOCA NODE. */
    INT RxNode; /**< The Node ID of Receive MOCA Node. */
    INT Channel; /**< The Primary channel or Secondary channel used to calculate the NPER and VLPER */
    UCHAR Mod[512]; /**< Subcarrier MODULATION used to calcuate the NPER and VLPER between two nodes */
    UCHAR Nper[512]; /**< Each NPER of between two nodes on Corresponding Channel */
    UCHAR Vlper[512]; /**< Each Vlper of between two nodes on Corresponding Channel */
}moca_scmod_stat_t;


typedef struct {
    UINT NodeID; /**< The NodeID where we want to start the ACA testing */
    PROBE_TYPE Type; /**< The Probe Type could be Enum EVM=1 or Quite=0 */
    UINT Channel; /**< The Channel on which ACA test should start */
    UINT ReportNodes;/**< Specifies the MoCA Nodes that are requested to be part of the channel assessment: Setting bits
corresponding to Node IDs of these MoCA Nodes to 1 (LSB corresponds to Node ID 0x0).
                        For example:
                        0000 0000 0000 0101 can be represented as 0x0005, Node 0 and Node 2.     */
    BOOL ACAStart; /**< The ACAStart will indiacte to start the ACA process or not. 0 for no action , 1 for config and
start
                     the process */
}moca_aca_cfg_t;

typedef struct{
    moca_aca_cfg_t acaCfg; /**< the current configuration on ACA process started */
    INT stat;/**< SUCCESS=0, Fail-BADCHANNEL=1,Fail-NoEVMPROBE=2, Fail=3,In-Progress=4 */
    INT RxPower; /**< Total RX Power in DBM */
    INT ACAPowProfile[512]; /**< Power Profile Representation for each channel*/
    BOOL ACATrapCompleted; /**< mocaIfAcaStatusTrapCompleted ReadOnly parameter, 
                              it will be TRUE when PowerPorfile is ready */
}moca_aca_stat_t;
/** @} */  //END OF GROUP MOCA_HAL_TYPES

void moca_associatedDevice_callback_register(moca_associatedDevice_callback callback_proc); //Callback registration function.

/**
 * @addtogroup MOCA_HAL_APIS
 * @{
 */
/**********************************************************************************
 *
 *  MoCA Subsystem level function prototypes 
 *
**********************************************************************************/
/* moca_GetIfConfig() function */
/**
* @description Gets the MoCA Configuration Parameters that were previously set.
*
* @param[in] ifIndex - Index of the MoCA Interface.
* @param[out] pmoca_config - Variable that represents a pointer to structure of type moca_cfg_t for configuration parameters.
* <pre>
*                The members of the moca_cfg_t structure are defined below.
*
*                InstanceNumber              - Instance Number when Multiple MoCA interfaces exist.
*                                              The range of acceptable values is 0 to 256, where InstanceNumber starts at 1 and just one interface is present if value is 0.
*
*                Alias[64]                   - Get the Alias Name for the interface.
*                                              Alias is a 64 bytes character array.
*
*                bEnabled                    - Enable/Disable the interface using bEnabled.
*                                              If the Interface is enabled, the bEnabled Flag is TURE; otherwise, it is FALSE.
*
*                bPreferredNC                - Enable/Disable the Node's preference to be Network Coordinator using bPreferredNC.
*                                              If the Local Node's preference to be Network Coordinator is enabled, the bPreferredNC Flag is TURE; otherwise, it is FALSE.
*
*                PrivacyEnabledSetting       - Enable/Disable the Link Privacy using PrivacyEnabledSetting.
*                                              A Password is required when Privacy is enabled, the PrivacyEnabledSetting flag is TRUE; otherwise, it is FALSE.
*
*                FreqCurrentMaskSetting[128] - Current Frequencies Mask that should be used for forming network (bitmask).
*                                              FreqCurrentMaskSetting is a 128 bytes character array. It is a vendor specific value.
*
*                KeyPassphrase[18]           - Privacy Password. This field is valid only if the Link Privacy is enabled.
*                                              KeyPassphrase is a 18 bytes character array. It is a vendor specific value.
*
*                TxPowerLimit                - Maximum Transmission Power allowed.
*                                              The range of acceptable values is -n to n, where n is a signed integer value.
*
*                AutoPowerControlPhyRate     - AutoPowerControlPhyRate: PowerCtrlPhyTarget Used as a reference to achieve the PHY rate by adjusting  power.
*                                              The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                BeaconPowerLimit            - Maximum Transmission Power Allowed when transmitting Beacons.
*                                              The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                MaxIngressBWThreshold       - Maximum Ingress Bandwidth Thresholds which used as a reference to achieve the PHY rate by adjusting power.
*                                              The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                Reset                       - Reset Condition of the MoCA Node.
*                                              If the Reset MoCA Configuration to defaults is enabled, the Reset Flag is TURE; otherwise, it is FALSE.
*
*                MixedMode                   - Enable/Disable the Node to operate in mixed mode (1.0/1.1/2.0 versions). Enable backward compatibility on the MoCA Protocol Versions.
*                                              If the Node is configured to operate in mixed mode is enabled, the MixedMode Flag is TRUE; otherwise, it is FALSE.
*
*                ChannelScanning             - Enable/Disable the Node to operate in single frequency mode or scanning mode.
*                                              If the Node is Scanning is enabled, the ChannelScanning Flag is TURE; otherwise, it is FALSE.
*
*                AutoPowerControlEnable      - Enable/Disable adjusting Power to achieve the Target PHY rate.
*                                              If the Auto Power Control is enabled, the AutoPowerControlEnable Flag is TRUE; otherwise, it is FALSE.
*
*                EnableTabooBit              - Enable/Disable the Node to support Taboo Mask.
*                                              If the Node to support Taboo Mask is enabled, the EnableTabooBit Flag is TRUE; otherwise, it is FALSE.
*
*                NodeTabooMask[128]          - Indicates the Set of Frequencis to Avoid (bitmask).
*                                              NodeTabooMask is a 128 bytes character array. It is a vendor specific value.
*
*                ChannelScanMask[128]        - Indicates the Set of Frequencies to Scan for Beacons to form network (bitmask).
*                                              ChannelScanMask is a 128 bytes character array. It is a vendor specific value.
* </pre>
*
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected.
*
*
* @remark The caller is responsible for providing a valid memory location for the pmoca_config parameter.
*         \n The function will populate this structure with the retrieved MoCA interface information.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system calls.
*       \n It should probably just send a message to a driver event handler task.
*
*/
INT moca_GetIfConfig(ULONG ifIndex, moca_cfg_t *pmoca_config);

/* moca_SetIfConfig() function */
/**
* @description Sets the MoCA Configuration Parameters.
*
* @param[in] ifIndex - Index of the MoCA Interface.
* @param[in] pmoca_config - Variable that represents a pointer to structure of type moca_cfg_t for configuration parameters.
* <pre>
*                The members of the moca_cfg_t structure are defined below.
*
*                InstanceNumber              - Instance Number when Multiple MoCA interfaces exist.
*                                              The range of acceptable values is 0 to 256, where InstanceNumber starts at 1 and just one interface is present if value is 0.
*
*                Alias[64]                   - Get the Alias Name for the interface.
*                                              Alias is a 64 bytes character array.
*
*                bEnabled                    - Enable/Disable the interface using bEnabled.
*                                              If the Interface is enabled, the bEnabled Flag is TURE; otherwise, it is FALSE.
*
*                bPreferredNC                - Enable/Disable the Node's preference to be Network Coordinator using bPreferredNC.
*                                              If the Local Node's preference to be Network Coordinator is enabled, the bPreferredNC Flag is TURE; otherwise, it is FALSE.
*
*                PrivacyEnabledSetting       - Enable/Disable the Link Privacy using PrivacyEnabledSetting.
*                                              A Password is required when Privacy is enabled, the PrivacyEnabledSetting flag is TRUE; otherwise, it is FALSE.
*
*                FreqCurrentMaskSetting[128] - Current Frequencies Mask that should be used for forming network (bitmask).
*                                              FreqCurrentMaskSetting is a 128 bytes character array. It is a vendor specific value.
*
*                KeyPassphrase[18]           - Privacy Password. This field is valid only if the Link Privacy is enabled.
*                                              KeyPassphrase is a 18 bytes character array. It is a vendor specific value.
*
*                TxPowerLimit                - Maximum Transmission Power allowed.
*                                              The range of acceptable values is -n to n, where n is a signed integer value.
*
*                AutoPowerControlPhyRate     - AutoPowerControlPhyRate: PowerCtrlPhyTarget Used as a reference to achieve the PHY rate by adjusting  power.
*                                              The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                BeaconPowerLimit            - Maximum Transmission Power Allowed when transmitting Beacons.
*                                              The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                MaxIngressBWThreshold       - Maximum Ingress Bandwidth Thresholds which used as a reference to achieve the PHY rate by adjusting power.
*                                              The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                Reset                       - Reset Condition of the MoCA Node.
*                                              If the Reset MoCA Configuration to defaults is enabled, the Reset Flag is TURE; otherwise, it is FALSE.
*
*                MixedMode                   - Enable/Disable the Node to operate in mixed mode (1.0/1.1/2.0 versions). Enable backward compatibility on the MoCA Protocol Versions.
*                                              If the Node is configured to operate in mixed mode is enabled, the MixedMode Flag is TRUE; otherwise, it is FALSE.
*
*                ChannelScanning             - Enable/Disable the Node to operate in single frequency mode or scanning mode.
*                                              If the Node is Scanning is enabled, the ChannelScanning Flag is TURE; otherwise, it is FALSE.
*
*                AutoPowerControlEnable      - Enable/Disable adjusting Power to achieve the Target PHY rate.
*                                              If the Auto Power Control is enabled, the AutoPowerControlEnable Flag is TRUE; otherwise, it is FALSE.
*
*                EnableTabooBit              - Enable/Disable the Node to support Taboo Mask.
*                                              If the Node to support Taboo Mask is enabled, the EnableTabooBit Flag is TRUE; otherwise, it is FALSE.
*
*                NodeTabooMask[128]          - Indicates the Set of Frequencis to Avoid (bitmask).
*                                              NodeTabooMask is a 128 bytes character array. It is a vendor specific value.
*
*                ChannelScanMask[128]        - Indicates the Set of Frequencies to Scan for Beacons to form network (bitmask).
*                                              ChannelScanMask is a 128 bytes character array. It is a vendor specific value.
* </pre>
*
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected.
*
*
* @remark The caller is responsible for providing a valid memory location for the pmoca_config parameter.
*         \n The function will populate this structure with the retrieved MoCA interface information.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system calls.
*       \n It should probably just send a message to a driver event handler task.
*
*/
INT moca_SetIfConfig(ULONG ifIndex, moca_cfg_t *pmoca_config);

/* moca_IfGetDynamicInfo() function */
/**
* @description Gets the Dynamic Status information on the interface & its associated network.
* @param[in] ifIndex - Index of the MoCA Interface.
* @param[out] pmoca_dynamic_info - Variable that represents a pointer to structure of type moca_dynamic_info_t for configuration parameters.
* <pre>
*                The members of the moca_dynamic_info_t structure are defined below.
*
*                moca_if_status_t                  - Local Interface's current status (Up, Down, Dormant, Not Present, Lowerlayer Down, etc.).
*                                                    The range of acceptable values is 1 to 7 based on moca_if_status_t enum type value.
*                                                    The moca_if_status_t is an enum type are defined below.
*                                                    IF_STATUS_Up = 1
*                                                    IF_STATUS_Down = 2
*                                                    IF_STATUS_Unknown = 3
*                                                    IF_STATUS_Dormant = 4
*                                                    IF_STATUS_NotPresent = 5
*                                                    IF_STATUS_LowerLayerDown = 6
*                                                    IF_STATUS_Error = 7
*
*                LastChange                        - Last Link Status Change (Up, Down, Dormant, Not Present, Lowerlayer Down, etc.).
*                                                    The range of acceptable values is 1 to 7, where LastChange value based on moca_if_status_t enum type.
*
*                MaxIngressBW                      - Maximum Ingress Bandwidth reached.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                MaxEgressBW                       - Maximum Egress Bandwidth reached.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                CurrentVersion[64]                - Current Operating MoCA Protocol Version.
*                                                    Valid Values: 1.0, 1.1, 2.0. CurrentVersion is a 128 bytes character array. It is a vendor specific value.
*
*                NetworkCoordinator                - Node ID of the Network Coordinator.
*                                                    Valid Values: 0-7 (For Protocol: 1.0) and Valid Values: 0-15 (For Protocol: 1.1, 2.0).
*
*                NodeID                            - Node ID of the Local Node.
*                                                    Valid Values: 0-7 (For Protocol: 1.0) and Valid Values: 0-15 (For Protocol: 1.1, 2.0).
*
*                BackupNC                          - Node ID of the Backup Network Coordinator.
*                                                    Valid Values: 0-7 (For Protocol: 1.0) and Valid Values: 0-15 (For Protocol: 1.1, 2.0).
*
*                PrivacyEnabled                    - Enable/Disable the Privacy on the network using PrivacyEnabled.
*                                                    If the Privacy is enabled on the network, the PrivacyEnabled Flag is TURE; otherwise, it is FALSE.
*
*                FreqCurrentMask[8]                - Frequencies Current Mask that the Node can operate.
*                                                    FreqCurrentMask is a 8 bytes character array. It is a vendor specific value.
*
*                CurrentOperFreq                   - The Current Frequency on which the Node formed the Network.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value. It is a vendor specific value.
*
*                LastOperFreq                      - The Last Operating Frequency on which the Node formed the Network earlier.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value. It is a vendor specific value.
*
*                TxBcastRate                       - Transmission Broadcast Rate.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned integer value.
*
*                MaxIngressBWThresholdReached      - Maximum Ingress Bandwidth Thresholds Reached.
*                                                    If the Ingress Bandwidth reached the Maximum Threshold is enabled, the MaxIngressBWThresholdReached Flag is TURE; otherwise, it is FALSE.
*
*                MaxEgressBWThresholdReached       - Maximum Egress Bandwidth Thresholds Reached.
*                                                    If the Egress Bandwidth reached the Maximum Threshold is enabled, the MaxEgressBWThresholdReached Flag is TURE; otherwise, it is FALSE.
*
*                NumberOfConnectedClients          - Number of Nodes on the MoCA Network.
*                                                    The range of acceptable values is 0 to 256.
*
*                MixedMode                         - Enable/Disable the Node to operate in mixed mode (1.0/1.1/2.0 versions). Enable backward compatibility on the MoCA Protocol Versions.
*                                                    If the Node is configured to operate in mixed mode is enabled, the MixedMode Flag is TRUE; otherwise, it is FALSE.
*
*                ChannelScanning                   - Enable/Disable the Node to operate in single frequency mode or scanning mode.
*                                                    If the Node is Scanning is enabled, the ChannelScanning Flag is TURE; otherwise, it is FALSE.
*
*                AutoPowerControlEnable            - Enable/Disable adjusting Power to achieve the Target PHY rate.
*                                                    If the Auto Power Control is enabled, the AutoPowerControlEnable Flag is TRUE; otherwise, it is FALSE.
*
*                EnableTabooBit                    - Enable/Disable the Node to support Taboo Mask.
*                                                    If the Node to support Taboo Mask is enabled, the EnableTabooBit Flag is TRUE; otherwise, it is FALSE.
*
*                NetworkCoordinatorMACAddress[18]  - Network Coordinator MAC Address.
*                                                    NetworkCoordinatorMACAddress is a 8 bytes character array. The MAC Address should be in the format AA:BB:CC:DD:EE:FF (colon-separated).
*
*                LinkUpTime                        - Indicate  the length of time this node has been connected to the MoCA network with at least one other node.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
* </pre>
*
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected.
*
* @remark The caller is responsible for providing a valid memory location for the pmoca_dynamic_info parameter.
*         \n The function will populate this structure with the retrieved MoCA interface information.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system calls.
*       \n It should probably just send a message to a driver event handler task.
*
*/
INT moca_IfGetDynamicInfo(ULONG ifIndex, moca_dynamic_info_t *pmoca_dynamic_info);

/* moca_IfGetStaticInfo() function */
/**
* @description Gets the Static Information from the Local Node.
* @param[in] ifIndex - Index of the MoCA Interface.
* @param[out] pmoca_static_info - Variable that represents a pointer to structure of type moca_static_info_t for static information of the interface.
* <pre>
*                The members of the moca_static_info_t structure are defined below.
*
*                Name[64]                          - Uniquely identifying the entry for Interface Name. For example: moca0.
*                                                    Name is a 64 bytes character array.
*                                                    Possible Name Values are moca0 and nmoca0.
*
*                MacAddress[6 + MAC_PADDING]       - MAC Address of the Local Node.
*                                                    MacAddress is a [6 + MAC_PADDING] bytes character array. MAC_PADDING is a 12 bytes. RDKB expects 6 byte MAC, padding required for platforms handling as 18 bytes MAC.
*                                                    The MAC Address should be in the format AA:BB:CC:DD:EE:FF (colon-separated).
*
*                FirmwareVersion[64]               - Firmware Version of the MoCA Firmware.
*                                                    FirmwareVersion is a 64 bytes character array.
*                                                    For example firmware version: 2.12.5p40. It is a vendor specific value.
*
*                MaxBitRate                        - Maximum PHY Rate that the Node can support.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                HighestVersion[64]                - Highest Version of the MoCA Protocol that the Local Node Supports.
*                                                    HighestVersion is a 64 bytes character array. Possible Valid values are 1.0, 1.1 and 2.0. It is a vendor specific value.
*
*                FreqCapabilityMask[8]             - Frequencies that the Local Node supports (bitmask).
*                                                    FreqCapabilityMask is a 8 bytes character array. It is a vendor specific value.
*
*                NetworkTabooMask[128]             - Indicates the Set of Frequencis to Avoid because the Local Node does not support (bitmask).
*                                                    NodeTabooMask is a 128 bytes character array. It is a vendor specific value.
*
*                TxBcastPowerReduction             - Beacon Backoff in dB.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                QAM256Capable                     - Enable/Disable the Local Node is QAM-256 Capable or Not.
*                                                    If the Local Node with QAM-256 Capable is enabled, the QAM256Capable Flag is TRUE; otherwise, it is FALSE.
*
*                PacketAggregationCapability       - Enable/Disable the Local Node can aggregate Ethernet Packets for MoCA PDU transfers.
*                                                    If the Local Node can aggregate Ethernet Packets for MoCA PDU transfersis Scanning is enabled, the PacketAggregationCapability Flag is TURE; otherwise, it is FALSE.
* </pre>
*
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected.
*
* @remark The caller is responsible for providing a valid memory location for the pmoca_static_info parameter.
*         The function will populate this structure with the retrieved MoCA interface information.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system calls.
*       \n It should probably just send a message to a driver event handler task.
*
*/
INT moca_IfGetStaticInfo(ULONG ifIndex, moca_static_info_t *pmoca_static_info);

/* moca_IfGetStats() function */
/**
* @description Gets the Statistics on the Interface at Network Layer.
* @param[in] ifIndex - Index of the MoCA Interface.
* @param[out] pmoca_stats - Variable that represents a pointer to structure of type moca_stats_t for statistics on the interface (Network layer).
* <pre>
*                The members of the moca_stats_t structure are defined below.
*
*                BytesSent                         - Number of Bytes Sent.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                BytesReceived                     - Number of Bytes Received.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                PacketsSent                       - Number of Packets Sent.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                PacketsReceived                   - Number of Packets Received.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                ErrorsSent                        - Number of Errors Sent.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                ErrorsReceived                    - Number of Errors Received.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                UnicastPacketsSent                - Number of Unicast Packets Sent.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                UnicastPacketsReceived            - Number of Unicast Packets Received.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                DiscardPacketsSent                - Number of Packets Discard (Tx side).
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                DiscardPacketsReceived            - Number of Packets Discard (Rx side).
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                MulticastPacketsSent              - Number of Multicast Packets Sent.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                MulticastPacketsReceived          - Number of Multicast Packets Received.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                BroadcastPacketsSent              - Number of Broadcast Packets Sent.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                BroadcastPacketsReceived          - Number of Broadcast Packets Received.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                UnknownProtoPacketsReceived       - Number of Unknown Protocol Packets Received.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                ExtAggrAverageTx                  - Aggregate Averages of Packet Counts (Tx).
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                ExtAggrAverageRx                  - Aggregate Averages of Packet Counts (Rx).
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
* </pre>
*
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected.
*
* @remark The caller is responsible for providing a valid memory location for the pmoca_stats parameter.
*         \n The function will populate this structure with the retrieved MoCA interface information.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system calls.
*       \n It should probably just send a message to a driver event handler task.
*
*/
INT moca_IfGetStats(ULONG ifIndex, moca_stats_t *pmoca_stats);

/* moca_GetNumAssociatedDevices() function */
/**
* @description Gets the Number of Nodes on the MoCA network.
* @param[in] ifIndex - Index of the MoCA Interface.
* @param[out] pulCount - A pointer to an unsigned long variable to store the Number of Nodes on the network.
* 
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected.
* 
* @remark The caller is responsible for allocating memory for the 'pulCount' variable.
*         \n The function will store the result in the memory location pointed to by 'pulCount'.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system calls.
*       \n It should probably just send a message to a driver event handler task.
*
*/
INT moca_GetNumAssociatedDevices(ULONG ifIndex, ULONG *pulCount);

/* moca_IfGetExtCounter() function */
/**
* @description Gets the Statistics on the Interface at MoCA MAC Layer.
* @param[in] ifIndex - Index of the MoCA Interface.
* @param[out] pmoca_mac_counters - Variable that represents a pointer to structure of type moca_mac_counters_t for the MoCA MAC Layer Statiscs.
* <pre>
*                The members of the moca_mac_counters_t structure are defined below.
*
*                Map                               - Number of MAP packets.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                Rsrv                              - Number of Bytes Received.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                Lc                                - Number of Packets Sent.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                Adm                               - Number of Packets Received.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                Probe                             - Number of Errors Sent.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                Async                             - Number of Errors Received.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
* </pre>
*
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected.
* 
* @remark The caller is responsible for providing a valid memory location for the pmoca_mac_counters parameter.
*         \n The function will populate this structure with the retrieved MoCA interface information.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system calls.
*       \n It should probably just send a message to a driver event handler task.
*
*/
INT moca_IfGetExtCounter(ULONG ifIndex, moca_mac_counters_t *pmoca_mac_counters);

/* moca_IfGetExtAggrCounter() function */
/**
* @description Gets the Aggregate DATA units Transferred (Tx & Rx)
* @param[in] ifIndex - Index of the MoCA Interface.
* @param[out] pmoca_aggregate_counts - Variable that represents a pointer to structure of type moca_aggregate_counters_t for Aggregate Tx/Rx Counters.
* <pre>
*                The members of the moca_aggregate_counters_t structure are defined below.
*
*                Tx                                - Aggregate Tx Payload Data Units (Not MoCA Control Packets).
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                Rx                                - Aggregate Rx Payload Data Units (Not MoCA Control Packets).
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
* </pre>
*
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected.
*
* @remark The caller is responsible for providing a valid memory location for the pmoca_aggregate_counts parameter.
*         \n The function will populate this structure with the retrieved MoCA interface information.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system calls.
*       \n It should probably just send a message to a driver event handler task.
*
*/
INT moca_IfGetExtAggrCounter(ULONG ifIndex, moca_aggregate_counters_t *pmoca_aggregate_counts);

/* moca_GetMocaCPEs() function */
/**
* @description Get MAC Address of all the Nodes Connected on MoCA Network.
* @param[in] ifIndex - Index of the MoCA Interface.
* @param[out] cpes - Variable that represents a pointer to structure of type moca_cpe_t for the List of MAC Addresses of MoCA Nodes.
* <pre>
*                The members of the moca_cpe_t structure are defined below.
*
*                mac_addr[6]                       - MAC Address of the Node.
*                                                    mac_addr is a 6 bytes character array.
*                                                    The MAC Address should be in the format AA:BB:CC:DD:EE:FF (colon-separated).
*
* </pre>
* @param[out] pnum_cpes - A pointer to an integer to store the Number of MoCA Nodes in the List.
*
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected 
*
* @remark The caller is responsible for allocating and freeing the memory for the cpes array.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system calls.
*       \n It should probably just send a message to a driver event handler task.
*
*/
INT moca_GetMocaCPEs(ULONG ifIndex, moca_cpe_t *cpes, INT *pnum_cpes);

/* moca_GetAssociatedDevices() function */
/**
* @description Get Information on all the associated Devices on the network.
* @param[in] ifIndex - Index of the MoCA Interface.
* @param[out] ppdevice_array - A pointer to a pointer of `moca_associated_device_t` array to store the set of information for each Node on the network.
* <pre>
*                The members of the moca_associated_device_t structure are defined below. This Data Structure corresponds to information of the associated device on the network.
*                The term 'this Node' pertains to that particulard device for which the information in this data structure is valid.
*                Tx means "Transmit" and "Rx" means "Receive".
*
*
*                MacAddress[6 + MAC_PADDING]       - MAC Address of the Associated Device.
*                                                    MacAddress is a [6 + MAC_PADDING] bytes character array. MAC_PADDING is a 12 bytes. RDKB expects 6 byte MAC, padding required for platforms handling as 18 bytes MAC.
*                                                    The MAC Address should be in the format AA:BB:CC:DD:EE:FF (colon-separated).
*
*                NodeID                            - Node ID of the Associated Device.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value. It is a vendor specific value.
*
*                PreferredNC                       - Enable/Disable the Node's preference to be Network Coordinator using PreferredNC.
*                                                    If the Local Node's preference to be Network Coordinator is enabled, the PreferredNC Flag is TURE; otherwise, it is FALSE.
*
*                HighestVersion[64]                - Highest MoCA Protocol Version that this Node supports.
*                                                    HighestVersion is a 64 bytes character array. Possible Valid values are 1.0, 1.1 and 2.0. It is a vendor specific value.
*
*                PHYTxRate                         - Tx PHY Rate of this Node.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                PHYRxRate                         - Rx PHY Rate of this Node.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                TxPowerControlReduction           - Tx Power Reduced by this Node.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                RxPowerLevel                      - Rx Power Level read by this Node.
*                                                    The range of acceptable values is -n to n, where n is a signed integer value.
*
*                TxBcastRate                       - Tx Broadcast PHY Rate.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                RxBcastPowerLevel                 - Rx Broadcast Power Level read by this Node.
*                                                    The range of acceptable values is -n to n, where n is a signed integer value.
*
*                TxPackets                         - Number of Transmitted Packets from this Node.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                RxPackets                         - Number of Recieved Packets by this Node.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                RxErroredAndMissedPackets         - Number of (Rx) Error or Missed Packets by this Node.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                QAM256Capable                     - Enable/Disable the Local Node is QAM-256 Capable or Not.
*                                                    If the Local Node with QAM-256 Capable is enabled, the QAM256Capable Flag is TRUE; otherwise, it is FALSE.
*
*                PacketAggregationCapability       - Enable/Disable the Local Node can aggregate Ethernet Packets for MoCA PDU transfers
*                                                    If the Local Node can aggregate Ethernet Packets for MoCA PDU transfersis Scanning is enabled, the PacketAggregationCapability Flag is TURE; otherwise, it is FALSE.
*
*                RxSNR                             - Receive Signal to Noise Ration.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                Active                            - Enable/Disable the this Node or Not.
*                                                    If the this Node is enabled, the Active Flag is TRUE; otherwise, it is FALSE.
*
*                RxBcastRate                       - Recevie Broadcast PHY Rate.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                NumberOfClients                   - Number of Clients connected to this Node.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
* </pre>
*
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the ppdevice_array parameter.
*         \n The function will populate this structure with the retrieved MoCA interface information.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system calls.
*       \n It should probably just send a message to a driver event handler task.
*
*/
INT moca_GetAssociatedDevices(ULONG ifIndex, moca_associated_device_t **ppdevice_array);


/* moca_FreqMaskToValue() function */
/**
* @description A utility function that converts Mask Value to Frequency Number.
* @param[in] mask - Pointer to an array of UCHAR values representing the Bit Mask of the Frequency.
*
* @return Frequency Value for the given Mask.
*
* @remark The size of the mask array must be compatible with the implementation of this function.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system calls.
*       \n It should probably just send a message to a driver event handler task. 
*
*/
//INT moca_FreqMaskToValue(UINT mask);
INT moca_FreqMaskToValue(UCHAR *mask);

/* moca_HardwareEquipped() function */
/**
* @description Functio that returns whether the MoCA Hardware is Equipped or Not.
* @param None.
*
* @return Flag Indicating whether the Hardware is Equipped or not.
* @retval TRUE if Hardware is present.
* @retval FALSE if Hardware is not present.
*
* @remark The return value is based on the current state of the hardware and its configuration.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system calls. 
*       \n It should probably just send a message to a driver event handler task.
*
*/
BOOL moca_HardwareEquipped(void);

/* moca_GetFullMeshRates() function */
/**
* @description Gets the MoCA Full Mesh Rates.
*
* @param[in] ifIndex - Index of the MoCA Interface.
* @param[out] pDeviceArray - Variable that represents a pointer to structure of type moca_mesh_table_t for MoCA Full Mesh Rate .
* @param[out] pulCount - A pointer to an unsigned long variable to store the Number of Nodes on the network.
*
* <pre>
*                The members of the moca_mesh_table_t structure are defined below.
*
*                RxNodeID                          - The node ID of the receive MoCA node is used as one of the index to order the mesh PHY rate table.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                TxNodeID                          - The node ID of the transmit MoCA node is used as one of the index to order the mesh PHY rate table.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                TxRate                            - Indicate the transmit PHY rate in Mbps from the MoCA node identified by 'mocaMeshTxNodeIndex' to the MoCA node identified by 'mocaMeshRxNodeIndex'.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                TxRateNper                        - Only for MoCA 2.x.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                RxRateNper                        - Only for MoCA 2.x.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
* </pre>
*
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected.
*
* @remark The caller is responsible for providing a valid memory location for the pDeviceArray parameter.
*         \n The function will populate this structure with the retrieved MoCA interface information.
*         \n The caller is responsible for allocating memory for the 'pulCount' variable.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system calls.
*       \n It should probably just send a message to a driver event handler task.
*
*/
#ifndef MOCA_VAR
INT moca_GetFullMeshRates(ULONG ifIndex, moca_mesh_table_t *pDeviceArray, ULONG *pulCount);
#endif

/* moca_GetFlowStatistics() function */
/**
* @description Gets the MoCA Flow Table.
* @param[in] ifIndex - Index of the MoCA Interface.
* @param[out] pDeviceArray - Variable that represents a pointer to structure of type moca_flow_table_t for a flow table entry.
* <pre>
*                The members of the moca_flow_table_t structure are defined below.
*                This Data Structure respresents the MoCA interface flow statistics table.
*                This table provides statistics of ingress PQoS flow in the MoCA interface.
*
*                FlowID                            - Indicate the flow ID of a PQoS flow.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                IngressNodeID                     - Indicate the flow ID of a Ingress PQoS flow.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                EgressNodeID                      - Indicate the flow ID of a Egress PQoS flow.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                FlowTimeLeft                      - Indicate the LEASE_TIME_LEFT of the PQoS flow identified by 'mocaIfFlowID' in which this MoCA interface is an ingress node for this PQoS flow.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                DestinationMACAddress[18]         - Indicate the Destination Address (DA) of Ethernet packets of the PQoS Flow for which this node is the ingress node.
*                                                    DestinationMACAddress is a 8 bytes character array. The MAC Address should be in the format AA:BB:CC:DD:EE:FF (colon-separated).
*
*                PacketSize                        - Indicate the number of MoCA aggregation MoCA frames.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                PeakDataRate                      - Indicate the T_PEAK_DATA_RATE of the PQoS flow identified by 'mocaIfFlowID' in which this MoCA interface is an ingress node for the PQoS flow.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                BurstSize                         - Indicate the T_BURST_SIZE of the PQoS flow identified by 'mocaIfFlowID' in which this MoCA interface is an ingress node for this PQoS flow.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                FlowTag                           - Indicate the FLOW_TAG of the PQoS flow identified by 'mocaIfFlowID' in which this MoCA interface is an ingress node for this PQoS flow. The FLOW_TAG carries application specific content of this PQoS flow.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                LeaseTime                         - Indicate the T_LEASE_TIME of the PQoS flow identified by 'mocaIfFlowID' in which this MoCA interface is an ingress node for this PQoS flow.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
* </pre>
*
* @param[out] pulCount - A pointer to an unsigned long variable to store the number of entries in the table.
*
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected.
*
* @remark The caller is responsible for providing a valid memory location for the pDeviceArray parameter.
*         \n The function will populate this structure with the retrieved MoCA interface information.
*         \n The caller is responsible for allocating memory for the 'pulCount' variable.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system calls.
*       \n It should probably just send a message to a driver event handler task.
*
*/
INT moca_GetFlowStatistics(ULONG ifIndex, moca_flow_table_t *pDeviceArray, ULONG *pulCount);

/* moca_GetResetCount() function */
/**
* @description Gets the MoCA reset count.
* @param[in] resetcnt - Pointer to an array of UCHAR values representing number of reset.
*
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected. 
* 
* @remark The reset count is an unsigned long value that indicates the number of times the MOCA module has been reset.
*         \n If the operation fails, the reset count value remains unchanged.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system calls.
*       \n It should probably just send a message to a driver event handler task.
*
*/

INT moca_GetResetCount(ULONG *resetcnt);

/****************************************************************/
/* moca_SetIfAcaConfig() function */
/**
* @description Sets the MoCA Configuration Parameters to start the ACA process.
* @param[in] interfaceIndex - Index of the MoCA Interface.
* @param[in] acaCfg - Variable that represents the structure of type moca_aca_cfg_t for Configuration Parameters required for MOCA ACA Process.
* <pre>
*                The members of the moca_aca_cfg_t structure are defined below.
*
*                NodeID                            - The NodeID where we want to start the ACA testing.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned integer value.
*
*                Type                              - The Probe Type could be Enum EVM=1 or Quite=0.
*                                                    The range of acceptable values is 0 to 1 based on PROBE_TYPE enum type value. The enum PROBE_TYPE defined below.
*                                                    PROBE_QUITE = 0
*                                                    PROBE_EVM = 1
*
*                Channel                           - The Channel on which ACA test should start.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned integer value.
*
*                ReportNodes                       - Specifies the MoCA Nodes that are requested to be part of the channel assessment: Setting bits corresponding to Node IDs of these MoCA Nodes to 1 (LSB corresponds to Node ID 0x0).
*                                                    For example: 0000 0000 0000 0101 can be represented as 0x0005, Node 0 and Node 2.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                DestinationMACAddress[18]         - Indicate the Destination Address (DA) of Ethernet packets of the PQoS Flow for which this node is the ingress node.
*                                                    DestinationMACAddress is a 8 bytes character array. The MAC Address should be in the format AA:BB:CC:DD:EE:FF (colon-separated).
*
*                ACAStart                          - The ACAStart will indiacte to start the ACA process or not.
*                                                    If the start the ACA process is enabled, the ACAStart Flag is TRUE for config; otherwise, it is FALSE for no action.
* </pre>
*
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected for unknown reason.
* @retval STATUS_INPROGRESS if already the ACA process running.
*
* @remark The caller is responsible for providing a valid memory location for the acaCfg parameter.
*         \n The function will populate this structure with the retrieved MoCA interface information.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system calls.
*       \n It should probably just send a message to a driver event handler task.
*       \n ACAStart bit is set then ACA Process should get start.
*       \n If user request ACA Start while ACA Process in progress, then HAL should send error saying ACA Is in progress.
*       \n It should not start new one.
*
*/
int moca_setIfAcaConfig(int interfaceIndex, moca_aca_cfg_t acaCfg);
/****************************************************************/
/* moca_GetIfAcaConfig() function */
/**
* @description Gets the MoCA Configuration Parameters set before starting the ACA process.
* @param[in] interfaceIndex - Index of the MoCA Interface.
* @param[out] acaCfg - Variable that represents a pointer to structure of type moca_aca_cfg_t for Configuration Parameters required for MOCA ACA Process.
* <pre>
*                The members of the moca_aca_cfg_t structure are defined below.
*
*                NodeID                            - The NodeID where we want to start the ACA testing.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned integer value.
*
*                Type                              - The Probe Type could be Enum EVM=1 or Quite=0.
*                                                    The range of acceptable values is 0 to 1 based on PROBE_TYPE enum type value. The enum PROBE_TYPE defined below.
*                                                    PROBE_QUITE = 0
*                                                    PROBE_EVM = 1
*
*                Channel                           - The Channel on which ACA test should start.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned integer value.
*
*                ReportNodes                       - Specifies the MoCA Nodes that are requested to be part of the channel assessment: Setting bits corresponding to Node IDs of these MoCA Nodes to 1 (LSB corresponds to Node ID 0x0).
*                                                    For example: 0000 0000 0000 0101 can be represented as 0x0005, Node 0 and Node 2.
*                                                    The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                DestinationMACAddress[18]         - Indicate the Destination Address (DA) of Ethernet packets of the PQoS Flow for which this node is the ingress node.
*                                                    DestinationMACAddress is a 8 bytes character array. The MAC Address should be in the format AA:BB:CC:DD:EE:FF (colon-separated).
*
*                ACAStart                          - The ACAStart will indiacte to start the ACA process or not.
*                                                    If the start the ACA process is enabled, the ACAStart Flag is TRUE for config; otherwise, it is FALSE for no action.
* </pre>
*
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected 
*
* @remark The caller is responsible for providing a valid memory location for the acaCfg parameter.
*         \n The function will populate this structure with the retrieved MoCA interface information.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system calls. 
*       \n It should probably just send a message to a driver event handler task. 
*
*/
int moca_getIfAcaConfig(int interfaceIndex, moca_aca_cfg_t *acaCfg);

/****************************************************************/
/* moca_cancelIfAca() function */
/**
* @description this function uses to cancel the ACA process which already running.
*
* @param[in] interfaceIndex - Index of the MoCA Interface on which ACA process started.
*
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected 
* 
* @execution ASynchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system calls.
*       \n It should probably just send a message to a driver event handler task.
*/
int moca_cancelIfAca(int interfaceIndex);


/****************************************************************/
/* moca_getIfAcaStatus() function */
/**
* @description Gets the MoCA ACA status after the starting the ACA process.
*
* @param[in] interfaceIndex - Index of the MoCA Interface.
* @param[out] pacaStat - Variable that represents a pointer to structure of type moca_aca_stat_t for Applied Configuration Parameters for MOCA ACA Process and ACA Process stats.
* <pre>
*                The members of the moca_aca_stat_t structure are defined below.
*
*                acaCfg                            - The current configuration on ACA process started.
*                                                    The members of the moca_aca_cfg_t structure are defined below.
*                                                    NodeID                            - The NodeID where we want to start the ACA testing.
*                                                                                        The range of acceptable values is 0 to n, where n is a unsigned integer value.
*
*                                                    Type                              - The Probe Type could be Enum EVM=1 or Quite=0.
*                                                                                        The range of acceptable values is 0 to 1 based on PROBE_TYPE enum type value. The enum PROBE_TYPE defined below.
*                                                                                        PROBE_QUITE = 0
*                                                                                        PROBE_EVM = 1
*
*                                                    Channel                           - The Channel on which ACA test should start.
*                                                                                        The range of acceptable values is 0 to n, where n is a unsigned integer value.
*
*                                                    ReportNodes                       - Specifies the MoCA Nodes that are requested to be part of the channel assessment: Setting bits corresponding to Node IDs of these MoCA Nodes to 1 (LSB corresponds to Node ID 0x0).
*                                                                                        For example: 0000 0000 0000 0101 can be represented as 0x0005, Node 0 and Node 2.
*                                                                                        The range of acceptable values is 0 to n, where n is a unsigned long value.
*
*                                                    DestinationMACAddress[18]         - Indicate the Destination Address (DA) of Ethernet packets of the PQoS Flow for which this node is the ingress node.
*                                                                                        DestinationMACAddress is a 8 bytes character array. The MAC Address should be in the format AA:BB:CC:DD:EE:FF (colon-separated).
*
*                                                    ACAStart                          - The ACAStart will indiacte to start the ACA process or not.
*                                                                                        If the start the ACA process is enabled, the ACAStart Flag is TRUE for config; otherwise, it is FALSE for no action.
*
*                stat                              - Stats of the ACA process.
*                                                    The range of acceptable values is 0 to 4. Results equivalent to acceptables values are SUCCESS=0, Fail-BADCHANNEL=1,Fail-NoEVMPROBE=2, Fail=3 and In-Progress=4.
*
*                ACAPowProfile[512]                - Power Profile Representation for each channel.
*                                                    It is a array of integer named ACAPowProfile consisting of 512 elements.
*                                                    Acceptable values for each elements is -n to n, where n is a signed integer value.
*
*                ACATrapCompleted                  - mocaIfAcaStatusTrapCompleted ReadOnly parameter.
*                                                    If the PowerPorfile is ready, the ACATrapComplete Flag is TRUE; otherwise, it is FALSE.
* </pre>
*
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected.
*
* @remark The caller is responsible for providing a valid memory location for the pacaStat parameter.
*         \n The function will populate this structure with the retrieved MoCA interface information.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system calls.
*       \n It should probably just send a message to a driver event handler task.
*
*/
int moca_getIfAcaStatus(int interfaceIndex,moca_aca_stat_t *pacaStat);

/****************************************************************/
/* moca_getIfScmod() function */
/**
* @description Gets the MoCA SCMODE status after the starting the ACA process.
*
* @param[in] interfaceIndex - The index of the MOCA interface.
* @param[out] pnumOfEntries - A pointer to an integer that will be filled with the number of entries in the statistics array.
* @param[out] ppscmodStat - A pointer to a pointer that will be set to the array of moca_scmod_stat_t structures containing the status of test between Transmit and recieve node.
* <pre>
*                The members of the moca_scmod_stat_t structure are defined below.
*
*                TxNode                            - The NODE ID of Transmit MOCA NODE.
*                                                    The range of acceptable values is -n to n, where n is a signed integer value.
*
*                RxNode                            - The Node ID of Receive MOCA Node.
*                                                    The range of acceptable values is -n to n, where n is a signed integer value.
*
*                Channel                           - The Primary channel or Secondary channel used to calculate the NPER and VLPER.
*                                                    The range of acceptable values is -n to n, where n is a signed integer value.
*
*                UCHAR Mod[512]                    - Subcarrier MODULATION used to calcuate the NPER and VLPER between two node.
*                                                    It is a array of integer named Mod consisting of 512 elements.
*                                                    Acceptable values for each elements is 0 to n, where n is a unsigned long value.
*
*                UCHAR Nper[512]                   - Each NPER of between two nodes on Corresponding Channel.
*                                                    It is a array of integer named Nper consisting of 512 elements.
*                                                    Acceptable values for each elements is 0 to n, where n is a unsigned long value.
*
*                UCHAR Vlper[512]                  - Each Vlper of between two nodes on Corresponding Channel.
*                                                    It is a array of integer named Vlper consisting of 512 elements.
*                                                    Acceptable values for each elements is 0 to n, where n is a unsigned long value.
* </pre>
*
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected.
*
* @remark The caller is responsible for providing a valid memory location for the ppscmodStat parameter.
*         \n The function will populate this structure with the retrieved MoCA interface information.
*
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system calls.
*       \n It should probably just send a message to a driver event handler task.
*
*/

int moca_getIfScmod(int interfaceIndex,int *pnumOfEntries,moca_scmod_stat_t **ppscmodStat);


/** @} */  //END OF GROUP MOCA_HAL_APIS
#endif

