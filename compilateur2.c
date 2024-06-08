#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Définition des constantes pour les unités lexicales
#define PROGRAM 1
#define ID 2
#define SEMICOLON 3
#define VAR 4
#define INTEGER 5
#define CHAR 6
#define BEGIN 7
#define END 8
#define ASSIGN 9
#define IF 10
#define THEN 11
#define ELSE 12
#define WHILE 13
#define DO 14
#define READ 15
#define READLN 16
#define WRITE 17
#define WRITELN 18
#define OPREL 19
#define OPADD 20
#define OPMUL 21
#define NB 22
#define PPE 23
#define EOF_SYMB 24
#define COLON 25
#define COMMA 26

// Structure pour le stockage des symboles
struct Symbole {
    int UL;        // Unité lexicale
    char att[50];  // Attribut
};

// Structure pour le stockage des identificateurs
struct Identificateur {
    char nom[50];
};
char chaine[50]; 
// Fonction pour initialiser une chaîne de caractères
void Init() {
    memset(chaine, 0, sizeof(chaine));
}

// Fonction pour ajouter un caractère à une chaîne
void Ajouter(char car) {
    strncat(chaine, &car, 1);
}
int debutlex = 0;
// Fonction pour reculer d'un certain nombre de caractères
void Reculer(int n) {
    debutlex -= n;
}

// Fonction pour retourner l'unité lexicale correspondant à un identificateur
int UniLexId() {
    return ID;
}

// Fonction pour lire le caractère suivant
char carsuivant(FILE* file) {
    return fgetc(file);
}

// Fonction pour vérifier si un caractère est une lettre
int isletter(char car) {
    return isalpha(car);
}

// Fonction pour vérifier si un caractère est un chiffre

// Fonction pour gérer les erreurs
void Erreur() {
    printf("Erreur lexique à la position %d\n", debutlex);
    exit(1);
}

// Fonction pour retourner un symbole avec son unité lexicale et attribut
struct Symbole Return(int unit) {
    struct Symbole symbole;
    symbole.UL = unit;
    strcpy(symbole.att, chaine);
    printf("%s %d \n",chaine,unit);
    return symbole;
}

// Fonction pour déterminer si un mot est un mot-clé et retourner son unité lexicale
int EstMotCle(char* mot) {
    if (strcmp(mot, "program") == 0) return PROGRAM;
    else if (strcmp(mot, "var") == 0) return VAR;
    else if (strcmp(mot, "integer") == 0) return INTEGER;
    else if (strcmp(mot, "char") == 0) return CHAR;
    else if (strcmp(mot, "begin") == 0) return BEGIN;
    else if (strcmp(mot, "end") == 0) return END;
    else if (strcmp(mot, "if") == 0) return IF;
    else if (strcmp(mot, "then") == 0) return THEN;
    else if (strcmp(mot, "else") == 0) return ELSE;
    else if (strcmp(mot, "while") == 0) return WHILE;
    else if (strcmp(mot, "do") == 0) return DO;
    else if (strcmp(mot, "read") == 0) return READ;
    else if (strcmp(mot, "readln") == 0) return READLN;
    else if (strcmp(mot, "write") == 0) return WRITE;
    else if (strcmp(mot, "writeln") == 0) return WRITELN;
    else return ID;
}

// Fonction principale de l'analyseur lexical
struct Symbole AnalLex(FILE* file) {
    char car;
    int etat = 0;
    struct Symbole symbole;

    Init();

