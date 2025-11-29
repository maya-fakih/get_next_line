/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfakih <mfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 18:18:19 by mfakih            #+#    #+#             */
/*   Updated: 2025/11/29 18:46:43 by mfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*init_string(char *s)
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

char	*read_and_stash(int fd, char *stash)
{
	char	*buffer;
	int		bytes;
	int		i;

	i = -1;
	stash = init_string(stash);
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
			stash = ft_strjoin(stash, buffer);
		}
	}
	return (free(buffer), stash);
}

char	*extract_line(char *stash)
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

char	*clean_stash(char *stash)
{
	int		i;
	int		j;
	int		stash_len;
	char	*new_stash;

	i = 0;
	j = 0;
	if (!stash)
		return (NULL);
	stash_len = ft_strlen(stash);
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
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_and_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (!line)
	{	
		free (stash);
		stash = NULL;
		return (NULL);
	}
	stash = clean_stash(stash);
	if (stash && stash[0] == '\0')
	{
		free(stash);
		stash = NULL;
	}
	return (line);
}
#include <fcntl.h>
#include <stdio.h>
int main()
{
	int fd = open("test.txt", O_RDONLY);
	char *s = get_next_line(fd);
	while (s)
	{
		printf("%s", s);
		free (s);
		s = get_next_line(fd);
	}
	free (s);
}