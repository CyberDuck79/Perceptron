#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>


////structures de donnees
#define coef 2.0	//pente de la fonction sigmoide en zero
#define coed 1.0	//demi-pente (pour l'oprerateur derive)

//#define diment 26	//dimension de l'espace d'entree -> sera lue dans le fichier
#define dimsor 1	//dimension de l'espace de sortie
#define maxcar 50	//nombre maximum de caracteres pour les noms des fichiers

// -- structure d'un neurone --
typedef struct
{
	int		nbent;	//nombre d'entrees du neurone
	double	*x;		//tableau des entrees X
	double	*w;		//tableau des poids W
	double	a;		//activation (somme ponderee des entrees = somme(WiXi))
	double	s;		//sortie (fonction sigmoide de l'activation =f(a))
	double	y;		//gradient
}	strucNeurone;

// -- structure d'une couche --
typedef struct
{
	int			 nbneu;		//nombre de neurones
	strucNeurone *neurone;	//tableau de neurones
}	strucCouche;

// -- structure d'un reseau --
typedef struct
{
	int			nbcou;		//nombre de couches
	strucCouche *couche;	//tableau de couches
}	strucReseau;

// -- base d'exemples --
typedef struct
{
	int		nbex;	//nombre d'exemples
	double	**xx;	//vecteurs des entrees
	double	**sd;	//vecteurs des sorties desirees
}	strucBase;

strucReseau res;	//le reseau MLP

char		nficapp[maxcar];	//nom du fichier d'apprentissage
char		nficgen[maxcar];	//nom du fichier de generalisation
strucBase	app,gen;			//les bases d'apprentissage et de generalisation

char	nresult[maxcar];	//nom du fichier de stockage des resultats
//fichier dans lequel on stockera les parametres et les resultats
FILE	*ficresu;

float	alpha;		//coefficient d'apprentissage (pas de gradient)
int		nbpass;		//nombre de passes de la base d'exemples
int		diment;		//dimension d'entree

////fonctions mathematiques
//fonction sigmoide -- s'applique a l'activation a
double	sigmo(double a)
{
	double	aux = exp(coef * a);
	//fonction impaire, a valeurs dans ]-1;+1[
	return ((aux - 1) / (aux + 1));
}

//operateur derive -- s'applique a la sortie s=f(a)
double	deriv(double fa)
{
	//formule pour calculer f'(a) a partir de f(a)
	return (coed * (1 + fa) * (1 - fa));
}

////procedures d'initialisation
void initNeurone(int i, int k)
{
	int	nbent = res.couche[k - 1].nbneu;

	printf("initialisation du neurone %d de la couche %d\n",i + 1, k);
	res.couche[k].neurone[i].nbent = nbent;
	res.couche[k].neurone[i].x = (double*)malloc(sizeof(double) * nbent);
	res.couche[k].neurone[i].w = (double*)malloc(sizeof(double) * nbent);
	for (int j = 0; j < res.couche[k].neurone[i].nbent; j++)
	{
		//poids initiaux dans [-0.3;+0.3]
		res.couche[k].neurone[i].w[j] = 0.6 * rand()/RAND_MAX - 0.3;
		printf("w[%d,%d,%d]=%lf\t", i, j, k, res.couche[k].neurone[i].w[j]);
	}
}

void	initCouche(int k)
{
	printf("initialisation de la couche %d\n", k);
	if (k == 0)						// couche d'entree
		res.couche[k].nbneu = diment;
	else if (k == res.nbcou - 1)	// couche de sortie
		res.couche[k].nbneu = dimsor;
	else							// couches cachees
	{
		printf("\nNombre de neurones sur la couche cachee %d : ", k);
		scanf("\n%d", &res.couche[k].nbneu);
		fprintf(ficresu, "Nombre de neurones sur la couche cachee %d : %d\n",\
		k, res.couche[k].nbneu);
	}
	res.couche[k].neurone = (strucNeurone*)malloc(sizeof(strucNeurone) * res.couche[k].nbneu);
	if (k > 0) //initialisation de chaque neurone i de la couche k
		for (int i = 0; i < res.couche[k].nbneu; i++)
		{
			printf("\n -- appel initNeurone avec i=%d et k=%d\n", i, k);
			initNeurone(i,k);
		}
}

