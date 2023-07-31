/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:17:58 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/31 16:20:04 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sstream>
# include "utils.h"

std::string utils::itoa(size_t number)
{
	std::stringstream out;
	out << number;
	return out.str();
}
