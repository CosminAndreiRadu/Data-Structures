#include <bits/stdc++.h>



using namespace std;
using namespace std::chrono;

ifstream input("date.txt");


// maxim
//=============================================================================================================
int getmax(vector<int> &v, int n)
{
    int maxim = v[0];
    for (int i=1; i<n; i++)
        if (v[i] > maxim)
            maxim = v[i];
    return maxim;
}

// Generare vector
//=============================================================================================================
void randomgen(int n, int maxim, vector<int> & v)
{

    srand((unsigned)time(0));

    for(int i = 0; i < n; i++)
    {
    v.push_back((rand()*rand())%maxim+1);


    }
}

void constantgen(int n, int maxim,vector<int> &v)
{
    for (int i=0;i<n;i++)
        v.push_back(maxim);


}

void descgen(int n, int maxim,vector<int> &v)
{
    for(int i=n-1;i>=0;i--)
        v.push_back(i);
}

// verificare daca vectorul e sortat
//=============================================================================================================
int vSortat(int n, vector<int> &v)
{

    for(int i=0; i<n-1; i++)
        if(v[i]>v[i+1]) return 0;


    return 1;

}
// 1) bubble
//=============================================================================================================
void bubbleSort(int nr_elemente,vector <int> &v)
{
        if(nr_elemente>=(50000))
        {cout<<"Ineficient pentru n> 5*10^4\n";return;}
    {


        auto t0 = high_resolution_clock::now();
        int i,j;
        bool ok;


        for(i = 0; i < nr_elemente-1; i++)
        {
            ok = 0;
            for( j = 0; j < nr_elemente - i - 1; j++)
            {

                if(v[j] > v[j+1])
                {
                    //swap(v[j],v[j+1]);
                    v[j] = v[j] + v[j+1];
                    v[j+1] = v[j] - v[j+1];
                    v[j] = v[j] - v[j+1];

                    ok = 1;

                }

            }

            if(ok == 0)
                break;


        }


        auto t1 = high_resolution_clock::now();
    auto durata = duration_cast<microseconds>(t1-t0);
    if(vSortat(nr_elemente,v))
    cout<<"Sortare reusita | "<<durata.count()/1000000.00000000000000<<" secunde\n";
    else cout<<"Absolut ineficient";
}
}

// 2) count
//=============================================================================================================
void countSort(int nr_elemente, vector<int> &v)
{
    auto t0 = high_resolution_clock::now();
    int  maxim,i, j = 0;

    maxim = getmax(v,nr_elemente);

            vector<int> counter;

    for( i = 0; i<= maxim; i++)
        counter.push_back(0);

    for( i = 0; i< nr_elemente; i++)
        counter[v[i]]++;

    for( i = 0; i <= maxim; i++)
        while(counter[i] > 0)
        {
            v[j++] = i;
            counter[i]--;

        }

    auto t1 = high_resolution_clock::now();
    auto durata = duration_cast<microseconds>(t1-t0);
    if(vSortat(nr_elemente,v))
    cout<<"Sortare reusita | "<<durata.count()/1000000.00000000000000<<" secunde \n";
    else cout<<"Absolut ineficient";
    counter.clear();




}

// pivoti pt qs
//=============================================================================================================
int medianaDin3(int left, int right, vector <int> &v)
{
    int x,y,z,i,j;
    x = v[left];
    y = v[(right-left)/2+left];
    z = v[right-1];
    i = left-1;
    j = right;

    if((y>x && y<z )||( y>z && y<x))
        x=y;
    else if((z>x && z<y )|| (z>y && z<x))
        x=z;

    while(301)
    {
        do
        {
            j--;
        }
        while(v[j]>x);

        do
        {
            i++;
        }
        while(v[i]<x);

        if (i<j) swap(v[i],v[j]);
        else return j+1;


    }


}

int standardPivot(int left, int right, vector<int> &v)
{

    int pivot = v[right];
    int i = left-1;

    for( int j = left; j<= right -1; j++)
    {
        if(v[j] <= pivot)
        {
            i++;
            swap(v[i],v[j]);
            //v[i] = v[i] + v[j];
            // v[j] = v[i] - v[j];
            //v[i] = v[i] - v[j];
        }

    }


    swap(v[i+1],v[right]);
    return (i+1);


}

int randomPivot(int left, int right, vector<int> &v)
{
    srand(time(NULL));
    int random = left + rand()%(right - left);

    swap(v[random],v[right]);

    return standardPivot(left,right, v);


}

