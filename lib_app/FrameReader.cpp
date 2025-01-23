// SPDX-FileCopyrightText: © 2025 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "lib_app/FrameReader.h"

#include <fstream>

uint64_t FrameReader::GetFileSize(void)
{
  auto position = m_recFile.tellg();
  m_recFile.seekg(0, std::ios_base::end);
  auto size = m_recFile.tellg();
  m_recFile.seekg(position);
  return size;
}

int32_t FrameReader::GotoNextPicture(int32_t iFileFrameRate, int32_t iEncFrameRate, int32_t iEncPictCount, int32_t iFilePictCount)
{
  const int32_t iMove = ((iEncPictCount * iFileFrameRate) / iEncFrameRate) - iFilePictCount;

  if(iMove)
    this->SeekR(iMove);

  return iMove;
}
