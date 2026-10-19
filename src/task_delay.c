#include <stdio.h>
#include <pico/stdlib.h>
#include <FreeRTOS.h>
#include <task.h>

uint OUT_PIN = 22;
uint DELAY_MS = 100;
uint volatile busy_count;

void main_task(__unused void *params)
{
    int toggle = 0;
    while (1) {
        busy_count = 0;
        toggle = !toggle;
        gpio_put(OUT_PIN, toggle);
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
        while(busy_count < 1000000)
        {
            busy_count ++;
        }
    }
}

int main(void)
{
    stdio_init_all();
    gpio_init(OUT_PIN);
    gpio_set_dir(OUT_PIN, GPIO_OUT);
    const char *rtos_name = "FreeRTOS";
    TaskHandle_t task;
    xTaskCreate(main_task, "MainThread",
                configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &task);
    vTaskStartScheduler();
    return 0;
}
