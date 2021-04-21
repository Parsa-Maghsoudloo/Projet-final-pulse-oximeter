/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

//Arnaud c'tune criss de pute

/* [] END OF FILE */
#include "filtre.h"
#include <math.h>
#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
//#include "uart_debug.h"
#include "variables.h"
#include "semphr.h"
#include "affichage.h"
#include <arm_math.h>
#include <core_cm4.h>
#if defined(SEMIHOSTING)
#include <stdio.h>
#endif


#define TAP_NUM_BRUIT 31
#define TAP_NUM_DC 301
#define BLOCK_SIZE 1000

//Coefficient pour les filtres
const float32_t FIR6[TAP_NUM_BRUIT] = {-0.0009970438f, -0.0017273239f, -0.0028783043f, -0.0043699962f, -0.0056686200f, -0.0057953168f, -0.0034965051f, 0.0024511213f, 0.0128724880f, 0.0278614783f, 0.0465826136f, 0.0672779019f, 0.0874996570f, 0.1045311746f, 0.1159054686f, 0.1199024133f, 0.1159054686f, 0.1045311746f, 0.0874996570f, 0.0672779019f, 0.0465826136f, 0.0278614783f, 0.0128724880f, 0.0024511213f, -0.0034965051f, -0.0057953168f, -0.0056686200f, -0.0043699962f, -0.0028783043f, -0.0017273239f, -0.0009970438f};
const float32_t FIR1_HIGH[TAP_NUM_DC]= {-0.0000000000f, -0.0000107447f, -0.0000216734f, -0.0000328282f, -0.0000442501f, -0.0000559785f, -0.0000680500f, -0.0000804974f, -0.0000933487f, -0.0001066264f, -0.0001203462f, -0.0001345161f, -0.0001491359f, -0.0001641960f, -0.0001796769f, -0.0001955487f, -0.0002117698f, -0.0002282874f, -0.0002450361f, -0.0002619386f, -0.0002789045f, -0.0002958312f, -0.0003126031f, -0.0003290925f, -0.0003451592f, -0.0003606516f, -0.0003754068f, -0.0003892512f, -0.0004020020f, -0.0004134674f, -0.0004234478f, -0.0004317374f, -0.0004381252f, -0.0004423964f, -0.0004443339f, -0.0004437201f, -0.0004403385f, -0.0004339755f, -0.0004244221f, -0.0004114763f, -0.0003949443f, -0.0003746433f, -0.0003504030f, -0.0003220677f, -0.0002894985f, -0.0002525754f, -0.0002111988f, -0.0001652919f, -0.0001148024f, -0.0000597045f, 0.0000000000f, 0.0000642792f, 0.0001330704f, 0.0002062781f, 0.0002837735f, 0.0003653925f, 0.0004509358f, 0.0005401673f, 0.0006328143f, 0.0007285666f, 0.0008270766f, 0.0009279595f, 0.0010307934f, 0.0011351199f, 0.0012404446f, 0.0013462388f, 0.0014519397f, 0.0015569525f, 0.0016606521f, 0.0017623845f, 0.0018614694f, 0.0019572021f, 0.0020488563f, 0.0021356869f, 0.0022169325f, 0.0022918190f, 0.0023595624f, 0.0024193727f, 0.0024704568f, 0.0025120229f, 0.0025432836f, 0.0025634603f, 0.0025717867f, 0.0025675131f, 0.0025499103f, 0.0025182735f, 0.0024719264f, 0.0024102252f, 0.0023325627f, 0.0022383715f, 0.0021271286f, 0.0019983584f, 0.0018516365f, 0.0016865930f, 0.0015029154f, 0.0013003521f, 0.0010787144f, 0.0008378798f, 0.0005777935f, 0.0002984712f, 0.0000000000f, -0.0003174597f, -0.0006536732f, -0.0010083307f, -0.0013810469f, -0.0017713608f, -0.0021787359f, -0.0026025608f, -0.0030421502f, -0.0034967458f, -0.0039655183f, -0.0044475690f, -0.0049419323f, -0.0054475781f, -0.0059634150f, -0.0064882932f, -0.0070210083f, -0.0075603049f, -0.0081048810f, -0.0086533920f, -0.0092044556f, -0.0097566564f, -0.0103085512f, -0.0108586737f, -0.0114055404f, -0.0119476557f, -0.0124835177f, -0.0130116238f, -0.0135304765f, -0.0140385889f, -0.0145344909f, -0.0150167346f, -0.0154839001f, -0.0159346012f, -0.0163674910f, -0.0167812668f, -0.0171746760f, -0.0175465209f, -0.0178956632f, -0.0182210293f, -0.0185216142f, -0.0187964859f, -0.0190447889f, -0.0192657481f, -0.0194586718f, -0.0196229546f, -0.0197580800f, -0.0198636223f, -0.0199392486f, -0.0199847202f, 0.9799947751f, -0.0199847202f, -0.0199392486f, -0.0198636223f, -0.0197580800f, -0.0196229546f, -0.0194586718f, -0.0192657481f, -0.0190447889f, -0.0187964859f, -0.0185216142f, -0.0182210293f, -0.0178956632f, -0.0175465209f, -0.0171746760f, -0.0167812668f, -0.0163674910f, -0.0159346012f, -0.0154839001f, -0.0150167346f, -0.0145344909f, -0.0140385889f, -0.0135304765f, -0.0130116238f, -0.0124835177f, -0.0119476557f, -0.0114055404f, -0.0108586737f, -0.0103085512f, -0.0097566564f, -0.0092044556f, -0.0086533920f, -0.0081048810f, -0.0075603049f, -0.0070210083f, -0.0064882932f, -0.0059634150f, -0.0054475781f, -0.0049419323f, -0.0044475690f, -0.0039655183f, -0.0034967458f, -0.0030421502f, -0.0026025608f, -0.0021787359f, -0.0017713608f, -0.0013810469f, -0.0010083307f, -0.0006536732f, -0.0003174597f, 0.0000000000f, 0.0002984712f, 0.0005777935f, 0.0008378798f, 0.0010787144f, 0.0013003521f, 0.0015029154f, 0.0016865930f, 0.0018516365f, 0.0019983584f, 0.0021271286f, 0.0022383715f, 0.0023325627f, 0.0024102252f, 0.0024719264f, 0.0025182735f, 0.0025499103f, 0.0025675131f, 0.0025717867f, 0.0025634603f, 0.0025432836f, 0.0025120229f, 0.0024704568f, 0.0024193727f, 0.0023595624f, 0.0022918190f, 0.0022169325f, 0.0021356869f, 0.0020488563f, 0.0019572021f, 0.0018614694f, 0.0017623845f, 0.0016606521f, 0.0015569525f, 0.0014519397f, 0.0013462388f, 0.0012404446f, 0.0011351199f, 0.0010307934f, 0.0009279595f, 0.0008270766f, 0.0007285666f, 0.0006328143f, 0.0005401673f, 0.0004509358f, 0.0003653925f, 0.0002837735f, 0.0002062781f, 0.0001330704f, 0.0000642792f, 0.0000000000f, -0.0000597045f, -0.0001148024f, -0.0001652919f, -0.0002111988f, -0.0002525754f, -0.0002894985f, -0.0003220677f, -0.0003504030f, -0.0003746433f, -0.0003949443f, -0.0004114763f, -0.0004244221f, -0.0004339755f, -0.0004403385f, -0.0004437201f, -0.0004443339f, -0.0004423964f, -0.0004381252f, -0.0004317374f, -0.0004234478f, -0.0004134674f, -0.0004020020f, -0.0003892512f, -0.0003754068f, -0.0003606516f, -0.0003451592f, -0.0003290925f, -0.0003126031f, -0.0002958312f, -0.0002789045f, -0.0002619386f, -0.0002450361f, -0.0002282874f, -0.0002117698f, -0.0001955487f, -0.0001796769f, -0.0001641960f, -0.0001491359f, -0.0001345161f, -0.0001203462f, -0.0001066264f, -0.0000933487f, -0.0000804974f, -0.0000680500f, -0.0000559785f, -0.0000442501f, -0.0000328282f, -0.0000216734f, -0.0000107447f, -0.0000000000f};
const float32_t FIR1_LOW[TAP_NUM_BRUIT] = {0.0043217344f, 0.0049641814f, 0.0067268530f, 0.0095907107f, 0.0134771944f, 0.0182508075f, 0.0237249534f, 0.0296707485f, 0.0358283571f, 0.0419202374f, 0.0476655699f, 0.0527950605f, 0.0570652803f, 0.0602717271f, 0.0622598570f, 0.0629334548f, 0.0622598570f, 0.0602717271f, 0.0570652803f, 0.0527950605f, 0.0476655699f, 0.0419202374f, 0.0358283571f, 0.0296707485f, 0.0237249534f, 0.0182508075f, 0.0134771944f, 0.0095907107f, 0.0067268530f, 0.0049641814f, 0.0043217344f};

