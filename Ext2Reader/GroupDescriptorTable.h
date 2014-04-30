#pragma once

#include "Ext2.h"

using namespace std;

class GroupDescriptorTable {

public:
	GroupDescriptorTable(char* dump, struct ext2_super_block* sb_struct);
	~GroupDescriptorTable();

private:

	unsigned short block_groups_count;
	GroupDescriptor* gd_array;
};

