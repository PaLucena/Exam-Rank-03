#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

void	ft_putstr(char *str, int *c)
{
	int	i = -1;

	if (!str)
		str = "(null)";
	while (str[++i])
		*c += write(1, &str[i], 1);
}

void	ft_putdigit(long long int n, int base, int *c)
{
	char	*hex = "0123456789abcdef";

	if (n < 0)
	{
		n *= -1;
		*c += write(1, "-", 1);
	}
	if (n >= base)
		ft_putdigit(n / base, base, c);
	*c += write(1, &hex[n % base], 1);
}

int	ft_printf(char *param, ...)
{
	va_list	args;
	int		c = 0;
	int		i = -1;

	va_start(args, param);
	while (param[++i])
	{
		if (param[i] == '%' && (param[i + 1] == 's' || param[i + 1] == 'd' || param[i + 1] == 'x'))
		{
			i++;
			if (param[i] == 's')
				ft_putstr(va_arg(args, char *), &c);
			else if (param[i] == 'd')
				ft_putdigit(va_arg(args, int), 10, &c);
			else if (param[i] == 'x')
				ft_putdigit(va_arg(args, unsigned int), 16, &c);
		}
		else
			c += write(1, &param[i], 1);
	}
	va_end((args));
	return (c);
}

/* int	main(void)
{
	int	a = printf("aaa\n%s, %d, %x\n", "Las patatas", -123456, -25000);
	int	b = ft_printf("aaa\n%s, %d, %x\n", "Las patatas", -123456, -25000);
	printf("\na: %i, b: %i\n", a, b);
} */