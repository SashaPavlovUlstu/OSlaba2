#include "schedulers.h"
#include "list.h"
#include "stdlib.h"
#include "cpu.h"
#include "sys/param.h"
#include "string.h"

// Включение заголовочных файлов для необходимых библиотек и пользовательских модулей

struct node* tasks = NULL;
struct node* first = NULL;

// Глобальные переменные tasks и first, представляющие список задач и указатель на первый элемент списка соответственно

void add(Task* task) {
    insert(&tasks, task);
    if (first == NULL){
        first = tasks;
    }

    // Функция add(), добавляющая новую задачу в список tasks и устанавливающая начальный элемент списка, если первый раз добавляется задача
}

Task* pick_next() {
    struct node* pointer = tasks->prev;
    struct node* max_task_priority_node = tasks->task->burst ? tasks : tasks->next;

    // Определение функции pick_next(), которая выбирает следующую задачу для выполнения

    while (pointer && pointer != tasks) {
        if (pointer->task->burst != 0 && pointer->task->priority >= max_task_priority_node->task->priority) {
            max_task_priority_node = pointer;
        }
        pointer = pointer->prev;
    }

    // Поиск задачи с наивысшим приоритетом и с ненулевым временем выполнения

    if (tasks != tasks->next){
        if (tasks->task->burst == 0){
            tasks->prev->next = tasks->next;
            tasks->next->prev = tasks->prev;
        }
        tasks = max_task_priority_node;
        return tasks->task;
    }
    return NULL;
}

// Возвращение задачи с наивысшим приоритетом для выполнения

void schedule() {
    first->next = tasks;
    tasks->prev = first;

    // Функция schedule(), реализующая основной цикл выполнения задач

    while (pick_next() != NULL) {
        run(tasks->task, MIN(tasks->task->burst, TIME_QUANTUM));
        tasks->task->burst -= MIN(tasks->task->burst, TIME_QUANTUM);
    }

    // Пока есть задачи для выполнения, запуск их выполнения с учетом TIME_QUANTUM
}
