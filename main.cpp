#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <array>
#include <vector>
#include <cstdlib>





using namespace std;


// Table de symboles
struct TS {
    int* type = new int[200]; // type=1 -> int, type=2 -> int[], type=3 -> int[][], type=4 -> int(), type=5 -> void()
    int* etat = new int[200]; // etat=1 -> declar�, etat=2 -> initialis�
    // S'il s'agit d'une fonction, elle ne peut �tre que d�clar�e
    int* blok = new int[200]; // stocker le idblock de chaque block
    int* nbrpar = new int[200]; // nbrpar des fct
    string* nom = new string[200]; // nom de l'identificateur
    int nbre = 0; // nbre d'identificateurs

};


// pile pour stocker les idblock , une fois on sort d'un bloc on fait appelle � pop

struct Noeud {
    int val;
    Noeud* suivant; // Pointeur vers le prochain �l�ment dans la pile
};

class pile {
private:
    Noeud* sommet; // Pointeur vers le sommet de la pile

public:
    pile() : sommet(nullptr) {} // Constructeur par d�faut

    // Fonction pour ajouter un �l�ment au sommet de la pile (push)
    void push(int val) {
        Noeud* nouveau_noeud = new Noeud{ val, sommet };
        sommet = nouveau_noeud;
    }

    // Fonction pour retirer l'�l�ment en haut de la pile (pop)
    // Renvoie false si la pile est vide et ne modifie pas le sommet
    bool pop() {
        if (empty()) {
            std::cerr << "Erreur : La pile est vide" << std::endl;
            return false;
        }
        Noeud* temp = sommet;
        sommet = sommet->suivant;
        delete temp;
        return true;
    }

    // Fonction pour v�rifier si la pile est vide
    bool empty() const {
        return sommet == nullptr;
    }

    // Fonction pour consulter l'�l�ment en haut sans le retirer
    int top() const {
        if (empty()) {
            std::cerr << "Erreur : La pile est vide" << std::endl;
            return -1; // Indique une erreur avec une valeur factice
        }
        return sommet->val;
    }

    // Fonction pour afficher les �l�ments de la pile
    void print() const {
        if (empty()) {
            std::cout << "La pile est vide" << std::endl;
            return;
        }
        Noeud* temp = sommet;
        while (temp) {
            std::cout << temp->val << " ";
            temp = temp->suivant;
        }
        std::cout << std::endl;
    }

    ~pile() {
        while (!empty()) {
            pop();
        }
    }
};



// declaration du pile st
pile st;


struct TS tsglobal;


int nbrparg = 0;
string dernierIdentif;


int typeDernierIdent;

int idBlock = 0; // Pour savoir dans quelle bloc on est ( 0 par defaut pour les variables globales)

//R1
void programme();
void programmePrime();

//R2
void listeDeclarations();

//R3
//void declaration();

//R4
void listeDeclarateurs();

//R5
void listeDeclarateursPrime();

//R6
void declarateur();

//R7
void declarateurPrime();
void declarateurSeconde();

//R8
void  fonction();

//R10
void  type();

//R11
void listeFonctions();

//R12
//void listeFonctionsPrime();

//R13
void  listeParms();

//R14
void listeParmsPrime();

//R15
void parm();

//R16
void listeInstructions();

//R17
//void listeInstructionsPrime();

//R18
void instruction();

//R19
void instructionPrime();

//R20
//void declartaionVariable();

//R21
//void listeDeclarateursVariables();

//R22
void iteration();

//R23
void selection();

//R24
void selectionPrime();

//R25
void saut();

//R26
void sautPrime();

//R27
void affectation();

void affectationIt();

//R28
void bloc();

//R29
//void appel();

//R30
void variable();

//R31
void variablePrime();

//R32
void variableSecond();

//R33
void expression();

//R34
void expressionPrime();

//R35
void expressionSeconde();

//R36
void listeExpressions();

//R37
void listeExpressionsPrime();

//R38
void condition();

//R39
void conditionPrime();

//R40
void binaryOp();

//R41
void binaryRel();

//R42
void binaryComp();



// Partie Lexicale
//m joue deux role Le max des mots cl�s et le nombre premier qu'on veut utiliser dans la fonction du hashing
const int m = 199;  // max des mots cl�s














//Les unit�s lexicales

enum NomUniteLexicale {
    identificateur, MOTCLE, PTVRG, VERG, CONSTANTE, INF, INFEGAL, SUP, SUPEGAL, EGALEGAL, DIFF, MOINS, DIV, MULT, AND,
    OR, PAROUV, PARFER, CROOUV, CROFER, ACCOUV, ACCFER, LETTRE, CHIFFRE, AFFECT, DOLLAR, PLUS, OU, ET, CMT, ERR, NOT, DEBCMT
};


//Tableau des noms des unit�s lexicales pour les r�cup�r�

string nomsUlexical[] = {
    "identificateur", "MOTCLE", "PTVRG", "VERG", "CONSTANTE", "INF", "INFEGAL", "SUP", "SUPEGAL",
                    "EGALEGAL", "DIFF", "MOINS", "DIV", "MULT", "AND", "OR", "PAROUV", "PARFER", "CROOUV", "CROFER",
                    "ACCOUV", "ACCFER", "LETTRE", "CHIFFRE", "AFFECT", "DOLLAR", "PLUS", "OU", "ET", "CMT", "ERR",
                    "NOT", "DEBCMT"
};



// La fonction responsable de la r�cup�ration des noms des unit�s lexicales

string trouveNom(enum NomUniteLexicale u) {
    return nomsUlexical[u];
}


