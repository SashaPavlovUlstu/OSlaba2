#include "schedulers.h"
#include "list.h"
#include "stdlib.h"
#include "cpu.h"

// Включение заголовочных файлов для необходимых библиотек и пользовательских модулей

struct node* tasks = NULL;

// Глобальная переменная tasks, представляющая список задач, инициализированная как пустой

void add(Task* task) {
    insert(&tasks, task);
}

// Определение функции add(), которая добавляет новую задачу в список tasks

Task* selected_task = NULL;

Task* pick_next_task() {
    if (selected_task != NULL) {
        delete(&tasks, selected_task);
    }
    if (tasks == NULL) {
        return NULL;
    }

    struct node* pointer = tasks->next;
    Task* max_task_priority = tasks->task;

    // Объявление локальных переменных для перебора списка задач и для хранения задачи с наивысшим приоритетом

    while (pointer != NULL) {
        if (pointer->task->priority > max_task_priority->priority) {
            max_task_priority = pointer->task;
        }
        pointer = pointer->next;
    }

    // Поиск задачи с наивысшим приоритетом в списке задач

    return max_task_priority;
}

// Определение функции pick_next_task(), которая выбирает задачу с наивысшим приоритетом из списка

void schedule() {
    selected_task = pick_next_task();
    while (selected_task != NULL){
        run(selected_task, selected_task->burst);
        selected_task = pick_next_task();
    }
}

// Определение функции schedule(), которая реализует основной цикл работы планировщика: выбор задачи с наивысшим приоритетом, выполнение данной задачи и выбор следующей задачи с наивысшим приоритетом до окончания списка задач
