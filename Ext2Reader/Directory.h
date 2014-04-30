#pragma once
#include "Ext2.h"

struct ext2_dir_entry {
	unsigned long   inode;                  /* Inode number */
	unsigned short  rec_len;                /* Directory entry length */
	unsigned short  name_len;               /* Name length */
	char    name[EXT2_NAME_LEN];			/* File name */
};

class Directory
{
public:
	Directory();
	~Directory();
};

