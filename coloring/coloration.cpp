#include <iostream>                                                    
#include <vector>
#include <stack>
#include <algorithm>
#include <iterator>
#include <time.h>
using namespace std;
using std::vector;
using std::stack;

typedef vector<vector<int> > graphe;


/*

Djamel BENAMARA

g++ -std=c++11 coloration.cpp

Numéroter de 1 à n les sommets selon leur degré décroissant
k=1
tant qu’il existe un sommet non colorié faire :
	colorier avec la couleur k le sommet de plus petit indice
	faire
	
		parmi les sommets non adjacents aux derniers sommets coloriés,
		colorier avec la couleur k celui de plus petit indice
		(parmi ceux qui ne sont pas encore coloriés)
	
	jusqu’à ce qu’il n’y en ait plus
	supprimer les sommets de couleur k du graphe
	k=k+1


*/



bool rep(vector<int> l,int _ran) { //verifie si il y a un doublon dans la liste d adjacence
	for(int i=0;i<l.size();i++) {
		if(l[i] == _ran) {
			return true;
		}
	}
	return false;
}

bool rep2(vector<int> l,int _ran) { //verifie si il y a un doublon dans la liste d adjacence
	for(int i=1;i<l.size();i++) {
		if(l[i] == _ran) {
			return true;
		}
	}
	return false;
}


graphe genererG(int nb_l) {
	graphe g;
	int _ran(0);
	g.resize(nb_l);
	//vector<int> v;//vector pour que le graphe soit non oriente
	for(int i=0;i<nb_l;i++) {
		//g[i].resize(rand()%5+2);
		g[i].push_back(i);
	}

	for(int i=0;i<nb_l;i++) {
		int nb_aretes = rand()%5+2;
		for(int j=g[i].size();j<nb_aretes;j++) {
			do {
				_ran = rand()%nb_l;
			}while(rep(g[i],_ran)); //pour pas de repetitions
		
			g[i].push_back(_ran);
			if(!rep2(g[_ran],g[i][0]))//pour que le graphe soit non oriente
				g[_ran].push_back(g[i][0]);
		}
	}
	return g;
}


void afficher_g(const graphe& g) {
	int nb_l = g.size();
	for(int i=0;i<nb_l;i++) {
		for(int j=0;j<g[i].size();j++)
			cout << g[i][j] << ' ';
		cout << endl;
	}
}

void afficher_v(const vector<int>& v) {
	for(int i=0;i<v.size();i++)
		cout << v[i] << endl;
}

void afficher_c(const graphe& g, const vector<int>& v) {
	for(int i=0;i<v.size();i++) {
		cout << g[i][0] << " : ";
		cout << v[i] << endl;
	}
}



bool nonAdjacent(stack<vector<int> > s, int a) {

	while(!s.empty()) {
		vector<int> tmp = s.top();
		s.pop();
		for(int i=1;i<tmp.size();i++) {
			if(tmp[i] == a)
				return false;
		}
	}
	return true;
}

//Le degré d'un noeud est le nombre de sommet qui lui sont adjacent
int comparedeg(vector<int> a, vector<int> b) {
	return !(a.size()<b.size());

}



vector<int> coloriage(graphe& g) {
	std::sort(g.begin(),g.end(),comparedeg);
	
	stack<vector<int> > s;
	int nb_l = g.size(),couleur(0);
	vector<int> color(nb_l,-1);

	for(int i=0;i<nb_l;i++) {
		if(color[i] == -1) {
			color[i] = couleur; //la couleur actuelle
			s.push(g[i]);
		}
		for(int j=i+1;j<nb_l;j++) {
			if(nonAdjacent(s,g[j][0])) {
				if(color[j] == -1) {
					color[j] = couleur;
					s.push(g[j]);
				}
			}
		}
		while(!s.empty())
			s.pop();

		couleur++;		
	}
	return color;
}






int main() {
	srand(time(NULL));
	graphe g = genererG(10);
	cout << "Random graph " << endl;
	afficher_g(g);
	cout << "------------" << endl;
	cout << "Sorted graph by decreasing degree" << endl;
	vector<int> col = coloriage(g);
	afficher_g(g);
	cout << "------------" << endl;
	cout << "Coloring : " << endl;
	afficher_c(g,col);
	return 0;
}
