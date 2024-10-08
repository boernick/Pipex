/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:41:06 by nboer             #+#    #+#             */
/*   Updated: 2024/10/07 17:01:47 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include "/home/nick/42Berlin/Pipex/includes/ft_printf/ft_printf.h"
# include "/home/nick/42Berlin/Pipex/includes/Libft/libft.h"
// # include "/home/nboer/git/Pipex/includes/ft_printf/ft_printf.h"
// # include "/home/nboer/git/Pipex/includes/Libft/libft.h"

int		str_error(char *error);
void	free_array(char **array);

#endif