/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:43:32 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/17 23:49:49 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/error.h"

std::string get_error_message(int err_code)
{
    switch (err_code) 
	{
        #define ERROR_MESSAGE(code, message) case code: return message;
        ERROR_MESSAGES_MAP
        #undef ERROR_MESSAGE

        default: return "Unknown error";
    }
}

int error_command(int fd, int err_code, std::string& err_params, 
		std::string& err_trailing_mess)
{
	std::string err_mess = get_error_message(err_code); 
	std::string message = err_params + err_trailing_mess;
	send(fd, message.c_str(), sizeof(message), 0); 
	return err_code;
}
