# Makefile for nand block
#

EXTRA_CFLAGS		+= -Idrivers/nand/inc/

obj-$(CONFIG_NAND)	+= nand_block.o nand_char.o nand_debug.o
obj-$(CONFIG_NAND)	+= driver/


ifndef CONFIG_ANDROID
	obj-$(CONFIG_NAND)	+= nandfs/
endif

ifdef CONFIG_NAND_MANAGER_V1_4_2
	EXTRA_CFLAGS            += -Idrivers/nand/manager_v1.4.2/inc/
	obj-$(CONFIG_NAND)      += manager_v1.4.2/
endif

ifdef CONFIG_NAND_MANAGER_V1_6_1
	EXTRA_CFLAGS            += -Idrivers/nand/manager_v1.6.1/inc/
	obj-$(CONFIG_NAND)      += manager_v1.6.1/
endif

ifdef CONFIG_NAND_MANAGER_V1_6_2
	EXTRA_CFLAGS           	+= -Idrivers/nand/manager_v1.6.2/inc/
obj-$(CONFIG_NAND)      	+= manager_v1.6.2/
endif
