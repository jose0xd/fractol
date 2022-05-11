/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:02:57 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/11 15:05:53 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_atoi(const char *str)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		num = num * 10 + (*str++ - '0');
	num *= sign;
	if (num != (int) num)
	{
		if (sign > 0)
			return (-1);
		return (0);
	}
	return ((int) num);
}

static unsigned int	ft_strlen(const char *s)
{
	unsigned int	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

static char	*ft_strdup(const char *s1)
{
	unsigned int	len;
	char			*copy;
	char			*tmp;

	len = ft_strlen(s1);
	copy = (char *)malloc(sizeof(char) * len + 1);
	if (copy == 0)
		return (0);
	tmp = copy;
	while (*s1)
		*tmp++ = *s1++;
	*tmp = '\0';
	return (copy);
}

double	ft_atof(char *str)
{
	char	*copy;
	int		i;
	double	ret;
	char	*deci;
	double	n_deci;

	copy = ft_strdup(str);
	i = 0;
	while (copy[i] && copy[i] != '.')
		i++;
	if (!copy[i])
	{
		ret = (double)ft_atoi(copy);
		free(copy);
		return (ret);
	}
	deci = &copy[i + 1];
	copy[i] = '\0';
	ret = (double)ft_atoi(copy);
	n_deci = (double)ft_atoi(deci);
	while (n_deci >= 1)
		n_deci /= 10;
	free(copy);
	return (ret + n_deci);
}

/*
#include <stdio.h>

int main(int ac, char **av)
{
	while (--ac > 0)
		printf("%s -> %lf\n", av[ac], ft_atof(av[ac]));
}
*/
