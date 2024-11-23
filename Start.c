#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKINGS 50
#define MAX_USERS 50
#define MAX_FLIGHTS 20
#define superAdminUsername "superadmin"
#define superAdminPassword "S@fep@ssw0rd!"
#define maxUsernameLength 20

const char l_destination[5][20] = {"LAHORE", "ISLAMABAD", "KARACHI", "PESHAWAR", "QUETTA"};
const char i_destination[MAX_DESTINATIONS][20] = {
    "LONDON", "BERLIN", "DUBAI", "RIYADH", "BEIJING", "PARIS", 
    "CANBERRA", "TOKYO", "WASHINGTON", "DELHI", "ISLAMABAD"
};

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


// void flight(){
// 	if (flightCount >= MAX_FLIGHTS) {
//         printf("Flight limit reached! Cannot add more flights.\n");
//         return;
//     }

//     Flight flight;
    
//     printf("Enter flight number: ");
//     scanf("%d", &flight.flightNumber);
//     clearInputBuffer(); 

//     printf("Enter airline name: ");
//     fgets(flight.airline, sizeof(flight.airline), stdin);
//     flight.airline[strcspn(flight.airline, "\n")] = '\0'; 

//     printf("Enter departure location: ");
//     fgets(flight.departure, sizeof(flight.departure), stdin);
//     flight.departure[strcspn(flight.departure, "\n")] = '\0';

//     printf("Enter arrival location: ");
//     fgets(flight.arrival, sizeof(flight.arrival), stdin);
//     flight.arrival[strcspn(flight.arrival, "\n")] = '\0';

//     printf("Enter flight date (dd mm yyyy): ");
//     scanf("%d %d %d", &flight.flightdate.day, &flight.flightdate.month, &flight.flightdate.year);
//     clearInputBuffer(); 
//     printf("Enter time (HH:MM): ");
//     fgets(flight.time, sizeof(flight.time), stdin);
//     flight.time[strcspn(flight.time, "\n")] = '\0';

//     printf("Enter number of available seats: ");
//     scanf("%d", &flight.seatsAvailable);
    

//     flights[flightCount++] = flight;
//     printf("Flight added successfully!\n");
// }

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
    User passenger;
    printf("Enter passenger username:");
    fgets(passenger.username, sizeof(passenger.username), stdin);
    passenger.username[strcspn(username, "\n")] = '\0';
    printf("Enter passenger password: ");
    fgets(passenger.password, sizeof(passenger.password), stdin);
    passenger.password[strcspn(password, "\n")] = '\0';
    strncpy(passenger.role, "Passenger", sizeof(passenger.role) - 1);
    passenger.role[sizeof(passenger.role) - 1] = '\0'; 
    fwrite(&passenger, sizeof(User), 1, file);
    fclose(file);
}

void verifyPassengerAccount(char *username) {
    char Password[50];
    int attempt = 0;
    int loginSuccessful = 0;  

    FILE *file = fopen("passenger_accounts.txt", "r");
    if (file == NULL) {
        printf("Error: Passenger accounts file not found.\n");
        return;  
    }

    while (attempt < 3) {  
        printf("Enter passenger username: ");
        fgets(username, 50, stdin);
        username[strcspn(username, "\n")] = '\0';  

        printf("Enter passenger password: ");
        fgets(Password, sizeof(Password), stdin);
        Password[strcspn(Password, "\n")] = '\0'; 

        char line[100];
        while (fgets(line, sizeof(line), file)) {  
            char storedUsername[50], storedPassword[50];
            sscanf(line, "%s %s", storedUsername, storedPassword);  

            if (strcmp(username, storedUsername) == 0 && strcmp(Password, storedPassword) == 0) {
                printf("\nLogin successful. Welcome, %s!\n", username);
                loginSuccessful = 1;
                break; 
            }
        }

        if (loginSuccessful) {
            break;  
        } else {
            printf("Invalid username or password. Try again.\n");
        }

        rewind(file);  
        attempt++;
    }

    if (!loginSuccessful) {
        printf("\nToo many failed attempts. Access denied.\n");
    }

    fclose(file);  
}


