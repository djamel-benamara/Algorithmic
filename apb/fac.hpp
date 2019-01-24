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

#ifndef __FAC__
#define __FAC__
#define NB_PLACES_MIN 500 //le nombre min d'élèves que la fac peut choisir
#define NB_PLACES_MAX 1000 //le nombre max d'élèves que la fac peut choisir

/*
	Pour redéfinir la façon de gérer la priority_queue
*/
class comparePQ {
public:
    bool operator()(pair<int,int> x,pair<int,int> y) {
        return x.second < y.second;
    }
};



class fac {
public:

	bool notIn(int e) {
		for(int i=0;i<m_postulants.size();i++) {
			if(m_postulants[i] == e)
				return false;
		}
		return true;
	}

	void init(int id) {//on lui envoie tous en params pour 
		m_id = id;
		m_nbPlaces = rand()%(NB_PLACES_MAX-NB_PLACES_MIN+1) + NB_PLACES_MIN;
	}

	int id() {
		return m_id;
	}

	int nbPlaces() {
		return m_nbPlaces;
	}

	vector<int>& propositions() {
		return m_postulants;
	}

 	priority_queue<pair<int,int>,vector<pair<int,int>>,comparePQ>& admission() {
		return m_admis;
	}

	void addP(int& ide) {//ajout dans postulant
		m_postulants.push_back(ide);
	}

	void addA(int ide,int pos) {//ajout dans admis
		m_admis.push(make_pair(ide,pos));
	}

	/*void addAt(int pos, int i) {
		if(pos > m_admis.size())
			m_admis.resize(pos+1);
		m_admis[pos] = i;
	}*/

	void removeA() {
		m_admis.pop();
	}

	void melanger() {
		std::random_shuffle ( m_postulants.begin(), m_postulants.end() );
	}

	void interchangerA(int ide, int pos) {
		//std::swap(m_admis[posx],m_admis[m_admis.size()-1]);
		m_admis.pop();
		m_admis.push(make_pair(ide,pos));
	}

	/*void calculerRes() {
		for(int i=0;i<m_postulants.size();i++) {
			m_postulants[i].second += i;
		}
	}*/

	/*void tri() {
		std::sort(m_postulants.begin(),m_postulants.end(), [](pair<int,int> x, pair<int,int> y) {
			return x.second < y.second;
		});
	}*/

	void redimensionner() {
		m_postulants.resize(m_nbPlaces);
	}

	void aff(priority_queue<pair<int,int>,vector<pair<int,int>>,comparePQ> pq) {
		cout << "fac " << m_id << " a " << m_nbPlaces << " places :" << std::endl;
		cout << "Postulants : ";
		for(int i=0;i<m_postulants.size();i++)
			cout << m_postulants[i] << ' ';
		cout << std::endl << "Admis : ";
		vector<pair<int,int>> tmp;
		while(!pq.empty()) {
			pair<int,int> buff = pq.top();
			pq.pop();
			tmp.push_back(buff);
		}
		for(int i = tmp.size()-1;i>=0;i--) {
			cout << tmp[i].first << ' ';

			//cout << m_admis[i] << ' ';
		}
		cout << std::endl << std::endl;
	}

private:

   	int m_id; //plutôt que de garder des noms on garde un id
   	int m_nbPlaces;
   	vector<int> m_postulants;//les postulants
   	priority_queue<pair<int,int>,vector<pair<int,int>>,comparePQ> m_admis;//les admis
   	//en first l'id de l'élève et en second sa position dans postulants
};

#endif