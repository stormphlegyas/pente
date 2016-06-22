#ifndef MINIMAX_HPP
# define MINIMAX_HPP


# include "Node.hpp"
# include <list>
# include <map>
#include <math.h>
#include <time.h>
#include <future>
#include <thread>

class MiniMax
{
	public:
		// bool 	_mybool;
		int 	len;
		int 	nwin;
		int 	decal;
		int 	plop;
		int 	depth;
		int 	Pos_Infinity;
		int 	Neg_Infinity;
		int 	maxNode;
		double 	timeout;
		bool 	overtime;
		clock_t tStart;

		MiniMax(int, Node &);
		// MiniMax();
		void				ft_ia();
		void				Run(bool);


		int 				caller(Node *);
		int 				ft_my_fucking_heuristic(std::array<std::array<char, 15>, 15>, int );
		void 				ft_display_map(std::array<std::array<char, 15>, 15> );
		bool				ft_mod_map(Node & , char , char , char );
		bool 				ft_check_parse_entry(std::string line, Node & );
		bool				ft_check_if_win_D(std::array<std::array<char, 15>, 15> const , char *);
		bool				ft_check_if_win_V(std::array<std::array<char, 15>, 15> const , char *);
		bool				ft_check_if_win_H(std::array<std::array<char, 15>, 15> const , char *);
		bool 				ft_check_if_win(std::array<std::array<char, 15>, 15> const , char *);
		bool				ft_is_finished_for(std::array<std::array<char, 15>, 15> map, char c);

		bool				ft_is_full(std::array<std::array<char, 15>, 15> const );
		int 				ft_eval_H(std::array<std::array<char, 15>, 15> , int , char );
		int 				ft_eval_V(std::array<std::array<char, 15>, 15> , int , char );
		int 				ft_eval_D(std::array<std::array<char, 15>, 15> , int , char );
		int 				ft_eval(std::array<std::array<char, 15>, 15> , int , char );
		int 				ft_MINIMAX_AB_MAX(std::pair<int, Node &>, int, int , int, Node *, int);
		int 				ft_MINIMAX_AB_MIN(std::pair<int, Node &>, int, int , int, Node *, int);


		// int					ft_MiniMax_A_B_Pruning(int , int , int , bool );
		Node				ft_new_state(std::array<std::array<char, 15>, 15>);
		std::multimap<int, Node> 	ft_get_child(std::pair<int, Node &>, bool);
		int 				ft_heuristic(Node &, int);
		int 				ft_MiniMax_A_B_Pruning(std::pair<int, Node &>, int, int, int, bool, Node *, int);
		void 				Display(std::array<std::array<char, 15>, 15> map);
		bool				ft_is_terminal_node(std::array<std::array<char, 15>, 15>, bool);

		virtual ~MiniMax();

	private:
		std::pair<int, Node &> 	State;
		// Node 	State;
		bool 	_isRun;
};

#endif