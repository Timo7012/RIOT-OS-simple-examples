# name of your application
APPLICATION = interrupts

# If no BOARD is found in the environment, use this default:

# BOARD ?= nucleo-l152re
# BOARD ?= nucleo-f103rb
# BOARD ?= bluepill-stm32f103cb

# weact-f411ce flashing 
BOARD ?= weact-f411ce #Type-C DFU Mode
# weact-f411ce flashing with OpenOCD
PROGRAMMER = openocd
OPENOCD_DEBUG_ADAPTER = stlink
FLASHFILE = bin/weact-f411ce/interrupts.elf 
OPENOCD_RESET_USE_COONECT_ASSERT_SRST = 1
OPENOCD_CONFIG = openocd.cfg


USEMODULE += periph_gpio # GPIO
USEMODULE += periph_gpio_irq # GPIO Interrupts
USEMODULE += xtimer

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1
include $(RIOTBASE)/Makefile.include
