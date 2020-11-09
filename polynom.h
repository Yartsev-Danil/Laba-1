//
// Created by yarze on 06.11.2020.
//

#ifndef UNTITLED6_POLYNOM_H
#define UNTITLED6_POLYNOM_H
#include <stdio.h>
#include <complex.h>
#include <stdlib.h>

typedef enum
{
    DOUBLE,
    COMPLEX
} El_type;

typedef struct {
    El_type el_type;
    void* data;
    int power;
} polynomial;



polynomial* MakePolynom(int, El_type, void*);
/////////////////////////////////////////////////
void DeletePolynom(polynomial*);
///////////////////////////////////
void* GetData(polynomial const *);
int* GetDataI(polynomial const *);
complex* GetDataC(polynomial const *);
//////////////////////////////////////////////
polynomial* max_pol(polynomial*, polynomial*);
polynomial* min_pol(polynomial*, polynomial*);
int max_power(polynomial*, polynomial*);
int min_power(polynomial*, polynomial*);
//////////////////////////////////////////////
polynomial* Adding(polynomial*, polynomial*);
polynomial* Multiplication(polynomial*, polynomial*);
void* calculating(polynomial*, void*);
#endif //UNTITLED6_POLYNOM_H