// La table des mots cl�s

string tableMotCle[] = { "int","void","for","while","if","then","else"
, "return","lire","ecrire"
};


string tableIdent[200];  //
int nbrIdent = 0;



struct UniteLexicale {
    enum NomUniteLexicale us;
    int atr;
};


// On va lire un caract�re � partir du ficher (passage par r�ference)
char lireCar(ifstream& fichierEntree) {
    char ch;
    fichierEntree.get(ch);
    //cout << "c=" << ch << endl;
    return ch;
}

bool estBlanc(char cc) {
    return cc == ' ' || cc == '\t' || cc == '\n';
}

bool estLettre(char cc) {
    return ('A' <= cc && cc <= 'Z') || ('a' <= cc && cc <= 'z');
}
bool estChiffre(char c) {
    return '0' <= c && c <= '9';
}


// Avec cette fonction on va calculer la valeur de hash d'un string
// Puis on va associer chaque valeur � son string
// On va appliquer �a au table des mot cl�s
int compute_hash(string const& s) {
    const int p = 31;
    // Entier m pour ne pas avoir une valeur qui depasse la taille du tableau des mots cl�s
    int hash_value = 0;
    int p_pow = 1;
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}



// On va cr�er une table de hachage qui va jouer le role d'un dictionnaire
class HashTable {
    int nbr;
    string mots[m]; // Table qui va contenir les mots cl�s
public:
    HashTable() {
        nbr = 0;
    }
    void ajouterMot(string m) {
        mots[compute_hash(m)] = m; // Associer � chaque valeur de hash son lexeme
        nbr++;
    }
    bool estMotCle(string m) {
        return mots[compute_hash(m)] == m; // V�rifier que lexeme qu'on a donn� est dans la table
    }
};







// declaration du table de hash
// Notre table de hashing qui va contenir les mots cl�s
HashTable hashTable;



//-----------------------------------Le fichier de test-------------------------------------------
ifstream fichierEntree("exemple.txt");
char c;

struct UniteLexicale uniteSuivante() {
    UniteLexicale uniteLexicale;
    while (estBlanc(c)) {
        c = lireCar(fichierEntree);
    }
    //cout << "c = " << c << endl;
    switch (c)
    {
    case '$': {
        uniteLexicale.us = DOLLAR;
        c = lireCar(fichierEntree);
        return uniteLexicale;
    }
    case ';':
        uniteLexicale.us = PTVRG;
        c = lireCar(fichierEntree);
        return uniteLexicale;
    case ',':
        uniteLexicale.us = VERG;
        c = lireCar(fichierEntree);
        return uniteLexicale;
    case '[':
        uniteLexicale.us = CROOUV;
        c = lireCar(fichierEntree);
        return uniteLexicale;
    case ']':
        uniteLexicale.us = CROFER;
        c = lireCar(fichierEntree);
        return uniteLexicale;
    case '(':
        uniteLexicale.us = PAROUV;
        c = lireCar(fichierEntree);
        return uniteLexicale;
    case ')':
        uniteLexicale.us = PARFER;
        c = lireCar(fichierEntree);
        return uniteLexicale;
    case'{':
        uniteLexicale.us = ACCOUV;
        c = lireCar(fichierEntree);
        return uniteLexicale;
    case '}':
        uniteLexicale.us = ACCFER;
        c = lireCar(fichierEntree);
        return uniteLexicale;
    case '+':
        uniteLexicale.us = PLUS;
        c = lireCar(fichierEntree);
        return uniteLexicale;
    case '-':
        uniteLexicale.us = MOINS;
        c = lireCar(fichierEntree);
        return uniteLexicale;
    case 'OU':
        uniteLexicale.us = OU;
        c = lireCar(fichierEntree);
        return uniteLexicale;
    case '|': {
        c = lireCar(fichierEntree);
        if (c == '|') {
            uniteLexicale.us = OU;
            c = lireCar(fichierEntree);
            return uniteLexicale;
        }
        else {
            uniteLexicale.us = ERR;
            return uniteLexicale;
        }
    }
    case '&': {
        c = lireCar(fichierEntree);
        if (c == '&') {
            uniteLexicale.us = ET;
            c = lireCar(fichierEntree);
            return uniteLexicale;
        }
        else {
            uniteLexicale.us = ERR;
            return uniteLexicale;
        }
    }
    case '=': {
        c = lireCar(fichierEntree);
        if (c == '=') {
            uniteLexicale.us = EGALEGAL;
            c = lireCar(fichierEntree);
            return uniteLexicale;
        }
        else {
            uniteLexicale.us = AFFECT;
            return uniteLexicale;
        }
    }
    case '!': {
        char t = c;
        c = lireCar(fichierEntree);
        if (c == '=') {
            uniteLexicale.us = DIFF;
            c = lireCar(fichierEntree);
            return uniteLexicale;
        }
        else {
            uniteLexicale.us = NOT;
            return uniteLexicale;
        }
    }
    case '/': {
        c = lireCar(fichierEntree);
        if (c == '*') {
            while (c != '$') {
                c = lireCar(fichierEntree);
                if (c == '*') {
                    c = lireCar(fichierEntree);
                    if (c == '/') {
                        uniteLexicale.us = CMT;
                        c = lireCar(fichierEntree);
                        return uniteLexicale;
                    }
                }
            }
            uniteLexicale.us = ERR;
            return uniteLexicale;
        }
        else {
            uniteLexicale.us = DIV;
            return uniteLexicale;
        }
    }
            //Question ??
            /*
            case '*': {
                c = lireCar(fichier);
                if (c == '/') {
                    uniteLexicale.us = ERR;
                    c = lireCar(fichier);
                    return uniteLexicale;
                }
                else {
                    uniteLexicale.us = MULT;
                    return uniteLexicale;
                }
            }
            */
    case '<': {
        char t = c;
        c = lireCar(fichierEntree);
        if (c == '=') {
            uniteLexicale.us = SUPEGAL;
            c = lireCar(fichierEntree);
            return uniteLexicale;
        }
        else {
            uniteLexicale.us = SUP;
            return uniteLexicale;
        }
    }
    default:
        if (estLettre(c)) {
            string lexeme;
            while (estLettre(c) || estChiffre(c)) {
                lexeme.push_back(c);  // add to string its caracters
                c = lireCar(fichierEntree);
            }
            //cout <<"\n" << lexeme << ":::\n";
            if (hashTable.estMotCle(lexeme)) {
                uniteLexicale.us = MOTCLE;
                uniteLexicale.atr = compute_hash(lexeme);
                return uniteLexicale;
            }
            else {
                uniteLexicale.us = identificateur;
                dernierIdentif = lexeme;
                tableIdent[nbrIdent++] = lexeme;
                return uniteLexicale;
            }
            uniteLexicale.us = ERR;
            return uniteLexicale;
        }
        else if (estChiffre(c)) {
            string lexeme;
            while (estChiffre(c)) {
                lexeme.push_back(c);
                c = lireCar(fichierEntree);
            }
            uniteLexicale.us = CHIFFRE;
            return uniteLexicale;
        }
        else {
            uniteLexicale.us = ERR;
            c = lireCar(fichierEntree);
            return uniteLexicale;
        }
    }
    uniteLexicale.us = ERR;
    c = lireCar(fichierEntree);
    return uniteLexicale;
}

