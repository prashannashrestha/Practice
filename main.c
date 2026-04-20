//added a top line comment
#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
int data;
struct node *next;
}node;

void traverse(node *head)
{
while(head)
{
printf("%d -> ",head->data);
head=head->next;
}
printf(" NULL \n");
}
node *createnode(int data)
{
node *newnode=malloc(sizeof(node));
if(newnode==NULL)
return NULL;
newnode->data=data;
newnode->next=NULL;
return newnode;
}

void addatbegin(node **head,int data)
{
node *newnode=createnode(data);
if(newnode==NULL)
return;
newnode->next=*head;
*head=newnode;
}

void addatend(node **head,int data)
{
//i am using the linus way bitch
node **temp=head;
//while(temp->next) in older way to get to the end node
while(*temp) //this stop us right before the null where our pointer part will be temp and *temp will be next block to whom its pointing to
temp=&((*temp)->next); 

//think it like we jumping from address and temp is initially at head i.e address of first node whole block when loop runs once then it gets the address of the next part of the 1st block so loop stops when temp is null . but *temp is null temp will be address before the null and we can modify the *temp easily

//this checks the null case edge case too so i prefer it
node *newnode=createnode(data);
*temp=newnode;
}

void addatindex(node **head,int index,int data)
{
if(index<0)
{
printf("Negative index \n");
return;
}
if(index==0)
{
addatbegin(head,data);
return;
}
//the for loop needs to be stopped 1 step ahead so its i=0 , i<index but if index is 0 loop wont even run so for that we need a test case as above insert at beginning 
node *temp=*head;
for(int i=0;i<index && temp;i++)
{
temp=temp->next;
}  //we will understand why we wrote temp there by seeing code below
if(temp==NULL)
{
printf("Index out of bound \n");
return;
}
node *newnode=createnode(data);
if(newnode==NULL)
return;

newnode->next=temp->next;
temp->next=newnode;

//so what if temp was null? then program would crash so outof bound is checked using NULL
}

void delatbegin(node **head)
{
//has 1 test case of null
if(*head==NULL)
{
printf("Node is empty . Cannot be deleted \n");
return;
}
node *todel=*head;
*head=(*head)->next;
}

void delatend(node **head)
{
//normal logic was head->next->next but this caused 2 test cases of head being null and single node case so with linus way i cant avoid the single node case easily 
if(*head==NULL)
{
printf("Node cannot be deleted . It is empty\n");
return;
}
node **temp=head;
while((*temp)->next)  //i needed to reach the 2nd last node using head->next->next so remember rule for linus way 1 step elimitaet like for add at end was head->next vice versa. this is for my understanding
temp=&((*temp)->next);   //so temp will stop exactly at the pointer part of the previous node of the node that we want and *temp is the actualy last node that we want to delete
node *todel=*temp;
*temp=NULL;
free(todel);
}

void delatindex(node **head,int index,int data)
{
if(index<0)
{
printf("Invalid , Negative index \n");
return;
}
if(index==0)
{
delatbegin(head);
return;
}
node *temp=*head;
for(int i=0;i<index && temp;i++)
temp=temp->next;  // same logic we stop one step before the node that we want to delte
if(temp==NULL || temp->next==NULL)
{
printf("Index out of bound \n" );
return;
}
node *todel=temp->next;
temp->next=todel->next;

//so assume temp was null it would crash and todel is simpl temp next and if it is null then it could crash 
//so we neeed a outbound check case using temp & temp->next
}

//lets find the middle element and then delete it 

void findmiddle(node *head)
{
if(head==NULL)
{
printf("The node is null . No middle element \n");
return;
}
//we use the hare and the tor logic
node *hare=head;
node *tor=head;
//there are 2 was to find the middle . 1st is the first middle and the other is the second nmiddle

while(hare && hare->next)
{
hare=hare->next->next;
tor=tor->next;
}
printf("Middle node = %d\n",tor->data);
//so when the loop ends tor is the middle element okay but the head can be null too and tor will stil be printed and the program could crash so we need a null case of head
}

