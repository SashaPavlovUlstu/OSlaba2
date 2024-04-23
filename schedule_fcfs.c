#include "schedulers.h"
#include "list.h"
#include <stdlib.h>
#include "cpu.h"

struct node* tasks = NULL;

// Декларация глобальной переменной tasks, которая является указателем на первый элемент списка задач

void add(Task* task) {
    insert(&tasks, task);
}

// Определение функции add(), которая добавляет новую задачу в список tasks при помощи функции insert() из модуля list.h

Task* selected_task = NULL;

Task* pick_next_task() {
    if (selected_task != NULL) {
        delete(&tasks, selected_task);
    }
    if (tasks == NULL) {
        return NULL;
    }
    return tasks->task;
}

// Определение функции pick_next_task(), которая выбирает следующую задачу для выполнения из списка tasks, удаляя предыдущую выбранную задачу, если она есть

void schedule() {
    selected_task = pick_next_task();
    while (selected_task != NULL) {
        run(selected_task, selected_task->burst);
        selected_task = pick_next_task();
    }
}

// Определение функции schedule(), которая реализует основной цикл работы планировщика: выбор следующей задачи,
// выполнение задачи через функцию run(), и повторение этого до тех пор, пока есть активные задачи
