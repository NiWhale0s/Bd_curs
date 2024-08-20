#include <fstream>
#include <time.h>
#include <cmath>
#include <iostream>  
#include <conio.h>   
#include <Windows.h> 
#include <iomanip>   
#include <cstdio>    
#include <cstring>   
#include <cstdlib>
#include <ctime>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "string"

const int N = 4000;
int s = 0;
double C[1100][1100], L[1100];
int Length[1100];
float chas[256] = {0};
char ch[256];

struct Beutifull_People
{
  char Author[12];
  char Title[32];
  char Publishing_house[16];
  short int years;
  short int pages;
};

struct list
{
  struct list *next;
  Beutifull_People *data;
};

struct queue
{
  list *head;
  list *tail;
};
struct FS
{
  struct FS *next;
  Beutifull_People *data;
};

struct tree
{
  Beutifull_People *data;
  int Bal;
  struct tree *left, *right;
};

struct search
{
  Beutifull_People *data;
};

struct Symbols
{

  char Simvol;
  double Probability;
  std::string KeyWord = "";
  int KeyWordLength;
  char C[20];
};

list *Printlist(list *p, short int &count, short int x)
{
  system("cls");
  for (int i = 0; i < x; i++, count++)
  {
    std::cout << count << ")" << p->data->Author << "\t" << p->data->Title << "\t" << p->data->Publishing_house << "\t" << p->data->years << "\t" << p->data->pages << std::endl;
    p = p->next;
  }
  return p;
}

FS *Printlist1(FS *p, short int &count, short int x)
{
  system("cls");
  while (p != NULL)
  {
    std::cout << count << ")" << p->data->Author << "\t" << p->data->Title << "\t" << p->data->Publishing_house << "\t" << p->data->years << "\t" << p->data->pages << std::endl;
    p = p->next;
  }
  return p;
}

void Deletelist(list **head)
{
  list *r = *head;
  while (r != NULL)
  {
    *head = r->next;
    delete r;
    r = *head;
  }
}

void Deletelist1(FS **head)
{
  FS *r = *head;
  while (r != NULL)
  {
    *head = r->next;
    delete r;
    r = *head;
  }
}
// сортировка по году издания и автору

void itemMovement(list **head,list **tail){
  (*tail)->next = *head;
  *tail = *head;
  *head = (*head)->next;
  (*tail)->next = NULL;
}

void mergeLists(list **head_a, list **head_b, list **tail, int q, int r)
{
  while (q != 0 && r != 0)
  {

    if ((*head_a)->data->years < (*head_b)->data->years)
    {
      itemMovement(head_a, tail);
      q--;
    }
    else if ((*head_a)->data->years == (*head_b)->data->years)
    {
      if (strcmp((*head_a)->data->Author, (*head_b)->data->Author) <= 0)
      {
        itemMovement(head_a, tail);
        q--;
      }
      else
      {
        itemMovement(head_b, tail);
        r--;
      }
    }
    else
    {
      itemMovement(head_b, tail);
      r--;
    }
  }
  while (q > 0)
  {
    itemMovement(head_a, tail);
    q--;
  }
  while (r > 0)
  {
    itemMovement(head_b, tail);
    r--;
  }
}

void Split(list **head, list **head_a, list **head_b)
{
  list *k, *p;
  *head_a = *head;
  *head_b = (*head)->next;
  k = *head_a;
  p = *head_b;
  while (p != NULL)
  {
    k->next = p->next;
    k = p;
    p = p->next;
  }
}

