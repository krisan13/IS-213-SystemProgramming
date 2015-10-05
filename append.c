#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

static volatile bool keepRunning = true;

char* intToString(int i)
{
  int digits = 1;
  int mod = 10;
  char *result;

  while (floor(i % mod) < i)
  {
    digits++;
    mod *= 10;
  }

  result = malloc(digits);
  sprintf(result, "%d", i);
  return result;
}

static void interrupt(int signo)
{
  printf("Interrupted\n");
  keepRunning = false;
}

int main(int argc, char **argv)
{
  int fd;
  char *pid = intToString(getpid());
  char *buffer;

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

  buffer = malloc(sizeof(*pid) + sizeof(*argv[2]) + 4);
  sprintf(buffer, "%s (%s) ", argv[2], pid);
  signal(SIGINT, interrupt);
  while (keepRunning)
  {
    if (write(fd, buffer, sizeof(buffer)) == -1)
    {
      perror("write");
      break;
    }
    usleep(10 * 1000);
  }

  close(fd);
  return 0;
}
