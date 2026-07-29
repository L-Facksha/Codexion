/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azebahad <azebahad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 19:06:18 by azebahad          #+#    #+#             */
/*   Updated: 2026/07/29 19:06:22 by azebahad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	heap_swap(t_request *c1, t_request *c2)
{
	t_request	temp;

	temp = *c1;
	*c1 = *c2;
	*c2 = temp;
}

int	request_has_higher_priority(t_request *f, t_request *s, char *scheduler)
{
	if (strcmp(scheduler, "edf") == 0)
		return (f->deadline < s->deadline);
	return (f->timestamp < s->timestamp);
}