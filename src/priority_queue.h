/**
 * @file priority_queue.h
 * @author panxingyuan (panxingyuan1@163.com)
 * @brief Priority queue.
 * @version 0.1
 * @date 2025-01-18
 *       Create this file.
 * @copyright Copyright (c) 2025
 * @note Encoding: "utf-8".
 */

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdint.h>
#include <stdbool.h>

#include "stdafx.h"

typedef int pq_datatype_t;
typedef bool (*pq_equal_t)(const pq_datatype_t *, const pq_datatype_t *);

typedef struct {
    pq_equal_t equal;       /** 比较函数 */
    pq_datatype_t *eles;  /** 元素存储地址 */
    uint32_t capacity;
    uint32_t size;
} priority_queue_t;

CDEVKIT_DECLS_BEGIN

/**
 * @brief 获取队首元素
 *
 * @param[in] queue
 * @param[out] node
 * @return 0 - 成功，非0 - 失败。
 * @retval -EINVAL 参数错误。
 * @retval -ENODATA 队列为空。
 */
int CDEVKIT_EXPORT pq_get_head(priority_queue_t *queue, pq_datatype_t *node);

/**
 * @brief Enqueue
 *
 * @param[in,out] queue
 * @param val 插入队列的新元素
 * @return 0 - 成功，非0 - 失败。
 * @retval -EINVAL 参数错误。
 * @retval -ENOMEM 队列已满。
 */
int CDEVKIT_EXPORT pq_enqueue(priority_queue_t *queue, pq_datatype_t val);

/**
 * @brief Dequeue
 *
 * @param[in,out] queue
 * @param[out] node
 * @return 0 - 成功，非0 - 失败。
 * @retval -EINVAL 参数错误。
 * @retval -ENODATA 队列为空。
 */
int CDEVKIT_EXPORT pq_dequeue(priority_queue_t *queue, pq_datatype_t *node);

/**
 * @brief Init
 *
 * @param[out] queue
 * @param[in] capacity
 * @param[in] func 节点比较函数。
 * @return 0 - 成功，非0 - 失败。
 * @retval -EINVAL queue为NULL。
 * @retval -ENOMEM 分配内存失败。
 */
int CDEVKIT_EXPORT pq_init(priority_queue_t *queue, uint32_t capacity, pq_equal_t func);

/**
 * @brief Destroy
 *
 * @param[in,out] queue
 */
void CDEVKIT_EXPORT pq_destroy(priority_queue_t *queue);

/**
 * @brief clear
 *
 * @param[in,out] queue
 */
void CDEVKIT_EXPORT pq_clear(priority_queue_t *queue);

/**
 * @brief 队列是否为为空
 *
 * @param[in] queue
 * @retval -EINVAL 参数错误。
 * @retval 0 - 队列不为空。
 * @retval 1 - 队列为空。
 */
bool CDEVKIT_EXPORT pq_empty(priority_queue_t *queue);

CDEVKIT_DECLS_END

#endif  // PRIORITY_QUEUE_H