#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define and &&
#define or  ||
#define i16 int16_t
#define i32 int32_t
#define i64 int64_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t

double relacaoJurosMensaleAnual(double A, double J)
{
    return -pow(1+J/100, 12) + 1 + A/100;
}

double fJ(double x)
{
    double starting = -1559.15;
    
    for( i16 i = 0; i < 12; i++ )
    {
        starting += 141.08/pow(1 + x/100, i);
    }

    return starting;
}

double findRoot(double left, double right, double (*f)(double))
{
    double m = (right+left)/2;

    if ( fabs((*f)(left)) < 10e-14 )
        return left;
    else if ( fabs((*f)(right)) < 10e-14 )
        return right;

    double oleft  = left;
    double oright = right;

    i32 i = 0;

    while( (fabs((*f)( m )) > 10e-13) and i < 0x7fffffff )
    {
        if( (*f)( left ) * (*f)( m ) > 0 )
        {
            left = m;
        }
        else
        {
            right = m;
        }

        m = ( right + left )/ 2;
        if( i == 0x7ffffffd or i == 0x7ffffffe )
            printf("O m está travado em : %.16e\n", m);
        i += 1;
    }

    if(m == oleft || m == oright)
        printf("Apparently the range was not properly set.");


    return m;
}

double findJ(double left, double right, double A, double (*f)(double, double))
{
    double m = (right+left)/2;

    while( fabs( (*f)(A, m) ) > 10e-14)
    {
        if( (*f)(A, left) * (*f)(A, m) > 0 )
        {
            left = m;
        }
        else
        {
            right = m;
        }

        m = ( right + left )/ 2;
    }

    return m;
}

double findA(double left, double right, double J, double (*f)(double, double))
{
    double m = (right+left)/2;

    while( fabs( (*f)(m, J) ) > 10e-14 )
    {
        if( (*f)(left, J) * (*f)(m, J) > 0 )
        {
            left = m;
        }
        else
        {
            right = m;
        }

        m = ( right + left )/ 2;
    }

    return m;
}

void problema1()
{
    u16 size = 12;
    double aVista = 1559.15;
    double* aPrazo;

    aPrazo = (double*) malloc(sizeof(double) * size);

    for( u16 i = 0; i < size; i++ )
    {
        aPrazo[i] = 141.08;
    }

    double totalAPrazo = 141.08 * 12;
    double diferencaJuros = totalAPrazo - aVista;

    printf("O custo total a prazo é: %lf\n", totalAPrazo);
    printf("O diferenca a prazo é: %lf\n", diferencaJuros);

    //1+(A/100)
    double aumentoAnual = totalAPrazo/aVista;
    printf("O aumento anual é: %.4lf\n", aumentoAnual);
    double A = (aumentoAnual - 1)*100;
    printf("Portanto A = %.16e\n", A);


    double J = findRoot(0, 100, fJ);
    printf("J with future value = %.16e\n", J);

    double A2 = findA(0, 100, J, relacaoJurosMensaleAnual);
    printf("Portanto e finalmente A = %.16e\n\n", A2);
    
    free( aPrazo );
}

void problema2()
{

}

int32_t main(void){

    problema1();

    return 0;
}
