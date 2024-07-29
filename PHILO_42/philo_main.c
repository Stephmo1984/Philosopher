/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:12:56 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/18 19:49:02 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

int	join_and_destroy(t_data *data, t_philo *threads)
{
	int	i;

	i = 0;
	while (i < data->nbr_phi)
	{
		if (pthread_join(threads[i].thread_id, NULL))
			return (error_free(data, threads, ER_THREAD_JOIN));
		i++;
	}
	i = 0;
	while (i < data->nbr_phi)
	{
		if (pthread_mutex_destroy(&data->forks[i]))
			return (error_free(data, threads, ER_THREAD_JOIN));
		i++;
	}
	if (pthread_mutex_destroy(&data->mtx_print))
		return (error_free(data, threads, ER_THREAD_JOIN));
	if (pthread_mutex_destroy(&data->mtx_time))
		return (error_free(data, threads, ER_THREAD_JOIN));
	if (pthread_mutex_destroy(&data->mtx_bool))
		return (error_free(data, threads, ER_THREAD_JOIN));
	return (0);
}

void	*one_philo_do(void *thread_one)
{
	t_philo	*thread;

	thread = (t_philo *) thread_one;
	usleep(thread->data->t_death * 1000);
	printf("%5li   ", get_timestamp_millisec(thread->data->start));
	printf("  P%d    dead\n", thread->phi_num);
	return (NULL);
}

int	one_philo(t_data data)
{
	t_philo	*threads;

	threads = malloc(sizeof(t_philo) * 1);
	if (!threads)
		return (error_message("ERROR: malloc() failed\n"));
	init_philo(&data, threads);
	if (pthread_create(&threads[0].thread_id, NULL, one_philo_do,
			(void *) &threads[0]))
		return (error_message(ER_THREAD_CREATE));
	if (pthread_join(threads[0].thread_id, NULL))
		return (error_free(&data, threads, ER_THREAD_JOIN));
	free(threads);
	free(data.forks);
	exit (0);
}

int	main(int argc, char **argv)
{
	int			nbr_of_chairs;
	t_philo		*threads;
	t_data		data;

	if (parse_and_init_data(&data, argc, argv) == 1)
		return (1);
	nbr_of_chairs = data.nbr_phi;
	if (nbr_of_chairs == 1)
		return (one_philo(data));
	threads = malloc(sizeof(t_philo) * nbr_of_chairs);
	if (!threads)
		return (error_message("ERROR: malloc() failed\n"));
	if (init_mutex(&data, threads) == 1)
		return (1);
	if (init_thread(&data, threads) == 1)
		return (1);
	usleep(1000);
	philo_is_dead(threads, nbr_of_chairs, 1, 0);
	if (join_and_destroy(&data, threads) == 1)
		return (1);
	free(threads);
	free(data.forks);
	return (0);
}
