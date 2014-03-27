# drivers/nand/driver/Makefile
#

KBUILD_CFLAGS += -I$(srctree)/drivers/nand/inc/

ifdef CONFIG_NAND_MANAGER_V1_4_2
KBUILD_CFLAGS += -I$(srctree)/drivers/nand/manager_v1.4.2/inc/
endif

ifdef CONFIG_NAND_MANAGER_V1_6_1
KBUILD_CFLAGS += -I$(srctree)/drivers/nand/manager_v1.6.1/inc/
endif

ifdef CONFIG_NAND_MANAGER_V1_6_2
KBUILD_CFLAGS += -I$(srctree)/drivers/nand/manager_v1.6.2/inc/
endif

obj-$(CONFIG_REAL_NAND_DRIVER) += nand_api.o
obj-$(CONFIG_REAL_NAND_DRIVER) += core/ jz_ctrl/
obj-$(CONFIG_NAND_DMA) += dma/
obj-$(CONFIG_FAKE_NAND_DRIVER) += fake_driver/
