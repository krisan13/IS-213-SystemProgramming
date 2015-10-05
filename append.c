#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
  int fd;

  if (argc < 3)
  {
    printf("%s\n", "Usage: append <file> <message>");
    return -1;
  }

  fd = open(argv[1], O_CREAT | O_APPEND | O_WRONLY, 0644);

  if (fd == -1)
  {
    perror("open");
    return -1;
  }

  return 0;
}
