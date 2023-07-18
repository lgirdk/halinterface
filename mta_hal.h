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

/**
* @file mta_hal.h
* @author cisco
* @brief For CCSP Component:  CcspMtaAgent
*
*@description This header file gives the function call prototypes and
structure definitions used for the RDK-Broadband
hardware abstraction layer for Cable Modem
*/
/**********************************************************************

    module: mta_hal.h

        For CCSP Component:  CcspMtaAgent

    ---------------------------------------------------------------

    description:

        This header file gives the function call prototypes and
        structure definitions used for the RDK-Broadband
        hardware abstraction layer for Cable Modem

    ---------------------------------------------------------------

    environment:

        This HAL layer is intended to support cable modem drivers
        through an open API.
        Changes may be needed to support different hardware enviornments.

    ---------------------------------------------------------------

    author:

        Cisco

**********************************************************************/


#ifndef __MTA_HAL_H__
#define __MTA_HAL_H__

#include <stdint.h>
#include <netinet/in.h>

/**********************************************************************
               CONSTANT DEFINITIONS
**********************************************************************/
/**
* @defgroup mta_hal MTA HAL
*
* This module provides the function call prototypes and structure definitions used for the  MTA hardware abstraction layer.
*
* @defgroup MTA_HAL_TYPES  MTA HAL Data Types
* @ingroup  mta_hal
*
* @defgroup MTA_HAL_APIS   MTA HAL  APIs
* @ingroup  mta_hal
*
**/


/**
 * @addtogroup MTA_HAL_TYPES
 * @{
 */

#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef CHAR
#define CHAR  char
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef BOOLEAN
#define BOOLEAN  UCHAR
#endif

#ifndef INT
#define INT   int
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

#ifndef IPV4_ADDRESS_SIZE
#define  IPV4_ADDRESS_SIZE                          4
#endif

#ifndef MTA_HAL_SHORT_VALUE_LEN
#define  MTA_HAL_SHORT_VALUE_LEN   16
#endif

#ifndef MTA_HAL_LONG_VALUE_LEN
#define  MTA_HAL_LONG_VALUE_LEN   64
#endif

#ifndef ANSC_IPV4_ADDRESS
/*
 * While we're trying really hard to smooth the procedure of switch-over from IPv4 to IPv4, there
 * are many places where using the IP address as an integer for comparision and calculation is much
 * easier than array-based operation.
 */
#define  ANSC_IPV4_ADDRESS                                                                  \
         union                                                                              \
         {                                                                                  \
            unsigned char           Dot[IPV4_ADDRESS_SIZE];                                 \
            uint32_t                Value;                                                  \
         }
#endif

/* dect */
/*
 *  DH  This is not the right place to place platform/HAL
 *      implementation specific definitions here.
 *      This kind of definitions belongs to hal.c, or another
 *      header file which is included by hal.c
 *
 *  Fix the other RDK-B vendor's code!!!
 *
typedef enum
{
    SNMPA_REQ_USER_HANDLER,
    SNMPA_REQ_GET_VAL_BY_OID,
    SNMPA_REQ_GETNEXT_VAL_BY_OID,
    SNMPA_REQ_SET_STRING_BY_OID,
    SNMPA_REQ_SET_BYTE_BY_OID,
    SNMPA_REQ_SET_OID_BY_OID,
    SNMPA_REQ_SET_INT_BY_OID,
    SNMPA_REQ_SET_UINT_BY_OID,
    SNMPA_REQ_SET_SHORT_BY_OID,
    SNMPA_REQ_SET_USHORT_BY_OID,
    SNMPA_REQ_SET_IP_BY_OID,
    SNMPA_REQ_ENGINE_GET_MY_ID,
    SNMPA_REQ_ENGINE_GET_MY_BOOTS,
    SNMPA_REQ_ENGINE_GET_MY_TIME,
    SNMPA_REQ_TLV11_CONF,
    SNMPA_REQ_TLV64_CONF,
    SNMPA_REQ_SET_MY_ENGINE_INFO,
}  SnmpaIfRequest_e;
 */

/*
 *  DH  This is also questionable why we have to define this kind of
 *      platform specific capacility in the hal header file
 */
#define DECT_MAX_HANDSETS 5

/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/

typedef struct
_MTAMGMT_MTA_DECT
{
    ULONG                           RegisterDectHandset;
    ULONG                           DeregisterDectHandset;
    char                            HardwareVersion[64];
    char                            RFPI[64];
    char                            SoftwareVersion[64];
    char                            PIN[64];
}
MTAMGMT_MTA_DECT, *PMTAMGMT_MTA_DECT;

typedef  struct
_MTAMGMT_MTA_HANDSETS_INFO
{
    ULONG                           InstanceNumber;
    BOOLEAN                         Status;
    char                            LastActiveTime[64];
    char                            HandsetName[64];
    char                            HandsetFirmware[64];
    char                            OperatingTN[64];
    char                            SupportedTN[64];
}
MTAMGMT_MTA_HANDSETS_INFO,  *PMTAMGMT_MTA_HANDSETS_INFO;

typedef  struct
_MTAMGMT_MTA_DHCP_INFO
{
    ANSC_IPV4_ADDRESS               IPAddress;
    CHAR                            BootFileName[64];
    CHAR                            FQDN[64];
    ANSC_IPV4_ADDRESS               SubnetMask;
    ANSC_IPV4_ADDRESS               Gateway;
    ULONG                           LeaseTimeRemaining;
    CHAR                            RebindTimeRemaining[64];
    CHAR                            RenewTimeRemaining[64];
    ANSC_IPV4_ADDRESS               PrimaryDNS;
    ANSC_IPV4_ADDRESS               SecondaryDNS;
    CHAR                            DHCPOption3[64];
    CHAR                            DHCPOption6[64];
    CHAR                            DHCPOption7[64];
    CHAR                            DHCPOption8[64];
    CHAR                            PCVersion[64];
    CHAR                            MACAddress[64];
    ANSC_IPV4_ADDRESS               PrimaryDHCPServer;
    ANSC_IPV4_ADDRESS               SecondaryDHCPServer;
}
MTAMGMT_MTA_DHCP_INFO, *PMTAMGMT_MTA_DHCP_INFO;

typedef  struct
_MTAMGMT_MTA_DHCPv6_INFO
{
    CHAR                            IPV6Address[INET6_ADDRSTRLEN];
    CHAR                            BootFileName[64];
    CHAR                            FQDN[64];
    CHAR                            Prefix[INET6_ADDRSTRLEN];
    CHAR                            Gateway[INET6_ADDRSTRLEN];
    ULONG                           LeaseTimeRemaining;
    CHAR                            RebindTimeRemaining[64];
    CHAR                            RenewTimeRemaining[64];
    CHAR                            PrimaryDNS[INET6_ADDRSTRLEN];
    CHAR                            SecondaryDNS[INET6_ADDRSTRLEN];
    CHAR                            DHCPOption3[64];
    CHAR                            DHCPOption6[64];
    CHAR                            DHCPOption7[64];
    CHAR                            DHCPOption8[64];
    CHAR                            PCVersion[64];
    CHAR                            MACAddress[64];
    CHAR                            PrimaryDHCPv6Server[INET6_ADDRSTRLEN];
    CHAR                            SecondaryDHCPv6Server[INET6_ADDRSTRLEN];
}
MTAMGMT_MTA_DHCPv6_INFO, *PMTAMGMT_MTA_DHCPv6_INFO;

typedef  struct
_MTAMGMT_MTA_SERVICE_FLOW
{
    ULONG                           SFID;                         /* Id */
    CHAR                            ServiceClassName[256];
    CHAR                            Direction[16];               /* Upstream, Downstream */
    ULONG                           ScheduleType;
    BOOLEAN                         DefaultFlow;
    ULONG                           NomGrantInterval;
    ULONG                           UnsolicitGrantSize;
    ULONG                           TolGrantJitter;
    ULONG                           NomPollInterval;
    ULONG                           MinReservedPkt;
    ULONG                           MaxTrafficRate;
    ULONG                           MinReservedRate;
    ULONG                           MaxTrafficBurst;
    CHAR                            TrafficType[64];              /* SIP, RTP */
    ULONG                           NumberOfPackets;              /* packet count */
}
MTAMGMT_MTA_SERVICE_FLOW, *PMTAMGMT_MTA_SERVICE_FLOW;

