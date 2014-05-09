#pragma once
#include "Ext2.h"

struct ext2_dir_entry {
	unsigned long   inode;                  /* Inode number */
	unsigned short  rec_len;                /* Directory entry length */
	unsigned char  name_len;               /* Name length */
	unsigned char   file_type;				/* File type */
	char*    name;							/* File name */
};

class Directory
{
private:
	ext2_dir_entry d_struct;

public:
	Directory(char* dump, int offset);
	~Directory();

	ext2_dir_entry* get_struct() {
		return &d_struct;
	}
};

