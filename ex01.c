#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){


	int fd;

	fd = open("madagascar", O_WRONLY | O_TRUNC);

	if (fd == -1){
		printf("Error opening file\n");
	}
	else{
		printf("File opened\n");
	}


	return 0;
}
