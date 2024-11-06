/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsambing <rsambing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:07:32 by reinaldo-sa       #+#    #+#             */
/*   Updated: 2024/09/24 13:41:35 by rsambing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	extra_main(int ac, char **av)
{
	t_lista	*l;

	l = create_list();
	if (ft_atoi_besta(av[1]) == 1)
	{
		l = insert(l, 1, NULL);
		l = initialize_one(ac, av, l);
		if (!l)
			return (-1);
		l->start_time = current_time();
		pthread_create(&l->philo, NULL, only_one, (void *)l);
		pthread_join(l->philo, NULL);
	}
	else
	{
		l = initialize(ac, av, l);
		if (!l)
			return (-1);
		l = initial_loop(ac, av, l);
		create_threads(ac, av, l);
		join_threads(l);
		destroy_mutex(l);
	}
	l = delete_list(l);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf(M "./philo n_philosophers time_to_die time_to_eat ");
		printf("time_to_sleep times_each_philosopher_must_eat\n" SC);
		return (0);
	}
	extra_main(ac, av);
	return (0);
}
