PROGRAM = my_program
OPEN_RTOS_SDK_PATH=../esp-open-rtos

ESPTOOL ?= esptool.py
ESPTOOL_RUN ?=esptool.py

EXTRA_COMPONENTS = extras/commutils
# EXTRA_COMPONENTS=extras/dhcpserver extras/rboot-ota extras/mbedtls extras/espbase  extras/commutils

include $(OPEN_RTOS_SDK_PATH)/common.mk
