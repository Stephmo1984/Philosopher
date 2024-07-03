/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:59 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/03 17:01:33 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "struct.h"

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

void	print_philo(pthread_mutex_t *mtx_print, int n, long long start, char *str)
{
	pthread_mutex_lock(mtx_print);
	printf("[%li]  ", get_timestamp_millisec(start));
	printf("P%d %s\n", n, str);
	pthread_mutex_unlock(mtx_print);
}

void	init_mutex(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nbr_phi)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

