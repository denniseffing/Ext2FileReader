#include "InodeTable.h"


InodeTable::InodeTable(char* dump, Superblock* sb, GroupDescriptor* gd) {

	cout << "Rebuilidng Inode Table" << endl;
	cout << "----------------------" << endl << endl;

	cout << "Creating Inode Array.." << endl;
	table_size = sb->get_struct()->s_inodes_per_group * sizeof(ext2_inode);
	cout << "Size of Table: " << table_size << " Bytes" << endl << endl;

	inode_array = (Inode**)malloc(table_size);

	cout << "Allocating Inodes" << endl;
	cout << "-----------------" << endl;

	int temp_blocksize = 1024 << sb->get_struct()->s_log_block_size;

	for (int i = 0; i < sb->get_struct()->s_inodes_per_group; i++) {

		// you can print Inode Offsets here!
		/*if (i < 5)
			cout << (gd_table->get_array()[j]->get_struct()->bg_inode_table) * temp_blocksize + sizeof(ext2_inode)*i << endl;*/

		if (i == 0)
			cout << "1. Inode found at Offset: " << (gd->get_struct()->bg_inode_table) * temp_blocksize + sizeof(ext2_inode)*i << endl;

		inode_array[i] = new Inode(dump, (gd->get_struct()->bg_inode_table) * temp_blocksize + sizeof(ext2_inode)*i);
	}

	cout << endl << "Inode Table was successfully rebuilt!" << endl;
	cout << "----------------------" << endl << endl;
}


InodeTable::~InodeTable() {

	free(inode_array);
}

