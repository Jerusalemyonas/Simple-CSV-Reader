#include<stdio.h> 

typedef struct data
{
   char type;
   char name[50];
   int age;
   double salary;
} Employee;

int main(void)
{
    FILE *file;

    file = fopen("file.txt", "r");

    if (file == NULL) {
        printf("Error opening the file\n");
        return 1;
    }

    Employee employees[100];

    int read = 0;
    int records = 0;

    do {
        read = fscanf(file,
                      "%c, %49[^,], %d, %lf\n",
                      &employees[records].type,  // & for passing the memory address
                      employees[records].name,
                      &employees[records].age,
                      &employees[records].salary);

        if (read == 4) 
            records++;

        if (read != 4 && !feof(file)) {
            printf("File format incorrect.\n");
            fclose(file);
            return 1;
        }

        if (ferror(file)) {
            printf("Error reading file.\n");
            fclose(file);
            return 1;
        }

    } while (!feof(file)); // continue until the end of file

    fclose(file);

    printf("\n%d records read.\n\n", records);

    for (int i = 0; i < records; i++)
        printf("%c %s %d %.2f\n",
               employees[i].type,
               employees[i].name,
               employees[i].age,
               employees[i].salary);

    printf("\n");

    return 0;
}
