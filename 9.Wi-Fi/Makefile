# name of your application
APPLICATION = wi-fi

# If no BOARD is found in the environment, use this default:

# esp32 flashing
BOARD ?= esp32-wroom-32
# BOARD ?= native
PROG_DEV=/dev/ttyS17
PROGRAMMER_SPEED=115200

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
#DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

USEMODULE += esp_wifi
USEMODULE += netdev_default
WIFI_SSID += "YourNetName"
WIFI_PASS += "YourNetPassword"

USEMODULE += periph_gpio # для работы с GPIO
USEMODULE += xtimer # x таймеры
USEMODULE += periph_gpio_irq # поддержка прерываний от GPIO
USEMODULE += atomic_utils # атомарный доступ к памяти
USEMODULE += stdio_uart # вывод для uart
USEMODULE += analog_util


# FEATURES_REQUIRED += periph_gpio periph_i2c periph_adc

#USEMODULE += dht
#USEMODULE += bme280_i2c

# CFLAGS += -DBMX280_PARAM_I2C_DEV=I2C_DEV\‍(0\‍)
# CFLAGS += -DBMX280_PARAM_I2C_ADDR=0x77

#paho-mqtt depends on TCP support, choose which stacks you want
LWIP_IPV4 ?= 1
# LWIP_IPV6 ?= 1

include Makefile.lwip

USEMODULE += sock_udp
USEMODULE += sock_tcp
USEMODULE += sock_ip
USEMODULE += sock_async_event

####

include $(RIOTBASE)/Makefile.include

ifneq (,$(filter arch_esp,$(FEATURES_USED)))
  CFLAGS += -DWIFI_SSID=\"$(WIFI_SSID)\"
  CFLAGS += -DWIFI_PASS=\"$(WIFI_PASS)\"
endif
