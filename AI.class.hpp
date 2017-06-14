// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AI.class.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/09 18:38:14 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/12 14:36:49 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef _AI_HPP_
# define _AI_HPP_

#include "Player.class.hpp"

class AI : public Player {

public:
	AI( void );
	AI( AI const &src );
	AI( int np );
	~AI( void );

	t_pions	*put_token( Game & game );
	AI & operator=( AI const &rhs );
};

#endif