typedef  struct
_MTAMGMT_MTA_CALLS
{
    CHAR                            Codec[64];                    /* local side codec used for the call */
    CHAR                            RemoteCodec[64];              /* remote side codec used for the call */
    CHAR                            CallStartTime[64];            /* start time of a call */
    CHAR                            CallEndTime[64];              /* end time of a call */
    CHAR                            CWErrorRate[MTA_HAL_SHORT_VALUE_LEN];              /* ratio of useful signal to background noise */
    CHAR                            PktLossConcealment[MTA_HAL_SHORT_VALUE_LEN];       /* ratio of pkt lost to total expected */
    BOOLEAN                         JitterBufferAdaptive;         /* JBA used or not */
    BOOLEAN                         Originator;                   /* originating side of the call or not */
    ANSC_IPV4_ADDRESS               RemoteIPAddress;              /* remote IP */
    ULONG                           CallDuration;                 /* length of the call in minutes */
    CHAR                            CWErrors[MTA_HAL_SHORT_VALUE_LEN];                     /* code word errors on this channel */
    CHAR                            SNR[MTA_HAL_SHORT_VALUE_LEN];                          /* signal to noise ratio * 256 */
    CHAR                            MicroReflections[MTA_HAL_SHORT_VALUE_LEN];             /* return loss measurement */
    CHAR                            DownstreamPower[MTA_HAL_SHORT_VALUE_LEN];              /* downstream power in dbmv */
    CHAR                            UpstreamPower[MTA_HAL_SHORT_VALUE_LEN];                /* upstream power in dbmv */
    CHAR                            EQIAverage[MTA_HAL_SHORT_VALUE_LEN];                   /* EQI average */    
    CHAR                            EQIMinimum[MTA_HAL_SHORT_VALUE_LEN];                   /* EQI minimum */
    CHAR                            EQIMaximum[MTA_HAL_SHORT_VALUE_LEN];                   /* EQI maximum */
    CHAR                            EQIInstantaneous[MTA_HAL_SHORT_VALUE_LEN];             /* EQI instantaneous */
    CHAR                            MOS_LQ[MTA_HAL_SHORT_VALUE_LEN];                       /* mean opinion score of listening quality, 10-50 */
    CHAR                            MOS_CQ[MTA_HAL_SHORT_VALUE_LEN];                       /* mean opinion score of conversational quality, 10-50 */
    CHAR                            EchoReturnLoss[MTA_HAL_SHORT_VALUE_LEN];               /* residual echo return loss, in db */
    CHAR                            SignalLevel[MTA_HAL_SHORT_VALUE_LEN];                  /* voice signal relative level, in db */
    CHAR                            NoiseLevel[MTA_HAL_SHORT_VALUE_LEN];                   /* noise relative level, in db */
    CHAR                            LossRate[MTA_HAL_SHORT_VALUE_LEN];                     /* fraction of RTP data packet loss * 256 */
    CHAR                            DiscardRate[MTA_HAL_SHORT_VALUE_LEN];                  /* fraction of RTP data packet discarded * 256 */
    CHAR                            BurstDensity[MTA_HAL_SHORT_VALUE_LEN];                 /* fraction of bursting data packet * 256 */
    CHAR                            GapDensity[MTA_HAL_SHORT_VALUE_LEN];                   /* fraction of packets within inter-burst gap * 256 */
    CHAR                            BurstDuration[MTA_HAL_SHORT_VALUE_LEN];                /* mean duration of bursts, in milliseconds */
    CHAR                            GapDuration[MTA_HAL_SHORT_VALUE_LEN];                  /* mean duration of gaps, in milliseconds */
    CHAR                            RoundTripDelay[MTA_HAL_SHORT_VALUE_LEN];               /* most recent measured RTD, in milliseconds */
    CHAR                            Gmin[MTA_HAL_SHORT_VALUE_LEN];                         /* local gap threshold */
    CHAR                            RFactor[MTA_HAL_SHORT_VALUE_LEN];                      /* voice quality evaluation for this RTP session */
    CHAR                            ExternalRFactor[MTA_HAL_SHORT_VALUE_LEN];              /* voice quality evaluation for segment on network external to this RTP session */
    CHAR                            JitterBufRate[MTA_HAL_SHORT_VALUE_LEN];                /* adjustment rate of jitter buffer, in milliseconds */
    CHAR                            JBNominalDelay[MTA_HAL_SHORT_VALUE_LEN];               /* nominal jitter buffer length, in milliseconds */
    CHAR                            JBMaxDelay[MTA_HAL_SHORT_VALUE_LEN];                   /* maximum jitter buffer length, in milliseconds */
    CHAR                            JBAbsMaxDelay[MTA_HAL_SHORT_VALUE_LEN];                /* absolute maximum delay, in milliseconds */
    CHAR                            TxPackets[MTA_HAL_SHORT_VALUE_LEN];                    /* count of transmitted packets */
    CHAR                            TxOctets[MTA_HAL_SHORT_VALUE_LEN];                     /* count of transmitted octet packets */
    CHAR                            RxPackets[MTA_HAL_SHORT_VALUE_LEN];                    /* count of received packets */
    CHAR                            RxOctets[MTA_HAL_SHORT_VALUE_LEN];                     /* count of received octet packets */
    CHAR                            PacketLoss[MTA_HAL_SHORT_VALUE_LEN];                   /* count of lost packets */
    CHAR                            IntervalJitter[MTA_HAL_SHORT_VALUE_LEN];               /* stat variance of packet interarrival time, in milliseconds */
    CHAR                            RemoteIntervalJitter[MTA_HAL_SHORT_VALUE_LEN];         /* remote sie IntervalJitter (see local side) */
    CHAR                            RemoteMOS_LQ[MTA_HAL_SHORT_VALUE_LEN];                 /* remote side MOS_LQ (see local side) */
    CHAR                            RemoteMOS_CQ[MTA_HAL_SHORT_VALUE_LEN];                 /* remote side MOS_CQ (see local side) */
    CHAR                            RemoteEchoReturnLoss[MTA_HAL_SHORT_VALUE_LEN];         /* remote side EchoReturnLoss (see local side) */
    CHAR                            RemoteSignalLevel[MTA_HAL_SHORT_VALUE_LEN];            /* remote side SignalLevel (see local side) */
    CHAR                            RemoteNoiseLevel[MTA_HAL_SHORT_VALUE_LEN];             /* remote side NoiseLevel (see local side) */
    CHAR                            RemoteLossRate[MTA_HAL_SHORT_VALUE_LEN];               /* remote side LossRate (see local side) */
    CHAR                            RemotePktLossConcealment[MTA_HAL_SHORT_VALUE_LEN];     /* remote side PktLossConcealment (see local side) */
    CHAR                            RemoteDiscardRate[MTA_HAL_SHORT_VALUE_LEN];            /* remote side DiscardRate (see local side) */
    CHAR                            RemoteBurstDensity[MTA_HAL_SHORT_VALUE_LEN];           /* remote side BurstDensity (see local side) */
    CHAR                            RemoteGapDensity[MTA_HAL_SHORT_VALUE_LEN];             /* remote side GapDensity (see local side) */
    CHAR                            RemoteBurstDuration[MTA_HAL_SHORT_VALUE_LEN];          /* remote side BurstDuration (see local side) */
    CHAR                            RemoteGapDuration[MTA_HAL_SHORT_VALUE_LEN];            /* remote side GapDuration (see local side) */
    CHAR                            RemoteRoundTripDelay[MTA_HAL_SHORT_VALUE_LEN];         /* remote side RoundTripDelay (see local side) */
    CHAR                            RemoteGmin[MTA_HAL_SHORT_VALUE_LEN];                   /* remote side Gmin (see local side) */
    CHAR                            RemoteRFactor[MTA_HAL_SHORT_VALUE_LEN];                /* remote side RFactore (see local side) */
    CHAR                            RemoteExternalRFactor[MTA_HAL_SHORT_VALUE_LEN];        /* remote side ExternalRFactor (see local side) */
    BOOLEAN                         RemoteJitterBufferAdaptive;   /* remote side JitterBufferAdaptive (see local side) */
    CHAR                            RemoteJitterBufRate[MTA_HAL_SHORT_VALUE_LEN];          /* remote side JitterBufRate (see local side) */
    CHAR                            RemoteJBNominalDelay[MTA_HAL_SHORT_VALUE_LEN];         /* remote side JBNominalDelay (see local side) */
    CHAR                            RemoteJBMaxDelay[MTA_HAL_SHORT_VALUE_LEN];             /* remote side JBMaxDelay (see local side) */
    CHAR                            RemoteJBAbsMaxDelay[MTA_HAL_SHORT_VALUE_LEN];          /* remote side JBAbsMaxDelay (see local side) */
}
MTAMGMT_MTA_CALLS, *PMTAMGMT_MTA_CALLS;

