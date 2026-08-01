#include <stdio.h>

struct Complex {
    float real;
    float imag;
};

void Add_cmplx(struct Complex *c1, struct Complex *c2, struct Complex *res) {
    res->real = c1->real + c2->real;
    res->imag = c1->imag + c2->imag;
}

void Mult_cmplx(struct Complex *c1, struct Complex *c2, struct Complex *res) {
    res->real = (c1->real * c2->real) - (c1->imag * c2->imag);
    res->imag = (c1->real * c2->imag) + (c1->imag * c2->real);
}

void Div_cmplx(struct Complex *c1, struct Complex *c2, struct Complex *res) {
    float denom = (c2->real * c2->real) + (c2->imag * c2->imag);
    res->real = ((c1->real * c2->real) + (c1->imag * c2->imag)) / denom;
    res->imag = ((c1->imag * c2->real) - (c1->real * c2->imag)) / denom;
}

void Negate(struct Complex *c, struct Complex *res) {
    res->real = c->real;
    res->imag = -c->imag;
}

int main() {
    struct Complex num1 = {4.0, 3.0};
    struct Complex num2 = {2.0, 1.0};
    struct Complex res;

    printf("--- Complex Number Operations ---\n\n");
    printf("Operand 1: %.2f + %.2fi\n", num1.real, num1.imag);
    printf("Operand 2: %.2f + %.2fi\n\n", num2.real, num2.imag);

    Add_cmplx(&num1, &num2, &res);
    printf("Addition Result       : %.2f + %.2fi\n", res.real, res.imag);

    Mult_cmplx(&num1, &num2, &res);
    printf("Multiplication Result : %.2f + %.2fi\n", res.real, res.imag);

    Div_cmplx(&num1, &num2, &res);
    printf("Division Result       : %.2f + %.2fi\n", res.real, res.imag);

    Negate(&num1, &res);
    printf("Conjugate of Op 1     : %.2f + %.2fi\n", res.real, res.imag);

    return 0;
}