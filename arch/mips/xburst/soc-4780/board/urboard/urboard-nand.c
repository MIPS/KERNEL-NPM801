#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/resource.h>

#include <soc/gpio.h>
#include <soc/base.h>
#include <soc/irq.h>

#include <mach/platform.h>

#include <mach/jznand.h>
#include "urboard.h"

#define ECCBIT 24
#ifdef CONFIG_MUL_PARTS

/*
 * These SIZE and OFFSETS must be kept in sync sync with the xboot urboard.h file.
 */

#define MB 0x100000LL                                     /* 1024 * 1024 */

#ifdef CONFIG_PARTITIONS_FOR_2GB_NAND                     /* Original partititions on V1.1 and V1.2 Boards */
#define PTN_BOOT_OFFSET            (8    * MB)
#define PTN_BOOT_SIZE              (16   * MB)
#define PTN_RECOVERY_SIZE          (16   * MB)
#define PTN_MISC_SIZE              (4    * MB)
#define PTN_BATTERY_SIZE           (1    * MB)
#define PTN_DEVICES_ID_SIZE        (2    * MB)
#define PTN_SYSTEM_SIZE            (512  * MB)
#define PTN_USERDATA_SIZE          (1024 * MB)
#define PTN_CACHE_SIZE             (128  * MB)

#define PTN_RECOVERY_OFFSET        (PTN_BOOT_OFFSET + PTN_BOOT_SIZE)
#define PTN_MISC_OFFSET            (PTN_RECOVERY_OFFSET + PTN_RECOVERY_SIZE)
#define PTN_BATTERY_OFFSET         (PTN_MISC_OFFSET + PTN_MISC_SIZE)
#define PTN_DEVICES_ID_OFFSET      (PTN_BATTERY_OFFSET + PTN_BATTERY_SIZE + (14 * MB))
#define PTN_SYSTEM_OFFSET          (PTN_DEVICES_ID_OFFSET + PTN_DEVICES_ID_SIZE + (3 * MB))
#define PTN_USERDATA_OFFSET        (PTN_SYSTEM_OFFSET + PTN_SYSTEM_SIZE)
#define PTN_CACHE_OFFSET           (PTN_USERDATA_OFFSET + PTN_USERDATA_SIZE + (0 * MB))
#define PTN_STORAGE_OFFSET         (PTN_CACHE_OFFSET + PTN_CACHE_SIZE)
#else

#ifdef CONFIG_PARTITIONS_FOR_4GB_NAND
#define SF 2
#else

#ifdef CONFIG_PARTITIONS_FOR_8GB_NAND
#define SF 4
#else
#error   "CONFIG_PARTITIONS_FOR_*GB_NAND is MISSING!"
#endif /* CONFIG_PARTITIONS_FOR_8GB_NAND */
#endif /* CONFIG_PARTITIONS_FOR_4GB_NAND */
#endif /* CONFIG_PARTITIONS_FOR_2GB_NAND */

#define PTN_BOOT_SIZE               (16   * MB)
#define PTN_RECOVERY_SIZE           (16   * MB)
#define PTN_MISC_SIZE               (4    * MB)
#define PTN_BATTERY_SIZE            (1    * MB)
#define PTN_DEVICES_ID_SIZE         (2    * MB)
#define PTN_SYSTEM_SIZE            ((500  * SF) * MB)
#define PTN_USERDATA_SIZE          ((800  * SF) * MB)
#define PTN_CACHE_SIZE             ((500  * SF) * MB)

#define PTN_BOOT_OFFSET            (8    * MB)
#define PTN_RECOVERY_OFFSET        (PTN_BOOT_OFFSET + PTN_BOOT_SIZE)
#define PTN_MISC_OFFSET            (PTN_RECOVERY_OFFSET + PTN_RECOVERY_SIZE)
#define PTN_BATTERY_OFFSET         (PTN_MISC_OFFSET + PTN_MISC_SIZE)
#define PTN_DEVICES_ID_OFFSET      (PTN_BATTERY_OFFSET + PTN_BATTERY_SIZE + (14 * MB))
#define PTN_SYSTEM_OFFSET          (PTN_DEVICES_ID_OFFSET + PTN_DEVICES_ID_SIZE + (3 * MB))
#define PTN_USERDATA_OFFSET        (PTN_SYSTEM_OFFSET + PTN_SYSTEM_SIZE)
#define PTN_CACHE_OFFSET           (PTN_USERDATA_OFFSET + PTN_USERDATA_SIZE)
#define PTN_STORAGE_OFFSET         (PTN_CACHE_OFFSET + PTN_CACHE_SIZE)