UniteLexicale uniteLexical;



//

void afficherGlobale() {
    for (int i = 0; i <= tsglobal.nbre; i++) {
        cout << tsglobal.nom[i] << " " << tsglobal.etat[i] << " " << tsglobal.type[i] << " " << tsglobal.blok[i];
        if (tsglobal.type[i] > 3) {
            cout << " " << tsglobal.nbrpar[i];     // nbr de par de chaque fct
        }
        cout << endl;
    }
}


// Partie Syntaxique Dirig�e par le S�mantique

int main()
{
    //Ajout des mots cl�s dans notre hashTable
    for (auto x : tableMotCle) {
        hashTable.ajouterMot(x);
    }
    cout << "\t\t\t\tTable des mots cles\n";
    cout << "\tMot cle ||  valeur de hash\n";

    for (auto x : tableMotCle) {
        cout << "\t" << x << " : " << compute_hash(x) << endl;
    }
    cout << endl;


    c = lireCar(fichierEntree);
    if (fichierEntree.is_open()) {
        int numUL = 1;
        //uniteLexical = uniteSuivante();
        //while (uniteLexical.us != DOLLAR) {
         //   string uniteL = trouveNom(uniteLexical.us);
            //cout << uniteL << endl;
            /*if (uniteL == "ERR") {
                system("Color 4");
                cout << uniteL << " ERREUR lors de l'analyse lexical";
                break;
            }
            else {
                cout << numUL << " " << "unite lexical est : " << trouveNom(uniteLexical.us) << endl;
            }*/





        uniteLexical = uniteSuivante();
        programme();

        /*uniteLexical = uniteSuivante();
        numUL++;*/
        //}
        fichierEntree.close();
    }
    else {
        cout << "Erreur lors de l'ouverture du fichier en lecture." << endl;
    }
    for (int i = 0; i < tsglobal.nbre; i++) {

        cout << tsglobal.nom[i] << " ";
        switch (tsglobal.type[i]) {
        case 1:
            cout << "ENTIER ";
            break;
        case 2:
            cout << "TABLE DE 1 DIM ";
            break;
        case 3:
            cout << "TABLE DE 2 DIM ";
            break;
        case 4:
            cout << "FCT INT ";
            break;
        case 5:
            cout << "FCT VOID ";
            break;
        default:
            break;
        }
        cout << endl;
    }
    return 0;
}




