#include "eleve.hpp"
#include "fac.hpp"

#define NB_ELEVES 40000 //le nombre d'élèves
#define NB_CHOIX 10 //l'élève à 10 choix
#define NB_FAC 50 //le nombre d'établissments



/*
	Initialise les données des élèves
*/
void init_e(vector<eleve>& e,vector<fac>& f) {
	for(int i=0;i<e.size();i++) {
		e[i].init(i);
		for(int j=0;j<NB_CHOIX;) {
			int choix_fac = rand()%NB_FAC;
			if(e[i].notIn(choix_fac)) {
				e[i].add(choix_fac);
				f[choix_fac].addP(i);
				j++;
			}
		}
	}
}

/*
	Initialise les données des établissements
*/
void init_f(vector<fac>& f) {
	for(int i=0;i<f.size();i++) {
		f[i].init(i);
	}
}

/*
	Affiche un vector d'élèves
*/
void afficher_e(vector<eleve>& e) {
	int i;
	for(i=0;i<e.size();i++) {
		cout << e[i].id() << " : ";
		for(auto& it: e[i].choix())
			cout << it << ' ';
		cout << std::endl;
	}

}


/*
	Affiche un vector de fac
*/
void afficher_f(vector<fac>& f) {
	int i;
	for(i=0;i<f.size();i++) {
		f[i].aff(f[i].admission());
	}
}

void melange(vector<fac>& f) {
	for(int i=0;i<f.size();i++) {
		f[i].melanger();
		
	}
}
/*
pair<int,int>& findAdmisMoinsAime(fac& f) {
	vector<pair<int,int>> tmp;//en first la pos de l'eleve dans m_admis, en second sa pos dans le vector shuffle(m_postulants)
	for(int i=0;i<f.admission().size();i++) {
		for(int j=0; j < f.propositions().size();j++) {
			if(f.propositions()[j] == f.admission()[i])
				tmp.push_back(make_pair(i,j));//pos dans m_admis,pos dans m_postulants
		}
	}
	std::sort(tmp.begin(),tmp.end(), [](pair<int,int> x, pair<int,int> y) {
			return x.second < y.second;
	});
	return tmp.back();
}
*/
bool prefere(fac& f,int pos) { 
	pair<int,int> tmp = f.admission().top();
	return pos < tmp.second;
}

int findpos(fac& f, int ide) {
	for(int i=0;i<f.propositions().size();i++) {
		if(f.propositions()[i] == ide)
			return i;
	}
	return -1;
}

void mariageStable(vector<eleve>& e,vector<fac>& f) {
	double nbSatisfait = 0.0;
	for(int i=0;i<e.size();i++) { //tant que ∃ homme célibataire m qui peut se proposer à une femme w
		//cout << i << endl;
		for(int j=0;j<e[i].choix().size();j++) { //tant que ∃ homme célibataire m qui peut se proposer à une femme w
			int tmp = e[i].choix()[j]; //w = femme préférée de m parmi celles à qui il ne s'est pas déjà proposé
			int pos = findpos(f[tmp],i);
			if(pos == -1)
				exit(1);
			if(f[tmp].admission().size() < f[tmp].nbPlaces()) { //si w est célibataire
				f[tmp].addA(i,pos);//(m, w) forment un couple
				
				if(j==0) {
					e[i].satisfaction() = true;
					nbSatisfait++;
				}
				
				break;
			}
			else { //sinon un couple (m', w) existe
				if(prefere(f[tmp],pos)) { //si w préfère m à m'
					pair<int,int> buff = f[tmp].admission().top();
					if(e[buff.first].satisfaction() == true) {
						nbSatisfait--;
						e[buff.first].satisfaction() = false;
					}
					if(j == 0) {
						e[i].satisfaction() = true;
						nbSatisfait++;
					}

					f[tmp].interchangerA(i,pos);
					break;
				}

			}
		}
	}
	cout << "  TAUX DE SATISFACTION : " << nbSatisfait/(double)e.size()*100 << '%' << std::endl << endl;
}


int main() {
	srand(time(NULL));
	
	vector<eleve> e(NB_ELEVES);
	vector<fac> f(NB_FAC);
	init_f(f);
	init_e(e,f);
	cout << "ELEVES" << std::endl;
	//afficher_e(e);
	cout << "FAC" << std::endl;
	//afficher_f(f);
	cout << "--------RES---------" << std::endl << std::endl;
	melange(f);
	mariageStable(e,f);
	//cout << "APRÈS MARIAGESTABLE" << std::endl << endl;
	//afficher_f(f);
	return 0;


	
}