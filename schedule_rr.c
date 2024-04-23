#include "schedulers.h"
#include "list.h"
#include "stdlib.h"
#include "cpu.h"
#include "sys/param.h"

// Включение заголовочных файлов для необходимых библиотек и пользовательских модулей

struct node* tasks = NULL;
struct node* first = NULL;

// Объявление глобальных переменных tasks и first, представляющих список задач и указатель на первый элемент списка соответственно

void add(Task* task) {
    insert(&tasks, task);
    if (first == NULL){
        first = tasks;
    }

    // Функция add(), добавляющая новую задачу в список tasks и устанавливающая начальный элемент списка, если первая задача добавляется
}

Task* pick_next() {
    if (tasks != tasks->next){
        if (tasks->task->burst == 0){
            tasks->prev->next = tasks->next;
            tasks->next->prev = tasks->prev;
        }
        tasks = tasks->next;
        return tasks->task;
    }
    return NULL;

    // Функция pick_next(), выбирающая следующую задачу для выполнения и обновляющая указатель на текущую задачу
}

void schedule() {
    first->next = tasks;
    tasks->prev = first;
    tasks = first;

    // Функция schedule(), устанавливающая начальное состояние списка задач и начинающая основной цикл выполнения задач

    while (pick_next() != NULL) {
        run(tasks->task, MIN(tasks->task->burst, TIME_QUANTUM));
        tasks->task->burst -= MIN(tasks->task->burst, TIME_QUANTUM);
    }

    // Пока есть задачи для выполнения, запускает выполнение задач с учетом TIME_QUANTUM
}
