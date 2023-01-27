/******************************************************************************
* The VDU_MCU_firmware files distributed with this project are provided in binary
* form under the following license; source files are not provided.
*
* While the following license is similar to the MIT open-source license,
* it is NOT the MIT open source license or any other OSI-approved open-source license.
*
* Copyright (C) 2015-2023 Allegro DVT2
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
******************************************************************************/

#pragma once

/*************************************************************************//*!
   \brief Nal unit type enum
 *************************************************************************/
typedef enum e_NalUnitType
{
  AL_AVC_NUT_UNSPEC_0 = 0,
  AL_AVC_NUT_VCL_NON_IDR = 1,
  AL_AVC_NUT_VCL_IDR = 5,
  AL_AVC_NUT_PREFIX_SEI = 6,
  AL_AVC_NUT_SPS = 7,
  AL_AVC_NUT_PPS = 8,
  AL_AVC_NUT_AUD = 9,
  AL_AVC_NUT_EOS = 10,
  AL_AVC_NUT_EOB = 11,
  AL_AVC_NUT_FD = 12,
  AL_AVC_NUT_SPS_EXT = 13,
  AL_AVC_NUT_PREFIX = 14,
  AL_AVC_NUT_SUB_SPS = 15,
  AL_AVC_NUT_DPS = 16,
  AL_AVC_NUT_RSV17 = 17,
  AL_AVC_NUT_RSV18 = 18,
  AL_AVC_NUT_AUX = 19,
  AL_AVC_NUT_EXT = 20,
  AL_AVC_NUT_3D_EXT = 21,
  AL_AVC_NUT_RSV22 = 22,
  AL_AVC_NUT_RSV23 = 23,
  AL_AVC_NUT_UNSPEC_24 = 24,
  AL_AVC_NUT_UNSPEC_25 = 25,
  AL_AVC_NUT_UNSPEC_26 = 26,
  AL_AVC_NUT_UNSPEC_27 = 27,
  AL_AVC_NUT_UNSPEC_28 = 28,
  AL_AVC_NUT_UNSPEC_29 = 29,
  AL_AVC_NUT_UNSPEC_30 = 30,
  AL_AVC_NUT_UNSPEC_31 = 31,
  AL_AVC_NUT_ERR = 32,
  AL_HEVC_NUT_TRAIL_N = 0,
  AL_HEVC_NUT_TRAIL_R = 1,
  AL_HEVC_NUT_TSA_N = 2,
  AL_HEVC_NUT_TSA_R = 3,
  AL_HEVC_NUT_STSA_N = 4,
  AL_HEVC_NUT_STSA_R = 5,
  AL_HEVC_NUT_RADL_N = 6,
  AL_HEVC_NUT_RADL_R = 7,
  AL_HEVC_NUT_RASL_N = 8,
  AL_HEVC_NUT_RASL_R = 9,
  AL_HEVC_NUT_RSV_VCL_N10 = 10,
  AL_HEVC_NUT_RSV_VCL_R11 = 11,
  AL_HEVC_NUT_RSV_VCL_N12 = 12,
  AL_HEVC_NUT_RSV_VCL_R13 = 13,
  AL_HEVC_NUT_RSV_VCL_N14 = 14,
  AL_HEVC_NUT_RSV_VCL_R15 = 15,
  AL_HEVC_NUT_BLA_W_LP = 16,
  AL_HEVC_NUT_BLA_W_RADL = 17,
  AL_HEVC_NUT_BLA_N_LP = 18,
  AL_HEVC_NUT_IDR_W_RADL = 19,
  AL_HEVC_NUT_IDR_N_LP = 20,
  AL_HEVC_NUT_CRA = 21,
  AL_HEVC_NUT_RSV_IRAP_VCL22 = 22,
  AL_HEVC_NUT_RSV_IRAP_VCL23 = 23,
  AL_HEVC_NUT_RSV_VCL24 = 24,
  AL_HEVC_NUT_RSV_VCL25 = 25,
  AL_HEVC_NUT_RSV_VCL26 = 26,
  AL_HEVC_NUT_RSV_VCL27 = 27,
  AL_HEVC_NUT_RSV_VCL28 = 28,
  AL_HEVC_NUT_RSV_VCL29 = 29,
  AL_HEVC_NUT_RSV_VCL30 = 30,
  AL_HEVC_NUT_RSV_VCL31 = 31,
  AL_HEVC_NUT_VPS = 32,
  AL_HEVC_NUT_SPS = 33,
  AL_HEVC_NUT_PPS = 34,
  AL_HEVC_NUT_AUD = 35,
  AL_HEVC_NUT_EOS = 36,
  AL_HEVC_NUT_EOB = 37,
  AL_HEVC_NUT_FD = 38,
  AL_HEVC_NUT_PREFIX_SEI = 39,
  AL_HEVC_NUT_SUFFIX_SEI = 40,
  AL_HEVC_NUT_RSV_NVCL41 = 41,
  AL_HEVC_NUT_RSV_NVCL42 = 42,
  AL_HEVC_NUT_RSV_NVCL43 = 43,
  AL_HEVC_NUT_RSV_NVCL44 = 44,
  AL_HEVC_NUT_RSV_NVCL45 = 45,
  AL_HEVC_NUT_RSV_NVCL46 = 46,
  AL_HEVC_NUT_RSV_NVCL47 = 47,
  AL_HEVC_NUT_UNSPEC_48 = 48,
  AL_HEVC_NUT_UNSPEC_49 = 49,
  AL_HEVC_NUT_UNSPEC_50 = 50,
  AL_HEVC_NUT_UNSPEC_51 = 51,
  AL_HEVC_NUT_UNSPEC_52 = 52,
  AL_HEVC_NUT_UNSPEC_53 = 53,
  AL_HEVC_NUT_UNSPEC_54 = 54,
  AL_HEVC_NUT_UNSPEC_55 = 55,
  AL_HEVC_NUT_UNSPEC_56 = 56,
  AL_HEVC_NUT_UNSPEC_57 = 57,
  AL_HEVC_NUT_UNSPEC_58 = 58,
  AL_HEVC_NUT_UNSPEC_59 = 59,
  AL_HEVC_NUT_UNSPEC_60 = 60,
  AL_HEVC_NUT_UNSPEC_61 = 61,
  AL_HEVC_NUT_UNSPEC_62 = 62,
  AL_HEVC_NUT_UNSPEC_63 = 63,
  AL_HEVC_NUT_ERR = 64,
  AL_NUT_ERR = ~0,
}AL_ENut;

