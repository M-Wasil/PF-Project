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

typedef struct{
    int bookingID;                 
    int flightNumber;              
    char passengerName[50];        
    char contactInfo[50];          
    int seatNumber;                
    char status[15]; 
} Booking;

typedef struct{
    char username[20];             
    char password[20];             
} Admin;

typedef struct{
    
    char username[20];             
    char password[20];             
    char role[10];                 
}User;

Flight flights[MAX_FLIGHTS];
Booking bookings[MAX_BOOKINGS];
User users[MAX_USERS];

Flight flights[MAX_FLIGHTS];
int flightCount = 0;

void headMessage(const char *title)
{
	system("cls");
	printf("\t\t\t###########################################################################");
	printf("\n\t\t\t############                                                   ############");
	printf("\n\t\t\t############            Flight management System              ############");
	printf("\n\t\t\t############                                                   ############");
	printf("\n\t\t\t###########################################################################");
	printf("\n\t\t\t---------------------------------------------------------------------------\n");
	printf("\t\t\t\t\t\t\t%s", title);
	printf("\n\t\t\t----------------------------------------------------------------------------");
}

void start()
{
	headMessage("PF PROJECT");
	printf("\n\n\n\n\n");
	printf("\n\t\t\t  ********************\n");
	printf("\n\t\t\t        =============================================");
	printf("\n\t\t\t        =                 WELCOME                   =");
	printf("\n\t\t\t        =                   TO                      =");
	printf("\n\t\t\t        =                 FLIGHT                    =");
	printf("\n\t\t\t        =               MANAGEMENT                  =");
	printf("\n\t\t\t        =                 SYSTEM                    =");
	printf("\n\t\t\t        =============================================");
	printf("\n\n\t\t\t  ********************\n");
	printf("\n\n\n\t\t\t Press Enter to continue.....");
	getch(); // this will pause the program until the user has pressed some key on the keyboard
}

void ensureFileExists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        
        file = fopen(filename, "w");
        if (file != NULL) {
            printf("File '%s' created successfully.\n", filename);
        } else {
            printf("Error creating file '%s'.\n", filename);
        }
    } else {

        fclose(file);
    }
}


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
    ensureFileExists("admin_passwords.txt");
    ensureFileExists("destinations.txt");
    ensureFileExists("bookings.txt");
    ensureFileExists("canceled_flights.txt");

    printf("All necessary files are ready.\n");
    
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
