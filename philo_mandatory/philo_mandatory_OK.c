/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mandatory_OK.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:12:56 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/15 17:59:28 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "struct.h"

void	philo_eat(t_philo_thread *thread_n, pthread_mutex_t *forks, int first_fork, int second_fork)
{
	unsigned long meal_start;
	
	meal_start = get_timestamp_millisec(thread_n->start_simu);
	thread_n->last_meal = thread_n->start_meal;
	set_value_unlong(&thread_n->data->mtx_time, &thread_n->start_meal, meal_start);
	if(get_value_bool(&thread_n->data->mtx_bool, &thread_n->data->one_dead) != TRUE)
		print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " is eating");
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
			if(get_value_bool(&thread->data->mtx_bool, &thread->is_full) == TRUE)
			{
				count++;
				if (count == nbr_phi)
					return ;
			}
			else
			{
				time_stamp = get_timestamp_millisec(thread[i].start_simu);
				if (time_stamp - get_value_unlong(&thread->data->mtx_time, &thread->start_meal) > death)
					return (philo_dead(&thread[i], &thread->data->mtx_print, thread[i].start_simu));
			}
			i++;
		}
		usleep(1000);
	}
}

void	philo_take_forks(t_philo_thread *thread, pthread_mutex_t *forks, int l, int r)
{
		pthread_mutex_lock(&forks[l]);
		print_philo(thread, &thread->data->mtx_print, thread->data->start, " has taken a fork");
		pthread_mutex_lock(&forks[r]);
		print_philo(thread, &thread->data->mtx_print, thread->data->start, " has taken a fork");
		philo_eat(thread, forks, l, r);
}

void	*philo_do(void *thread_philo_n)
{
	t_philo_thread *thread_n;
	pthread_mutex_t *forks;	
	int l;
	int r;

	thread_n = (t_philo_thread *) thread_philo_n;
	forks = thread_n->data->forks;
	l = thread_n->phi_num - 1;
	r =  thread_n->phi_num % thread_n->data->nbr_phi;
	while(1)
	{
			if(get_value_bool(&thread_n->data->mtx_bool, &thread_n->data->one_dead) == TRUE)
				return (NULL);
			print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " is thinking");
			if(get_value_bool(&thread_n->data->mtx_bool, &thread_n->data->one_dead) != TRUE)
			{
				if (thread_n->phi_num % 2 == 0 )
					philo_take_forks(thread_n, forks, l, r);
				else
					philo_take_forks(thread_n, forks, r, l);
				if (thread_n->meals_are_limited == TRUE)
					thread_n->counter_meals--;
				if(thread_n->counter_meals == 0)
					return (philo_full(thread_n, &thread_n->data->mtx_print, thread_n->data->start));
			}
			if(get_value_bool(&thread_n->data->mtx_bool, &thread_n->data->one_dead) == TRUE)
				return (NULL);
			print_philo(thread_n, &thread_n->data->mtx_print, thread_n->data->start, " is sleeping");
			usleep(thread_n->data->t_sleep * 1000);
	}
	return (NULL);
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
	pthread_mutex_destroy(&data->mtx_time);
	pthread_mutex_destroy(&data->mtx_bool);
}

	
void	*one_philo_do(void *thread_one)
{
	t_philo_thread *thread;

	thread = (t_philo_thread *) thread_one;
	usleep(thread->data->t_death * 1000);
	printf("%5li   ", get_timestamp_millisec(thread->data->start));
	printf("  P%d    dead\n", thread->phi_num);
	return (NULL);
}
	
int	one_philo(t_data data)
{
    t_philo_thread *threads;

	threads = malloc(sizeof(t_philo_thread) * 1);// protections
	init_philo(&data, threads);
	if(pthread_create(&threads[0].thread_id, NULL, one_philo_do, (void *) &threads[0]))
		exit_error_message("ERROR: pthread_create()\n");
    pthread_join(threads[0].thread_id, NULL);
	free(threads);
	free(data.forks);
	exit (0);

}

int main(int argc, char **argv) 
{
	int nbr_of_chairs;
    t_philo_thread *threads;
	t_data data;

// protections
// make file

	if (argc < 5)
		exit_error_message("Not enough args\n");
	if (argc > 6)
		exit_error_message("Too many args\n");
	init_data(&data, argv);
	nbr_of_chairs = data.nbr_phi;
	if(nbr_of_chairs == 1)
		one_philo(data);
	threads = malloc(sizeof(t_philo_thread) * nbr_of_chairs);// protections
	pthread_mutex_init(&data.mtx_print, NULL);// protections
	pthread_mutex_init(&data.mtx_time, NULL);// protections
	pthread_mutex_init(&data.mtx_bool, NULL);// protections
	init_mutex(&data);// protections
	init_thread(&data, threads);// protections
	philo_is_dead(threads, nbr_of_chairs, data.t_death, 1);
	join_and_destroy(&data, threads);// protections
	free(threads);
	free(data.forks);
	return (0);
}
