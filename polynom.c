//
// Created by yarze on 05.11.2020.
//
#include <stdio.h>
#include <complex.h>
#include <stdlib.h>
#include "polynom.h"
#include <string.h>

polynomial* MakePolynom(int power, El_type elType, void* DATA){

    polynomial* new_polynom = (polynomial*)malloc(sizeof(polynomial));
    new_polynom -> el_type = elType;
    size_t size_type = 0;

    if(new_polynom -> el_type == DOUBLE)
    {
        size_type = sizeof(double);
    }
    else {
        if (new_polynom->el_type == COMPLEX) {
            size_type = sizeof(complex);
        }
    }
    new_polynom->power = power;
    new_polynom -> data = (double*)calloc(power, sizeof(size_type));
    memcpy(new_polynom->data, DATA, power * sizeof(size_type));


    return new_polynom;
};
void FreeData(void* ptr) {
    if (ptr) {
        free(ptr);
        ptr = NULL;
    }
}
void DeletePolynom(polynomial* P){
    FreeData(P->data);
    FreeData(P);
    P = NULL;
}

void* GetDATA(polynomial* polynom){
    return polynom -> data;
};