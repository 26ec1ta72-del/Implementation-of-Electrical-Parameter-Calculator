
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <float.h>

double read_value(const char *prompt)
{
    char buffer[100];
    char *end;
    double value;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            printf("\nInput error.\n");
            exit(1);
        }

        value = strtod(buffer, &end);

        if (end == buffer)
        {
            printf("Invalid input! Enter a numeric value.\n");
            continue;
        }

        while (isspace((unsigned char)*end))
            end++;

        if (*end != '\0')
        {
            printf("Invalid input! Enter only a numeric value.\n");
            continue;
        }

        /* Reject NaN and infinity */
        if (value != value || value > DBL_MAX || value < -DBL_MAX)
        {
            printf("Invalid number! Enter a finite value.\n");
            continue;
        }

        if (value < 0)
        {
            printf("Value cannot be negative.\n");
            continue;
        }

        return value;
    }
}

int main()
{
    int choice;
    double voltage, current, resistance, power;
    double input;

    while (1)
    {
        printf("\n====================================\n");
        printf(" ELECTRICAL PARAMETER CALCULATOR\n");
        printf("====================================\n");
        printf("1. Calculate Voltage\n");
        printf("2. Calculate Current\n");
        printf("3. Calculate Resistance\n");
        printf("4. Calculate Power\n");
        printf("5. Exit\n");
        printf("====================================\n");

        input = read_value("Enter your choice: ");

        if (input != (int)input || input < 1 || input > 5)
        {
            printf("Invalid choice! Select an option from 1 to 5.\n");
            continue;
        }

        choice = (int)input;

        switch (choice)
        {
            case 1:
                printf("\n--- Voltage Calculation ---\n");
                current = read_value("Enter Current (A): ");
                resistance = read_value("Enter Resistance (Ohms): ");

                voltage = current * resistance;

                printf("Calculated Voltage = %.2f V\n", voltage);
                break;

            case 2:
                printf("\n--- Current Calculation ---\n");
                voltage = read_value("Enter Voltage (V): ");
                resistance = read_value("Enter Resistance (Ohms): ");

                if (resistance == 0)
                {
                    printf("Error! Resistance cannot be zero.\n");
                    break;
                }

                current = voltage / resistance;

                printf("Calculated Current = %.2f A\n", current);
                break;

            case 3:
                printf("\n--- Resistance Calculation ---\n");
                voltage = read_value("Enter Voltage (V): ");
                current = read_value("Enter Current (A): ");

                if (current == 0)
                {
                    printf("Error! Current cannot be zero.\n");
                    break;
                }

                resistance = voltage / current;

                printf("Calculated Resistance = %.2f Ohms\n",
                       resistance);
                break;

            case 4:
                printf("\n--- Power Calculation ---\n");
                voltage = read_value("Enter Voltage (V): ");
                current = read_value("Enter Current (A): ");

                power = voltage * current;

                printf("Calculated Power = %.2f W\n", power);
                break;

            case 5:
                printf("\nThank you for using the calculator!\n");
                return 0;
        }
    }

    return 0;
}
