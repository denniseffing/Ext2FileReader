#include "InodeTable.h"


InodeTable::InodeTable(char* dump, Superblock* sb, GroupDescriptorTable* gd_table) {

	cout << "Rebuilidng Inode Table" << endl;
	cout << "----------------------" << endl << endl;

	cout << "Creating Inode Array.." << endl;
	table_size = gd_table->get_blocks_group_count() * sb->get_struct()->s_inodes_per_group * sizeof(ext2_inode);
	cout << "Size of Table: " << table_size << " Bytes" << endl << endl;

	inode_array = (Inode**)malloc(table_size);

	cout << "Allocating Inodes" << endl;
	cout << "-----------------" << endl;

	int temp_blocksize = 1024 << sb->get_struct()->s_log_block_size;




	for (int i = 0; i < sb->get_struct()->s_inodes_per_group; i++) {

		for (int j = 0; j < gd_table->get_blocks_group_count(); j++) {

			if (i < 5)
				cout << (gd_table->get_array()[j]->get_struct()->bg_inode_table) * temp_blocksize + sizeof(ext2_inode)*i << endl;

			inode_array[i] = new Inode(dump, (gd_table->get_array()[j]->get_struct()->bg_inode_table) * temp_blocksize + sizeof(ext2_inode)*i);
		}
	}
}


InodeTable::~InodeTable() {

	free(inode_array);
}

