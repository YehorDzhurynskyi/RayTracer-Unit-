/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 14:44:26 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/03 15:26:41 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FILE_H
# define FT_FILE_H

char	*ft_merge_file_names(const char *s1, const char *s2);
char	*ft_get_dir_part(const char *filepath);
char	*ft_get_basename_part(const char *filepath);
char	*ft_read_file(const char *filename);

#endif
