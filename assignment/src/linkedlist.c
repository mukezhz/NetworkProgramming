#include <stdio.h>
#include <stdlib.h>

#include "assignment.h"
#include "clientinfo.h"

typedef struct ClientInfo ClientInfo;
typedef struct node node;

node *init()
{
    node *head = NULL;
    ClientInfo c1 = {id : 1, name : "Aashish", registration_no : 171501};
    ClientInfo c2 = {id : 2, name : "Abinash", registration_no : 171502};
    ClientInfo c3 = {id : 3, name : "Adarsha", registration_no : 171503};
    ClientInfo c4 = {id : 4, name : "Biraj", registration_no : 171504};
    ClientInfo c5 = {id : 5, name : "Bibek", registration_no : 171505};
    ClientInfo c6 = {id : 6, name : "Chelsea", registration_no : 171506};
    ClientInfo c7 = {id : 7, name : "David", registration_no : 171507};
    ClientInfo c8 = {id : 8, name : "Eggsy", registration_no : 171508};
    ClientInfo c9 = {id : 9, name : "Fire", registration_no : 171509};
    ClientInfo c10 = {id : 10, name : "Gary", registration_no : 171510};
    ClientInfo c11 = {id : 11, name : "Hari Bahadur", registration_no : 171511};
    ClientInfo c12 = {id : 12, name : "Samee", registration_no : 171512};
    ClientInfo c13 = {id : 13, name : "Yoona", registration_no : 171513};
    ClientInfo c[15] = {c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13};
    for (size_t i = 0; i < 13; i++)
        head = insert(head, c[i]);
    return head;
}

node *insert(node *ll, ClientInfo data)
{
    node *link = (struct node *)malloc(sizeof(struct node));
    link->data = data;
    link->next = NULL;
    if (ll == NULL)
    {
        ll = link;
        ll->last = link;
        return ll;
    }
    ll->last->next = link;
    ll->last = link;
    return ll;
}

void traverse(node *ll)
{
    node *temp;
    temp = ll;
    while (temp != NULL)
    {
        printf("id: %d\tname: %s\n", temp->data.id, temp->data.name);
        temp = temp->next;
    }
}

node *search(node *ll, long rollNo)
{
    node *temp;
    temp = ll;
    while (temp != NULL)
    {
        if (temp->data.registration_no == rollNo)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