/*
 * With a SF of 4 we have a relatively full Partition table on a 8GB NAND chip.
 *
 * name:boot,          start:8 MB,     length:16 MB}
 * name:recovery,      start:24 MB,    length:16 MB}
 * name:misc,          start:40 MB,    length:4 MB}
 * name:battery,       start:44 MB,    length:1 MB}
 * name:device_id,     start:59 MB,    length:2 MB}
 * name:system,        start:64 MB,    length:2000 MB}
 * name:userdata,      start:2064 MB,  length:3200 MB}
 * name:cache,         start:5264 MB,  length:2000 MB}
 * name:storage,       start:7264 MB,  length:0 MB}
 *
 */

/* With a SF of 2 we have a relatively full Partition table on a 4GB NAND chip.
 *
 * name:boot,          start:8 MB,     length:16 MB}
 * name:recovery,      start:24 MB,    length:16 MB}
 * name:misc,          start:40 MB,    length:4 MB}
 * name:battery,       start:44 MB,    length:1 MB}
 * name:device_id,     start:59 MB,    length:2 MB}
 * name:system,        start:64 MB,    length:1000 MB}
 * name:userdata,      start:1064 MB,  length:1600 MB}
 * name:cache,         start:2664 MB,  length:1000 MB}
 * name:storage,       start:3664 MB,  length:0 MB}
 */

static struct platform_nand_partition partition_info[] = {
	{
	name:"ndxboot",
	offset:0 * 0x100000LL,
	size:8 * 0x100000LL,
	mode:SPL_MANAGER,
	eccbit:ECCBIT,
	use_planes:ONE_PLANE,
	part_attrib:PART_XBOOT,
	ex_partition:{{0},{0},{0},{0}}			/* These are the 4 MUL_PARTS */
	},

	{
	name:"ndboot",
	offset: PTN_BOOT_OFFSET,
	size: PTN_BOOT_SIZE,
	mode: DIRECT_MANAGER,
	eccbit: ECCBIT,
	use_planes: ONE_PLANE,
	part_attrib: PART_KERNEL,
	ex_partition:{{0},{0},{0},{0}}
	},

	{
	name: "ndrecovery",
	offset: PTN_RECOVERY_OFFSET,
	size: PTN_RECOVERY_SIZE,
	mode: DIRECT_MANAGER,
	eccbit: ECCBIT,
	use_planes: ONE_PLANE,
	part_attrib: PART_RECOVERY,
	ex_partition: {{0},{0},{0},{0}}
	},

	{
	name:"ndmisc",
	offset: PTN_MISC_OFFSET,
	size: PTN_MISC_SIZE,
	mode: DIRECT_MANAGER,
	eccbit: ECCBIT,
	use_planes: ONE_PLANE,
	part_attrib: PART_MISC,
	ex_partition: {{0},{0},{0},{0}}
	},

	{
	name: "ndsystem",
	offset: PTN_SYSTEM_OFFSET,
	size: PTN_SYSTEM_SIZE,
	mode: ZONE_MANAGER,
	eccbit: ECCBIT,
	use_planes: ONE_PLANE,
	part_attrib: PART_SYSTEM,
	ex_partition: {{0},{0},{0},{0}}
	},

	{
	name:"nddata",
	offset: PTN_USERDATA_OFFSET,
	size: PTN_USERDATA_SIZE,
	mode: ZONE_MANAGER,
	eccbit: ECCBIT,
	use_planes: ONE_PLANE,
	part_attrib: PART_DATA,
	ex_partition: {{0},{0},{0},{0}}
	},

	{
	name:"ndcache",
	offset: PTN_CACHE_OFFSET,
	size: PTN_CACHE_SIZE,
	mode: ZONE_MANAGER,
	eccbit: ECCBIT,
	use_planes: ONE_PLANE,
	part_attrib: PART_CACHE,
	ex_partition: {{0},{0},{0},{0}}
	},
};

