#if !defined(__CLIENTINFO__)
#define __CLIENTINFO__

struct ClientInfo {
    unsigned int id;
    char name[100];
    long registration_no;
    long msj_sent_count;
};

struct node {
    struct ClientInfo data;
    struct node* next;
    struct node* last;
};

struct node* init();
struct node* insert(struct node *ll, struct ClientInfo data);
void traverse(struct node *ll);
struct node* search(struct node* head, long rollNo);
#endif