void	initReseau()
{
	int		nbcach;

	printf("initialisation du reseau MLP\n");
	printf("\nNombre de couches cachees : ");
	scanf("\n%d",&nbcach);
	res.nbcou = nbcach + 2;
	fprintf(ficresu,"Nombre de couches cachees : %d\n", nbcach);
	res.couche = (strucCouche*)malloc(sizeof(strucCouche) * (nbcach + 2));
	for (int k = 0; k < res.nbcou; k++)
	{
		printf("\n -- appel initCouche avec k=%d\n",k);
		initCouche(k);
	}
}

void	initBase(char *nomfich, strucBase *base)
{
	FILE	*fich;

	printf("Lecture des motifs, a partir du fichier %s\n", nomfich);
	fich = fopen(nomfich, "r");
	//le nombre d'exemples est en 1ere ligne du fichier
	fscanf(fich, "%d", &(base->nbex));
	printf("nbex = %d \n", base->nbex);
	//la dim. des entrees est en 2eme ligne du fichier
	fscanf(fich, "%d", &diment);
	printf("diment = %d \n", diment);
	base->xx = (double**)malloc(sizeof(double) * base->nbex);
	base->sd = (double**)malloc(sizeof(double) * base->nbex);
	//on lit, l'un apres l'autre, tous les exemples de la base
	for (int i = 0; i < base->nbex; i++)
	{
		//le vecteur des entrees, suivi de...
		base->xx[i] = (double*)malloc(sizeof(double) * diment);
		for (int j = 0; j < diment; j++)
			fscanf(fich, "%lf", &(base->xx[i][j]));
		//...le vecteur des sorties desirees
		base->sd[i] = (double*)malloc(sizeof(double) * dimsor);
		for (int j = 0; j < dimsor; j++)
			fscanf(fich, "%lf", &(base->sd[i][j]));
	}
	fclose(fich);
	printf("fin de la lecture des motifs\n");
}

////procedures de presentation d'un exemple au reseau
//presentation d'un exemple au reseau
void	prezEntrees(int numex, strucBase base)
{
	/*
	les composantes de l'exemple numex sont les sorties des neurones de la couche 0 du reseau
	*/
	for (int i = 0; i < diment; i++)
		res.couche[0].neurone[i].s = base.xx[numex][i];
}

////procedures de fonctionnement du reseau
//passe avant : calcul de la sortie du reseau, pour l'exemple presente
void	aller()
{
	for (int k = 1; k < res.nbcou; k++)
		for (int i = 0; i < res.couche[k].nbneu; i++)
		{
			res.couche[k].neurone[i].a = 0.0;
			for (int j = 0; j < res.couche[k].neurone[i].nbent; j++)
			{
				res.couche[k].neurone[i].x[j] = res.couche[k-1].neurone[j].s;
				res.couche[k].neurone[i].a += res.couche[k].neurone[i].w[j] * res.couche[k].neurone[i].x[j];
			}
			res.couche[k].neurone[i].s = sigmo(res.couche[k].neurone[i].a);
		}
}

//calcul des gradients d'erreur, sur la couche de sortie
void	gradsor(int numex)
{
	double	dsig;	//derivee de la sigmoide

	for (int i = 0; i < dimsor; i++)
	{
		dsig = deriv(res.couche[res.nbcou-1].neurone[i].s);
		res.couche[res.nbcou-1].neurone[i].y = 2 * dsig * (app.sd[numex][i] - res.couche[res.nbcou-1].neurone[i].s);
	}
}

//passe arriere : calcul des gradients retropropages, dans les couches cachees
void	retour()
{
	double	dsig;
	double	somm;

	for (int k = res.nbcou - 2; k > 0; k--)
		for (int i = 0; i < res.couche[k].nbneu; i++)
		{
			dsig = deriv(res.couche[k].neurone[i].s);
			somm=0.0;
			for(int m = 0; m < res.couche[k+1].nbneu; m++)
				somm += res.couche[k+1].neurone[m].w[i] * res.couche[k+1].neurone[m].y;
			res.couche[k].neurone[i].y = dsig * somm;
		}
}

