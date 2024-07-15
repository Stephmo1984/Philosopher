/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mandatory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:12:56 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/13 22:45:23 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "struct.h"

t_bool	get_value_bool(pthread_mutex_t *mtx, t_bool to_get)
{
	t_bool	value;
	pthread_mutex_lock(mtx);
	value = to_get;
	// write(1, "t_bool updated\n", 16);
	pthread_mutex_unlock(mtx);
	return (value);
}

void	set_value_bool(pthread_mutex_t *mtx, t_bool to_modify, t_bool value)
{
	pthread_mutex_lock(mtx);
	to_modify = value;
	pthread_mutex_unlock(mtx);
}

unsigned long	get_value_unlong(pthread_mutex_t *mtx, unsigned long to_get)
{
	unsigned long	value;
	pthread_mutex_lock(mtx);
	value = to_get;
	pthread_mutex_unlock(mtx);
	return (value);
}

void	set_value_unlong(pthread_mutex_t *mtx, unsigned long to_modify, unsigned long value)
{
	pthread_mutex_lock(mtx);
	to_modify = value;
	pthread_mutex_unlock(mtx);
}

void	philo_eat(t_philo_thread *thread_n, pthread_mutex_t *forks, int fisrt_fork, int second_fork)
{
	thread_n->last_meal = thread_n->start_meal;
	thread_n->start_meal = get_timestamp_millisec(thread_n->data->start);

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
	pthread_mutex_unlock(&forks[fisrt_fork]);
}

void *philo_is_dead(void *thread_philo)
{
	t_philo_thread *thread;
	unsigned long death;
	thread = (t_philo_thread *) thread_philo;	
	
	unsigned long diff;
	unsigned long start;
	int nbr_phi;
	int i;

	i = 0;
	death = thread->data->t_death;
	diff = 0;
	nbr_phi = thread->data->nbr_phi;
	start = thread->data->start;
	while(1)
	{
		while (i < nbr_phi)
		{
			diff =  get_timestamp_millisec(start) - thread[i].start_meal;
			if (diff > death && thread[i].is_full == FALSE) 
			{
				set_value_bool(&thread->data->mtx_death, thread->data->one_dead, TRUE);
				print_philo(&thread[i].data->mtx_print, thread[i].phi_num, thread[i].data->start, " PHILOSOPHER IS DEAD");
				// return (NULL);
				sleep(10);
				exit(1);
			}
		}
		usleep(1000);
		i = 0;
	}
	return(NULL);
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
	while(1)
	{
		// if(get_value_bool(&thread_n->data->mtx_death, thread_n->data->one_dead) == TRUE)
		// 	return (NULL);
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
				print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " PHILOSOPHER IS FULL");
				return (NULL);
			}
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " is sleeping");
			usleep(thread_n->data->t_sleep * 1000);
		}
		if (n % 2 != 0)
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
				print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " PHILOSOPHER IS FULL");
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
	data->nbr_phi = 5;
	data->t_death = 800;
	data->t_eat= 200;
	data->t_sleep = 200;
	data->nbr_meals = 7;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_phi);
	data->start = get_time_millisec();
	data->one_dead = FALSE;

}

void	init_thread(t_data *data, t_philo_thread *threads)
{
	int ret;
	int i;

	i = 0;
	while( i < data->nbr_phi )
	{
			threads[i].one_dead = &data->one_dead;
			threads[i].death = data->t_death;
			threads[i].is_full = FALSE;
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
	pthread_mutex_destroy(&data->mtx_death);
	pthread_mutex_destroy(&data->mtx_time);


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
	pthread_mutex_init(&data.mtx_death, NULL);
	pthread_mutex_init(&data.mtx_time, NULL);

	init_mutex(&data);
	init_thread(&data, threads);
	
	philo_is_dead(threads);
	
	join_and_destroy(&data, threads);
	free(threads);
	free(data.forks);
	return (0);
}
