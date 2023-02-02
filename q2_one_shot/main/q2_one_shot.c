/*Question 2: One Shot Timer*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

TaskHandle_t task1_handle, task2_handle, task3_handle;
TimerHandle_t one_shot_handle;

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

void timer_callback(TimerHandle_t one_shot_handle)
{
    printf("Timer Callback function: Timer triggered...\n");
}

void task3(void *data)
{   // Triggering timer from task 3
	while(1)
	{
		printf(" Task 3\n");

        one_shot_handle = xTimerCreate("One_Shot_Timer",pdMS_TO_TICKS(10000),pdFALSE, NULL, timer_callback);
        
        if(pdPASS == (xTimerStart(one_shot_handle,5000)))
        {
            printf("Timer Start command is successfull!!\n");
        }
        vTaskDelete(task3_handle);
    }
}

void app_main(void)
{
    BaseType_t res_1, res_2, res_3;
    
    res_1 = xTaskCreate(task1,"first task", 2048, NULL, 5, &task1_handle);
    if(res_1 == pdPASS)
    {
        printf("    Task 1 created successfully!!\n");
    }

    res_3 = xTaskCreate(task3,"third task", 2048, NULL, 7, &task3_handle);
    if(res_3 == pdPASS)
    {
        printf("    Task 3 created successfully!!\n");
    }

    res_2 = xTaskCreate(task2,"second task", 2048, NULL, 6, &task2_handle);
    if(res_2 == pdPASS)
    {
        printf("    Task 2 created successfully!!\n");
    }
}
