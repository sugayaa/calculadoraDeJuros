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

double fJ1(double x)
{
    double starting = -1559.15;
    
    for( i16 i = 0; i < 12; i++ )
    {
        starting += 141.08/pow(1 + x/100, i);
    }

    return starting;
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

double fJf1(double x)
{
    double starting = -1692.96;

    for ( i16 i = 11; i >= 0; i-- )
    {
        starting += 141.08/pow(1 + x/100, i);
    }

    return starting;
}

double newfindRoot(double left, double right, double fA, double* ins, i16 s, double (*f)(double, double, double*, i16))
{
    double m = (right+left)/2;

    if ( fabs((*f)(left, fA, ins, s)) < 10e-14 )
        return left;
    else if ( fabs((*f)(right, fA, ins, s)) < 10e-14 )
        return right;

    double oleft  = left;
    double oright = right;

    i32 i = 0;

    while( (fabs((*f)( m, fA, ins, s )) > 10e-13) and i < 0x7fffffff )
    {
        if( (*f)( left, fA, ins, s ) * (*f)( m, fA, ins, s ) > 0 )
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
    //double aumentoAnual = totalAPrazo/aVista;
    //printf("O aumento anual é: %.4lf\n", aumentoAnual);
    //double A = (aumentoAnual - 1)*100;
    //printf("Portanto A = %.16e\n", A);

    double Jf = findRoot(0, 100, fJf1);
    printf("Taxa de juros mensais com valor futuro (JF) = %1.15lf\%\n", Jf);

    double J = newfindRoot(0, 100, aVista, aPrazo, size, fJ);
    printf("Taxa de juros mensais (J) = %1.15lf\%\n", J);
 
    double J2 = findRoot(0, 100, fJ1);
    printf("Taxa de juros mensais (J) = %1.15lf\%\n", J2);



    double A2 = findA(0, 100, J, relacaoJurosMensaleAnual);
    printf("Taxa de juros anual (A)   = %1.15lf\%\n\n\n", A2);
    
    free( aPrazo );
}

void problema2()
{
    double valorAVista = 129000;
    double taxaAVista  = 2;

    double pagamentoAPrazo[] = { 27000, 24000, 30000, 32000, 22000 };
    double valorAPrazo = 0;

    i16 size = sizeof( pagamentoAPrazo ) / sizeof( pagamentoAPrazo[0] );

    printf("O tamanho é: %d\n", size);

    for ( i16 i = 0; i < 5; i++ )
    {
        valorAPrazo += pagamentoAPrazo[i];
    }

    printf("O pagamento total a vista é = %.2lf\n", valorAVista);
    printf("O pagamento total a prazo é = %.2lf\n", valorAPrazo);
    printf("O diferenca entre os pagamentos é = %.2lf\n\n", valorAPrazo - valorAVista);

    double J = newfindRoot(0, 100, valorAVista, pagamentoAPrazo, size, fJ);
    printf("Taxa de juros mensais (J) = %1.15lf\%\n", J);


}


int32_t main(void){

    problema1();
    problema2();

    return 0;
}
