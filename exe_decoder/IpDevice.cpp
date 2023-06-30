/******************************************************************************
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

#include <iostream>
#include <stdexcept>
#include <memory>

#include <dirent.h>
#include <cstring>

#include "IpDevice.h"
#include "lib_app/console.h"
#include "lib_app/utils.h"

extern "C"
{
#include "lib_fpga/DmaAlloc.h"
#include "lib_perfs/Logger.h"
}

using namespace std;

AL_TAllocator* createDmaAllocator(const char* deviceName)
{
  auto h = AL_DmaAlloc_Create(deviceName);

  if(h == nullptr)
    throw runtime_error("Can't find dma allocator (trying to use " + string(deviceName) + ")");
  return h;
}

std::string g_DecDevicePath = "/dev/allegroDecodeIP";

extern "C"
{
#include "lib_decode/DecSchedulerMcu.h"
}

AL_TAllocator* CreateProxyAllocator(char const*)
{
  // support for the proxy allocator isn't compiled in.
  return nullptr;
}

void CIpDevice::ConfigureMcu(AL_TDriver* driver, bool useProxy)
{

  if(m_bDeviceisPresent){
   int i = 0;

   if(useProxy)
    m_pAllocator[i] = CreateProxyAllocator(g_DecDevicePath.c_str());
   else
    m_pAllocator[i] = createDmaAllocator(g_DecDevicePath.c_str());

   if(!m_pAllocator[i])
     throw runtime_error("Can't open DMA allocator");

   m_pScheduler[i] = AL_DecSchedulerMcu_Create(driver, g_DecDevicePath.c_str());

   if(!m_pScheduler[i])
     throw runtime_error("Failed to create MCU scheduler");
  }else{
   for(int i = 0; i < m_nIPDevices; i++)
   {
    string sDevice_name = string("/dev/allegroDecodeIP") + to_string(i);
    char const* device_name = sDevice_name.c_str();

    if(useProxy)
      m_pAllocator[i] = CreateProxyAllocator(device_name);
    else
      m_pAllocator[i] = createDmaAllocator(device_name);

    if(!m_pAllocator[i])
      throw runtime_error("Can't open DMA allocator");

    m_pScheduler[i] = AL_DecSchedulerMcu_Create(driver, device_name/*g_DecDevicePath.c_str()*/);

    if(!m_pScheduler[i])
      throw runtime_error("Failed to create MCU scheduler");
   }
  }
}

CIpDevice::~CIpDevice()
{
 if(m_bDeviceisPresent){
    int i = 0;
    if(m_pScheduler[i])
        AL_IDecScheduler_Destroy(m_pScheduler[i]);

      if(m_pAllocator[i])
        AL_Allocator_Destroy(m_pAllocator[i]);
  }else{
    for(int i = 0; i < m_nIPDevices; i++)
    {
      if(m_pScheduler[i])
        AL_IDecScheduler_Destroy(m_pScheduler[i]);

      if(m_pAllocator[i])
        AL_Allocator_Destroy(m_pAllocator[i]);
    }
  }
}

int CIpDevice::CountIPDevices()
{
  DIR* directory = opendir("/dev");
  if (directory == nullptr) {
          cerr<< "Error: could not open directory\n";
  }

  struct dirent* entry;
  int count = 0;
  while ((entry = readdir(directory)) != nullptr) {
         if (std::strncmp(entry->d_name, "allegroDecodeIP", 15) == 0) {
                 ++count;
         }
  }
  m_nIPDevices = count;
  closedir(directory);
  return count;
}

void CIpDevice::Configure(CIpDeviceParam& param)
{

  m_bDeviceisPresent = param.bDeviceisPresent;
  if(param.iSchedulerType == AL_SCHEDULER_TYPE_MCU)
  {
    ConfigureMcu(AL_GetHardwareDriver(), false);
    return;
  }

  throw runtime_error("No support for this scheduling type");
}

