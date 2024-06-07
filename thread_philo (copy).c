#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t					*mutex[5];

typedef struct s_env
{
	int				philo;
	pthread_mutex_t	mutex;
}					t_env;

// void	*increment_counter(void *thread_id)
// {
// 	long	tid;

// 	tid = (long)thread_id;
// 	// Verrouiller le mutex avant de modifier le compteur
// 	pthread_mutex_lock(&mutex);
// 	counter++;
// 	printf("Thread %ld incremented counter to %d\n", tid, counter);
// 	// Déverrouiller le mutex après avoir modifié le compteur
// 	pthread_mutex_unlock(&mutex);
// 	pthread_exit(NULL);
// }

void	*philo_do(void *num)
{
	long i = (long)num;
	i = (int)i;
	//verrouille mutex n & n-1
	pthread_mutex_lock(&mutex[i]);
	printf("Philo %ld prends fourchette %ld\n", i, i);
	pthread_mutex_lock(&mutex[i-1]);
	printf("Philo %ld prends fourchette %ld\n", i, i-1);
	//libere mutex n & n-1
	pthread_mutex_unlock(&mutex[i]);
	printf("Philo %ld libere fourchette %ld\n", i, i);
	pthread_mutex_unlock(&mutex[i-1]);
	printf("Philo %ld libere fourchette %ld\n", i, i-1);
	pthread_exit(NULL); //???
}

int	main(void)
{
	pthread_t	threads[5];
	int			ret;
	long			i;

	// MUTEX INIT ->  while(nbr philo)
	while (i < 5)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	i = 0;
	// THREAD INIT -> while(nbr philo)
	while( i < 5)
	{
		printf("Creating thread %ld\n", i);
		ret = pthread_create(&threads[i], NULL, philo_do, (void *)i);
		if (ret)
		{
			printf("ERROR; return (code from pthread_create() is %d\n", ret);
			exit(-1);
		}
		i++;
	}
	i = 0;
	// ATTENDRE THREAD -> while(nbr philo)
	while (i < 5)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	i = 0;
	printf("Main thread finished.\n");
	// DETRUIRE LES MUTEX
	while (i < 5)
	{
		pthread_mutex_destroy(&mutex[i]);
		i++;
	}
}
