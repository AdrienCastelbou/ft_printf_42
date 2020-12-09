#include "includes/ft_printf.h"

int	main()
{
	int b;
	printf("hello%n", &b);
	printf("\n b value = %d\n", b);
	ft_printf("hello%n", &b);
	ft_printf("\n b value = %d", b);

}
