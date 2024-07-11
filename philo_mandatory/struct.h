/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:30:39 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/11 23:19:48 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo_thread t_philo_thread;
typedef struct s_data t_data;

typedef unsigned char		t_bool; // ?

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
	// pthread_mutex_t mtx_time;

	pthread_mutex_t *forks;
	unsigned long	start;
	t_bool			one_dead;
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
	
	t_bool			*one_dead;
	t_bool			is_full;
};

unsigned long	get_time_millisec(void);
unsigned long	get_timestamp_millisec(unsigned long start_milli);
void	print_philo(pthread_mutex_t *mtx_print, int n, long long start, char *str);
void	init_mutex(t_data *data);

#endif
