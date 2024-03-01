#include <stdio.h>
#include <strings.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"


// Criação da task 1

void task1(void *params)
{
    while (1)
    {
        // printf("Leitura de sensores\n");
        ESP_LOGI("TASK1","Leitura de sensores");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    
}

// Criação da task2 
void task2(void *params)
{
    while (1)
    {
        // printf("Escrever no display\n");
        ESP_LOGI("TASK2","Escrever no display");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    
}

void app_main(void)
{
    xTaskCreate(&task1,"Leitura",2048,"Task 1",1,NULL);
    xTaskCreate(&task2,"Display",2048,"Task 2",1,NULL);

}