typedef  struct
_MTAMGMT_MTA_LINETABLE_INFO
{
    ULONG                           InstanceNumber;
    ULONG                           LineNumber;
    ULONG                           Status;                       /* 1 = OnHook; 2 = OffHook */
    CHAR                            HazardousPotential[128];       /* HEMF Test Passed, Not Started */
    CHAR                            ForeignEMF[128];               /* FEMF Test Passed, Not Started */
    CHAR                            ResistiveFaults[128];         /* Not Started */
    CHAR                            ReceiverOffHook[128];          /* Not Started */
    CHAR                            RingerEquivalency[64];        /* Not Started */
    CHAR                            CAName[64];
    ULONG                           CAPort;
    ULONG                           MWD;
    ULONG                           CallsNumber;
    PMTAMGMT_MTA_CALLS              pCalls;
    ULONG                           CallsUpdateTime;
    ULONG                           OverCurrentFault;            /* 1 = Normal,2 = Fault */
}
MTAMGMT_MTA_LINETABLE_INFO, *PMTAMGMT_MTA_LINETABLE_INFO;

typedef  struct
_MTAMGMT_MTA_CALLP
{
    CHAR                            LCState[64];                  /* In Use, Idle, Out of Service */
    CHAR                            CallPState[64];               /* In Service, OOS */
    CHAR                            LoopCurrent[64];              /* Boosted */
}
MTAMGMT_MTA_CALLP,  *PMTAMGMT_MTA_CALLP;

typedef  struct
_MTAMGMT_MTA_DSXLOG
{
    CHAR                            Time[64];
    CHAR                            Description[128];
    ULONG                           ID;
    ULONG                           Level;
}
MTAMGMT_MTA_DSXLOG,  *PMTAMGMT_MTA_DSXLOG;

typedef  struct
_MTAMGMT_MTA_MTALOG_FULL
{
    ULONG                           Index;
    ULONG                           EventID;
    CHAR                            EventLevel[64];
    CHAR                            Time[64];
    CHAR*                           pDescription;
}
MTAMGMT_MTA_MTALOG_FULL,  *PMTAMGMT_MTA_MTALOG_FULL;

typedef  struct
_MTAMGMT_MTA_BATTERY_INFO
{
    CHAR                            ModelNumber[32];
    CHAR                            SerialNumber[32];
    CHAR                            PartNumber[32];
    CHAR                            ChargerFirmwareRevision[32];
}
MTAMGMT_MTA_BATTERY_INFO,  *PMTAMGMT_MTA_BATTERY_INFO;

#define MTA_LINENUMBER 8
typedef  enum {
	MTA_INIT=0,
	MTA_START=1,
	MTA_COMPLETE=2,
	MTA_ERROR=3,
	MTA_REJECTED=4
} MTAMGMT_MTA_STATUS;

typedef enum{
        MTA_PROVISIONED=0,
        MTA_NON_PROVISIONED=1
} MTAMGMT_MTA_PROVISION_STATUS;
/**
 * @}
 */

/**
 * @addtogroup MTA_HAL_APIS
 * @{
 */


/**********************************************************************************
 *
 *  MTA Subsystem level function prototypes
 *
**********************************************************************************/

