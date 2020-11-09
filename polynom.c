//
// Created by yarze on 06.11.2020.
//
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include "polynom.h"
#include <string.h>


polynomial* MakePolynom1(int power, El_type elType, void* DATA) {

    polynomial* new_polynom = (polynomial*)malloc(sizeof(polynomial));
    new_polynom->el_type = elType;
    size_t size_type = 0;

    if (new_polynom->el_type == DOUBLE)
    {
        size_type = sizeof(double);
    }
    else {
        if (new_polynom->el_type == COMPLEX) {
            size_type = sizeof(double complex);
        }
    }
    new_polynom->power = power;
    new_polynom->data = calloc(power, sizeof(size_type));
    memcpy(new_polynom->data, DATA, power*sizeof(size_type));


    return new_polynom;
};

polynomial* MakePolynom2(int power, El_type elType) {

    polynomial* new_polynom = (polynomial*)malloc(sizeof(polynomial));
    new_polynom->el_type = elType;
    size_t size_type = 0;

    if (new_polynom->el_type == DOUBLE)
    {
        size_type = sizeof(double);
    }
    else {
        if (new_polynom->el_type == COMPLEX) {
            size_type = sizeof(double complex);
        }


    }
    new_polynom->power = power;
    new_polynom->data = calloc(power, sizeof(size_type));

    return new_polynom;
};


void* GetDATA(polynomial* P){
    return P->data;
}

/////////////////////////////////////////////////////
void DeletePolynom(polynomial* pol){
    free(pol->data);
    pol->data = NULL;
    free(pol);
    pol = NULL;
}

polynomial* max_pol(polynomial* pol1, polynomial* pol2) {
    polynomial* max_pol;
    if (pol1->power <= pol2->power)
        max_pol = pol2;
    else
        max_pol = pol1;
    return max_pol;
}
polynomial* min_pol(polynomial* pol1, polynomial* pol2){
    polynomial* minpol;
    if(pol1->power <= pol2->power){minpol = pol1;}
    else{minpol = pol2;}
    return minpol;
}
int max_power(polynomial* pol1, polynomial* pol2){
    int maxpower;
    if(pol1->power <= pol2->power){maxpower = pol2->power;}
    else{maxpower = pol1->power;}
    return maxpower;
}

int min_power(polynomial* pol1, polynomial* pol2) {
    int minpower;
    if(pol1->power <= pol2->power){minpower = pol1->power;}
    else{minpower = pol2->power;}
    return minpower;
}
polynomial* max_size_type_pol(polynomial* pol1, polynomial* pol2){
    polynomial* maxsize;
    if(sizeof(pol1->el_type) <= sizeof(pol2->el_type)){maxsize = pol2;}
    else{maxsize = pol1;}
    return maxsize;
}
polynomial* Adding(polynomial* pol1, polynomial* pol2){
    polynomial* result;
    if(pol1->el_type == DOUBLE && pol2->el_type == DOUBLE){
        result = MakePolynom2(max_power(pol1,pol2), DOUBLE);
        for(int i = 0; i < min_power(pol1,pol2); i++){
            *((double*)result->data + i) = *((double*)pol1->data + i) + *((double*)pol2->data + i);
        }
        for(int i = min_power(pol1, pol2); i < max_power(pol1,pol2); i++){
            *((double*)result->data + i) += *((double*)max_pol(pol1, pol2)->data + i);
        }

    }
    if(pol1->el_type == COMPLEX && pol2->el_type == DOUBLE){
        result = MakePolynom2(max_power(pol1,pol2), COMPLEX);
        for(int i = 0; i < min_power(pol1,pol2); i++){
            *((double complex*)result->data + i) = creal(*((double complex*)pol1->data + i)) + *((double*)pol2->data + i) + cimag(*(double complex*)pol1->data + i)*I;
        }
        for(int i = min_power(pol1, pol2); i < max_power(pol1,pol2); i++){
            if(max_pol(pol1, pol2) == pol1){*((double complex*)result->data + i) = *((double complex*)max_pol(pol1, pol2)->data + i);}
            else{*((double complex*)result->data + i) = *((double*)max_pol(pol1, pol2)->data + i) + 0 + 0*I;}
        }

    }

    if(pol1->el_type == DOUBLE && pol2->el_type == COMPLEX){
        result = MakePolynom2(max_power(pol1,pol2), COMPLEX);
        for(int i = 0; i < min_power(pol1,pol2); i++){
            *((double complex*)result->data + i) = *((double *)pol1->data + i) + creal(*((double complex*)pol2->data + i)) + cimag(*(double complex*)pol2->data + i)*I;
        }
        for(int i = min_power(pol1, pol2); i < max_power(pol1,pol2); i++){
            if(max_pol(pol1, pol2) == pol1){*((double complex*)result->data + i) = *((double*)max_pol(pol1, pol2)->data + i) + 0 + 0*I;}
            else{*((double complex*)result->data + i) = *((double complex*)max_pol(pol1, pol2)->data + i);}
        }

    }
    if(pol1->el_type == COMPLEX && pol2->el_type == COMPLEX){
        result = MakePolynom2(max_power(pol1,pol2), COMPLEX);
        for(int i = 0; i < min_power(pol1,pol2); i++){
            *((double complex*)result->data + i) = *((double complex*)pol1->data + i) + *((double complex*)pol2->data + i) ;
        }
        for(int i = min_power(pol1, pol2); i < max_power(pol1,pol2); i++){
            *((double complex*)result->data + i) = *((double complex*)max_pol(pol1, pol2)->data + i);

        }

    }
    return result;
}

