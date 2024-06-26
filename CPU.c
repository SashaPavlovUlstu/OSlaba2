/**
 * "Virtual" CPU that also maintains track of system time.
 */

#include <stdio.h>

#include "task.h"

int time = 0;

// Объявление переменной time для отслеживания системного времени

// Запуск задачи на выполнение с заданным временным срезом
void run(Task *task, int slice) {
    if (task->time_start == -1) task->time_start = time;
    if (task->burst - slice <= 0) task->time_end = time + slice;
    task->wait_time += time - task->last_call_time;
    task->last_call_time = time;

    // Обновление информации о задаче и вывод сообщения о выполнении задачи

    printf("Running task = [%s] [%d] [%d] for %d units. Time start [%d], time end [%d].\n", task->name, task->priority, task->burst, slice, task->time_start, task->time_end);

    time += slice; // Увеличение времени на продолжительность выполнения задачи
}
