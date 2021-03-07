#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include "media.h"

using namespace std;

double mediaPonderata(int* voti, int* cfu, int index){

    double res = 0;
    double num = 0;
    double den = 0;

    for(int i = 0; i < index; i++){
        num += (voti[i] * cfu[i]);
        den += cfu[i];
    }
    res = num / den;
    return res;
}

double mediaAritmetica(int* voti, int index){

    double res = 0;
    double num = 0;
    for(int i = 0; i < index; i++){
        num += voti[i];
    }
    res = num / index;
    return res;
}

void stampaLista(int* voti, int* cfu, int index, bool leng){

    if(leng)
        cout<<"Voto     CFU"<<endl;
    else
        cout<<"Grade     credits"<<endl;
    for(int i = 0; i < index; i++){
        cout<<" "<<voti[i]<<"      "<<cfu[i]<<endl;
    }
    cout<<"\n"<<endl;
}

int cancellaVoto(int* voti, int* cfu, int index, bool leng){
    
    stampaLista(voti,cfu,index,leng);
    if(leng)
        cout<<"Inserisci il voto che vuoi cancellare: ";
    else
        cout<<"Enter the grade you want to delete: ";
    int voto, c;
    int i = 0;
    cin>>voto;
    if(leng)
        cout<<"Inserire il numero di CFU: ";
    else
        cout<<"Enter the number of credits: ";
    cin>>c;
    while(i < index){
        if(voto == voti[i] && c == cfu[i]){
            break;
        }
        i++;
    }
    if(voto == voti[i] && c == cfu[i]){
        for(int start = i; start < index; start++){
            voti[start] = voti[start+1];
            cfu[start] = cfu[start+1];
            if(start == index - 1){
                voti[start] = 0;
                cfu[start] = 0;
                return 1;
            }
        }
    }
    return 0;
}

void previsioniMedia(int* voti, int* cfu, int index, int cfu_prev, bool leng){
    
    int voti_temp[MAX_ESAMI];
    copiaArray(voti,voti_temp,index);
    int cfu_temp[MAX_ESAMI];
    copiaArray(cfu,cfu_temp,index);
    int index_temp = index;
    unsigned short divisore = 0;
    
    if(leng)
        cout<<"Previsioni media"<<endl;
    else
        cout<<"Average forecasts"<<endl;
    
    for(int i = 18; i <= 30; i++){
        voti_temp[index_temp] = i;
        cfu_temp[index_temp] = cfu_prev;
        index_temp++;
        if(mediaPonderata(voti,cfu,index) < mediaPonderata(voti_temp,cfu_temp,index_temp) && divisore == 0){
            cout<<"-------------------"<<endl;
            divisore = 1;
        }
        cout<<i<<":     "<<mediaPonderata(voti_temp,cfu_temp,index_temp)<<endl;
        index_temp--;
    }
}

int insertVoto(int* voti, int* cfu, int index, bool leng){
    
    int voto, cfu2;
    int index_temp = index;
    if(leng)
        cout<<"Inserire 0 per uscire"<<endl;
    else
        cout<<"Enter 0 to exit"<<endl;
    while(1){
        if(leng)
            cout<<"Voto: ";
        else
            cout<<"Grade: ";
        cin>>voto;
        if(voto == 0){
            break;
        }else {
            if(voto < 18){
                if(leng)
                    cout<<"Voto minimo: 18\n Reimposto..."<<endl;
                else
                    cout<<"Minimum grade: 18\n Fixing..."<<endl;
                usleep(500000);
                voto = 18;
            }
            if(voto > 30){
                if(leng)
                    cout<<"Voto massimo: 30\n Reimposto..."<<endl;
                else
                    cout<<"Maximum grade: 30\n Fixing..."<<endl;
                usleep(500000);
                voto = 30;
            }
        }
        if(leng)
            cout<<"CFU: ";
        else
            cout<<"Credits: ";
        cin>>cfu2;
        if(cfu2 == 0){
            break;
        }
        voti[index_temp] = voto;
        cfu[index_temp] = cfu2;
        index_temp++;
    }
    return index_temp;
}

void copiaArray(int* array1, int* array2, int index){
    for(int i = 0; i < index; i++){
        array2[i] = array1[i];
    }
}

