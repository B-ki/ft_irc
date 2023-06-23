/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:47:06 by rmorel            #+#    #+#             */
/*   Updated: 2023/06/22 17:09:51 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "tests.h"

int parsing_test_parameters(void)
{
	std::vector<std::string> tested_parameters;
	tested_parameters.push_back("PRIVMSG * LIST :");
	tested_parameters.push_back("PRIVMSG * LS :multi-prefix sasl");
	tested_parameters.push_back("PRIVMSG :bla bla bla");
	tested_parameters.push_back("PRIVMSG #chan :Hey!");
	tested_parameters.push_back("PRIVMSG #chan Hey!");
	tested_parameters.push_back("PRIVMSG #chan ::-)");
	tested_parameters.push_back("PRIVMSG ");
	tested_parameters.push_back("PRIVMSG :");
	tested_parameters.push_back("PRIVMSG bla bla bla");
	for (it = tested_parameters.begin(); it != tested_parameters.end(), it++)
	{
		
	}
	return 0;
}
