#include "MiniMax.hpp"

MiniMax::MiniMax(int h,Node & n) : State(h,n){
	_isRun = true;
	maxNode = 20;
	nwin = 5;
	decal = 11;//len - 5 (ou 4)
	plop = 0;
	depth = 6;	
	len = (int)(n.getMap()).size();
	Pos_Infinity = std::numeric_limits<int>::max();
	Neg_Infinity = std::numeric_limits<int>::min();
	timeout = 0.5;
	overtime = false;
	tStart = clock();
}

void 		MiniMax::ft_display_map(std::array<std::array<char, 15>, 15> map){// display 3x3 map with coordinates A to C for Y, and 1 to 3 for X

	char	c = 'A';

	std::cout << "  1 2 3 4 5 6 7 8 910111213141516171819" << std::endl << c << ' ';
	for (int i = 0; i < len; ++i){
		for (int j = 0; j < len; ++j){
			if (!map[i][j])
				std::cout << ' ';
			else
				std::cout << map[i][j];
			if (j < (len - 1))
				std::cout << '|';
		}
		std::cout << std::endl;
		if ((int)(c - 64) < len)
			std::cout << " ---------------------------------------" << std::endl << ++c << ' ';
	}
	std::cout << std::endl;
}

bool		MiniMax::ft_mod_map(Node & node, char c, char y, char x){ //write char c at the x, y coordinates in the given vecotr

	if (node.getMap_char_at_XY(x, y) == 0)
		node.setMap_char_at_XY(x, y, c);
	else{
		std::cout << "Thos coordinates are not empty"<< std::endl;
		return (false);
	}
	return (true);
}

bool 		MiniMax::ft_check_parse_entry(std::string line, Node & node){ //check the user input and parse value	
	if (!line.empty()){
		char c1 = line[0];
		if (line.size() == 2){
			char c2 = line[1];
			if ((c1 >= 'A' && c1 <= 'S') && (c2 >= '1' && c2 <= '9')){
				c1 -= 'A';
				c2 -= '1';
				return (ft_mod_map(node, 'X', c1, c2));
			}
		}		
		else if (line.size() == 3){
			char c2 = line[1];
			char c3 = line[2];
			if ((c1 >= 'A' && c1 <= 'S')
				&& (c2 >= '1' && c2 <= '9')
				&& (c3 >= '0' && c3 <= '9')){
				c1 -= 'A';
				c2 -= '1';	
				// c3 -= '1';
				c2 += 10 + (c3 - '0' - 1);
				return (ft_mod_map(node, 'X', c1, c2));
			}
		}
	}
	std::cout << "invalide input\nusage :[A...S][1...19]" << std::endl;
	return (false);
}

bool		MiniMax::ft_check_if_win_D(std::array<std::array<char, 15>, 15> const map, char *p){
	char 	c = 1;
	int 	count = 0;

	for (int i = 0; i < decal; ++i){ //only first diagonal where we can have at leat anough place
		count = 0;
		if (map[0][0+i] != 0)
			c = map[0][0+i];
		for (int j = 0; j < len - i; ++j){
			if (map[j][j+i] != 0 && map[j][j+i] == c){
				count++;
				// std::cout << "A" << std::endl;
				if (count == nwin){
					*p = c;
					return (true);
				}
			}
			else{
				c = map[j][j+i];
				count = 1;
			}
		}
		count = 0;
		if (map[0+i][0] != 0)
			c = map[0+i][0];
		for (int j = 0; j < len - i; ++j){
			if (map[j+i][j] != 0 && map[j+i][j] == c){
				// std::cout << "B" << std::endl;
				count++;
				if (count == nwin){
					*p = c;
					return (true);
				}
			}
			else{
				c = map[j+i][j];
				count = 1;
			}
		}
	}

	count = 0;
	for (int k = 0; k < decal; ++k){ //only first diagonal where we can have at leat anough place
		int j = 0;
		if (map[0][len - 1 - k] != 0)
			c = map[0][len - 1 - k];
		for (int i = (len - 1); i >= k; --i){
			if (map[j][i-k] != 0 && map[j][i-k] == c){
				// std::cout << int(count) << std::endl;
				count++;
				if (count == nwin){
					*p = c;
					return (true);
				}
			}
			else{
				c = map[j][i-k];
				count = 1;
			}
			j++;
		}
		count = 0;
		j = 0;
		if (map[0+k][len - 1] != 0)
			c = map[0+k][len - 1];
		for (int i = (len - 1); i >= k; --i){
			if (map[j+k][i] != 0 && map[j+k][i] == c){
				count++;
				if (count == nwin){
					*p = c;
					return (true);
				}
			}
			else{
				c = map[j+k][i];
				count = 1;
			}
			j++;
		}
	}
	return (false);
}

