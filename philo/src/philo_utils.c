/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsambing <rsambing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:22:13 by rsambing          #+#    #+#             */
/*   Updated: 2024/09/24 13:38:53 by rsambing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long int	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	someone_died(t_lista *l)
{
	t_lista	*aux;
	t_lista	*first;

	first = first_philo(l);
	pthread_mutex_lock(&first->to_sd);
	if (l->died != 0)
	{
		pthread_mutex_unlock(&first->to_sd);
		return (1);
	}
	aux = l->prox;
	while (aux != l)
	{
		if (aux->died != 0)
		{
			pthread_mutex_unlock(&first->to_sd);
			return (1);
		}
		aux = aux->prox;
	}
	pthread_mutex_unlock(&first->to_sd);
	return (0);
}

int	everyone_ate(t_lista *l, t_lista *aux, t_lista *f)
{
	f = first_philo(l);
	pthread_mutex_lock(&f->to_ea);
	if (l->times_each_philo_must_eat == -1)
	{
		pthread_mutex_unlock(&f->to_ea);
		return (0);
	}
	if (l->times_each_philo_must_eat > 0)
	{
		pthread_mutex_unlock(&f->to_ea);
		return (0);
	}
	aux = l->prox;
	while (aux != l)
	{
		if (aux->times_each_philo_must_eat > 0)
		{
			pthread_mutex_unlock(&f->to_ea);
			return (0);
		}
		aux = aux->prox;
	}
	pthread_mutex_unlock(&f->to_ea);
	return (1);
}

long int	time_from_start(long int start_time)
{
	return (current_time() - start_time);
}

t_lista	*first_philo(t_lista *l)
{
	t_lista	*aux;

	aux = l->prox;
	if (l->id == 1)
		return (l);
	while (aux != l)
	{
		if (aux->id == 1)
			return (aux);
		aux = aux->prox;
	}
	return (NULL);
}
