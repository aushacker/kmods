
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

#define MEM_SIZE 16384

int main(void)
{
	int fd;
	unsigned char * map = NULL;

	//fd = open("/dev/mem", O_RDWR | O_SYNC);
	fd = open("/sys/bus/pci/devices/0000:01:00.0/resource0", O_RDWR | O_SYNC);

	if (fd < 0) {
		printf("failed\n");
		return -1;
	} else {
		printf("opened ok\n");
	}

	map = (unsigned char *)(mmap(NULL, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));

	for (int i = 0; i < 16; i++) {
		printf("%02x ", map[i]);
		map[i]++;
	}
	printf("\n");

	for (int i = 0; i < 16; i++) {
		printf("%02x ", map[i + 8192]);
	}
	printf("\n");

	munmap(map, MEM_SIZE);
	
	close(fd);
	return 0;
}

