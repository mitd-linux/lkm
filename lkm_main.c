// main LKM file

#include <linux/kernel.h>           // we are doing KERNEL job
#include <linux/module.h>           // specifically, module
#include <linux/init.h>             // module init
#include <linux/skbuff.h>           // sk_buff
#include <linux/netfilter_ipv4.h>   // netfilter hooks

#include "macros.h"

// metadata
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dmitry Sidorov");

// netfilter hook
unsigned int hook_in(void *priv, struct sk_buff *skb,
                        const struct nf_hook_state *state)
{
    // send packet to queue
    return NF_QUEUE_NR(21);
}

// hook ops for input
static struct nf_hook_ops __nfho_in;

static int __init lkm_init(void)
{
    pr_info("mitfw init");
    
    // nf hooks
    __nfho_in.hook = hook_in;
    __nfho_in.hooknum = NF_INET_LOCAL_IN;
    __nfho_in.pf = PF_INET;
    __nfho_in.priority = NF_IP_PRI_FIRST;
    nf_register_net_hook(&init_net, &__nfho_in);

    return 0;
}

static void __exit lkm_exit(void)
{
    pr_info("mitfw exit");
    nf_unregister_net_hook(&init_net, &__nfho_in);
}

module_init(lkm_init);
module_exit(lkm_exit);
