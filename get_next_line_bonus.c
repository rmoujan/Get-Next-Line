/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:35:11 by rmoujan           #+#    #+#             */
/*   Updated: 2021/12/11 15:44:56 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_checker(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	if (i == 0)
		return (-2);
	return (-1);
}

char	*ft_process(char **rest)
{
	char	*line;
	char	*tmp;
	int		nl;

	if (!*rest)
		return (NULL);
	if (*(*rest) == '\0')
		return (ft_free(rest));
	nl = ft_checker(*rest);
	if (nl > -1)
	{
		line = ft_substr(*rest, 0, nl + 1);
		tmp = ft_substr(*rest, nl + 1, ft_strlen(*rest + nl + 1));
		ft_free(rest);
		*rest = tmp;
		return (line);
	}
	else if (nl == -1)
	{
		line = ft_substr(*rest, 0, ft_strlen(*rest));
		ft_free(rest);
		return (line);
	}
	return (NULL);
}

void	*ft_free(char **p1)
{
	if (*p1)
	{
		free(*p1);
		*p1 = NULL;
	}
	return (NULL);
}

char	*ft_work(char **buffer, char **rest, int fd)
{
	int	rd;

	rd = 1;
	while (rd > 0)
	{
		rd = read(fd, *buffer, BUFFER_SIZE);
		if (rd < 0)
		{
			ft_free(buffer);
			return (ft_free(rest));
		}
		*(*buffer + rd) = '\0';
		if (ft_checker(*buffer) > -1)
		{
			*rest = ft_strjoin(rest, buffer);
			break ;
		}
		else if (ft_checker(*buffer) == -2)
			break ;
		*rest = ft_strjoin(rest, buffer);
	}
	ft_free(buffer);
	return (ft_process(rest));
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*rest[OPEN_MAX];
	char		*str;

	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || !buffer)
		return (ft_free(&buffer));
	if (!rest[fd])
	{
		rest[fd] = (char *) malloc(1 * sizeof(char));
		rest[fd][0] = '\0';
	}
	str = ft_work(&buffer, &rest[fd], fd);
	return (str);
}
