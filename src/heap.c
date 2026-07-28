/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azebahad <azebahad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 22:24:41 by azebahad          #+#    #+#             */
/*   Updated: 2026/07/28 23:14:12 by azebahad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codixion.h"

static void heap_swap(t_request *c1, t_request *c2)
{
    t_request temp;

    temp = *c1;
    *c1 = *c2;
    *c2 = temp;
}

static int request_has_higher_priority(t_request *f, t_request *s, char *scheduler)
{
    if (strcmp(scheduler, "edf") == 0)
        return (f->deadline < s->deadline);
    return (f->timestamp < s->timestamp);
}

int heap_push(t_heap *heap, t_request req, char *scheduler)
{
    int current;
    
    if (heap->size == heap->capacity)
        return 0;
    
    heap->data[heap->size] = req;
    current = heap->size;
    while (current > 0)
    {
        parent = (current - 1) / 2;

        if (!request_has_higher_priority(
                &heap->data[current],
                &heap->data[parent],
                scheduler))
            break;

        heap_swap(&heap->data[current], &heap->data[parent]);
        current = parent;
    }
    heap->size++;
    
}


