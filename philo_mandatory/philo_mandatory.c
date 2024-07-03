/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mandatory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:12:56 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/03 17:41:21 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "struct.h"

void	philo_eat(t_philo_thread *thread_n, pthread_mutex_t *forks, int fisrt_fork, int second_fork)
{
	thread_n->start_meal = get_time_millisec();
	if ((thread_n->start_meal - thread_n->last_meal) >= thread_n->data->t_death)
	{
		pthread_mutex_lock(&thread_n->data->mtx_print);
		printf("XXXXXXXXXXXXXXXXXX PHILO %d *** XXXX DEAD XXXXX **** \n", thread_n->phi_num);
		pthread_mutex_unlock(&thread_n->data->mtx_print);
		thread_n->is_dead = TRUE;////// voir fonction set ///
		// exit(-1);//a enlever
	}
	print_philo(&thread_n->data->mtx_print, thread_n->phi_num, thread_n->data->start, " is eating");
	usleep(thread_n->data->t_eat);
	thread_n->last_meal = thread_n->start_meal;
	pthread_mutex_unlock(&forks[second_fork]);
	pthread_mutex_unlock(&forks[fisrt_fork]);
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
	thread_n->last_meal = thread_n->data->start;
	l = n - 1;
	r =  n % thread_n->data->nbr_phi;

	// https://www.delftstack.com/fr/howto/c/gettimeofday-in-c/
	while(counter_meals != 0)
	// while(1)
	{
		if (n % 2 == 0)
		{
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " is thinking");
			pthread_mutex_lock(&forks[l]);
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " has taken a fork");
			pthread_mutex_lock(&forks[r]);
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " has taken a fork");
			philo_eat(thread_n, forks, l, r);
			counter_meals--;
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " is sleeping");
			usleep(thread_n->data->t_sleep);
		}
		else if (n % 2 != 0)
		{
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " is thinking");
			pthread_mutex_lock(&forks[r]);
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " has taken a fork");
			pthread_mutex_lock(&forks[l]);
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " has taken a fork");
			philo_eat(thread_n, forks, r, l);
			counter_meals--;
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " is sleeping");
			usleep(thread_n->data->t_sleep);
		}
	}
	return (NULL);
}

void init_data(t_data *data)
{
	data->nbr_phi = 5;
	data->t_death = 1500;
	data->t_eat= 2000000;
	data->t_sleep = 1000000;
	data->nbr_meals = 3;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_phi);
	data->start = get_time_millisec();
}

void	init_thread(t_data *data, t_philo_thread *threads)
{
	int ret;
	int i;

	i = 0;
    while( i < data->nbr_phi)
	{
		threads[i].phi_num = i + 1;
		threads[i].data = data;
		threads[i].counter_meals_eaten = data->nbr_meals;
		ret = pthread_create(&threads[i].thread_id, NULL, philo_do, (void *) &threads[i]);
		if (ret)
		{
			printf("ERROR; return (code from pthread_create() is %d\n", ret);
			exit(-1);
		}
		i++;
	}
}

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
}

int main() 
{
	int nbr_places = 5;
	int i;
    t_philo_thread *threads;
	t_data data;
	
	init_data(&data);
	threads = malloc(sizeof(t_philo_thread) * nbr_places);
	pthread_mutex_init(&data.mtx_print, NULL);
	init_mutex(&data);
	init_thread(&data, threads);
	// while(1)
	// {
	
		
	// }
	join_and_destroy(&data, threads);
	free(threads);
	free(data.forks);
}
