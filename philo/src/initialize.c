/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsambing <rsambing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:57:20 by reinaldo-sa       #+#    #+#             */
/*   Updated: 2024/09/24 13:38:35 by rsambing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	verify_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	if (ac != 5 && ac != 6)
		return (0);
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
			if (!ft_isdigit(av[i][j]) || ft_atoi_besta(av[i]) < 1)
				return (0);
	}
	return (1);
}

t_lista	*initialize(int ac, char **av, t_lista *l)
{
	long int	len;
	long int	i;

	if (!verify_args(ac, av))
	{
		printf(M "./philo n_philosophers time_to_die time_to_eat ");
		printf("time_to_sleep times_each_philosopher_must_eat\n" SC);
		return (NULL);
	}
	l = create_list();
	i = 0;
	len = ft_atoi_besta(av[1]);
	while (++i <= len)
		l = insert(l, i, NULL);
	if (!l)
	{
		printf("Erro ao inicializar lista\n");
		return (NULL);
	}
	return (l);
}

t_lista	*initialize_info(int ac, char **av, t_lista *info)
{
	info->time_to_die = ft_atoi_besta(av[2]);
	info->time_to_eat = ft_atoi_besta(av[3]) * 1000;
	info->time_to_sleep = ft_atoi_besta(av[4]) * 1000;
	if (ac == 6)
		info->times_each_philo_must_eat = ft_atoi_besta(av[5]);
	else
		info->times_each_philo_must_eat = -1;
	info->last_meal = 0;
	info->start_time = current_time();
	info->died = 0;
	info->time_stop = -1;
	info->eating = 0;
	pthread_mutex_init(&info->fork, NULL);
	pthread_mutex_init(&info->to_sd, NULL);
	pthread_mutex_init(&info->to_ea, NULL);
	pthread_mutex_init(&info->to_ms, NULL);
	pthread_mutex_init(&info->to_ps, NULL);
	return (info);
}

t_lista	*initial_loop(int ac, char **av, t_lista *l)
{
	t_lista	*aux;

	l = initialize_info(ac, av, l);
	aux = l->prox;
	while (aux != l)
	{
		aux = initialize_info(ac, av, aux);
		aux = aux->prox;
	}
	return (l);
}

t_lista	*initialize_one(int ac, char **av, t_lista *info)
{
	if (!verify_args(ac, av))
	{
		printf("./philo n_philosophers time_to_die time_to_eat \
		time_to_sleep times_each_philosopher_must_eat\n");
		return (NULL);
	}
	info->time_to_die = ft_atoi_besta(av[2]) * 1000;
	if (ac == 6)
		info->times_each_philo_must_eat = ft_atoi_besta(av[5]);
	else
		info->times_each_philo_must_eat = -1;
	info->last_meal = 0;
	info->start_time = current_time();
	info->died = 0;
	info->start_time = current_time();
	return (info);
}
