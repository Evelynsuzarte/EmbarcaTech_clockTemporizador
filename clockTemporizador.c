#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

const uint LED_VM = 11;
const uint LED_AM = 12;
const uint LED_VD = 13;

volatile int ativado = 0; 

bool ciclo_callback(repeating_timer_t *t);


int main()
{
    stdio_init_all();
    gpio_init(LED_VM);
    gpio_set_dir(LED_VM, GPIO_OUT);
    gpio_init(LED_AM);
    gpio_set_dir(LED_AM, GPIO_OUT);
    gpio_init(LED_VD);
    gpio_set_dir(LED_VD, GPIO_OUT);

    struct repeating_timer timer;
    add_repeating_timer_ms(3000, ciclo_callback, NULL, &timer);

    while (true) {
        printf("Semáfaro funcionando...\n");
        sleep_ms(1000);  
    }
}

//indica qual led acender
bool ciclo_callback(repeating_timer_t *t) {

    gpio_put(LED_VM, 0);
    gpio_put(LED_AM, 0);
    gpio_put(LED_VD, 0);

    switch (ativado) {
    case 0:
        gpio_put(LED_VM, 1);
        printf("LED VERMELHA\n");
        ativado = 1;
        break;
    case 1:
        gpio_put(LED_VM, 1);
        gpio_put(LED_VD, 1);
        printf("LED AMARELA\n");
        ativado = 2;    
        break;
    case 2:
        gpio_put(LED_VD, 1);
        printf("LED VERDE\n");
        ativado = 0;
        break;
    }
    return true;
}
