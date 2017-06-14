// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AI.class.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/09 17:15:37 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/12 14:38:13 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "AI.class.hpp"

AI::AI( void ): Player("MinMax", 1){
}

AI::AI( AI const &src ){
	*this = src;
}

AI::AI( int np ) : Player("MinMax", np){
}

AI::~AI( void ){
}

t_pions		*AI::put_token( Game & game ){
	t_pions		*pions = new t_pions;

	pions->x = rand() % 19;
	pions->y = rand() % 19;
	pions->player = this->player;
	while ( game.whoisHere(pions) != 0)
	{
		pions->x = rand() % 19;
		pions->y = rand() % 19;
		pions->player = this->player;
	}
	return (pions);
}

AI		& AI::operator=( AI const &rhs ) {
	this->name = rhs.name;
	this->player = rhs.player;
	return *this;
}
