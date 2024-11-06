/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_essentials.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsambing <rsambing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 22:14:18 by reinaldo-sa       #+#    #+#             */
/*   Updated: 2024/09/24 13:38:49 by rsambing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	create_threads(int ac, char **av, t_lista *l)
{
	t_lista	*aux;

	(void) ac;
	(void) av;
	pthread_create(&l->philo, NULL, routine, (void *)l);
	aux = l->prox;
	while (aux != l)
	{
		pthread_create(&aux->philo, NULL, routine, (void *)aux);
		aux = aux->prox;
	}
}

void	join_threads(t_lista *l)
{
	t_lista	*aux;

	pthread_join(l->philo, NULL);
	aux = l->prox;
	while (aux != l)
	{
		pthread_join(aux->philo, NULL);
		aux = aux->prox;
	}
}

void	destroy_mutex(t_lista *l)
{
	t_lista	*aux;

	pthread_mutex_destroy(&l->fork);
	pthread_mutex_destroy(&l->to_sd);
	pthread_mutex_destroy(&l->to_ea);
	pthread_mutex_destroy(&l->to_ms);
	pthread_mutex_destroy(&l->to_ps);
	aux = l->prox;
	while (aux != l)
	{
		pthread_mutex_destroy(&aux->fork);
		pthread_mutex_destroy(&aux->to_sd);
		pthread_mutex_destroy(&aux->to_ea);
		pthread_mutex_destroy(&aux->to_ms);
		pthread_mutex_destroy(&aux->to_ps);
		aux = aux->prox;
	}
}
