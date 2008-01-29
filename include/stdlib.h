#ifndef STDLIB_H
#define STDLIB_H

#ifndef NULL
#define NULL		((void*)0)
#endif

#define __cdecl

//#define _CRTIMP

//#define __inline__

#define __NO_ISOCEXT


//
// !!! stat is 0x48 bytes on digic
//
#define _STAT_DEFINED TRUE

struct	stat
    {
    unsigned long	st_dev;		/* device ID number */
    unsigned long	st_ino;		/* file serial number */
    unsigned short	st_mode;	/* file mode (see below) */
    short		st_nlink;	/* number of links to file */
    short		st_uid;		/* user ID of file's owner */
    short		st_gid;		/* group ID of file's group */
    unsigned long	st_rdev;	/* device ID, only if special file */
    unsigned long	st_size;	/* size of file, in bytes */
    unsigned long	st_atime;	/* time of last access */
    unsigned long	st_mtime;	/* time of last modification */
    unsigned long	st_ctime;	/* time of last change of file status */
    long		st_blksize;
    long		st_blocks;
    unsigned char	st_attrib;	/* file attribute byte (dosFs only) */
    int			reserved1;	/* reserved for future use */
    int			reserved2;	/* reserved for future use */
    int			reserved3;	/* reserved for future use */
    int			reserved4;	/* reserved for future use */
    int			reserved5;	/* reserved for future use */
    int			reserved6;	/* reserved for future use */
};

#define _stat stat

#include "stdio.h"
#include <fcntl.h>
#include <io.h>
#include <sys/stat.h>
#include <string.h>


extern int rand(void);
extern void* srand(unsigned int seed);

extern void qsort (void *__base, int __nelem, int __size, int (*__cmp)(const void *__e1, const void *__e2));

extern int isdigit(int c);
extern int isspace(int c);
extern int isalpha(int c);
extern int isupper(int c);

extern int sprintf(char *, const char *, ...);

extern long strtol(const char *nptr, char **endptr, int base);
#define atoi(n) strtol((n),NULL,0)

extern void *malloc(long size);
extern void free(void *p);
extern void *umalloc(long size);
extern void ufree(void *p);


extern void SleepTask(long msec);
extern long taskLock();
extern long taskUnlock();

extern long Fopen_Fut(const char *filename, const char *mode);
extern void Fclose_Fut(long file);
extern long Fread_Fut(void *buf, long elsize, long count, long f);
extern long Fwrite_Fut(const void *buf, long elsize, long count, long f);
extern long Fseek_Fut(long file, long offset, long whence);
extern long RenameFile_Fut(const char *oldname, const char *newname);
extern long Feof_Fut(long file);
extern long DeleteFile_Fut(const char *name);
extern long Fflush_Fut(long file);

extern int _Open (const char *name, int flags, int mode );
extern int _Close (int fd);
extern int _Write (int fd, void *buffer, long nbytes);
extern int _Read (int fd, void *buffer, long nbytes);
extern int _Lseek (int fd, long offset, int whence);
extern int _Remove(const char *name);

#define feof Feof_Fut
#define fdelete DeleteFile_Fut

#define open _Open
#define close _Close
#define write _Write
#define read _Read
#define lseek _lseek
#define remove _Remove
#define mkdir _mkdir

#define fopen(a,b) Fopen_Fut(a,b)
#define fclose(a) Fclose_Fut(a)
#define fread(a,b,c,d) Fread_Fut(a,b,c,d)
#define fwrite(a,b,c,d) Fwrite_Fut(a,b,c,d)
#define fseek(a,b,c) Fseek_Fut(a,b,c)
#define fflush(a) Fflush_Fut(a)
#define feof(a) Feof_Fut(a)
#define fdelete(a) DeleteFile_Fut(a)

extern void msleep(long msec);
extern long task_lock();
extern long task_unlock();

#define DOS_ATTR_RDONLY         0x01            /* read-only file */
#define DOS_ATTR_HIDDEN         0x02            /* hidden file */
#define DOS_ATTR_SYSTEM         0x04            /* system file */
#define DOS_ATTR_VOL_LABEL      0x08            /* volume label (not a file) */
#define DOS_ATTR_DIRECTORY      0x10            /* entry is a sub-directory */
#define DOS_ATTR_ARCHIVE        0x20            /* file subject to archiving */

struct dirent {
    char                name[100];
};

typedef struct {
    unsigned int        fd;
    unsigned int        loc;
    struct dirent       dir;
} DIR;

extern DIR*           opendir (const char* name);
extern struct dirent* readdir (DIR*);
extern int            closedir (DIR*);
extern void           rewinddir (DIR*);


struct tm
	{
	int tm_sec;	/* seconds after the minute	- [0, 59] */
	int tm_min;	/* minutes after the hour	- [0, 59] */
	int tm_hour;	/* hours after midnight		- [0, 23] */
	int tm_mday;	/* day of the month		- [1, 31] */
	int tm_mon;	/* months since January		- [0, 11] */
	int tm_year;	/* years since 1900	*/
	int tm_wday;	/* days since Sunday		- [0, 6] */
	int tm_yday;	/* days since January 1		- [0, 365] */
	int tm_isdst;	/* Daylight Saving Time flag */
	};

extern struct tm * localtime(const unsigned long *_tod);

struct utimbuf {
    unsigned long actime;       /* set the access time */
    unsigned long modtime;      /* set the modification time */
};

extern int utime(char *file, struct utimbuf *newTimes);
extern unsigned long time(unsigned long *timer);

#endif
