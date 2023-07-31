/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:21:22 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/31 13:44:08 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/Command.h"

bool is_valid_modestring(const std::string& modestring)
{

	for (std::string::const_iterator it = modestring.begin() + 1;
			it != modestring.end(); it++) {
		if (!isalpha(*it) && !isdigit(*it) && *it != '_' && *it != '-')
			return false;
	}
}

int Command::execute_MODE()
{

}