polynomial* Multiplication(polynomial* pol1, polynomial* pol2){
    polynomial* result;
    if(pol1->el_type == DOUBLE && pol2->el_type == DOUBLE){
        double temp;
        result = MakePolynom2((pol1->power - 1) + (pol2->power - 1) + 1, DOUBLE);
        for(int i = 0; i < pol1->power; i++){
            for(int j = 0; j < pol2->power; j++){
                temp = *((double*)pol1->data + i) * *((double*)pol2->data + j);
                *((double*)result->data + i + j) += temp;
            }
        }

    }
    if(pol1->el_type == DOUBLE && pol2->el_type == COMPLEX){
        double temp;
        result = MakePolynom2((pol1->power - 1) + (pol2->power - 1) + 1, COMPLEX);
        for(int i = 0; i < pol1->power; i++){
            for(int j = 0; j < pol2->power; j++){
                temp = *((double*)pol1->data + i) * creal(*((double complex*)pol2->data + j)) + *((double*)pol1->data + i) * cimag(*((double complex*)pol2->data + j))*I;
                *((double*)result->data + i + j) += temp;
            }
        }

    }
    if(pol2->el_type == DOUBLE && pol1->el_type == COMPLEX){
        double temp;
        result = MakePolynom2((pol1->power - 1) + (pol2->power - 1) + 1, COMPLEX);
        for(int i = 0; i < pol1->power; i++){
            for(int j = 0; j < pol2->power; j++){
                temp = *((double*)pol2->data + j) * creal(*((double complex*)pol1->data + i)) + *((double*)pol2->data + j) * cimag(*((double complex*)pol1->data + i))*I;
                *((double*)result->data + i + j) += temp;
            }
        }

    }
    if(pol1->el_type == COMPLEX && pol2->el_type == COMPLEX){
        double temp;
        result = MakePolynom2((pol1->power - 1) + (pol2->power - 1) + 1, COMPLEX);
        for(int i = 0; i < pol1->power; i++){
            for(int j = 0; j < pol2->power; j++){
                temp = creal(*((double complex*)pol2->data + j)) * creal(*((double complex*)pol1->data + i)) + cimag(*((double complex*)pol2->data + j)) * cimag(*((double complex*)pol1->data + i))*I + creal(*((double complex*)pol2->data + j)) * cimag(*((double complex*)pol1->data + i))*I + cimag(*((double complex*)pol2->data + j)) * creal(*((double complex*)pol1->data + i))*I;
                *((double*)result->data + i + j) += temp;
            }
        }
    }
    return result;
}

void* calculating(polynomial* pol, void* value){
void* result;
if(pol->el_type == DOUBLE) {
    if (sizeof(value) == sizeof(double)) {
        *(double*)result = 0;
        for (int i = 0; i < pol->power; i++) { *(double *)result += *((double*)pol->data + i) * pow(i, *(double*)value);}
        printf("%f", *(double *)result);
    }
    else
        if(sizeof(value) == sizeof(int)){
            *(double*)result = 0;
            for (int i = 0; i < pol->power; i++) { *(double *) result += *((double*)pol->data + i) * pow(i, *(int*)value);}
            printf("%f", *(double *)result);
        }
    else{
            *(double*)result = 0;
            for (int i = 0; i < pol->power; i++) { *(double *) result += *((double*)pol->data + i) * cpow(i, *(double complex*)value);}
            printf("%f", *(double *)result);
    }

}
    if(pol->el_type == COMPLEX) {
        if (sizeof(value) == sizeof(double)) {
            *(double complex*)result = 0;
            for (int i = 0; i < pol->power; i++) { *(double complex*) result += *((double*)pol->data + i) * pow(i, *(double*)value);}
            printf("%.2f %+.2fi\\n", creal(*(double complex*)result), cimag(*(double complex*)result));
        }
        else
        if(sizeof(value) == sizeof(int)){
            *(double complex*)result = 0;
            for (int i = 0; i < pol->power; i++) { *(double complex*) result += *((double*)pol->data + i) * pow(i, *(int*)value);}
            printf("%.2f %+.2fi\\n", creal(*(double complex*)result), cimag(*(double complex*)result));
        }
        else{
            *(double complex*)result = 0;
            for (int i = 0; i < pol->power; i++) { *(double complex*) result += *((double*)pol->data + i) * cpow(i, *(double complex*)value);}
            printf("%.2f %+.2fi\\n", creal(*(double complex*)result), cimag(*(double complex*)result));
        }

    }

}