bool		MiniMax::ft_check_if_win_V(std::array<std::array<char, 15>, 15> const map, char *p){
	char 	c = 1;

	for (int i = 0; i < len; ++i){
		int 	count = 0;
		if (map[0][i] != 0)
			c = map[0][i];
		for (int j = 0; j < len; ++j){
			if (map[j][i] != 0 && map[j][i] == c){
				count++;
				if (count == nwin){
					*p = c;
					return (true);
				}
			}
			else {
				c = map[j][i];
				count = 1;
			}
		}
	}
	return (false);
}


bool		MiniMax::ft_check_if_win_H(std::array<std::array<char, 15>, 15> const map, char *p){
	char 	c = 1;
	// int 	nwin = 5;

	for (int i = 0; i < len; ++i){
		int 	count = 0;
		if (map[i][0] != 0)
			c = map[i][0];
		for (int j = 0; j < len; ++j){
			if (map[i][j] != 0 && map[i][j] == c){
				count++;
				if (count == nwin){
					*p = c;
					return (true);
				}
			}
			else{
				c = map[i][j];
				count = 1;
			}
		}
	}
	return (false);
}

bool		MiniMax::ft_is_full(std::array<std::array<char, 15>, 15> const map){
	// std::find(std::begin(array), std::end(array), someObject);

	for (int i = 0; i < len; ++i){
		if (std::find(map[i].begin(), map[i].end(), 0) != map[i].end())
			return (false);
	}
	return (true);
}


// 0000XX0XX


bool	MiniMax::ft_is_finished_for(std::array<std::array<char, 15>, 15> map, char c){
	int count = 0;
	int p = 0;
	for (int i = 0; i < len; ++i){
		count = 0;
		for (int j = 0; j < len; ++j){
			if (map[j][i] == c){
				count++;
				if (count == nwin)
					return (true);
			}
			else
				count = 0;
		}
	}
	count = 0;
	for (int i = 0; i < len; ++i){
		count = 0;
		for (int j = 0; j < len; ++j){
			if (map[i][j] == c){
				count++;
				if (count == nwin)
					return (true);
			}
			else
				count = 0;
		}
	}
	count = 0;
	for (int k = 0; k < decal; ++k){
		count = 0;
		for (int i = 0; i < len - k; ++i){
			if (map[i][i+k] == c){
				count++;
				if (count == nwin)
					return (true);
			}
			else
				count = 0;
		}
		count = 0;
		p = 0;
		for (int i = len - 1; i >= k; --i){
			if (map[p][i-k] == c){
				count++;
				if (count == nwin)
					return (true);
			}
			else
				count = 0;
			p++;
		}
		if (k == 0)
			continue;
		count = 0;
		for (int i = 0; i < len - k; ++i){
			if (map[i+k][i] == c){
				count++;
				if (count == nwin)
					return (true);
			}
			else
				count = 0;
		}
		p = 0;
		count = 0;
		for (int i = len - 1; i >= k; --i){
			if (map[i][p+k] == c){
				count++;
				if (count == nwin)
					return (true);
			}
			else
				count = 0;
			p++;
		}
	}
	return (false);

}


//OK
int 	MiniMax::ft_eval_H(std::array<std::array<char, 15>, 15> map, int n, char c){
	int 	ret = 0;
	bool 	joker = false;
	for (int i = 0; i < len; ++i){
		int count = 0;
		for (int j = 0; j < len; ++j){
			if (joker && map[i][j] == 0)
				joker = false;
			else if (map[i][j] == c && count == 0 && j > 0 && map[i][j-1] == 0){
				count++;
				joker = true;
			}
			else if (count != 0 && map[i][j] == c){
				count++;
				if (count == n && j < (len-1) && map[i][j+1] == 0)
					ret += 1;
				// else if (count == n && !joker)
				// 	ret++;
			}
			else{
				joker = false;
				count = 0;
			}
		}
	}
	return (ret);
}

