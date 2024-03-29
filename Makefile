CFLAGS+=-O3
CFLAGS+=-g0

SCM_REV:=-D'SCM_REV="$(shell git rev-parse HEAD 2> /dev/null || echo 0)"'
SCM_BRANCH=-D'SCM_BRANCH="$(shell git rev-parse --abbrev-ref HEAD 2> /dev/null || echo unknown)"'

REQUIRED_MAKE_VERSION:=4.0
ifneq ($(REQUIRED_MAKE_VERSION), $(firstword $(sort $(MAKE_VERSION) $(REQUIRED_MAKE_VERSION))))
  $(error Bad 'make' version $(MAKE_VERSION), required a version $(REQUIRED_MAKE_VERSION) or higher)
endif

include config.mk

-include delivery.mk

DELIVERY_BUILD_NUMBER?=-D'DELIVERY_BUILD_NUMBER=0'
DELIVERY_SCM_REV?=-D'DELIVERY_SCM_REV="unknown"'
DELIVERY_DATE?=-D'DELIVERY_DATE="unknown"'

# Cross build support
CROSS_COMPILE?=
CXX:=$(CROSS_COMPILE)g++
CC:=$(CROSS_COMPILE)gcc
AS:=$(CROSS_COMPILE)as
AR:=$(CROSS_COMPILE)gcc-ar
NM:=$(CROSS_COMPILE)gcc-nm
LD:=$(CROSS_COMPILE)ld
OBJDUMP:=$(CROSS_COMPILE)objdump
OBJCOPY:=$(CROSS_COMPILE)objcopy
RANLIB:=$(CROSS_COMPILE)gcc-ranlib
STRIP:=$(CROSS_COMPILE)strip
SIZE:=$(CROSS_COMPILE)size

TARGET:=$(shell $(CC) -dumpmachine)


all: true_all

# Basic build rules and external variables
include ctrlsw_version.mk
include codec_defs.mk
include base.mk
-include compiler.mk

# Libraries
-include lib_fpga/project.mk
-include lib_common/project.mk
-include lib_rtos/project.mk
-include lib_ip_ctrl/project.mk
-include lib_perfs/project.mk
-include lib_app/project.mk #lib_common and lib_perfs dependency


BUILD_EXE_FBC=0
BUILD_EXE_FBD=0



ifneq ($(BUILD_EXE_FBC),0)
  -include lib_fbc_standalone/project.mk
endif

BUILD_LIB_COM_DEC=0
ifneq ($(ENABLE_DECODER),0)
  BUILD_LIB_COM_DEC=1
endif
ifneq ($(BUILD_LIB_COM_DEC),0)
  -include lib_common_dec/project.mk
endif

-include ref.mk

ifneq ($(ENABLE_DECODER),0)
  # AL_Decoder
  -include lib_parsing/project.mk
  -include lib_scheduler_dec/project.mk
  -include lib_decode/project.mk
  -include exe_decoder/project.mk
endif




ifneq ($(BUILD_EXE_FBC),0)
  # AL_Compress
  -include exe_compress/project.mk
endif
ifneq ($(BUILD_EXE_FBD),0)
  # AL_Decompress
  -include lib_fbd_standalone/project.mk
  -include exe_decompress/project.mk
endif




ifneq ($(ENABLE_PERF),0)
  # AL_PerfMonitor
  -include exe_perf_monitor/project.mk
endif





INSTALL ?= install -c
PREFIX ?= /usr
HDR_INSTALL_OPT = -m 0644

INCLUDE_DIR := include
HEADER_DIRS_TMP := $(sort $(dir $(wildcard $(INCLUDE_DIR)/*/)))
HEADER_DIRS := $(HEADER_DIRS_TMP:$(INCLUDE_DIR)/%=%)
INSTALL_HDR_PATH := ${PREFIX}/include
INSTALL_PATH ?= /bin/

install_headers:
	mkdir -p ${INSTALL_HDR_PATH}
	@echo $(HEADER_DIRS)
	for dirname in $(HEADER_DIRS); do \
		$(INSTALL) -d "$(INCLUDE_DIR)/$$dirname" "$(INSTALL_HDR_PATH)/$$dirname"; \
		$(INSTALL) $(HDR_INSTALL_OPT) "$(INCLUDE_DIR)/$$dirname"/*.h "$(INSTALL_HDR_PATH)/$$dirname"; \
	done; \
	$(INSTALL) $(HDR_INSTALL_OPT) "$(INCLUDE_DIR)"/*.h "$(INSTALL_HDR_PATH)/";

pack_includes:
	@echo $(PACK_INCLUDES)

pack_defines:
	@echo $(PACK_DEFINES)

install: install_headers
	mkdir -p ${INSTALL_PATH}
	install -Dm 0755 bin/AL_Decoder.exe ${INSTALL_PATH}/ctrlsw_decoder

true_all: $(TARGETS)

.PHONY: true_all clean all
