/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mandatory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:12:56 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/06 13:45:40 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "struct.h"

void	philo_eat(t_philo_thread *thread_n, pthread_mutex_t *forks, int fisrt_fork, int second_fork)
{
	// thread_n->start_meal = get_time_millisec();
	
	thread_n->last_meal = thread_n->start_meal;
	// printf("P%d thread_n->last_meal = %lu\n", thread_n->phi_num, thread_n->last_meal);

	thread_n->start_meal = get_timestamp_millisec(thread_n->data->start);

	// printf("P%d thread_n->start_meal = %lu\n", thread_n->phi_num, thread_n->start_meal);

	// if ((thread_n->start_meal - thread_n->last_meal) >= thread_n->data->t_death)
	// {
	// 	pthread_mutex_lock(&thread_n->data->mtx_print);
	// 	printf("XXXXXXXXXXXXXXXXXX PHILO %d *** XXXX DEAD XXXXX **** \n", thread_n->phi_num);
	// 	pthread_mutex_unlock(&thread_n->data->mtx_print);
	// 	thread_n->is_dead = TRUE;////// voir fonction set et unset///
	// 	// exit(-1);//a enlever
	// }
	print_philo(&thread_n->data->mtx_print, thread_n->phi_num, thread_n->data->start, " is eating");
	usleep(thread_n->data->t_eat * 1000);

	pthread_mutex_unlock(&forks[second_fork]);
	// print_philo(&thread_n->data->mtx_print, thread_n->phi_num, thread_n->data->start, " has drop a fork");
	// printf("fork dropped -> %d\n", second_fork);

	
	pthread_mutex_unlock(&forks[fisrt_fork]);
	// print_philo(&thread_n->data->mtx_print, thread_n->phi_num, thread_n->data->start, " has drop a fork");
	// printf("fork dropped -> %d\n", fisrt_fork);

}


// void *philo_is_dead(void *thread_philo)
// {
// 	t_philo_thread *thread;
// 	unsigned long death;
// 	thread = (t_philo_thread *) thread_philo;	
// 	death = thread->data->t_death;
// 	// printf("diff = %li\n", get_time_millisec() - thread.last_meal );
	
// 	unsigned long diff;
// 	unsigned long time_stamp;

	
// 	unsigned long start;
	
// 	start = thread->data->start;

// 	while(1)
// 	{
// 		// printf("MONITOR death = %li\n", death);
// 		// printf("MONITOR get_time_millisec() = %li\n", get_time_millisec() );
// 		// printf("MONITOR thread->last_meal = %li\n", thread->last_meal );
// 		// printf("MONITOR get_timestamp_millisec(start) = %li\n", get_timestamp_millisec(start) );
// 		// printf("MONITOR TimeStamp diff = %li\n", get_timestamp_millisec(start) - thread->last_meal );
// 		// printf("MONITOR TimeStamp diff = %li\n", get_timestamp_millisec(start) - (thread->start_meal - thread->last_meal) );
// 		if(thread->is_full == TRUE)
// 			return(NULL);
		
// 		time_stamp =  get_timestamp_millisec(start);
// 		diff = time_stamp - (thread->start_meal);	
// 		if (diff > death)
// 		{
// 			// printf("MONITOR TimeStamp= %li\n", time_stamp );

// 			// printf("MONITOR TimeStamp diff = %li\n", diff );
// 			// printf("MONITOR thread->start_meal= %li\n", thread->start_meal );
// 			printf("A PHILOSOPHER IS DEAD -> P%d\n", thread->phi_num);
// 			// return(NULL);
// 			exit(1);
// 		}
// 		usleep(1000);
// 	}
// 	return(thread_philo);
// }


void *philo_is_dead(void *thread_philo)
{
	t_philo_thread *thread;
	unsigned long death;
	thread = (t_philo_thread *) thread_philo;	
	death = thread->data->t_death;
	
	unsigned long diff;
	unsigned long time_stamp;

	unsigned long start;
	int nbr_phi;
	int i;

	i = 0;
	nbr_phi = thread->data->nbr_phi;
	
	start = thread->data->start;

	while(1)
	{
		if(thread->is_full == TRUE)
			return(NULL);
		while (i < nbr_phi)
		{
			time_stamp =  get_timestamp_millisec(start);
			diff = time_stamp - (thread->start_meal);	
			if (diff > death)
			{
				// printf("MONITOR TimeStamp= %li\n", time_stamp );
				// printf("MONITOR TimeStamp diff = %li\n", diff );
				// printf("MONITOR thread->start_meal= %li\n", thread->start_meal );
				print_philo(&thread->data->mtx_print, thread->phi_num, thread->data->start, " A PHILOSOPHER IS DEAD");

				// printf("A PHILOSOPHER IS DEAD -> P%d\n", thread->phi_num);
				// return(NULL);
				exit(1);
			}
		}
		usleep(1000);
		i = 0;
	}
	return(thread_philo);
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
	thread_n->start_meal = 0;

	l = n - 1;
	r =  n % thread_n->data->nbr_phi;

	// printf("PHILO %d r->%d l->%d\n", n, l , r );
	// pthread_create(&thread_n->philo_monitor, NULL, philo_is_dead, (void *) thread_n);
	
	while(1)
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
			if(counter_meals == 0)
			{
				thread_n->is_full = TRUE;
				write(1, "philo full \n", 13);
				return (NULL);
			}
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " is sleeping");
			usleep(thread_n->data->t_sleep * 1000);
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
			if(counter_meals == 0)
			{
				thread_n->is_full = TRUE;
				write(1, "philo full \n", 13);
				return (NULL);
			}
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " is sleeping");
			usleep(thread_n->data->t_sleep * 1000);
		}
	}
	return (NULL);
}

void init_data(t_data *data)
{
	data->nbr_phi = 4;
	data->t_death = 310;
	data->t_eat= 200;
	data->t_sleep = 100;
	data->nbr_meals = 1000;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_phi);
	data->start = get_time_millisec();
	data->is_dead = FALSE;
}

void	init_thread(t_data *data, t_philo_thread *threads)
{
	int ret;
	int i;

	i = 0;
	while( i < data->nbr_phi )
	{
			threads[i].is_dead = &data->is_dead;
			threads[i].is_full = FALSE;
			threads[i].phi_num = i + 1;
			threads[i].data = data;
			threads[i].counter_meals_eaten = data->nbr_meals;
			threads[i].last_meal = data->start;
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
	while (i < data->nbr_phi)
	{
		 pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mtx_print);
}

int main() 
{
	int nbr_places = 4;
	int i;
    t_philo_thread *threads;
	t_data data;
	
	init_data(&data);
	threads = malloc(sizeof(t_philo_thread) * nbr_places);
	pthread_mutex_init(&data.mtx_print, NULL);
	init_mutex(&data);
	init_thread(&data, threads);
	philo_is_dead(threads);
	join_and_destroy(&data, threads);
	free(threads);
	free(data.forks);
	return (0);
}