//OK
int 	MiniMax::ft_eval_V(std::array<std::array<char, 15>, 15> map, int n, char c){
	int 	ret = 0;
	bool 	joker = false;
	for (int i = 0; i < len; ++i){
		int count = 0;
		for (int j = 0; j < len; ++j){
			if (joker && map[j][i] == 0)
				joker = false;
			else if (map[j][i] == c && count == 0 && j > 0 && map[j-1][i] == 0){
				joker = true;
				count++;
			}
			else if (count != 0 && map[j][i] == c){
				count++;
				if (count == n && j < (len-1) && map[j+1][i] == 0)
					ret += 1;
				// else if (count == n && !joker)
				// 	ret++;
			}
			else{
				joker = false;
				count = 0;
			}
		}
	}
	return (ret);
}

//WRONG
int 	MiniMax::ft_eval_D(std::array<std::array<char, 15>, 15> map, int n, char c){
	int 	ret = 0;
	int 	count = 0;
	bool 	joker = false;
	int 	p = 0;
	
	for (int k = 0; k < decal; ++k){
		count = 0;
		joker = false;
		for (int i = 0; i < len - k; ++i){ //start up left -> down right toward up right
			if (joker && map[i][i+k] == 0)
				joker = false;
			else if (map[i][i+k] == c && count == 0){
				if ((i > 0 && map[i-1][i+k-1] == 0)){
					joker = true;
					count++;
				}
			}
			else if (count != 0 && map[i][i+k] == c){
				count++;
				if (count == n && i < (len - 1 - k) && map[i+1][i+k+1] == 0)
					ret += 1;
				// else if (count == n && !joker)
				// 	ret++;
				// std::cout <<"A" << std::endl;
			}
			else{
				joker = false;
				count = 0;
			}
		}
		if (k == 0)
			continue;
		count = 0;
		joker = false;
		for (int i = 0; i < len - k; ++i){  //start up left -> down right toward down left
			if (joker && map[i+k][i] == 0)
				joker = false;
			else if (map[i+k][i] == c && count == 0){
				if ((i > 0 && map[i+k-1][i-1] == 0)){
					joker = true;
					count++;
				}
			}
			else if (count != 0 && map[i+k][i] == c){
				count++;
				if (count == n && i < (len-1-k) && map[i+k+1][i+1] == 0)
					ret += 1;
				// else if (count == n && !joker)
				// 	ret++;
				// std::cout <<"B" << std::endl;
			}
			else{
				joker = false;
				count = 0;
			}
		}
	}
	count = 0;
	joker = false;
	// bool fre = false;
	for (int k = 0; k < decal; ++k){ 
		p = 0;
		count = 0;
		joker = false;

		for (int i = len - 1 - k; i >= 0; --i){ //start up right -> down left toward left up
			// std::cout << int(p) << ":" << int (i) << std::endl;
			if (joker && map[p][i] == 0)
				joker = false;
			else if (map[p][i] == c && count == 0){
				if (p > 0 && (i < (len - 1) && map[p-1][i+1] == 0)){//bof
					joker = true;
					count++;
				}
			}
			else if (count != 0 && map[p][i] == c){
				count++;
				if (count == n && p < (len-1-k) && i > 0 && map[p+1][i-1] == 0){
					ret += 1;
					// std::cout << "HEHE" << std::endl;
				}
				// if (count == n && !joker){
					// std::cout << "HEHE2" << std::endl;
				// 	ret++;
				// }
				// std::cout <<"3" << std::endl;
			}
			else{
				joker = false;
				count = 0;
			}
			p++;
		}
		if (k == 0)
			continue;
		count = 0;
		joker = false;
		p = 0;
		for (int i = len - 1; i >= k; --i){ //start up right -> down left toward down right //PRETY SPACE
			if (joker && map[p+k][i] == 0)
				joker = false;
			else if (map[p+k][i] == c && count == 0){
				if ((p > 0 && i < (len-1) && map[p+k-1][i+1] == 0)){
					joker = true;
					count++;
				}
			}
			else if (count != 0 && map[p+k][i] == c){
				count++;
				if (count == n && i > 0 && p + k < (len - 1) && map[p+k+1][i-1] == 0)
					ret += 1;
				// else if (count == n && !joker)
				// 	ret++;
				// std::cout <<"4" << std::endl;
			}
			else{
				joker = false;
				count = 0;
			}
			p++;
		}
	}
	return (ret);
}


