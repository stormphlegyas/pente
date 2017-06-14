// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Game.class.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/09 17:15:37 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/29 13:43:14 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Game.class.hpp"
#include "Human.class.hpp"
#include "AI.class.hpp"

#define DIM 10
#define SQUARE_H 200
#define SQUARE_L 550
#define SPACE 70

void			Game::removeVirtualToken( int x, int y ){
	std::list<t_pions*>::iterator	it;

	for (it = fake.begin(); it != fake.end(); it++)
	{
		t_pions		*token;
		
		token = *it;
		if (token->x == x && token->y == y)
		{
			fake.remove(*it);
			return ;
		}
	}
}

bool			Game::CaptureVirtualB( t_pions * ntoken ){
	int			v;

	v = this->c;
	if ( (this->whoisHere(ntoken->x + 1, ntoken->y) == 1) 
		 && (this->whoisHere(ntoken->x + 2, ntoken->y) == 1) 
		 && (this->whoisHere(ntoken->x + 3, ntoken->y) == 2) )
	{
		this->removeVirtualToken(ntoken->x + 1, ntoken->y);
		this->removeVirtualToken(ntoken->x + 2, ntoken->y);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x - 1, ntoken->y) == 1) 
		 && (this->whoisHere(ntoken->x - 2, ntoken->y) == 1) 
		 && (this->whoisHere(ntoken->x - 3, ntoken->y) == 2) )
	{
		this->removeVirtualToken(ntoken->x - 1, ntoken->y);
		this->removeVirtualToken(ntoken->x - 2, ntoken->y);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x, ntoken->y + 1) == 1) 
		 && (this->whoisHere(ntoken->x, ntoken->y + 2) == 1) 
		 && (this->whoisHere(ntoken->x, ntoken->y + 3) == 2) )
	{
		this->removeVirtualToken(ntoken->x, ntoken->y + 1);
		this->removeVirtualToken(ntoken->x, ntoken->y + 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x, ntoken->y - 1) == 1) 
		 && (this->whoisHere(ntoken->x, ntoken->y - 2) == 1) 
		 && (this->whoisHere(ntoken->x, ntoken->y - 3) == 2) )
	{
		this->removeVirtualToken(ntoken->x, ntoken->y - 1);
		this->removeVirtualToken(ntoken->x, ntoken->y - 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x + 1, ntoken->y + 1) == 1) 
		 && (this->whoisHere(ntoken->x + 2, ntoken->y + 2) == 1) 
		 && (this->whoisHere(ntoken->x + 3, ntoken->y + 3) == 2) )
	{
		this->removeVirtualToken(ntoken->x + 1, ntoken->y + 1);
		this->removeVirtualToken(ntoken->x + 2, ntoken->y + 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x - 1, ntoken->y - 1) == 1)
		 && (this->whoisHere(ntoken->x - 2, ntoken->y - 2) == 1) 
		 && (this->whoisHere(ntoken->x - 3, ntoken->y - 3) == 2) )
	{
		this->removeVirtualToken(ntoken->x - 1, ntoken->y - 1);
		this->removeVirtualToken(ntoken->x - 2, ntoken->y - 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x + 1, ntoken->y - 1) == 1)
		 && (this->whoisHere(ntoken->x + 2, ntoken->y - 2) == 1) 
		 && (this->whoisHere(ntoken->x + 3, ntoken->y - 3) == 2) )
	{
		this->removeVirtualToken(ntoken->x + 1, ntoken->y - 1);
		this->removeVirtualToken(ntoken->x + 2, ntoken->y - 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x - 1, ntoken->y + 1) == 1) 
		 && (this->whoisHere(ntoken->x - 2, ntoken->y + 2) == 1) 
		 && (this->whoisHere(ntoken->x - 3, ntoken->y + 3) == 2) )
	{
		this->removeVirtualToken(ntoken->x - 1, ntoken->y + 1);
		this->removeVirtualToken(ntoken->x - 2, ntoken->y + 2);
		this->c = this->c - 2;
	}
	if (v != this->c)
	{
		this->c = v;
		return (true);
	}
	return (false);
}

