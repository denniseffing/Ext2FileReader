#pragma once

#include "Ext2.h"

using namespace std;

struct ext2_super_block2 {
	unsigned long   s_inodes_count;         /* Inodes count */
	unsigned long   s_blocks_count;         /* Blocks count */
	unsigned long   s_r_blocks_count;       /* Reserved blocks count */
	unsigned long   s_free_blocks_count;    /* Free blocks count */
	unsigned long   s_free_inodes_count;    /* Free inodes count */
	unsigned long   s_first_data_block;     /* First Data Block */
	unsigned long   s_log_block_size;       /* Block size */
	signed long		s_log_frag_size;        /* Fragment size */
	unsigned long   s_blocks_per_group;     /* # Blocks per group */
	unsigned long   s_frags_per_group;      /* # Fragments per group */
	unsigned long   s_inodes_per_group;     /* # Inodes per group */
	unsigned long   s_mtime;                /* Mount time */
	unsigned long   s_wtime;                /* Write time */
	unsigned short  s_mnt_count;            /* Mount count */
	signed short	s_max_mnt_count;        /* Maximal mount count */
	unsigned short  s_magic;                /* Magic signature */
	unsigned short  s_state;                /* File system state */
	unsigned short  s_errors;               /* Behaviour when detecting errors */
	unsigned short  s_pad;
	unsigned long   s_lastcheck;            /* time of last check */
	unsigned long   s_checkinterval;        /* max. time between checks */
	unsigned long   s_creator_os;           /* OS */
	unsigned long   s_rev_level;            /* Revision level */
	unsigned short  s_def_resuid;           /* Default uid for reserved blocks */
	unsigned short  s_def_resgid;           /* Default gid for reserved blocks */
	unsigned long   s_reserved[235];        /* Padding to the end of the block */
};


struct ext2_super_block {
	unsigned long s_inodes_count;					/*Total number of inodes*/
	unsigned long s_blocks_count;					/*Filesystem size in blocks*/
	unsigned long s_r_blocks_count;					/*Number of reserved blocks*/
	unsigned long s_free_blocks_count;				/*Free blocks counter*/
	unsigned long s_free_inodes_count;				/*Free inodes counter*/
	unsigned long s_first_data_block;				/*Number of first useful block(always 1)*/
	unsigned long s_log_block_size;					/*Block size*/
	signed long s_log_frag_size;					/*Fragment size*/
	unsigned long s_blocks_per_group;				/*Number of blocks per group*/
	unsigned long s_frags_per_group;				/*Number of fragments per group*/
	unsigned long s_inodes_per_group;				/*Number of inodes per group*/
	unsigned long s_mtime;							/*Time of last mount operation*/
	unsigned long s_wtime;							/*Time of last write operation*/
	unsigned short s_mnt_count;						/*Mount operations counter*/
	unsigned short s_max_mnt_count;					/*Number of mount operations before check*/
	unsigned short s_magic;							/*Magic signature*/
	unsigned short s_state;							/*Status flag*/
	unsigned short s_errors;						/*Behavior when detecting errors*/
	unsigned short s_minor_rev_level;				/*Minor revision level*/
	unsigned long s_lastcheck;						/*Time of last check*/
	unsigned long s_checkinterval;					/*Time between checks*/
	unsigned long s_creator_os;						/*OS where filesystem was created*/
	unsigned long s_rev_level;						/*Revision level*/
	unsigned short s_def_resuid;					/*Default UID for reserved blocks*/
	unsigned short s_def_resgid;					/*Default GID for reserved blocks*/
	unsigned long s_first_ino;						/*Number of first nonreserved inode*/
	unsigned short s_inode_size;					/*Size of on - disk inode structure*/
	unsigned short s_block_group_nr;				/*Block group number of this superblock*/
	unsigned long s_feature_compat;					/*Compatible features bitmap*/
	unsigned long s_feature_incompat;				/*Incompatible features bitmap*/
	unsigned long s_feature_ro_compat;				/*Read - only - compatible features bitmap*/
	unsigned char s_uuid[16];						/*128 - bit filesystem identifier*/
	char s_volume_name[16];							/*Volume name*/
	char s_last_mounted[64];						/*Pathname of last mount point*/
	unsigned long s_algorithm_usage_bitmap;			/*Used for compression*/
	unsigned char s_prealloc_blocks;				/*Number of blocks to preallocate*/
	unsigned char s_prealloc_dir_blocks;			/*Number of blocks to preallocate for directories*/
	unsigned char s_padding[818];					/*Nulls to pad out 1024 bytes*/
};


class Superblock
{
public:

	Superblock(char* dump, unsigned long dump_size, int offset = 0);
	Superblock(char* dump, unsigned long dump_size, int offset, int offset_addition);
	~Superblock();

	ext2_super_block* get_struct() { return sb_struct; }

	unsigned short get_offset() { return s_offset; }

private:

	ext2_super_block* sb_struct;

	unsigned short s_offset;

	void print_details();
	int findSB(char* dump, unsigned long dump_size, int offset);
	int findSB_with_addition(char* dump, unsigned long dump_size, int offset, int offset_addition);
};

