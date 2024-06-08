#include <stdio.h>
#include <stdlib.h>
#include <string.h>


FILE *fs;
FILE *fd;

// Definir les constantes pour les symboles(lexeme)
#define program 1
#define id 2
#define pv 3
#define pt 4
#define var 5
#define dp 6
#define integer 7
#define chart 8
#define begin 9
#define end 10
#define v 11
#define aff 12
#define iff 13
#define then 14
#define elsee 15
#define read 16
#define readln 17
#define write 18
#define writeln 19
#define po 20
#define pf 21
#define doo 22
#define whilee 23
#define opadd 24
#define oprel 25
#define opmul 26
#define nb 27
#define ppe 28
#define dif 29
#define ppq 30
#define pgq 31
#define pge 32
#define ega 33



void type();
void facteur();
void L();
void D();
void terme();
void exp_simple();
void K();
void exp();
void I();
void C();
void liste_inst();
void Inst();
void Inst_composee();
void liste_id();
void DCL();
void P();

int symbole_courant;

///////////////////////////////////

//sementique


#define MAX_TYPES 100 // Définir la taille maximale de la table des symboles

// Structure pour représenter un symbole dans la table des symboles
typedef struct {
    char* nom;
    char* type;
} Symbole;

Symbole tableSymboles[MAX_TYPES]; // Table des symboles
int nbSymboles = 0; // Nombre de symboles dans la tablet



// Fonction pour vérifier la compatibilité de deux types 1-> les deux identique
int compatible(char* type1, char* type2) {
    return strcmp(type1, type2) == 0;
}

// Fonction pour ajouter un nouveau type à la table des symboles
void ajouter_type(char* nom, char* type) {
    // Vérifier si le type existe déjà dans la table
    for (int i = 0; i < nbSymboles; i++) {
        if (strcmp(tableSymboles[i].nom, nom) == 0) {
            // Le type existe déjà, mise à jour du type existant
            tableSymboles[i].type = type;
            return;
        }
    }

    // Le type n'existe pas, ajouter un nouveau symbole à la table
    if (nbSymboles < MAX_TYPES) {
        tableSymboles[nbSymboles].nom = strdup(nom);
        tableSymboles[nbSymboles].type = strdup(type);
        nbSymboles++;
    } else {
        fprintf(stderr, "Erreur : Table des symboles pleine.\n");
        exit(EXIT_FAILURE);
    }
}

// Fonction pour chercher le type d'un symbole dans la table des symboles
char* chercher_type(char* nom) {
    for (int i = 0; i < nbSymboles; i++) {
        if (strcmp(tableSymboles[i].nom, nom) == 0) {
            // Symbole trouvé, retourner son type
            return tableSymboles[i].type;
        }
    }

    // Symbole non trouvé dans la table
    return NULL;
}

// Fonction pour émettre du code intermédiaire
void emettre(char* ch) {
    FILE* fichier = fopen("codeInterm.txt", "a");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier codeInterm.txt.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(fichier, "%s\n", ch);
    fclose(fichier);
}


/////////////////////////////////






int symbole_suivant()
{
    symbole_courant = analex().ul;
    return symbole_courant;

}

void error() {
    printf("Error!\n");
    strcpy(symbole_courant,symbole_suivant()) ;

}


void accepter(int str)
{
// si le symbole courant est compatible avec la chaine lue,il passe au symbole suivant
    if (symbole_courant==str) symbole_courant=symbole_suivant() ;
    else error();

}

void type()
{

    if(symbole_courant==integer)
    {   // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(integer);
    }
    else {// Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
               }
            accepter(chart);
         }
}

