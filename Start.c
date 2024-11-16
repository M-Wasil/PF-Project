#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FLIGHTS 20

typedef struct {
    int flightNumber;
    char airline[50];
    char departure[50];
    char arrival[50];
    char date[20];
    char time[10];
    int seatsAvailable;
} Flight;

Flight flights[MAX_FLIGHTS];
int flightCount = 0;

void clearInputBuffer() {
    while (getchar() != '\n'); 
}

void choiceMenu(){
	printf("\n--- Flight Management System ---\n");
    printf("1. Add Flight\n");
    printf("2. Display Flights\n");
    printf("3. Search Flight\n");
    printf("4. Delete Flight\n");
    printf("5. Exit\n");
    printf("Select an option: ");
}

void flight(){
	if (flightCount >= MAX_FLIGHTS) {
        printf("Flight limit reached! Cannot add more flights.\n");
        return;
    }

    Flight flight;
    
    printf("Enter flight number: ");
    scanf("%d", &flight.flightNumber);
    clearInputBuffer(); 

    printf("Enter airline name: ");
    fgets(flight.airline, sizeof(flight.airline), stdin);
    flight.airline[strcspn(flight.airline, "\n")] = '\0'; 

    printf("Enter departure location: ");
    fgets(flight.departure, sizeof(flight.departure), stdin);
    flight.departure[strcspn(flight.departure, "\n")] = '\0';

    printf("Enter arrival location: ");
    fgets(flight.arrival, sizeof(flight.arrival), stdin);
    flight.arrival[strcspn(flight.arrival, "\n")] = '\0';

    printf("Enter date (DD/MM/YYYY): ");
    fgets(flight.date, sizeof(flight.date), stdin);
    flight.date[strcspn(flight.date, "\n")] = '\0';

    printf("Enter time (HH:MM): ");
    fgets(flight.time, sizeof(flight.time), stdin);
    flight.time[strcspn(flight.time, "\n")] = '\0';

    printf("Enter number of available seats: ");
    scanf("%d", &flight.seatsAvailable);
    clearInputBuffer(); 

    flights[flightCount++] = flight;
    printf("Flight added successfully!\n");
}

    

int main() {
    int choice;
    char user[20];
    printf("Are you an admin or a passenger? ");
    fgets(user, sizeof(user), stdin);
    user[strcspn(user, "\n")] = '\0';
    choiceMenu();
    scanf("%d", &choice);
    if (strcmp(user, "admin") == 0){
        do {
        	switch(choice){
        		case 1:
        			flight();
        			break;
        		case 5:
        			break;
			}
        }while (choice != 5);
    }
}
