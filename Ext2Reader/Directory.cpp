#include "Directory.h"


Directory::Directory(char* dump, int offset)
{
	memcpy(&d_struct, &dump[offset], 8);

	d_struct.name = (char*)malloc(d_struct.name_len + 1);

	memcpy(d_struct.name, &dump[offset] + 8, d_struct.name_len + 1);

	d_struct.name[d_struct.name_len] = 0;
}


Directory::~Directory()
{
	free(d_struct.name);
}
