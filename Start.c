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
    printf("Enter airline name: ");
    scanf(" %[^\n]s", flight.airline);
    printf("Enter departure location: ");
    scanf(" %[^\n]s", flight.departure);
    printf("Enter arrival location: ");
    scanf(" %[^\n]s", flight.arrival);
    printf("Enter date (DD/MM/YYYY): ");
    scanf(" %[^\n]s", flight.date);
    printf("Enter time (HH:MM): ");
    scanf(" %[^\n]s", flight.time);
    printf("Enter number of available seats: ");
    scanf("%d", &flight.seatsAvailable);

    flights[flightCount++] = flight;
    printf("Flight added successfully!\n");
}

int main() {
    int choice;
    char user[20];
    printf("Are you an admin or a passenger? ");
    scanf("%[^\n]s",user);
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