// 3) quicksorts
//=============================================================================================================
void standardQuickSort(int stanga, int dreapta, vector<int> &v)
{
    int pv;
    if (stanga < dreapta)
    {
        pv = standardPivot(stanga, dreapta, v);

        standardQuickSort(stanga, pv -1, v );
        standardQuickSort(pv+1, dreapta, v);

    }


}

void median3QuickSort(int stanga, int dreapta, vector<int> &v)
{
    int pv;
    if (dreapta-stanga>=2)
    {
        pv = medianaDin3(stanga,dreapta,v);

        median3QuickSort(stanga,pv,v);
        median3QuickSort(pv,dreapta,v);


    }



}

void randomQuickSort(int stanga, int dreapta, vector<int> &v)
{
    if (stanga<dreapta)
    {
        int pv = randomPivot(stanga,dreapta,v);

        randomQuickSort(stanga,pv-1,v);
        randomQuickSort(pv+1,dreapta,v);

    }

}

// 4) merge sort
//=============================================================================================================
void mergeFunction(int left, int mid, int right, vector<int> &v)
{
    int lungime1 = mid - left +1;
    int lungime2 = right-mid;

    vector<int> L;
    vector<int> R;

    for (int i = 0; i < lungime1; i++)
        L.push_back(v[left+i]);
    for (int j = 0; j < lungime2; j++)
        R.push_back(v[mid+j+1]);


    int i=0, j=0;
    int k = left;

    while ( i < lungime1 && j < lungime2)
    {
        if(L[i] <= R[j])
        {
            v[k] = L[i];
            i++;
        }
        else
        {
            v[k] = R[j];
            j++;
        }

        k++;
    }

    while(i < lungime1)
    {
        v[k] = L[i];
        i++;
        k++;
    }

    while(j < lungime2)
    {
        v[k] = R[j];
        j++;
        k++;
    }
    L.clear();
    R.clear();

}

void mergeSort(int stanga, int dreapta, vector<int> &v)
{
    if(stanga>=dreapta)
    {
        return;
    }

    int mijloc = stanga + (dreapta-stanga)/2;
    mergeSort(stanga,mijloc,v);
    mergeSort(mijloc+1,dreapta,v);
    mergeFunction(stanga,mijloc,dreapta,v);




}

// 5) radix sort
//==============================================================================================================

void countForRadix(vector<int> &a, int n, int exp,int baza)
{
    vector<int> result;

    int i;
    for(i = 0; i<= n; i++)
    {
        result.push_back(0);
    }


    vector<int> counter;

    for(i = 0; i<= baza; i++)
    {
        counter.push_back(0);
    }

    // Counting occurence of digits
    for (i =0; i <n; i++)
        counter[(a[i] / exp) % baza]++;

    // Changing the position of count so that it appears at actual position in result.
    for (i =1; i<baza; i++)
        counter[i] += counter[i-1];

    // Resultant output array
    for (i =n-1; i>= 0; i--)
    {
        result[counter[(a[i] / exp) % baza] - 1] = a[i];
        counter[(a[i] / exp) % baza]--;
    }
    for (i =0; i <n; i++)
        a[i] = result[i];

    result.clear();
    counter.clear();
}

void radixsort(vector<int> &v, int n,int baza)
{
    auto t0 = high_resolution_clock::now();

    int exp, i;
    i = getmax(v,n);
    for (exp = 1; i/exp > 0; exp *= baza)
        countForRadix(v, n, exp,baza);

    auto t1 = high_resolution_clock::now();
    auto durata = duration_cast<microseconds>(t1-t0);
    if(vSortat(n,v))
    cout<<"Sortare reusita | "<<durata.count()/1000000.00000000000000<<" secunde \n";
    else cout<<"Sortare nereusita\n";
}