void programme() {
    st.push(0);
    if (uniteLexical.us == MOTCLE && uniteLexical.atr == compute_hash("int")) {

        uniteLexical = uniteSuivante();
        if (uniteLexical.us == identificateur) {

            //
            tsglobal.nom[tsglobal.nbre] = dernierIdentif;
            for (int i = 0; i < tsglobal.nbre; i++) {
                if (tsglobal.nom[i] == dernierIdentif && tsglobal.blok[i] == st.top()) {
                    cout << "Erreur lors de l'analyse s�mantique | Cet identificateur est d�j� utilis�.\n";
                    break;
                }
            }
            tsglobal.type[tsglobal.nbre] = 1;// int
            tsglobal.etat[tsglobal.nbre] = 1;// Etat d�clar�
            tsglobal.blok[tsglobal.nbre] = idBlock;
            tsglobal.nbre++;
            uniteLexical = uniteSuivante();
            programmePrime();
        }
        else {
            cout << __LINE__ << " identificateur Attendu \n";
        }
    }
    else if (uniteLexical.us == MOTCLE && uniteLexical.atr == compute_hash("void")) {
        uniteLexical = uniteSuivante();

        // Les fonctions dans le bloc global

        tsglobal.nom[tsglobal.nbre] = dernierIdentif;
        for (int i = 0; i < tsglobal.nbre; i++) {
            if (tsglobal.nom[i] == dernierIdentif && tsglobal.blok[i] == st.top()) {
                cout << "Erreur lors de l'analyse s�mantique | Cet identificateur est d�j� utilis�.\n";
                break;
            }
        }
        tsglobal.type[tsglobal.nbre] = 5;// void()
        tsglobal.etat[tsglobal.nbre] = 1;// Etat d�clar�
        tsglobal.blok[tsglobal.nbre] = idBlock;

        nbrparg = 0;
        tsglobal.nbre++;

        if (uniteLexical.us == identificateur) {
            uniteLexical = uniteSuivante();
            if (uniteLexical.us == PAROUV) {
                uniteLexical = uniteSuivante();
                listeParms();
                tsglobal.nbrpar[tsglobal.nbre - 1] = nbrparg;
                nbrparg = 0;
                if (uniteLexical.us == PARFER) {
                    uniteLexical = uniteSuivante();
                    if (uniteLexical.us == ACCOUV) {
                        uniteLexical = uniteSuivante();
                        listeDeclarations();
                        listeInstructions();
                        if (uniteLexical.us == ACCFER) {
                            uniteLexical = uniteSuivante();
                            st.pop();
                            listeFonctions();
                        }
                        else {
                            cout << __LINE__ << " ACCFER Attendu \n";
                        }
                    }
                    else {
                        cout << __LINE__ << " ACCOUV Attendu \n";
                    }
                }
                else {
                    cout << __LINE__ << " PARFER Attendu \n";
                }
            }
            else {
                cout << __LINE__ << " PAROUV Attendu \n";
            }
        }
        else {
            cout << __LINE__ << " identificateur Attendu \n";
        }
    }
    else
    {
        /*epsilon*/
    }
}

void programmePrime() {
    if (uniteLexical.us == PAROUV) {
        if (tsglobal.nbre > 0) {
            tsglobal.type[tsglobal.nbre - 1] = 4;   // fct int

        }
        uniteLexical = uniteSuivante();
        listeParms();
        tsglobal.nbrpar[tsglobal.nbre - 1] = nbrparg;   // affecter � chaque fct son nbr de parametre
        nbrparg = 0;                                        // initialiser nbr de parametre � 0

        if (uniteLexical.us == PARFER) {
            uniteLexical = uniteSuivante();
            if (uniteLexical.us == ACCOUV) {
                uniteLexical = uniteSuivante();
                listeDeclarations();
                listeInstructions();
                if (uniteLexical.us == ACCFER) {
                    uniteLexical = uniteSuivante();
                    st.pop();                 /// quant on sort d'un block on supprime le id de ce block dans la pile
                    listeFonctions();
                }
                else {
                    cout << __LINE__ << " ACCFER Attendu \n";
                }
            }
            else {
                cout << __LINE__ << " ACCOUV Attendu \n";
            }
        }
        else {
            cout << __LINE__ << " PARFER Attendu \n";
        }
    }
    else {
        declarateurPrime();
        listeDeclarateursPrime();
        if (uniteLexical.us == PTVRG) {
            uniteLexical = uniteSuivante();
            programme();
        }
        else {

            cout << __LINE__ << " PTVRG Attendu \n";
        }
    }
}

void listeDeclarations() {
    if (uniteLexical.us == MOTCLE && uniteLexical.atr == compute_hash("int")) {
        uniteLexical = uniteSuivante();
        listeDeclarateurs();
        if (uniteLexical.us == PTVRG) {
            uniteLexical = uniteSuivante();
            listeDeclarations();
        }
        else {
            cout << __LINE__ << " PTVRG Attendu \n";
        }
    }
    else
    {
        /*epsilon*/
    }
}

void listeFonctions()
{
    if (uniteLexical.us == MOTCLE && (uniteLexical.atr == compute_hash("int") || uniteLexical.atr == compute_hash("void"))) // void
    {
        fonction();
        listeFonctions();
    }
}

void listeDeclarateurs()
{
    declarateur();
    listeDeclarateursPrime();
}

void listeDeclarateursPrime()
{
    if (uniteLexical.us == VERG)
    {
        uniteLexical = uniteSuivante();
        declarateur();
        listeDeclarateursPrime();
    }
    else
    {
        /*epsilon*/
    }

}

void declarateur() {
    if (uniteLexical.us == identificateur) {
        tsglobal.nom[tsglobal.nbre] = dernierIdentif;     /// stocker dernier identif dans ts et puis on parcour les identifs exist�s dans ts ,
        for (int i = 0; i < tsglobal.nbre; i++) {
            if (tsglobal.nom[i] == dernierIdentif && tsglobal.blok[i] == st.top()) { /// si on troouve un identique et ds le meme block , error
                cout << "Erreur lors de l'analyse s�mantique | Cet identificateur est d�j� utilis�.\n";
                break;
            }
        }
        /// sinon on fais ces actions  dans le ts
        tsglobal.etat[tsglobal.nbre] = 1;
        tsglobal.type[tsglobal.nbre] = 1;
        tsglobal.blok[tsglobal.nbre] = idBlock;
        tsglobal.nbre++;
        uniteLexical = uniteSuivante();
        declarateurPrime();
    }
    else {
        cout << "identificateur ATTENDU" << endl;
    }
}


