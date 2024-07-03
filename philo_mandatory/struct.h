/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:30:39 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/03 16:49:56 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo_thread t_philo_thread;
typedef struct s_data t_data;

struct s_data{
	int nbr_phi;
	int t_death;
	int t_eat;
	int t_sleep;
	int nbr_meals;
	pthread_mutex_t mtx_print;
	pthread_mutex_t *forks;
	unsigned long	start;
};

struct s_philo_thread{
	int				phi_num;
	t_data			*data;
	pthread_t		thread_id;
	int 			counter_meals_eaten;
	unsigned long	last_meal;
	unsigned long	start_meal;
};

unsigned long	get_time_millisec(void);
unsigned long	get_timestamp_millisec(unsigned long start_milli);
void	print_philo(pthread_mutex_t *mtx_print, int n, long long start, char *str);
void	init_mutex(t_data *data);
