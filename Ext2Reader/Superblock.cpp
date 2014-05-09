#include "Superblock.h"



Superblock::Superblock(char* dump, unsigned long dump_size, int offset) {

	cout << "Searching for Superblock..." << endl;

	findSB(dump, dump_size, offset);

	s_blockID = s_offset / (1024 << get_struct()->s_log_block_size);

	print_details();
}

Superblock::Superblock(char* dump, unsigned long dump_size, int offset, int offset_addition) {

	cout << "Searching for Superblock..." << endl;

	findSB_with_addition(dump, dump_size, offset, offset_addition);

	s_blockID = s_offset / (1024 << get_struct()->s_log_block_size);

	print_details();
}

Superblock::~Superblock() {
}

void Superblock::print_details() {

	cout << "Inodes: " << sb_struct->s_inodes_count << endl;
	cout << "Blocks: " << sb_struct->s_blocks_count << endl;
	cout << "Log Blocksize: " << sb_struct->s_log_block_size << endl << endl << endl;
}

int Superblock::findSB(char* dump, unsigned long dump_size, int offset) {

	int sb_found = 0;

	sb_struct = (ext2_super_block*)&dump[offset];

	for (int i = 0; !(sb_struct->s_magic == MAGIC_NUMBER) && offset + i < dump_size; i += 512) {

		if (offset + i < dump_size)		
			sb_struct = (ext2_super_block*)&dump[offset + i];

		if (sb_struct->s_magic == MAGIC_NUMBER) {
			sb_found = 1;

			s_offset = offset + i;

			cout << "Superblock found at offset: " << s_offset << endl << endl;
		}
	}

	if (sb_found == 0)
		cout << "Could not find Superblock. Exiting..";

	return sb_found;
}

int Superblock::findSB_with_addition(char* dump, unsigned long dump_size, int offset, int offset_addition) {

	int sb_found = 0;

	sb_struct = (ext2_super_block*)&dump[offset];

	for (unsigned long i = 0; !(sb_struct->s_magic == MAGIC_NUMBER) && offset + i < dump_size; i += offset_addition) {

		if (offset + i < dump_size)
			sb_struct = (ext2_super_block*)&dump[offset + i];

		if (sb_struct->s_magic == MAGIC_NUMBER) {
			sb_found = 1;

			s_offset = offset + i;

			cout << "Superblock found at Offset: " << s_offset << endl << endl;

			cout << "DEBUG: " << i << endl;
		}
	}

	if (sb_found == 0)
		cout << "Could not find Superblock. Exiting..";

	return sb_found;
}