/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfakih <mfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 15:06:42 by mfakih            #+#    #+#             */
/*   Updated: 2025/11/30 15:06:43 by mfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*init_string_bonus(char *s)
{
	if (!s)
	{
		s = malloc(1);
		if (!s)
			return (NULL);
		s[0] = '\0';
	}
	return (s);
}

char	*read_and_stash_bonus(int fd, char *stash)
{
	char	*buffer;
	int		bytes;
	int		i;

	i = -1;
	stash = init_string_bonus(stash);
	if (!stash)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(stash), NULL);
	while (stash[++i] != '\n')
	{
		if (stash[i] == '\0')
		{
			bytes = read(fd, buffer, BUFFER_SIZE);
			if (bytes == 0)
				return (free(buffer), stash);
			if (bytes < 0)
				return (free(buffer), free(stash), NULL);
			buffer[bytes] = '\0';
			stash = ft_strjoin_bonus(stash, buffer);
		}
	}
	return (free(buffer), stash);
}

char	*extract_line_bonus(char *stash)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (!stash || stash[0] == '\0')
		return (NULL);
	while (stash[i] != '\n' && stash[i])
		i++;
	line = malloc (i + (stash[i] == '\n') + 1);
	if (!line)
		return (NULL);
	while (++j < i)
		line[j] = stash[j];
	if (stash[i] == '\n')
		line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

char	*clean_stash_bonus(char *stash)
{
	int		i;
	int		j;
	int		stash_len;
	char	*new_stash;

	i = 0;
	j = 0;
	if (!stash)
		return (NULL);
	stash_len = ft_strlen_bonus(stash);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	i++;
	new_stash = malloc(stash_len - i + 1);
	if (!new_stash)
		return (stash);
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	return (free(stash), new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_and_stash_bonus(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = extract_line_bonus(stash[fd]);
	if (!line)
	{
		free (stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = clean_stash_bonus(stash[fd]);
	if (stash[fd] && stash[fd][0] == '\0')
	{
		free(stash[fd]);
		stash[fd] = NULL;
	}
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// int main()
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	int fd2 = open ("test2.txt", O_RDONLY);
// 	char *s = get_next_line_bonus(fd);
// 	char *s2 = get_next_line_bonus(fd2);
// 	while (s)
// 	{
// 		printf("%s%s", s, s2);
// 		free (s);
// 		free (s2);
// 		s2 = get_next_line_bonus(fd2);
// 		s = get_next_line_bonus(fd);
// 	}
// 	free (s);
// }
