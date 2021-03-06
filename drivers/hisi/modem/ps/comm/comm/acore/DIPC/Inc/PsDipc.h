/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
 
#ifndef __PSDIPC_H__
#define __PSDIPC_H__


/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include    "AtDipcInterface.h"
#include    "ImmInterface.h"
#include    "AdsDeviceInterface.h"
#include    "mdrv.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 ??????
*****************************************************************************/
#define DIPC_DEV_NUM                (DIPC_DEV_BUTT)       /* DIPC?????????????????? */

/* ??????????Rab????????????[5,15],??????????????????????????[0??15] 16????????[0,4]????????  */
#define RAB_MAX_NUM                 (MAX_RAB_ID + 1)   

#define SERVICE_MAX_NUM             (6) /* ????????3????????????????????????2??SERVICE_ID */

#define DIPC_SERVICE_TYPE_MAX_NUM   (DIPC_SERVICE_TYPE_BUTT)

#define DIPC_DATA_MAX_DATA_LEN      (1536)    /* DIPC?????????????????????????? */

#define DIPC_IP_VER_IPV4            (4)
#define DIPC_IP_VER_IPV6            (6)

/* ?????????????????????? */
#define DIPC_GET_SERVICE_STRU_USE(ulServiceMask, ucServiceNo)   (((ulServiceMask) & (1 << (ucServiceNo))) >> (ucServiceNo))

/* ???????????????????????? */
#define DIPC_SET_SERVICE_STRU_REG(ulServiceMask, ucServiceNo)   ((ulServiceMask) = ((ulServiceMask) | (1 << (ucServiceNo))))

/* ?????????????????????????? */
#define DIPC_CLR_SERVICE_STRU_REG(ulServiceMask, ucServiceNo)   ((ulServiceMask) = ((ulServiceMask) & (~((VOS_UINT32)(1 << (ucServiceNo))))))


/* ???????????????? */
#define DIPC_GET_SERVICE_REG(ulServerMask, enServiceType)   (((ulServerMask) & (1 << (enServiceType))) >> (enServiceType))

/* ???????????????????????? */
#define DIPC_SET_SERVICE_REG(ulServerMask, enServiceType)   ((ulServerMask) = ((ulServerMask) | (1 << (enServiceType))))

/* ?????????????????? */
#define DIPC_CLR_SERVICE_REG(ulServerMask, enServiceType)   ((ulServerMask) = ((ulServerMask) & (~((VOS_UINT32)(1 << (enServiceType))))))

/* ??????AT??????????????????BearerType?????????????? */
#define DIPC_GET_SERVICE_TYPE_BY_BEARER_TYPE(enBearerType)  ((enBearerType) - 1)

#define DIPC_SET_APP(enDir, Para)   (((enDir) << 8) | (VOS_UINT8)Para)
#define DIPC_GET_DIR(App)           ((App) >> 8)
#define DIPC_GET_PARA(App)          ((App) & 0xff)

#define INVALID_RABID_VALUE             (0xFF)


/*****************************************************************************
  3 ????????
*****************************************************************************/
/*????DrvInterface.h??UDI_DEVICE_ID????UDI_ACM_HSIC_ACM1_ID/UDI_ACM_HSIC_ACM3_ID/UDI_ACM_HSIC_ACM5_ID
??????????????????????????????????*/
typedef enum
{
    DIPC_DEV_ID1    = 0,
    DIPC_DEV_ID2    = 1,
    DIPC_DEV_ID3    = 2,
    DIPC_DEV_BUTT
}DIPC_DEV_ID_ENUM;
typedef VOS_UINT32  DIPC_DEV_ID_ENUM_UINT32;

/* DIPC???????????????? */
typedef enum
{
    DIPC_SERVICE_TYPE_IPV4  = 0,
    DIPC_SERVICE_TYPE_IPV6  = 1,
    DIPC_SERVICE_TYPE_BUTT
}DIPC_SERVICE_TYPE_ENUM;
typedef VOS_UINT32  DIPC_SERVICE_TYPE_ENUM_UINT32;