void mergeSort(list **head, list **tail, int n)
{
  int i, m, q, p = 1, r;
  list *a = NULL, *b = NULL;
  queue c[2];
  Split(head, &a, &b);
  while (p < n)
  {
    c[0].tail = (list *)&c[0].head;
    c[1].tail = (list *)&c[1].head;
    i = 0;
    m = n;
    while (m > 0)
    {
      if (m >= p)
        q = p;
      else
        q = m;
      m -= q;
      if (m >= p)
        r = p;
      else
        r = m;
      m -= r;
      mergeLists(&a, &b, &c[i].tail, q, r);
      i = 1 - i;
    }
    a = c[0].head;
    b = c[1].head;
    p *= 2;
  }
  c[0].tail->next = NULL;
  *head = c[0].head;
}

int Years()
{
  int year;
  std::cout << "Please enter years (1898-1997)" << std::endl;
  std::cin >> year;
  if (year > 1997)
  {
    Years();
    
  }
  if (year < 1898)
  {
    Years();
  }
  return year;
}
// индексация
void Index_arr(Beutifull_People *index_arr[], list *p, int N)
{
  for (int i = 0; i < N; i++)
  {
    index_arr[i] = p->data;
    p = p->next;
  }
}
// ключ поиска год

void Bin_Search(Beutifull_People *index_arr[], int key, FS *p1, FS *tail)
{
  int L=0;
  int R=N-1;
  int m=0;
   int h=0; 
   int t=0;
  while (L<R){
    m=(L+R)/2;
    if (index_arr[m]->years > key){ L=m+1;}
    else if (index_arr[m]->years < key){ R=m;}
    else if(index_arr[m]->years == key){ break;}
  }
  h=m;
  t=m;
  while (index_arr[h]->years == key){
    h--;
    if ((h-1) == -1){ break;}
  }
  while (index_arr[t]->years == key){
    t++;
    if (t+1 == 3999){ break;}
  }
  for (int i=h;i<=t;i++){
    p1->data=index_arr[i];
    p1->next = new FS;
    p1=p1->next;
  }
  p1->data = NULL;
}

void Search_Fast(Beutifull_People *index_arr[], int key, FS *p1, FS *tail)
{
  for (int i = 0; i < N; i++)
  {
    if (index_arr[i]->years == key)
    {
      p1->data = index_arr[i];
      p1->next = new FS;
      p1 = p1->next;
    }
  }
  p1->data = NULL;
}
void Printlist(FS *p)
{
  while (1)
  {
    if (p->data == NULL)
    {
      break;
    }
    std::cout << p->data->Author << "\t" << p->data->Title << "\t" << p->data->Publishing_house << "\t" << p->data->years << "\t" << p->data->pages << std::endl;
    p = p->next;
  }
}
bool rost;

void rotateRR(tree *&p)
{
  tree *q = p->right;
  p->Bal = 0;
  q->Bal = 0;
  p->right = q->left;
  q->left = p;
  p = q;
}

void rotateLR(tree *&p)
{
  tree *q = p->left;
  tree *r = q->right;
  if (r->Bal < 0)
  {
    p->Bal = 1;
  }
  else
  {
    p->Bal = 0;
  }
  if (r->Bal > 0)
  {
    q->Bal = -1;
  }
  else
  {
    q->Bal = 0;
  }
  r->Bal = 0;
  q->right = r->left;
  p->left = r->right;
  r->left = q;
  r->right = p;
  p = r;
}

void rotateRL(tree *&p)
{
  tree *q = p->right;
  tree *r = q->left;
  if (r->Bal > 0)
    p->Bal = -1;
  else
    p->Bal = 0;

  if (r->Bal < 0)
    q->Bal = 1;
  else
    q->Bal = 0;

  r->Bal = 0;
  q->left = r->right;
  p->right = r->left;
  r->right = q;
  r->left = p;
  p = r;
}
void rotateLL(tree *&p)
{
  tree *q = p->left;
  p->Bal = 0;
  q->Bal = 0;
  p->left = q->right;
  q->right = p;
  p = q;
}
bool Rost;

