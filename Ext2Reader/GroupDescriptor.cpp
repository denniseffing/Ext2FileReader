#include "GroupDescriptor.h"


GroupDescriptor::GroupDescriptor(char* dump, int offset)
{
	create_gd(dump, offset);
}


GroupDescriptor::~GroupDescriptor()
{
}

void GroupDescriptor::create_gd(char* dump, int offset) {

	gd_struct = (ext2_group_desc*)&dump[offset];
}