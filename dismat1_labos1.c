#include <stdio.h>
#include <math.h>

double rek(double lambda_1, double lambda_2, double a_0, double a_1, int n)
{

    if (n == 0)
    {
        return a_0;
    }

    else if (n == 1)
    {
        return a_1;
    }

    return ((lambda_1 * rek(lambda_1, lambda_2, a_0, a_1, n - 1)) + (lambda_2 * rek(lambda_1, lambda_2, a_0, a_1, n - 2)));
}

int main(void)
{

    double lambda_1;
    double lambda_2;
    double a_0;
    double a_1;
    int n;

    double rjFormula;
    double rjRekurzija;

    printf("Unesite prvi koeficijent λ_1 rekurzivne relacije: ");
    scanf("%lf", &lambda_1);

    printf("Unesite drugi koeficijent λ_2 rekurzivne relacije: ");
    scanf("%lf", &lambda_2);

    printf("Unesite vrijednost nultog clana niza a_0: ");
    scanf("%lf", &a_0);

    printf("Unesite vrijednost prvog clana niza a_1: ");
    scanf("%lf", &a_1);

    printf("Unesite redni broj n trazenog clana niza: ");
    scanf("%d", &n);

    double b = -lambda_1;
    double c = -lambda_2;

    double x1;
    double x2;

    x1 = (-b + sqrt(pow(b, 2) - (4 * c))) / 2.0;
    x2 = (-b - sqrt(pow(b, 2) - (4 * c))) / 2.0;

    double k1;
    double k2;

    if (x1 != x2)
    {
        k1 = a_0 - k1;
        k2 = ((a_0 * x1) - a_1) / (x1 - x2);
        rjFormula = k1 * pow(x1, n) + k2 * pow(x2, n);
    }

    else
    {
        k1 = a_0;
        k2 = (a_1 - (k1 * x1)) / x2;
        rjFormula = k1 * pow(x1, n) + k2 * n * pow(x2, n);
    }

    printf("Vrijednost n-tog clana niza pomocu formule: ");
    printf("%lf\n", rjFormula);

    printf("Vrijednost n-tog clana niza iz rekurzije: ");
    printf("%lf\n", rek(lambda_1, lambda_2, a_0, a_1, n));

    return 0;
}