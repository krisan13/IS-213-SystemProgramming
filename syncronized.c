#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv){

	int fd;

	fd = open("testFile", O_WRONLY | O_CREAT);

	if (fsync (fd) == -1){

		if (errno == EINVAL) {

			if (fdatasync (fd) == -1)
				perror("fdatasync");

		}
		else
			perror ("fsync");

	}
}
