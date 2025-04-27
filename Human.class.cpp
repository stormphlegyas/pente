// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Human.class.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/09 17:15:37 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/12 14:48:30 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Human.class.hpp"

Human::Human( void ): Player("unknow", 1), make(false){
}

Human::Human(Human const &src) : Player(src) {
	this->make = src.make;
	this->human = src.human;
}

Human::Human( std::string n, int np ) : Player(n, np), make(false){
	human = true;
}

Human::Human( int np ) : Player("unknow", np), make(false){
}

Human::~Human( void ){
}

void		Human::ft_machin_learning(){

}

void		Human::make_hitBox( void ){

	int			x;
	int			y;

	x = ORIGIN_X;
	y = ORIGIN_Y;
	while (y < (19 * GO_CASE) + ORIGIN_Y)
	{
		Hit_box		*hb = new Hit_box(x, y);
		hb->initiate();
		box.push_back(hb);
		x = x + GO_CASE;
		if (x > (18 * GO_CASE) + ORIGIN_X)
		{
			x = ORIGIN_X;
			y = y + GO_CASE;
		}
	}
	this->make = true;
}

t_pions* Human::put_token(Game& game) {
    t_pions* pions = new t_pions;
    bool quit = false;
    bool continuer = true;
    std::list<Hit_box*>::iterator it;
    Hit_box* tmp;

    pions->player = this->player;

    if (!this->make)
        this->make_hitBox();

    while (continuer) {
        std::optional<sf::Event> eventOpt = game.app->pollEvent();
        if (!eventOpt.has_value())
            continue;

        const sf::Event& event = *eventOpt;

        if (event.is<sf::Event::Closed>()) {
            continuer = false;
            quit = true;
        }

        if (event.is<sf::Event::KeyPressed>()) {
            const auto* keyEvent = event.getIf<sf::Event::KeyPressed>();
            if (keyEvent && keyEvent->code == sf::Keyboard::Key::Escape) {
                continuer = false;
                quit = true;
            }
        }

        if (event.is<sf::Event::MouseButtonPressed>()) {
            const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>();
            if (mouseEvent) {
                it = box.begin();
                while (it != box.end()) {
                    tmp = *it;
                    if (tmp->isOnThebox(mouseEvent->position.x, mouseEvent->position.y)) {
                        pions->x = (tmp->x - ORIGIN_X) / GO_CASE;
                        pions->y = (tmp->y - ORIGIN_Y) / GO_CASE;
                        if (game.whoisHere(pions) == 0 && !game.forbidden(pions)) {
                            continuer = false;
                            break;
                        }
                    }
                    ++it;
                }
            }
        }
    }

    if (quit) {
        game.app->close();
        exit(0);
    }
    return pions;
}


Human		& Human::operator=( Human const &rhs ) {
	this->name = rhs.name;
	this->player = rhs.player;
	return *this;
}
