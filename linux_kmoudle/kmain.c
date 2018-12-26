#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

//int* g_ptr = NULL;


static int inf_rec(void) {
    return inf_rec();
}

static int my_init(void) {
    printk("Hello Kernel!\n");
    //*g_ptr = 1;
    inf_rec();
    return 0;
}

static void my_exit(void) {
    printk("kmain exiting\n");
}

module_init(my_init);
module_exit(my_exit);
