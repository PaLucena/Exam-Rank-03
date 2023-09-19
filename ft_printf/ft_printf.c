#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

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

int	ft_printf(char *arg, ...)
{
	va_list	params;
	int		c = 0;
	int		i = -1;

	va_start(params, arg);
	while (arg[++i])
	{
		if (arg[i] == '%' && (arg[i + 1] == 's' || arg[i + 1] == 'd' || arg[i + 1] == 'x'))
		{
			i++;
			if (arg[i] == 's')
				ft_putstr(va_arg(params, char *), &c);
			else if (arg[i] == 'd')
				ft_putdigit(va_arg(params, int), 10, &c);
			else if (arg[i] == 'x')
				ft_putdigit(va_arg(params, unsigned int), 16, &c);
		}
		else
			c += write(1, &arg[i], 1);
	}
	va_end(params);
	return (c);
}