#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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
  int fd, buffer_length;
  char *pid = intToString(getpid());
  char *buffer;
  struct timeval time;

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

  buffer_length = strlen((const char*)pid) + strlen((const char*)argv[2]) + 23; // 8 for chars, 15 for timestamp
  buffer = malloc(buffer_length);
  signal(SIGINT, interrupt);
  while (keepRunning)
  {
    gettimeofday(&time, NULL);
    sprintf(buffer, "%lu - %s (%s) \n", time.tv_sec * 1000 + time.tv_usec / 1000, argv[2], pid);
    if (write(fd, buffer, buffer_length) == -1)
    {
      perror("write");
      break;
    }
    usleep(10 * 1000);
  }

  free(pid);
  free(buffer);
  close(fd);
  return 0;
}
