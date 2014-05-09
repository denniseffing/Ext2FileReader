#include "InodeCluster.h"


InodeCluster::InodeCluster(char* dump, Superblock* sb, GroupDescriptorTable* gd_table) {

	inode_tables = (InodeTable**)malloc(sizeof(InodeTable*) * gd_table->get_blocks_group_count());

	create_inode_tables(dump, sb, gd_table, inode_tables);
}


InodeCluster::~InodeCluster() {

	free(inode_tables);
}

void InodeCluster::create_inode_tables(char* dump, Superblock* sb, GroupDescriptorTable* gd_table, InodeTable** dest) {

	int groups_count = gd_table->get_blocks_group_count();

	for (int i = 0; i < groups_count; i++) {

		dest[i] = new InodeTable(dump, sb, gd_table->get_array()[i]);
	}
}