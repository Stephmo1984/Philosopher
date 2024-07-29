/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:32:45 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/18 19:34:05 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

void	init_philo(t_data *data, t_philo *threads)
{
	int	i;

	i = 0;
	while (i < data->nbr_phi)
	{
		threads[i].one_dead = &data->one_dead;
		threads[i].meals_are_limited = data->meals_number;
		threads[i].is_full = FALSE;
		threads[i].phi_num = i + 1;
		threads[i].data = data;
		threads[i].start_simu = data->start;
		threads[i].counter_meals_eaten = data->nbr_meals;
		threads[i].last_meal = 0;
		threads[i].start_meal = 0;
		threads[i].counter_meals = data->nbr_meals;
		i++;
	}
}

int	init_mutex(t_data *data, t_philo *threads)
{
	int	i;

	if (pthread_mutex_init(&data->mtx_print, NULL))
		return (error_free(data, threads, ER_MTX_INIT));
	if (pthread_mutex_init(&data->mtx_time, NULL))
		return (error_free(data, threads, ER_MTX_INIT));
	if (pthread_mutex_init(&data->mtx_bool, NULL))
		return (error_free(data, threads, ER_MTX_INIT));
	i = 0;
	while (i < data->nbr_phi)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (error_free(data, threads, ER_MTX_INIT));
		i++;
	}
	return (0);
}

int	create_thread(t_philo *thread)
{
	if (pthread_create(&thread->thread_id, NULL, philo_do, (void *) thread))
		return (1);
	return (0);
}

int	init_thread(t_data *data, t_philo *threads)
{
	int	i;

	init_philo(data, threads);
	i = 0;
	while (i < data->nbr_phi)
	{
		if (i % 2 == 0)
			if (create_thread(&threads[i]) == 1)
				return (error_free(data, threads, ER_THREAD_CREATE));
		i++;
	}
	i = 1;
	usleep(1000);
	while (i < data->nbr_phi)
	{
		if (i % 2 != 0)
			if (create_thread(&threads[i]))
				return (error_free(data, threads, ER_THREAD_CREATE));
		i++;
	}
	return (0);
}

int	parse_and_init_data(t_data *data, int argc, char **argv)
{
	if (philo_check_args(argc, argv) == 1)
		return (1);
	data->nbr_meals = 1;
	data->meals_number = FALSE;
	data->nbr_phi = ft_atoi_philo(argv[1]);
	if (data->nbr_phi > 9999)
		return (error_message("Error:Too many threads to create (max 9999)\n"));
	data->t_death = ft_atol_unsigned_philo(argv[2]);
	data->t_eat = ft_atol_unsigned_philo(argv[3]);
	data->t_sleep = ft_atol_unsigned_philo(argv[4]);
	if (argv[5])
	{
		data->nbr_meals = ft_atoi_philo(argv[5]);
		data->meals_number = TRUE;
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_phi);
	if (!data->forks)
		return (error_message("ERROR: malloc() failed\n"));
	data->one_dead = FALSE;
	data->start = get_time_millisec();
	return (0);
}
