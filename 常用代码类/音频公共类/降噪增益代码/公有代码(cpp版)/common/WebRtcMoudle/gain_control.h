/*
 *  Copyright (c) 2012 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef WEBRTC_MODULES_AUDIO_PROCESSING_AGC_INCLUDE_GAIN_CONTROL_H_
#define WEBRTC_MODULES_AUDIO_PROCESSING_AGC_INCLUDE_GAIN_CONTROL_H_

#include "typedefs.h"

// Errors
#define AGC_UNSPECIFIED_ERROR           18000
#define AGC_UNSUPPORTED_FUNCTION_ERROR  18001
#define AGC_UNINITIALIZED_ERROR         18002
#define AGC_NULL_POINTER_ERROR          18003
#define AGC_BAD_PARAMETER_ERROR         18004

// Warnings
#define AGC_BAD_PARAMETER_WARNING       18050

enum
{
    kAgcModeUnchanged,
    kAgcModeAdaptiveAnalog,
    kAgcModeAdaptiveDigital,
    kAgcModeFixedDigital
};

enum
{
    kAgcFalse = 0,
    kAgcTrue
};

typedef struct
{
    int16_t targetLevelDbfs;   // default 3 (-3 dBOv)
    int16_t compressionGaindB; // default 9 dB
    uint8_t limiterEnable;     // default kAgcTrue (on)
} WebRtcAgc_config_t;

int WebRtcAgc_AddFarend(void* agcInst,
                        const int16_t* inFar,
                        int16_t samples);
int WebRtcAgc_AddMic(void* agcInst,
                     int16_t* inMic,
                     int16_t* inMic_H,
                     int16_t samples);
int WebRtcAgc_VirtualMic(void* agcInst,
                         int16_t* inMic,
                         int16_t* inMic_H,
                         int16_t samples,
                         int32_t micLevelIn,
                         int32_t* micLevelOut);
int WebRtcAgc_Process(void* agcInst,
                      const int16_t* inNear,
                      const int16_t* inNear_H,
                      int16_t samples,
                      int16_t* out,
                      int16_t* out_H,
                      int32_t inMicLevel,
                      int32_t* outMicLevel,
                      int16_t echo,
                      uint8_t* saturationWarning);


int WebRtcAgc_set_config(void* agcInst, WebRtcAgc_config_t config);

int WebRtcAgc_get_config(void* agcInst, WebRtcAgc_config_t* config);
int WebRtcAgc_Create(void **agcInst);
int WebRtcAgc_Free(void *agcInst);
int WebRtcAgc_Init(void *agcInst,
                   int32_t minLevel,
                   int32_t maxLevel,
                   int16_t agcMode,
                   uint32_t fs);
#endif