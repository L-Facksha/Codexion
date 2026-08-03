/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azebahad <azebahad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 23:01:34 by azebahad          #+#    #+#             */
/*   Updated: 2026/08/03 17:01:42 by azebahad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../include/codixion.h"

static void	set_wait_timeout(struct timespec *timeout, long wait_ms)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	timeout->tv_sec = current.tv_sec + (wait_ms / 1000);
	timeout->tv_nsec = (current.tv_usec * 1000) + ((wait_ms % 1000) * 1000000);
	while (timeout->tv_nsec >= 1000000000)
	{
		timeout->tv_nsec -= 1000000000;
		timeout->tv_sec++;
	}
}

static long	get_request_deadline(t_coder *coder)
{
	long	now;

	now = get_time_ms() - coder->config->start_time;
	if (coder->last_compile_start >= 0)
		return (coder->last_compile_start + coder->config->time_to_burnout);
	return (now + coder->config->time_to_burnout);
}

static int	can_grant_dongle(t_coder *coder, t_dongle *dongle)
{
	long	now;

	if (dongle->taken)
		return (0);
	now = get_time_ms();
	if (dongle->last_released_at != 0
		&& (now - dongle->last_released_at) < coder->config->dongle_cooldown)
		return (0);
	return (heap_peek(&dongle->scheduler.pending).coder_id == coder->id);
}

static int	can_grant_pair(t_coder *coder, t_dongle *left, t_dongle *right)
{
	if (left->taken || right->taken)
		return (0);
	return (can_grant_dongle(coder, left) && can_grant_dongle(coder, right));
}

static int	push_coder_request(t_coder *coder, t_dongle *dongle)
{
	t_request	req;

	req.coder_id = coder->id;
	req.timestamp = get_time_ms() - coder->config->start_time;
	req.deadline = get_request_deadline(coder);
	pthread_mutex_lock(&dongle->mutex);
	if (!heap_push(&dongle->scheduler.pending, req, coder->config->scheduler))
	{
		pthread_mutex_unlock(&dongle->mutex);
		return (0);
	}
	pthread_cond_broadcast(&dongle->scheduler.cond);
	pthread_mutex_unlock(&dongle->mutex);
	return (1);
}

static void	remove_request(t_coder *coder, t_dongle *dongle)
{
	t_heap		*heap;
	int		index;
	int		parent;
	int		left_child;
	int		right_child;
	int		best_child;

	pthread_mutex_lock(&dongle->mutex);
	heap = &dongle->scheduler.pending;
	index = 0;
	while (index < heap->size)
	{
		if (heap->data[index].coder_id == coder->id)
			break ;
		index++;
	}
	if (index >= heap->size)
	{
		pthread_mutex_unlock(&dongle->mutex);
		return ;
	}
	heap->data[index] = heap->data[heap->size - 1];
	heap->size--;
	if (heap->size == 0)
	{
		pthread_cond_broadcast(&dongle->scheduler.cond);
		pthread_mutex_unlock(&dongle->mutex);
		return ;
	}
	if (index > 0)
	{
		parent = (index - 1) / 2;
		while (index > 0 && request_has_higher_priority(&heap->data[index],
				&heap->data[parent], coder->config->scheduler))
		{
			heap_swap(&heap->data[index], &heap->data[parent]);
			index = parent;
			parent = (index - 1) / 2;
		}
	}
	while (1)
	{
		left_child = (index * 2) + 1;
		right_child = left_child + 1;
		best_child = index;
		if (left_child < heap->size && request_has_higher_priority(
				&heap->data[left_child], &heap->data[best_child],
				coder->config->scheduler))
			best_child = left_child;
		if (right_child < heap->size && request_has_higher_priority(
				&heap->data[right_child], &heap->data[best_child],
				coder->config->scheduler))
			best_child = right_child;
		if (best_child == index)
			break ;
		heap_swap(&heap->data[index], &heap->data[best_child]);
		index = best_child;
	}
	pthread_cond_broadcast(&dongle->scheduler.cond);
	pthread_mutex_unlock(&dongle->mutex);
}

int	request_dongles(t_coder *coder, t_dongle *first, t_dongle *second)
{
	t_dongle	*left;
	t_dongle	*right;
	struct timespec	timeout;
	long		wait_ms;

	left = first;
	right = second;
	if (left->id > right->id)
	{
		left = second;
		right = first;
	}
	if (!push_coder_request(coder, left) || !push_coder_request(coder, right))
	{
		if (left->scheduler.pending.size > 0)
			remove_request(coder, left);
		if (right->scheduler.pending.size > 0)
			remove_request(coder, right);
		return (0);
	}
	while (!should_stop(coder->config))
	{
		pthread_mutex_lock(&left->mutex);
		pthread_mutex_lock(&right->mutex);
		if (can_grant_pair(coder, left, right))
		{
			left->taken = 1;
			right->taken = 1;
			heap_pop(&left->scheduler.pending, coder->config->scheduler);
			heap_pop(&right->scheduler.pending, coder->config->scheduler);
			pthread_cond_broadcast(&left->scheduler.cond);
			pthread_cond_broadcast(&right->scheduler.cond);
			pthread_mutex_unlock(&right->mutex);
			pthread_mutex_unlock(&left->mutex);
			print_status(coder, "has taken a dongle");
			print_status(coder, "has taken a dongle");
			return (1);
		}
		pthread_mutex_unlock(&right->mutex);
		pthread_mutex_unlock(&left->mutex);
		wait_ms = 1;
		if (left->last_released_at != 0)
		{
			wait_ms = (get_time_ms() - left->last_released_at)
				- coder->config->dongle_cooldown;
			if (wait_ms < 1)
				wait_ms = 1;
		}
		if (right->last_released_at != 0)
		{
			long right_wait = (get_time_ms() - right->last_released_at)
				- coder->config->dongle_cooldown;
			if (right_wait < wait_ms)
				wait_ms = right_wait < 1 ? 1 : right_wait;
		}
		set_wait_timeout(&timeout, wait_ms);
		pthread_mutex_lock(&left->mutex);
		pthread_cond_timedwait(&left->scheduler.cond, &left->mutex, &timeout);
		pthread_mutex_unlock(&left->mutex);
		pthread_mutex_lock(&right->mutex);
		pthread_cond_timedwait(&right->scheduler.cond, &right->mutex, &timeout);
		pthread_mutex_unlock(&right->mutex);
	}
	remove_request(coder, left);
	remove_request(coder, right);
	return (0);
}

void	release_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->taken = 0;
	dongle->last_released_at = get_time_ms();
	pthread_cond_broadcast(&dongle->scheduler.cond);
	pthread_mutex_unlock(&dongle->mutex);
}
