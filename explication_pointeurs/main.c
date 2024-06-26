#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_ex{

	int i;
	int *p;
} t_ex ;

int main()
{
	t_ex a;
	t_ex b;
	t_ex c;

	a.i = 1;
	b.i = 2;
	c.i = 3;
	int *x = malloc(sizeof(int) * 1);
	*x = 3;
	int y = 5;
	int z = 42;

	a.p = x;
	b.p = x;
	c.p = x;

	printf("a:%p - b:%p - c:%p\n", &a.i, &b.i, &c.i);
	printf("a:%p - b:%p - c:%p\n", a.p, b.p, c.p);
	printf("a:%i - b:%i - c:%i", *a.p, *b.p, *c.p);

}