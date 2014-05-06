#include "GroupDescriptor.h"
#include "GroupDescriptorTable.h"
#include "Inode.h"
#include "InodeTable.h"
#include "Superblock.h"

using namespace std;

int saveDump(const char* path, char** dest) {

	unsigned long size = 0;

	ifstream file(path, std::ifstream::binary);

	if (!file) {
		cerr << "Kann Datei: " << path << " nicht lesen oder finden" << endl;
		return 0;
	}

	file.seekg(0, file.end);
	size = file.tellg();
	file.seekg(0, file.beg);

	cout << endl << "Filesize of " << path << ": " << size << " Bytes" << endl << endl;

	*dest = (char*)malloc(sizeof(char)*size);

	file.read(*dest, size);

	file.close();

	return size;
}

int saveDumpToFile(const char* path, char* src, int length) {

	ofstream file(path, std::ofstream::binary);

	file.write(path, length);

	file.close();

	return 1;
}

int save_inode_to_file(char* dump, const char* path, Inode* p_inode, int blocksize) {

	ext2_inode* i_struct = p_inode->get_struct();

	ofstream* outstream = new ofstream(path, std::ofstream::binary);

	// 12 direct blocks
	for (int i = 0; i < 12; i++) {

		if (i_struct->i_block[i] != 0)
			outstream->write(&dump[i_struct->i_block[i] * blocksize], blocksize);
	}

	// indirect block
	if (i_struct->i_block[12] != 0) {

		for (int i = 0; i < 256; i++) {

			unsigned long current = ((unsigned long*)&dump[i_struct->i_block[12] * blocksize])[i];

			if (current != 0)
				outstream->write(&dump[current * blocksize], blocksize);
		}
	}

	// double indirect block
	if (i_struct->i_block[13] != 0) {

		for (int i = 0; i < 256; i++) {

			unsigned long current_indirect = ((unsigned long*)&dump[i_struct->i_block[13] * blocksize])[i];

			if (current_indirect != 0) {

				for (int j = 0; j < 256; j++) {

					unsigned long current = ((unsigned long*)&dump[current_indirect * blocksize])[j];

					if (current != 0)
						outstream->write(&dump[current*blocksize], blocksize);
				}
			}
		}
	}

	// triple indirect block
	if (i_struct->i_block[14] != 0) {

		for (int i = 0; i < 256; i++) {

			unsigned long current_double_indirect = ((unsigned long*)&dump[i_struct->i_block[14] * blocksize])[i];

			if (current_double_indirect != 0) {

				for (int j = 0; j < 256; j++) {

					unsigned long current_indirect = ((unsigned long*)&dump[current_double_indirect * blocksize])[j];

					if (current_indirect != 0) {

						for (int k = 0; k < 256; k++) {

							unsigned long current = ((unsigned long*)&dump[current_indirect * blocksize])[k];

							if (current != 0)
								outstream->write(&dump[current*blocksize], blocksize);
						}
					}
				}
			}
		}
	}

	// quadruple indirect block
	if (i_struct->i_block[14] != 0) {

		for (int i = 0; i < 256; i++) {

			unsigned long current_triple_indirect = ((unsigned long*)&dump[i_struct->i_block[14] * blocksize])[i];

			if (current_triple_indirect != 0) {

				for (int j = 0; j < 256; j++) {

					unsigned long current_double_indirect = ((unsigned long*)&dump[current_triple_indirect * blocksize])[j];

					if (current_double_indirect != 0) {

						for (int k = 0; k < 256; k++) {

							unsigned long current_indirect = ((unsigned long*)&dump[current_double_indirect * blocksize])[k];

							if (current_indirect != 0) {

								for (int l = 0; l < 256; l++) {

									unsigned long current = ((unsigned long*)&dump[current_indirect * blocksize])[l];

									if (current != 0)

										outstream->write(&dump[current*blocksize], blocksize);
								}
							}
						}
					}
				}
			}
		}
	}

	return 1;
}


void main() {

	cout << "************************" << endl;
	cout << "- - EXT2 File Reader - -" << endl;
	cout << "************************" << endl;

	char* dump;
	unsigned long dump_size;

	dump_size = saveDump("ext2fs1.raw", &dump);

	Superblock* sb = new Superblock(dump, dump_size, 0);
	GroupDescriptorTable* gd_table = new GroupDescriptorTable(dump, sb);

	int temp_blocksize = 1024 << sb->get_struct()->s_log_block_size;

	cout << "Rebuilding Block Bitmap..";
	char* block_bitmap = (char*)&dump[temp_blocksize * (gd_table->get_array()[0]->get_struct()->bg_block_bitmap)];
	cout << " Done" << endl;

	cout << "Rebuilding Inode Bitmap..";
	char* inode_bitmap = (char*)&dump[temp_blocksize * (gd_table->get_array()[0]->get_struct()->bg_inode_bitmap)];
	cout << " Done" << endl << endl;

	InodeTable* inode_table = new InodeTable(dump, sb, gd_table);

	Inode* nonres_inode = inode_table->get_array()[10];

	save_inode_to_file(dump, "test.jpg", nonres_inode, 1024);


	int* used_blocks = new int[sb->get_struct()->s_blocks_count]();

	int* used_inodes = new int[sb->get_struct()->s_inodes_count]();

	cout << endl << endl << endl;

	// FIND USED BLOCKS
	for (int i = 0; i < (sb->get_struct()->s_blocks_count); i++) {

		int mod = 1 << (i % 8); 

		if (block_bitmap[i / 8] & mod)
			used_blocks[i] = 1;

		/*if (i >= 0 && i < 300)
			cout << "TEST " << i << ": " << used_blocks[i] << endl;*/
	}

	// FIND USED INODES
	for (int i = 0; i < (sb->get_struct()->s_inodes_count); i++) {

		int mod = 1 << (i % 8);

		if (inode_bitmap[i / 8] & mod)
			used_inodes[i] = 1;

		if (used_inodes[i] == 1)
			cout << "TEST " << i << ": " << used_inodes[i] << endl;
	}



	//	saveDumpToFile("test.txt", file2->data_array, 3585 * 1024);

	free(dump);
}