int 	MiniMax::ft_eval(std::array<std::array<char, 15>, 15> map, int n, char c){
	int sum_h = 0;
	int sum_v = 0;
	int sum_d = 0;

	sum_h = ft_eval_H(map, n , c);
	// if (sum_h != 0)
		// std::cout << "SUM H" << std::endl;
	sum_v = ft_eval_V(map, n , c);
	// if (sum_v != 0)
		// std::cout << "SUM V" << std::endl;
	sum_d = ft_eval_D(map, n , c);
	// if (sum_d != 0)
		// std::cout << "SUM D" << std::endl;
	return (sum_h + sum_v + sum_d);
	// return (ft_eval_D(map, n, c) + ft_eval_H(map, n, c) + ft_eval_V(map, n, c));
	// if (ft_eval_H(map, n, c))
	// 	std::cout << "EVAL H ";
	// else if (ft_eval_V(map, n, c))
	// 	std::cout << "EVAL V ";
	// return (0);
	// return (ft_eval_H(map, n, c) + ft_eval_V(map, n, c) + ft_eval_D(map, n, c));
	// return (ft_eval_H(map, n, c) + ft_eval_V(map, n, c));// + ft_eval_D(map, n, c));
	// return (ft_eval_D(map, n, c));
	// return (/*ft_eval_H(map, n, c) +*/ ft_eval_H(map, n, c));// + ft_eval_D(map, n, c));
	// return (ft_eval_H(map, n, c) + ft_eval_V(map, n, c));
}

bool 		MiniMax::ft_check_if_win(std::array<std::array<char, 15>, 15> const map, char *p){
	// if (ft_check_if_win_H(map, p)){
	// 	// std::cout << "WIN in H" << std::endl;
	// 	return (true);
	// }
	// if (ft_check_if_win_V(map, p)){
	// 	// std::cout << "WIN in V" << std::endl;
	// 	return (true);
	// }
	(void)p;
	if (ft_is_finished_for(map, 'O'))//optimizable
		return (true);
	if (ft_is_finished_for(map, 'X'))//optimizable
		return (true);
	// if (ft_check_if_win_D(map, p)){
	// 	// std::cout << "WIN in D" << std::endl;
	// 	return (true);
	// }
	return (false);
}

bool		MiniMax::ft_is_terminal_node(std::array<std::array<char, 15>, 15> const map, bool flag){
	char 	p = 0;
	if (ft_check_if_win(map, &p)){
		if (p == 'O')
		if (flag == true){
			std::cout << "GAME OVER " << p << " WINS" << std::endl;
			sleep(1);
		}
		return (true);
	}
	// if (ft_is_full(map)){
	// 	if (flag == true)
			// std::cout << "GAME OVER Draw" << std::endl;
	// 	return (true);
	// }
	return (false);
}

Node 			MiniMax::ft_new_state(std::array<std::array<char, 15>, 15> map_tmp)
{
	Node 		state;
	
	state.setMap(map_tmp);
	return state;
}

std::multimap<int,Node> MiniMax::ft_get_child(std::pair<int,Node &> node, bool MaxP)
{
  	std::multimap<int, Node> myhash;
  	Node 		*tmp_state = new Node();
  	std::array<std::array<char, 15>, 15> map = node.second.getMap();
  	for (int i = 0; i < len; ++i){
  		for (int j = 0; j < len; ++j){
  			if (map[i][j] == 0){
  				if ((j > 0 && map[i][j-1] != 0) ||
  					(j < len - 1 && map[i][j+1] != 0) ||
  					(i > 0 && map[i-1][j] != 0) ||
  					(i < len - 1 && map[i+1][j] != 0) ||
  					(i < len - 1 && j > 0 && map[i+1][j-1] != 0) ||
  					(i > 0 && j < len - 1 && map[i-1][j+1] != 0) ||
  					(i > 0 && j > 0 && map[i-1][j-1] != 0) ||
  					(i < len - 1 && j < len - 1 && map[i+1][j+1] != 0)) {

	  				std::array<std::array<char, 15>, 15> tmp = map;
	  				if (!MaxP)
	  					tmp[i][j] = 'O';
	  				else
	  					tmp[i][j] = 'X';

	  				*tmp_state = ft_new_state(tmp);

	  				myhash.insert(std::pair<int, Node>(ft_heuristic(*tmp_state, 0), *tmp_state)); 
  				}
  			}
   		}
  	}
  	return (myhash);
}



