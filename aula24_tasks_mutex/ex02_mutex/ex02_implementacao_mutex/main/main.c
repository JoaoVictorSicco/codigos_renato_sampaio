#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

float temperatura;
#define DELAY (1000/portTICK_PERIOD_MS)

// Criação do mutex
SemaphoreHandle_t mutexi2c;

//Função acessa um recurso i2c
float acessa_i2c(int comando)
{
    if(comando==1)
    {
        ESP_LOGI("I2C","Leitura do sensor de temperatura\n");
        return 20.0 + ((float) rand()/(float)(RAND_MAX/10));
    }

    else
    {
        ESP_LOGI("I2C","Leitura do sensor de temperatura\n");
        printf("Tela LCD - Temperatura: %f\n",temperatura);
    }
    return 0;
}

// Criação da task 1

void le_sensor(void *params)
{
    while (1)
    {
        if(xSemaphoreTake(mutexi2c,DELAY))
        {
            temperatura = acessa_i2c(1);
            ESP_LOGI("Leitura", "Temperatura: %f\n", temperatura);
            xSemaphoreGive(mutexi2c);
        }
        else
        {
            ESP_LOGE("Leitura", "Não foi possível ler o sensor");
        }
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

// Criação da task 2
void lcd_display(void *params)
{
    while (1)
    {
        if(xSemaphoreTake(mutexi2c,DELAY))
        {
            ESP_LOGI("Display","Escreve no LCD");
            acessa_i2c(2);
            xSemaphoreGive(mutexi2c);
        }
        else
        {
            ESP_LOGE("Display", "Não foi possível escrever no display");
        }
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}


void app_main(void)
{
    mutexi2c = xSemaphoreCreateMutex();
    xTaskCreate(&le_sensor,"Leitura Sensor 1", 2048, NULL, 2, NULL);
    xTaskCreate(&lcd_display,"Atualização do display", 2048, NULL, 2, NULL); 
}