    while (1) {
        switch (etat) {
            case 0:
                car = carsuivant(file);

                if (car == ' ' || car == '\t' || car == '\n') {
                    etat = 0;
                    debutlex++;
                } else if (car == '<') {
                    etat = 5;
                } else if (car == '=') {
                    etat = 9;
                } else if (car == '>') {
                    etat = 10;
                } else if (isletter(car)) {
                    Ajouter(car);
                    etat = 1;
                } else if (isdigit(car)) {
                    Ajouter(car);
                    etat = 3;
                }else if( car==','){
                    Ajouter(car);
                    symbole = Return(COMMA);
                    return symbole;
                }

                else if (car == ';') {
                    Ajouter(car);
                    symbole = Return(SEMICOLON);
                    return symbole;
                }
                else if (car == ':') {
                    Ajouter(car);
                    symbole = Return(COLON);
                    return symbole;
                }
                else if (car == EOF) {
                    etat = 13;
                } else {
                    Erreur();
                }
                break;

            case 1:
                car = carsuivant(file);

                if (isletter(car) || isdigit(car)) {
                    Ajouter(car);
                } else {
                    etat = 2;
                }
                break;

            case 2:
                Reculer(1);
                //RangerId();
                symbole = Return(EstMotCle(chaine));
                return symbole;
                break;

            case 3:
                car = carsuivant(file);

                if (isdigit(car)) {
                    Ajouter(car);
                } else {
                    etat = 4;
                }
                break;

            case 4:
                Reculer(1);
                symbole = Return(NB);
                return symbole;
                break;

            case 5:
                car = carsuivant(file);

                if (car == '>') {
                    Ajouter(car);
                    etat = 6;
                } else if (car == '=') {
                    Ajouter(car);
                    etat = 7;
                } else {
                    etat = 8;
                }
                break;

            case 6:
                symbole = Return(OPREL);
                return symbole;
                break;

            case 7:
                symbole = Return(OPREL);
                return symbole;
                break;

            case 8:
                Reculer(1);
                symbole = Return(OPREL);
                return symbole;
                break;

            case 9:
                symbole = Return(ASSIGN);
                return symbole;
                break;

            case 10:
                car = carsuivant(file);

                if (car == '=') {
                    Ajouter(car);
                    etat = 11;
                } else {
                    etat = 12;
                }
                break;

            case 11:
                symbole = Return(OPREL);
                return symbole;
                break;

            case 12:
                Reculer(1);
                symbole = Return(OPREL);
                return symbole;
                break;

            case 13:
                symbole = Return(EOF_SYMB);
                return symbole;
                break;
        }
    }
}

// Fonctions pour chaque non-terminal dans la grammaire
void Programme(FILE* file);
void Declaration(FILE* file);
void Liste_id(FILE* file);
void Type(FILE* file);
void Inst_composee(FILE* file);
void Instruction(FILE* file);
void Liste_inst(FILE* file);
void I(FILE* file);
void Exp(FILE* file);
void Exp_simple(FILE* file);
void Terme(FILE* file);
void Facteur(FILE* file);

// Fonction pour ajouter un identificateur à la table des identificateurs
void AjouterIdentificateur(char* nom);

// Fonction pour afficher les erreurs syntaxiques
void ErreurSyntaxique(char* message);

// Fonction principale pour l'analyse syntaxique
void AnalyseSyntaxique(FILE* file) {
    Programme(file);
}

// Table des identificateurs
struct Identificateur tableId[100];
int idxId = 0;

int main() {
    FILE* file = fopen("text.txt", "r");

    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    AnalyseSyntaxique(file);

    fclose(file);
    return 0;
}

// Implémentation des fonctions de l'analyseur syntaxique
void Programme(FILE* file) {
    if (AnalLex(file).UL == PROGRAM) {
        if (AnalLex(file).UL == ID) {
            AjouterIdentificateur(chaine);
            Declaration(file);
            if (strcmp(chaine,"begin")==0){
                Inst_composee(file);
                if (AnalLex(file).UL == SEMICOLON) {
                    if (AnalLex(file).UL != EOF_SYMB) {
                        ErreurSyntaxique("Erreur : Fin de programme non atteinte.");
                    }
                } else {
                        printf("%d\n", AnalLex(file).UL);
                        ErreurSyntaxique("Erreur : ';' attendu après le nom du programme.");
                    }
            } else {
                ErreurSyntaxique("Erreur : Identificateur attendu après le mot clé 'program'.");
            }
        } else {
            printf("%d\n", AnalLex(file).UL);
            ErreurSyntaxique("Erreur : Mot clé 'program' attendu.");
        }
}
}
void Declaration(FILE* file) {
            if (AnalLex(file).UL == SEMICOLON) {
                printf("ouiiii\n");
                if (AnalLex(file).UL == VAR) {
                    Liste_id(file);
                    if (AnalLex(file).UL==COLON) {
                        Type(file);
                        if (AnalLex(file).UL == SEMICOLON) {
                            Declaration(file);
                        } else {
                            ErreurSyntaxique("Erreur : ';' attendu après la déclaration.");
                        }
                    } else {
                        ErreurSyntaxique("Erreur : ':' attendu après la liste des identifiants.");
                    }
                }
            }
}

