#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>
#define PI 3.141592653589793

int get_radius();
float area_trapezoid(float r);
void print_definition(void);
void draw_trapezoid(int r, char symbol);
float compare_trapezoids(int r1, int r2);

int main()
{
    setlocale(LC_CTYPE, "RUS");
    int r = get_radius();
    int choice;

    printf("1 — рассчитать площадь\n2 — вывести определение фигуры\n3 — нарисовать фигуру\n4 — сравнить площади двух фигур\n");
    printf("Ваш выбор: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        printf("Площадь: %.2f\n", area_trapezoid((float)r));
        break;
    case 2:
        print_definition();
        break;
    case 3: {
        char symbol;
        printf("Введите символ для рисования: ");
        scanf(" %c", &symbol);
        draw_trapezoid(r, symbol);
        break;
    }
    case 4: {
        int r2 = get_radius();
        float difference = compare_trapezoids(r, r2);

        if (difference > 0)
            printf("Первая фигура больше на %.2f.\n", difference);
        else if (difference < 0)
            printf("Вторая фигура больше на %.2f.\n", -difference);
        else
            printf("Площади равны.\n");

        break;
    }}
    return 0;
}

int get_radius()
{
    int r;
    printf("Введите радиус r: ");
    scanf("%d", &r);
    return r;
}
float area_trapezoid(float r)
{
    double cos30 = cos(30.0 * PI / 180.0);

    return (float)(4.0 * r * r / cos30);
}
void print_definition(void)
{
    printf("Равнобедренная трапеция — четырёхугольник с параллельными основаниями и равными боковыми сторонами, в который вписана окружность.\n");
}

void draw_trapezoid(int r, char symbol)
{
    double cos30 = cos(30.0 * PI / 180.0);
    double sin30 = sin(30.0 * PI / 180.0);

    double topHalf = r * (1.0 - sin30) / cos30;
    double bottomHalf = r * (1.0 + sin30) / cos30;
    int xLimit = (int)(2.0 * bottomHalf) + 2;

    for (int y = r; y >= -r; y--) {
        for (int xScreen = -xLimit; xScreen <= xLimit; xScreen++) {
            double x = xScreen / 2.0;

            double rightSide = fabs(cos30 * x + sin30 * y - r);
            double leftSide = fabs(-cos30 * x + sin30 * y - r);

            int onSide = rightSide < 0.5 || leftSide < 0.5;
            int onBase =
                (y == r && fabs(x) <= topHalf) ||
                (y == -r && fabs(x) <= bottomHalf);

            double circleError = fabs(sqrt(x * x + y * y) - r);
            int onCircle = circleError < 0.5;

            if (onSide || onBase || onCircle)
                putchar(symbol);
            else
                putchar(' ');
        }

        putchar('\n');
    }
}

float compare_trapezoids(int r1, int r2)
{
    return area_trapezoid((float)r1) - area_trapezoid((float)r2);
}