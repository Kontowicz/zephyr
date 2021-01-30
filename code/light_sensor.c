#include "light_sensor.h"

#define I2C_ADDR 0x40
#define I2C_MODE 0xe5

static const struct device *light_sensor;

int light_sensor_init()
{
    light_sensor =  device_get_binding("I2C_1");
    if(NULL == light_sensor)
    {
        printk("\n\nERROR: light sensor\n\n");
        return 1;
    }
    return 0;
}

int sensor_get_value()
{
    int value = 0;
    uint8_t data[2];

    if(NULL == i2c_burst_read(light_sensor, I2C_ADDR, I2C_MODE, data, sizeof(data)))
    {
        value = ((125 * ((data[0] * 256) + data[1])) / 65536) - 5;
    } 
    else
    {
        printk("\n\nERROR: light sens cant read\n\n");
        value = -1;
    }
    return value;
}