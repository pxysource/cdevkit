
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "priority_queue.h"

bool comparison(const pq_datatype_t *par, const pq_datatype_t *chi)
{
    // 父节点的值大于子节点
    return (*par > *chi) ? true : false;
}

// int test_capcity_overflow()
// {
//     priority_queue_t *pq = Priority_Queue_Init(5, comparison);
//     element_t arr[10] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };

//     for (int i = 0; i < 10; i++)
//     {
//         Priority_Queue_Push(pq, arr[i]);
//         printf("push: %d, top: %d\n", arr[i], Priority_Queue_Top(pq));
//     }

//     for (int i = 0; i < 10; i++)
//     {
//         printf("top: %d\n", Priority_Queue_Top(pq));
//         Priority_Queue_Pop(pq);
//     }

//     Priority_Queue_Destroy(pq);
//     return 0;
// }

int main()
{
    priority_queue_t pq;
    pq_datatype_t arr[20] = { 0 };
    pq_datatype_t node;
    int ret = 0;

    srand((unsigned int)time(NULL));

    printf("arr: {");
    for (size_t i = 0; i < 20; i++)
    {
        arr[i] = rand() % 100;
        printf(" %d,", arr[i]);
    }
    printf("\b }\n");

    pq_init(&pq, 30, comparison);

    for (int i = 0; i < (sizeof(arr) / sizeof(arr[0])); i++)
    {
        pq_enqueue(&pq, arr[i]);
        pq_get_head(&pq, &node);
        printf("push: %d, top: %d\n", arr[i], node);
    }

    while (!pq_empty(&pq))
    {
        ret = pq_dequeue(&pq, &node);
        if (ret)
        {
            fprintf(stderr, "Err: Dequeue error!\n");
            break;
        }

        printf("Head node: %d\n", node);
    }

    pq_destroy(&pq);

    return 0;
}