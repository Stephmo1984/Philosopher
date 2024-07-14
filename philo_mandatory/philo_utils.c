/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:59 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/14 15:04:43 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "struct.h"

void	exit_error_message(char *str)
{
	printf("%s", str);
	exit (1);
}

unsigned long	get_time_millisec(void)
{
	struct timeval time;
	unsigned long time_usec;
	
	gettimeofday(&time, NULL);
	time_usec = ((time.tv_sec * 1000000) + time.tv_usec);
	return (time_usec / 1000);
}

unsigned long	get_timestamp_millisec(unsigned long start_milli)
{
	struct timeval time;
	unsigned long time_millisec;

	gettimeofday(&time, NULL);
	time_millisec = ((time.tv_sec * 1000000) + time.tv_usec) / 1000;
	return (time_millisec - start_milli);
}

void	print_philo(t_philo_thread *thread, pthread_mutex_t *mtx_print, long long start, char *str)
{
	if(get_value_onedead_bool(thread, &thread->data->mtx_bool) == TRUE)
		return ;
	pthread_mutex_lock(mtx_print);
	printf("%5li   ", get_timestamp_millisec(start));
	printf("  P%d   %10s\n", thread->phi_num, str);
	pthread_mutex_unlock(mtx_print);
}

void	philo_dead(t_philo_thread *thread, pthread_mutex_t *mtx_print, long long start)
{
	set_value_onedead_bool(thread, &thread->data->mtx_bool, TRUE);
	pthread_mutex_lock(mtx_print);
	printf("%5li   ", get_timestamp_millisec(start));
	printf("  P%d    dead\n", thread->phi_num);
	pthread_mutex_unlock(mtx_print);
}

void	*philo_full(t_philo_thread *thread, pthread_mutex_t *mtx_print, long long start)
{
	set_value_isfull_bool(thread, &thread->data->mtx_bool, TRUE);
	pthread_mutex_lock(mtx_print);
	printf("%5li   ", get_timestamp_millisec(start));
	printf("  P%d    PHILOSOPHER IS FULL\n", thread->phi_num);
	pthread_mutex_unlock(mtx_print);
	return (NULL);
}

