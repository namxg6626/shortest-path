#include <bits/stdc++.h>
using namespace std;

int a[3][3] = {{2, 8, 3}, {1, 6, 4}, {7, 0, 5}}; // input matrix
int A[3][3] = {{1, 2, 3}, {8, 0, 4}, {7, 6, 5}}; // output matix
int b[3][3] = {{2, 8, 3}, {1, 6, 4}, {7, 0, 5}}; // temp matrix

int I, J, I1, J1, g = 0, h;

void XuLy();
int KetThuc();
int Tinh();
int Tim(int a);
void TimDinhTrong();
void Swap(int &a, int &b);
void XetChon();
void Chep1();
void Chep2();

int main()
{
  XuLy();
  cout << endl
       << "So buoc lap: g = " << g;
}

void XuLy()
{
  while (!KetThuc())
  {
    g++;
    XetChon();
    cout << endl
         << "So o chua dung vi tri: h = "
         << h << endl;
    for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j < 3; j++)
        cout << a[i][j] << " ";
      cout << endl;
    }
  }
}

int KetThuc()
{
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (a[i][j] != A[i][j])
        return 0;
  return 1;
}

int Tinh()
{
  int bac = 0;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (Tim(b[i][j]))
        bac += abs(I1 - i) + abs(J1 - j);
    }
  }
  return bac;
}

int Tim(int x)
{
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (A[i][j] == x && x != 0)
      {
        I1 = i;
        J1 = j;
        return 1;
      }
  return 0;
}

void TimDinhTrong()
{
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (a[i][j] == 0)
      {
        I = i;
        J = j;
      }
}

void Swap(int &x, int &y)
{
  int temp;
  temp = x;
  x = y;
  y = temp;
}

void XetChon()
{
  int min = 100;
  TimDinhTrong();
  for (int j = 0; j < 3; j++)
    for (int l = 0; l < 3; l++)
    {
      if ((abs(I - j) + (abs(J - l)) == 1))
      {
        Swap(b[j][l], b[I][J]);
        h = Tinh();
        if (h <= min)
        {
          min = h;
          Chep2();
        }
        Swap(b[j][l], b[I][J]);
      }
    }
  Chep1();
  h = min;
}

void Chep1()
{
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      b[i][j] = a[i][j];
}

void Chep2()
{
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      a[i][j] = b[i][j];
}
