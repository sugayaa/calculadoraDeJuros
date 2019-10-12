#include <math.h>
#include <stdint.h>
#include <stdio.h>
#define i16 int16_t
#define i32 int32_t
#define i64 int64_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t


i64 powerOf ( i64 a, i32 x )
{

    i64 mul = a;

    for( i32 i = 0; i < x-1 ; i++ )
    {
        a *= mul;
    }

    return a;
}

i64 powerOf32i ( i32 b, i32 x )
{
    i64 a = b;

    for( i32 i = 0; i < x; i++ )
    {
        a *= b;
    }

    return a;
}

double powerOfd ( double b, i32 x )
{
    double a = b;

    for( i32 i = 0; i < x; i++ )
    {
        a *= b;
    }

    return a;
}

double f1p1(double A, double J)
{
    return powerOfd( 1 + J/100, 12 ) - ( 1 + A/100 );
}

double fTeste(double x)
{
    return x*x - 2*x - 3;
}

double findRoot(double left, double right, double (*f)(double))
{
    double m = (right+left)/2;

    while( fabs((*f)( m )) > 10e-14)
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
    }

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

    while( fabs( (*f)(m, J) ) > 10e-10 )
    {
        if( (*f)(m, J) * (*f)(m, J) > 0 )
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
    double aPrazo[size];

    for( u16 i = 0; i < size; i++ )
    {
        aPrazo[i] = 141.08;
    }

    double totalAPrazo = 141.08 * 12;
    double diferencaJuros = totalAPrazo - aVista;

    printf("O custo total a prazo é: %.16E\n", totalAPrazo);
    printf("O diferenca a prazo é: %.16E\n", diferencaJuros);

    //1+(A/100)
    double aumentoAnual = totalAPrazo/aVista;
    printf("O aumento anual é: %.16e\n", aumentoAnual);
    double A = (aumentoAnual - 1)*100;
    printf("Portanto A = %.16E\n", A);


    double J = findJ(0, 100, A, f1p1);
    printf("J = %.16e\n\n", J);

}

void problema2()
{

}

int16_t main(void){

    i64 investimento = 100;
   

    printf("A raiz da equação debug é : %.16e\n", findRoot(0,5,fTeste));
    problema1();

    return 0;
}
