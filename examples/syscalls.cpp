/* Includes */
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>

extern "C"{

int _getpid(void)
{
	return 1;
}

int _kill(int pid, int sig)
{
	errno = EINVAL;
	return -1;
}

void _exit (int status)
{
	_kill(status, -1);
	while (1) {} //Make sure we hang here
}

int _read(int file, char *ptr, int len)
{
	return -1;
}

int _write(int file, char *ptr, int len)
{
	return -1;
}

int _close(int file)
{
	return -1;
}


int _fstat(int file, struct stat *st)
{
	st->st_mode = S_IFCHR;
	return 0;
}

int _isatty(int file)
{
	return 1;
}

int _lseek(int file, int ptr, int dir)
{
	return 0;
}

int _open(char *path, int flags, ...)
{
	return -1;
}

int _wait(int *status)
{
	errno = ECHILD;
	return -1;
}

int _unlink(char *name)
{
	errno = ENOENT;
	return -1;
}

int _gettimeofday(struct timeval* tv, void* tz) {
    return -1;
}

int _times(struct tms *buf)
{
	return -1;
}

int _stat(char *file, struct stat *st)
{
	st->st_mode = S_IFCHR;
	return 0;
}

int _link(char *old, char *n)
{
	errno = EMLINK;
	return -1;
}

int _fork(void)
{
	errno = EAGAIN;
	return -1;
}

int _execve(char *name, char **argv, char **env)
{
	errno = ENOMEM;
	return -1;
}

void *_sbrk(ptrdiff_t incr)
{
	return NULL;
}

int __aeabi_atexit(void *object,
		void (*destructor)(void *),
		void *dso_handle)
{
	return 0;
}

void __cxa_pure_virtual()
{
	
}

namespace __gnu_cxx {
void __verbose_terminate_handler()
{
  while(1);
}
}

}