#include <grub/types.h>
#include <grub/env.h>
#include <grub/misc.h>
#include <grub/dl.h>
#include <grub/command.h>

/* This is a simple module to check if the CPU is ARM or not.
 * It's not perfect, but it's good enough for our purposes.
 * -jm 10/25/2023 jim.mcbride@gmail.com
 *
*/

GRUB_MOD_LICENSE("GPLv3+");

static void check_arm(void)
{
    grub_uint32_t value = 0;

    // Print ASCII Art
    grub_printf("   ,--.\n");
    grub_printf(" /      \\\n");
    grub_printf("<  πMiga  >\n");
    grub_printf(" \\      /\n");
    grub_printf("   `--'\n");
    grub_printf("\n");
    grub_printf("Checking CPU type...\n");

    // Execute a basic ARM MOV instruction to move the value 42 into a register.
    asm volatile("mov %0, #42"
                 : "=r"(value));

    // Check the result to determine if we're on an ARM CPU.
    if (value == 42)
    {
        grub_env_set("cpu_type", "arm");
        grub_printf("Running on ARM CPU. Set cpu_type=arm.\n");
    }
    else
    {
        grub_printf("Not running a known ARM cpu.\n");

        // Set an error environment variable (optional)
        grub_env_set("cpu_error", "unknown_cpu_type");
    }
}

GRUB_MOD_INIT(check_arm)
{
    check_arm();
}

GRUB_MOD_FINI(check_arm)
{
    // Cleanup actions, if needed.
}
