#include "media.h"

static unsigned short keep_running;

using namespace std;

int main(){
    
    int voti[MAX_ESAMI];
    int cfu[MAX_ESAMI];
    int index = 0;
    int select;
    keep_running = 1;
    int ctrl,l;
    double media_p, media_A, media_a, media_P;
    int cfu_prev, resto;
    bool leng;
    
    while(1) {
        cout<<"Choose language"<<endl;
        cout<<"1) English\n2) Italiano"<<endl;
        cin>>l;
        if(l == 1) {
            leng = false;
            break;
        }
        else if(l == 2) {
            leng = true;
            break;
        } else {
            cout<<"Invalid option..."<<endl;
        }
    }

    if(leng)
        cout<<"[MAIN] Calcolo della media ponderata dei voti...\n";
    else
        cout<<"[MAIN] Calculation of the weighted average of the marks...\n";
    while(keep_running){
        if(leng) {
            cout<<"\nScegliere un operazione\n1) Aggiungi esami\n2) Calcolo media ponderata\n3) Stampa lista\n4) Cancella voto\n5) Previsioni media\n6) Massima media raggiungibile\n7) Minima media raggiungibile\n0) Exit\n";
            cout<<"\nNumero esami: "<<index<<endl;
            cout<<">> ";
        } else {
            cout<<"\nChoose an operation\n1) Add exams\n2) Calculation of the weighted average\n3) Print the list\n4) Remove grade\n5) Average forecasts\n6) Maximum achievable average\n7) Minimum achievable average\n0) Exit\n";
            cout<<"\nNumero esami: "<<index<<endl;
            cout<<">> ";
        }
        cin>>select;
        system("clear");
        cout<<endl;
        switch(select){
            case 1:
                resto = insertVoto(voti,cfu,index,leng) - index;
                index += resto;
                break;
            case 2:
                if(leng)
                    cout<<"Calcolo media..."<<endl;
                else
                    cout<<"Average calculation..."<<endl;
                usleep(500000);
                media_p = mediaPonderata(voti,cfu,index);
                media_P = (media_p * 110) / 30;
                media_a = mediaAritmetica(voti,index);
                media_A = (media_a * 110) / 30;
                if(leng) {
                    cout<<"\nNumero esami: "<<index<<"\nMedia aritmetica su 30: "<<media_a<<"\nMedia ponderata su 30: "<<media_p<<"\nMedia aritmetica su 110: "<<media_A<<"\nMedia ponderata su 110: "<<media_P<<endl;
                } else {
                    cout<<"\nNumber of exams: "<<index<<"\nArithmetic average over 30: "<<media_a<<"\nWeighted average over 30: "<<media_p<<"\nArithmetic average over 110: "<<media_A<<"\nWeighted average over 110: "<<media_P<<endl;
                }
                break;
            case 3:
                if(index != 0){
                    stampaLista(voti,cfu,index,leng);
                }else{
                    if(leng)
                        cout<<"\nNon ci sono voti registrati al momento..."<<endl;
                    else
                        cout<<"There are no votes registered at the moment..."<<endl;
                }
                break;
            case 4:
                ctrl = cancellaVoto(voti,cfu,index,leng);
                if(ctrl == 1){
                    index = index - 1;
                }else{
                    if(leng)
                        cout<<"\nVOTO NON TROVATO"<<endl;
                    else
                        cout<<"\nNOT FOUND"<<endl;
                    usleep(500000);
                }
                break;
            case 5:
                if(leng)
                    cout<<"\nInserire il numero di cfu del prossimo esame: ";
                else
                    cout<<"\nEnter the number of credits for the next exam: ";
                cin>>cfu_prev;
                cout<<endl;
                previsioniMedia(voti,cfu,index,cfu_prev,leng);
                break;
            case 6:
                maxMedia(voti,cfu,index,leng);
                break;
            case 7:
                minMedia(voti,cfu,index,leng);
                break;
            case 0:
                if(leng)
                    cout<<"\nUscita in corso...\n";
                else
                    cout<<"\nExit in progress...\n";
                keep_running = 0;
                break;
            default:
                if(leng)
                    cout<<"\n[ERROR] Opzione non valida\n";
                else
                    cout<<"\n[ERROR] Invalid option\n";
                break;
        }
    }
    return 0;
}
