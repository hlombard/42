/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_valid_hex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 02:28:12 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/29 08:23:19 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_str_valid_hex(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			continue;
		else if (str[i] >= 'a' && str[i] <= 'f')
			continue;
		else if (str[i] >= 'A' && str[i] <= 'F')
			continue;
		else
			return (0);
	}
	return (1);
}