//mise a jour des poids du reseau (toutes les couches)
void	modifw()
{
	for (int k = 1; k < res.nbcou; k++)
		for (int i = 0; i < res.couche[k].nbneu; i++)
			for (int j = 0; j < res.couche[k].neurone[i].nbent; j++)
				res.couche[k].neurone[i].w[j] += alpha * res.couche[k].neurone[i].y * res.couche[k].neurone[i].x[j];
}

////fonctions d'evaluation des perfromances
//resultat booleen -- version actuelle : pour dimsor = 1
int tstsor(int numex, strucBase base)
{
	/*
	test actuel implemente pour le seul cas ou il n'y a qu'une seule sortie, valant -1 ou +1
	*/
	if (res.couche[res.nbcou-1].neurone[0].s * base.sd[numex][0] > 0)
		return (1);
	else
		return (0);
}

double	tauxSucces(strucBase base)
{
	int nbsuc = 0;

	for (int i = 0; i < base.nbex; i++)
	{
		prezEntrees(i, base);
		aller();
		if (tstsor(i, base) == 1)
			nbsuc++;
	}
	return ((double)(nbsuc / base.nbex));
}

////procedure de controle des processus d'apprentissage et de generalisation
/*
//TODO : change l'ordre de presentation des exemples
void	melange(int n)
{
	//non implemente actuellement
}

//TODO : apprentissage sur nbpass passes de la base d'exemples
void	appren(int nbpass) 
{
	//non implemente actuellement
}

//TODO : teste le reseau sur la base de generalisation
void general()  
{
	//non implemente actuellement
}
*/

//apprentissage avec test en generalisation a chaque passe
void	appgen(int nbpass) 
{
	double	taux;
	for (int p = 0; p < nbpass; p++)
	{
		printf("Passe n. %d\t", p + 1);
		fprintf(ficresu, "Passe n. %d\t", p + 1);
		//une passe d'apprentissage sur toute la base d'exemples
		for (int i = 0; i < app.nbex; i++)
		{
			prezEntrees(i,app);
			aller();
			gradsor(i);
			retour();
			modifw();
		}
		//evaluation du taux de succes en apprentissage
		taux = tauxSucces(app);
		printf("taux app : %lf\t", taux);
		fprintf(ficresu, "taux app : %lf\t", taux);
		//evaluation du taux de succes en generalisation
		taux = tauxSucces(gen);
		printf("taux gen : %lf\n", taux);
		fprintf(ficresu, "taux gen : %lf\n", taux);
	}
}

////programme principal
int		main()
{
	srand(1234);
	double tt1, tt2;

	printf("\nNom du fichier d'apprentissage : ");
	scanf("\n%s", nficapp);
	printf("Nom du fichier de generalisation : ");
	scanf("\n%s", nficgen);
	printf("\nNom du fichier de resultats : ");
	scanf("\n%s", nresult);

	ficresu = fopen(nresult, "w");
	fprintf(ficresu, "Apprentissage sur %s\t", nficapp);
	printf("\n -- appel initBase, pour les donnees d'apprentissage\n");
	initBase(nficapp, &app);
	fprintf(ficresu, "  [ %d exemples ]\n", app.nbex);
	fprintf(ficresu, "Generalisation sur %s\t", nficgen);
	printf("\n -- appel initBase, pour les donnees de generalisation\n");
	initBase(nficgen, &gen);
	fprintf(ficresu, "  [ %d exemples ]\n", gen.nbex);

	printf("\nValeur du pas de gradient : ");
	scanf("%f", &alpha);
	fprintf(ficresu, "alpha=%f\t", alpha);
	printf("Nombre de passes de la base d'exemples : ");
	scanf("%d", &nbpass);
	fprintf(ficresu, "nbpass=%d\n", nbpass);

	fprintf(ficresu, "Taille de la couche d'entree = %d\n", diment);
	fprintf(ficresu, "Taille de la couche de sortie = %d\n", dimsor);
	printf("\n -- appel initReseau\n");
	initReseau();

	printf("\n\nPhase d'apprentissage, avec test en apprentissage et en generalisation, apres chaque passe de la base d'exemples.\n\n");
	tt1 = clock();
	appgen(nbpass);
	tt2 = clock();
	printf("temps--->%f s\n", (tt2 - tt1) * 0.000001);
	fprintf(ficresu, "\ntemps--->%f s\n", (tt2 - tt1) * 0.000001);

	fclose(ficresu);
}