/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfakih <mfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 18:18:19 by mfakih            #+#    #+#             */
/*   Updated: 2025/11/22 18:23:19 by mfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	init_file(char **file)
{
	if (*file != NULL)
		return (1);
	*file = malloc(1);
	if (!*file)
		return (0);
	(*file)[0] = '\0';
	return (1);
}

static int	join_and_replace(char **file, char *buffer)
{
	char	*tmp;

	tmp = *file;
	*file = ft_strjoin(tmp, buffer);
	free(tmp);
	if (!*file)
		return (0);
	return (1);
}

static ssize_t	attach_buffer(char **file, int fd)
{
	char	*buffer;
	ssize_t	bytes;

	if (!init_file(file))
		return (-1);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes <= 0)
	{
		free(buffer);
		return (bytes);
	}
	buffer[bytes] = '\0';
	if (!join_and_replace(file, buffer))
	{
		free(buffer);
		return (-1);
	}
	free(buffer);
	return (bytes);
}

static char	*extract_line(char *file, int *i, int j)
{
	char	*r;
	int		k;

	r = malloc(j + (file[*i + j] == '\n') + 1);
	if (!r)
		return (NULL);
	k = 0;
	while (file[*i] && file[*i] != '\n')
		r[k++] = file[(*i)++];
	if (file[*i] == '\n')
		r[k++] = file[(*i)++];
	r[k] = '\0';
	return (r);
}

char	*get_next_line(int fd)
{
	static char	*file;
	static int	i;
	ssize_t		ret;
	int			j;

	ret = attach_buffer(&file, fd);
	if (ret <= 0 && (!file || file[i] == '\0'))
		return (NULL);
	j = 0;
	while (file[i + j] != '\n')
	{
		if (file[i + j] == '\0')
		{
			ret = attach_buffer(&file, fd);
			if (ret <= 0)
				break ;
		}
		j++;
	}
	return (extract_line(file, &i, j));
}

// #include <fcntl.h>
// #include <stdio.h>
// int main(int argc, char **argv)
// {
// 	argc = 12;
// 	int fd = open(argv[1], O_RDONLY);
// 	char *s = get_next_line(fd);
// 	char *line2 = get_next_line(fd);
// 	char *line3 = get_next_line(fd);
// 	printf("%s%s%s", s, line2, line3);
// 	free (s);
// 	free (line3);
// 	free (line2);
// }