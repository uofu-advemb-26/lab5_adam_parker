#include <stdio.h>
#include <pico/stdlib.h>

uint OUT_PIN = 22;
uint DELAY_MS = 100;
uint volatile busy_count;

// Measured Delay: 176 ms when 100 ms is expected.
int main(void)
{
    int toggle = 0;
    stdio_init_all();
    gpio_init(OUT_PIN);
    gpio_set_dir(OUT_PIN, GPIO_OUT);
    gpio_put(OUT_PIN, toggle);

    while (true) {
        busy_count = 0;
        toggle = !toggle;
        gpio_put(OUT_PIN, toggle);
        sleep_ms(DELAY_MS);
        while(busy_count < 1000000)
        {
            busy_count ++;
        }
    }
}
