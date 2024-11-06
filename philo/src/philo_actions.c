/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsambing <rsambing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:03:29 by reinaldo-sa       #+#    #+#             */
/*   Updated: 2024/09/24 13:38:45 by rsambing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*only_one(void *arg)
{
	t_lista	*l;

	l = (t_lista *)arg;
	l = print_status(l, 't');
	l = print_status(l, 'f');
	usleep(l->time_to_die);
	l = print_status(l, 'd');
	return (NULL);
}

static void	smart_sleep(t_lista *l, long int sleep_time)
{
	long int	start_time;
	t_lista		*f;

	f = first_philo(l);
	start_time = current_time();
	while (time_from_start(start_time) < sleep_time / 1000 && !must_stop(l))
	{
		if (time_from_start(l->start_time) - l->last_meal > l->time_to_die
			&& l->eating)
		{
			pthread_mutex_lock(&f->to_sd);
			l->died = 1;
			pthread_mutex_unlock(&f->to_sd);
			l = print_status(l, 'd');
			return ;
		}
		if (must_stop(l))
			return ;
		usleep(100);
	}
}

t_lista	*eat(t_lista *l)
{
	t_lista	*f;

	f = first_philo(l);
	{
		print_status(l, 'e');
		l->eating = 1;
		smart_sleep(l, l->time_to_eat);
		l->eating = 0;
		if (!must_stop(l))
		{
			l->last_meal = time_from_start(l->start_time);
			if (l->times_each_philo_must_eat > 0)
			{
				pthread_mutex_lock(&f->to_ea);
				l->times_each_philo_must_eat--;
				pthread_mutex_unlock(&f->to_ea);
			}
		}
	}
	return (l);
}

static t_lista	*lock_mutexes(t_lista *l)
{
	l = print_status(l, 't');
	if (l->id % 2 != 0)
		usleep(100);
	if (l->id < l->prox->id)
	{
		pthread_mutex_lock(&l->fork);
		pthread_mutex_lock(&l->prox->fork);
	}
	else
	{
		pthread_mutex_lock(&l->prox->fork);
		pthread_mutex_lock(&l->fork);
	}
	return (l);
}

void	*routine(void *arg)
{
	t_lista	*l;
	t_lista	*f;

	l = (t_lista *)arg;
	f = first_philo(l);
	l->start_time = current_time();
	while (must_stop(l) != 1)
	{
		l = lock_mutexes(l);
		l = print_status(l, 'f');
		if (time_from_start(l->start_time) - l->last_meal > l->time_to_die)
		{
			pthread_mutex_lock(&f->to_sd);
			l->died = 1;
			pthread_mutex_unlock(&f->to_sd);
			print_status(l, 'd');
		}
		l = eat(l);
		pthread_mutex_unlock(&l->prox->fork);
		pthread_mutex_unlock(&l->fork);
		if (must_stop(l) != 1)
			l = print_status(l, 's');
		smart_sleep(l, l->time_to_sleep);
	}
	return (NULL);
}
