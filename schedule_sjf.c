#include "schedulers.h"
#include "list.h"
#include <stdlib.h>
#include "cpu.h"

// Включение заголовочных файлов для необходимых библиотек и пользовательских модулей

struct node* tasks = NULL;

// Объявление глобальной переменной tasks, представляющей список задач

void add(Task* task) {
    insert(&tasks, task);
}

// Функция add(), добавляющая задачу в список задач

Task* selected_task = NULL;

// Объявление глобальной переменной selected_task для хранения выбранной задачи

Task* pick_next_task() {
    if (selected_task != NULL) {
        delete(&tasks, selected_task);
    }

    // Функция pick_next_task(), выбирающая следующую задачу для выполнения

    if (tasks == NULL) {
        return NULL;
    }

    struct node* pointer = tasks->next;
    Task* min_task_burst = tasks->task;

    // Нахождение задачи с наименьшим временем выполнения

    while (pointer != NULL) {
        if (pointer->task->burst < min_task_burst->burst) {
            min_task_burst = pointer->task;
        }
        pointer = pointer->next;
    }

    return min_task_burst;
}

// Возврат задачи с наименьшим временем выполнения

void schedule() {
    selected_task = pick_next_task();
    while (selected_task != NULL) {
        run(selected_task, selected_task->burst);
        selected_task = pick_next_task();
    }
}

// Функция schedule(), осуществляющая запуск выбранных задач на выполнение
