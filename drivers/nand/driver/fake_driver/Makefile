#
# Makefile for Namd driver
#

ifdef CONFIG_NAND_MANAGER_V1_4_2
EXTRA_CFLAGS	+= -Idrivers/nand/manager_v1.4.2/inc/ \
		-Idrivers/nand/inc/ \
		-Idrivers/nand/manager_v1.4.2/inc/linux/
endif


ifdef CONFIG_NAND_MANAGER_V1_6_1
EXTRA_CFLAGS	+= -Idrivers/nand/manager_v1.6.1/inc/ \
		-Idrivers/nand/inc/ \
		-Idrivers/nand/manager_v1.6.1/inc/linux/
endif

ifdef CONFIG_NAND_MANAGER_V1_6_2
EXTRA_CFLAGS	+= -Idrivers/nand/manager_v1.6.2/inc/ \
		-Idrivers/nand/inc/ \
		-Idrivers/nand/manager_v1.6.2/inc/linux/
endif

obj-y		+= os_vnand.o
