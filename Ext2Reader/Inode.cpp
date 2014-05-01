#include "Inode.h"


Inode::Inode(char* dump, int offset)
{
	create_inode(dump, offset);
}


Inode::~Inode()
{
}

void Inode::create_inode(char* dump, int offset) {

	inode_struct = (ext2_inode*)&dump[offset];
}