/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:06:18 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/17 23:49:49 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/error.h"

std::string create_string(int err_code, std::string& err_params,
							std::string& err_trailing_mess)
{
	std::string err_mess = get_error_message(err_code); 
	std::string message = err_params + err_mess + err_trailing_mess;
	return message;
}

void command_test(void)
{
	assert(create_string(401, "rmorel", "") == ); 

}

