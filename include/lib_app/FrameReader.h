// SPDX-FileCopyrightText: © 2025 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <iostream>
#include <stdexcept>
#include <fstream>

extern "C"
{
#include "lib_common/PicFormat.h"
#include "lib_common/BufferAPI.h"
}

class FrameReader
{
protected:
  std::ifstream& m_recFile;
  bool m_bLoopFile;
  int32_t m_uTotalFrameCnt;

  FrameReader(std::ifstream& iRecFile, bool bLoopFrames) :
    m_recFile(iRecFile),
    m_bLoopFile(bLoopFrames),
    m_uTotalFrameCnt(0) {};

public:
  inline int32_t GetTotalFrameCnt() const { return m_uTotalFrameCnt; }

  virtual bool ReadFrame(AL_TBuffer* pFrameBuffer) = 0;

  virtual void SeekA(uint32_t uFrameIdx) = 0; // seek to Absolution position from the beginning
  virtual void SeekR(int32_t iFrameDlt) = 0;      // seek to Relative position from the current position (both direction allowed)

  int32_t GotoNextPicture(int32_t iFileFrameRate, int32_t iEncFrameRate, int32_t iFilePictCount, int32_t iEncPictCount);

  uint64_t GetFileSize();

  virtual ~FrameReader() = default;
};
