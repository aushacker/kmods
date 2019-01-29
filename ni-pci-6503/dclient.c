
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

#define MEM_SIZE 4096

int main(void)
{
	int fd;
	unsigned char * map = NULL;

	fd = open("/sys/bus/pci/devices/0000:03:02.0/resource1", O_RDWR | O_SYNC);

	if (fd < 0) {
		printf("failed\n");
		return -1;
	} else {
		printf("opened ok\n");
	}

	map = (unsigned char *)(mmap(NULL, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));

	map[3] = 0x80;
	map[0] = 2;

	munmap(map, MEM_SIZE);
	
	close(fd);
	return 0;
}

