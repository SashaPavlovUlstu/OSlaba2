/**
 * Driver.c
 *
 * Schedule is in the format
 *
 *  [name] [priority] [CPU burst]
 */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"

#define SIZE 10000

int main(int argc, char *argv[]) {
    FILE *in;
    char *temp;
    char task[SIZE];

    char *name;
    int priority;
    int burst;

    // Определение переменных и открытие файла входных данных

    in = fopen(argv[1], "r");

    Task* tasks_array[MAX_TASKS];
    int tasks_count = 0;
    struct node* temp_list;

    // Создание массива задач, чтение данных из файла и заполнение списка задач

    while (fgets(task, SIZE, in) != NULL) {
        temp = strdup(task);
        name = strsep(&temp, ",");
        priority = atoi(strsep(&temp, ","));
        burst = atoi(strsep(&temp, ","));

        // Добавление задачи в список задач в памяти и в массив задач

        add_task(&temp_list, name, priority, burst);
        tasks_array[tasks_count] = temp_list->task;
        tasks_count++;

        free(temp);
    }

    // Перенос задач из временного списка в основной список задач

    while (temp_list != NULL) {
        add(temp_list->task);
        delete(&temp_list, temp_list->task);
    }

    fclose(in);

    // Вызов функции планировщика для запуска выполнения задач

    schedule();

    // Вычисление и вывод средних показателей времени выполнения задач

    float average_turnaround_time = 0;
    float average_wait_time = 0;
    float average_response_time = 0;
    for (int x = 0; x < tasks_count; x++) {
        average_turnaround_time += tasks_array[x]->time_end - tasks_array[x]->time_start;
        average_wait_time += tasks_array[x]->wait_time;
        average_response_time += tasks_array[x]->time_start;
    }
    average_turnaround_time /= tasks_count;
    average_wait_time /= tasks_count;
    average_response_time /= tasks_count;

    printf("\nAverage turnaround time: %f", average_turnaround_time);
    printf("\nAverage wait time: %f", average_wait_time);
    printf("\nAverage response time: %f\n", average_response_time);

    return 0;
}
