/*
    K Audio Interface library for OS/2
    Copyright (C) 2010 by KO Myung-Hun <komh@chollian.net>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef __KAI_H__
#define __KAI_H__

#include <os2.h>

#define INCL_OS2MM
#include <os2me.h>

#ifdef __cplusplus
extern "C" {
#endif

#define KAIM_AUTO       0
#define KAIM_DART       1
#define KAIM_UNIAUD     2

#define KAIE_NO_ERROR                  0
#define KAIE_NOT_INITIALIZED        ( -1 )
#define KAIE_ALREADY_INITIALIZED    ( -2 )
#define KAIE_INVALID_PARAMETER      ( -3 )
#define KAIE_CANNOT_LOAD_SUB_MODULE ( -4 )
#define KAIE_NOT_OPENED             ( -5 )
#define KAIE_ALREADY_OPENED         ( -6 )
#define KAIE_NOT_ENOUGH_MEMORY      ( -7 )

#define KAIT_PLAY       0
#define KAIT_RECORD     1

#define KAIS_PLAYING    0x0001
#define KAIS_PAUSED     0x0002
#define KAIS_COMPLETED  0x0004

#ifndef BPS_32
#define BPS_32  32
#endif

typedef ULONG ( APIENTRY FNKAICB )( PVOID, PVOID, ULONG );
typedef FNKAICB *PFNKAICB;

#pragma pack( 1 )
typedef struct tagKAICAPS
{
    ULONG   ulMode;
    ULONG   ulMaxChannels;
    CHAR    szPDDName[ 256 ];
} KAICAPS, *PKAICAPS;

typedef struct tagKAISPEC
{
    USHORT      usDeviceIndex;
    ULONG       ulType;             /* support KAIT_PLAY only */
    ULONG       ulBitsPerSample;
    ULONG       ulSamplingRate;
    ULONG       ulDataFormat;
    ULONG       ulChannels;
    ULONG       ulNumBuffers;
    ULONG       ulBufferSize;
    BOOL        fShareable;
    PFNKAICB    pfnCallBack;
    PVOID       pCallBackData;
    BYTE        bSilence;           /* output only */
} KAISPEC, *PKAISPEC;
#pragma pack()

APIRET APIENTRY kaiInit( ULONG ulKaiMode );
APIRET APIENTRY kaiDone( VOID );
APIRET APIENTRY kaiCaps( PKAICAPS pkc );
APIRET APIENTRY kaiOpen( const PKAISPEC pksWanted, PKAISPEC pksObtained );
APIRET APIENTRY kaiClose( VOID );
APIRET APIENTRY kaiPlay( VOID );
APIRET APIENTRY kaiStop( VOID );
APIRET APIENTRY kaiPause( VOID );
APIRET APIENTRY kaiResume( VOID );
APIRET APIENTRY kaiSetSoundState( ULONG ulCh, BOOL fState );
APIRET APIENTRY kaiSetVolume( ULONG ulCh, USHORT usVol );
APIRET APIENTRY kaiGetVolume( ULONG ulCh );
APIRET APIENTRY kaiClearBuffer( VOID );
APIRET APIENTRY kaiStatus( VOID );

#ifdef __cpluslus
}
#endif

#endif