#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

char macierz_kombinacji[500][100];
int jot=0;

int silnia(int x, int y)
{
    if(x == y) return 1;
    return x*silnia(x-1, y);
}

int ile_komb(int n, int k)
{

    k = min(k, n-k);
    int K = n-k;
    int L = silnia(n, K);
    int M =silnia(k,0);
    return L/M;
}

void combinationUtil(char arr[], char data[], int start, int ende, int index, int r)
{
    if (index == r)
    {
        for (int j=0; j<r; j++)
            macierz_kombinacji[jot][j]=data[j];
        jot++;
        return;
    }

    for (int i=start; ((i<=ende) && (ende-i+1 >= r-index)); i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, data, i+1, ende, index+1, r);
    }
}

void zapodej_macierza(char arr[], int n, int r)
{
    char data[r];

    combinationUtil(arr, data, 0, n-1, 0, r);
}

int main()
{

    int ile, ilosc, komb;
    bool iloscpodano=0;
    string slowo = "";
    string stareslowo="";

    while(1)
    {

        cin.clear();
        fflush(stdin);

        if(!iloscpodano){
        cout<<"podaj litery"<<endl;
        cin>>slowo;
        stareslowo = slowo;
        cout<<"ile literowe ma byc slowo?"<<endl;
        cin>>ilosc;
        }
        else{
            slowo = stareslowo;
        }

        ile = slowo.length();
        komb = ile_komb(ile,ilosc);
        char liter[ile];

        for(int i=0; i<ile; i++)
        {
            if(slowo[i]<97 || slowo[i]>122)
                liter[i] = '{';
            else
                liter[i] = slowo[i];
        }
        jot = 0;

        sort(liter, liter+ile);

        zapodej_macierza(liter, ile, ilosc);

        ifstream slownik("sjp-20170924/slowa.txt");

        bool dalej = true;
        char permut[ilosc];

        slowo= "aa";
//        system("cls");
        while((int)slowo[0]<=(int)liter[ile-1] && !slownik.eof())
        {
            slownik>>slowo;

            if(slowo.length()==ilosc)
            {
                for(int i=0; i<ilosc; i++)
                {
                    permut[i] = slowo[i];
                }

                for(int i=0; i<komb; i++)
                {
                    if(is_permutation(permut, permut+ilosc, macierz_kombinacji[i]))
                    {
                        cout<<slowo<<endl;
                        break;
                    }
                }
            }

        }

        slownik.close();
        cout<<"no to tyle"<<endl;

        cin.clear();
        fflush(stdin);

        if(cin>>ilosc){
            iloscpodano = 1;
        }
        else{
            iloscpodano = 0;
        }

        system("cls");
    }


    return 0;
}