int main()
{
    vector<int> v;
    vector<int> copie;

    static int nr_teste;
    int nr_numerePERtest, nr_maxim ;
    input>>nr_teste;

    for(int i=0;i<nr_teste;i++)
    {
     input>>nr_numerePERtest>>nr_maxim;
     cout<<"----------------------------------------------------------------------\n";
     cout<<"Testul "<<i+1<<"|"<<" numar elemente: "<<nr_numerePERtest<<"| maxim: "<<nr_maxim<<"\n----------------------------------------------------------------------\n";
     randomgen(nr_numerePERtest,nr_maxim,v);

     for(int i=0;i<nr_numerePERtest;i++)
        copie.push_back(v[i]);
        cout<<">BubbleSort:                       ";
        bubbleSort(nr_numerePERtest,copie);
        cout<<"\n";
        copie.clear();

    for(int i=0;i<nr_numerePERtest;i++)
        copie.push_back(v[i]);
        cout<<">QuickSort: \n"<<" -Pivot standard(ultimul element): ";
        auto t0 = high_resolution_clock::now();
        if(nr_numerePERtest >= 1000000)
        cout<<"Ineficient pentru n> 10^6\n";
        else
        {
        standardQuickSort(0,nr_numerePERtest,copie);
        auto t1 = high_resolution_clock::now();
        auto durata = duration_cast<microseconds>(t1-t0);

        if(vSortat(nr_numerePERtest,copie))
        cout<<"Sortare reusita | "<<durata.count()/1000000.00000000000000<<" secunde\n";
        else cout<<"Sortare nereusita";}
        cout<<"\n";
        copie.clear();

     for(int i=0;i<nr_numerePERtest;i++)
        copie.push_back(v[i]);
        cout<<" -Pivot mediana(din 3):            ";
        auto t01 = high_resolution_clock::now();
        median3QuickSort(0,nr_numerePERtest,copie);
        auto t11 = high_resolution_clock::now();
        auto durata1 = duration_cast<microseconds>(t11-t01);
        if(vSortat(nr_numerePERtest,copie))
        cout<<"Sortare reusita | "<<durata1.count()/1000000.00000000000000<<" secunde\n";
        else cout<<"Sortare nereusita";
        cout<<"\n";
        copie.clear();

     for(int i=0;i<nr_numerePERtest;i++)
        copie.push_back(v[i]);
        cout<<" -Pivot random:                    ";
        auto t02 = high_resolution_clock::now();
        median3QuickSort(0,nr_numerePERtest,copie);
        auto t12 = high_resolution_clock::now();
        auto durata2 = duration_cast<microseconds>(t12-t02);
        if(vSortat(nr_numerePERtest,copie))
        cout<<"Sortare reusita | "<<durata2.count()/1000000.00000000000000<<" secunde\n";
        else cout<<"Sortare nereusita";
        cout<<"\n";
        copie.clear();

     for(int i=0;i<nr_numerePERtest;i++)
        copie.push_back(v[i]);
        cout<<">CountSort:                        ";
        countSort(nr_numerePERtest, copie);
        cout<<"\n";
        copie.clear();

    for(int i=0;i<nr_numerePERtest;i++)
        copie.push_back(v[i]);
        cout<<">MergeSort:                        ";
        auto t03 = high_resolution_clock::now();
        if(nr_numerePERtest>10000000)
        cout<<"Ineficient pentru n> 10^7\n";
        else
        {


        mergeSort(0,nr_numerePERtest,copie);
        auto t13 = high_resolution_clock::now();
        auto durata3 = duration_cast<microseconds>(t13-t03);
        if(vSortat(nr_numerePERtest,copie))
        cout<<"Sortare reusita | "<<durata3.count()/1000000.00000000000000<<" secunde\n";
        else cout<<"Sortare nereusita";}


        cout<<"\n";
        copie.clear();

    for(int i=0;i<nr_numerePERtest;i++)
            copie.push_back(v[i]);
            cout<<">C++NativeSort:                    ";
            auto t04 = high_resolution_clock::now();
            sort(copie.begin(), copie.end());
            auto t14 = high_resolution_clock::now();
            auto durata4 = duration_cast<microseconds>(t14-t04);
            if(vSortat(nr_numerePERtest,copie))
            cout<<"Sortare reusita | "<<durata4.count()/1000000.00000000000000<<" secunde\n";
            else cout<<"Sortare nereusita";
            cout<<"\n";
            copie.clear();

    for(int i=0;i<nr_numerePERtest;i++)
        copie.push_back(v[i]);
        cout<<">RadixSort: \n"<<" -Baza 2:                          ";
        radixsort(copie,nr_numerePERtest,2);
        cout<<"\n";
        copie.clear();

    for(int i=0;i<nr_numerePERtest;i++)
        copie.push_back(v[i]);
        cout<<" -Baza 16:                         ";
        radixsort(copie,nr_numerePERtest,16);
        cout<<"\n";
        copie.clear();

    for(int i=0;i<nr_numerePERtest;i++)
        copie.push_back(v[i]);
        cout<<" -Baza 256:                        ";
        radixsort(v,nr_numerePERtest,256);
        cout<<"\n";
        copie.clear();





        //for(int i=0;i<nr_numerePERtest;i++)
          //  cout<<copie[i]<<" ";

        v.clear();
    }








    return 0;
}
