#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int print_help()
{
  printf("Usage: ctryout <source> <destination>\n");
  return -1;
}

//This is the main method
int main(int argc, char **args)
{
  const int BUFFER_SIZE = 1024 * 1024 * 5;
  char buffer[BUFFER_SIZE];
  int file_source, file_dest, bytes_read;

  if (argc < 3)
    return print_help();

  file_source = open(args[1], O_RDONLY);

  if (file_source == -1)
  {
    perror("open");
    return -1;
  }

  file_dest = open(args[2], O_CREAT | O_WRONLY, 0644);

  if (file_dest == -1)
  {
    close(file_source);
    perror("open");
    return -1;
  }

  while ((bytes_read = read(file_source, buffer, BUFFER_SIZE)) != 0)
  {
    if (bytes_read == -1)
    {
      if (errno == EINTR)
        continue;

      perror("read");
      break;
    }

    if (write(file_dest, buffer, bytes_read) == -1)
    {
      perror("write");
      break;
    }
  }

  close(file_source);
  close(file_dest);
  return 0;
}
