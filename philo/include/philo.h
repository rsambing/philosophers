/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsambing <rsambing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:08:02 by reinaldo-sa       #+#    #+#             */
/*   Updated: 2024/09/24 12:24:26 by rsambing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define P "\033[1;30m"
# define VA "\033[1;31m"
# define VE "\033[1;32m"
# define AO "\033[1;33m"
# define AL "\033[1;34m"
# define M "\033[1;35m"
# define C "\033[1;36m"
# define B "\033[1;37m"
# define SC "\033[0m"

typedef struct s_lista
{
	int				id;
	pthread_mutex_t	fork;
	pthread_mutex_t	to_ms;
	pthread_mutex_t	to_sd;
	pthread_mutex_t	to_ea;
	pthread_mutex_t	to_ps;
	pthread_t		philo;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	long int		times_each_philo_must_eat;
	long int		start_time;
	long int		last_meal;
	int				time_stop;
	int				eating;
	int				died;
	struct s_lista	*ant;
	struct s_lista	*prox;
}					t_lista;

int					ft_isdigit(int c);
int					verify_args(int ac, char **av);
int					someone_died(t_lista *l);
int					everyone_ate(t_lista *l, t_lista *aux, t_lista *f);
int					must_stop(t_lista *l);

long int			ft_atoi_besta(const char *nptr);
long int			current_time(void);
long int			time_from_start(long int start_time);

t_lista				*create_list(void);
t_lista				*insert(t_lista *l, int id, t_lista *aux);
t_lista				*delete_list(t_lista *l);
t_lista				*initialize(int ac, char **av, t_lista *l);
t_lista				*initialize_one(int ac, char **av, t_lista *info);
t_lista				*initialize_info(int ac, char **av, t_lista *info);
t_lista				*initial_loop(int ac, char **av, t_lista *l);
t_lista				*eat(t_lista *l);
t_lista				*first_philo(t_lista *l);
t_lista				*print_status(t_lista *l, char msg);

void				create_threads(int ac, char **av, t_lista *l);
void				join_threads(t_lista *l);
void				destroy_mutex(t_lista *l);
void				*routine(void *arg);
void				*only_one(void *arg);

#endif
