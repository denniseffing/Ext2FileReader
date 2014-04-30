#include "GroupDescriptorTable.h"

GroupDescriptorTable::GroupDescriptorTable(char* dump,struct ext2_super_block* sb_struct) {

	block_groups_count = sb_struct->s_inodes_count / sb_struct->s_inodes_per_group;

	gd_array = (GroupDescriptor*)malloc(sizeof(GroupDescriptor) * block_groups_count);

}


GroupDescriptorTable::~GroupDescriptorTable() {
}