void declarateurPrime()
{
    if (uniteLexical.us == CROOUV)
    {
        uniteLexical = uniteSuivante();
        if (uniteLexical.us == CHIFFRE)
        {
            uniteLexical = uniteSuivante();
            if (uniteLexical.us == CROFER)
            {
                uniteLexical = uniteSuivante();
                declarateurSeconde();
            }
            else
            {
                cout << "CROFER ATTENDU" << endl;
            }
        }
        else
        {
            cout << "ENTIER ATTENDU" << endl;
        }
    }
    else {
        /*epsilon*/
    }
}


void declarateurSeconde()
{

    if (uniteLexical.us == CROOUV)
    {
        uniteLexical = uniteSuivante();
        if (uniteLexical.us == CHIFFRE)
        {
            uniteLexical = uniteSuivante();
            if (uniteLexical.us == CROFER)
            {
                tsglobal.type[tsglobal.nbre - 1] = 3;   /// int[][]
                uniteLexical = uniteSuivante();
            }
            else
            {
                cout << "CROFER ATTENDU" << endl;
            }
        }
        else
        {
            cout << "ENTIER ATTENDU" << endl;
        }

    }
    else
    {
        tsglobal.type[tsglobal.nbre - 1] = 2;   /// int[]
        /*epsilon*/
    }
}


int typefct = 4;

void fonction()
{

    type();
    if (uniteLexical.us == identificateur) {

        for (int i = 0; i < tsglobal.nbre; i++) {
            if (tsglobal.nom[i] == dernierIdentif && tsglobal.blok[i] == st.top()) {
                cout << "Erreur lors de l'analyse s�mantique | Cet identificateur est d�j� utilis� pour d�clarer une fonction.\n";
                break;
            }
        }
        tsglobal.nom[tsglobal.nbre] = dernierIdentif;
        tsglobal.type[tsglobal.nbre] = typefct;
        tsglobal.etat[tsglobal.nbre] = 1;
        tsglobal.blok[tsglobal.nbre] = idBlock;
        tsglobal.nbre++;
        uniteLexical = uniteSuivante();
        if (uniteLexical.us == PAROUV) {
            uniteLexical = uniteSuivante();
            listeParms();
            tsglobal.nbrpar[tsglobal.nbre - 1] = nbrparg;
            nbrparg = 0;
            if (uniteLexical.us == PARFER) {
                uniteLexical = uniteSuivante();
                if (uniteLexical.us == ACCOUV) {

                    uniteLexical = uniteSuivante();
                    listeDeclarations();
                    listeInstructions();
                    if (uniteLexical.us == ACCFER) {
                        uniteLexical = uniteSuivante();
                        st.pop();
                    }
                    else {

                        cout << __LINE__ << " ACCFER attendu\n";
                    }
                }
                else {
                    cout << __LINE__ << " ACCOUV attendu\n";
                }
            }
            else {
                cout << __LINE__ << " PARFER attendu\n";
            }
        }
        else {
            cout << __LINE__ << " PAROUV attendu\n";
        }
    }
    else {
        cout << __LINE__ << "identificateur attendu\n";
    }
}


void type() {
    if (uniteLexical.us == MOTCLE && (uniteLexical.atr == compute_hash("void") || uniteLexical.atr == compute_hash("int"))) {
        if (uniteLexical.atr == compute_hash("void"))
            typefct = 5;
        else
            typefct = 4;
        uniteLexical = uniteSuivante();
    }
    else {
        cout << "TYPE ATTENDU\n";
    }
}


void  listeParms()
{
    idBlock++;   /// new block
    st.push(idBlock);
    if (uniteLexical.us == MOTCLE && uniteLexical.atr == compute_hash("int")) {

        parm();
        listeParmsPrime();

    }
    else {

        /*epsilon*/
    }
}


void listeParmsPrime()
{
    if (uniteLexical.us == VERG)
    {
        uniteLexical = uniteSuivante();
        parm();
        listeParmsPrime();
    }
    else
    {
        /*epsilon*/
    }
}

void parm()
{
    nbrparg++;
    if (uniteLexical.us == MOTCLE && uniteLexical.atr == compute_hash("int")) //entier
    {
        uniteLexical = uniteSuivante();
        if (uniteLexical.us == identificateur)
        {
            uniteLexical = uniteSuivante();
        }
        else
        {
            cout << "identificateur ATTENDU" << endl;
        }
    }
    else
    {
        cout << "ENTIER ATTENDU" << endl;
    }
}



void listeInstructions()
{
    // V�rification si <instruction> commence par le lex�me courant pour d�duire le choix.

    if ((uniteLexical.us == identificateur) ||
        (uniteLexical.us == MOTCLE && (uniteLexical.atr == compute_hash("for") || uniteLexical.atr == compute_hash("while"))) ||
        (uniteLexical.us == MOTCLE && (uniteLexical.atr == compute_hash("return"))) ||
        (uniteLexical.us == MOTCLE && uniteLexical.atr == compute_hash("if")) ||
        (uniteLexical.us == ACCOUV)
        )
    {
        instruction();
        listeInstructions();
    }
    else
    {
        /*epsilon*/
    }

}


int nbrArg = 0; // Nombre d'arguments pour notre fonction courante

