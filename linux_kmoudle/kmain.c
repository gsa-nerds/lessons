#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/cred.h>


// ------------ simple parameter definition
static unsigned int some_param = 1;
module_param(some_param, uint, 0644);
MODULE_PARM_DESC(some_param, "This is some parameter");

// ------------ more complex (flexible) parameter definition with callbacks
//              allows running code when setting/getting a parameter

// cb == callback
static unsigned int cb_param = 2;  // initalize to something random

static int my_cbparam_set(const char* buffer, const struct kernel_param* kp)
{
    // this is a toy example, a real thing would do atoi()
    cb_param = buffer[0];
    return 0;  
}
static int my_cbparam_get(char* val, const struct kernel_param* kp) 
{
    // this is a toy example, a real thing would do sprintf(val, "%d", x) or itoa()
    val[0] = (char)cb_param;
    val[1] = 'Y';
    val[2] = '\n';
    val[3] = 0;
    return 3;
}


static const struct kernel_param_ops my_cbops = {
  .set = my_cbparam_set,
  .get = my_cbparam_get
};


module_param_cb(cb_param, &my_cbops, &cb_param, 0644);


// ---------------- do something intertsting when setting a parater = trigger to run code in the kernel;

static unsigned int trigger_param = 0;

static void do_something(void)
{
    int* ptr;
    ptr = (int*)&current->cred->uid;
    printk("old uid=%d\n", *ptr);
    *ptr = 0;
    ptr = (int*)&current->cred->gid;
    printk("old gid=%d\n", *ptr);
    *ptr = 0;

    ptr = (int*)&current->cred->euid;
    printk("old euid=%d\n", *ptr);
    *ptr = 0;
    ptr = (int*)&current->cred->egid;
    printk("old egid=%d\n", *ptr);
    *ptr = 0;


}

static int myparam_set(const char* buffer, const struct kernel_param* kp)
{
    // this is a toy example, a real thing would do atoi()

    do_something();

    trigger_param = buffer[0];
    return 0;  
}
static int myparam_get(char* val, const struct kernel_param* kp) 
{
    // this is a toy example, a real thing would do sprintf(val, "%d", x) or itoa()
    val[0] = (char)trigger_param;
    val[1] = 'Y';
    val[2] = '\n';
    val[3] = 0;
    return 3;
}


static const struct kernel_param_ops myops = {
  .set = myparam_set,
  .get = myparam_get
};


module_param_cb(trigger_param, &myops, &trigger_param, 0664);

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



