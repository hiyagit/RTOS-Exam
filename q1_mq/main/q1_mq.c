#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

TaskHandle_t task1_handle, task2_handle, task3_handle, task4_handle, task5_handle; 
static int taskcore = 1;
QueueHandle_t mq_handle;

void task1(void *data)
{
    while(1)
    {
        printf(" Task 1\n");
        vTaskDelay(1000);
    }
    vTaskDelete(task1_handle);
}

void task2(void *data)
{
    while(1)
    {
        printf(" Task 2\n");
        vTaskDelay(2000);
    }
    vTaskDelete(task2_handle);
}

void task3(void *data)
{
    while(1)
    {
        printf(" Task 3\n");
        vTaskDelay(5000);
    }
    vTaskDelete(task3_handle);
}

void task4(void *data)
{
    int int_data = 100;
    printf(" Task 4\n");
    while(1)
    {
        int_data++;
        xQueueSend(mq_handle,&int_data, pdMS_TO_TICKS(5000));
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(task4_handle);
}

void task5(void *data)
{
    int buf = 0;
    int count = 0;
    printf(" Task 5\n");
    while(1)
    {
        xQueueReceive(mq_handle, &buf, pdMS_TO_TICKS(5000));
        printf("Task 5: Received data: %d\n", buf);
        count++;
        if(count>5)
        {
            count = 0;
            vTaskDelay(pdMS_TO_TICKS(5000));
        }
    }
    vTaskDelete(task5_handle);
}

void app_main(void)
{
    BaseType_t res_1, res_2, res_3, res_4, res_5;

    mq_handle = xQueueCreate(4, 64);

    res_1 = xTaskCreatePinnedToCore(task1,"first task", 2048, NULL, 5, &task1_handle, taskcore);
    if(res_1 == pdPASS)
    {
        printf("    Task 1 created successfully!!\n");
    }

    res_2 = xTaskCreatePinnedToCore(task2,"second task", 2048, NULL, 6, &task2_handle, taskcore);
    if(res_2 == pdPASS)
    {
        printf("    Task 2 created successfully!!\n");
    }

    res_3 = xTaskCreatePinnedToCore(task3,"third task", 2048, NULL, 7, &task3_handle, taskcore);
    if(res_3 == pdPASS)
    {
        printf("    Task 3 created successfully!!\n");
    }

    res_4 = xTaskCreatePinnedToCore(task4,"fourth task", 2048, NULL, 8, &task4_handle, taskcore);
    if(res_4 == pdPASS)
    {
        printf("    Task 4 created successfully!!\n");
    }

    res_5 = xTaskCreatePinnedToCore(task5,"fifth task", 2048, NULL, 9, &task5_handle, taskcore);
    if(res_5 == pdPASS)
    {
        printf("    Task 5 created successfully!!\n");
    }
}
