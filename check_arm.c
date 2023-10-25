#include <grub/types.h>
#include <grub/env.h>
#include <grub/misc.h>
#include <grub/dl.h>
#include <grub/command.h>

/* This is a simple module to check if the CPU is ARM or not. 
 * It's not perfect, but it's good enough for our purposes.
 * -jm 10/25/2023 jim.mcbride@gmail.com
 * 
 * compile as a grub module.  insmod it, run check_arm and it will set the environment variable
 * cpu_type to arm if it's running on an ARM CPU.  Then you can access it in the grub environment
 * like this:
 * menuentry "Check CPU Architecture" {
 *   insmod echo
 *   echo "Checking CPU Architecture..."
 *   insmod check_arm
 *   check_arm
 *
 *   if [ "${cpu_type}" = "arm" ]; then
 *       echo "ARM CPU detected - Please insert logic to start AmiBerry here."
 *       sleep 10
 *       # Do arm stuff
 *   else
 *       echo "Doing not ARM stuff"
 *   fi
 *}
 */

GRUB_MOD_LICENSE("GPLv3+");

static grub_err_t grub_cmd_check_arm(grub_command_t cmd __attribute__ ((unused)),
                                     int argc __attribute__ ((unused)),
                                     char *argv[] __attribute__ ((unused)))
{
    grub_uint32_t value = 0;

    // A basic MOV instruction
    asm volatile("mov %0, #42" : "=r"(value));

    // If the value is 42, it's likely an ARM CPU
    if (value == 42) {
        grub_env_set("cpu_type", "arm");
    }

    return GRUB_ERR_NONE;
}

static grub_command_t cmd;

GRUB_MOD_INIT(check_arm)
{
    cmd = grub_register_command("check_arm", grub_cmd_check_arm, 0, "Checks if running on ARM and sets an environment variable.");
}

GRUB_MOD_FINI(check_arm)
{
    grub_unregister_command(cmd);
}
