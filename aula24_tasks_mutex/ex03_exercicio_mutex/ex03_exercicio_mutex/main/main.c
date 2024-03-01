#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

// Variável global para contagem
int8_t global_count = 0;

// Variável mutex
SemaphoreHandle_t mutex_counter;

// Implementação da task 1
void task_sum(void *params)
{
    while(1)
    {
        if(xSemaphoreTake(mutex_counter,1000/portTICK_PERIOD_MS))
        {
            global_count++;
            printf("contagem soma: %d\n",global_count);
            xSemaphoreGive(mutex_counter);
        }
            vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void task_sub(void *params)
{
    while(1)
    {
        if(xSemaphoreTake(mutex_counter,1000/portTICK_PERIOD_MS))
        {
            global_count--;
            printf("contagem subtracao: %d\n",global_count);
            xSemaphoreGive(mutex_counter);
        }
        vTaskDelay(3000/portTICK_PERIOD_MS);
    }
}


void app_main(void)
{
    mutex_counter = xSemaphoreCreateMutex();
    xTaskCreate(&task_sum,"TASK SOMA",2048,NULL,1,NULL);
    xTaskCreate(&task_sub,"TASK SUB",2048,NULL,1,NULL);

}
