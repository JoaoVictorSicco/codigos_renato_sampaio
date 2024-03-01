/*  Aula 25 - Introdução ao FreeRTOS do canal Renato Sampaio
    Exemplo 01 - Semáforo Binario

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

//Criação do semáforo binário
SemaphoreHandle_t semaforoBinario; // A criação do semáforo varia conforme a versão

// Criação da função que conecta com o servidor
void conexao_servidor(void *params)
{
    while(1)
    {
        ESP_LOGI("Servidor","Conectando ao servidor");
        xSemaphoreGive(semaforoBinario);
        vtaskDelay(2000/portTICK_PERIOD_MS);
    }
}

// Criação da função que processa os dados recebidos
void processa_dados(void *params)
{
    while(1)
    {   
        xSemaphoreTake(semaforoBinario,portMAX_DELAY);
        printf("Pagina carregada!\n");
    }
}


void app_main(void)
{
    xTaskcreate(&conexao_servidor,"Conexao com o servidor", 2048, NULL, 1, NULL);
    xTaskcreate(&processa_dados,"Processa dados", 2048, NULL, 1, NULL);

}
