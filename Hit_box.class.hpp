/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hit_box.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumini <mmoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/09 17:56:39 by mmoumini          #+#    #+#             */
/*   Updated: 2025/04/11 12:40:10 by mmoumini         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef _HITBOX_HPP_
# define _HITBOX_HPP_

#include <optional> 
#include "Gomoku.hpp"
#include "Game.class.hpp"

class Hit_box{
private:
    int				xa;
    int				ya;
    int				xb;
    int				yb;

public:
	int				x;
	int				y;
	
	Hit_box( void );
	Hit_box( Hit_box const &src );
	Hit_box( int xc, int yc );
	~Hit_box( void );
	void		initiate( void );
	bool		isOnThebox( int xc, int yc );
	Hit_box & operator=( Hit_box const &rhs );

};

#endif
