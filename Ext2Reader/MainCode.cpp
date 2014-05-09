#include "GroupDescriptor.h"
#include "GroupDescriptorTable.h"
#include "Inode.h"
#include "InodeTable.h"
#include "InodeCluster.h"
#include "Superblock.h"
#include "Directory.h"


#include <direct.h>
#include <string.h>

#include "C:\Users\Dennis\SkyDrive\C++ Workspace\Betriebssysteme\C++\!ITI.h"

using namespace std;

void DisplayValue(char *Content, long Size) {
	//cout<<hex;
	long i = 0;
	long j = 0;

	for (; Size != i;) {
		for (; Size != i; ++i) {
			printf("%02X", (unsigned char)Content[i]);
			if (15 == (i & 15)) {
				++i;
				break;
				//cout<<endl;
			}
			if (3 == (i & 3)) {
				cout << " ";
			}
		}
		printf("%03s", " - |");
		for (; Size != j; ++j) {
			if (((Content[j] >= ' ') && (Content[j] <= '~')) ||
				((Content[j] >= 128) && (Content[j] <= 255))) {
				cout << Content[j];
			}
			else {
				cout << (char)177;
			}
			if (15 == (j & 15)) {
				++j;
				break;
			}
			if (3 == (j & 3)) {
				cout << " ";
			}
		}
		cout << "|" << endl;
	}
}

char* concat(char* string1, char* string2, char* string3) {

	int length1 = strlen(string1);
	int length2 = strlen(string2);
	int length3 = strlen(string3);

	char* ret = (char*)malloc(length1 + length2 + length3 + 1);

	memcpy(ret, string1, length1);

	memcpy(ret + length1, string2, length2);

	memcpy(ret + length1 + length2, string3, length3);

	ret[length1 + length2 + length3] = 0;

	return ret;
}

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

void calc_used_blocks(Superblock* sb, char* block_bitmap, int* used_blocks) {

	cout << "Calculating used blocks..";

	for (int i = 0; i < (sb->get_struct()->s_blocks_count); i++) {

		int mod = 1 << (i % 8);

		if (block_bitmap[i / 8] & mod)
			used_blocks[i] = 1;

		/*if (i >= 0 && i < 300)
		cout << "TEST " << i << ": " << used_blocks[i] << endl;*/
	}

	cout << " Done." << endl;
}

void calc_used_inodes(Superblock* sb, char* inode_bitmap, int* used_inodes) {

	cout << "Calculating used inodes.. " /*<< endl*/;

	/*cout << "Used Inodes" << endl;
	cout << "-----------" << endl;*/

	for (int i = 0; i < (sb->get_struct()->s_inodes_count); i++) {

		int mod = 1 << (i % 8);

		if (inode_bitmap[i / 8] & mod)
			used_inodes[i] = 1;

		// you can print used inodes here!
		/*if (used_inodes[i] == 1)
			cout << "ID " << i << ": " << used_inodes[i] << endl;*/
	}

	cout << "Done." << endl;
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

	outstream->close();

	return 1;
}

List* make_dir_list(char* dump, Inode* p_inode) {

	List* directories = new List;
	Directory* current;

	for (int i = 0; i < 12; i++) {

		if (p_inode->get_struct()->i_block[i] != 0) {

			for (int j = 0, k = 0, l = p_inode->get_struct()->i_size * p_inode->get_struct()->i_block[i]; j < p_inode->get_struct()->i_size; j += current->get_struct()->rec_len) {

				current = new Directory(dump, l);

				l += current->get_struct()->rec_len;
				directories->Insert<Directory>(k, current);
				k++;
			}
		}
	}

	return directories;
}

void create_directory(char* dump, Superblock* sb,  InodeCluster* inode_cluster, char* name, List* directories, int blocksize) {

	mkdir(name);

	Directory* dir_current;
	Inode* i_current;

	for (int i = 0; i < directories->GetSize(); i++) {

		directories->Get<Directory>((iusy)i, &dir_current);

		int inode_number = dir_current->get_struct()->inode;

		int inode_blockgroup = (inode_number - 1) / sb->get_struct()->s_inodes_per_group;
		int inode_localindex = (inode_number - 1) % sb->get_struct()->s_inodes_per_group;

		i_current = inode_cluster->get(inode_blockgroup)->get_array()[inode_localindex];

		if (dir_current->get_struct()->file_type == 1) {

			save_inode_to_file(dump, concat(name, "/", (dir_current->get_struct()->name)), 
				i_current, blocksize);
		}
		else if (dir_current->get_struct()->file_type == 2 && strcmp(dir_current->get_struct()->name, ".") && strcmp(dir_current->get_struct()->name, "..")) {

			create_directory(dump, sb, inode_cluster, concat(name, "/", dir_current->get_struct()->name), make_dir_list(dump, i_current), blocksize);
		}
	}
}

void main() {

	cout << "************************" << endl;
	cout << "- - EXT2 File Reader - -" << endl;
	cout << "************************" << endl;

	char* dump;
	unsigned long dump_size;

	dump_size = saveDump("ext2fs2.raw", &dump);

	Superblock* sb = new Superblock(dump, dump_size, 0, 2);
	GroupDescriptorTable* gd_table = new GroupDescriptorTable(dump, sb);

	GroupDescriptor* test = gd_table->get_array()[2];

	int temp_blocksize = 1024 << sb->get_struct()->s_log_block_size;

	cout << "Rebuilding Block Bitmap..";
	char* block_bitmap = (char*)&dump[temp_blocksize * (gd_table->get_array()[0]->get_struct()->bg_block_bitmap)];
	cout << " Done" << endl;

	cout << "Rebuilding Inode Bitmap..";
	char* inode_bitmap = (char*)&dump[temp_blocksize * (gd_table->get_array()[0]->get_struct()->bg_inode_bitmap)];
	cout << " Done" << endl << endl;

	InodeCluster* inode_cluster = new InodeCluster(dump, sb, gd_table);

	int* used_blocks = new int[sb->get_struct()->s_blocks_count]();

	int* used_inodes = new int[sb->get_struct()->s_inodes_count]();

	cout << endl << endl << endl;

	calc_used_blocks(sb, block_bitmap, used_blocks);
	calc_used_inodes(sb, inode_bitmap, used_inodes);

	cout << endl;

	//creating root directory list
	cout << "Creating root Directory.." << endl;
	List* directories = make_dir_list(dump, inode_cluster->get(0)->get_array()[1]);
	create_directory(dump, sb, inode_cluster, "root", directories, temp_blocksize);
	cout << "Done." << endl << endl;

	free(dump);
}