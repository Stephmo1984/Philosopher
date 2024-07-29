/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:59 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/19 13:39:14 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

unsigned long	get_time_millisec(void)
{
	struct timeval	time;
	unsigned long	time_usec;

	gettimeofday(&time, NULL);
	time_usec = ((time.tv_sec * 1000000) + time.tv_usec);
	return (time_usec / 1000);
}

unsigned long	get_timestamp_millisec(unsigned long start_milli)
{
	struct timeval	time;
	unsigned long	time_millisec;

	gettimeofday(&time, NULL);
	time_millisec = ((time.tv_sec * 1000000) + time.tv_usec) / 1000;
	return (time_millisec - start_milli);
}

void	philo_is_sleeping_eating(t_philo *thr, t_ulong time_to_do)
{
	t_ulong		time;
	t_ulong		time_mod;
	t_ulong		i;

	if (time_to_do >= 10)
	{
		time = (time_to_do) / 10;
		time_mod = ((time_to_do) % 10);
	}
	else
		time = time_to_do;
	i = 0;
	while (i < time)
	{
		usleep(10000);
		if (get_value_bool(&thr->data->mtx_bool, &thr->data->one_dead) == TRUE)
			return ;
		i++;
	}
	if (time_mod)
		usleep(time_mod * 1000);
}
