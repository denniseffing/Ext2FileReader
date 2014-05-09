#pragma once

#include "Superblock.h"
#include "GroupDescriptorTable.h"
#include "InodeTable.h"

class InodeCluster {

private:
	InodeTable** inode_tables;

	void create_inode_tables(char* dump, Superblock* sb, GroupDescriptorTable* gd_table, InodeTable** dest);

public:
	InodeCluster(char* dump, Superblock* sb, GroupDescriptorTable* gd_table);
	~InodeCluster();


	InodeTable* get(int index) {

		return inode_tables[index];
	}
};

