/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:30:39 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/14 14:17:04 by smortemo         ###   ########.fr       */
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

// PHILO_PARSING_01 ---------------------------------------------------------------
int len_num(long long num);
int len_str_num(char *str);
int	ft_atoi_philo(char *str);
long long	ft_atol_unsigned_philo(char *str);
void philo_check_args(char **argv);


// PHILO_PARSING_02 ---------------------------------------------------------------
size_t	ft_strlen(const char *str);
int	ft_isdigit(int c);
int	ft_is_sign(char sign, char c);
int	ft_isother(int c);
void	check_validity(char *str);


// MAIN
void	*philo_do(void *thread_philo_n);


// PHILO_UTILS --------------------------------------------------------------
void	exit_error_message(char *str);
unsigned long	get_time_millisec(void);
unsigned long	get_timestamp_millisec(unsigned long start_milli);
void	print_philo(t_philo_thread *thread, pthread_mutex_t *mtx_print, long long start, char *str);
void	philo_dead(t_philo_thread *thread, pthread_mutex_t *mtx_print, long long start);
void	*philo_full(t_philo_thread *thread, pthread_mutex_t *mtx_print, long long start);


// PHILO_GET_SET -------------------------------------------------------------
t_bool	get_value_onedead_bool(t_philo_thread *thread, pthread_mutex_t *mtx);
t_bool	get_value_isfull_bool(t_philo_thread *thread, pthread_mutex_t *mtx);
unsigned long	get_value_startmeal_unlong(t_philo_thread *thread, pthread_mutex_t *mtx);
void	set_value_onedead_bool(t_philo_thread *thread, pthread_mutex_t *mtx, t_bool value);
void	set_value_startmeal_unlong(t_philo_thread *thread, pthread_mutex_t *mtx, unsigned long value);
void	set_value_isfull_bool(t_philo_thread *thread, pthread_mutex_t *mtx, t_bool value);

// PHILO_INIT ---------------------------------------------------------------
void init_data(t_data *data, char **argv);
void	init_philo(t_data *data, t_philo_thread *threads);
void	init_mutex(t_data *data);
void	init_thread(t_data *data, t_philo_thread *threads);





#endif
