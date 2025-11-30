/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfakih <mfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 18:18:29 by mfakih            #+#    #+#             */
/*   Updated: 2025/11/29 18:42:55 by mfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100  
# endif

char	*ft_strjoin_bonus(char *s1, char *s2);
size_t	ft_strlen_bonus(const char *str);
char	*get_next_line(int fd);
char	*extract_line_bonus(char *stash);
char	*read_and_stash_bonus(int fd, char *stash);
char	*init_string_bonus(char *s);
char	*clean_stash_bonus(char *stash);

#endif