/* ???????????????? */
typedef enum
{
    ID_DIPC_ADD_NEW_MAPPING_INFO_FAIL       = 0x0001,   /* ???????????????????????? */ 
    ID_DIPC_DEL_MAPPING_INFO_FAIL           = 0x0002,   /* ???????????????????????? */
    ID_DIPC_REG_ADS_DL_DATA_CALLBACK_FAIL   = 0x0003,   /* PDP??????????ADS???????????????? */
    ID_DIPC_DEREG_ADS_DL_DATA_CALLBACK_FAIL = 0x0004,   /* PDP??????????????ADS???????????????? */
    ID_DIPC_PDP_ACT_SUCC                    = 0x0005,   /* PDP???????? */
    ID_DIPC_PDP_DEACT_SUCC                  = 0x0006,   /* PDP?????????? */
    ID_DIPC_SHOW_MAPPING_INFO               = 0x0007,   /* ???????????????????????? */
    ID_DIPC_TRACE_UL_DATA                   = 0x1001,   /* ???????????? */
    ID_DIPC_TRACE_DL_DATA                   = 0x1002,   /* ???????????? */
    ID_DIPC_TRACE_TYPE_BUTT
}DIPC_TRACE_MSG_TYPE_ENUM;
typedef VOS_UINT32 DIPC_TRACE_MSG_TYPE_ENUM_UINT32;

typedef VOS_UINT32 (*DIPC_SERV_ULDATA_CALLFUNC)(IMM_ZC_STRU *pData, VOS_UINT8 ucRabId);
typedef VOS_UINT32 (*DIPC_SERV_DLDATA_CALLFUNC)(DIPC_DEV_ID_ENUM_UINT32 enUdiDevId, IMM_ZC_STRU *pstBuf);
typedef VOS_UINT32 (*DIPC_SERV_ULDATA_MATCHFUNC)(IMM_ZC_STRU *pstBuf);
typedef VOS_UINT32 (*DIPC_SERV_DLDATA_MATCHFUNC)(IMM_ZC_STRU *pstBuf);

typedef enum
{
    ID_DIPC_UL_DATA,
    ID_DIPC_DL_DATA,
    ID_DIPC_DATA_BUTT
}DIPC_DATA_TYPE_ENUM;
typedef VOS_UINT16  DIPC_DATA_TYPE_ENUM_UINT16;

enum ID_DIPC_MSG_TYPE_ENUM
{
    ID_DIPC_DATA_NOTIFY_REQ
};
typedef VOS_UINT32  ID_DIPC_MSG_TYPE_ENUM_UINT32;


/*****************************************************************************
  4 ????????????
*****************************************************************************/


/*****************************************************************************
  5 ??????????
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                              /* ?????? */     
    ID_DIPC_MSG_TYPE_ENUM_UINT32    enMsgType;  /* ???????? */   
}DIPC_DATA_PROC_NOTIFY_MSG;

/*****************************************************************************
  6 ????????
*****************************************************************************/
/*TTF ??????????32????????????????????????*/
typedef struct
{
    VOS_MSG_HEADER                      /* ?????? */
    VOS_UINT32 ulMsgType;               /* ???????? */
}TTF_U32MSG_COMM_HEAD_STRU;

/*????????*/
typedef struct
{
    VOS_MSG_HEADER
    DIPC_TRACE_MSG_TYPE_ENUM_UINT32     enMsgType;
    DIPC_DEV_ID_ENUM_UINT32             enDevId;
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                           aucData[DIPC_DATA_MAX_DATA_LEN];
} TRACE_UL_DIPC_DATA_MSG;

typedef struct
{
    VOS_MSG_HEADER
    DIPC_TRACE_MSG_TYPE_ENUM_UINT32     enMsgType;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                           aucData[DIPC_DATA_MAX_DATA_LEN];
} TRACE_DL_DIPC_DATA_MSG;

typedef struct
{
    DIPC_SERVICE_TYPE_ENUM_UINT32       enServiceType;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucRsv[3];   
}DIPC_DEV_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    DIPC_TRACE_MSG_TYPE_ENUM_UINT32     enMsgType;
    DIPC_DEV_INFO_STRU                  astDipcDevData[DIPC_DEV_NUM];     
}DIPC_DEV_SUITE_INFO_MSG;