//Buffer pour les filtres locaux
const uint32_t blockSize = BLOCK_SIZE;
static float32_t buff_filtered_IR_DC[BLOCK_SIZE];
static float32_t buff_filtered_RED_DC[BLOCK_SIZE];
static float32_t firStateHigh[BLOCK_SIZE + TAP_NUM_DC - 1];

//Variable commune aux fonctions
volatile float R = 0;


/*
Fonction secondaire
 Calcul le SpO2
 Valeurs d'entrées :
	- AC des valeurs rouges (A_RED)
	- DC des valeurs rouges (D_RED)
	- AC des valeurs infrarouges (A_IR)
	- DC des valeurs infrarouges (D_IR)

 Valeurs modifiées:
	- Coefficient R (R)
	- % d'oxygénation du sang (SpO2)

 Valeurs de sortie:
	-void 
*/
void calcul_SpO2(float A_RED, float D_RED,float A_IR,float D_IR)
{
    R = A_RED/D_RED/(A_IR/D_IR);
    const float coeff_a = -0.24614699;
    const float coeff_b = 0.09460578;
    const float coeff_c = 1.00154192;

    SpO2 = 100*(coeff_a*pow(R, 2) + coeff_b* R + coeff_c);
}

/* Fonction principale
 Filtre le signal et acquiert les valeurs requises au calcul du BPM et SpO2
 Valeurs d'entrées :
	-Addresse non utilisée afin d'utiliser comme tâche (*arg)

 Valeurs modifiées:
	- Coefficient R (R)....voir fonction calcul_SpO2
	- % d'oxygénation du sang (SpO2)....voir fonction calcul_SpO2
	- Le nombre de battements par minutes (BPM)

 Valeurs de sortie:
	-void
*/
void Traitement(void* arg)
{
 (void) arg;
 for(;;){
  if(xSemaphoreTake(semaph, pdMS_TO_TICKS(11000)) == true){
 
// Déclaration des variables pour le filtrage du signal
  arm_fir_instance_f32 S_IR, S_RED, S_IR_DC, S_RED_DC;
  arm_status status;
  float32_t  *input_IR, *output_signal_IR, *input_RED, *output_signal_RED, *output_IR_DC, *output_RED_DC;
  
  
  
// Initialise les entrées et sortie du buffer pointeur 
  input_IR = &vecteur_IR[read - 500];
  output_signal_IR = &buff_filtered_IR[0];
  output_IR_DC = &buff_filtered_IR_DC[0];
  input_RED = &vecteur_RED[read - 500];
  output_signal_RED = &buff_filtered_RED[0];
  output_RED_DC = &buff_filtered_RED_DC[0];


//Filatrage passe haut de 1 Hz pour enlever la composante DC
  arm_fir_init_f32(&S_IR, TAP_NUM_DC, (float32_t *)&FIR1_HIGH[0], &firStateHigh[0], blockSize);
  arm_fir_f32(&S_IR, input_IR, output_signal_IR, blockSize);
  arm_fir_init_f32(&S_RED, TAP_NUM_DC, (float32_t *)&FIR1_HIGH[0], &firStateHigh[0], blockSize);
  arm_fir_f32(&S_RED, input_RED, output_signal_RED, blockSize);

//Filatrage passe bas de 6 Hz pour enlever le bruit
  arm_fir_init_f32(&S_IR, TAP_NUM_BRUIT, (float32_t *)&FIR6[0], &firStateHigh[0], blockSize);
  arm_fir_f32(&S_IR, output_signal_IR, output_signal_IR, blockSize);
  arm_fir_init_f32(&S_RED, TAP_NUM_BRUIT, (float32_t *)&FIR6[0], &firStateHigh[0], blockSize);
  arm_fir_f32(&S_RED, output_signal_RED, output_signal_RED, blockSize);


//Filatrage passe bas de 1 Hz pour avoir seulement la composante DC
  input_IR = &vecteur_IR[0];
  input_RED = &vecteur_RED[0];
  arm_fir_init_f32(&S_IR_DC, TAP_NUM_BRUIT, (float32_t *)&FIR1_LOW[0], &firStateHigh[0], blockSize);
  arm_fir_f32(&S_IR_DC, input_IR, output_IR_DC, blockSize);
  arm_fir_init_f32(&S_RED_DC, TAP_NUM_BRUIT, (float32_t *)&FIR1_LOW[0], &firStateHigh[0], blockSize);
  arm_fir_f32(&S_RED_DC, input_RED, output_RED_DC, blockSize);


//Initialisation des variables globales utiles pour le calcul du BPM et SpO2
  maxIR = -100000;
  minIR = 100000;
  maxRED = -100000;
  minRED = 100000;

//BPM et SpO2
  volatile int nb_peak_max = 0;
  int nb_peak_min = 0;
  volatile float AC_IR = 0;
  volatile float DC_IR = 0;
  volatile float AC_RED = 0;
  volatile float DC_RED = 0;
  float moyenne_max_IR = 0;
  float moyenne_min_IR = 0;
  float moyenne_max_RED = 0;
  float moyenne_min_RED = 0;
  bool keep_min_IR = false;
  bool keep_min_RED = false;
  float32_t pos_first_max = 0;
  float32_t pos_last_max = 0;

//Détection des minimums et maximums et prises des valeurs pour la variables ci-haut
  for(int i =400; i<BLOCK_SIZE-10; i++){
    bool v1 = buff_filtered_IR[i] > buff_filtered_IR[i-1];
    bool v2 = buff_filtered_IR[i] > buff_filtered_IR[i-2];
    bool v3 = buff_filtered_IR[i] > buff_filtered_IR[i-3];
    bool v4 = buff_filtered_IR[i] > buff_filtered_IR[i-4];
    bool v5 = buff_filtered_IR[i] > buff_filtered_IR[i-5];
    bool v6 = buff_filtered_IR[i] > buff_filtered_IR[i+1];
    bool v7 = buff_filtered_IR[i] > buff_filtered_IR[i+2];
    bool v8 = buff_filtered_IR[i] > buff_filtered_IR[i+3];
    bool v9 = buff_filtered_IR[i] > buff_filtered_IR[i+4];
    bool v10 = buff_filtered_IR[i] > buff_filtered_IR[i+5];
    bool r1 = buff_filtered_RED[i] > buff_filtered_RED[i-1];
    bool r2 = buff_filtered_RED[i] > buff_filtered_RED[i-2];
    bool r3 = buff_filtered_RED[i] > buff_filtered_RED[i-3];
    bool r4 = buff_filtered_RED[i] > buff_filtered_RED[i-4];
    bool r5 = buff_filtered_RED[i] > buff_filtered_RED[i-5];
    bool r6 = buff_filtered_RED[i] > buff_filtered_RED[i+1];
    bool r7 = buff_filtered_RED[i] > buff_filtered_RED[i+2];
    bool r8 = buff_filtered_RED[i] > buff_filtered_RED[i+3];
    bool r9 = buff_filtered_RED[i] > buff_filtered_RED[i+4];
    bool r10 = buff_filtered_RED[i] > buff_filtered_RED[i+5];
    bool keep_max_IR = buff_filtered_IR[i+10] < buff_filtered_IR[i - 10];
    bool keep_max_RED = buff_filtered_RED[i+10] < buff_filtered_RED[i - 10];
    DC_IR += buff_filtered_IR[i]/(BLOCK_SIZE - 410);
    DC_RED += buff_filtered_RED[i]/(BLOCK_SIZE - 410);
    
    if(v1 & v2 & v3 & v4 & v5 & v6 & v7 & v8 & v9 & v10 & keep_max_IR){
        nb_peak_max += 1;
        moyenne_max_IR += buff_filtered_IR[i];
        keep_min_IR = true;
        if(i >= 800){
            if(buff_filtered_IR[i] > maxIR){maxIR = buff_filtered_IR[i];}
        }
        if(nb_peak_max == 1){pos_first_max = i;}
        pos_last_max = i;
    }
    
    else if (!v1 & !v2 & !v3 & !v4 & !v5& !v6 & !v7 & !v8 & !v9 & !v10 & keep_min_IR){
        nb_peak_min += 1;
        moyenne_min_IR += buff_filtered_IR[i];
        keep_min_IR = false;
        if(i >= 800){
            if(buff_filtered_IR[i] < minIR){minIR = buff_filtered_IR[i];}
        }
    }   
    
    if(r1 & r2 & r3 & r4 & r5 & r6 & r7 & r8 & r9 & r10 & keep_max_RED){
        moyenne_max_RED += buff_filtered_RED[i];
        keep_min_RED = true;
        if(i >= 800){
            if(buff_filtered_RED[i] > maxRED){maxRED = buff_filtered_RED[i];}
        }
    }

    else if (!r1 & !r2 & !r3 & !r4 & !r5& !r6 & !r7 & !r8 & !r9 & !r10 & keep_min_RED){
        moyenne_min_RED += buff_filtered_RED[i];
        if(i >= 800){
            if(buff_filtered_RED[i] < minRED){minRED = buff_filtered_RED[i];}
        }
        keep_min_RED  = false;
    }   
}

// Calcul du BPM et du SpO2  
  moyenne_max_IR = moyenne_max_IR/nb_peak_max;
  moyenne_min_IR = moyenne_min_IR/nb_peak_min;
  moyenne_max_RED = moyenne_max_RED/nb_peak_max;
  moyenne_min_RED = moyenne_min_RED/nb_peak_min;
  BPM = ((float32_t)(nb_peak_max-1))*(6000/(pos_last_max-pos_first_max));
  AC_IR = moyenne_max_IR - moyenne_min_IR;
  AC_RED = moyenne_max_RED - moyenne_min_RED;
  calcul_SpO2(AC_RED, DC_RED, AC_IR, DC_IR);

for(int i = 800; i<1000; i++){
    buff_filtered_RED_copy[i-800] = buff_filtered_RED[i];
    buff_filtered_IR_copy[i-800] = buff_filtered_IR[i];
}

  xSemaphoreGive(graph_semph);
  }
 }
}