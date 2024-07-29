/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:30:39 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/18 22:11:22 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# include "parsing.h"

typedef struct s_philo		t_philo;
typedef struct s_data		t_data;
typedef unsigned char		t_bool;

typedef pthread_mutex_t		t_mutex;
typedef unsigned long		t_ulong;

# define TRUE 1
# define FALSE 0

# define THINK " is thinking"
# define EAT " is eating"
# define SLEEP " is sleeping"
# define FORK " has taken a fork"

# define ER_MTX_INIT "ERROR: pthread_mutex_init() failed\n"
# define ER_THREAD_CREATE "ERROR: pthread_create() failed\n"
# define ER_THREAD_JOIN "ERROR: pthread_join() failed\n"

struct s_data
{
	int				nbr_phi;
	unsigned long	t_death;
	unsigned long	t_eat;
	unsigned long	t_sleep;
	int				nbr_meals;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	mtx_death;
	pthread_mutex_t	mtx_time;
	pthread_mutex_t	mtx_bool;
	pthread_mutex_t	*forks;
	unsigned long	start;
	t_bool			one_dead;
	t_bool			meals_number;
};

struct s_philo
{
	int				phi_num;
	t_data			*data;
	pthread_t		thread_id;
	int				counter_meals_eaten;
	unsigned long	last_meal;
	unsigned long	start_meal;
	unsigned long	death;
	unsigned long	start_simu;
	t_bool			meals_are_limited;
	t_bool			*one_dead;
	t_bool			is_full;
	int				counter_meals;
};

// PHILO_DINER -------------------------------------------------------------
void	*philo_do(void *thread_philo_n);
void	*philo_is_dinning(t_philo *thrd, t_mutex *forks, int l, int r);
void	philo_take_forks(t_philo *thread, t_mutex *forks, int l, int r);

// PHILO_TIME --------------------------------------------------------------
t_ulong	get_time_millisec(void);
t_ulong	get_timestamp_millisec(unsigned long start_milli);
void	philo_is_sleeping_eating(t_philo *threads, t_ulong time_to_do);//new

// PHILO_DEATH --------------------------------------------------------------
t_bool	philo_time_dead(t_philo *thrd, int i);
void	philo_is_dead(t_philo *thread, int nbr_phi, int count, int i);

// PHILO_UTILS --------------------------------------------------------------
int		error_free(t_data *data, t_philo *threads, char *str);
int		error_message(char *str);
void	print_philo(t_philo *thread, t_mutex *mtx, long long start, char *str);
void	philo_dead(t_philo *thread, t_mutex *mtx_print, long long start);
void	*philo_full(t_philo *thread, t_mutex *mtx_print, long long start);

// PHILO_GET_SET -------------------------------------------------------------
t_ulong	get_value_unlong(t_mutex *mtx, unsigned long *to_get);
t_bool	get_value_bool(t_mutex *mtx, t_bool *to_get);
void	set_value_bool(t_mutex *mtx, t_bool *to_modify, t_bool value);
void	set_value_unlong(t_mutex *mtx, t_ulong *to_modify, t_ulong value);

// PHILO_INIT ---------------------------------------------------------------
int		parse_and_init_data(t_data *data, int argc, char **argv);
void	init_philo(t_data *data, t_philo *threads);
int		init_mutex(t_data *data, t_philo *threads);
int		init_thread(t_data *data, t_philo *threads);

#endif