void instruction()
{
    if (uniteLexical.us == identificateur)
    {
        string localIdent = dernierIdentif;// Pour r�cuperer notre identificateur courant
        bool flag = false; // Pour v�rifier si l'identificateur est deja declar�
        for (int i = 0; i < tsglobal.nbre; i++) {
            if (tsglobal.nom[i] == dernierIdentif) {
                typeDernierIdent = tsglobal.type[i]; // Le type du dernier identificateur lu
                flag = 1;
                break;
            }
        }
        if (!flag) {    /// if true trouv� et non d�clar�
            cout << "Erreur lors de l'analyse s�mantique | L'identificateur " << dernierIdentif << " n'est pas declar�.\n";
        }
        uniteLexical = uniteSuivante();
        nbrArg = 0;
        instructionPrime();
        for (int i = 0; i < tsglobal.nbre; i++) {
            if (tsglobal.type[i] > 3 && tsglobal.nom[i] == localIdent && tsglobal.nbrpar[i] != nbrArg) {
                cout << "Erreur lors de l'analyse s�mantique | Le nombre d'arguments de la fonction " << localIdent << " ne correspond pas au nombre d'arguments donn� : " << nbrArg << endl;
                break;
            }
        }
    }
    // V�rification si les diff�rents choix qui commencent par des non-terminaux commencent par le lex�me courant pour d�duire le choix.
    else if (uniteLexical.us == MOTCLE && (uniteLexical.atr == compute_hash("for") || uniteLexical.atr == compute_hash("while")))
    {
        iteration();
    }
    else if (uniteLexical.us == MOTCLE && (uniteLexical.atr == compute_hash("if")))
    {
        selection();
    }
    else if (uniteLexical.us == MOTCLE && uniteLexical.atr == compute_hash("return"))
    {
        saut();
    }
    else if (uniteLexical.us == ACCOUV)
    {
        bloc();
    }
    else
    {
        cout << "Instruction Attendu" << endl;
    }
}


void instructionPrime()
{
    if (uniteLexical.us == PAROUV)
    {
        uniteLexical = uniteSuivante();
        listeExpressions();
        if (uniteLexical.us == PARFER) {
            uniteLexical = uniteSuivante();
            if (uniteLexical.us == PTVRG) {
                uniteLexical = uniteSuivante();
            }
            else {
                cout << __LINE__ << " PTVRG attendu\n";
            }
        }
        else {
            cout << __LINE__ << " PARFER attendu\n";
        }
    }
    else
    {
        variablePrime();
        if (uniteLexical.us == AFFECT)
        {
            bool f = false;
            for (int i = tsglobal.nbre - 1; i > -1; i--) {
                if (tsglobal.nom[i] == dernierIdentif && typeDernierIdent == 1) {
                    f = true;     /// meme type int
                    break;
                }
            }
            if (!f) {     /// pas le meme type de celle avant affectation
                cout << "Erreur lors de l'analyse s�mantique | Affectation avec des types incompatibles.\n";
                cout << dernierIdentif << endl;
            }
            uniteLexical = uniteSuivante();
            expression();
            if (uniteLexical.us == PTVRG)
            {
                uniteLexical = uniteSuivante();
            }
            else {
                cout << __LINE__ << " PTVRG attendu" << endl;
            }
        }
        else
        {
            cout << __LINE__ << " AFFECT attendu" << endl;
        }
    }
}


void iteration()
{
    if (uniteLexical.us == MOTCLE && uniteLexical.atr == compute_hash("for"))
    {
        uniteLexical = uniteSuivante();
        if (uniteLexical.us == PAROUV)
        {
            uniteLexical = uniteSuivante();
            affectationIt();
            if (uniteLexical.us == PTVRG)
            {
                uniteLexical = uniteSuivante();
                condition();
                if (uniteLexical.us == PTVRG)
                {
                    uniteLexical = uniteSuivante();
                    affectationIt();
                    if (uniteLexical.us == PARFER)
                    {
                        uniteLexical = uniteSuivante();
                        instruction();
                    }
                    else
                    {
                        cout << __LINE__ << " PARFER Attendu" << endl;
                    }
                }
                else
                {
                    cout << __LINE__ << " PTVRG Attendu" << endl;
                }
            }
            else
            {
                cout << __LINE__ << " PTVRG Attendu" << endl;
            }
        }
        else {
            cout << __LINE__ << " PAROUV Attendu\n";
        }
    }
    else if (uniteLexical.us == MOTCLE && uniteLexical.atr == compute_hash("while"))
    {
        uniteLexical = uniteSuivante();
        if (uniteLexical.us == PAROUV)
        {
            uniteLexical = uniteSuivante();
            condition();
            if (uniteLexical.us == PARFER)
            {
                uniteLexical = uniteSuivante();
                instruction();
            }
            else
            {
                cout << __LINE__ << " PARFER Attendu" << endl;
            }
        }
        else
        {
            cout << __LINE__ << " PAROUV Attendu" << endl;
        }
    }
    else
    {
        cout << __LINE__ << " FOR ou WHILE Attendu" << endl;
    }

}



void selection()
{
    if (uniteLexical.us == MOTCLE && uniteLexical.atr == compute_hash("if"))
    {
        uniteLexical = uniteSuivante();
        if (uniteLexical.us == PAROUV)
        {
            uniteLexical = uniteSuivante();
            condition();
            if (uniteLexical.us == PARFER)
            {
                uniteLexical = uniteSuivante();
                instruction();
                selectionPrime();
            }
            else
            {
                cout << __LINE__ << " PARFER Attendu" << endl;
            }
        }
        else
        {
            cout << __LINE__ << " PAROUV Attendu" << endl;
        }
    }
    else
    {
        cout << __LINE__ << " IF Attendu" << endl;
    }
}


void selectionPrime()
{
    if (uniteLexical.us == MOTCLE && uniteLexical.atr == compute_hash("else"))
    {
        uniteLexical = uniteSuivante();
        instruction();
    }
    else
    {
        /*epsilon*/
    }
}


