#ifndef NUMBER_H
#define NUMBER_H
typedef enum {
    SHORT,
    INT,
    FLOAT,
    DOUBLE,
    LONGLONG
}number_t;

typedef union{
    short s;
    int i;
    float f;
    double d;
    long long ll;
}number;

#define Arithmetic(c, a, operator, b, type){\
    switch (type){\
        case SHORT:\
            c.s = a.s operator b.s;\
            break;\
        case INT:\
            c.i = a.i operator b.i;\
            break;\
        case FLOAT:\
            c.f = a.f operator b.f;\
            break;\
        case DOUBLE:\
            c.d = a.d operator b.d;\
            break;\
        default:\
            c.ll = a.ll operator b.ll;\
    }\
}

#define number_set(a, value, type){\
    switch (type){\
        case SHORT:\
            a.s = (short)value;\
            break;\
        case INT:\
             a.i = (int)value;\
            break;\
        case FLOAT:\
            a.f = (float)value;\
            break;\
        case DOUBLE:\
            a.d = (double)value;\
            break;\
        default:\
            a.ll = (long long)value;\
    }\
}

#define number_print(a, type){\
    switch (type){\
        case SHORT:\
            printf("%d", a.s);\
            break;\
        case INT:\
            printf("%d", a.i);\
            break;\
        case FLOAT:\
            printf("%f", a.f);\
            break;\
        case DOUBLE:\
            printf("%lf", a.d);\
            break;\
        default:\
            printf("%ld", a.ll);\
    }\
}


#endif
