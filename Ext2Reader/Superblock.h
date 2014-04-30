#pragma once

#include "Ext2.h"

using namespace std;

struct ext2_super_block {
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

class Superblock
{
public:

	Superblock(char* dump, unsigned long dump_size, int offset = 0);
	Superblock(char* dump, unsigned long dump_size, int offset, int offset_addition);
	~Superblock();

	ext2_super_block* get_struct() { return sb_struct; }

private:

	ext2_super_block* sb_struct;

	void print_details();
	int findSB(char* dump, unsigned long dump_size, int offset);
	int findSB_with_addition(char* dump, unsigned long dump_size, int offset, int offset_addition);
};