int 	MiniMax::ft_my_fucking_heuristic(std::array<std::array<char, 15>, 15> map, int gamma){
	// if (ft_eval(map, 3 , 'X') > 0)
	// char c = 'O';
	// char p1 = 'X';
	if (ft_is_finished_for(map, 'O')){//optimizable
		// std::cout << "EVAL MAX O win" << std::endl;
		return (-10000 - gamma);
	}
	if (ft_is_finished_for(map, 'X')){//optimizable
		// std::cout << "EVAL MAX X win" << std::endl;
		return (10000 + gamma);
	}
	// return (0);
	// return (3 * ft_eval(map, 2, 'X') + ft_eval(map, 1, 'X') 
	// 	- (3 * ft_eval(map, 2, 'O') + ft_eval(map, 1, 'O')));

	// return (4 * ft_eval(map, 3, 'X') + ft_eval(map, 2, 'X') + ft_eval(map, 1, 'X') 
	// 	- (4 * ft_eval(map, 3, 'O') + ft_eval(map, 2, 'O') + ft_eval(map, 1, 'O')));

	// std::cout << "ft_eval(4,X) = " << int(ft_eval(map,4,'X')) << std::endl;
	// std::cout << "ft_eval(4,O) = " << int(ft_eval(map,4,'O')) << std::endl;
	// std::cout << "ft_eval(3,X) = " << int(ft_eval(map,3,'X')) << std::endl;
	// std::cout << "ft_eval(3,O) = " << int(ft_eval(map,3,'O')) << std::endl;
	// std::cout << "ft_eval(2,X) = " << int(ft_eval(map,2,'X')) << std::endl;
	// std::cout << "ft_eval(2,O) = " << int(ft_eval(map,2,'O')) << std::endl;

	return ((200 * ft_eval(map, 4, 'X')) + (75 * ft_eval(map, 3, 'X')) 
		- ((200 * ft_eval(map, 4, 'O')) + (75 * ft_eval(map, 3, 'O'))
			));
}

int 	MiniMax::ft_heuristic(Node & node, int gamma){
	// return (0);
	// (void)gamma;
	// (void)node;
	// int x = ft_my_fucking_heuristic(node.getMap(), gamma*20);
	// std::cout << "ft_heuristic = " << int(x) << std::endl;
	// return (x);
	return (ft_my_fucking_heuristic(node.getMap(), gamma*20));
}

int 	MiniMax::ft_MINIMAX_AB_MAX(std::pair<int,Node&> root, int depth, int a, int b, Node *tmp_n, int bkp_depth){
	std::multimap<int, Node> hash_child;

	if (overtime)
		return (0);

	// if ((overtime || static_cast<double>(clock() - tStart)/CLOCKS_PER_SEC) > timeout)
	// {
	// 	overtime = true;
	// 	return (0);
	// }

	hash_child = ft_get_child(root, true);
	// int i = 0;
	int delta = a;
	for (std::multimap<int,Node>::reverse_iterator it = hash_child.rbegin(); it != hash_child.rend(); it++){
	// if (i == maxNode)
	// 	break;
		delta = ft_MiniMax_A_B_Pruning(*it, depth-1, a, b, false, tmp_n, bkp_depth);
		if (delta > a){
			if (depth == bkp_depth)
				*tmp_n = it->second;
			a = std::max(a, delta);
		}
		if (a >= b)
			break;
		// i++;
	}
	return (a);
}

int 	MiniMax::ft_MINIMAX_AB_MIN(std::pair<int,Node&> root, int depth, int a, int b, Node *tmp_n, int bkp_depth){
	std::multimap<int, Node> hash_child;

	if (overtime)
		return (0);
	// if ((overtime || static_cast<double>(clock() - tStart)/CLOCKS_PER_SEC) > timeout)
	// {
	// 	overtime = true;
	// 	return (0);
	// }
	hash_child = ft_get_child(root, false);
	// int i = 0;
	int delta = b;
	for (std::multimap<int,Node>::iterator it = hash_child.begin(); it != hash_child.end(); it++){
		// if (i == maxNode)
		// 	break;
		delta = ft_MiniMax_A_B_Pruning(*it, depth-1, a, b, true, tmp_n, bkp_depth);
		if (delta < b){
			if (depth == bkp_depth)
				*tmp_n = it->second;
			b = std::min(b, delta);
		}
		if (a >= b)
			break;
		// i++;
	}
	return (b);
}

