<<<<<<< HEAD
#include "milieu_ligne.h"
#include "constantes.h"

#define max(i, j) (i > j ? i : j)

void moyenne_glissante(int8_t* valeurs)
{
    uint8_t i;
    int8_t previous = *valeurs;
    int8_t temp;

    *valeurs = (previous*2 + *(valeurs + 1))/3;

	for(i = 1; i < 125; i++)
    {
        temp = *(valeurs + i);
        *(valeurs + i) = (temp + previous + *(valeurs + i + 1)) / 3;
        previous = temp;
    }

    *(valeurs + 125) = ((*(valeurs + 125))*2 + previous)/3;
}
    

void milieu_ligne(uint8_t* milieu, uint16_t* incertitude)
{
    int8_t valeurs[126];
	uint8_t pos_max = 0;
	uint8_t pos_min = 0;
	uint8_t max_hors_ligne = 0;
	uint8_t i;

	// calcul de la d�riv�e
    for(i = 0; i < 126; i++)
   	{
        valeurs[i] = (int8_t)camera_valeurs[i + 2] - (int8_t)camera_valeurs[i];
    }
	
	// recherche du min / du max
	for(i = 1; i < 126; i++)
	{
		if(valeurs[i] > valeurs[pos_max])
			pos_max = i;
		if(valeurs[i] < valeurs[pos_min])
			pos_min = i;
		TransmitCharacter(valeurs[i] + 0x40);
	}
	TransmitCharacter(0);
	// recherche du plus gros pic en dehors de la ligne (incertitude)
	for(i = 0; i < 126; i++)
	{
		if(abs((int8_t)pos_max - (int8_t)i) > LARGEUR_LIGNE && abs(valeurs[i]) > max_hors_ligne)
			max_hors_ligne = abs(valeurs[i]);
	}

	/*printhex8(pos_min);
	TransmitCharacter('\n');
	printhex8(pos_max);
	TransmitCharacter('\n');
	printhex8(*(valeurs + pos_max));
	TransmitCharacter('\n');
	TransmitCharacter('\n');*/
	
	*milieu = (pos_min + pos_max) / 2;
	
	*incertitude =
		abs((int8_t)pos_min - (int8_t)pos_max - LARGEUR_LIGNE) < DELTA_LARGEUR_LIGNE
		? max(valeurs[pos_max], valeurs[pos_min]) * 10 / max_hors_ligne
		: 127;
	*incertitude = 0;
}

/*
void milieu_ligne(uint8_t* milieu, uint16_t* incertitude)
{
    int8_t valeurs[128];
	uint8_t pos_max = 0;
	uint8_t i;
    int8_t moyenne;
    int16_t somme = 0;

    // copie des valeurs pour la caméra (elles sont modifiées dans la moyenne glissante)
    // + moyenne
    for(i = 0; i < 128; i++)
    {
        *(valeurs + i) = *(camera_valeurs + i);
        somme += *(valeurs + i);
    }
    moyenne = somme / 128;
	
	for(i = 0; i < 4; i++)
		moyenne_glissante(valeurs);
	
	for(i = 0; i < 128; i++)
		if(*(valeurs + i) > *(valeurs + pos_max))
			pos_max = i;
	
	*milieu = pos_max;

    moyenne = (moyenne + *(valeurs + pos_max)) / 2;

    *incertitude = 0;
    for(i = 0; i < 128; i++)
        if(*(valeurs + i) > moyenne)
            *incertitude += (i > pos_max) ? i - pos_max : pos_max - i;

}
*/
=======
#include "milieu_ligne.h"
#include "constantes.h"

#define max(i, j) (i > j ? i : j)

void moyenne_glissante(int8_t* valeurs)
{
    uint8_t i;
    int8_t previous = *valeurs;
    int8_t temp;

    *valeurs = (previous*2 + *(valeurs + 1))/3;

	for(i = 1; i < 125; i++)
    {
        temp = *(valeurs + i);
        *(valeurs + i) = (temp + previous + *(valeurs + i + 1)) / 3;
        previous = temp;
    }

    *(valeurs + 125) = ((*(valeurs + 125))*2 + previous)/3;
}
    

void milieu_ligne(uint8_t* milieu, uint16_t* incertitude)
{
    int8_t valeurs[126];
	uint8_t pos_max = 0;
	uint8_t pos_min = 0;
	uint8_t max_hors_ligne = 0;
	uint8_t i;

	// calcul de la d�riv�e
    for(i = 0; i < 126; i++)
   	{
        valeurs[i] = (int8_t)camera_valeurs[i + 2] - (int8_t)camera_valeurs[i];
    }
	
	// recherche du min / du max
	for(i = 1; i < 126; i++)
	{
		if(valeurs[i] > valeurs[pos_max])
			pos_max = i;
		if(valeurs[i] < valeurs[pos_min])
			pos_min = i;
		TransmitCharacter(valeurs[i] + 0x80);
	}
	TransmitCharacter(0);
	// recherche du plus gros pic en dehors de la ligne (incertitude)
	for(i = 0; i < 126; i++)
	{
		if(abs((int8_t)pos_max - (int8_t)i) > LARGEUR_LIGNE && abs(valeurs[i]) > max_hors_ligne)
			max_hors_ligne = abs(valeurs[i]);
	}

	/*printhex8(pos_min);
	TransmitCharacter('\n');
	printhex8(pos_max);
	TransmitCharacter('\n');
	printhex8(*(valeurs + pos_max));
	TransmitCharacter('\n');
	TransmitCharacter('\n');*/
	
	*milieu = (pos_min + pos_max) / 2;
	
	*incertitude =
		abs((int8_t)pos_min - (int8_t)pos_max - LARGEUR_LIGNE) < DELTA_LARGEUR_LIGNE
		?  max_hors_ligne * 10 / max(valeurs[pos_max], -valeurs[pos_min])
		: 127;
	*incertitude = 0;
}

/*
void milieu_ligne(uint8_t* milieu, uint16_t* incertitude)
{
    int8_t valeurs[128];
	uint8_t pos_max = 0;
	uint8_t i;
    int8_t moyenne;
    int16_t somme = 0;

    // copie des valeurs pour la caméra (elles sont modifiées dans la moyenne glissante)
    // + moyenne
    for(i = 0; i < 128; i++)
    {
        *(valeurs + i) = *(camera_valeurs + i);
        somme += *(valeurs + i);
    }
    moyenne = somme / 128;
	
	for(i = 0; i < 4; i++)
		moyenne_glissante(valeurs);
	
	for(i = 0; i < 128; i++)
		if(*(valeurs + i) > *(valeurs + pos_max))
			pos_max = i;
	
	*milieu = pos_max;

    moyenne = (moyenne + *(valeurs + pos_max)) / 2;

    *incertitude = 0;
    for(i = 0; i < 128; i++)
        if(*(valeurs + i) > moyenne)
            *incertitude += (i > pos_max) ? i - pos_max : pos_max - i;

}
*/
>>>>>>> 8cc3d4b7c04b365f75ff9ec34344faf004f2dc92