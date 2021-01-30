#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
// My include 
#include "light_sensor.h"

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 350

int init()
{
	int err = 0;
	err = err + light_sensor_init();
	return err;
}

void internal_light(int light)
{
	if(light > 40 && light < 70)
		printk("Light off.\n");
	else
		printk("Light on.\n");
}
void blinds_driver(int light)
{
	if(light > 40 && light < 70)
		printk("Blinds open.\n");
	else
		printk("Blinds close.\n");
}

void main(void)
{
	printk("Szmart home switch on...\n");
	if(init() != 0)
	{
		printk("Error occured.\nSwitch off.\n");
		return;
	}

	int lumens = 0;

	for(;;)
	{
		k_msleep(SLEEP_TIME_MS);
		lumens = sensor_get_value();
		printk("Light outside: %d\n", lumens);
		blinds_driver(lumens);
		internal_light(lumens);
		printk("*************************\n\n");
	}
}