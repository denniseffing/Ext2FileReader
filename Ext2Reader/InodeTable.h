#pragma once


#include "GroupDescriptorTable.h"
#include "Inode.h"
#include "Superblock.h"


class InodeTable {



public:
	InodeTable(char* dump, Superblock* sb, GroupDescriptorTable* gd_table);
	~InodeTable();

	unsigned long size() { return table_size; }

	Inode** get_array() { return inode_array; }

private:

	unsigned long table_size;

	Inode** inode_array;
};

