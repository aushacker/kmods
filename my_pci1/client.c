
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

int main(void)
{
	int fd;
	unsigned char * map = NULL;

	fd = open("/dev/mem", O_RDWR | O_SYNC);

	if (fd < 0) {
		printf("failed\n");
		return -1;
	} else {
		printf("opened ok\n");
	}

	map = (unsigned char *)(mmap(NULL, 8192, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0xfe800000));

	for (int i = 0; i < 16; i++) {
		printf("%02x ", map[i]);
	}
	printf("\n");

	munmap(map, 8192);
	
	close(fd);
	return 0;
}