int Add_AVL(tree *&p, FS *p1)
{
  if (p == NULL)
  {
    p = new tree;
    p->data = p1->data;
    p->left = NULL;
    p->right = NULL;
    p->Bal = 0;
    Rost = true;
  }
  else if (strcmp(p->data->Publishing_house, p1->data->Publishing_house) > 0)
  {
    Add_AVL(p->left, p1);
    if (Rost == true)
    {
      if (p->Bal > 0)
      {
        p->Bal = 0;
        Rost = false;
      }
      else if (p->Bal == 0)
      {
        p->Bal = -1;
        Rost = true;
      }
      else
      {
        if (p->left->Bal < 0)
        {
          rotateLL(p);
          Rost = false;
        }
        else
        {
          rotateLR(p);
          Rost = false;
        }
      }
    }
  }

  else if (strcmp(p->data->Publishing_house, p1->data->Publishing_house) < 0)
  {
    Add_AVL(p->right, p1);
    if (Rost == true)
    {
      if (p->Bal < 0)
      {
        p->Bal = 0;
        Rost = false;
      }
      else if (p->Bal == 0)
      {
        p->Bal = 1;
        Rost = true;
      }
      else
      {
        if (p->right->Bal > 0)
        {
          rotateRR(p);
          Rost = false;
        }
        else
        {
          rotateRL(p);
          Rost = false;
        }
      }
    }
  }
  else if (strcmp(p->data->Publishing_house, p1->data->Publishing_house) == 0)
  {
    if (strcmp(p->data->Title, p1->data->Title) > 0)
    {
      Add_AVL(p->left, p1);
      if (Rost == true)
      {
        if (p->Bal > 0)
        {
          p->Bal = 0;
          Rost = false;
        }
        else if (p->Bal == 0)
        {
          p->Bal = -1;
          Rost = true;
        }
        else
        {
          if (p->left->Bal < 0)
          {
            rotateLL(p);
            Rost = false;
          }
          else
          {
            rotateLR(p);
            Rost = false;
          }
        }
      }
    }
    else if ((strcmp(p->data->Title, p1->data->Title) < 0))
    {
      Add_AVL(p->right, p1);
      if (Rost == true)
      {
        if (p->Bal < 0)
        {
          p->Bal = 0;
          Rost = false;
        }
        else if (p->Bal == 0)
        {
          p->Bal = 1;
          Rost = true;
        }
        else
        {
          if (p->right->Bal > 0)
          {
            rotateRR(p);
            Rost = false;
          }
          else
          {
            rotateRL(p);
            Rost = false;
          }
        }
      }
    }
    else
    {
      if ((strcmp(p->data->Author, p1->data->Author) > 0))
      {
        Add_AVL(p->left, p1);
        if (Rost == true)
        {
          if (p->Bal > 0)
          {
            p->Bal = 0;
            Rost = false;
          }
          else if (p->Bal == 0)
          {
            p->Bal = -1;
            Rost = true;
          }
          else
          {
            if (p->left->Bal < 0)
            {
              rotateLL(p);
              Rost = false;
            }
            else
            {
              rotateLR(p);
              Rost = false;
            }
          }
        }
      }
      else
      {
        Add_AVL(p->right, p1);
        if (Rost == true)
        {
          if (p->Bal < 0)
          {
            p->Bal = 0;
            Rost = false;
          }
          else if (p->Bal == 0)
          {
            p->Bal = 1;
            Rost = true;
          }
          else
          {
            if (p->right->Bal > 0)
            {
              rotateRR(p);
              Rost = false;
            }
            else
            {
              rotateRL(p);
              Rost = false;
            }
          }
        }
      }
    }
  }
}

