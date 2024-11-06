/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsambing <rsambing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:21:44 by rsambing          #+#    #+#             */
/*   Updated: 2024/09/24 13:38:25 by rsambing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	must_stop(t_lista *l)
{
	t_lista	*f;

	f = first_philo(l);
	pthread_mutex_lock(&f->to_ms);
	if (everyone_ate(l, NULL, NULL) == 1)
	{
		pthread_mutex_unlock(&f->to_ms);
		return (1);
	}
	if (someone_died(l) == 1)
	{
		pthread_mutex_unlock(&f->to_ms);
		return (1);
	}
	pthread_mutex_unlock(&f->to_ms);
	return (0);
}

static void	print_aux(t_lista *l, char msg)
{
	if (msg == 't')
		printf(AO "[%ld] philo %d is thinking\n" SC,
			time_from_start(l->start_time), l->id);
	else if (msg == 'f')
		printf(AO "[%ld] philo %d has taken a fork\n" SC,
			time_from_start(l->start_time), l->id);
	else if (msg == 'e')
		printf(VE "[%ld] philo %d is eating\n" SC,
			time_from_start(l->start_time), l->id);
	else if (msg == 'd')
		printf(VA "[%ld] philo %d died\n" SC, time_from_start(l->start_time),
			l->id);
	else if (msg == 's')
		printf(AO "[%ld] philo %d is sleeping\n" SC,
			time_from_start(l->start_time), l->id);
}

t_lista	*print_status(t_lista *l, char msg)
{
	t_lista	*first;

	first = first_philo(l);
	pthread_mutex_lock(&first->to_ps);
	if (must_stop(l) == 1)
	{
		if (first->time_stop == 2)
		{
			pthread_mutex_unlock(&first->to_ps);
			return (l);
		}
		if (first->died == 2)
		{
			pthread_mutex_unlock(&first->to_ps);
			return (l);
		}
		print_aux(l, msg);
		first->time_stop = 2;
		first->died = 2;
		pthread_mutex_unlock(&first->to_ps);
		return (l);
	}
	print_aux(l, msg);
	pthread_mutex_unlock(&first->to_ps);
	return (l);
}
