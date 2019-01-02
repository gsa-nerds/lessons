#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>


// ------------ simple parameter definition
static unsigned int some_param = 1;
module_param(some_param, uint, 0644);
MODULE_PARM_DESC(some_param, "This is some parameter");

// ------------ more complex (flexible) parameter definition

static unsigned int trigger_param = 2;

static int myparam_set(const char* buffer, const struct kernel_param* kp)
{
    // this is a toy example, a real thing would do atoi()
    trigger_param = buffer[0];
    return 0;  
}
static int myparam_get(char* val, const struct kernel_param* kp) 
{
    // this is a toy example, a real thing would do sprintf(val, "%d", x) or itoa()
    val[0] = 'X';
    val[1] = 'Y';
    val[2] = '\n';
    val[3] = 0;
    return 3;
}


static const struct kernel_param_ops myops = {
  .set = myparam_set,
  .get = myparam_get
};

module_param_cb(trigger_param, &myops, &trigger_param, 0644);


// ---------------- initialization and destruction of the module

static int my_init(void) {
    printk("Hello Kernel!\n");
    return 0;
}

// exit is mandatory, otherwise the module can't go down
static void my_exit(void) {
    printk("kmain exiting %d trigger=%d\n", some_param, trigger_param);
}

module_init(my_init);
module_exit(my_exit);



