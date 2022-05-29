#include <iostream>
#include <map>
#include <string>

// Define a map
typedef std::map<int, std::pair<long, char*>> MapType;

// status: work, comment lines 11, 15
void print_map(const MapType& m)
{
	std::cout << "==================\n";
	for (const auto& n : m) {
		std::cout << n.first << ' ' << n.second.first << ' ' << n.second.second << '\n';
	}
	std::cout << "==================";
	std::cout << '\n';
}

// status: work
int hashKey(long ink, int is)
{
	int k = ink % is;
	return k;
}

// status: work
int getFirstEmpty(long ink, int is, const MapType& m)
{
	int k = hashKey(ink, is);

	if (!m.empty()) {

		MapType::const_iterator it;/* = m.find(in);*/

		// unique key

		//for (const auto& n : m) {
		//	if (n.second.first == in)
		//		return -1;
		//}

		int n;
		for (n = k; n < is; ++n) {	// 1st loop range < k,is )

			it = m.upper_bound(n);
			if (it != m.begin())
			{
				it--;
				if (it->first < n)
					return n;
			}
		}
		for (n = 0; n < k; ++n) {	// 2nd loop range < 0,k )

			it = m.find(n);
			if (it == m.end()) // if doesnt exist
				return n;
		}
	}
	return k;
}

// status: work
int getIndex(long ink, int is, const MapType& m)
{
	int a;
	int k = hashKey(ink, is);

	for (const auto& n : m)
		if (n.first >= k && n.second.first == ink) {
			a = n.first;
			return a;
		}
	for (const auto& n : m)
		if (n.first < k && n.second.first == ink) {
			a = n.first;
			return a;
		}
	return -1;
}

// status: doesnt work like it should
// todo: sort all elements
void rewriteIndexes(long ink, int indx, int is, MapType::const_iterator& ite, MapType& m)
{
	bool flag = 0;
	MapType::const_iterator it;
	int del = -1;

	for (const auto& n : m) {

		if (n.first > indx) {
			if (flag == 1 && n.first != indx + 1)
				break;

			if (n.first == indx + 1) {
				it = m.find(n.first);
				int key = hashKey(n.second.first, is);
				if (it != m.end() && indx >= key) {

					del = n.first;
					m[n.first - 1] = std::make_pair(n.second.first, n.second.second);
				}
				++indx;
				flag = 1;
			}
		}
	}
	flag = 0;
	for (const auto& n : m) {

		if (n.first <= indx) {
			if (flag == 1 && n.first != indx + 1)
				break;

			if (n.first == indx + 1) {
				it = m.find(n.first);
				int key = hashKey(n.second.first, is);
				if (it != m.end() && indx >= key) {

					del = n.first;
					m[n.first - 1] = std::make_pair(n.second.first, n.second.second);
				}
				++indx;
				flag = 1;
			}
		}
	}
	if (del != -1) m.erase(del);
}

int main()
{
	// source: https://en.cppreference.com/w/cpp/container/map

	bool end;
	int max;
	std::cin >> max;

	for (int loop = 0; loop < max; ++loop) {

		int isize = 0;
		end = 1;

		// Create a map
		MapType m;

		do {
			std::string sinp;
			std::cin >> sinp;

			if (sinp == "size") {
				int in;
				std::cin >> in;

				if (in != 0)
					isize = in;
			}
			else if (sinp == "add" && isize != 0) {
				long inkey; // should be unique
				std::cin >> inkey;
				char* si = new char[9];
				std::cin >> si; // if key exists change char[9] only

				// todo: unique keys?
				/*int key = hashKey(in, isize);*/
				int fempty = getFirstEmpty(inkey, isize, m);

				if (fempty != -1)
					m.insert(std::make_pair(fempty, std::make_pair(inkey, si)));
			}
			else if (sinp == "delete" && isize != 0) {
				long inkey;
				std::cin >> inkey;

				if (inkey >= 0) {

					int indx = getIndex(inkey, isize, m);
					if (indx != -1) {
						m.erase(indx);

						MapType::iterator it;
						// todo: unique keys, sort all elements
						rewriteIndexes(inkey, indx, isize, it, m);
					}
				}
			}
			else if (sinp == "print" && isize != 0)
				print_map(m);

			else if (sinp == "stop" && isize != 0) {
				m.clear();
				isize = 0;
				end = 0;
			}
		} while (end == 1);
	}
}