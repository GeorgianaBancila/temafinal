
typedef struct Player {
	char* firstName;
	char* secondName;
	int points;
} Player;
typedef struct Node {
	char* nume_echipa;
	int nrjucatori;
	Player* jucator;
	struct Node* next;
} Node;
typedef struct coada {
	Node *front, *rear;
} coada;
typedef struct stiva {
	char* echipa;
	struct stiva* next;
} stiva;
void addAtStart(Node** head, Node* new_node);
float calculpunctajechipa(Node* head) ;
int calculpunctajminim(float* vectorpuncte, int nrechipe);
void stergerenod(Node** head, int indice);
void stergereelementvector(float* vector, int size, int indice);
void enQueue(coada* q, char* v) ;
void push(stiva** top, char* v);
int isEmpty(stiva* top);
void deleteStack(stiva** top) ;
int isEmptyq(coada* q);
void deleteQueue(coada* q);