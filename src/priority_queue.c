/**
 * @file priority_queue.c
 * @author panxingyuan (panxingyuan1@163.com)
 * @brief Priority queue.
 * @version 0.1
 * @date 2025-01-18
 *       Create this file.
 * @copyright Copyright (c) 2025
 * @note Encoding: "utf-8".
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "priority_queue.h"

static void swap(pq_datatype_t *a, pq_datatype_t *b)
{
    pq_datatype_t temp = *a;
    *a = *b;
    *b = temp;
}

int pq_get_head(priority_queue_t *queue, pq_datatype_t *node)
{
    if (!queue || !node)
    {
        return -EINVAL;
    }

    if (!queue->size)
    {
        return -ENODATA;
    }

    *node = queue->eles[0];

    return 0;
}

int pq_enqueue(priority_queue_t *queue, pq_datatype_t val)
{
    int new_node_idx = 0;
    int parent_node_idx = 0;

    if (!queue)
    {
        return -EINVAL;
    }

    if (queue->size >= queue->capacity)
    {
        return -ENOMEM;
    }

    new_node_idx = queue->size;
    // 计算父节点所在位置，整除为向下取整。
    parent_node_idx = (new_node_idx - 1) / 2;
    queue->eles[new_node_idx] = val;

    /*
     * 父节点存在，且父节点与子节点的值不满足要求时，交换它们的值。
     */
    while (new_node_idx && queue->equal(&queue->eles[parent_node_idx], &queue->eles[new_node_idx]) == false)
    {
        swap(&queue->eles[parent_node_idx], &queue->eles[new_node_idx]);
        // 计算新一轮的节点位置
        new_node_idx = parent_node_idx;
        parent_node_idx = (new_node_idx - 1) / 2;
    }

    queue->size++;

    return 0;
}

int pq_dequeue(priority_queue_t *pq, pq_datatype_t *node)
{
    if (!pq || !node)
    {
        return -EINVAL;
    }

    if (!pq->size)
    {
        return -ENODATA;
    }

    bool l_cond = false;
    bool r_cond = false;
    uint32_t pos = 0;
    uint32_t l_pos = 0;
    uint32_t r_pos = 0;

    // 入队的时候，最高优先级的节点已经排在队列的头部，直接取出即可。
    *node = pq->eles[0];

    // 判断是否有元素能够删除
    swap(&pq->eles[pos], &pq->eles[pq->size - 1]);
    // 删除元素
    pq->size--;

    while (pos < pq->size - 1)
    {
        l_pos = pos * 2 + 1;
        r_pos = pos * 2 + 2;

        // 子节点存在时判断数值是否满足要求
        l_cond = (l_pos < pq->size) ? pq->equal(&pq->eles[pos], &pq->eles[l_pos]) : true;
        r_cond = (r_pos < pq->size) ? pq->equal(&pq->eles[pos], &pq->eles[r_pos]) : true;

        if (l_cond && r_cond)
        {
            // 两个子节点均满足条件，退出循环
            break;
        }
        else if (!l_cond && r_cond)
        {
            // 只有左子节点不满足条件，与其交换数值。
            swap(&pq->eles[pos], &pq->eles[l_pos]);
            pos = l_pos;
        }
        else if (l_cond && !r_cond)
        {
            // 只有右子节点不满足条件，与其交换数值
            swap(&pq->eles[pos], &pq->eles[r_pos]);
            pos = r_pos;
        }
        else
        {
            // 两个子节点均不满足条件，挑选一个交换后数值仍满足要求的节点进行交换。
            if (pq->equal(&pq->eles[l_pos], &pq->eles[r_pos]))
            {
                swap(&pq->eles[pos], &pq->eles[l_pos]);
                pos = l_pos;
            }
            else
            {
                swap(&pq->eles[pos], &pq->eles[r_pos]);
                pos = r_pos;
            }
        }
    }

    return 0;
}

int pq_init(priority_queue_t *queue, uint32_t capacity, pq_equal_t func)
{
    if (!queue || !capacity || !func)
    {
        return -EINVAL;
    }

    queue->eles = (pq_datatype_t *)calloc(capacity, sizeof(pq_datatype_t));
    if (!queue->eles)
    {
        return -errno;
    }

    queue->capacity = capacity;
    queue->equal = func;
    queue->size = 0;

    return 0;
}

void pq_destroy(priority_queue_t *queue)
{
    if (!queue)
    {
        return;
    }

    if (queue->eles)
    {
        free(queue->eles);
        queue->eles = NULL;
    }

    queue->capacity = 0;
    queue->size = 0;
    queue->equal = NULL;
}

void pq_clear(priority_queue_t *queue)
{
    if (!queue)
    {
        return;
    }

    if (queue->eles && queue->capacity)
    {
        memset(queue->eles, 0, sizeof(pq_datatype_t) * queue->capacity);
    }

    queue->size = 0;
}

bool pq_empty(priority_queue_t *queue)
{
    if (!queue)
    {
        return true;
    }

    return !queue->size;
}