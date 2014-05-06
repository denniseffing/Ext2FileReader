#pragma once

//#include "Ext2.h"

#include "Superblock.h"
#include "GroupDescriptor.h"

using namespace std;

class GroupDescriptorTable {

public:
	GroupDescriptorTable(char* dump, Superblock* sb);
	~GroupDescriptorTable();

	unsigned short get_offset() {
		return gd_array[0]->get_offset();
	}
	unsigned short get_blocks_group_count() { return block_groups_count; }
	unsigned short size() { return table_size; }
	GroupDescriptor** get_array() { return gd_array; }

private:

	unsigned short block_groups_count;
	unsigned short table_size;
	GroupDescriptor** gd_array;

	int find_gds(char* dump);
};

