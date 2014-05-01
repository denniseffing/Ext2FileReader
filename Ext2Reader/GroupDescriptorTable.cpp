#include "GroupDescriptorTable.h"

GroupDescriptorTable::GroupDescriptorTable(char* dump, Superblock* sb) {

	cout << "Rebuilidng Group Descriptor Table" << endl;
	cout << "---------------------------------" << endl;

	block_groups_count = sb->get_struct()->s_inodes_count / sb->get_struct()->s_inodes_per_group;

	cout << "Creating Table Array.." << endl;
	cout << "Block Groups Count: " << block_groups_count << endl;

	table_size = sizeof(GroupDescriptor)*block_groups_count;
	cout << "Size of Table: " << table_size << " Bytes"  << endl << endl;

	gd_array = (GroupDescriptor**)malloc(table_size);	

	cout << "Allocating Group Descriptors" << endl;
	cout << "----------------------------" << endl;

	for (int i = 0; i < block_groups_count; i++) {

		int temp_blocksize = 1024 << sb->get_struct()->s_log_block_size;

		gd_array[i] = new GroupDescriptor(dump, 1024 + sb->get_offset() + sizeof(ext2_group_desc)*i);

		cout << i + 1 << ". Group Descriptor found at offset: " << 1024 + sb->get_offset() + sizeof(ext2_group_desc)*i << endl;
	}

	cout << endl << "Group Descriptor Table was successfully rebuilt!" << endl << endl;
}


GroupDescriptorTable::~GroupDescriptorTable() {

	free(gd_array);
}

