#pragma once


using namespace std;

struct ext2_group_desc
{
	unsigned long   bg_block_bitmap;        /* Blocks bitmap block */
	unsigned long   bg_inode_bitmap;        /* Inodes bitmap block */
	unsigned long   bg_inode_table;         /* Inodes table block */
	unsigned short   bg_free_blocks_count;   /* Free blocks count */
	unsigned short   bg_free_inodes_count;   /* Free inodes count */
	unsigned short   bg_used_dirs_count;     /* Directories count */
	unsigned short   bg_pad;
	unsigned long   bg_reserved[3];
};

class GroupDescriptor
{
public:
	GroupDescriptor(char* dump, int offset);
	~GroupDescriptor();

	ext2_group_desc* get_struct() { return gd_struct; }

private:

	ext2_group_desc* gd_struct;
	
	void create_gd(char* dump, int offset);
};

