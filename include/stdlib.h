#ifndef STDLIB_H
#define STDLIB_H

#define NULL		((void*)0)

#define SEEK_CUR        1
#define SEEK_END        2

#define O_RDONLY        0
#define O_WRONLY        1
#define O_RDWR          2
#define O_TRUNC         0x400
#define O_CREAT         0x200

extern long rand_set_seed(long int sd);
extern long rand_get_seed();
extern unsigned long rand();

extern float logf(float v);
extern long strlen(const char *s);
extern long sprintf(char *s, const char *st, ...);

extern int isdigit(int c);
extern int isspace(int c);
extern int isalpha(int c);
extern int isupper(int c);

extern int strcmp(const char *s1, const char *s2);
extern int strncmp(const char *s1, const char *s2, long n);
extern char *strchr(const char *s, int c);
extern void *memcpy(void *dest, const void *src, long n);
extern void *malloc(long size);
extern void free(void *p);

extern long strtol(const char *nptr, char **endptr, int base);
#define atoi(n) strtol((n),NULL,0)


extern void SleepTask(long msec);
extern long mkdir(const char *dirname);
extern long taskLock();
extern long taskUnlock();

extern long Fopen_Fut(const char *filename, const char *mode);
extern void Fclose_Fut(long file);
extern long Fread_Fut(void *buf, long elsize, long count, long f);
extern long Fwrite_Fut(const void *buf, long elsize, long count, long f);
extern long Fseek_Fut(long file, long offset, long whence);

extern int creat (const char *name, int flags);
extern int open (const char *name, int flags, int mode );
extern int close (int fd);
extern int write (int fd, void *buffer, long nbytes);
extern int read (int fd, void *buffer, long nbytes);
extern int lseek (int fd, long offset, int whence);

#define fopen(a,b) Fopen_Fut(a,b)
#define fclose(a) Fclose_Fut(a)
#define fread(a,b,c,d) Fread_Fut(a,b,c,d)
#define fwrite(a,b,c,d) Fwrite_Fut(a,b,c,d)
#define fseek(a,b,c) Fseek_Fut(a,b,c)

//#define FILENAME_MAX 260
//typedef	long	time_t;
//typedef	unsigned long	_fsize_t;
//struct _finddata_t
//{
//	unsigned	attrib;		/* Attributes, see constants above. */
//	time_t		time_create;
//	time_t		time_access;	/* always midnight local time */
//	time_t		time_write;
//	_fsize_t	size;
//	char		name[FILENAME_MAX];	/* may include spaces. */
//};
//struct dirent
//{
//	long		d_ino;		/* Always zero. */
//	unsigned short	d_reclen;	/* Always zero. */
//	unsigned short	d_namlen;	/* Length of name in d_name. */
//	char		d_name[FILENAME_MAX]; /* File name. */
//};
//typedef struct
//{
//	struct _finddata_t	dd_dta;
//	struct dirent		dd_dir;
//	long			dd_handle;
//	int			dd_stat;
//	char			dd_name[1];
//} DIR;

struct dirent {
    char                name[100];
};

typedef struct {
    unsigned int        fd;
    unsigned int        loc;
    struct dirent       dir;
} DIR;

extern DIR* opendir (const char* name);
extern struct dirent* readdir (DIR*);
extern int   closedir (DIR*);
extern void  rewinddir (DIR*);


#endif
