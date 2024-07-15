/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:32:45 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/15 15:50:08 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "struct.h"

void init_data(t_data *data, char **argv)
{
	philo_check_args(argv);
	data->nbr_meals = 1;
	data->meals_number = FALSE;
	data->nbr_phi = ft_atoi_philo(argv[1]);
	if (data->nbr_phi > 124098)
		exit_error_message("Too many threads (philosophers) -> see: cat /proc/sys/kernel/threads-max\n");     
	data->t_death =  ft_atol_unsigned_philo(argv[2]);
	data->t_eat=  ft_atol_unsigned_philo(argv[3]);
	data->t_sleep =  ft_atol_unsigned_philo(argv[4]);
	if (argv[5])
	{
		data->nbr_meals =  ft_atoi_philo(argv[5]);
		data->meals_number = TRUE;
	}	
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_phi);
	data->one_dead = FALSE;
	data->start = get_time_millisec();
}

void	init_philo(t_data *data, t_philo_thread *threads)
{
	int i;

	i = 0;
	while( i < data->nbr_phi )
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

void	init_mutex(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nbr_phi)
	{
		pthread_mutex_init(&data->forks[i], NULL);// protections
		i++;
	}
}

void	init_thread(t_data *data, t_philo_thread *threads)
{
	int i;
	
	init_philo(data, threads);
	i = 0;
	while( i < data->nbr_phi )
	{
		if(i % 2 == 0)
		{
			if(pthread_create(&threads[i].thread_id, NULL, philo_do, (void *) &threads[i]))
				exit_error_message("ERROR: pthread_create()\n");
		}
		i++;
	}
	usleep(1000);
	i = 1;
	while( i < data->nbr_phi )
	{
		if( i % 2 != 0)
		{
			if(pthread_create(&threads[i].thread_id, NULL, philo_do, (void *) &threads[i]))
				exit_error_message("ERROR: pthread_create()\n");
		}
		i++;
	}
}
