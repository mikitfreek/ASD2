#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

#include <ctime>
#include <cstdlib>

/*		Spanning tree		*/

struct Node
{
	std::vector<std::shared_ptr<Node>> nodes;

	int val;
	int n;

	Node() {
		val = 0;
		n = 0;
	}
	Node(int v) {
		val = v;
		n = 0;
	}
	virtual ~Node() = default; //{
	//    std::cout << "Destructing Node:" << val << '\n';
	//}
};
typedef std::shared_ptr<Node> nodeptr;
typedef std::vector<nodeptr> vnode;
typedef std::vector<int> ve;
typedef std::vector<ve> Vec;

/*		Test functions		*/
//void print_ve(ve v) {
//	for (int value : v) {
//		std::cout << value << " ";
//	}
//	std::cout << '\n';
//}
//void print_vec(Vec v) {
//	for (auto ve : v) {
//		print_ve(ve);
//	}
//}
void print_node(nodeptr n) {
	//if (n != nullptr) {
		std::cout << n->val << " - ";

		for (auto m : n->nodes) {
			print_node(m);
			if (m != n->nodes.back()) std::cout << "<" << n->val << ">: ";
		}
	//}
}
void print_vnode(vnode v) {
	//for (auto n : v) {
	for (int i = (int)v.size(); i-- > 0; ) {
		print_node(v[i]);
		std::cout << '\n';
	}
}

//int rng(int a, int b) {
//	int r;
//	r = (rand() % (b - a + 2)) + a + 1;
//	return r;
//}

bool largestOnBack(ve a, ve b) {
	return a[2] < b[2];
}

void changeToOpposite(Vec& a) {
	for (auto& v : a) {
		v[2] *= -1;
	}
}

nodeptr n_tree(int a, int b) {
	nodeptr root(new Node(a));
	nodeptr n = root;
	n->nodes.push_back(nodeptr(new Node(b)));
	return root;
}
void new_tree(vnode& v, ve last) {
	nodeptr root = n_tree(last[0], last[1]);
	v.push_back(root);
}

int DFS_tree(nodeptr n, int a) {
	//if (n != nullptr) {
	if (a == n->val)
		return a;

	for (auto m : n->nodes) {
		int z = DFS_tree(m, a);
		if (z != -1) return z;
	}
	//}
	return -1;
}
int tree_find(vnode& v, int last) {
	int i = 0;
	for (auto n : v) {
		int a = DFS_tree(n, last);
		if (a != -1) return i;
		++i;
	}
	return -1;
}

int DFS_tree_ptr(nodeptr& n, nodeptr& p, int a, int b) {
	//if (n != nullptr) {
	if (a == n->val) {
		p = n;
		return a;
	}
	else if (b == n->val) {
		p = n;
		return b;
	}

	for (auto m : n->nodes) {
		int q = DFS_tree_ptr(m, p, a, b);
		if (q != -1) {
			return q;
		}
	}
	//}
	return -1;
}

void group_trees(vnode& v, int a, int b, int aa, int bb) {
	nodeptr x, y;
	x = v[a]; y = v[b];

	if (x->n <= y->n) {
		y->nodes.push_back(x);

		v.erase(v.begin() + a);
	}
	else {
		x->nodes.push_back(y);

		v.erase(v.begin() + b);
	}

	if (x->n == y->n) y->n++;
}

int find_root(Vec d, int& el, int stops) {
	int tmp, ztmp;
	int z, c;
	for (int n = 1; n <= stops; n++) {
		z = 0;
		for (int i = 0; i <= 1; i++) {
			c = 0;
			for (ve de : d) {
				if ((int)de[i] == n) {
					++z; 
					ztmp = i;
					tmp = c;
				}
				++c;
			}
		}
		if (z == 1) { 
			el = ztmp; return tmp; }
	}
	return -1;
}
int find_node(Vec d, int& el, int n) {
	for (int i = 0; i < 2; i++) {
		int c = 0;
		for (ve de : d) {
			if (de[i] == n) { el = i; return c; }//z++;

			c++;
		}
	}
	return -1;
}

int DFS_tree_ptr(nodeptr& n, nodeptr& p, int a) {
	//if (n != nullptr) {
	if (a == n->val) {
		p = n;
		return a;
	}

	for (auto m : n->nodes) {
		int q = DFS_tree_ptr(m, p, a);
		if (q != -1) {
			return q;
		}
	}
	//}
	return -1;
}


