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

double fJ(double x, double fullAmount, double* installments, i16 size_of_i)
{
    fullAmount = -fullAmount;
    
    for ( i16 i = 0; i < size_of_i; i++ )
    {
        fullAmount += installments[i] / pow( 1 + x/100, i );
    }

    return fullAmount;
}

double findRoot(double left, double right, double fA, double* ins, i16 s, double (*f)(double, double, double*, i16))
{
    double m = (right+left)/2;

    if ( fabs((*f)(left, fA, ins, s)) < 10e-14 )
        return left;
    else if ( fabs((*f)(right, fA, ins, s)) < 10e-14 )
        return right;

    double oleft  = left;
    double oright = right;

    i32 i = 0;

    while( (fabs((*f)( m, fA, ins, s )) > 10e-13) and i < 0x0fffffff )
    {
        if( (*f)( left, fA, ins, s ) * (*f)( m, fA, ins, s ) > 0 )
        {
            left = m;
        }
        else
        {
            right = m;
        }

        if ( ( right + left ) / 2 == m )//middle point isn't changing anymore
            break;
        
        m = ( right + left )/ 2;

        if( i == 0x7ffffffd or i == 0x7ffffffe )
            printf("O m está travado em : %.16e", m);
        
        
        if( i == 0x00000fff )
            printf(". "); fflush(stdin);
        if( i == 0x000fffff )
            printf(". "); fflush(stdin);
        if( i == 0x7ffffffe )
            printf(". "); fflush(stdin);
        

        i += 1;
    }
    printf("\n");
    if(m == oleft or m == oright)
        printf("Apparently the range was not properly set.");


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

void problema1( void )
{
    
    printf("Problema 1:\n");

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

    double J = findRoot(0, 100, aVista, aPrazo, size, fJ);
    printf("Taxa de juros mensais (J) = %1.15lf\%\n", J);
 
    double A = findA(0, 100, J, relacaoJurosMensaleAnual);
    printf("Taxa de juros anual (A)   = %1.15lf\%\n\n\n", A);
    
    free( aPrazo );

}

void problema2( void )
{

    printf("Problema 2:\n");

    double valorAVista = 129000;
    double taxaAVista  = 2;

    double pagamentoAPrazo[] = { 27000, 24000, 30000, 32000, 22000 };
    double valorAPrazo = 0;

    i16 size = sizeof( pagamentoAPrazo ) / sizeof( pagamentoAPrazo[0] );

    for ( i16 i = 0; i < 5; i++ )
    {
        valorAPrazo += pagamentoAPrazo[i];
    }

    double J = findRoot(0, 100, valorAVista, pagamentoAPrazo, size, fJ);
    printf("Taxa de juros mensais (J) = %1.15lf\%\n", J);

    if ( J > 2 )
    {
        printf("Vale mais a pena pagar à vista. A taxa de juros é maior que 2\% ao mês\n\n");
    }
    else
    {
        printf("Vale mais a pena pagar em parcelas. A taxa de juros é menor que 2\% ao mês\n\n");
    }


}

void problema3( void )
{
    printf("Problema 3:\n");

    double aVista = 889.18;
    double* aPrazo;
    i16 sz = 112;
    aPrazo = (double*) malloc(sizeof(double) * sz);

    for( i16 i = 0; i < sz - 1; i++ )
    {
        //0 is october
        //1 is november
        //2 is december
        //3 is january
        //4 is february
        //5 is march
        //6 is abril
        //7 is may
        //8 is june
        //9 is july
        //10 is august
        //11 is september
        if ( i % 12 == 3 or i % 12 == 9 )
            aPrazo[i] = 48.81;
    }

    //last january
    aPrazo[111] = 1048.81;

    double J = findRoot(0, 100, aVista, aPrazo, sz, fJ);
    printf("Taxa de rendimento mensal (J) = %.16lf\%\n", J);

    double A = findA(0, 100, J, relacaoJurosMensaleAnual);
    printf("Taxa de rendimento anual (A)   = %2.15lf\%\n\n\n", A);
    
    free( aPrazo );


}

void problema4( void )
{
    printf("Problema 4:\n");

    double aVista = 1207.52;
    double* aPrazo;
    i16 sz = 112;
    aPrazo = (double*) malloc(sizeof(double) * sz);

    for( i16 i = 0; i < sz - 1; i++ )
    {
        if ( i % 12 == 3 or i % 12 == 9 )
            aPrazo[i] = 48.81;
    }

    aPrazo[111] = 1048.81;

    double J = findRoot(0, 100, aVista, aPrazo, sz, fJ);
    printf("Taxa de rendimento mensal (J) = %.16lf\%\n", J);

    double A = findA(0, 100, J, relacaoJurosMensaleAnual);
    printf("Taxa de rendimento anual (A)   = %1.15lf\%\n\n\n", A);
    
    free( aPrazo );


}


int32_t main(void){

    problema1();
    problema2();
    problema3();
    problema4();

    return 0;
}