void traversal(tree *p, int type)
{
  if (p != NULL)
  {
    if (type == 1)
    {
      std::cout << p->data->Author << "\t" << p->data->Title << "\t" << p->data->Publishing_house << "\t" << p->data->years << "\t" << p->data->pages << std::endl;
      traversal(p->left, 1);
      traversal(p->right, 1);
    }
    else if (type == 2)
    {
      traversal(p->left, 2);
      std::cout << p->data->Author << "\t" << p->data->Title << "\t" << p->data->Publishing_house << "\t" << p->data->years << "\t" << p->data->pages << std::endl;
      traversal(p->right, 2);
    }
    else if (type == 3)
    {
      traversal(p->left, 3);
      traversal(p->right, 3);
      std::cout << p->data->Author << "\t" << p->data->Title << "\t" << p->data->Publishing_house << "\t" << p->data->years << "\t" << p->data->pages << std::endl;
    }
  }
}

void Search_tree1(tree *p, char house[])
{
  if (p != NULL)
  {
    if (strcmp(house, p->data->Publishing_house) == 0)
    {
      std::cout << p->data->Author << "\t" << p->data->Title << "\t" << p->data->Publishing_house << "\t" << p->data->years << "\t" << p->data->pages << std::endl;
      Search_tree1(p->left, house);
      Search_tree1(p->right, house);
    }
    else if (strcmp(house, p->data->Publishing_house) > 0)
    {
      Search_tree1(p->right, house);
    }
    else
    {
      Search_tree1(p->left, house);
    }
  }
}
void Search_tree2(tree *p, char house[], char title[])
{
  if (p != NULL)
  {
    if (strcmp(house, p->data->Publishing_house) == 0)
    {
      if (strcmp(title, p->data->Title) == 0)
      {
        std::cout << p->data->Author << "\t" << p->data->Title << "\t" << p->data->Publishing_house << "\t" << p->data->years << "\t" << p->data->pages << std::endl;
        Search_tree2(p->left, house, title);
        Search_tree2(p->right, house, title);
      }
      else if (strcmp(title, p->data->Title) > 0)
      {
        Search_tree2(p->right, house, title);
      }
      else
      {
        Search_tree2(p->left, house, title);
      }
    }
    else if (strcmp(house, p->data->Publishing_house) > 0)
    {
      Search_tree2(p->right, house, title);
    }
    else
    {
      Search_tree2(p->left, house, title);
    }
  }
}

void Search_tree3(tree *p, char house[], char title[], char author[])
{
  if (p != NULL)
  {
    if (strcmp(house, p->data->Publishing_house) == 0)
    {
      if (strcmp(title, p->data->Title) == 0)
      {
            if (strcmp(author,p->data->Author) == 0){
            std::cout << p->data->Author << "\t" << p->data->Title << "\t" << p->data->Publishing_house << "\t" << p->data->years << "\t" << p->data->pages << std::endl;
            Search_tree3(p->left, house, title, author);
            Search_tree3(p->right, house, title, author);
            }
            else if (strcmp(author, p->data->Author) > 0){
              Search_tree3(p->right, house, title, author);
            }
            else {
              Search_tree3(p->left, house, title, author);
            }
      }
      else if (strcmp(title, p->data->Title) > 0)
      {
        Search_tree3(p->right, house, title, author);
      }
      else
      {
        Search_tree3(p->left, house, title, author);
      }
    }
    else if (strcmp(house, p->data->Publishing_house) > 0)
    {
      Search_tree3(p->right, house, title, author);
    }
    else
    {
      Search_tree3(p->left, house, title, author);
    }
  }
}



void quickSortCoding(float *A, char *A2, int R, int L)
{
  while (L < R)
  {
    float x = A[L];
    int i = L;
    int j = R;
    while (i <= j)
    {
      while (A[i] > x)
        i++;
      while (A[j] < x)
        j--;

      if (i <= j)
      {
        char tmp_ch;
        tmp_ch = A2[i];
        A2[i] = A2[j];
        A2[j] = tmp_ch;

        float tmp_prop;
        tmp_prop = A[i];
        A[i] = A[j];
        A[j] = tmp_prop;
        i++;
        j--;
      }
    }

    if (j - L > R - i)
    {
      quickSortCoding(A, A2, R, i);
      R = j;
    }
    else
    {
      quickSortCoding(A, A2, j, L);
      L = i;
    }
  }
}

