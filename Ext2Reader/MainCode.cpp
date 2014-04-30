#include "Ext2.h"



using namespace std;

int saveDump(const char* path, char** dest) {

	unsigned long size = 0;

	ifstream file(path, std::ifstream::binary);

	if (!file)      
	{
		cerr << "Kann Datei: " << path << " nicht lesen oder finden" << endl;
		return 0;                     
	}

	file.seekg(0, file.end);
	size = file.tellg();
	file.seekg(0, file.beg);

	cout << endl << "Filesize of " << path << ": " << size << " Bytes" << endl << endl;

	*dest = (char*)malloc(sizeof(char)*size);

	file.read(*dest, size);

	return size;
}


void main() {

	cout << "************************" << endl;
	cout << "- - EXT2 File Reader - -" << endl;
	cout << "************************" << endl;

	char* dump;
	unsigned long dump_size;

	dump_size = saveDump("ext2fs1.raw", &dump);

	Superblock* sb = new Superblock(dump, dump_size, 0);
//	GroupDescriptorTable* gd_table = new GroupDescriptorTable(dump, sb->get_struct());



	free(dump);
}