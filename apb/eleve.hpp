#ifndef __BASE__
#define __BASE__

#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

using std::vector;
using std::queue;
using std::priority_queue;
using std::cout;
using std::pair;
using std::make_pair;
using std::endl;

#endif

#ifndef ELEVE
#define ELEVE

class eleve {
public:

	bool notIn(int f) {
		for(int i=0;i<m_facChoisies.size();i++) {
			if(m_facChoisies[i] == f)
				return false;
		}
		return true;
	}

	void init(int id) {
		m_id = id;
		m_satisfait = false;
	}

	int id() {
		return m_id;
	}

	vector<int>& choix() { 
		return m_facChoisies;
	}

	bool& satisfaction() {
		return m_satisfait;
	}

	void add(int n) {
		m_facChoisies.push_back(n);
	}

private:

	int m_id;
	vector<int> m_facChoisies;
	bool m_satisfait; //si il a son premier choix

};
#endif