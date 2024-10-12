#include <stdio.h>

#include "driver/i2c.h"
#include "i2c_bus.h"
#include "sht3x.h"

#define I2C_MASTER_SCL_IO       GPIO_NUM_10  /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO       GPIO_NUM_11  /*!< gpio number for I2C master data */
#define I2C_MASTER_NUM          I2C_NUM_1    /*!< I2C port number for master dev */
#define I2C_MASTER_FREQ_HZ      100000

static i2c_bus_handle_t i2c_bus = NULL;
static sht3x_handle_t sht3x = NULL;

void app_main(void)
{
    i2c_config_t conf =
    {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_bus = i2c_bus_create(I2C_MASTER_NUM, &conf);
    sht3x = sht3x_create(i2c_bus, SHT3x_ADDR_PIN_SELECT_VSS);

    sht3x_set_measure_mode(sht3x, SHT3x_PER_2_MEDIUM);

    vTaskDelay(1000 / portTICK_RATE_MS);
    
    float Tem_val, Hum_val;
    for(;;)
    {
        if(sht3x_get_humiture(sht3x, &Tem_val, &Hum_val) == 0)
        {
            printf("temperature %.2fºC   ", Tem_val);
            printf("humidity: %.2f %%\n", Hum_val);
        }
        vTaskDelay(1000 / portTICK_RATE_MS);
    }

}