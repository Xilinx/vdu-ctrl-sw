/******************************************************************************
*
* Copyright (C) 2015-2022 Allegro DVT2
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

/**************************************************************************//*!
   \addtogroup Buffers
   @{
   \file
 **************************************************************************/
#pragma once

#define AL_ENC_MAX_SEI_SIZE (10 * 1024)
#define AL_ENC_MAX_CONFIG_HEADER_SIZE (2 * 1024)
#define AL_ENC_MAX_HEADER_SIZE (AL_ENC_MAX_CONFIG_HEADER_SIZE + AL_ENC_MAX_SEI_SIZE)

#include "Profiles.h"
#include "lib_common/PicFormat.h"

/*************************************************************************//*!
   \brief Retrieves the maximum size of one VCL NAL unit
   This returns the actual worst case a NAL unit could take.
   If you want the decoder bitstream buffer to always be able to hold a frame,
   you should use this function to allocate them as the decoder can't assume
   the possible worst case stream generated by the encoder which generated
   the stream. If you are in a controlled environment, you might want to look
   at AL_GetMitigatedMaxNalSize().
   \param[in] tDim Frame dimension
   \param[in] eMode Chroma subsampling
   \param[in] iBitDepth Bitdepth
   \param[in] eProfile Profile
   \param[in] iLevel Level
   \return maximum size of one NAL unit
*****************************************************************************/
int AL_GetMaxNalSize(AL_TDimension tDim, AL_EChromaMode eMode, int iBitDepth, AL_EProfile eProfile, int iLevel);

/*************************************************************************//*!
   \brief Retrieves the most likely to happen real worst case size of the encoder
   generated NAL unit.
   You should use this function to allocate the encoder bitstream buffers as
   it optimize the memory footprint.
   \param[in] tDim Frame dimension
   \param[in] eMode Chroma subsampling
   \param[in] iBitDepth Bitdepth
   \return maximum size of one NAL unit
*****************************************************************************/
int AL_GetMitigatedMaxNalSize(AL_TDimension tDim, AL_EChromaMode eMode, int iBitDepth);

/*************************************************************************//*!
   \brief Retrieves the minimal memory space needed for the encoder to generate
   one frame.
   You should use this function to determine the minimal allocated buffer used for
   encoding. The user must add space for the slice datas of the frame
   \param[in] iNumSlices Number of slices in the frame
   \param[in] eCodec Codec used for encoding
   \return Minimal size for non-VCL NAL unit, slice header and
   specific structure to encode one frame
*****************************************************************************/
int AL_GetMinimalNalSize(int iNumSlices, AL_ECodec eCodec);

/*@}*/