void maxMedia(int* voti, int* cfu, int index, bool leng){
    int num, opt, i;
    int voti_t[MAX_ESAMI];
    copiaArray(voti,voti_t,index);
    int cfu_t[MAX_ESAMI];
    copiaArray(cfu,cfu_t,index);
    if(leng)
        cout<<"Inserire il numero di esami mancanti\n >> ";
    else
        cout<<"Enter the number of missing exams\n >>"<<endl;
    cin>>num;
    if(leng) {
        cout<<"\nSelezionare una delle seguenti opzioni"<<endl;
        cout<<" 1) Sono "<<num<<" esami da 9 cfu\n2) Sono "<<num<<" esami da 6 cfu\n3) Seleziona cfu manualmente"<<endl;
        cout<<">> ";
    } else {
        cout<<"\nSelect one of the following options"<<endl;
        cout<<"1) There are "<<num<<" exams of 9 credits\n2) There are "<<num<<" exams of 6 credits\n3) Enter the credits manually"<<endl;
        cout<<">> ";
    }
    cin>>opt;
    switch(opt){
        case 1:
            for(i = index; i < index + num; i++){
                voti_t[i] = 30;
                cfu_t[i] = 9;
            }
            break;
        case 2:
            for(i = index; i < index + num; i++){
                voti_t[i] = 30;
                cfu_t[i] = 6;
            }
            break;
        case 3:
            for(i = index; i < index + num; i++){
                voti_t[i] = 30;
                if(leng)
                    cout<<"Inserire cfu\n >> ";
                else
                    cout<<"Insert credits\n >>";
                cin>> cfu_t[i];
            }
            break;
        default:
            if(leng)
                cout<<"Opzione non valida"<<endl;
            else
                cout<<"Invalid option"<<endl;
            break;
    }
    int tot = index + num;
    double media = mediaAritmetica(voti_t,tot);
    double Media = (media * 110) / 30;
    double mediaP= mediaPonderata(voti_t,cfu_t,tot);
    double MediaP = (mediaP * 110) / 30;
    if(leng) {
        cout<<"\nMassimo della media raggiungibile con tutti gli esami"<<endl;
        cout<<"Media Aritmetica: "<<media<<"\nMedia Ponderata: "<<mediaP<<"\nMedia Aritmetica su 110: "<<Media<<"\nMedia Ponderata su 110: "<<MediaP<<endl;
    } else {
        cout<<"\nMaximum of the average achievable with all exams"<<endl;
        cout<<"Arithmetic average: "<<media<<"\nWeighted average: "<<mediaP<<"\nArithmetic mean over 110: "<<Media<<"\nWeighted average over 110: "<<MediaP<<endl;
    }
}

void minMedia(int* voti, int* cfu, int index, bool leng){
    int num,opt,i;
    int voti_t[MAX_ESAMI];
    copiaArray(voti,voti_t,index);
    int cfu_t[MAX_ESAMI];
    copiaArray(cfu,cfu_t,index);
    if(leng)
        cout<<"Inserire il numero di esami mancanti\n >> ";
    else
        cout<<"Enter the number of missing exams\n >>"<<endl;
    cin>>num;
    if(leng) {
        cout<<"\nSelezionare una delle seguenti opzioni"<<endl;
        cout<<" 1) Sono "<<num<<" esami da 9 cfu\n2) Sono "<<num<<" esami da 6 cfu\n3) Seleziona cfu manualmente"<<endl;
        cout<<">> ";
    } else {
        cout<<"\nSelect one of the following options"<<endl;
        cout<<"1) There are "<<num<<" exams of 9 credits\n2) There are "<<num<<" exams of 6 credits\n3) Enter the credits manually"<<endl;
        cout<<">> ";
    }
    cin>>opt;
    switch(opt){
        case 1:
            for(i = index; i < index + num; i++){
                voti_t[i] = 18;
                cfu_t[i] = 9;
            }
            break;
        case 2:
            for(i = index; i < index + num; i++){
                voti_t[i] = 18;
                cfu_t[i] = 6;
            }
            break;
        case 3:
            for(i = index; i < index + num; i++){
                voti_t[i] = 18;
                if(leng)
                    cout<<"Inserire cfu\n >> ";
                else
                    cout<<"Insert credits\n >>";
                cin>> cfu_t[i];
            }
            break;
        default:
            if(leng)
                cout<<"Opzione non valida"<<endl;
            else
                cout<<"Invalid option"<<endl;
            break;
    }
    int tot = index + num;
    double media = mediaAritmetica(voti_t,tot);
    double Media = (media * 110) / 30;
    double mediaP = mediaPonderata(voti_t,cfu_t,tot);
    double MediaP = (mediaP * 110) / 30;
    if(leng) {
        cout<<"\nMinimo della media raggiungibile con tutti gli esami"<<endl;
        cout<<"Media Aritmetica: "<<media<<"\nMedia Ponderata: "<<mediaP<<"\nMedia Aritmetica su 110: "<<Media<<"\nMedia Ponderata su 110: "<<MediaP<<endl;
    } else {
        cout<<"\nMinimum of the average achievable with all exams"<<endl;
        cout<<"Arithmetic average: "<<media<<"\nWeighted average: "<<mediaP<<"\nArithmetic mean over 110: "<<Media<<"\nWeighted average over 110: "<<MediaP<<endl;
    }
}
