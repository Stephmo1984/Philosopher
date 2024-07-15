/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:59 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/15 16:58:29 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "struct.h"

void	exit_error_message(char *str)
{
	printf("%s", str);
	exit (1);
}

void	print_philo(t_philo_thread *thread, pthread_mutex_t *mtx_print, long long start, char *str)
{
	if(get_value_bool(&thread->data->mtx_bool, &thread->data->one_dead) == TRUE)
		return ;
	pthread_mutex_lock(mtx_print);
	printf("%5li   ", get_timestamp_millisec(start));
	printf("  P%d   %10s\n", thread->phi_num, str);
	pthread_mutex_unlock(mtx_print);
}

void	philo_dead(t_philo_thread *thread, pthread_mutex_t *mtx_print, long long start)
{
	set_value_bool(&thread->data->mtx_bool, &thread->data->one_dead, TRUE);
	pthread_mutex_lock(mtx_print);
	printf("%5li   ", get_timestamp_millisec(start));
	printf("  P%d    dead\n", thread->phi_num);
	pthread_mutex_unlock(mtx_print);
}

void	*philo_full(t_philo_thread *thread, pthread_mutex_t *mtx_print, long long start)
{
	set_value_bool(&thread->data->mtx_bool, &thread->is_full, TRUE);
	// if(get_value_bool(&thread->data->mtx_bool, &thread->data->one_dead) == TRUE)
	// 	return (NULL);
	pthread_mutex_lock(mtx_print);
	printf("%5li   ", get_timestamp_millisec(start));
	printf("  P%d    PHILOSOPHER IS FULL\n", thread->phi_num);
	pthread_mutex_unlock(mtx_print);
	return (NULL);
}

