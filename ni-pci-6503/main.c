#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/pci.h>

/*
 * A sample PCI device driver for the
 * National Instruments PCI-6503.
 *
 * The kernel comes pre-supplied with 
 * the comedi driver. This needs to be
 * removed first.
 */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Stephen Davies");

static struct pci_device_id ids[] = {
	{ PCI_DEVICE(PCI_VENDOR_ID_NI, 0x17D0), },
	{ 0, }
};
MODULE_DEVICE_TABLE(pci, ids);

/* ripped from mite.h and mite_setup2() to avoid mite dependency */
#define MITE_IODWBSR	0xc0	/* IO Device Window Base Size Register */
#define WENAB		BIT(7)	/* window enable */

static int pci_8255_mite_init(struct pci_dev *pcidev)
{
	void __iomem *mite_base;
	u32 main_phys_addr;

	/* ioremap the MITE registers (BAR 0) temporarily */
	mite_base = pci_ioremap_bar(pcidev, 0);
	if (!mite_base)
		return -ENOMEM;

	/* set data window to main registers (BAR 1) */
	main_phys_addr = pci_resource_start(pcidev, 1);
	writel(main_phys_addr | WENAB, mite_base + MITE_IODWBSR);

	/* finished with MITE registers */
	iounmap(mite_base);
	return 0;
}

static int ni_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	int ret;

	if (pci_enable_device(dev)) {
		dev_err(&dev->dev, "can't enable PCI device\n");
		return -ENODEV;
	}

	ret = pci_8255_mite_init(dev);
	if (ret)
		return ret;

	//if (pci_request_region_exclusive(dev, PCI_BASE_ADDRESS_0, "my_pci1")) {
	//	return -1;
	//}

	return 0;
}

static void ni_remove(struct pci_dev *dev)
{
	pci_disable_device(dev);
}

static struct pci_driver pci_driver = {
	.name = "ni6503",
	.id_table = ids,
	.probe = ni_probe,
	.remove = ni_remove,
};
 
static __init int ni_init(void)
{
	return pci_register_driver(&pci_driver);
}

static __exit void ni_exit(void)
{
	pci_unregister_driver(&pci_driver);
}

module_init(ni_init);
module_exit(ni_exit);

