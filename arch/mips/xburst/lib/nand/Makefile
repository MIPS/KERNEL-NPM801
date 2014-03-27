
obj-$(CONFIG_NAND) += fate.o

$(obj)/fate.o:$(obj)/lib.a

ifdef CONFIG_NAND_MANAGER_V1_4_2
$(obj)/lib.a:$(obj)/libnm.hex.version_1.4.2
	cp $(obj)/libnm.hex.version_1.4.2 $(obj)/lib.a
endif

ifdef CONFIG_NAND_MANAGER_V1_6_1
$(obj)/lib.a:$(obj)/libnm.hex.version_1.6.1
	cp $(obj)/libnm.hex.version_1.6.1 $(obj)/lib.a
endif

ifdef CONFIG_NAND_MANAGER_V1_6_2
$(obj)/lib.a:$(obj)/libnm.hex.version_1.6.2
	cp $(obj)/libnm.hex.version_1.6.2 $(obj)/lib.a
endif

clean:
archclean:
	rm $(obj)/lib.a
