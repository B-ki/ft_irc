/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:18:31 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/26 17:11:43 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "color.h"

void	log(e_log_type type, std::ostringstream& msg_stream, std::string file, int line)
{
	switch (type) {
    	case LOG_INFO:
			std::cerr << "[" << GREEN  << "INFO ";
			break;
		case LOG_DEBUG:
			std::cerr << "[" << BLUE  << "DEBUG ";
			break;
		case LOG_WARNING:
			std::cerr << "[" << YELLOW  << "WARNING ";
			break;
		case LOG_ERROR:
			std::cerr << "[" << RED  << "ERROR ";
			break;
    }
	std::cerr << RESET << file << ":" << line << "] " << msg_stream.str() << std::endl;
}