int Med(int L, int R)
{
  int m1;
  float SL, SR;
  SL = 0;
  for (int i = L; i < R; i++)
    SL = SL + chas[i];
  if (SL == 0)
    return 0;
  SR = chas[R];
  m1 = R;
  while (SL >= SR)
  {
    m1 = m1 - 1;
    SL = SL - chas[m1];
    SR = SR + chas[m1];
  }
  return m1;
}

void Fano(int L, int R, int k)
{
  int m;
  int i = L;
  if (L < R)
  {
    k++;
    m = Med(L, R);
    for (int i = L; i <= R; i++)
    {
      if (i <= m)
      {
        C[i][k - 1] = 0;
        Length[i] = Length[i] + 1;
      }
      else
      {
        C[i][k - 1] = 1;
        Length[i] = Length[i] + 1;
      }
    }
    Fano(L, m, k);
    Fano(m + 1, R, k);
  }
}

void coding()
{
  int j = 0, q = 0, i, kol = 0, sum = 0;
  double H = 0, Lsr = 0.0;
  std::fstream f("testBase1.dat", std::ios::in | std::ios::binary);
  if (!(f.is_open()))
  {
    std::cout << "Error. File don't open.'";
    exit(1);
  }
  char c;
  int m[256] = {0};
  while (!f.read((char *)&c, sizeof(c)).eof())
  {
    kol++;
    if (int(c) < 0)
      m[int(c) + 256]++;
    else
      m[int(c)]++;
  }
  f.close();
  for (int i = 0; i < 256; i++)
  {
    if (m[i] != 0)
      s++;
  }
  int x = 0;
  for (int itr = 0; itr < 256; itr++)
  {
    if (m[itr] != 0)
    {
      ch[x] = (char)itr;
      chas[x] = (float)m[itr] / kol;
      x++;
    }
  }
  quickSortCoding(chas, ch, s - 1, 0);
  Fano(0, s - 1, 0);
  for (i = 0; i < s; i++)
  {
    std::cout << (int)ch[i] << '\t' << ch[i] << '\t';
    printf("%.8f", chas[i]);
    std::cout << '\t' << '\t';
    for (j = 0; j < Length[i]; j++)
    {
      if ((i > 10) && (j == 0))
        std::cout << "1";
      else
        std::cout << C[i][j];
    }
    std::cout << std::endl;
  }
  for (i = 0; i < s; i++)
    H = H - chas[i] * (log(chas[i]) / log(2.0));
  for (i = 0; i < s; i++)
    Lsr = Lsr + chas[i] * Length[i];
  std::cout << "Kol-vo = " << kol << std::endl;
  std::cout << "Size = " << s << std::endl;
  std::cout << "Entropy " << H << std::endl;
  std::cout << "Average word length = " << Lsr << std::endl;
}

