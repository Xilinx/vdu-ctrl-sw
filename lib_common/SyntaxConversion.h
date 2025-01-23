// SPDX-FileCopyrightText: © 2025 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once

#include "lib_common/HDR.h"

/***************************************************************************/
int32_t AL_H273_ColourDescToColourPrimaries(AL_EColourDescription colourDesc);

/***************************************************************************/
AL_EColourDescription AL_H273_ColourPrimariesToColourDesc(int32_t iColourPrimaries);

/***************************************************************************/
int32_t AL_TransferCharacteristicsToVUIValue(AL_ETransferCharacteristics eTransferCharacteristics);

/***************************************************************************/
AL_ETransferCharacteristics AL_VUIValueToTransferCharacteristics(int32_t iTransferCharacteristics);

/***************************************************************************/
int32_t AL_ColourMatrixCoefficientsToVUIValue(AL_EColourMatrixCoefficients eColourMatrixCoef);

/***************************************************************************/
AL_EColourMatrixCoefficients AL_VUIValueToColourMatrixCoefficients(int32_t iColourMatrixCoef);
