/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:32:19 by mgraefen          #+#    #+#             */
/*   Updated: 2023/02/17 13:54:49 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main (void)
{
	char *input;
	char *promptline;

	promptline = prompt();
	while (1)
		input = readline(promptline);
	freestrings(input, promptline, NULL, NULL);
	return (0);
}