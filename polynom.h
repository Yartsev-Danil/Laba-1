//
// Created by yarze on 05.11.2020.
//

#ifndef LAB1_POLYNOM_H
#define LAB1_POLYNOM_H

#include <stdio.h>
#include <complex.h>
#include <stdlib.h>

typedef enum {DOUBLE, COMPLEX} El_type;
typedef struct polynomial {
    El_type el_type;
    void *data;
    int power;
} polynomial;



polynomial* MakePolynom(int, El_type, void*);



void DeletePolynom(polynomial*);


#endif //LAB1_POLYNOM_H
