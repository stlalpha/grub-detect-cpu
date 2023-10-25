# GRUB ARM CPU Check Module

A custom GRUB module to check if the system is running on an ARM CPU and perform actions accordingly.

## Description

This custom GRUB module allows you to check the CPU architecture during the GRUB boot process and take specific actions based on whether the CPU is of the ARM architecture or not.

I needed a way to do this, and couldnt find anything that worked.  You can write multiple modules for the discrete cpu types you care about and run through them in your boot.cfg, and evaluate
the env variable when complete.   