void hey_tree(int stops, Vec& d, vnode& v) {
	Vec _d = d, tmp;

	if (_d.size() > 2) { // do poprawy

	/*		Group trees in forest
			and find edges			*/

		ve last = _d.back();
		tmp.push_back(last);
		_d.pop_back();
		new_tree(v, last);
		//std::cout << ":: " << last[0] << " - " << last[1] << '\n';

		int i = (int)_d.size() - 1;
		bool con = 1;
		int k = 1;
		while (k < stops - 1) {
			last = _d[i];

			int x = last[0], y = last[1];
			int z = (int)v.size();

			int tree_x = tree_find(v, x);
			int tree_y = tree_find(v, y);

			if (tree_x != tree_y || (tree_x == -1 && tree_y == -1))
			{
				if (z < stops)
					new_tree(v, last);

				//std::cout << "+1===========\n";
				//std::cout << ":: " << x << " - " << y << '\n';
				tmp.push_back(last);
				k++;

				tree_x = tree_find(v, x);
				tree_y = tree_find(v, y);
				/*std::cout << "o2=====\n";
				print_vnode(v);*/
				if (tree_x != tree_y && (tree_x != -1 && tree_y != -1)) {
					group_trees(v, tree_x, tree_y, x, y);
					_d.erase(_d.begin() + i);
				}
				/*std::cout << "o3=====\n";
				print_vnode(v);*/
			}
			--i;
			if (i < 0) i = (int)_d.size() - 1;
		}
		//print_vec(tmp);
		//d = tmp;

		v.clear();/*
		for (ve a : tmp)
			new_tree(v, a);*/

			/*		Write trees		*/

			//find node without parent, start adding to it
		int el;

		int root_tree = find_root(tmp, el, stops);
		//root_tree -= 1;
		//std::cout << root_tree << ", " << el << '\n';
		nodeptr nod; //= v[root_tree];
		int n;
		if (el == 0) {
			nodeptr root = n_tree(tmp[root_tree][0], tmp[root_tree][1]);
			nod = root;
			n = tmp[root_tree][1];//v[root_tree]->nodes.front()->val;
		}
		else
		{
			nodeptr root = n_tree(tmp[root_tree][1], tmp[root_tree][0]);
			nod = root;
			n = tmp[root_tree][0];//v[root_tree]->val;
		}
		tmp.erase(tmp.begin() + root_tree);
		//print_node(nod);
		//std::cout << '\n';


		nodeptr z = nod;
		nodeptr ls = nod;
		ve ln;
		//ln.push_back(n);
		//n = tmp.front()[0];
		i = (int)tmp.size() - 1;
		while (tmp.size() > 0) {
			int tree = find_node(tmp, el, n);						/// tu n sie nie zgadza
			//std::cout << tree << ", " << el << '\n';
			if (tree != -1) {
				if (el == 0) {
					int q = DFS_tree(nod, tmp[tree][1]); //v[tree]->nodes.front()->val
					if (q == -1) {
						nodeptr p;
						DFS_tree_ptr(nod, p, tmp[tree][0]);
						p->nodes.push_back(nodeptr(new Node(tmp[tree][1])));
						ln.push_back(n);
						n = tmp[tree][1];
					}
				}
				else
				{
					int q = DFS_tree(nod, tmp[tree][0]); //v[tree]->val
					if (q == -1) {
						nodeptr p;
						DFS_tree_ptr(nod, p, tmp[tree][1]);
						p->nodes.push_back(nodeptr(new Node(tmp[tree][0])));
						ln.push_back(n);
						n = tmp[tree][0];
					}
				}
				tmp.erase(tmp.begin() + tree);
			}
			else {
				if (ln.size() > 0) { n = ln.back(); ln.pop_back(); }//n = ln; //z = ls; 
			}

			//print_node(nod);
			//std::cout << '\n';
		}
		v.clear();
		v.push_back(nod);
	}
	else {
		nodeptr nod;
		ve last = _d.back();
		nodeptr root = n_tree(last[0], last[1]);
		nod = root;
		v.clear();
		v.push_back(nod);

		if (_d.size() != 1) {
			if (d[0][2] < d[1][2]) {
				d.erase(d.end() - 1);
			}
			else d.erase(d.begin());
		}
	}
}

//int DFS_tree_route2(nodeptr n, int r[]) {
//
//}
//
int DFS_tree_route2(nodeptr n, int r, ve& ln) {
	//save min capacity of route
	//if (n != nullptr) {
	ln.push_back(n->val);
	//ln.pop_back();
	if (r == n->val) {
		return r;
	}

	//for (auto m : n->nodes) {
	for (int i = 0; i < (int)n->nodes.size(); ++i) {
		int q = DFS_tree_route2(n->nodes[i], r, ln);
		//std::cout << q << '\n';
		if (q != -1) {
			//ln.pop_back();

			return q;
		}
		else ln.pop_back();

		//for (int k = 0; k < i; k++) ln.pop_back();
	}

	//}
	return -1;
}
// wypisac 2 trasy od root do val
// 
int DFS_tree_route(nodeptr n, int r, ve& ln) {
	ln.push_back(n->val);
	//std::cout << "-" << n->val << " ";
	if (r == n->val) {
		return r;
	}

	//for (auto m : n->nodes) {
	//	int q = DFS_tree_route(m, r, ln);
	for (int i = 0; i < (int)n->nodes.size(); ++i) {
		int q = DFS_tree_route(n->nodes[i], r, ln);
		if (q != -1) {
			//ln.pop_back();
			return q;
		}
		else ln.pop_back();
	}


	//ln.push_back(n->val);

	return -1;
}

