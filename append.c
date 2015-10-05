#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>

static volatile bool keepRunning = true;

static void interrupt(int signo)
{
  printf("Interrupted\n");
  keepRunning = false;
}

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

  signal(SIGINT, interrupt);
  while (keepRunning)
  {
    if (write(fd, argv[2], sizeof(argv[2])) == -1)
    {
      perror("write");
      break;
    }
    sleep(1);
  }

  close(fd);
  return 0;
}