bool			Game::CaptureVirtualW( t_pions * ntoken ){
	int			v;

	v = this->c;
	if ( (this->whoisHere(ntoken->x + 1, ntoken->y) == 2) 
		 && (this->whoisHere(ntoken->x + 2, ntoken->y) == 2) 
		 && (this->whoisHere(ntoken->x + 3, ntoken->y) == 1) )
	{
		this->removeVirtualToken(ntoken->x + 1, ntoken->y);
		this->removeVirtualToken(ntoken->x + 2, ntoken->y);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x - 1, ntoken->y) == 2) 
		 && (this->whoisHere(ntoken->x - 2, ntoken->y) == 2) 
		 && (this->whoisHere(ntoken->x - 3, ntoken->y) == 1) )
	{
		this->removeVirtualToken(ntoken->x - 1, ntoken->y);
		this->removeVirtualToken(ntoken->x - 2, ntoken->y);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x, ntoken->y + 1) == 2) 
		 && (this->whoisHere(ntoken->x, ntoken->y + 2) == 2) 
		 && (this->whoisHere(ntoken->x, ntoken->y + 3) == 1) )
	{
		this->removeVirtualToken(ntoken->x, ntoken->y + 1);
		this->removeVirtualToken(ntoken->x, ntoken->y + 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x, ntoken->y - 1) == 2) 
		 && (this->whoisHere(ntoken->x, ntoken->y - 2) == 2) 
		 && (this->whoisHere(ntoken->x, ntoken->y - 3) == 1) )
	{
		this->removeVirtualToken(ntoken->x, ntoken->y - 1);
		this->removeVirtualToken(ntoken->x, ntoken->y - 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x + 1, ntoken->y + 1) == 2) 
		 && (this->whoisHere(ntoken->x + 2, ntoken->y + 2) == 2) 
		 && (this->whoisHere(ntoken->x + 3, ntoken->y + 3) == 1) )
	{
		this->removeVirtualToken(ntoken->x + 1, ntoken->y + 1);
		this->removeVirtualToken(ntoken->x + 2, ntoken->y + 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x - 1, ntoken->y - 1) == 2) 
		 && (this->whoisHere(ntoken->x - 2, ntoken->y - 2) == 2) 
		 && (this->whoisHere(ntoken->x - 3, ntoken->y - 3) == 1) )
	{
		this->removeVirtualToken(ntoken->x - 1, ntoken->y - 1);
		this->removeVirtualToken(ntoken->x - 2, ntoken->y - 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x + 1, ntoken->y - 1) == 2) 
		 && (this->whoisHere(ntoken->x + 2, ntoken->y - 2) == 2) 
		 && (this->whoisHere(ntoken->x + 3, ntoken->y - 3) == 1) )
	{
		this->removeVirtualToken(ntoken->x + 1, ntoken->y - 1);
		this->removeVirtualToken(ntoken->x + 2, ntoken->y - 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x - 1, ntoken->y + 1) == 2) 
		 && (this->whoisHere(ntoken->x - 2, ntoken->y + 2) == 2) 
		 && (this->whoisHere(ntoken->x - 3, ntoken->y + 3) == 1) )
	{
		this->removeVirtualToken(ntoken->x - 1, ntoken->y + 1);
		this->removeVirtualToken(ntoken->x - 2, ntoken->y + 2);
		this->c = this->c - 2;
	}
	if (v != this->c)
	{
		this->c = v;
		return (true);
	}
	return (false);
}

void			Game::add_virtualtoken( t_pions * token ){

	token->player = token->player + 5;
	this->fake.push_back(token);
	if (token->player == 1)
		this->CaptureVirtualW(token);
	else if (token->player == 2)
		this->CaptureVirtualB(token);
}

void			Game::add_virtualtoken( int x, int y, int player ){

	player = player + 5;
	t_pions		*ntoken = new t_pions;
	ntoken->x = x;
	ntoken->y = y;
	ntoken->player = player;
	this->fake.push_back(ntoken);
	if (ntoken->player == 1)
		this->CaptureVirtualW(ntoken);
	else if (ntoken->player == 2)
		this->CaptureVirtualB(ntoken);
}

void		Game::clear_all_virtual( void ){
//	this->tracer = 0;
	std::list<t_pions*>::iterator		it;

	for (it = fake.begin(); it != fake.end(); it++)
	{
		if ((*it)->player > 5)
			delete (*it);
	}
	fake.clear();
	for (it = pions.begin(); it != pions.end(); it++)
	{
		fake.push_back(*it);
	}
}