/*****************************************************************************
  7 STRUCT????
*****************************************************************************/
/* ?????????????? */
typedef struct
{
    UDI_DEVICE_ID_E             enUdiDevId;     /* ??????????DIPC??????????????ID */
    UDI_HANDLE                  slUdiHsicHdl;   /* ?????????????? */

    VOS_UINT32  (*pTxFunc)(UDI_HANDLE ulhandle, IMM_ZC_STRU *pstBuf); /* ???????????????? */
    
    union
    {
        VOS_UINT32  (*pAcmRxFunc)(VOS_VOID);                                /* ACM???????????????????????????????????? */
        VOS_UINT32  (*pNcmRxFunc)(UDI_HANDLE ulhandle, VOS_VOID *pPktNode); /* NCM???????????????????????????????????? */
    }pRxFunc;
}DEV_INFO_STRU;

typedef struct
{   
    VOS_UINT8                   ucServiceIndex;     /* ?????????????????????????? */
    VOS_UINT8                   ucRabId;            /* Rab ID??????pUlCallFunc?????? */
    VOS_UINT8                   aucRsv[2];
    DIPC_DEV_ID_ENUM_UINT32     enDipcDevId;        /* DIPC????????dev ID??????pDlCallFunc?????? */
    DIPC_SERV_ULDATA_MATCHFUNC  pUlMatchFunc;
    DIPC_SERV_DLDATA_MATCHFUNC  pDlMatchFunc;
    DIPC_SERV_ULDATA_CALLFUNC   pUlCallFunc;
    DIPC_SERV_DLDATA_CALLFUNC   pDlCallFunc;
}SERVICE_INFO_STRU;

typedef struct
{
    VOS_UINT32                  ulServiceNum;
    VOS_UINT32                  ulServiceMask;
    SERVICE_INFO_STRU           astServiceInfo[SERVICE_MAX_NUM];
}TOTAL_SERVICE_INFO_STRU;

typedef struct
{   
    VOS_UINT32                  ulServiceCnt;
    VOS_UINT32                  ulServiceMask;
    SERVICE_INFO_STRU          *apstServiceInfo[DIPC_SERVICE_TYPE_MAX_NUM];
}DEV_SERVICE_INFO_STRU;

typedef struct
{   
    VOS_UINT32                  ulServiceCnt;
    VOS_UINT32                  ulServiceMask;
    SERVICE_INFO_STRU          *apstServiceInfo[DIPC_SERVICE_TYPE_MAX_NUM];
}RAB_SERVICE_INFO_STRU;

typedef struct
{
    VOS_UINT32                  ulGetDataFailNums;          /* ???????????????????????????? */
    VOS_UINT32                  ulSuccGetUlPacketNums;      /* ????Hsic???????????????????????? */
    VOS_UINT32                  ulFailMatchUlPacketNums;    /* ????Hsic?????????????????????????????? */
    VOS_UINT32                  ulFailSendUlPacketNums;     /* ????????ADS???????????????????????? */
    VOS_UINT32                  ulDiscardUlPacketNums;      /* ??????????????????????PDP?????????????????????????????????????????? */
    VOS_UINT32                  ulSuccSendUlPacketNums;     /* ????????ADS????????????????????????*/
    VOS_UINT32                  ulFailSendDlPacketNums;     /* ???????????????????????????????????? */
    VOS_UINT32                  ulSuccSendDlPacketNums;     /* ???????????????????????????????????? */
} DIPC_DEV_STATIC_INFO_STRU;

typedef struct
{
    DIPC_DEV_STATIC_INFO_STRU   astDipcDevStaticInfo[DIPC_DEV_NUM];
    VOS_UINT32                  ulNullDlPacketNums;         /* ????ADS???????????????????????????????? */
    VOS_UINT32                  ulSuccGetDlPacketNums;      /* ????Hsic???????????????????????? */
    VOS_UINT32                  ulFailMatchDlPacketNums;    /* ????Hsic?????????????????????????????? */
    VOS_UINT32                  ulDiscardDlPacketNums;      /* ??????????????????????PDP?????????????????????????????????????????? */
} DIPC_STATIC_INFO_STRU;

