#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKINGS 50
#define MAX_USERS 50
#define MAX_FLIGHTS 20
#define superAdminUsername "superadmin"
#define superAdminPassword "S@fep@ssw0rd!"

typedef struct{
	int day;
	int month;
	int year;
} date;

typedef struct {
    int flightNumber;
    char airline[50];
    char departure[50];
    char arrival[50];
    char time[10];
    int seatsAvailable;
    date flightdate;
} Flight;

typedef struct{
    int bookingID;                 
    int flightNumber;              
    char passengerName[50];        
    char contactInfo[50];          
    int seatNumber;                
    int status; 
} Booking;

// typedef struct{
//     char username[20];             
//     char password[20];             
// } Admin;

typedef struct{
    
    char username[20];             
    char password[20];             
    char role[10];                 
}User;

Flight flights[MAX_FLIGHTS];
Booking bookings[MAX_BOOKINGS];
User users[MAX_USERS];

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
	getch(); 
}

void goodbye() {
	printf("\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t                                  xxx\n");
	printf("\t\t\t                                xxxxxxx\n");
	printf("\t\t\t                            xxxxxxxxxxxxxxx\n");
	printf("\t\t\t                        xxxxxxxxxxxxxxxxxxxxxxx\n");
	printf("\t\t\t                    xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printf("\t\t\t                xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printf("\t\t\t            xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printf("\t\t\t        xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printf("\t\t\t    xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printf("\t\t\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printf("\t\t\t                 THANK YOU FOR CHOOSING HEATHROW AIRPORT\n");
	printf("\t\t\t                        Please come again soon\n");
	printf("\t\t\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printf("\t\t\t    xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printf("\t\t\t        xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printf("\t\t\t            xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printf("\t\t\t                xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printf("\t\t\t                    xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printf("\t\t\t                        xxxxxxxxxxxxxxxxxxxxxxx\n");
	printf("\t\t\t                            xxxxxxxxxxxxxxx\n");
	printf("\t\t\t                                xxxxxxx\n");
	printf("\t\t\t                                  xxx\n");
}

void printFlightDetails(Flight *flight) {
    printf("\t\t\tFlight Number: %d\n", flight->flightNumber);
    printf("\t\t\tAirline: %s\n", flight->airline);
    printf("\t\t\tDeparture: %s\n", flight->departure);
    printf("\t\t\tArrival: %s\n", flight->arrival);
    printf("\t\t\tTime: %s\n", flight->time);
    printf("\t\t\tSeats Available: %d\n", flight->seatsAvailable);
    printf("\t\t\tFlight Date: %02d/%02d/%04d\n", flight->flightdate.day, flight->flightdate.month, flight->flightdate.year);
    printf("press enter to continue\n");
    getchar();  
}

void clearInputBuffer() {
    int c;
    // Consume all characters left in the input buffer until a newline or EOF is found.
    while ((c = getchar()) != '\n' && c != EOF);
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

    printf("Enter flight date (dd mm yyyy): ");
    scanf("%d %d %d", &flight.flightdate.day, &flight.flightdate.month, &flight.flightdate.year);
    clearInputBuffer(); 
    printf("Enter time (HH:MM): ");
    fgets(flight.time, sizeof(flight.time), stdin);
    flight.time[strcspn(flight.time, "\n")] = '\0';

    printf("Enter number of available seats: ");
    scanf("%d", &flight.seatsAvailable);
    

    flights[flightCount++] = flight;
    printf("Flight added successfully!\n");
}

void verifySuperAdmin() {
    
    char Password[50];
    char Username[50];
    int maxAttempts = 3;
    int attempt = 0;

    printf("Super Admin Login\n");
    while (attempt < maxAttempts) {
        printf("Enter Super Admin Username: ");
        fgets(Username, sizeof(Username), stdin);
        Username[strcspn(Username, "\n")] = '\0'; 

        printf("Enter Super Admin Password: ");
        fgets(Password, sizeof(Password), stdin);
        Password[strcspn(Password, "\n")] = '\0'; 

        if (strcmp(Username, superAdminUsername) == 0 && strcmp(Password, superAdminPassword) == 0) {
            printf("Access granted!\n");
            return; 
        } else {
            printf("Invalid username or password. Try again.\n");
            attempt++;
        }
    }

    printf("Too many failed attempts. Access denied.\n");
    exit(1); // Exit the program for security reasons
}

// void addAdminAccount(){
//     if(!verifySuperAdminLogin){
//         printf("not a super admin\n");
//         return;
//     }
//     ensureFileExists("admin_accounts.txt");
//     FILE *file = fopen("admin_accounts.txt", "a");
//     char username[50], password[50];
//     printf("Enter admin username: ");
//     fgets(username, sizeof(username), stdin);
//     username[strcspn(username, "\n")] = '\0';
//     printf("Enter admin password: ");
//     fgets(password, sizeof(password), stdin);
//     password[strcspn(password, "\n")] = '\0';
//     fprintf(file, "%s %s\n", username, password);
//     fclose(file);
// }

void addPassengerAccount(){
    ensureFileExists("passenger_accounts.txt");
    FILE *file = fopen("passenger_accounts.txt", "a");
    char username[50], password[50];
    printf("Enter passenger username:");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';
    printf("Enter passenger password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';
    fprintf(file, "%s %s\n", username, password);
    fclose(file);
}

void verifyPassengerAccount() {
    char Username[50], Password[50];
    int attempt = 0;
    int loginSuccessful = 0;  

    FILE *file = fopen("passenger_accounts.txt", "r");
    if (file == NULL) {
        printf("Error: Passenger accounts file not found.\n");
        return;  
    }

    while (attempt < 3) {  
        printf("Enter passenger username: ");
        fgets(Username, sizeof(Username), stdin);
        Username[strcspn(Username, "\n")] = '\0';  

        printf("Enter passenger password: ");
        fgets(Password, sizeof(Password), stdin);
        Password[strcspn(Password, "\n")] = '\0'; 

        char line[100];
        while (fgets(line, sizeof(line), file)) {  
            char storedUsername[50], storedPassword[50];
            sscanf(line, "%s %s", storedUsername, storedPassword);  

            if (strcmp(Username, storedUsername) == 0 && strcmp(Password, storedPassword) == 0) {
                printf("\nLogin successful. Welcome, %s!\n", Username);
                loginSuccessful = 1;
                break; 
            }
        }

        if (loginSuccessful) {
            break;  
        } else {
            printf("Invalid username or password. Try again.\n");
        }

        rewind(file);  // Rewind file pointer for the next attempt
        attempt++;
    }

    if (!loginSuccessful) {
        printf("\nToo many failed attempts. Access denied.\n");
    }

    fclose(file);  
}


void addFlight() {
    FILE *fp;
    Flight flightinfo;  
    ensureFileExists("records.dat");
    fp = fopen("records.dat", "ab+");

    if (fp == NULL) {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }

    headMessage("ADD flightS");
    printf("\n\n\t\t\tENTER flight DETAILS BELOW:");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");

    printf("\n\t\t\tFlight number: ");
    scanf("%d", &flightinfo.flightNumber);
    getchar();  

    printf("\n\t\t\tAirline: ");
    fgets(flightinfo.airline, sizeof(flightinfo.airline), stdin);
    flightinfo.airline[strcspn(flightinfo.airline, "\n")] = '\0';  
    
    printf("\n\t\t\tDeparture: ");
    fgets(flightinfo.departure, sizeof(flightinfo.departure), stdin);
    flightinfo.departure[strcspn(flightinfo.departure, "\n")] = '\0'; 

    printf("\n\t\t\tArrival: ");
    fgets(flightinfo.arrival, sizeof(flightinfo.arrival), stdin);
    flightinfo.arrival[strcspn(flightinfo.arrival, "\n")] = '\0';  

    printf("\n\t\t\tTime: ");
    fgets(flightinfo.time, sizeof(flightinfo.time), stdin);
    flightinfo.time[strcspn(flightinfo.time, "\n")] = '\0';  

    printf("\n\t\t\tSeats Available: ");
    scanf("%d", &flightinfo.seatsAvailable);
    getchar(); 

    printf("\n\t\t\tEnter date (dd): ");
    scanf("%d", &flightinfo.flightdate.day);
    getchar();  

    printf("\n\t\t\tEnter month (mm): ");
    scanf("%d", &flightinfo.flightdate.month);
    getchar();  

    printf("\n\t\t\tEnter year (yyyy): ");
    scanf("%d", &flightinfo.flightdate.year);
    getchar();  
    
    fwrite(&flightinfo, sizeof(flightinfo), 1, fp);
    fclose(fp);
}

void searchFlight() {
    Flight flightinfo;
    int found = 0;  
    int searchflight;
    FILE *fp = fopen("records.dat", "rb");

    if (fp == NULL) {
        printf("\n\t\t\tFile not opened. Make sure the file exists.\n");
        exit(1);
    }
    headMessage("SEARCH FLIGHTS");
    printf("\n\n\t\t\tEnter flight number to search: ");
    scanf("%d", &searchflight);
    clearInputBuffer(); 

    while (fread(&flightinfo, sizeof(flightinfo), 1, fp) == 1){
        if (flightinfo.flightNumber == searchflight){
            printf("\n\t\t\tFlight Number: %d\n", flightinfo.flightNumber);
            printf("\t\t\tDeparture: %s\n", flightinfo.departure);
            printf("\t\t\tArrival: %s\n", flightinfo.arrival);
            printf("\t\t\tTimings: %s\n", flightinfo.time);
            printf("\t\t\tDate: %02d/%02d/%04d\n",
                   flightinfo.flightdate.day,
                   flightinfo.flightdate.month,
                   flightinfo.flightdate.year);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\n\t\t\tNo record found for flight number %d.\n", searchflight);
    }

    fclose(fp);
    printf("\n\n\t\t\tPress Enter to go to the main menu...");
    getchar();
}



int main() {
    int choice;
    char user[20];
   
   start();
   
   while (1) {
    //ensureFileExists("admin_accounts.txt");
    ensureFileExists("passenger_accounts.txt");
    ensureFileExists("destinations.txt");
    ensureFileExists("bookings.txt");
    ensureFileExists("canceled_flights.txt");

   
    printf("All necessary files are ready.\n");
    
    printf("Are you an admin or a passenger? ");
    fgets(user, sizeof(user), stdin);
    user[strcspn(user, "\n")] = '\0';
    
    if(strcmp(user, "admin") == 0){
        verifySuperAdmin();
    }else if(strcmp(user, "passenger") == 0){
        verifyPassengerAccount();
    }
    
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
}