/* Define max reserved bad blocks for each partition.
 * This is used by the mtdblock-jz.c NAND FTL driver only.
 *
 * The NAND FTL driver reserves some good blocks which can't be
 * seen by the upper layer. When the bad block number of a partition
 * exceeds the max reserved blocks, then there is no more reserved
 * good blocks to be used by the NAND FTL driver when another bad
 * block generated.
 */
static int partition_reserved_badblocks[] = {
	2,			/* reserved blocks of ndxboot */
	2,			/* reserved blocks of ndboot */
	2,			/* reserved blocks of ndrecovery */
	1,			/* reserved blocks of ndmisc */
	32,			/* reserved blocks of ndsystem */
	32,			/* reserved blocks of ndcache */
	32,			/* reserved blocks of ndextern */
	1,			/* reserved blocks of nderror */
};

#else /* !CONFIG_MUL_PARTS */

static struct platform_nand_partition partition_info[] = {
	{
	name:"ndxboot",
	offset:0 * 0x100000LL,
	size:8 * 0x100000LL,
	mode:SPL_MANAGER,
	eccbit:ECCBIT,
	use_planes:ONE_PLANE,
	part_attrib:PART_XBOOT
	},
	{
	name:"ndboot",
	offset:8 * 0x100000LL,
	size:16 * 0x100000LL,
	mode:DIRECT_MANAGER,
	eccbit:ECCBIT,
	use_planes:ONE_PLANE,
	part_attrib:PART_KERNEL
	},
    {
    name:"ndrecovery",
    offset:24 * 0x100000LL,
    size:16 * 0x100000LL,
    mode:DIRECT_MANAGER,
    eccbit:ECCBIT,
    use_planes:ONE_PLANE,
    part_attrib:PART_KERNEL
    },
	{
	name:"ndsystem",
	offset:64 * 0x100000LL,
	size:512 * 0x100000LL,
	mode:ZONE_MANAGER,
	eccbit:ECCBIT,
	use_planes:ONE_PLANE,
	part_attrib:PART_SYSTEM
    },
	{
	name:"nddata",
	offset:576 * 0x100000LL,
	size:1024 * 0x100000LL,
	mode:ZONE_MANAGER,
	eccbit:ECCBIT,
	use_planes:ONE_PLANE,
	part_attrib:PART_DATA
    },
	{
    name:"ndcache",
    offset:1600 * 0x100000LL,
    size:128 * 0x100000LL,
    mode:ZONE_MANAGER,
    eccbit:ECCBIT,
    use_planes:ONE_PLANE,
    part_attrib:PART_KERNEL
    },
	{
	name:"ndmisc",
	offset:1728 * 0x100000LL,
	size:2368 * 0x100000LL,
	mode:ZONE_MANAGER,
	eccbit:ECCBIT,
	use_planes:ONE_PLANE,
	part_attrib:PART_MISC
    },
};

/* Define max reserved bad blocks for each partition.
 * This is used by the mtdblock-jz.c NAND FTL driver only.
 *
 * The NAND FTL driver reserves some good blocks which can't be
 * seen by the upper layer. When the bad block number of a partition
 * exceeds the max reserved blocks, then there is no more reserved
 * good blocks to be used by the NAND FTL driver when another bad
 * block generated.
 */
static int partition_reserved_badblocks[] = {
	4,			/* reserved blocks of ndxboot */
	8,			/* reserved blocks of ndboot */
	8,			/* reserved blocks of ndrecovery */
	32,			/* reserved blocks of ndsystem */
	64,			/* reserved blocks of nddata */
	16,			/* reserved blocks of ndcache */
	128,		/* reserved blocks of ndmisc */
	1,			/* reserved blocks of nderror */
};
#endif

struct platform_nand_data jz_nand_chip_data = {
	.nr_partitions = ARRAY_SIZE(partition_info),
	.partitions = partition_info,
	/* there is no room for bad block info in struct platform_nand_data */
	/* so we have to use chip.priv */
	.priv = &partition_reserved_badblocks,
        .gpio_wp = GPIO_PF(22),
};
