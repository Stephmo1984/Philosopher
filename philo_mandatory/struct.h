/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:30:39 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/15 18:03:52 by smortemo         ###   ########.fr       */
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

typedef struct s_philo_thread t_philo_thread;
typedef struct s_data t_data;

typedef unsigned char		t_bool;

# ifndef TRUE
#  define TRUE 1
# endif
# ifndef FALSE
#  define FALSE 0
#endif

struct s_data{
	int nbr_phi;
	unsigned long t_death;
	unsigned long t_eat;
	unsigned long t_sleep;
	int nbr_meals;
	pthread_mutex_t mtx_print;
	pthread_mutex_t mtx_death;
	pthread_mutex_t mtx_time;
	pthread_mutex_t mtx_bool;
	pthread_mutex_t *forks;
	unsigned long	start;
	t_bool			one_dead;
	t_bool			meals_number;
};

struct s_philo_thread{
	int				phi_num;
	t_data			*data;
	pthread_t		thread_id;
	int 			counter_meals_eaten;
	unsigned long	last_meal;
	unsigned long	start_meal;
	unsigned long 	death;
	unsigned long	start_simu;
	t_bool			meals_are_limited;
	t_bool			*one_dead;
	t_bool			is_full;
	int 			counter_meals;
};

// MAIN
void	*philo_do(void *thread_philo_n);


// PHILO_TIME --------------------------------------------------------------
unsigned long	get_time_millisec(void);
unsigned long	get_timestamp_millisec(unsigned long start_milli);

// PHILO_UTILS --------------------------------------------------------------
void			exit_error_message(char *str);
void			print_philo(t_philo_thread *thread, pthread_mutex_t *mtx_print, long long start, char *str);
void			philo_dead(t_philo_thread *thread, pthread_mutex_t *mtx_print, long long start);
void			*philo_full(t_philo_thread *thread, pthread_mutex_t *mtx_print, long long start);

// PHILO_GET_SET -------------------------------------------------------------
unsigned long	get_value_startmeal_unlong(t_philo_thread *thread, pthread_mutex_t *mtx);
void			set_value_startmeal_unlong(t_philo_thread *thread, pthread_mutex_t *mtx, unsigned long value);
unsigned long	get_value_unlong(pthread_mutex_t *mtx, unsigned long *to_get);
t_bool			get_value_bool(pthread_mutex_t *mtx, t_bool *to_get);
void			set_value_bool(pthread_mutex_t *mtx, t_bool *to_modify, t_bool value);
void			set_value_unlong(pthread_mutex_t *mtx, unsigned long *to_modify, unsigned long value);

// PHILO_INIT ---------------------------------------------------------------
void 	init_data(t_data *data, char **argv);
void	init_philo(t_data *data, t_philo_thread *threads);
void	init_mutex(t_data *data);
void	init_thread(t_data *data, t_philo_thread *threads);


#endif
