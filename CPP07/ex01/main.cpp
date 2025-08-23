/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:42:42 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/23 21:34:18 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"
#include <iostream>
#include <string>

using std::string;

int main( void ) {
	
	int			arr[] = {0,1,2,3,4,5,6,7,8,9};
	const int	constArr[] = {1,3,5};
	string		strArr[4] = {"hello", "world",
	 "test", "string"}; 

	// double	arr4[] = {3.14, 2.71, 1.41, 0.57};
    // char	arr5[] = {'a', 'b', 'c', 'd', 'e'};
    // float	arr6[] = {1.1f, 2.2f, 3.3f};
	
	::iter(arr, sizeof(arr) / sizeof(arr[0]), ::print);
	::iter(arr, sizeof(arr) / sizeof(arr[0]), ::print);
	::iter(constArr, sizeof(constArr) / sizeof(constArr[0]), ::print);
	::iter(strArr, sizeof(strArr) / sizeof(strArr[0]), ::print);
	
	// Null pointer
	int	*arrnull = NULL;
	::iter(arrnull, 0, ::print); 

	return 0;
	
}
