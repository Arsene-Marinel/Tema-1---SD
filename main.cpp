#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <sys/time.h>
#include <iomanip>
#include <vector>
using namespace std;
ifstream f("citire.in");
ofstream g("citire.out");

int n, maxx;

void bubble_sort(int v[])
{
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n - i; j++)
            if(v[j] > v[j+1])
            {
                long long aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
}

void count_sort(int v[])
{
    int i, ap[maxx + 1] = {0};
    for(i = 1; i <= n; i++)
        ap[v[i]]++;
    for(int j = maxx; j >= 0 ; j--)
        while(ap[j] != 0)
        {
            v[--i] = j;
            ap[j]--;
        }
}

void countingsort(int v[], int n, int expp)
{
    int output[n + 1], ap[10] = {0};
    for(int i = 1; i <= n; i++)
        ap[(v[i]/expp) % 10]++;
    for(int i = 1; i <= 9; i++)
        ap[i] += ap[i - 1];       ///ap[i] va contine pozitia cifrei la iesire
    for (int i = n; i >= 1; i--)
    {
        output[ap[(v[i]/expp) % 10]] = v[i];
        ap[(v[i]/expp) % 10]--;
    }
    for (int i = 1; i <= n; i++)
        v[i] = output[i];
}

void radix_sort(int v[])
{
    for(int expp = 1; maxx/expp > 0; expp *= 10)
        countingsort(v, n, expp);
}

void interclasare(int v[], int p, int u, int m)
{
    int i = p, j = m + 1, k = 1;
    long long b[n + 1];
    while(i <= m && j <= u)
        if(v[i] <= v[j])
            b[k++] = v[i++];
        else
            b[k++] = v[j++];
    while(i <= m)
        b[k++] = v[i++];
    while(j <= u)
        b[k++] = v[j++];
    for(i = p, k = 1; i <= u; i++, k++)
        v[i] = b[k];
}

void mergesort(int v[], int p, int u)
{
    if(p < u)
    {
        int m = (p + u) / 2;
        mergesort(v, p, m);
        mergesort(v, m + 1, u);
        interclasare(v, p, u, m);
    }
}

int pivot(int v[], int p, int u)
{
    int cp = 0, cu = -1;
    while(p < u)
    {
        if(v[p] > v[u])
        {
            int aux = v[p];
            v[p] = v[u];
            v[u] = aux;
            //
            aux = cp;
            cp = -cu;
            cu = -aux;
        }
        p += cp;
        u += cu;
    }
    return p; ///pozitia pivotului
}

void quicksort(int v[], int p, int u)
{
    if(p < u)
    {
        int k = pivot(v, p, u);
        quicksort(v, p, k - 1);
        quicksort(v, k + 1, u);
    }
}

bool testare(int v[])
{
    for(int i = 1; i < n; i++)
        if(v[i] > v[i + 1])
        {
            g << "Vectorul nu este sortat\n";
            return 0;
        }
    if(n != 0)
    {
        g << "Vectorul este sortat\n";
        return 1;
    }
    else
    {
        g << "Vectorul nu este sortat\n";
        return 0;
    }
}

int main()
{
    int nr_teste;
    f >> nr_teste;
    for(int j = 1; j <= nr_teste; j++)
    {
        f >> n >> maxx;
        g << n << ' ' << maxx << '\n';

        int x[n + 1], copie[n + 1];
        for(int i = 1; i <= n; i++)
        {
            f >> x[i];
            copie[i] = x[i];
        }
        struct timeval start, endd;
        double time_taken;

        //STL sort

        gettimeofday(&start, NULL);
        ios_base::sync_with_stdio(false);
        sort(copie + 1, copie + n + 1);
        gettimeofday(&endd, NULL);
        g << "sort function: ";
        time_taken = (endd.tv_sec - start.tv_sec) * 1e6;
        time_taken = (time_taken + (endd.tv_sec - start.tv_sec)) * 1e-6;
        g <<"Timpul rularii programului este:" << fixed << time_taken << setprecision(5) << " seconds\n";

        //Bubble sort

        if(n > 10000)
            g << "bubble_sort nu functioneaza\n";
        else
        {
            for(int i = 1; i <= n; i++)
                copie[i] = x[i];

            gettimeofday(&start, NULL);
            ios_base::sync_with_stdio(false);
            bubble_sort(copie);
            gettimeofday(&endd, NULL);

            bool ok = testare(copie);
            if(ok == 1)
            {
                g << "bubble_sort: ";
                time_taken = (time_taken + (endd.tv_sec - start.tv_sec)) * 1e-6;
                g <<"Timpul rularii programului este:" << fixed << time_taken << setprecision(5) << " seconds\n";
            }
        }

        //Count sort

        if(maxx > 1000000)
            g << "count_sort nu functioneaza\n";
        else
        {
            for(int i = 1; i <= n; i++)
                copie[i] = x[i];

            gettimeofday(&start, NULL);
            ios_base::sync_with_stdio(false);
            count_sort(copie);
            gettimeofday(&endd, NULL);

            bool ok = testare(copie);
            if(ok == 1)
            {
                g<<"count_sort: ";
                time_taken = (time_taken + (endd.tv_sec - start.tv_sec)) * 1e-6;
                g <<"Timpul rularii programului este:" << fixed << time_taken << setprecision(5) << " seconds\n";
            }
        }

        //Radix sort

        for(int i = 1; i <= n; i++)
            copie[i] = x[i];

        gettimeofday(&start, NULL);
        ios_base::sync_with_stdio(false);
        radix_sort(copie);
        gettimeofday(&endd, NULL);

        bool ok = testare(copie);
        if(ok == 1)
        {
            g<<"radix_sort: ";
            time_taken = (time_taken + (endd.tv_sec - start.tv_sec)) * 1e-6;
            g <<"Timpul rularii programului este:" << fixed << time_taken << setprecision(5) << " seconds\n";
        }

        //Merge sort

        for(int i = 1; i <= n; i++)
            copie[i] = x[i];

        gettimeofday(&start, NULL);
        ios_base::sync_with_stdio(false);
        mergesort(copie, 1, n);
        gettimeofday(&endd, NULL);

        ok = testare(copie);
        if(ok == 1)
        {
            g<<"mergesort: ";
            time_taken = (time_taken + (endd.tv_sec - start.tv_sec)) * 1e-6;
            g <<"Timpul rularii programului este:" << fixed << time_taken << setprecision(5) << " seconds\n";
        }

        //

        for(int i = 1; i <= n; i++)
            copie[i] = x[i];

        gettimeofday(&start, NULL);
        ios_base::sync_with_stdio(false);
        quicksort(copie, 1, n);
        gettimeofday(&endd, NULL);

        ok = testare(copie);
        if(ok == 1)
        {
            g<<"quicksort: ";
            time_taken = (time_taken + (endd.tv_sec - start.tv_sec)) * 1e-6;
            g <<"Timpul rularii programului este:" << fixed << time_taken << setprecision(5) << " seconds\n";
        }

        g<<'\n'<<'\n';
    }
    return 0;
}