void Liste_id(FILE* file) {
    printf("listeidddd\n");
    if (AnalLex(file).UL == ID) {
        AjouterIdentificateur(chaine);
        if (AnalLex(file).UL==COMMA) {
            Liste_id(file);
        }
    } else {
        ErreurSyntaxique("Erreur : Identificateur attendu dans la liste.");
    }
}

void Type(FILE* file) {
    if (AnalLex(file).UL == INTEGER || AnalLex(file).UL == CHAR) {
        // Type valide
    } else {
        ErreurSyntaxique("Erreur : Type (integer/char) attendu.");
    }
}
struct Symbole symo;
struct Symbole sym;
void Inst_composee(FILE* file) {
    if (strcmp(chaine,"begin")==0) {
        Liste_inst(file);
        if (symo.UL == END) {
            // Fin de l'instruction composée
        } else {
            ErreurSyntaxique("Erreur : 'end' attendu à la fin de l'instruction composée.");
        }
    } else {
        ErreurSyntaxique("Erreur : 'begin' attendu au début de l'instruction composée.");
    }
}

void Liste_inst(FILE* file) {
    Instruction(file);
    if (symo.UL == SEMICOLON) {
        Liste_inst(file);
    }
}

void Instruction(FILE* file) {
    if (AnalLex(file).UL == ID) {
        if (AnalLex(file).UL == ASSIGN) {
            Exp(file);
        } else {
            ErreurSyntaxique("Erreur : '=' attendu après l'identificateur.");
        }
    } else if (AnalLex(file).UL == IF) {
        Exp(file);
        if (AnalLex(file).UL == THEN) {
            Instruction(file);
            if (AnalLex(file).UL == ELSE) {
                Instruction(file);
            }
        } else {
            ErreurSyntaxique("Erreur : 'then' attendu après la condition 'if'.");
        }
    }

     else if (AnalLex(file).UL == WHILE) {
        Exp(file);
        if (AnalLex(file).UL == DO) {
            Instruction(file);
        } else {
            ErreurSyntaxique("Erreur : 'do' attendu après la condition 'while'.");
        }
    } else if (AnalLex(file).UL == READ || AnalLex(file).UL == READLN ||
               AnalLex(file).UL == WRITE || AnalLex(file).UL == WRITELN) {
        if (AnalLex(file).UL == ID) {
            // L'instruction d'entrée/sortie est valide
        } else {
            ErreurSyntaxique("Erreur : Identificateur attendu après l'instruction d'entrée/sortie.");
        }
    } else {
        ErreurSyntaxique("Erreur : Instruction non reconnue.");
    }
}

void Exp(FILE* file) {
    Exp_simple(file);
    if (symo.UL == OPREL) {
        Exp_simple(file);
    }
}

void Exp_simple(FILE* file) {
    Terme(file);
    if (symo.UL == OPADD) {
        Exp_simple(file);
    }
}

void Terme(FILE* file) {
    Facteur(file);
    symo=AnalLex(file);
    if (symo.UL == OPMUL) {
        Terme(file);
    }
}

void Facteur(FILE* file) {
    sym = AnalLex(file);
    switch (sym.UL) {
        case ID:
        case NB:
            // Facteur valide
            break;
        case PPE:
            Facteur(file);
            break;
        case OPADD:
            Facteur(file);
            break;
        default:
            ErreurSyntaxique("Erreur : Facteur non reconnu.");
            break;
    }
}

int RechercherIdentificateur(char* nom) {
    for (int i = 0; i < idxId; i++) {
        if (strcmp(tableId[i].nom, nom) == 0) {
            // L'identificateur existe déjà dans la table
            return 1;
        }
    }
    // L'identificateur n'existe pas dans la table
    return 0;
}

void AjouterIdentificateur(char* nom) {
    // Vérifier si l'identificateur existe déjà dans la table
    if (RechercherIdentificateur(nom)) {
        // Gérer l'erreur ici, par exemple, vous pourriez choisir de ne pas ajouter l'identificateur ou signaler une erreur
        ErreurSyntaxique("Erreur : L'identificateur existe déjà dans la table.");
        return;
    }

    // Si l'identificateur n'existe pas, l'ajouter à la table
    strcpy(tableId[idxId].nom, nom);
    idxId++;
}


void ErreurSyntaxique(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