void addFlight() {
    if (flightCount >= MAX_FLIGHTS) {
        printf("Flight limit reached! Cannot add more flights.\n");
        return;
    }
    Flight flightinfo;  
    ensureFileExists("records.dat");
    FILE *fp; = fopen("records.dat", "ab+");

    if (fp == NULL) {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }

    headMessage("ADD flightS");
    printf("\n\n\t\t\tENTER flight DETAILS BELOW:");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");

    printf("\n\t\t\tFlight number: ");
    scanf("%d", &flightinfo.flightNumber);

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
    // int count = 2;

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

void displayAvailableFlights() {
    FILE *fp = fopen("records.dat", "rb");
    if (fp == NULL) {
        printf("\n\t\t\tFile not opened. Make sure the file exists.\n");
        exit(1);
    }

    headMessage("AVAILABLE FLIGHTS");

    Flight flight;
    int count = 1;

    while (fread(&flight, sizeof(flight), 1, fp) == 1) {
        printf("\n\t\t\tRecord: %d", count++);
        printf("\n\t\t\tFlight Number: %d\n", flight.flightNumber);
        printf("\t\t\tDeparture: %s\n", flight.departure);
        printf("\t\t\tArrival: %s\n", flight.arrival);
        printf("\t\t\tTimings: %s\n", flight.time);
        printf("\t\t\tDate: %02d/%02d/%04d\n", flight.flightdate.day, flight.flightdate.month, flight.flightdate.year);
    }

    fclose(fp);
}

void cancelBookings(){
    FILE *fp = fopen("records.dat", "rb");
    if (fp == NULL) {
        printf("\n\t\t\tFile not opened. Make sure the file exists.\n");
        exit(1);
    }
    headMessage("Cancel Bookings");
    FILE *temp = fopen("temp.dat", "wb");
    if(temp == NULL){
        printf("\n\t\t\tFile not opened. Make sure the file exists.\n");
        exit(1);
        }

    FLight flight;
    int flightno;
    int found = 0;
    printf("Enter the flight number to cancel the booking: "); scanf("%d", &flightno);
    
    while(fread(flight, sizeof(flight), 1, fp) == 1){
        if(flight.flightNumber == flightno){
        found = 1;
        printf("\t\t\tThe booking has been cancelled\n");
        continue;
        }
        fwrite(&flight, sizeof(flight), 1, temp);
    }

    if (!found) {
        printf("\n\t\t\tNo flight found with number %d.\n", flightno);
        fclose(fp);
        fclose(temp);
        remove(temp);
        return;
    }
    fclose(fp);
    fclose(temp);

     remove("records.dat");
     rename("temp.dat", "records.dat");

    printf("\n\t\t\tBooking cancellation process completed.\n");
}

void editFlightRecord() {
    int found = 0; 
    int editFlightNum; 
    FILE *fp = fopen("records.dat", "rb+"); 

    if (fp == NULL) {
        printf("\n\t\t\tError: Unable to open file. Ensure the file exists.\n");
        return;
    }

    headMessage("EDIT FLIGHTS");

    printf("\n\n\t\t\tEnter the flight number to edit: ");
    scanf("%d", &editFlightNum);
    fflush(stdin); 

    rewind(fp);

    Flight flightInfo;

    while (fread(&flightInfo, sizeof(flightInfo), 1, fp) == 1) {
        if (flightInfo.flightnum == editFlightNum) { 
            found = 1;
            
            printf("\n\t\t\tCurrent Flight Details:\n");
            printf("\t\t\tFlight Number: %d\n", flightInfo.flightnum);
            printf("\t\t\tCountry: %s\n", flightInfo.country);
            printf("\t\t\tTiming: %d\n", flightInfo.timing);
            printf("\t\t\tDate: %02d/%02d/%04d\n",
                   flightInfo.flightdate.d, flightInfo.flightdate.m, flightInfo.flightdate.y);

            int choice;
            do {
                printf("\n\t\t\tWhat would you like to edit?\n");
                printf("\t\t\t1. Flight Number\n");
                printf("\t\t\t2. Country\n");
                printf("\t\t\t3. Timing\n");
                printf("\t\t\t4. Date\n");
                printf("\t\t\t5. Exit Editing\n");
                printf("\t\t\tEnter your choice: ");
                scanf("%d", &choice);
                fflush(stdin);

                switch (choice) {
                    case 1:
                        printf("\t\t\tNew Flight Number: ");
                        scanf("%d", &flightInfo.flightnum);
                        fflush(stdin);
                        break;

                    case 2:
                        printf("\t\t\tNew Country: ");
                        fgets(flightInfo.country, sizeof(flightInfo.country), stdin);
                        flightInfo.country[strcspn(flightInfo.country, "\n")] = '\0'; // Remove newline
                        break;

                    case 3:
                        printf("\t\t\tNew Timing: ");
                        scanf("%d", &flightInfo.timing);
                        fflush(stdin);
                        break;

                    case 4:
                        printf("\t\t\tNew Date (dd mm yyyy): ");
                        scanf("%d %d %d", &flightInfo.flightdate.d, &flightInfo.flightdate.m, &flightInfo.flightdate.y);
                        fflush(stdin);
                        break;

                    case 5:
                        printf("\t\t\tExiting editing menu.\n");
                        break;

                    default:
                        printf("\t\t\tInvalid choice! Please try again.\n");
                        break;
                }
            } while (choice != 5);

            fseek(fp, -sizeof(flightInfo), SEEK_CUR);

            if (fwrite(&flightInfo, sizeof(flightInfo), 1, fp) != 1) {
                printf("\n\t\t\tError: Unable to update the record.\n");
            } else {
                printf("\n\t\t\tRecord updated successfully!\n");
            }
            break; 
        }
    }

    if (!found) { 
        printf("\n\t\t\tNo record found with Flight Number: %d\n", editFlightNum);
    }

    fclose(fp); 
    printf("\n\t\t\tPress Enter to return to the main menu...");
    getchar(); 
}

void changeAccountDetails() {
    int choice, found = 0;
    FILE *fp = fopen("passenger_accounts.txt", "r+b");
    if (fp == NULL) {
        printf("\n\t\t\tError: Unable to open the file.\n");
        return;
    }

    User accountInfo;
    char username[20];
    
    verifyPassengerAccount(username);  

    while (fread(&accountInfo, sizeof(accountInfo), 1, fp) == 1) {
        if (strcmp(username, accountInfo.username) == 0) {
            found = 1;
            printf("Account found. Select the field to edit:\n");
            printf("1. Username\n");
            printf("2. Password\n");
            printf("3. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            fflush(stdin);
            
            switch (choice) {
                case 1:
                    printf("Enter new username: ");
                    fgets(accountInfo.username, sizeof(accountInfo.username), stdin);
                    accountInfo.username[strcspn(accountInfo.username, "\n")] = '\0';
                    break;
                case 2:
                    printf("Enter new password: ");
                    fgets(accountInfo.password, sizeof(accountInfo.password), stdin);
                    accountInfo.password[strcspn(accountInfo.password, "\n")] = '\0';
                    break;
                case 3:
                    fclose(fp);
                    return; 
                default:
                    printf("Invalid choice.\n");
                    break;
            }

            
            rewind(fp);
            while (fread(&accountInfo, sizeof(accountInfo), 1, fp) == 1) {
                if (strcmp(username, accountInfo.username) == 0) {
                    fseek(fp, -sizeof(accountInfo), SEEK_CUR);  
                    fwrite(&accountInfo, sizeof(accountInfo), 1, fp); 
                    printf("Account details updated successfully.\n");
                    break;
                }
            }
            break;
        }
    }

    if (!found) {
        printf("No account found with username: %s\n", username);
    }

    fclose(fp);
}



int main() {
    int choice;
    int isLoggedIn = 0;  
    char username[50];

    start();

    while (1) {
        printf("\n--- Main Menu ---\n");
        printf("1. Super Admin Login\n");
        printf("2. Passenger Login\n");
        printf("3. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                verifySuperAdmin();  
                break;

            case 2:
                verifyPassengerAccount(username);  
                isLoggedIn = 1;
                break;

            case 3:
                goodbye();  
                exit(0); 

            default:
                printf("Invalid choice, please try again.\n");
                break;
        }

        
        if (isLoggedIn) {
            while (1) {
                choiceMenu();  
                scanf("%d", &choice);
                clearInputBuffer();

                switch (choice) {
                    case 1:
                        addFlight();  
                        break;

                    case 2:
                        displayAvailableFlights();  
                        break;

                    case 3:
                        searchFlight();  
                        break;

                    case 4:
                        printf("Delete flight functionality is under development.\n");
                        break;

                    case 5:
                        printf("Exiting the system...\n");
                        goodbye();  
                        exit(0);  

                    default:
                        printf("Invalid option, please try again.\n");
                        break;
                }
            }
        }
    }

    return 0;
}