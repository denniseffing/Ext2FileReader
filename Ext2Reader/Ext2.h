#pragma once

#include <iostream>
#include <fstream>


/*
* Constants relative to the data blocks
*/
#define	EXT2_NDIR_BLOCKS		12
#define	EXT2_IND_BLOCK			EXT2_NDIR_BLOCKS
#define	EXT2_DIND_BLOCK			(EXT2_IND_BLOCK + 1)
#define	EXT2_TIND_BLOCK			(EXT2_DIND_BLOCK + 1)
#define	EXT2_N_BLOCKS			(EXT2_TIND_BLOCK + 1)

#define EXT2_NAME_LEN 255

#define MAGIC_NUMBER 0xEF53

class Ext2
{
public:
	Ext2();
	~Ext2();
};