int 	MiniMax::ft_MiniMax_A_B_Pruning(std::pair<int, Node &> root, int depth, int a, int b, bool MaximizingPlayer, Node *tmp_n, int bkp_depth){
	plop += 1;

	if (overtime)
		return (0);
// if ((overtime || static_cast<double>(clock() - tStart)/CLOCKS_PER_SEC) > timeout)
	// {
	// 	overtime = true;
	// 	return (0);
	// }
	if (depth == 0 || ft_is_terminal_node(root.second.getMap(), false)){
		// 	// std::cout << "USED" << std::endl;
		// 	// sleep(1);
		// 	MiniMax::ft_display_map(tmp_n->getMap());
			// _isRun = false;
		// 	exit(0);
		// }
		// return(0);
		// std::cout << int(root.first) << std::endl;
		return(root.first);
		// return ft_heuristic(root, (depth - bkp_depth));
	}
	if (MaximizingPlayer)
		return (ft_MINIMAX_AB_MAX(root, depth, a, b, tmp_n, bkp_depth));
	else
		return (ft_MINIMAX_AB_MIN(root, depth, a, b, tmp_n, bkp_depth));
}

int MiniMax::caller(Node *tmp){
	int testdepth = 0;
	// , depth, Neg_Infinity, Pos_Infinity, false, tmp, depth
	while (testdepth++ < 20){
		// testdepth
		std::cout << "minimax = " << int(ft_MiniMax_A_B_Pruning(State, testdepth, Neg_Infinity, Pos_Infinity, false, tmp, testdepth)) << std::endl;
	}
	return (0);
}
// std::pair<int, Node &> root, int depth, int a, int b, bool MaximizingPlayer, Node *tmp_n, int bkp_depth)

int tot(){
	return (0);
}


void 	MiniMax::ft_ia(){
	plop = 0;

	Node *tmp = new Node();
	tmp->setMap(State.second.getMap());
	// int d = 1;

	overtime = false;
	tStart = clock();
	std::future<int>  hThread(std::async(std::launch::async, &MiniMax::caller, this, tmp));
	// ...
	// Terminate the thread.
	if (hThread.wait_for(std::chrono::milliseconds(500)) == std::future_status::timeout) {
		std::cout << "QUIT" << std::endl;
		overtime = true;
		// sleep(1);
	}
	// while ((static_cast<double>(clock() - tStart)/CLOCKS_PER_SEC) < timeout){
		// d = d + 1;
		// depth = d;
		// std::cout.precision(4);
		// printf("%.2f", static_cast<double>(clock() - tStart)/CLOCKS_PER_SEC );
		// std::cout << "while" << std::endl;
		// if (!gameover)
		// std::cout << "minimax = " << int(ft_MiniMax_A_B_Pruning(State, depth, Neg_Infinity, Pos_Infinity, false, tmp, depth)) << std::endl;
		// std::cout << "==============" << std::endl;
		// std::cout << "plop = " << int(plop) << std::endl;
		// printf("%.2f", static_cast<double>(clock() - tStart)/CLOCKS_PER_SEC );
		// std::cout << static_cast<double>(clock() - tStart)/CLOCKS_PER_SEC << std::endl;
	// }

	ft_display_map(tmp->getMap());
	State.second.setMap(tmp->getMap());
	std::cout << "TAMERE heuristic = " << int(ft_heuristic(State.second, 0)) << std::endl;
	if (ft_is_terminal_node(State.second.getMap(), true)){
		ft_display_map(State.second.getMap());
		_isRun = false;
	}
	return ;
}

void 	MiniMax::Run(bool p){
	std::string 	line;

	if (!p)
		State.second.setMap_char_at_XY(len/2, len/2, 'O');
		// ft_ia();
	while (_isRun){
		while ("Your Trun"){
			ft_display_map(State.second.getMap());
			std::cout << "Your turn:";
	 		getline (std::cin, line);
	 		if (ft_check_parse_entry(line, State.second))
	  			break;
 			if (ft_is_terminal_node(State.second.getMap(), true)){
				ft_display_map(State.second.getMap());
				_isRun = false;
			}
		}		
		ft_ia();
	}
}

void MiniMax::Display(std::array<std::array<char, 15>, 15> map){
	// char p = 'X';
	ft_display_map(State.second.getMap());
	if (ft_is_finished_for(map, 'X'))
		std::cout << "FINISHED" << std::endl;

	(void)map;
}

MiniMax::~MiniMax(){

}
