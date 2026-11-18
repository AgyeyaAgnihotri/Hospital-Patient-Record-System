
#include <stdio.h>
#include <string.h>

struct Patient {
    int id, age, severity;
    char name[50], disease[50], doctor[50];
    float cost;
};

struct Patient p[100];
int count = 0;

float calculateCost(int s) {
    if (s == 1)
        return 1000;
    else if (s == 2)
        return 3000;
    else
        return 5000;
}

void saveFile() {
    FILE *fp = fopen("hospital.dat", "wb");

    if (fp == NULL) {
        printf("File error!");
        return;
    }

    fwrite(&count, sizeof(int), 1, fp);
    fwrite(p, sizeof(struct Patient), count, fp);
    fclose(fp);
}

void loadFile() {
    FILE *fp = fopen("hospital.dat", "rb");

    if (fp != NULL) {
        if (fread(&count, sizeof(int), 1, fp) != 1 ||
            count < 0 || count > 100) {
            count = 0;
        } else {
            fread(p, sizeof(struct Patient), count, fp);
        }
        fclose(fp);
    }
}

void registerPatient() {
    if (count >= 100) {
        printf("Record limit reached!\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%d", &p[count].id);

    for (int i = 0; i < count; i++) {
        if (p[i].id == p[count].id) {
            printf("ID already exists!\n");
            return;
        }
    }

    printf("Enter Name: ");
    scanf(" %49[^\n]", p[count].name);

    printf("Enter Age: ");
    scanf("%d", &p[count].age);

    printf("Enter Disease: ");
    scanf(" %49[^\n]", p[count].disease);

    printf("Enter Doctor: ");
    scanf(" %49[^\n]", p[count].doctor);

    printf("Severity (1=Low, 2=Medium, 3=High): ");
    scanf("%d", &p[count].severity);

    if (p[count].severity < 1 || p[count].severity > 3) {
        printf("Invalid severity!\n");
        return;
    }

    p[count].cost = calculateCost(p[count].severity);
    count++;

    saveFile();
    printf("Patient registered successfully!\n");
}

void displayPatients() {
    if (count == 0) {
        printf("No records found!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\nID: %d", p[i].id);
        printf("\nName: %s", p[i].name);
        printf("\nAge: %d", p[i].age);
        printf("\nDisease: %s", p[i].disease);
        printf("\nDoctor: %s", p[i].doctor);
        printf("\nSeverity: %d", p[i].severity);
        printf("\nTreatment Cost: Rs. %.2f\n", p[i].cost);
    }
}

void searchPatient() {
    int id, choice, found = 0;
    char name[50];

    printf("1. Search by ID\n2. Search by Name\n");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter ID: ");
        scanf("%d", &id);
    } else if (choice == 2) {
        printf("Enter Name: ");
        scanf(" %49[^\n]", name);
    } else {
        printf("Invalid choice!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        if ((choice == 1 && p[i].id == id) ||
            (choice == 2 && strcmp(p[i].name, name) == 0)) {

            printf("\nID: %d", p[i].id);
            printf("\nName: %s", p[i].name);
            printf("\nAge: %d", p[i].age);
            printf("\nDisease: %s", p[i].disease);
            printf("\nDoctor: %s", p[i].doctor);
            printf("\nCost: Rs. %.2f\n", p[i].cost);

            found = 1;
        }
    }

    if (!found)
        printf("Patient not found!\n");
}

void updatePatient() {
    int id, found = 0;

    printf("Enter Patient ID: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (p[i].id == id) {
            printf("Enter New Name: ");
            scanf(" %49[^\n]", p[i].name);

            printf("Enter New Age: ");
            scanf("%d", &p[i].age);

            printf("Enter New Disease: ");
            scanf(" %49[^\n]", p[i].disease);

            printf("Enter New Doctor: ");
            scanf(" %49[^\n]", p[i].doctor);

            printf("Enter Severity (1-3): ");
            scanf("%d", &p[i].severity);

            if (p[i].severity < 1 || p[i].severity > 3) {
                printf("Invalid severity!\n");
                return;
            }

            p[i].cost = calculateCost(p[i].severity);
            saveFile();

            printf("Record updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Patient not found!\n");
}

int main() {
    int choice;

    loadFile();

    do {
        printf("\n\n===== HOSPITAL MANAGEMENT SYSTEM =====");
        printf("\n1. Register Patient");
        printf("\n2. Display All Patients");
        printf("\n3. Search Patient");
        printf("\n4. Update Patient");
        printf("\n5. Exit");
        printf("\nEnter Choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerPatient();
                break;

            case 2:
                displayPatients();
                break;

            case 3:
                searchPatient();
                break;

            case 4:
                updatePatient();
                break;

            case 5:
                printf("Thank You!\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while (choice != 5);

    return 0;
}