void delmiddle(node **head)
{
if(*head==NULL)
{
printf("The node is null . No middle element \n");
return;
}
node *hare=*head;
node **tor=head;   //i am using the linus way of traversal to get the middle nodes address directly

while(hare && hare->next)
{
hare=hare->next->next;
tor=&((*tor)->next);
}

node *todel=*tor;
*tor=todel->next;
free(todel);
}

//lets find cyle adn then start of cycle using floyd way

void detectcycle(node *head)
{
node *hare=head;
node *tor=head;
while(hare && hare->next)
{
hare=hare->next->next;
tor=tor->next;
if(hare==tor)
{
printf("The cycle exists \n");
return;
}
}

}

void detectstartofcycle(node *head)
{
node *hare=head;
node *tor=head;
while(hare && hare->next)
{
hare=hare->next->next;
tor=tor->next;
   if(hare==tor)
 {
  //floy said to move hare to head and start again
  tor=head;
     while(hare!=tor)
    { 
     hare=hare->next;
     tor=tor->next;
    }
   printf("Cycle starts at %d ",tor->next);
   return;
  }
}
printf("Cycle doesnt exists \n");
}
//---------------------------------------
int lengthoflist(node *head)
{
int lado=0;
while(head)
{
head=head->next;
lado++;
}
return lado;
}
//---------------------------------------

void rotatelist(node **head,int k)
{
//k means to roate by length k from the right side
//k can be very huge outof length so we use % concept 
int l=lengthoflist(*head);
k=k%l;
//make it circular list
//so the main logic is now to move to desired k steps ahead via tail node and we do need a new head which is just head=tail->next and can make tail point to null  
node *temp=*head;
node *tail=*head;
while(temp->next)
temp=temp->next;
temp->next=*head;  //this is now a circular list okay
//we need to stop right before the k u feel me
for(int i=0;i<(l-k-1);i++)
tail=tail->next;
*head=tail->next;
tail->next=NULL;
}
//-------------------------------------------------------------
void reverse(node **head)
{
node *prev=NULL;
node *curr=*head;
node *next;
while(curr)
{
next=curr->next;
curr->next=prev;
prev=curr;
curr=next;
}
*head=prev;
}
//------------------------------------------------------------
void reversemn(node **head)
{
//so i need to reverse m and n i need to stop right before the m and reverse till (n-m) but the problem is linkage  i need the tail aka 1st node and link to curr
int m,n;
printf("Enter the m and n : ");
scanf("%d %d",&m,&n);
int length=lengthoflist(*head);
if(m>=n || n>length || m<1)
{
printf("Invalid n \n");
return;
}
node *dummynode=createnode(0);
dummynode->next=*head;
node *temp=dummynode;

//lets move temp to 1 step ahead
for(int i=1;i<m;i++)
temp=temp->next;

//assume eg 1 2 3 4 5 and m is 2 and n is 4
// temp should point 1 step ahead . 1<2 true temp is at 1 which is correct loop ends

node *curr=temp->next;
node *tail=curr;
node *prev=NULL;
node *next;
for(int i=0;i<=(n-m);i++) //4-2 = 2 so  0<=2 , 1<=2 and 2<=2 loop runs 3 time
{
next=curr->next;
curr->next=prev;
prev=curr;
curr=next;
}
//  2->NULL one time || 3->2->NULL two time || 4->3->2->NULL three time
//so 2 is still 2 we can tail->next=curr so 2 links to 5
tail->next=curr;  //linakge of 1 is left
temp->next=prev;
*head=dummynode->next;
}
//-----------------------------------------------------------
void main()
{
node *head=createnode(1);
head->next=createnode(2);
head->next->next=createnode(3);
head->next->next->next=createnode(4);
head->next->next->next->next=createnode(5);

traverse(head);
reversemn(&head);
traverse(head);
}