void facteur()
{
    if(symbole_courant==id){
        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(id);
    else if(symbole_courant==nb) {
        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(nb);
    else if(symbole_courant==po)
    {
        {
        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(po);
        exp_simple();

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(pf);
    }

}
void L()
{
    if(symbole_courant==opmul)
    {

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(opmul);
        char* type1 =chercher_type(symbole_courant);
        facteur();
        L();
        char* type2 =chercher_type(symbole_courant);
        if (!compatible(type1,type2)==) {
            printf("Erreur sémantique : Variables non compatibles.\n");
            exit(EXIT_FAILURE);
        }


    }
    else strcpy(symbole,symbole) ;
}
void D()
{
    if(symbole_courant==opadd)
    {
        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(opadd);
        char* type1 =chercher_type(symbole_courant);
        terme();
        D();
        char* type2 =chercher_type(symbole_courant);
        if (!compatible(type1,type2)==) {
            printf("Erreur sémantique : Variables non compatibles.\n");
            exit(EXIT_FAILURE);
        }

    }
    else strcpy(symbole,symbole) ;
}
void terme()
{
    facteur();
    L();
}
void exp_simple()
{
    terme();
    D();
}
void K()
{
    if(symbole_courant==oprel)
    {

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(oprel);
        exp_simple();
    }
    else strcpy(symbole,symbole) ;
}

void exp()
{
    exp_simple();
    K();
}
void I()
{
    if(symbole_courant==id)
    {

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(id);
        emettre(id);

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(aff);
        exp_simple();
    }
    else if(symbole_courant==iff)
    {

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(iff);
        exp();

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(then);
        I();

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(elsee);
        I();
    }
    else if(symbole_courant==whilee)
    {

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(whilee);
        exp();

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(doo);
        I();
    }
    else if(symbole_courant==read)
    {

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(read);

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(po);

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(id);
        emettre(id);

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(pf);
    }



    else if(symbole_courant==readln)
    {

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(readln);

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(po);

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(id) ;
        emettre(id);

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(pf) ;

    }
    else if(symbole_courant==write)
    {

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(write);

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(po);

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(id) ;
        emettre(id);

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(pf) ;

    }
      else if(symbole_courant==writeln)
    {

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(writeln);

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(po);

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(id) ;
        emettre(id);

        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(pf) ;

    }
}
void C()
{
    if(symbole_courant==pv)
    {
        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(pv);
        I();
        C();
    }
    else symbole_courant=symbole_courant ;
}


void liste_inst()
{
    I();
    C();
}
void Inst()
{
    if((symbole_courant==id)||(symbole_courant== iff)||(symbole_courant==whilee||(symbole_courant==readln)||symbole_courant==write)||(symbole_courant==writeln) liste_inst();
    else symbole_courant=symbole_courant;
}
void Inst_composee()
{
        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
    accepter(begin);
    Inst();
    accepter(end);
}
void liste_id()
{
    if(symbole_courant==id)
    {   // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(id);
        emettre(id);
        liste_id();
    }

    else if(symbole_courant==v)
    {
        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(v);
        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(id);
        emettre(id);
        liste_id();
    }
    else symbole_courant=symbole_courant ;
}
void DCL()
{
    if(var==symbole_courant)
    {
        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(var);
        liste_id();
        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(dp);
        ajouter_type(var, type());//table de symbole
        // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
        accepter(pv);
        DCL();
    }
    else symbole_courant=symbole_courant;
}

//axiome de depart
//syntaxique
void P()
{
    // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
    accepter(program);
    // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
    accepter(id);
    emettre(id);//fd
    // Vérifie si l'identifiant a été déclaré.
        char* varType = chercher_type(symbole_courant);
        if (varType == NULL) {
            printf("Erreur sémantique : Variable non déclarée.\n");
            exit(EXIT_FAILURE);
        }
    accepter(pv);
    DCL();
    Inst_composee();
}






/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////



// Analyseur Lexical

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

typedef struct unilex
 {
    int ul;//unite lexical
    int att;//attribut
 } unilex;

int *c = 0;

FILE* fp;


int mot_cle[20]={1,9,5,7,8,10,14,13,15,16,17,18,19,22,23};


char tab_mot_cle[20][20] = {
    "program",
    "begin",
    "var",
    "integer",
    "chart",
    "end",
    "then",
    "if",
    "else",
    "read",
    "readln",
    "write",
    "writeln",
    "do",
    "while" };
char tab_iden[100][20];

char car;

unilex symbole;

char ch[20];
int z = 0;

void reculer(int k) {
    fseek(fp, -k, SEEK_CUR);
}


char carsuivant() {
    return fgetc(fp);
}
//on  le donne lexeme, s'il on le trouve dans le table de symbole on retoune son id, sinon retoune 0
int unilexid() {
    int k = 0;
    int i = 0;
    while (i < 14 && (!k)) {
        if (strcmp(tab_mot_cle[i], ch) == 0) {

            k = 1;
        } else {
            i++;
        }
    }
    if (k == 1){

        return mot_cle[i];
    }
    else {
        return id;
    }
}

//verifie que ch figure dans le tableu de mot cles, sil existe retourne lindice, sinon il lajoute et retourne lindice
int rangerid(int k, int* c) {
    int s = 0;
    if (k == id) {
        while ((strcmp(tab_iden[s], ch) != 0) && (s < (*c)))
        s++;
        if (s < *c) {

            return s;

        } else {
        (*c)++;
        strcpy(tab_iden[*c], ch);
        return *c;
    }}
    else{
        return 0;
    }
}

//implementation de lautomate de la grammaire
unilex analex() {
    int etat = 0;
    int colonne = 0, ligne = 1;
    while (1) {
        switch (etat) {
            case 0:
                car = carsuivant();
                if (car == ' ') {
                colonne++;
                etat = 0;
                } else if (car == '\n') {
                ligne++;
                colonne = 0;
                etat = 0;
                }else if(car=='\t'){
                colonne+=3;
                etat=0;
                }
                else if (isalpha(car)){
                z=0;
                ch[0]=car;

                etat=1;
                }
                else if (isdigit(car)) {
                etat = 3;
                } else if (car == '<') {
                etat = 5;
                } else if (car == '>') {


                    etat = 10;
                } else if (car == '=') {
                etat = 9;
                } else if (car == '$') {
                printf("end of file ");

                etat = 13;
                }else if(car==';'){
                etat=15;
                }
                else if (car==',')
                etat=16;
                else if (car=='(')
                etat=17;
                else if (car==':')
                etat=18;
                else if (car==')')
                etat=19;
                else {
                etat = 14;
                }
                break;
            case 1:
                car = carsuivant();
                if (isalpha(car) || isdigit(car)) {
                z++;
                ch[z] = car;
                } else {
                etat = 2;
                ch[z + 1] = '\0';
                printf("this is the chaine %s",ch);
                z = 0;
                }
                break;
            case 2:
                reculer(1);
                symbole.ul = unilexid();
                symbole.att = rangerid(symbole.ul, &c);
                return symbole;
            case 3:
                reculer(1);
                car = carsuivant();
                if (isdigit(car)) {
                z++;
                ch[z] = car;
                } else {
                etat = 4;
                ch[z + 1] = '\0';
                z = 0;
                }
                break;
            case 4:
                reculer(1);
                symbole.ul = nb;
                symbole.att = atoi(ch);
                return symbole;
            case 5:
                car = carsuivant();
                switch (car) {
                case '=':
                etat = 6;
                break;
                case '>':
                etat = 7;
                break;
                default:
                etat = 8;
                }
                break;
            case 9:
                symbole.ul = oprel;
                symbole.att = ega;
                return symbole;
            case 10:
                reculer(1);
                car = carsuivant();
                if (car == '=') {
                etat = 11;
                } else {
                symbole.ul = oprel;
                symbole.att = pge;
                return symbole;
                }
            case 11:
                symbole.ul = oprel;
                symbole.att = pgq;
                return symbole;
            case 6:
                symbole.ul = oprel;
                symbole.att = ppe;
                return symbole;
            case 7:
                symbole.ul = oprel;
                symbole.att = dif;
                return symbole;
            case 8:
                reculer(1);
                symbole.ul = oprel;
                symbole.att = ppq;
                return symbole;
            case 12:
                symbole.ul = oprel;
                symbole.att = pgq;
                return symbole;
            case 13:
                symbole.ul = 100;
                symbole.att = 0;
                return symbole;
            case 14:

                printf("Erreur : caractère inattendu à la ligne %d, colonne %d\n", ligne, colonne);
                etat=0;
                break;
            case 15:
                symbole.ul=pv;
                symbole.att=0;
                return symbole;
                break;
            case 16:
                symbole.ul=v;
                symbole.att=0;
                return symbole;
                break;
            case 17:
                symbole.ul=po;
                symbole.att=0;
                return symbole;
                break;
            case 18:
                ch[0]=car;
                car=carsuivant();
                if (car=='='){
                symbole.ul=aff;
                symbole.att=0;
                return
                symbole;
                } else{
                etat=20;
                }
                break;
            case 19:
                symbole.ul=pf;
                symbole.att=0;
                return symbole;
                break;
            case 20:
                reculer(1);
                symbole.ul=dp;
                symbole.att=0;
                return symbole;
                break;
        }
    }
}



int main()
{
    fs = fopen("codeSource.txt","rt");//lecture
    if (fs == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier source");
        exit(EXIT_FAILURE);
    }
    fd = fopen("codeInterm.txt","wt");//écriture
    P();//appel fonction
    if (currentSymbol == EOF)
    {
        printf("Analyse syntaxique réussie.\n");
    }
    else
    {
        printf("Erreur syntaxique.\n");
    }
    fclose(fs);
    fclose(fd);
    return 0;
}