int find_weight(Vec d, int a, int b) {
	for (int i = 0; i < (int)d.size(); i++) {
		if ((d[i][0] == a && d[i][1] == b) || (d[i][0] == b && d[i][1] == a))
			return d[i][2] * -1;
	}
	return -1;
}

void print_result(Vec d, nodeptr n, int r[]) {
	int i = 0;
	ve ln0, ln1, tmp0, tmp1;
	int _min;
	int z = find_weight(d, r[0], r[1]);
	if (z != -1) {
		_min = z;
	}
	else {
		// search DFS save min cap
		int q0 = DFS_tree_route(n, r[0], ln0);
		int q1 = DFS_tree_route(n, r[1], ln1);

		//ve tmp0, tmp1;
		if (ln0.size() < ln1.size()) { tmp0 = ln0; tmp1 = ln1; }
		else { tmp0 = ln1; tmp1 = ln0; }

		int st = 0;
		//for (int i = (int)tmp0.size(); i-- > 0; ) {
		for (int i = 0; i < (int)tmp0.size(); ++i)
			if (tmp0[i] != tmp1[i]) st = i - 1;

		std::reverse(tmp0.begin(), tmp0.end());
		std::reverse(tmp1.begin(), tmp1.end());

		for (int i = 0; i <= st; ++i)				tmp0.pop_back();
		for (int i = 0; i < st; ++i)				tmp1.pop_back();
		for (int i = 0; i < (int)tmp0.size(); ++i)	tmp1.push_back(tmp0[i]);

		//print_ve(tmp1);
		//get min from mins cap

		int _m = 1000000;
		for (int i = 0; i < (int)tmp1.size() - 1; ++i) {
			//int a=, int b=;
			int q = find_weight(d, tmp1[i], tmp1[(long long)i + 1]);
			if (q < _m) _m = q;
			//if (q != -1) {
				//q *= -1;
				//if (q < _max) _max = q;
			//}
			//std::cout << i << "\n";
		}
		_min = _m;
	}
	//std::cout << _min << "\n";

	double result = (double)r[2] / ((long long)_min - 1);
	result = std::ceil(result);
	std::cout << result << '\n';
}

int main()
{
	srand((unsigned int)time(NULL));

	int r = 1;
	int a, b, c, d, e, f;


		//Vec data; ve arr, t; int stops = rng(9, 10), tmp;
		//for (int i = 0; i++ < stops; ) {
		//	t.push_back(i);
		//}
		//for (int k = 0; k < stops; ++k) { //i = rnd
		//	for (int i = 0; i < stops; ++i) { //i = rnd
		//		if (i > k) {
		//			tmp = t[k];
		//			std::cout << "g.addEdge(" << tmp;
		//			arr.push_back(tmp);
		//			tmp = t[i];
		//			std::cout << ", " << tmp;
		//			arr.push_back(tmp);
		//			tmp = rng(0, 200);
		//			std::cout << ", " << tmp << ");\n";
		//			arr.push_back(tmp);
		//			data.push_back(arr);
		//			arr.clear();
		//		}
		//	}
		//}


	Vec data;
	int stops;
	std::cin >> stops;
	int roads;
	std::cin >> roads;

	for (int i = 0; i++ < roads; ) {
		std::cin >> d;
		std::cin >> e;
		std::cin >> f;
		ve col = { d, e, f };
		data.push_back(col);
	}

	std::sort(data.begin(), data.end(), largestOnBack);

	changeToOpposite(data); // change sign on d[2]
	vnode datatree;
	hey_tree(stops, data, datatree);

	// ======================

	do {
		a = 0, b = 0;
		std::cin >> a;
		std::cin >> b;
		if (a == 0 && b == 0) return 0;
		std::cin >> c;
		int route[3] = { a, b, c };
		//int route[3] = { 1, stops, 99 };

		//std::cout << "= = = = = =\n";
		//print_vnode(datatree);

		//std::cout << "= = result = =\n";
		print_result(data, datatree.back(), route);

	} while (a != 0 && b != 0);//(e > 0);

	return 0;
}