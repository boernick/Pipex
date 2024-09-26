/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:41:06 by nboer             #+#    #+#             */
/*   Updated: 2024/09/26 17:56:12 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include "/home/nboer/git/Pipex/includes/ft_printf/ft_printf.h"
# include "/home/nboer/git/Pipex/includes/Libft/libft.h"

int	str_error(char *error);

#endif