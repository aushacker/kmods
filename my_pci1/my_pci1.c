#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/pci.h>

MODULE_LICENSE("MIT");

static struct pci_device_id ids[] = {
	{ PCI_DEVICE(PCI_VENDOR_ID_XILINX, 0x0007), },
	{ 0, }
};
MODULE_DEVICE_TABLE(pci, ids);

static int my_pci1_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	if (pci_enable_device(dev)) {
		dev_err(&dev->dev, "can't enable PCI device\n");
		return -ENODEV;
	}

	return 0;
}

static void my_pci1_remove(struct pci_dev *dev)
{
}

static struct pci_driver pci_driver = {
	.name = "my_pci1",
	.id_table = ids,
	.probe = my_pci1_probe,
	.remove = my_pci1_remove,
};
 
static __init int my_pci1_init(void)
{
	return pci_register_driver(&pci_driver);
}

static __exit void my_pci1_exit(void)
{
	pci_unregister_driver(&pci_driver);
}

module_init(my_pci1_init);
module_exit(my_pci1_exit);