/* mta_hal_InitDB :  */
/**
* @description Retrieves the global information for all shared DBs and makes them accessible locally.
* @param None
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT   mta_hal_InitDB(void);

/*  mta_hal_GetDHCPInfo : */
/**
* @description Retrieve all the relevant DHCP info for MTA.
* @param[out] pInfo pointer to PMTAMGMT_MTA_DHCP_INFO that will hold all DHCP info for MTA, to be returned
*                   <pre>
*                   The structure members are defined as below:
*                       IPAddress            - It is a ANSC_IPV4_ADDRESS union type value that represents the IP Address.  The union members are defined as below:
*                                                     Dot - An unsigned character array of size 4. Possible values: "IPAddress.Dot = {192, 168, 0, 100}".
*                                                     Value - A 32 bit unsigned integer value.
*                       BootFileName         - It is a 64 bytes character array that represents the Boot File Name. Possible values: "ccsp.boot".
*                       FQDN                 - It is a 64 bytes character array that represents the FQDN. Possible values: "www.example.com"
*                       SubnetMask           - It is a ANSC_IPV4_ADDRESS union type value that represents the Subnet Mask.  The union members are defined as below:
*                                                     Dot - An unsigned character array of size 4.  Possible values: "SubnetMask.Dot = {255, 255, 255, 0}".
*                                                     Value - A 32 bit unsigned integer value.
*                       Gateway              - It is a ANSC_IPV4_ADDRESS union type value that represents the Gateway.  The union members are defined as below:
*                                                     Dot - An unsigned character array of size 4. Possible values: "Gateway.Dot={192, 168, 0, 1}".
*                                                     Value - A 32 bit unsigned integer value.
*                       LeaseTimeRemaining   - It is an unsigned long value that represents the Lease Time Remaining. The range of acceptable values is 0 to n, where n is an unsigned long value. Possible values: 3600.
*                       RebindTimeRemaining  - It is a 64 bytes character array that represents the Rebind Time Remaining. The range of acceptable values is 0 to n. Possible values: 3700.
*                       RenewTimeRemaining   - It is a 64 bytes character array that represents the Renew Time Remaining. The range of acceptable values is 0 to n. Possible values: 1200.
*                       PrimaryDNS           - It is a ANSC_IPV4_ADDRESS union type value that represents the Primary DNS. The union members are defined as below:
*                                                     Dot - An unsigned character array of size 4. Possible values: "10.0.1.8".
*                                                     Value - A 32 bit unsigned integer value.
*                       SecondaryDNS         - It is a ANSC_IPV4_ADDRESS union type value that represents the Secondary DNS. The union members are defined as below:
*                                                     Dot - An unsigned character array of size 4. Possible values: "10.0.1.1".
*                                                     Value - A 32 bit unsigned integer value.
*                       DHCPOption3          - It is a 64 bytes character array that specifies the IP address of the default gateway(router) for the DHCP client to use for internet access and communication with devices outside the local network. Example: "192.168.1.1".
*                       DHCPOption6          - It is a 64 bytes character array that specifies the IP Address of a DNS servers that the DNS client should use for domain name resolution. Possible values: "8.8.8.8".
*                       DHCPOption7          - It is a 64 bytes character array that specifies the IP address of a log server that the DHCP client can use for loggin purpose. Possible values: "192.168.1.100".
*                       DHCPOption8          - It is a 64 bytes character array that specifies the IP address of a cookie server that the DHCP client can use to retrieve cookies. Possible values: "10.0.0.15".
*                       PCVersion            - It is a 64 bytes character array that represents the version of a PC. Possible values: "2.5.1".
*                       MACAddress           - It is a 64 bytes character array that represents the MAC Address. Possible values: "00:1A:2B:11:22:33".
*                       PrimaryDHCPServer    - It is a ANSC_IPV4_ADDRESS union type value that represents the Primary DHCP server. The union members are defined as below:
*                                                     Dot - An unsigned character array of size 4. Possible values: "192.168.16.55".
*                                                     Value - A 32 bit unsigned integer value.
*                       SecondaryDHCPServer  - It is a ANSC_IPV4_ADDRESS union type value that represents the Secondary DHCP Server. The union members are defined as below:
*                                                     Dot - An unsigned character array of size 4. Possible values: "192.168.16.215".
*                                                     Value - A 32 bit unsigned integer value.
*                   </pre>
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_GetDHCPInfo(PMTAMGMT_MTA_DHCP_INFO pInfo);

/*  mta_hal_GetDHCPInfo : */
/**
* @description Retrieve all the relevant DHCP info for MTA.
* @param[out] pInfo pointer to PMTAMGMT_MTA_DHCP_INFO that will hold all DHCP info for MTA, to be returned
*                   <pre>
*                   The structure members are defined as below:
*                         IPV6Address            - It is a 46 bytes character array represents the IPV6 Address. Possible values: "2012:cafe:100::1".
*                         BootFileName           - It is a 64 bytes character array that represents the Boot File Name. Possible values: "ccsp.boot".
*                         FQDN                   - It is a 64 bytes character array that represents the FQDN. Possible values: "www.example.com".
*                         Prefix                 - It is a 46 bytes character array represents the prefix. Possible values: "/64".
*                         Gateway                - It is a 46 bytes character array that represents the Gateway. Possible values: "{192, 168, 0, 1}".
*                         LeaseTimeRemaining     - It is an unsigned long value that represents the Lease Time Remaining. The range of acceptable values is 0 to n, where n is an unsigned long value. Possible values: 3600.
*                         RebindTimeRemaining    - It is a 64 bytes character array that represents the Rebind Time Remaining. The range of acceptable values is 0 to n. Possible values: 3700.
*                         RenewTimeRemaining     - It is a 64 bytes character array that represents the Renew Time Remaining. The range of acceptable values is 0 to n. Possible values: 1200.
*                         PrimaryDNS             - It is a 46 bytes character array that represents the Primary DNS. Possible values: "2001:4860:4860::8888".
*                         SecondaryDNS           - It is a 46 bytes character array that represents the Secondary DNS. Possible values: "2001:4860:4860::8844".
*                         DHCPOption3            - It is a 64 bytes character array that provides information about the IPv6 address prefix to be used by the client for autoconfiguration. Possible values: "2001:db8:abcd::/48".
*                         DHCPOption6            - It is a 64 bytes character array that supplies the IPv6 addresses of DNS servers that the DHCPv6 client should use for domain name resolution. Possible values: "DNS Server 1: 2001:4860:4860::8888, DNS Server 2: 2001:4860:4860::8844".
*                         DHCPOption7            - It is a 64 bytes character array that provides a list of domain names that the DHCPv6 client can search when performing domain name resolution. Possible values: "example.com".
*                         DHCPOption8            - It is a 64 bytes character array that conveys the maximum transmission unit (MTU) for the client's network interface. Possible values: 1500.
*                         PCVersion              - It is a 64 bytes character array that represents the PC version. Possible values: "3.5".
*                         MACAddress             - It is a 64 bytes character array that represents the MAC Address. Possible values: "00:1A:2B:11:22:33".
*                         PrimaryDHCPv6Server    - It is a 46 bytes character array that represents the Primary DHCPv6 server. It is a server-specific value. Possible values: "00:01:00:01:2a:3b:4c:5d:6e:7f".
*                         SecondaryDHCPv6Server  - It is a 46 bytes character array that represents the Secondary DHCPv6 Server. It is a server-specific value. Possible values: "00:01:2a:3b:4c:5e".
*                   </pre>
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/

INT mta_hal_GetDHCPV6Info(PMTAMGMT_MTA_DHCPv6_INFO pInfo);

/*  mta_hal_LineTableGetNumberOfEntries :  */
/**
* @description Get number of entries in the line table.
* @param None
*
* @return ULONG - number of entries
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
ULONG mta_hal_LineTableGetNumberOfEntries(void);

/* mta_hal_LineTableGetEntry : */
/**
* @description Get entry of the line table at the given index
* @param[in] INT Index - index to the table entry. The value ranges from 0 to n. Possible values: 3.
* @param[out] PMTAMGMT_MTA_LINETABLE_INFO pEntry - entry info, to be returned.
*                                                  \n The structure members are defined below:
*                                                  <pre>
*                                                         InstanceNumber     - It is a unsigned long integer value that represents the instance number. The value ranges from 0 to n. Possible values: 4.
*                                                         LineNumber         - It is a unsigned long integer value that represents the line number. The value ranges from 0 to n. Possible values: 3.
*                                                         Status             - It is a unsigned long integer value that defines the status. The value ranges from 0 to n. Possible values: 2.
*                                                         HazardousPotential - It is a 128 bytes of character value that represents the Hazardous potential. It is a vendor-specific value.
*                                                         ForeignEMF         - It is a 128 bytes of character value that represents the foreign EMF. It is a vendor-specific value.
*                                                         ResistiveFaults    - It is a 128 bytes of character value that represents the resistive faults. It is a vendor-specific value.
*                                                         ReceiverOffHook    - It is a 128 bytes of character value that represents the receiver off hook. It is a vendor-specific value.
*                                                         RingerEquivalency  - It is a 64 bytes of character value that represents the Ringer equivalency. It is a vendor-specific value.
*                                                         CAName             - It is a 64 bytes of character value that represents the CA name. It is a vendor-specific value.
*                                                         CAPort             - It is a unsigned long integer value that represents the CA port. The value ranges from 0 to n, where n is an unsigned long value. Possible values: 80.
*                                                         MWD                - It is a unsigned long integer value that represents the MWD. The value ranges from 0 to n, where n is an unsigned long value. It is a vendor-specific value.
*                                                         CallsNumber        - It is a unsigned long integer value that represents the calls number. The value ranges from 0 to n, where n is an unsigned long value. It is a vendor-specific value.
*                                                         pCalls             - It is a structure PMTAMGMT_MTA_CALLS that defines the MTA calls. It is a vendor-specific value.
*                                                         CallsUpdateTime    - It is a unsigned long integer value that represents the update time of calls. The value ranges from 0 to n, where n is an unsigned long value. It is a vendor-specific value.
*                                                         OverCurrentFault   - It is a unsigned long integer value that represents the over current fault. The value ranges from 0 to n. Possible values: 1, 2.
*                                                  </pre>
* @return The status of the operation
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT   mta_hal_LineTableGetEntry(ULONG Index, PMTAMGMT_MTA_LINETABLE_INFO pEntry);

/*  mta_hal_TriggerDiagnostics : */
/**
* @description Trigger GR909 Diagnostics
* @param[in] INT Index - line number to perform the GR909 diagnostics on. The value ranges from 0 to n, where n is an unsigned long value. Possible values: 3.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT   mta_hal_TriggerDiagnostics(ULONG Index);

/*  mta_hal_GetServiceFlow :  */
/**
* @description Get all the service flow info
* @param[out] ULONG* Count - number of service flow entries, to be returned
* @param[out] PMTAMGMT_MTA_SERVICE_FLOW *ppCfg - service flow info, to be returned.
*                                                <pre>
*                                                The structure members are defined below:
*                                                       SFID               - It is a unsigned long integer value that represents the service flow ID. It is a vendor-specific value.
*                                                       ServiceClassName   - It is a 256 bytes of character value that represents the service class name. It is a vendor-specific value.
*                                                       Direction          - It is a 16 bytes of character value that represents the direction. It is a vendor-specific value.
*                                                       ScheduleType       - It is a unsigned long integer value that represents the schedule type. It is a vendor-specific value.
*                                                       DefaultFlow        - It is a boolean value that specifies the default flow. Possible values: "{TRUE, FLASE}".
*                                                       NomGrantInterval   - It is a unsigned long integer value that represents the NomGrantInterval. It is a vendor-specific value.
*                                                       UnsolicitGrantSize - It is a unsigned long integer value that represents the UnsolicitGrantSize. It is a vendor-specific value.
*                                                       TolGrantJitter     - It is a unsigned long integer value that represents the TolGrantJitter. It is a vendor-specific value.
*                                                       NomPollInterval    - It is a unsigned long integer value that represents the NomPollInterval. It is a vendor-specific value.
*                                                       MinReservedPkt     - It is a unsigned long integer value that represents the minimum reserved packet. It is a vendor-specific value.
*                                                       MaxTrafficRate     - It is a unsigned long integer value that represents the maximum traffic rate. It is a vendor-specific value.
*                                                       MinReservedRate    - It is a unsigned long integer value that represents the minimum reserved rate. It is a vendor-specific value.
*                                                       MaxTrafficBurst    - It is a unsigned long integer value that represents the maximum traffic burst. It is a vendor-specific value.
*                                                       TrafficType        - It is a 64 bytes of character value that represents the traffic type. It is a vendor-specific value.
*                                                       NumberOfPackets    - It is a unsigned long integer value that represents the number of packets. It is a vendor-specific value.
*                                                </pre>
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT   mta_hal_GetServiceFlow(ULONG* Count, PMTAMGMT_MTA_SERVICE_FLOW *ppCfg);

/*  mta_hal_DectGetEnable : */
/**
* @description Get info on if Dect is enabled
* @param[out] BOOLEAN* pBool - boolean value for enabled or not, to be returned. Possible values: "TRUE", "FALSE".
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT   mta_hal_DectGetEnable(BOOLEAN *pBool);

/*  mta_hal_DectSetEnable: */
/**
* @description Set Dect to boolean value passed in
* @param[in] BOOLEAN* bBool - boolean value for enabled or not, to be returned. Possible values: "TRUE", "FALSE".
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_DectSetEnable(BOOLEAN bBool);

/*  mta_hal_DectGetRegistrationMode: */
/**
* @description Set Dect to boolean value passed in
* @param[out] BOOLEAN* bBool - boolean value for enabled or not, to be returned. Possible values: "TRUE", "FALSE".
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_DectGetRegistrationMode(BOOLEAN* pBool);

/*  mta_hal_DectSetRegistrationMode: */
/**
* @description Set Dect registration mode
* @param[in] BOOLEAN* bBool - boolean value for enabled or not, to be returned. Possible values: "TRUE","FALSE".
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_DectSetRegistrationMode(BOOLEAN bBool);

/*  mta_hal_DectDeregisterDectHandset: */
/**
* @description Deregister Dect Handset
* @param[in] ULONG* uValue - unsigned long value for deregister dect handset. The value ranges from 0 to n, where n is an unsigned long value. It is a vendor-specific value.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_DectDeregisterDectHandset(ULONG uValue);

/*  mta_hal_GetDect: */
/**
* @description  Get Dect info
* @param[out] PMTAMGMT_MTA_DECT* pDect - info of Dect. pDect is a pointer to structure PMTAMGMT_MTA_DECT.
*                                        \n The structure members are defined as below:
*                                        <pre>
*                                               RegisterDectHandset   - It is a unsigned long integer value that represents the register dect handset. It is a vendor-specific value.
*                                               DeregisterDectHandset - It is a unsigned long integer value that represents the deregister dect handset. It is a vendor-specific value.
*                                               HardwareVersion       - It is a 64 bytes of character value that represents the hardware version. Possible values: "1.0.0".
*                                               RFPI                  - It is a 64 bytes of character value that represents the RFPI. It is a vendor-specific value.
*                                               SoftwareVersion       - It is a 64 bytes of character value that represents the software version. Possible values: "v1.0".
*                                               PIN                   - It is a 64 bytes of character value that represents the PIN. It is a vendor-specific value.
*                                        </pre>
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_GetDect(PMTAMGMT_MTA_DECT pDect);

/*  mta_hal_GetDectPIN: */
/**
* @description get Decr PIN
* @param[out] char* pPINString - PIN value. It is a vendor-specific value.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_GetDectPIN(char* pPINString);

/*  mta_hal_SetDectPIN: */
/**
* @description Set Dect PIN
* @param[in] char* pPINString - PIN value. It is a vendor-specific value.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_SetDectPIN(char* pPINString);

/*  mta_hal_GetHandsets: */
/**
* @description Get MTA handset info
* @param[in] ULONG* pulCount  - handset number. The value ranges from 0 to n, where n is a unsigned long value. It is a vendor-specific value.
* @param[out] PMTAMGMT_MTA_HANDSETS_INFO* ppHandsets - Info of MTA handset. ppHandsets is a pointer to structure PMTAMGMT_MTA_HANDSETS_INFO.
*                                                      <pre>
*                                                      The structure members are defined below:
*                                                           InstanceNumber  - It is a unsigned long integer value that represents the instance number. It is a vendor-specific value.
*                                                           Status          - It is a boolean value that defines the status. Possible values: "TRUE", "FALSE".
*                                                           LastActiveTime  - It is a 64 bytes of character value that represents the last active time. It is a vendor-specific value.
*                                                           HandSetName     - It is a 64 bytes of character value that represents the hand set name. It is a vendor-specific value.
*                                                           HandsetFirmware - It is a 64 bytes of character value that represents the hand set firmware. It is a vendor-specific value.
*                                                           OperatingTN     - It is a 64 bytes of character value that represents the operating TN. It is a vendor-specific value.
*                                                           SupportedTN     - It is a 64 bytes of character value that represents the supported TN. It is a vendor-specific value.
*                                                      </pre>
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_GetHandsets(ULONG* pulCount, PMTAMGMT_MTA_HANDSETS_INFO* ppHandsets);

/*  mta_hal_GetCalls : */
/**
* @description Retrieve all call info for the given instance number of LineTable
* @param[in] ULONG InstanceNumber - LineTable's instance number
* @param[out] ULONG *Count - number of entries(calls) for the call info array, to be returned.
* @param[out] PMTAMGMT_MTA_CALLS *ppCfg - Array of call info, to be returned
*                                         \n The structure members are defined below:
*                                         <pre>
*                                               Codec                      - It is a 64 bytes of character value that represents the local side codec used for the call. It is a vendor-specific value. Possible values: "Opus".
*                                               RemoteCodec                - It is a 64 bytes of character value that represents the remote side codec used for the call. It is a vendor-specific value. Possible values: "VOIP".
*                                               CallStartTime              - It is a 64 bytes of character value that represents the start time of a call. It is a vendor-specific value. Possible values: "09:30".
*                                               CallEndTime                - It is a 64 bytes of character value that represents the end time of a call. It is a vendor-specific value. Possible values: "10:30".
*                                               CWErrorRate                - It is a 16 bytes of character value that represents the ratio of useful signal to background noise. It is a vendor-specific value. Possible values: "26.02dB".
*                                               PktLossConcealment         - It is a 16 bytes of character value that represents the ratio of pkt lost to total expected. It is a vendor-specific value.
*                                               JitterBufferAdaptive       - It is a boolean value that specifies whether the JBA used or not. Possible values: "{TRUE, FALSE}".
*                                               Originator                 - It is a boolean value that represents the originating side of the call or not. Possible values: "{TRUE, FALSE}".
*                                               RemoteIPAddress            - It is a ANSC_IPV4_ADDRESS union type value that represents the Primary DHCP server. The union members are defined as below:
*                                                                            Dot - An unsigned character array of size 4. Possible values: "192.168.16.55".
*                                                                            Value - A 32 bit unsigned integer value.
*                                               CallDuration               - It is a unsigned integer value that represents the length of the call in minutes. It is a vendor-specific value.
*                                               CWErrors                   - It is a 16 bytes of character value that represents the code word errors on this channel. It is a vendor-specific value.
*                                               SNR                        - It is a 16 bytes of character value that represents the signal to noise ratio. It is a vendor-specific value.
*                                               MicroReflections           - It is a 16 bytes of character value that represents the return loss measurement. It is a vendor-specific value.
*                                               DownstreamPower            - It is a 16 bytes of character value that represents the downstream power in dbmv. It is a vendor-specific value.
*                                               UpstreamPower              - It is a 16 bytes of character value that represents the upstream power in dbmv. It is a vendor-specific value.
*                                               EQIAverage                 - It is a 16 bytes of character value that represents the EQI average. It is a vendor-specific value.
*                                               EQIMinimum                 - It is a 16 bytes of character value that represents the EQI minimum. It is a vendor-specific value.
*                                               EQIMaximum                 - It is a 16 bytes of character value that represents the EQI maximum. It is a vendor-specific value.
*                                               EQIInstantaneous           - It is a 16 bytes of character value that represents the EQI instantaneous. It is a vendor-specific value.
*                                               MOS_LQ                     - It is a 16 bytes of character value that represents the mean opinion score of listening quality. It is a vendor-specific value.
*                                               MOS_CQ                     - It is a 16 bytes of character value that represents the mean opinion score of conversational quality. It is a vendor-specific value.
*                                               EchoReturnLoss             - It is a 16 bytes of character value that represents the residual echo return loss, in db. It is a vendor-specific value.
*                                               SignalLevel                - It is a 16 bytes of character value that represents the voice signal relative level, in db. It is a vendor-specific value.
*                                               NoiseLevel                 - It is a 16 bytes of character value that represents the noise relative level, in db. It is a vendor-specific value.
*                                               LossRate                   - It is a 16 bytes of character value that represents the fraction of RTP data packet loss. It is a vendor-specific value.
*                                               DiscardRate                - It is a 16 bytes of character value that represents the fraction of RTP data packet discarded. It is a vendor-specific value.
*                                               BurstDensity               - It is a 16 bytes of character value that represents the fraction of bursting data packet. It is a vendor-specific value.
*                                               GapDensity                 - It is a 16 bytes of character value that represents the fraction of packets within inter-burst gap. It is a vendor-specific value.
*                                               BurstDuration              - It is a 16 bytes of character value that represents the mean duration of bursts, in milliseconds. It is a vendor-specific value.
*                                               GapDuration                - It is a 16 bytes of character value that represents the mean duration of gaps, in milliseconds. It is a vendor-specific value.
*                                               RoundTripDelay             - It is a 16 bytes of character value that represents the most recent measured RTD, in milliseconds. It is a vendor-specific value.
*                                               Gmin                       - It is a 16 bytes of character value that represents the local gap threshold. It is a vendor-specific value.
*                                               RFactor                    - It is a 16 bytes of character value that represents the voice quality evaluation for this RTP session. It is a vendor-specific value.
*                                               ExternalRFactor            - It is a 16 bytes of character value that represents the voice quality evaluation for segment on network external to this RTP session. It is a vendor-specific value.
*                                               JitterBufRate              - It is a 16 bytes of character value that represents the adjustment rate of jitter buffer, in milliseconds. It is a vendor-specific value.
*                                               JBNominalDelay             - It is a 16 bytes of character value that represents the nominal jitter buffer length, in milliseconds. It is a vendor-specific value.
*                                               JBMaxDelay                 - It is a 16 bytes of character value that represents the maximum jitter buffer length, in milliseconds. It is a vendor-specific value.
*                                               JBAbsMaxDelay              - It is a 16 bytes of character value that represents the absolute maximum delay, in milliseconds. It is a vendor-specific value.
*                                               TxPackets                  - It is a 16 bytes of character value that represents the count of transmitted packets. It is a vendor-specific value.
*                                               TxOctets                   - It is a 16 bytes of character value that represents the count of transmitted octet packets. It is a vendor-specific value.
*                                               RxPackets                  - It is a 16 bytes of character value that represents the count of received packets. It is a vendor-specific value.
*                                               RxOctets                   - It is a 16 bytes of character value that represents the count of received octet packets. It is a vendor-specific value.
*                                               PacketLoss                 - It is a 16 bytes of character value that represents the count of lost packets. It is a vendor-specific value.
*                                               IntervalJitter             - It is a 16 bytes of character value that represents the stat variance of packet interarrival time, in milliseconds. It is a vendor-specific value.
*                                               RemoteIntervalJitter       - It is a 16 bytes of character value that represents the remote side IntervalJitter. It is a vendor-specific value.
*                                               RemoteMOS_LQ               - It is a 16 bytes of character value that represents the remote side MOS_LQ. It is a vendor-specific value.
*                                               RemoteMOS_CQ               - It is a 16 bytes of character value that represents the remote side MOS_CQ. It is a vendor-specific value.
*                                               RemoteEchoReturnLoss       - It is a 16 bytes of character value that represents the remote side EchoReturnLoss. It is a vendor-specific value.
*                                               RemoteSignalLevel          - It is a 16 bytes of character value that represents the remote side SignalLevel. It is a vendor-specific value.
*                                               RemoteNoiseLevel           - It is a 16 bytes of character value that represents the remote side NoiseLevel. It is a vendor-specific value.
*                                               RemoteLossRate             - It is a 16 bytes of character value that represents the remote side LossRate. It is a vendor-specific value.
*                                               RemotePktLossConcealment   - It is a 16 bytes of character value that represents the remote side PktLossConcealment. It is a vendor-specific value.
*                                               RemoteDiscardRate          - It is a 16 bytes of character value that represents the remote side DiscardRate. It is a vendor-specific value.
*                                               RemoteBurstDensity         - It is a 16 bytes of character value that represents the remote side BurstDensity. It is a vendor-specific value.
*                                               RemoteGapDensity           - It is a 16 bytes of character value that represents the remote side GapDensity. It is a vendor-specific value.
*                                               RemoteBurstDuration        - It is a 16 bytes of character value that represents the remote side BurstDuration. It is a vendor-specific value.
*                                               RemoteGapDuration          - It is a 16 bytes of character value that represents the remote side GapDuration. It is a vendor-specific value.
*                                               RemoteRoundTripDelay       - It is a 16 bytes of character value that represents the remote side RoundTripDelay. It is a vendor-specific value.
*                                               RemoteGmin                 - It is a 16 bytes of character value that represents the remote side Gmin. It is a vendor-specific value.
*                                               RemoteRFactor              - It is a 16 bytes of character value that represents the remote side RFactor. It is a vendor-specific value.
*                                               RemoteExternalRFactor      - It is a 16 bytes of character value that represents the remote side External RFactor. It is a vendor-specific value.
*                                               RemoteJitterBufferAdaptive - It is a 16 bytes of character value that represents the remote side Buffer Adaptive. It is a vendor-specific value.
*                                               RemoteJitterBufRate        - It is a 16 bytes of character value that represents the remote side Buffer rate. It is a vendor-specific value.
*                                               RemoteJBNominalDelay       - It is a 16 bytes of character value that represents the remote side JBNominalDelay. It is a vendor-specific value.
*                                               RemoteJBMaxDelay           - It is a 16 bytes of character value that represents the remote side JBMaxDelay. It is a vendor-specific value.
*                                               RemoteJBAbsMaxDelay        - It is a 16 bytes of character value that represents the remote side JBAbsMaxDelay. It is a vendor-specific value.
*                                         </pre>
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT   mta_hal_GetCalls(ULONG InstanceNumber, ULONG *Count, PMTAMGMT_MTA_CALLS *ppCfg);

/*  mta_hal_GetCALLP : */
/**
* @description Retrieve the CALLP status info for the line number
* @param[in]  ULONG LineNumber - Line number for which to retrieve info on CALLP status.
* @param[out]  PMTAMGMT_MTA_CALLP pCallp - CallP info, to be returned.
*                                          \n Structure members are defined below:
*                                          <pre>
*                                                   LCState     - It is a 64 bytes of character value that represents the LC State. It is a vendor-specific value.
*                                                   CallPState  - It is a 64 bytes of character value that represents the callpstate. It is a vendor-specific value.
*                                                   LoopCurrent - It is a 64 bytes of character value that represents the Loop current. It is a vendor-specific value.
*                                          </pre>
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT   mta_hal_GetCALLP(ULONG LineNumber, PMTAMGMT_MTA_CALLP pCallp);

/*  mta_hal_GetDSXLogs : */
/**
* @description Retrieve all DSX log entries
* @param[out] ULONG *Count - number of entries in the log, to be returned. The value ranges from 0 to n, where n is an unsigned long value. Possible values: 2.
* @param[out] PMTAMGMT_MTA_DSXLOG *ppDSXLog - array of log entries, to be returned.
*                                             \n Structure members are defined below:
*                                             <pre>
*                                                   Time        - It is a 64 bytes of character value that represents the time. Possible values: "15:30:35".
*                                                   Description - It is a 128 bytes of character value that represents the description. It is a vendor-specific value.
*                                                   ID          - It is a unsigned long integer value that represents the ID. It is a vendor-specific value.
*                                                   Level       - It is a unsigned long integer value that represents the level. It is a vendor-specific value.
*                                             </pre>
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT   mta_hal_GetDSXLogs(ULONG *Count, PMTAMGMT_MTA_DSXLOG *ppDSXLog);

/*  mta_hal_GetDSXLogEnable : */
/**
* @description Get the value of if DSX log is enabled
* @param[out] BOOLEAN * pBool - boolean value of enable, to be returned. Possible values: "TRUE", "FALSE".
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT   mta_hal_GetDSXLogEnable(BOOLEAN *pBool);

/*  mta_hal_SetDSXLogEnable : */
/**
* @description Set value of DSX enable to the value
* @param[in] BOOLEAN Bool - value to set DSX log enable to the value. Possible values: "TRUE", "FALSE".
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT   mta_hal_SetDSXLogEnable(BOOLEAN Bool);


/*  mta_hal_ClearDSXLog : */
/**
* @description Set value of ClearDSXLog to the value
* @param[in] BOOLEAN Bool - value to set to clear DSX log. Possible values: "TRUE", "FALSE".
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_ClearDSXLog(BOOLEAN Bool) ;

/*  mta_hal_GetCallSignallingLogEnable : */
/**
* @description Get the value of if CallSignalling log is enabled
* @param[out] BOOLEAN * pBool - boolean value of enable, to be returned. Possible values: "TRUE", "FALSE".
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/

INT mta_hal_GetCallSignallingLogEnable(BOOLEAN *pBool) ;

/*  mta_hal_SetCallSignallingLogEnable : */
/**
* @description Set value of CallSignalling enable to the value
* @param[in] BOOLEAN Bool - value to set CallSignalling log enable to the value. Possible values: "TRUE", "FALSE".
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/

INT mta_hal_SetCallSignallingLogEnable(BOOLEAN Bool) ;


/*  mta_hal_ClearCallSignallingLog : */
/**
* @description Set value of CallSignalling enable to the value
* @param[in] BOOLEAN Bool - value to set to clear CallSignalling log. Possible values: "TRUE", "FALSE".
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/

INT mta_hal_ClearCallSignallingLog(BOOLEAN Bool) ;

/*  mta_hal_GetMtaLog : */
/**
* @description Get all log entries from the MTA Log
* @param[out] ULONG *Count - number of entries in the log, to be returned
* @param[out] PMTAMGMT_MTA_MTALOG_FULL *ppCfg - array of log entries, to be returned.
*                                               \n Structure members are defined below:
*                                               <pre>
*                                                       Index        - It is a unsigned long integer value that represents the Index. The value ranges from 0 to n, where n is an unsigned long value. Possible values: 1, 2.
*                                                       EventID      - It is a unsigned long integer value that represents the eventID. The value ranges from 0 to n, where n is an unsigned long value. Possible values: 1, 2.
*                                                       EventLevel   - It is a 64 bytes of character value that represents the event level. Possible values: "1", "2".
*                                                       Time         - It is a 64 bytes of character value that represents the time. Possible values: "1998-05-14".
*                                                       pDescription - It is a 64 bytes of character value that represents the description. Possible values: "this is a log for matLog1", "this is a log for matLog2".
*                                               </pre>
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_GetMtaLog(ULONG *Count, PMTAMGMT_MTA_MTALOG_FULL *ppCfg);

/*  mta_hal_BatteryGetInstalled : */
/**
* @description Check to see if the battery is installed
* @param[out] BOOLEAN* Val - TRUE/FALSE, value to be returned. Possible values: "TRUE", "FALSE".
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_BatteryGetInstalled(BOOLEAN* Val);

/*  mta_hal_BatteryGetTotalCapacity : */
/**
* @description Get the total capacity of the battery
* @param[out] INT* Val - capacity in mAVHour, to be returned. The value ranges from 0 to n, where n is an unsigned long value. Possible values: 0.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_BatteryGetTotalCapacity(ULONG* Val);

/*  mta_hal_BatteryGetActualCapacity : */
/**
* @description Retrieve the actual capacity of the battery
* @param[out] INT* Val - capacity in mAVHour, to be returned. The value ranges from 0 to n, where n is an unsigned long value. Possible values: 0.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_BatteryGetActualCapacity(ULONG* Val);

/*  mta_hal_BatteryGetRemainingCharge : */
/**
* @description Retrieve the current charge remain in the battery
* @param[out] INT* Val - capacity in mAVHour, to be returned. The value ranges from 0 to n, where n is an unsigned long value. Possible values: 0.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_BatteryGetRemainingCharge(ULONG* Val);

/* mta_hal_BatteryGetRemainingTime : */
/**
* @description Get estimated battery remaining time if current usage continues
* @param[out] INT* Val - Remaining time in minutes, to be returned. The value ranges from 0 to n, where n is an unsigned long value. Possible values: 0.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_BatteryGetRemainingTime(ULONG* Val);

/*  mta_hal_BatteryGetNumberofCycles : */
/**
* @description Get max number of cycles the battery can be charge cycled
* @param[out] INT* Val - Max number of cycles, to be returned. The value ranges from 0 to n, where n is an unsigned long value. Possible values: 0.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_BatteryGetNumberofCycles(ULONG* Val);

/*  mta_hal_BatteryGetPowerStatus : */
/**
* @description Get power status of MTA
* @param[out] CHAR* Val - Status of "AC", "Battery", or "Unknown", to be returned. Possible values: "Battery".
* @param[out] ULONG *len - string length, to be returned. The value ranges from 0 to n, where n is an unsigned long value. Possible values: 8.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_BatteryGetPowerStatus(CHAR *Val, ULONG *len);

/*  mta_hal_BatteryGetCondition: */
/**
* @description Get the battery condition
* @param[out] CHAR* Val - Status of "Good" or "Bad", to be returned. Possible values: "Good".
* @param[out] ULONG *len - string length, to be returned. The value ranges from 0 to n, where n is an unsigned long value. Possible values: 5.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_BatteryGetCondition(CHAR *Val, ULONG *len);

/*  mta_hal_BatteryGetStatus: */
/**
* @description Get the battery status
* @param[out] CHAR* Val - Status of "Missing", "Idle", "Charging",
*                         \n "Discharging", or "Unknown", to be returned. Possible values: "Unknown".
* @param[out] ULONG *len - string length, to be returned. The value ranges from 0 to n, where n is an unsigned long value. Possible values: 8.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_BatteryGetStatus(CHAR* Val, ULONG *len);

/*  mta_hal_BatteryGetLife: */
/**
* @description Get the battery life status
* @param[out] CHAR* Val - Values of "Need Replacement", or "Good", to be returned. Possible values: "Unknown".
* @param[out] ULONG *len - string length, to be returned. The value ranges from 0 to n, where n is an unsigned long value. Possible values: 8.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_BatteryGetLife(CHAR* Val, ULONG *len);


/*  mta_hal_BatteryGetInfo: */
/**
* @description Get the battery info
* @param[out] PMTAMGMT_MTA_BATTERY_INFO pInfo - battery info, to be returned
*                                               \n Structure members are defined below:
*                                               <pre>
*                                                       ModelNumber             - It is a 32 bytes of character value that represents the model number. Possible values: "ModelNumber1.0".
*                                                       SerialNumber            - It is a 32 bytes of character value that represents the serial number. Possible values: "SerialNumber1.0".
*                                                       PartNumber              - It is a 32 bytes of character value that represents the part number. Possible values: "PartNumber1.0".
*                                                       ChargerFirmwareRevision - It is a 32 bytes of character value that represents the charger firmware revision. Possible values: "ChargerFirmwareRevision1.0".
*                                               </pre>
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_BatteryGetInfo(PMTAMGMT_MTA_BATTERY_INFO pInfo);

/*  mta_hal_BatteryGetPowerSavingModeStatus: */
/**
* @description Get the battery Power Saving Mode Status
* @param[out] ULONG *pValue- Values of 1 for Enabled, 2 for Disabled.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_BatteryGetPowerSavingModeStatus(ULONG *pValue);

/*  mta_hal_Get_MTAResetCount: */
/**
* @description Get the reset count of MTA
* @param[out] ULONG * resetcnt- count. The value ranges from 0 to n, where n is an unsigned long value. Possible values: 2.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/

INT mta_hal_Get_MTAResetCount(ULONG *resetcnt);

/*  mta_hal_Get_MTAResetCount: */
/**
* @description Get the reset count of MTA Lines
* @param[out] ULONG *resetcnt- count. The value ranges from 0 to n, where n is an unsigned long value. Possible values: 2.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/

INT mta_hal_Get_LineResetCount(ULONG *resetcnt);

/**
* @description clear the VQM stats per line
* @param[in] ULONG InstanceNumber - instance number. It is a vendor-specific value. The value ranges from 0 to n, where n is an unsigned long value. Possible values: 1.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_ClearCalls(ULONG InstanceNumber);

/* mta_hal_getDhcpStatus: */
/**
* @description Get the DHCP status for MTA
* @param[out] MTAMGMT_MTA_STATUS *output_pIpv4status - ipv4 dhcp status.
*                                                      \n The enum values are defined below:
*                                                      <pre>
*                                                           MTA_INIT     = 0
*                                                           MTA_START    = 1
*                                                           MTA_COMPLETE = 2
*                                                           MTA_ERROR    = 3
*                                                           MTA_REJECTED = 4
*                                                      </pre>
* @param[out] MTAMGMT_MTA_STATUS *output_pIpv6status - ipv6 dhcp status
*                                                      \n The enum values are defined below:
*                                                      <pre>
*                                                           MTA_INIT     = 0
*                                                           MTA_START    = 1
*                                                           MTA_COMPLETE = 2
*                                                           MTA_ERROR    = 3
*                                                           MTA_REJECTED = 4
*                                                      </pre>
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_getDhcpStatus(MTAMGMT_MTA_STATUS *output_pIpv4status, MTAMGMT_MTA_STATUS *output_pIpv6status);

/* mta_hal_getConfigFileStatus: */
/**
* @description Get the MTA config file status
* @param[out] MTAMGMT_MTA_STATUS *poutput_status - config file status
*                                                  \n The enum values are defined below:
*                                                  <pre>
*                                                       MTA_INIT     = 0
*                                                       MTA_START    = 1
*                                                       MTA_COMPLETE = 2
*                                                       MTA_ERROR    = 3
*                                                       MTA_REJECTED = 4
*                                                  </pre>
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_getConfigFileStatus(MTAMGMT_MTA_STATUS *poutput_status);

/* mta_hal_getLineRegisterStatus: */
/**
* @description Get the register status for all lines
* @param[out] MTAMGMT_MTA_STATUS *output_status_array - return array buffer for all line register status.
*                                                       \n The enum values are defined below:
*                                                       <pre>
*                                                            MTA_INIT     = 0
*                                                            MTA_START    = 1
*                                                            MTA_COMPLETE = 2
*                                                            MTA_ERROR    = 3
*                                                            MTA_REJECTED = 4
*                                                       </pre>
* @param[in] int array_size - buffer size (total line number). Possible values: 6.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_getLineRegisterStatus(MTAMGMT_MTA_STATUS *output_status_array, int array_size);

/*  mta_hal_devResetNow: */
/**
* @description Set boolean value passed to reset MTA device
* @param[in] BOOLEAN bResetValue - boolean value to reset the device. Possible values: "TRUE", "FALSE".
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_devResetNow(BOOLEAN bResetValue);

/* mta_hal_getMtaOperationalStatus: */
/**
* @description Get the operational status of MTA
* @param[out] MTAMGMT_MTA_STATUS *operationalStatus - return buffer for operational status
*                                                     \n The enum values are defined below:
*                                                     <pre>
*                                                          MTA_INIT     = 0
*                                                          MTA_START    = 1
*                                                          MTA_COMPLETE = 2
*                                                          MTA_ERROR    = 3
*                                                          MTA_REJECTED = 4
*                                                     </pre>
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_getMtaOperationalStatus(MTAMGMT_MTA_STATUS *operationalStatus);

/* mta_hal_getMtaProvisioningStatus: */
/**
* @description Get the provisional status of MTA
* @param[out] MTAMGMT_MTA_PROVISION_STATUS *provisionStatus - return buffer for provision status.
*                                                             \n The enum values are defined below:
*                                                             <pre>
*                                                               MTA_PROVISIONED     = 0
*                                                               MTA_NON_PROVISIONED = 1
*                                                             </pre>
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_getMtaProvisioningStatus(MTAMGMT_MTA_PROVISION_STATUS *provisionStatus);

#define MTA_DHCPOPTION122SUBOPTION1_MAX          4
#define MTA_DHCPOPTION122SUBOPTION2_MAX          4
#define MTA_DHCPOPTION122CCCV6DSSID1_MAX         32
#define MTA_DHCPOPTION122CCCV6DSSID2_MAX         32


typedef  enum {
   MTA_IPV4=0,
   MTA_IPV6=1,
   MTA_DUAL_STACK=2,
} MTAMGMT_MTA_PROV_IP_MODE; // MTAMGMT_PROVISIONING_PARAMS.MtaIPMode


typedef struct _MTAMGMT_PROVISIONING_PARAMS
{
  
INT  MtaIPMode;
INT  DhcpOption2171CccV6DssID1Len;                                       // Length of DhcpOption2171CccV6DssID1
INT  DhcpOption2171CccV6DssID2Len;                                       // Length of DhcpOption2171CccV6DssID2
CHAR DhcpOption122Suboption1[MTA_DHCPOPTION122SUBOPTION1_MAX+1];         // 4 byte hex value ie. FFFFFFFF = "255.255.255.255". IPv4 addresses MUST be encoded as 4 binary octets in network  byte-order (high order byte first).
CHAR DhcpOption122Suboption2[MTA_DHCPOPTION122SUBOPTION2_MAX+1];        //  4 byte hex value ie. FFFFFFFF = "255.255.255.255"
CHAR DhcpOption2171CccV6DssID1[MTA_DHCPOPTION122CCCV6DSSID1_MAX+1];     // 32 byte hex value
CHAR DhcpOption2171CccV6DssID2[MTA_DHCPOPTION122CCCV6DSSID2_MAX+1];     // 32 byte hex value
}
MTAMGMT_PROVISIONING_PARAMS, *PMTAMGMT_MTA_PROVISIONING_PARAMS;


/* mta_hal_start_provisioning: */
/**
* @description This API call will start IP provisioning for all the lines for IPv4/IPv6 , or dual mode
* @param[in] PMTAMGMT_MTA_PROVISIONING pParameters - IP provisioning for all line register status
*                                                \n The structure members are defined below:
*                                                <pre>
*                                                       MtaIPMode                    - It is a integer value that represents the Mta Ip mode. The value ranges from 0 to 2. Possible value: 1.
*                                                       DhcpOption2171CccV6DssID1Len - It is a integer value that represents the Length of DhcpOption2171CccV6DssID1. Possible value: 32.
*                                                       DhcpOption2171CccV6DssID2Len - It is a integer value that represents the Length of DhcpOption2171CccV6DssID2. Possible value: 32.
*                                                       DhcpOption122Suboption1      - It is a 4 byte hex value. ie. FFFFFFFF = "255.255.255.255". IPv4 addresses MUST be encoded as 4 binary octets in network  byte-order (high order byte first). Possible value: 4.
*                                                       DhcpOption122Suboption2      - It is a 4 byte hex value ie. FFFFFFFF = "255.255.255.255". Possible values: 4.
*                                                       DhcpOption2171CccV6DssID1    - It is a 32 byte hex value. It is a vendor-specific value.
*                                                       DhcpOption2171CccV6DssID2    - It is a 32 byte hex value. It is a vendor-specific value.
*                                                </pre>
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT mta_hal_start_provisioning(PMTAMGMT_MTA_PROVISIONING_PARAMS pParameters); // This API call will start IP provisioning for all the lines for IPv4/IPv6 , or dual mode

/* mta_hal_getLineRegisterStatus_callback: */
/**
* @description This call back will be invoked to returing MTA line
* @param MTAMGMT_MTA_STATUS *output_status_array - return array buffer for all line register status.
* @param int array_size - buffer size (total line number)
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Asynchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
typedef INT ( * mta_hal_getLineRegisterStatus_callback)(MTAMGMT_MTA_STATUS *output_status_array, int array_size); //This call back will be invoked to returing MTA line provisionoing status

/* mta_hal_LineRegisterStatus_callback_register: */
/**
* @description This call back will be invoked to returing MTA line
* @param[in] mta_hal_getLineRegisterStatus_callback callback_proc - Callback registration function.
*                                                                   The values defined below:
*                                                                   <pre>
*                                                                   output_status_array - Output parameter to return array buffer for all line register status.
*                                                                                         The enum values are defined below:
*                                                                                             MTA_INIT     = 0
*                                                                                             MTA_START    = 1
*                                                                                             MTA_COMPLETE = 2
*                                                                                             MTA_ERROR    = 3
*                                                                                             MTA_REJECTED = 4
*                                                                                         </pre>
*                                                                   array_size - buffer size (total line number). Input parameter of type int. Possible value: 6.
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/

void mta_hal_LineRegisterStatus_callback_register(mta_hal_getLineRegisterStatus_callback callback_proc); //Callback registration function.

#endif /* __MTA_HAL_H__ */
/**
 * @}
 */


