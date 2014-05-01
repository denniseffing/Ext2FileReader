#pragma once
#include "Ext2.h"

struct ext2_inode {
	unsigned short   i_mode;         /* File mode */
	unsigned short   i_uid;          /* Owner Uid */
	unsigned long   i_size;         /* Size in bytes */
	unsigned long   i_atime;        /* Access time */
	unsigned long   i_ctime;        /* Creation time */
	unsigned long   i_mtime;        /* Modification time */
	unsigned long   i_dtime;        /* Deletion Time */
	unsigned short   i_gid;          /* Group Id */
	unsigned short   i_links_count;  /* Links count */
	unsigned long   i_blocks;       /* Blocks count */
	unsigned long   i_flags;        /* File flags */
	union {
		struct {
			unsigned long  l_i_reserved1;
		} linux1;
		struct {
			unsigned long  h_i_translator;
		} hurd1;
		struct {
			unsigned long  m_i_reserved1;
		} masix1;
	} osd1;                         /* OS dependent 1 */
	unsigned long   i_block[EXT2_N_BLOCKS];/* Pointers to blocks */
	unsigned long   i_version;      /* File version (for NFS) */
	unsigned long   i_file_acl;     /* File ACL */
	unsigned long   i_dir_acl;      /* Directory ACL */
	unsigned long   i_faddr;        /* Fragment address */
	union {
		struct {
			unsigned char    l_i_frag;       /* Fragment number */
			unsigned char    l_i_fsize;      /* Fragment size */
			unsigned short   i_pad1;
			unsigned long   l_i_reserved2[2];
		} linux2;
		struct {
			unsigned char    h_i_frag;       /* Fragment number */
			unsigned char    h_i_fsize;      /* Fragment size */
			unsigned short   h_i_mode_high;
			unsigned short   h_i_uid_high;
			unsigned short   h_i_gid_high;
			unsigned long   h_i_author;
		} hurd2;
		struct {
			unsigned char    m_i_frag;       /* Fragment number */
			unsigned char    m_i_fsize;      /* Fragment size */
			unsigned short   m_pad1;
			unsigned long   m_i_reserved2[2];
		} masix2;
	} osd2;                         /* OS dependent 2 */
};

class Inode
{
public:
	Inode(char* dump, int offset);
	~Inode();

	ext2_inode* get_struct() { return inode_struct; }

private:
	ext2_inode* inode_struct;

	void create_inode(char* dump, int offset);
};