typedef struct
{
    VOS_UINT8                   ucIpHdrLen  :4;     /* IP???????? */
    VOS_UINT8                   ucIpVer     :4;     /* IP??????*/
    VOS_UINT8                   ucServiceType;      /* IP TOS????*/
    VOS_UINT16                  usTotalLen;         /* IP????????????*/
    VOS_UINT16                  usIdentification;   /* IP??????ID*/
    VOS_UINT16                  usOffset;           /* IP??????????*/
    VOS_UINT8                   ucTTL;              /* IPTTL*/
    VOS_UINT8                   ucProtocol;         /* IP????????????????*/
    VOS_UINT16                  usCheckSum;         /* IP??????????*/
    VOS_UINT32                  ulSrcAddr;          /* ??IP????*/
    VOS_UINT32                  ulDstAddr;          /* ????IP????*/
} DIPC_IPHDR_STRU;

typedef struct
{
    IMM_ZC_HEAD_STRU            stDipcDataQ;        /* DIPC???????????????????????????? */
    /* DIPC????????????????????????????????????DIPC???????????????????????????????????? */
    VOS_UINT32                  ulNotifyMsgCnt;     
}DIPC_DATA_Q_CTRL_ST;


/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/


/*****************************************************************************
  10 ????????
*****************************************************************************/
/* OAM ACPU???????? */
extern VOS_VOID DIPC_PrintLog(VOS_UINT32 ulModuleId, VOS_UINT32 ulSubMod,
    VOS_UINT32 ulLevel, VOS_CHAR *pcString);
extern VOS_VOID DIPC_PrintLog1(VOS_UINT32 ulModuleId, VOS_UINT32 ulSubMod,
    VOS_UINT32 ulLevel, VOS_CHAR  *pcString, VOS_INT32 lPara1);
extern VOS_VOID DIPC_PrintLog2(VOS_UINT32 ulModuleId, VOS_UINT32 ulSubMod,
    VOS_UINT32 ulLevel, VOS_CHAR *pcString, VOS_INT32 lPara1, VOS_INT32 lPara2);
    
extern VOS_VOID DIPC_DEV_HsicAcmFreeDlDataCB(IMM_ZC_STRU *pstBuf);    
extern VOS_UINT32 DIPC_DEV_AcmOpenDevice(DEV_INFO_STRU *pstDevInfo);
extern VOS_UINT32 DIPC_DEV_NcmOpenDevice(DEV_INFO_STRU *pstDevInfo);
extern VOS_UINT32 DIPC_DEV_AcmGetUlDataBuf(UDI_HANDLE slUdiHsicAcmHdl, IMM_ZC_STRU **ppstBuf);
extern VOS_UINT32 DIPC_DEV_UsbAcmReadUlData(DIPC_DEV_ID_ENUM_UINT32 ulDeviceId);
extern VOS_UINT32 DIPC_DEV_UsbAcm1ReadUlData( VOS_VOID);
extern VOS_UINT32 DIPC_DEV_UsbAcm3ReadUlData( VOS_VOID);
extern VOS_UINT32 DIPC_DEV_UsbAcm5ReadUlData( VOS_VOID);
extern VOS_UINT32 DIPC_DEV_UsbNcmReadUlData(DIPC_DEV_ID_ENUM_UINT32 enDeviceId, IMM_ZC_STRU *pstImmZcData);
extern VOS_UINT32 DIPC_DEV_UsbNcm0ReadUlData(UDI_HANDLE ulhandle, VOS_VOID *pPktNode);
extern VOS_UINT32 DIPC_DEV_UsbNcm1ReadUlData(UDI_HANDLE ulhandle, VOS_VOID *pPktNode);
extern VOS_UINT32 DIPC_DEV_UsbNcm2ReadUlData(UDI_HANDLE ulhandle, VOS_VOID *pPktNode);
extern VOS_UINT32 DIPC_DEV_UsbAcmWriteData(UDI_HANDLE slUdiHandle, IMM_ZC_STRU *pstBuf);
extern VOS_UINT32 DIPC_DEV_UsbNcmWriteData(UDI_HANDLE slUdiHandle, IMM_ZC_STRU *pstBuf);
extern VOS_UINT32 DIPC_DEV_UsbWriteData(DIPC_DEV_ID_ENUM_UINT32 enDipcDevId, IMM_ZC_STRU *pstBuf);
extern VOS_UINT32 DIPC_DEV_PortInit( VOS_VOID );
extern VOS_VOID DIPC_DEV_AddNewIpTypeService(DIPC_DEV_ID_ENUM_UINT32 enDevId,
    DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType, SERVICE_INFO_STRU *pstServiceInfo);
