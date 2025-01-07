#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const int num_attrezzi=5;

typedef struct{
    int numRecord;
    char NomeAttrezzo[30];
    int quantita;
    float prezzo;
}Attrezzo;

void aggiungiAttrezzo(Attrezzo a);


void aggiornamento(char nome[30]); 

FILE *fileptr;
FILE *filetemp;
int main(void){
  Attrezzo a;
  int scelta=0;
  
  while (scelta!=9){
    printf("\nBenvenuto nell'inventario del ferramenta!\nFai la tua scelta:\n1 - Riempi inventario\n2 - Modifica attrezzo inventario(tra quelli esistenti)\n9-->Esci\nInserisci: ");
  
    scanf("%d",&scelta);
  { 
    switch (scelta)
    {
    case 1:
        aggiungiAttrezzo(a);
      break;
    
      case 2:
          printf("Inserisci il nome dell'attrezzo da cercare:");
            char nomeSearch[30];
            scanf("%s",nomeSearch);
            aggiornamento(nomeSearch);
      break;

      case 9: 
      printf("Arrivederci!");
      exit(0);
      
    default :
      printf("Digitazione errata!Fai la tua scelta:\n1 - Riempi inventario\n2 - Modifica attrezzo inventario(tra quelli esistenti)\nEOF(CTRL+Z)-->Esci\nInserisci:");
      break;
    }
  
   }
  }
}




void aggiungiAttrezzo(Attrezzo a){

 
 fileptr=fopen("hardware.dat","w+"); // puntatore al file hardware.dat
 
 if(fileptr==NULL){

    printf("\nImpossibile aprire il file\n");
    exit(1);
   }
 fprintf(fileptr,"Record #\tNome Attrezzo\tQuantita\t  Prezzo\n");
    // for per scrivere 100 attrezzi sul file
 for (int i = 1; i < num_attrezzi+1; i++)
   {  printf("Inserire i dati nel seguente formato\n(nomeAttrezzo quantita' prezzo(es: chiodo 5 0.15))\nInserisci:");
      scanf("%s %d %f",a.NomeAttrezzo,&a.quantita,&a.prezzo);
      a.numRecord=i;
     fprintf(fileptr,"%5d\t%15s\t   %5d\t\t   %5.2f\n",a.numRecord,a.NomeAttrezzo,a.quantita,a.prezzo);
     
   }
  fflush(fileptr);
  fclose(fileptr);


}


void aggiornamento(char nome[30]){
 
  bool prod_manacante=false;
   int nonTrovato=0;

    fileptr=fopen("hardware.dat","r");
    if(fileptr==NULL){ 
    printf("\nImpossibile aprire il file\n");
     exit(1);
    }
      Attrezzo a;
  
    filetemp=fopen("temp.dat","w"); // puntatore al file hardware.dat
 
    if(filetemp==NULL){

    printf("\nImpossibile aprire il file\n");
    exit(1);
   }

   //prima riga del file temp
    fprintf(filetemp,"Record #\tNome Attrezzo\tQuantita\t  Prezzo\n");

   // sposto di 40 byte per saltare la prima riga
    fseek(fileptr,40, SEEK_SET);

     int i=1; // contatore per i record

      while(fscanf(fileptr, "%d %s %d %f", &a.numRecord, a.NomeAttrezzo, &a.quantita, &a.prezzo) == 4){

          prod_manacante=false;
          
      
      
    
      //se il nome dell'attrezzo letto è uguale
      if(strcmp(nome,a.NomeAttrezzo)==0){
        //scrivo su terminale
        printf("\nAttrezzo trovato!\n");
        
        printf("\nModificare quantita' o prezzo?\n1-quantita'\n2-prezzo\nScegli: ");
        int scelta=0;
        scanf("%d",&scelta);
        if (scelta==1)
        {
          printf("\nInserisci valore di magazzino aggiornato(maggiore o uguale a zero): ");
          int mod_quant;
          scanf("%d",&mod_quant);
            while(mod_quant<0){
                printf("\nInserisci valore di magazzino aggiornato(maggiore o uguale a zero):  ");
                scanf("%d",&mod_quant);
            }  
          printf("\n");
          a.quantita=mod_quant;

          if(a.quantita==0){
            prod_manacante=true;
          }
        }else{
          float mod_prezzo;
             printf("\nInserisci il prezzo del prodotto(maggiore o uguale a zero): ");
          scanf("%f",&mod_prezzo);
            while(mod_prezzo<0){
                printf("\nInserisci valore di magazzino aggiornato(maggiore o uguale a zero):  ");
                scanf("%f",&mod_prezzo);
            }  
          printf("\n");
          a.prezzo=mod_prezzo;

        }        
        
 

          //scrittura del record sul file
          if (prod_manacante!=true) // se il prodotto ha la quantità uguale a zero è mancante
          {
            fprintf(filetemp,"%2d\t%15s\t   %5d\t\t   %.2f\n",i,a.NomeAttrezzo,a.quantita,a.prezzo);
          
          }
        
        
         } else {
            nonTrovato++;
            // scrivo gli oggetti non modificati sul file temporaneo
            fprintf(filetemp,"%2d\t%15s\t   %5d\t\t   %.2f\n",i,a.NomeAttrezzo,a.quantita,a.prezzo);
        }
       
      i++;
    }


  if((nonTrovato-1)==num_attrezzi){
    fclose(fileptr);
    fclose(filetemp);
    printf("\nAttrezzo non trovato!!!\n");
  
  }else{
     fclose(fileptr);
  fclose(filetemp);
  printf("\nAggiornamento completato. I dati modificati sono stati salvati in 'temp.dat'.\n");

  // Sostituisci il file originale con il file aggiornato
  remove("backup.dat");
  if (rename("hardware.dat","backup.dat") != 0 || rename("temp.dat", "hardware.dat") != 0) {
      printf("Errore nella sostituzione del file.\n");
      exit(1);
  } else {
      printf("\nAggiornamento completato con successo.\n");
  }
  }
}
