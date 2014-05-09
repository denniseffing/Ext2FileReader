#include "GroupDescriptor.h"


GroupDescriptor::GroupDescriptor(char* dump, unsigned long offset)
{
	gd_offset = offset;

	create_gd(dump, offset);
}


GroupDescriptor::~GroupDescriptor()
{
}

void GroupDescriptor::create_gd(char* dump, unsigned long offset) {

	gd_struct = (ext2_group_desc*)&dump[offset];
}