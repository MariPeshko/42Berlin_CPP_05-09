/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:53:34 by mpeshko           #+#    #+#             */
/*   Updated: 2025/07/19 19:42:22 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

#include <cstdint>
#include "Data.hpp"

/**
 * Static methods of this class demonstrate that the 
 * serialization/deserialization process preserves the pointer value correctly.
 */

class Serializer {
    
    public:
        static uintptr_t	serialize(Data* ptr);
        static Data*		deserialize(uintptr_t raw);
    
    private:
        Serializer( void );
        Serializer ( const Serializer & other );
        Serializer & operator=( const Serializer &assign);
        ~Serializer( void );
};

#endif