void saut()
{
    if (uniteLexical.us == MOTCLE && uniteLexical.atr == compute_hash("return"))
    {
        uniteLexical = uniteSuivante();
        sautPrime();
    }
    else
    {
        cout << __LINE__ << " RETURN Attendu" << endl;
    }
}


void sautPrime()
{
    if (uniteLexical.us == PTVRG)
    {
        uniteLexical = uniteSuivante();
        for (int i = tsglobal.nbre - 1; i > -1; i--) {
            if (tsglobal.type[i] == 4 && tsglobal.blok[i] == st.top() - 1) {
                cout << "Erreur lors de l'analyse s�mantique | Un retour d'entier est n�cessaire pour une fonction de type int.\n";
                break;
            }
        }
    }
    else if ((uniteLexical.us == PAROUV || uniteLexical.us == MOINS || uniteLexical.us == identificateur || uniteLexical.us == CHIFFRE))
    {
        expression();
        for (int i = tsglobal.nbre - 1; i > -1; i--) {

            if (tsglobal.type[i] == 5 && tsglobal.blok[i] == st.top() - 1) {
                cout << "Erreur lors de l'analyse s�mantique | Retour d'entier impossible pour une fonction de type void.\n";
                break;
            }
        }
        if (uniteLexical.us == PTVRG)
        {
            uniteLexical = uniteSuivante();
        }
        else
        {
            cout << __LINE__ << " PTVRG Attendu" << endl;
        }
    }
    else
    {
        cout << __LINE__ << " Expression ou PTVRG Attendu" << endl;
    }
}

void affectation()
{
    variable();
    if (uniteLexical.us == AFFECT)
    {
        uniteLexical = uniteSuivante();
        expression();
        if (uniteLexical.us == PTVRG) {
            uniteLexical = uniteSuivante();
        }
        else {
            cout << __LINE__ << " PTVRG Attendu\n";
        }
    }
    else
    {
        cout << __LINE__ << " AFFECT Attendu" << endl;
    }
}


void affectationIt()
{
    variable();
    if (uniteLexical.us == AFFECT)
    {
        uniteLexical = uniteSuivante();
        expression();
    }
    else
    {
        cout << __LINE__ << " AFFECT Attendu" << endl;
    }
}


void bloc()
{
    if (uniteLexical.us == ACCOUV)
    {
        uniteLexical = uniteSuivante();
        listeInstructions();
        if (uniteLexical.us == ACCFER)
        {
            uniteLexical = uniteSuivante();
        }
        else
        {
            cout << __LINE__ << " ACCFER Attendu" << endl;
        }
    }
    else
    {
        cout << __LINE__ << " ACCOUV Attendu" << endl;
    }
}


void variable()
{
    if (uniteLexical.us == identificateur)
    {
        uniteLexical = uniteSuivante();
        variablePrime();
    }
    else
    {
        cout << __LINE__ << " identificateur Attendu" << endl;
    }
}


void variablePrime()
{
    if (uniteLexical.us == CROOUV)
    {
        uniteLexical = uniteSuivante();
        expression();
        if (uniteLexical.us == CROFER)
        {
            uniteLexical = uniteSuivante();
            typeDernierIdent--;
            variableSecond();
        }
        else
        {
            cout << __LINE__ << " CROFER Attendu" << endl;
        }
    }
    else
    {
        /*epsilon*/
    }

}



void variableSecond()
{
    if (uniteLexical.us == CROOUV)
    {
        uniteLexical = uniteSuivante();
        expression();
        if (uniteLexical.us == CROFER)
        {
            uniteLexical = uniteSuivante();
            typeDernierIdent--;
        }
        else
        {
            cout << __LINE__ << " CROFER Attendu" << endl;
        }
    }
    else
    {
        /*epsilon*/
    }
}



void expression()
{
    if (uniteLexical.us == PAROUV)
    {
        uniteLexical = uniteSuivante();
        expression();
        if (uniteLexical.us == PARFER)
        {
            uniteLexical = uniteSuivante();
            expressionPrime();
        }
        else
        {
            cout << __LINE__ << " PARFER Attendu" << endl;
        }

    }
    else if (uniteLexical.us == MOINS)
    {
        uniteLexical = uniteSuivante();
        expression();
        expressionPrime();
    }
    else if (uniteLexical.us == identificateur)
    {
        uniteLexical = uniteSuivante();
        expressionSeconde();
    }
    else if (uniteLexical.us == CHIFFRE)
    {
        uniteLexical = uniteSuivante();
        expressionPrime();
    }
    else
    {
        cout << __LINE__ << " Expression Attendu" << endl;
    }
}




void expressionPrime()
{
    if ((uniteLexical.us == PLUS || uniteLexical.us == MOINS || uniteLexical.us == MULT || uniteLexical.us == DIV))
    {
        binaryOp();
        expression();
        expressionPrime();
    }
    else
    {
        /*epsilon*/
    }
}



void expressionSeconde()
{
    if (uniteLexical.us == PAROUV)
    {
        uniteLexical = uniteSuivante();
        nbrArg = 0;
        listeExpressions();
        // Test du nombre d'arguments
        for (int i = 0; i < tsglobal.nbre; i++) {
            if (tsglobal.type[i] > 3 && tsglobal.nom[i] == dernierIdentif && tsglobal.nbrpar[i] != nbrArg) {
                cout << "Erreur lors de l'analyse s�mantique | Le nombre d'arguments de la fonction " << dernierIdentif << " ne correspond pas au nombre d'arguments donn� : " << nbrArg << endl;
                break;
            }
        }
        if (uniteLexical.us == PARFER)
        {
            uniteLexical = uniteSuivante();
            expressionPrime();
        }
        else
        {
            cout << __LINE__ << " PARFER Attendu" << endl;
        }
    }
    else
    {
        variablePrime();
        expressionPrime();
    }
}