int main()
{
  SetConsoleCP(1600);
  SetConsoleOutputCP(1200);
  FILE *fin;
  fin = fopen("testBase1.dat", "rb");

  int z = 0, i, s_ind, s_n = -1;
  short int count, choice, x, a;
  bool b;
  int search_ind, search_n = -1;
  int key, key_page;
  char author[12];
  char *house = new char[16];
  char title[32];
  Beutifull_People *ind_arr[N];
  list *head = new list;
  list *tail;
  FS *head1 = new FS;
  FS *tail1 = new FS;
  list *p = head;
  list *index_arr[N];
  tail = &(*head);
  tail1 = &(*head1);
  for (int i = 0; i < N; i++)
  {
    p->data = new Beutifull_People;
    z = fread((Beutifull_People *)p->data, sizeof(Beutifull_People), 1, fin);

    if (i != N - 1)
    {
      p->next = new list;
      p = p->next;
    }
    else
    {
      p->next = NULL;
      tail = p;
    }
  }

  std::cout << "You choise: 1-database output (unsorted) 2-database output (sorted) 3-Search by key of search 4-tree by no key of search and search of tree  5-coding  0-exit" << std::endl;
  std::cin >> choice;
  if (choice == 1)
  {
    p = head;
    count = 1;
    x = 20;
    for (i = 0; i < N / 20 + 1; i++)
    {
      p = Printlist(p, count, x);
      std::cout << "Next 20?  1/0: ";
      std::cin >> b;
      if (b == false)
      {
        x = N - count + 1;
        p = Printlist(p, count, x);
        break;
        system("pause");
      }
    }
  }
  else if (choice == 2)
  {
    mergeSort(&head, &tail, N);
    p = head;
    x = 20;
    count = 1;
    for (i = 0; i < N / 20 + 1; i++)
    {
      p = Printlist(p, count, x);
      std::cout << "Next 20?  1/0: ";
      std::cin >> b;
      if (b == false)
      {
        x = N - count + 1;
        p = Printlist(p, count, x);
        break;
        system("pause");
      }
    }
  }
  else if (choice == 3)
  {
    // по пойску , делаем новую очередь по годам, дальше выводим очередь
    mergeSort(&head, &tail, N);
    key = Years();
    p = head;
    Index_arr(ind_arr, p, N);
    FS *p1 = head1;
    Search_Fast(ind_arr, key, p1, tail1);
    p1 = head1;
    Printlist(p1);
  }
  else if (choice == 4)
  {
    // не по поиску сортируем, тоесть по ключу уменьшаем, дальше делаем по чему хотим сортировать, и дальше выводим их
    mergeSort(&head, &tail, N);
    x = 20;
    count = 1;
    key = Years();
    p = head;
    Index_arr(ind_arr, p, N);
    FS *p1 = head1;
    Search_Fast(ind_arr, key, p1, tail1);
    p1 = head1;
    Printlist(p1);
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "Searh of Publishing House->Title->Author" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;

    p1 = head1;
    tree *root = new tree;
    root->data = p1->data;
    root->Bal = 0;
    root->left = NULL;
    root->right = NULL;
    p1 = p1->next;
    while (p1->data != NULL)
    {
      Add_AVL(root, p1);
      p1 = p1->next;
    }
    traversal(root, 2);
    int a, a1, a2;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "Do you want search full?(1/0)" << std::endl;
    std::cin >> a;

    if (a == 1)
    {
      fflush(stdin);
      std::cout << "Please enter Publishing house( 15 simvolov):";
      fgets(house, 16, stdin);
      std::cout << house << std::endl;
      Search_tree1(root, house);
      std::cout << "Do you want next search - Title? (1/0):";
      std::cin >> a1;

      if (a1 == 1)
      {
        fflush(stdin);
        std::cout << std::endl
                  << "Please enter Title (30 simvol probel):";
        fgets(title, 32, stdin);
        title[30] = '\0';
        title[31] = '\0';
        //for (int i = 0; i < 32; i++)
        //{
        //  std::cout << p->data->Title[i] << "_______" << title[i] << "/" << std::endl;
        //}
        // std::cout<<std::endl<<house;
        Search_tree2(root, house, title);
        std::cout << "Do you want next search - Author? (1/0)" << std::endl;
        std::cin >> a2;
        if (a2 == 1)
        {
          fflush(stdin);
          std::cout << "Please enter Author (11 simvolov):";
          fgets(author, 12, stdin);
          Search_tree3(root, house, title, author);
        }
      }
    }
  }

  else if (choice == 5)
  {
    coding();
  }

  else if (choice == 0)
  {
  }

  return 0;
  system("pause");

  // удаление всего;

  Deletelist(&head);
  Deletelist1(&head1);
  delete[] house;
  delete[] author;
  delete[] title;
  // удаление search
}
