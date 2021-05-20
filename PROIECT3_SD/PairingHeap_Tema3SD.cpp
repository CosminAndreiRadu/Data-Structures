#include<bits/stdc++.h>

using namespace std;

class Nod {
    private:

        int valoare;
        Nod* copilStang;
        Nod* frateDrept;

    public:

        Nod(int val = 0, Nod* copil = NULL, Nod* frate = NULL):valoare(val),copilStang(copil),frateDrept(frate){}

        void setValoare(int v);
        void setCopilStang(Nod* copil);
        void setFrateDrept(Nod* frate);

        int getValoare();
        Nod* getCopilStang();
        Nod* getFrateDrept();


};

void Nod::setValoare(int v){
    this->valoare = v;
}
void Nod::setCopilStang(Nod* copil){
    this->copilStang = copil;
}
void Nod::setFrateDrept(Nod* frate){
    this->frateDrept = frate;
}
int Nod::getValoare(){
    return this->valoare;
}
Nod* Nod::getCopilStang(){
    return this->copilStang;
}
Nod* Nod::getFrateDrept(){
    return this->frateDrept;
}


class PairingHeap {
    private:

        Nod* radacina;

    public:

        PairingHeap();
        PairingHeap(int x);
        void setRadacina(Nod* rad);
        Nod* getRadacina();

        bool isEmpty();
        void mergeHeaps(PairingHeap heap);
        void insertInHeap(int val);
        void heapify(vector<int> elemente);
        void twoPassMerge();
        void deleteMax();

};

PairingHeap::PairingHeap(){
    this->radacina = NULL;
}
PairingHeap::PairingHeap(int x){
    Nod* aux = new Nod(x);
    this->radacina = aux;
}
void PairingHeap::setRadacina(Nod* rad){
    this->radacina = rad;
}
Nod* PairingHeap::getRadacina(){
    return this->radacina;
}
bool PairingHeap::isEmpty(){
    if(this->radacina == NULL)
        return 1;
    return 0;
}
void PairingHeap::mergeHeaps(PairingHeap heap){

    if (heap.isEmpty()) {
        return;
    }

    if (this->isEmpty()) {

        this->setRadacina(heap.getRadacina());
        return;
    }


    if (this->getRadacina()->getValoare() <= heap.getRadacina()->getValoare()) {
        heap.getRadacina()->setFrateDrept(this->getRadacina()->getCopilStang());
        this->getRadacina()->setCopilStang(heap.getRadacina());

    }
    else {
        this->getRadacina()->setFrateDrept(heap.getRadacina()->getCopilStang());
        heap.getRadacina()->setCopilStang(this->getRadacina());
        this->setRadacina(heap.getRadacina());

    }


}
void PairingHeap::insertInHeap(int val){
    PairingHeap auxheap = PairingHeap(val);
    this->mergeHeaps(auxheap);

}
void PairingHeap::heapify(vector<int> elemente){

    if (elemente.size()) {
        Nod* aux = new Nod(elemente[0]);
        this->setRadacina(aux);

        for (int i = 1; i < elemente.size(); i++) {
            this->insertInHeap(elemente[i]);
        }
    }
}
void PairingHeap::twoPassMerge(){

    if (getRadacina()->getCopilStang() == NULL){
        setRadacina(NULL);
        return;
    }

    if (getRadacina()->getCopilStang()->getFrateDrept() == NULL){
        setRadacina(getRadacina()->getCopilStang());
        return;
    }

    vector<PairingHeap> aux;
    int nr = 0;

    Nod* curent = this->getRadacina()->getCopilStang();
    Nod* frateCurent = this->getRadacina()->getCopilStang()->getFrateDrept();
    Nod* frateUrmator = frateCurent->getFrateDrept();

    do {

        aux.push_back(PairingHeap());
        PairingHeap frateDreptHeap = PairingHeap();

        aux[nr].setRadacina(curent);
        frateDreptHeap.setRadacina(frateCurent);

        aux[nr].mergeHeaps(frateDreptHeap);

        if (frateUrmator == NULL){
            nr++;
            break;
        }

        curent = frateUrmator;

        if(curent->getFrateDrept() == NULL) {
            nr++;

            aux.push_back(PairingHeap());
            aux[nr].setRadacina(curent);

            nr++;
            break;
        }

        frateCurent = curent->getFrateDrept();
        frateUrmator = frateCurent->getFrateDrept();

        nr++;

    } while (curent != NULL);


    this->setRadacina(aux[nr - 1].getRadacina());

    for (int i = nr - 2; i >= 0; i--) {

        this->mergeHeaps(aux[i]);

    }

}
void PairingHeap::deleteMax(){
    if (!this->isEmpty()){
        this->twoPassMerge();
    }
}


int main() {

    vector<PairingHeap> heapuri;
    int nrHeapuri = 0;
    int ok = 1, op;
    cout<<"Tema 3:     Pairing Heap(de minim)";
    cout<<"\nProiect realizat de Radu Cosmin-Andrei";
    cout<<"\nin cadrul laboratorului de Structuri de Date.";

    while(ok){
            cout<<"\n\n\n1. Build/Heapify";
            cout<<"\n2. Insert element in Heap";
            cout<<"\n3. Delete min from Heap";
            cout<<"\n4. Merge 2 Heaps";
            cout<<"\n5. Exit";
            cout<<"\n\nIntroduceti comanda: ";
            cin>>op;

            switch(op){

                case 1:{
                    int n,x;
                    PairingHeap heap;
                    vector<int> elemente;
                    cout<<"\nNr de elemente: ";
                    cin>>n;
                    cout<<"\nIntroduceti elementele: ";
                    for(int i = 0; i < n; i++)
                        {
                            cin>>x;
                            elemente.push_back(x);
                        }
                    heap.heapify(elemente);
                    heapuri.push_back(heap);
                    nrHeapuri++;
                    cout<<"\nHeap-ul "<<nrHeapuri-1<<" a fost creat;";

                    break;
                }


                case 2:{
                    cout<<"\nIn care heap doriti sa inserati element? ";
                    cout<<"\nAlegeti un numar intre 0 si "<<nrHeapuri-1<<": ";
                    int y,nr;
                    cin>>y;
                    cout<<"\nCe numar doriti sa inserati? ";
                    cin>>nr;

                    heapuri[y].insertInHeap(nr);
                    cout<<"Numarul a fost inserat in heap;";
                    break;
                }
                case 3:{
                    cout<<"\nDinn care heap doriti sa stergeti minimul? ";
                    cout<<"\nAlegeti un numar intre 0 si "<<nrHeapuri-1<<": ";
                    int y;
                    cin>>y;
                    cout<<"\nMinimul inainte de stergere: ";
                    cout<<heapuri[y].getRadacina()->getValoare();
                    heapuri[y].deleteMax();
                    cout<<"\nMinimul dupa stergere: ";
                    cout<<heapuri[y].getRadacina()->getValoare();
                    break;

                }

                case 4:{
                    int x,y;
                    cout<<"\n Alegeti 2 heap-uri pentru a face merge din intervalul: 0 - "<<nrHeapuri-1<<": ";
                    cout<<"\nMerge la heap-ul: ";
                    cin>>x;
                    cout<<" cu heap-ul: ";cin>>y;

                    heapuri[x].mergeHeaps(heapuri[y]);
                    break;
                }

                case 5:{
                    ok = 0;
                    break;
                }
            }




    }



    return 0;
}