void listeExpressions()
{
    if ((uniteLexical.us == PAROUV || uniteLexical.us == MOINS || uniteLexical.us == identificateur || uniteLexical.us == CHIFFRE))
    {
        nbrArg++;
        expression();

        listeExpressionsPrime();
    }
    else
    {
        /*epsilon*/
    }
}

void listeExpressionsPrime()
{
    if (uniteLexical.us == VERG)
    {
        nbrArg++;
        uniteLexical = uniteSuivante();
        expression();
        listeExpressionsPrime();
    }
    else
    {
        /*epsilon*/
    }

}

void condition()
{
    if (uniteLexical.us == NOT)
    {
        uniteLexical = uniteSuivante();
        if (uniteLexical.us == PAROUV)
        {
            uniteLexical = uniteSuivante();
            condition();
            if (uniteLexical.us == PARFER)
            {
                uniteLexical = uniteSuivante();
                conditionPrime();
            }
            else
            {
                cout << __LINE__ << " PARFER Attendu" << endl;
            }
        }
        else
        {
            cout << __LINE__ << " PAROUV Attendu" << endl;
        }

    }
    else if (uniteLexical.us == PAROUV)
    {
        uniteLexical = uniteSuivante();
        condition();
        if (uniteLexical.us == PARFER)
        {
            uniteLexical = uniteSuivante();
            conditionPrime();
        }
        else
        {
            cout << __LINE__ << " PARFER Attendu" << endl;
        }
    }
    else if ((uniteLexical.us == MOINS || uniteLexical.us == identificateur || uniteLexical.us == CHIFFRE))
    {
        expression();
        binaryComp();
        expression();
        conditionPrime();
    }
    else
    {

        cout << __LINE__ << " Condition Attendue" << endl;
    }
}



void conditionPrime()
{
    if (uniteLexical.us == ET || uniteLexical.us == OU)
    {
        binaryRel();
        condition();
        conditionPrime();
    }
    else
    {
        /*epsilon*/
    }
}

void binaryOp()
{
    if (uniteLexical.us == PLUS || uniteLexical.us == MOINS || uniteLexical.us == MULT || uniteLexical.us == DIV)
    {
        uniteLexical = uniteSuivante();
    }
    else
    {
        cout << __LINE__ << " Op�rateur Binaire Attendu" << endl;
    }
}


void binaryRel()
{
    if (uniteLexical.us == ET || uniteLexical.us == OU)
    {
        uniteLexical = uniteSuivante();
    }
    else
    {
        cout << __LINE__ << " && ou || Attendu" << endl;
    }
}



void binaryComp()
{
    if (uniteLexical.us == SUP || uniteLexical.us == INF || uniteLexical.us == SUPEGAL || uniteLexical.us == INFEGAL ||
        uniteLexical.us == EGALEGAL || uniteLexical.us == DIFF) {
        uniteLexical = uniteSuivante();
    }
    else
    {
        cout << __LINE__ << " Op�rateur De Comparaison Attendu" << endl;
    }
}

// Code inutilis�
/*
void programmeSecond();

void programmeSecond() {
    if (uniteLexical.us == MOTCLE && uniteLexical.atr == compute_hash("int")) {
        uniteLexical = uniteSuivante();
        if (uniteLexical.us == identificateur) {
            uniteLexical = uniteSuivante();
            if (uniteLexical.us == PAROUV) {
                uniteLexical = uniteSuivante();
                listeParms();
                if (uniteLexical.us == PARFER) {
                    uniteLexical = uniteSuivante();
                    if (uniteLexical.us = ACCOUV) {
                        uniteLexical = uniteSuivante();
                        listeDeclarations();
                        listeInstructions();
                        if (uniteLexical.us == ACCFER) {
                            uniteLexical = uniteSuivante();
                            listeFonctionsPrime();
                        }
                        else {
                            cout << "573 accferm attendu \n";
                        }
                    }
                    else {
                        cout << "569 accouv attendu \n";
                    }
                }
                else {
                    cout << "567 parferm attendu \n";
                }
            }
            else {
                cout << "565 parouv attendu \n";
            }
        }
        else {
            cout << "564 identificateur attendu\n";
        }
    }
    else if (uniteLexical.us == MOTCLE && uniteLexical.atr==compute_hash("void")) {
        uniteLexical = uniteSuivante();
        if (uniteLexical.us == identificateur) {
            uniteLexical = uniteSuivante();
            if (uniteLexical.us == PAROUV) {
                uniteLexical = uniteSuivante();
                listeParms();
                if (uniteLexical.us == PARFER) {
                    uniteLexical = uniteSuivante();
                    if (uniteLexical.us == ACCOUV) {
                        uniteLexical = uniteSuivante();
                        listeDeclarations();
                        listeInstructions();
                        if(uniteLexical.us==ACCFER){
                            uniteLexical = uniteSuivante();
                            listeFonctionsPrime();
                        }
                        else {
                            cout << "610 accferm attendu\n";
                        }
                    }
                    else {
                        cout << "606 accouv attendu \n";
                    }
                }
                else {
                    cout << "604 parferm attendu \n";
                }
            }
            else {
                cout << "601 parouver attendu\n";
            }
        }
        else {
            cout << "identificateur attendu\n";
        }
    }
    else {
        //epsilon
    }
}
*/
