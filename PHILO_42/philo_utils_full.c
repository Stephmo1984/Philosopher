/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_full.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:59 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/19 13:42:19 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

int	error_message(char *str)
{
	printf("%s", str);
	return (1);
}

int	error_free(t_data *data, t_philo *threads, char *str)
{
	printf("%s", str);
	if (threads)
		free(threads);
	if (data && data->forks)
		free(data->forks);
	return (1);
}

void	print_philo(t_philo *thrd, t_mutex *mtx, long long start, char *str)
{
	if (get_value_bool(&thrd->data->mtx_bool, &thrd->data->one_dead) == TRUE)
		return ;
	pthread_mutex_lock(mtx);
	printf("%5li   ", get_timestamp_millisec(start));
	printf("  P%d    %10s\n", thrd->phi_num, str);
	pthread_mutex_unlock(mtx);
}

void	philo_dead(t_philo *thread, t_mutex *mtx_print, long long start)
{
	set_value_bool(&thread->data->mtx_bool, &thread->data->one_dead, TRUE);
	pthread_mutex_lock(mtx_print);
	printf("%5li   ", get_timestamp_millisec(start));
	printf("  P%d     dead\n", thread->phi_num);
	pthread_mutex_unlock(mtx_print);
}

void	*philo_full(t_philo *thread, t_mutex *mtx_print, long long start)
{
	set_value_bool(&thread->data->mtx_bool, &thread->is_full, TRUE);
	pthread_mutex_lock(mtx_print);
	printf("%5li   ", get_timestamp_millisec(start));
	printf("  P%d    PHILOSOPHER IS FULL\n", thread->phi_num);
	pthread_mutex_unlock(mtx_print);
	return (NULL);
}
