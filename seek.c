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

	off_t ret;
	//set file position of fd to 1825
	ret = lseek (fd, (off_t) 1825, SEEK_SET);
	if (ret == (off_t) -1)
		perror("Seek error:");

	//set file position of fd to end of file
	ret = lseek (fd,0, SEEK_END);
        if (ret == (off_t) -1)
                perror("Seek error:");

	int pos;
	
	//set pos to position of cursor
	pos = lseek (fd, 0, SEEK_CUR);
	if (pos == (off_t) -1){
		perror("Error finding position:");
	}
	else {
		printf("File position is %d",pos);
	}


	close(fd);
}