extern UDI_HANDLE DIPC_DRV_GetDevHandleByDevId(DIPC_DEV_ID_ENUM_UINT32 enDevId);
extern VOS_VOID DIPC_MGR_AddNewIpTypeService(VOS_UINT8 ucRabId,
    DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType, SERVICE_INFO_STRU *pstServiceInfo);
extern VOS_UINT32 DIPC_MGR_DelIpVService(VOS_UINT8 ucRabId, DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType);
extern VOS_UINT32 DIPC_MGR_AddNewService(DIPC_DEV_ID_ENUM_UINT32 enDevId,
    VOS_UINT8 ucRabId, DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType);
extern VOS_UINT32 DIPC_DEV_UlDataProc(DIPC_DEV_ID_ENUM_UINT32 enDeviceId, IMM_ZC_STRU *pstBuf);    
extern VOS_UINT32 DIPC_MGR_UlDataProc(DIPC_DEV_ID_ENUM_UINT32 enDeviceId, IMM_ZC_STRU *pstBuf);
extern VOS_UINT32 DIPC_MGR_DlAdsDataRcv(VOS_UINT8 ucRabId, IMM_ZC_STRU *pData);
extern DIPC_DEV_ID_ENUM_UINT32 DIPC_GetDevIdByRabId(VOS_UINT8 ucRabId);
extern VOS_UINT32 DIPC_DlAdsDataRcv(VOS_UINT8 ucRabId, IMM_ZC_STRU *pData,
    ADS_PKT_TYPE_ENUM_UINT8 enPktType, VOS_UINT32 ulExParam);
extern SERVICE_INFO_STRU* DIPC_MGR_GetServiceByRabId(VOS_UINT8 ucRabId,
    DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType);
extern VOS_VOID DIPC_MGR_DelIpTypeService(VOS_UINT8 ucRabId, DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType);
extern VOS_VOID DIPC_RcvAtPdpActIndProc(AT_DIPC_PDP_ACT_STRU *pstAtDipcPdpActMsg);
extern VOS_VOID DIPC_RcvAtPdpRelIndProc(AT_DIPC_PDP_DEACT_STRU *pstAtDipcPdpDeactMsg);
extern VOS_VOID  DIPC_ProcDataNotify(VOS_VOID);
extern VOS_UINT32 DIPC_AtMsgProc(const MsgBlock *pMsgBlock);
extern VOS_UINT32  DIPC_EnqueueData(IMM_ZC_STRU *pstImmZc);
extern VOS_UINT32 DIPC_Init(VOS_VOID);
extern VOS_UINT32 DIPC_Pid_InitFunc(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_VOID DIPC_TraceUlData(DIPC_DEV_ID_ENUM_UINT32 ulDeviceId, IMM_ZC_STRU *pstData);
extern VOS_VOID DIPC_TraceDlData(VOS_UINT8 ucRabId, IMM_ZC_STRU *pstData);
extern VOS_VOID DIPC_MappingInfoTrace(DIPC_TRACE_MSG_TYPE_ENUM_UINT32 enDipcTraceMsgType);
extern VOS_VOID DIPC_StaticInfoInit( VOS_VOID );

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of PsHsic.h */

