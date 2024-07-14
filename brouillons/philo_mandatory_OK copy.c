/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mandatory_OK copy.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:12:56 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/14 15:06:05 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "struct.h"

void	philo_eat(t_philo_thread *thread_n, pthread_mutex_t *forks, int first_fork, int second_fork)
{
	unsigned long meal_start;
	
	meal_start = get_timestamp_millisec(thread_n->start_simu);
	thread_n->last_meal = thread_n->start_meal;

	set_value_startmeal_unlong(thread_n, &thread_n->data->mtx_time, meal_start);
	if(get_value_onedead_bool(thread_n, &thread_n->data->mtx_bool) != TRUE)
		print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " ---------------> is eating");
	usleep(thread_n->data->t_eat * 1000);
	pthread_mutex_unlock(&forks[second_fork]);
	pthread_mutex_unlock(&forks[first_fork]);
}


void philo_is_dead(t_philo_thread *thread, int nbr_phi, unsigned long death, int count)
{
	unsigned long time_stamp;
	int i;

	while(1)
	{
		i = 0;
		count = 1;
		while (i < nbr_phi)
		{
			if(get_value_isfull_bool(thread, &thread->data->mtx_bool) == TRUE)
			{
				count++;
				if (count == nbr_phi)
					return ;
			}
			else
			{
				time_stamp = get_timestamp_millisec(thread[i].start_simu);
				if (time_stamp - get_value_startmeal_unlong(&thread[i], &thread[i].data->mtx_time) > death)
					return (print_philo_dead(&thread[i], &thread->data->mtx_print, thread[i].start_simu));
			}
			i++;
		}
		usleep(1000);
	}
}

void	*philo_do(void *thread_philo_n)
{
	t_philo_thread *thread_n;
	int n;
	pthread_mutex_t *forks;
	int counter_meals;
	int l;
	int r;

	thread_n = (t_philo_thread *) thread_philo_n;
	n = thread_n->phi_num;
	forks = thread_n->data->forks;
	counter_meals = thread_n->data->nbr_meals;
	thread_n->last_meal = 0;
	l = n - 1;
	r =  n % thread_n->data->nbr_phi;
	while(1)
	{
			if(get_value_onedead_bool(thread_n, &thread_n->data->mtx_bool) == TRUE)
				return(NULL);
			if(get_value_onedead_bool(thread_n, &thread_n->data->mtx_bool) != TRUE)
			{
				print_philo( thread_n, &thread_n->data->mtx_print, thread_n->data->start, " is thinking");
				pthread_mutex_lock(&forks[l]);
				print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " has taken a fork");
				pthread_mutex_lock(&forks[r]);
				print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " has taken a fork");
				philo_eat(thread_n, forks, l, r);
			}	
			if(get_value_onedead_bool(thread_n, &thread_n->data->mtx_bool) == TRUE)
				return(NULL);
			if (thread_n->meals_are_limited == TRUE)
				counter_meals--;
			if(counter_meals == 0)
			{
				thread_n->is_full = TRUE;
				print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " PHILOSOPHER IS FULL");
				return (NULL);
			}
			if(get_value_onedead_bool(thread_n, &thread_n->data->mtx_bool) == TRUE)
				return(NULL);
			print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " is sleeping");
			usleep(thread_n->data->t_sleep * 1000);
	}
	return (NULL);
}

// void	*philo_do_odd(void *thread_philo_n)
// {
// 	t_philo_thread *thread_n;
// 	int n;
// 	pthread_mutex_t *forks;
// 	int counter_meals;
// 	int l;
// 	int r;

// 	thread_n = (t_philo_thread *) thread_philo_n;
// 	n = thread_n->phi_num;
// 	forks = thread_n->data->forks;
// 	counter_meals = thread_n->data->nbr_meals;
// 	thread_n->last_meal = 0;
// 	l = n - 1;
// 	r =  n % thread_n->data->nbr_phi;
// 	while(1)
// 	{
// 		if(get_value_onedead_bool(thread_n, &thread_n->data->mtx_bool) == TRUE)
// 			return(NULL);
// 		if(get_value_onedead_bool(thread_n, &thread_n->data->mtx_bool) != TRUE)
// 		{
// 			print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " is thinking");
// 			pthread_mutex_lock(&forks[r]);
// 			print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " has taken a fork");
// 			pthread_mutex_lock(&forks[l]);
// 			print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " has taken a fork");
// 			if(get_value_onedead_bool(thread_n, &thread_n->data->mtx_bool) == TRUE)//
// 			{
// 				pthread_mutex_unlock(&forks[l]);
// 				pthread_mutex_unlock(&forks[r]);
// 				return(NULL);
// 			}
// 			philo_eat(thread_n, forks, r, l);
// 		}
// 		if(get_value_onedead_bool(thread_n, &thread_n->data->mtx_bool) == TRUE)
// 			return(NULL);
// 		if (thread_n->meals_are_limited == TRUE)
// 			counter_meals--;
// 		if(counter_meals == 0)
// 		{
// 			thread_n->is_full = TRUE;
// 			print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " PHILOSOPHER IS FULL");
// 			return (NULL);
// 		}
// 		if(get_value_onedead_bool(thread_n, &thread_n->data->mtx_bool) == TRUE)
// 			return(NULL);;
// 		print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " is sleeping");
// 		usleep(thread_n->data->t_sleep * 1000);
// 	}
// 	return (NULL);
// }

void	join_and_destroy(t_data *data, t_philo_thread *threads)
{
	int i;

	i = 0;
	while( i < data->nbr_phi)
    {
        pthread_join(threads[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < data->nbr_phi)
	{
		 pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mtx_print);
	pthread_mutex_destroy(&data->mtx_time);
	pthread_mutex_destroy(&data->mtx_bool);
}

int main(int argc, char **argv) 
{
	int nbr_of_chairs;
	int i;
    t_philo_thread *threads;
	t_data data;
	
// !! faire fonction pour nbr_phi == 1 

	if (argc < 5)
		exit_error_message("Not enough args\n");
	if (argc > 6)
		exit_error_message("Too many args\n");
	init_data(&data, argv);
	nbr_of_chairs = data.nbr_phi;
	threads = malloc(sizeof(t_philo_thread) * nbr_of_chairs);
	pthread_mutex_init(&data.mtx_print, NULL);
	pthread_mutex_init(&data.mtx_time, NULL);
	pthread_mutex_init(&data.mtx_bool, NULL);
	init_mutex(&data);
	init_thread(&data, threads);
	philo_is_dead(threads, nbr_of_chairs, data.t_death, 1);
	join_and_destroy(&data, threads);
	free(threads);
	free(data.forks);
	return (0);
}
