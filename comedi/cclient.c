
#include <stdio.h>
#include <comedilib.h>

int main(void)
{
	comedi_t *cdev;
	int	 rc;

	cdev = comedi_open("/dev/comedi0");
	if (!cdev) {
		comedi_perror("comedi_open");
		return -1;
	}

	// All pins as outputs
	for (int i = 0; i < 24; i++) {
		rc = comedi_dio_config(cdev, 0, i, COMEDI_OUTPUT);
		if (rc) { 
			comedi_perror("comedi_dio_config");
			return -1;
		}
	}

	comedi_dio_write(cdev, 0, 0, 0);
	comedi_dio_write(cdev, 0, 1, 1);

	return 0;
}

