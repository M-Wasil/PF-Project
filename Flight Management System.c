#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKINGS 50
#define MAX_USERS 50
#define MAX_FLIGHTS 20
#define MAX_DESTINATIONS 10
#define superAdminUsername "superadmin"
#define superAdminPassword "S"
#define maxUsernameLength 20

const char l_destination[5][20]={"LAHORE", "ISLAMABAD", "KARACHI", "PESHAWAR", "QUETTA"};
const char i_destination[MAX_DESTINATIONS][20]={
    "LONDON", "BERLIN", "DUBAI", "RIYADH", "BEIJING", "PARIS", 
    "CANBERRA", "TOKYO", "WASHINGTON", "DELHI"
};

typedef struct{
    int day;
    int month;
    int year;
} date;

typedef struct{
    char flightNumber[10];
    char airline[50];
    char departure[50];
    char arrival[50];
    char time[10];
    int seatsAvailable;
    date flightdate;
    int price;
} Flight;

typedef struct{
    int bookingID;
    char flightNumber [20];
    char passengerName[50];
    char departure[50];
    char arrival[50];
    int seatsBooked;
    date flightdate;
    int price;
} Booking;

typedef struct{
	char userID[20];
    char username[20];             
    char password[20];             
    char role[10];                 
} User;

Flight flights[MAX_FLIGHTS];
Booking bookings[MAX_BOOKINGS];
User users[MAX_USERS];

int flightCount = 0;
//Default

void headMessage(const char *title){
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

void start(){
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

void goodbye(){
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
    printf("\t\t\t                 THANK YOU FOR CHOOSING FAST NUCES AIRPORT\n");
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

void printFlightDetails(Flight *flight){
    printf("\t\t\tFlight Number: %s\n", flight->flightNumber);
    printf("\t\t\tAirline: %s\n", flight->airline);
    printf("\t\t\tDeparture: %s\n", flight->departure);
    printf("\t\t\tArrival: %s\n", flight->arrival);
    printf("\t\t\tTime: %s\n", flight->time);
    printf("\t\t\tSeats Available: %d\n", flight->seatsAvailable);
    printf("\t\t\tTicket Price: %d\n",flight->price);
    printf("\t\t\tFlight Date: %02d/%02d/%04d\n", flight->flightdate.day, flight->flightdate.month, flight->flightdate.year);
    printf("press enter to continue\n");
    getchar();
}

void clearInputBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void ensureFileExists(const char *filename){
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        file = fopen(filename, "w");
        if (file != NULL) {
            printf("File '%s' created successfully.\n", filename);
        } else {
            printf("Error creating file '%s'.\n", filename);
        }
    } else{
        fclose(file);
    }
}

void choiceMenu(){
    printf("\n--- Flight Management System ---\n");
    printf("1. Add Flight\n");
    printf("2. Display Flights\n");
    printf("3. Search Flight\n");
    printf("4. Delete Flight\n");
    printf("5. View Booked Flights\n");
    printf("6. Exit\n");
    printf("Select an option: ");
}

int verifySuperAdmin(){
    char Password[50];
    char Username[50];
    int maxAttempts = 3;
    int attempt = 0;

    printf("Super Admin Login\n");
    while (attempt < maxAttempts){
        printf("Enter Super Admin Username: ");
        fgets(Username, sizeof(Username), stdin);
        Username[strcspn(Username, "\n")] = '\0';

        printf("Enter Super Admin Password: ");
        fgets(Password, sizeof(Password), stdin);
        Password[strcspn(Password, "\n")] = '\0';

        if (strcmp(Username, superAdminUsername) == 0 && strcmp(Password, superAdminPassword) == 0){
            printf("Access granted!\n");
            return 1;
        }
        printf("Invalid Username or Password. You have %d attempts left.\n", maxAttempts - attempt - 1);
        attempt++;
    }
    printf("Access denied.\n");
    return 0;
}

void searchFlight(){
    Flight flightinfo;
    int found = 0;  
    char search [20];
    FILE *fp = fopen("records.dat", "rb");

    if (fp == NULL){
        printf("\n\t\t\tFile not opened. Make sure the file exists.\n");
        exit(1);
    }
    headMessage("SEARCH FLIGHTS");
    printf("\n\n\t\t\tEnter flight number to search: ");
    fgets(search,sizeof(search),stdin);
	search[strcspn(search,"\n")]='\0';

    while (fread(&flightinfo, sizeof(flightinfo), 1, fp) == 1){
        if (strcmp(flightinfo.flightNumber,search)==0){
            printf("\n\t\t\tFlight Number: %s\n", flightinfo.flightNumber);
            printf("\t\t\tDeparture: %s\n", flightinfo.departure);
            printf("\t\t\tArrival: %s\n", flightinfo.arrival);
            printf("\t\t\tFlight Departure Time: %s\n", flightinfo.time);
            printf("\t\t\tTicket Price: %d\n",flightinfo.price);
            printf("\t\t\tDate: %02d/%02d/%04d\n",flightinfo.flightdate.day,flightinfo.flightdate.month,flightinfo.flightdate.year);
            found=1;
            break;
        }
    }

    if (!found){
        printf("\n\t\t\tNo record found for flight number %d.\n",search);
    }

    fclose(fp);
    printf("\n\n\t\t\tPress Enter to go to the main menu...");
    getchar();
}

void displayAvailableFlights(){
    FILE *fp = fopen("records.dat", "rb+");
    if (fp == NULL){
        printf("\n\t\t\tFile not opened. Make sure the file exists.\n");
        exit(1);
    }
    Flight flight;
    int count = 1;

    while (fread(&flight, sizeof(Flight), 1, fp) == 1){
        printf("\n\tRecord: %d", count++);
        printf("\n\tFlight Number: %s", flight.flightNumber);
        printf("\n\tDeparture: %s", flight.departure);
        printf("\n\tArrival: %s", flight.arrival);
        printf("\n\tTime: %s", flight.time);
        printf("\n\tTicket Price: %d",flight.price);
        printf("\n\tDate: %02d/%02d/%04d", flight.flightdate.day, flight.flightdate.month, flight.flightdate.year);
        printf("\n\tSeats Available: %d\n", flight.seatsAvailable);
    }
    fclose(fp);
}

void deleteFlight(){
    FILE *fptr = fopen("records.dat", "rb+");
    if (fptr == NULL) {
        printf("Error in opening file\n");
        return;
    }

    Flight flight;
    char flightNumber[10];
    int found = 0;

    printf("Enter the flight number to delete: ");
    scanf("%s", flightNumber);

    FILE *temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        printf("Error creating temporary file.\n");
        fclose(fptr);
        return;
    }

    // Read each flight and write it to the temp file unless it matches the flight number to be deleted
    while (fread(&flight, sizeof(Flight), 1, fptr)) {
        if (strcmp(flight.flightNumber, flightNumber) == 0) {
            found = 1;
            printf("Flight %s has been deleted.\n", flightNumber);
            continue;  // Skip writing this flight to the temp file
        }
        fwrite(&flight, sizeof(Flight), 1, temp);  // Write the flight to temp file
    }

    fclose(fptr);
    fclose(temp);

    if (!found) {
        printf("Flight number %s not found.\n", flightNumber);
        return;
    }

    // Replace the original file with the temp file
    remove("records.dat");
    rename("temp.dat", "records.dat");

    printf("Flight deletion successful.\n");
}


void addFlight(){
    FILE *fp = fopen("records.dat", "ab+");
    if (fp == NULL){
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }

    Flight flight;
    printf("\nEnter Flight Number: ");
    fgets(flight.flightNumber, sizeof(flight.flightNumber), stdin);
    flight.flightNumber[strcspn(flight.flightNumber, "\n")] = '\0';  
    printf("\nEnter Airline Name: ");
    fgets(flight.airline, sizeof(flight.airline), stdin);
    flight.airline[strcspn(flight.airline, "\n")] = '\0';
    printf("\nEnter Departure City: ");
    fgets(flight.departure, sizeof(flight.departure), stdin);
    flight.departure[strcspn(flight.departure, "\n")] = '\0';
    printf("\nEnter Arrival City: ");
    fgets(flight.arrival, sizeof(flight.arrival), stdin);
    flight.arrival[strcspn(flight.arrival, "\n")] = '\0';
    printf("\nEnter Ticket Price: ");
    scanf("%d",&flight.price);
    printf("\nEnter Time: ");
    fgets(flight.time, sizeof(flight.time), stdin);
    flight.time[strcspn(flight.time, "\n")] = '\0';
    printf("\nEnter Number of Seats Available: ");
    scanf("%d", &flight.seatsAvailable);
    printf("\nEnter Flight Date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &flight.flightdate.day, &flight.flightdate.month, &flight.flightdate.year);

    fwrite(&flight, sizeof(Flight), 1, fp);
    fclose(fp);

    printf("\nFlight added successfully.\n");
    getchar();  
}
// Passenger portion
void passengerMenu(){
    printf("----Passenger Menu----\n\n");
    printf("1.Book a flight\n");
    printf("2.Cancel booking\n");
    printf("3.Change login credentials\n");
    printf("4.View booked flights\n");
    printf("5.Exit\n");
}

void addPassengerAccount() {
    ensureFileExists("Passenger Accounts.txt");
    FILE *file = fopen("Passenger Accounts.txt", "rb+");
    if (!file) {
        printf("Error: Could not open file\n");
        return;
    }

    User passenger, temp;
    int usernameTaken = 0;

    printf("Enter passenger username: ");
    fgets(passenger.username, sizeof(passenger.username), stdin);
    passenger.username[strcspn(passenger.username, "\n")] = '\0';

    // Check for existing username
    while (fread(&temp, sizeof(User), 1, file)) {
        if (strcmp(temp.username, passenger.username) == 0) {
            usernameTaken = 1;
            break;
        }
    }

    if (usernameTaken) {
        printf("Error: Username is already taken.\n");
        fclose(file);
        return;
    }

    printf("Enter passenger password: ");
    fgets(passenger.password, sizeof(passenger.password), stdin);
    passenger.password[strcspn(passenger.password, "\n")] = '\0';

    strncpy(passenger.role, "Passenger", sizeof(passenger.role) - 1);
    passenger.role[sizeof(passenger.role) - 1] = '\0';

    srand(time(NULL));
    int str1 = rand() % 1000000;
    char str2[2] = {rand() % (90 - 65 + 1) + 65, '\0'};
    sprintf(passenger.userID, "%s%06d", str2, str1);

    printf("Your User ID is: %s\n", passenger.userID);

    fseek(file, 0, SEEK_END);
    fwrite(&passenger, sizeof(User), 1, file);
    fclose(file);

    printf("Passenger account added successfully.\n");
}


int verifyPassengerAccount(char *username) {
    char password[50],userID[20];
    int attempt = 0;

    FILE *file = fopen("Passenger Accounts.txt", "rb");
    if (file == NULL) {
        printf("Error: Passenger accounts file not found.\n");
        return 0;
    }

    while (attempt < 3){
    	printf("Enter user ID: ");
    	fgets(userID, 50, stdin);
        userID[strcspn(userID, "\n")] = '\0';
        
        printf("Enter passenger username: ");
        fgets(username, 50, stdin);
        username[strcspn(username, "\n")] = '\0';

        printf("Enter passenger password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';

        User passenger;
        while (fread(&passenger, sizeof(User), 1, file)){
            if (strcmp(username, passenger.username) == 0 && strcmp(password, passenger.password) == 0 && strcmp(userID, passenger.userID) == 0){
                printf("\nLogin successful. Welcome, %s!\n", username);
                fclose(file);
                return 1;
            }
        }
        rewind(file);
        printf("Invalid username or password. Try again.\n");
        attempt++;
    }

    fclose(file);
    printf("Too many failed attempts\n");
    return 0;
}


int verification(int bill) {
    char passportNumber[50], visaNumber[50], modeOfPayment[50], credit[20], debit[20], bank[20];
    int isValidPassport = 0, isValidVisa = 0, isValidPayment = 0, bal = 0, lim = 0, count = 0;

    while (count < 3) {
        printf("Enter your passport number: ");
        fgets(passportNumber, sizeof(passportNumber), stdin);
        passportNumber[strcspn(passportNumber, "\n")] = '\0';

        if (strlen(passportNumber) >= 6) {
            isValidPassport = 1;
        } else {
            printf("Invalid passport number. Must be at least 6 characters.\n");
        }

        printf("Enter your visa number: ");
        fgets(visaNumber, sizeof(visaNumber), stdin);
        visaNumber[strcspn(visaNumber, "\n")] = '\0';

        if (strlen(visaNumber) >= 6) {
            isValidVisa = 1;
        } else {
            printf("Invalid visa number. Must be at least 6 characters.\n");
        }

        printf("Enter mode of payment (Credit/Debit/Cash): ");
        fgets(modeOfPayment, sizeof(modeOfPayment), stdin);
        modeOfPayment[strcspn(modeOfPayment, "\n")] = '\0';

        if (strcmp(modeOfPayment, "Credit") == 0) {
            printf("Enter your credit card number (16 digits, no spaces): ");
            scanf("%s", credit);
            getchar(); // Clear buffer
            if (strlen(credit) == 16) {
                printf("Enter your credit card limit: ");
                scanf("%d", &lim);
                getchar(); // Clear buffer
                if (lim >= bill) {
                    isValidPayment = 1;
                } else {
                    printf("Insufficient credit card limit.\n");
                }
            } else {
                printf("Invalid credit card number. Must be 16 digits.\n");
            }

        } else if (strcmp(modeOfPayment, "Debit") == 0) {
            printf("Enter your debit card number (16 digits, no spaces): ");
            scanf("%s", debit);
            getchar(); // Clear buffer
            if (strlen(debit) == 16) {
                printf("Enter your account balance: ");
                scanf("%d", &bal);
                getchar(); // Clear buffer
                if (bal >= bill) {
                    isValidPayment = 1;
                } else {
                    printf("Insufficient account balance.\n");
                }
            } else {
                printf("Invalid debit card number. Must be 16 digits.\n");
            }

        } else if (strcmp(modeOfPayment, "Cash") == 0) {
            printf("Enter your bank account number (14 digits, no spaces): ");
            scanf("%s", bank);
            getchar(); // Clear buffer
            if (strlen(bank) == 14) {
                printf("Enter your account balance: ");
                scanf("%d", &bal);
                getchar(); // Clear buffer
                if (bal >= bill) {
                    isValidPayment = 1;
                } else {
                    printf("Insufficient account balance.\n");
                }
            } else {
                printf("Invalid bank account number. Must be 14 digits.\n");
            }

        } else {
            printf("Invalid payment mode. Please select Credit, Debit, or Cash.\n");
        }

        if (isValidPassport && isValidVisa && isValidPayment) {
            printf("\nVerification successful! All details are valid.\n");
            return 1;
        } else {
            printf("\nVerification failed. Please check your details and try again.\n");
            count++;
        }
    }

    printf("Error: Too many failed attempts. Booking terminated.\n");
    return 0;
}



void booking(const char *loggedInUsername) {
    Flight f;
    FILE *fptr = fopen("records.dat", "r+b");
    FILE *file = fopen("Passenger Accounts.txt", "rb");
    if (fptr == NULL) {
        printf("\n\t\t\tError opening flight records file.\n");
        return;
    }
    if (file == NULL) {
        printf("\n\t\t\tError opening passenger accounts file.\n");
        fclose(fptr);
        return;
    }

    char dest[50], dept[50];
    int seats, day, month, year, total = 0;

    printf("Welcome, %s!\n", loggedInUsername);
    printf("Enter your destination: ");
    fgets(dest, sizeof(dest), stdin);
    dest[strcspn(dest, "\n")] = '\0';
    printf("Enter your departure: ");
    fgets(dept, sizeof(dept), stdin);
    dept[strcspn(dept, "\n")] = '\0';
    printf("When do you want to fly with us (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &day, &month, &year);
    getchar();

    int found = 0;
    while (fread(&f, sizeof(Flight), 1, fptr) == 1) {
        if (strcmp(f.arrival, dest) == 0 && strcmp(f.departure, dept) == 0 &&
            f.flightdate.day == day && f.flightdate.month == month && f.flightdate.year == year) {
            printf("Flight found!\n");
            printf("Available seats: %d\n", f.seatsAvailable);
            printf("Ticket Price: %d\n", f.price);
            printf("How many seats would you like to book? ");
            scanf("%d", &seats);
            getchar();
            total = seats * f.price;

            int check = verification(total);
            if (check == 1) {
                if (seats <= f.seatsAvailable) {
                    f.seatsAvailable -= seats;
                    printf("Booking successful! %d seats booked.\n", seats);
                    srand(time(NULL));
                    int bookingNumber = rand() % 1000000;

                    Booking newBooking;
                    newBooking.bookingID = bookingNumber;
                    strcpy(newBooking.passengerName, loggedInUsername);
                    strcpy(newBooking.flightNumber, f.flightNumber);
                    strcpy(newBooking.departure, f.departure);
                    strcpy(newBooking.arrival, f.arrival);
                    newBooking.flightdate = f.flightdate;
                    newBooking.seatsBooked = seats;

                    FILE *bookingFile = fopen("bookings.txt", "ab");
                    if (bookingFile == NULL) {
                        printf("\nError opening booking file.\n");
                        fclose(fptr);
                        fclose(file);
                        return;
                    }
                    fwrite(&newBooking, sizeof(Booking), 1, bookingFile);
                    fclose(bookingFile);

                    printf("\nBooking Details:\n");
                    printf("Booking ID: %d\n", newBooking.bookingID);
                    printf("Passenger Name: %s\n", newBooking.passengerName);
                    printf("Flight Number: %s\n", newBooking.flightNumber);
                    printf("Departure: %s\n", newBooking.departure);
                    printf("Arrival: %s\n", newBooking.arrival);
                    printf("Date: %02d/%02d/%04d\n", newBooking.flightdate.day, newBooking.flightdate.month, newBooking.flightdate.year);
                    printf("Seats Booked: %d\n", newBooking.seatsBooked);

                    fseek(fptr, -sizeof(Flight), SEEK_CUR);
                    if (fwrite(&f, sizeof(Flight), 1, fptr) != 1) {
                        printf("\nError updating flight record.\n");
                    }
                    found = 1;
                    break;
                } else {
                    printf("Not enough seats available. Please try again.\n");
                    found = 1;
                    break;
                }
            } else {
                printf("Verification Failed\n");
            }
        }
    }
    if (!found) {
        printf("No matching flight found.\n");
    }
    fclose(fptr);
    fclose(file);
}


void cancelBookings(const char *loggedInUser) {
    FILE *fptr = fopen("records.dat", "rb+");
    if (fptr == NULL) {
        printf("Error opening flight records file.\n");
        return;
    }

    FILE *bookingFile = fopen("bookings.txt", "r+b");
    if (bookingFile == NULL) {
        printf("Error opening booking file.\n");
        fclose(fptr);
        return;
    }

    Flight flight;
    Booking booking;
    int bookingId, foundFlight = 0, foundBooking = 0;

    printf("Enter booking ID to cancel: ");
    scanf("%d", &bookingId);
    getchar();

    // Search for the booking in the file
    while (fread(&booking, sizeof(Booking), 1, bookingFile)) {
        if (booking.bookingID == bookingId && strcmp(booking.passengerName, loggedInUser) == 0) {
            foundBooking = 1;
            printf("Booking found for %s on flight %s, %d seats booked.\n",
                   booking.passengerName, booking.flightNumber, booking.seatsBooked);
            break;
        }
    }

    if (!foundBooking) {
        printf("Booking ID %d not found or does not belong to %s.\n", bookingId, loggedInUser);
        fclose(fptr);
        fclose(bookingFile);
        return;
    }

    fseek(fptr, 0, SEEK_SET);

    // Update flight records
    while (fread(&flight, sizeof(Flight), 1, fptr)) {
        if (strcmp(flight.flightNumber, booking.flightNumber) == 0) {
            foundFlight = 1;
            flight.seatsAvailable += booking.seatsBooked;

            fseek(fptr, -sizeof(Flight), SEEK_CUR);
            fwrite(&flight, sizeof(Flight), 1, fptr);
            printf("Seats successfully added back to the flight %s.\n", flight.flightNumber);
            break;
        }
    }

    if (!foundFlight) {
        printf("Flight not found for booking ID %d.\n", bookingId);
        fclose(fptr);
        fclose(bookingFile);
        return;
    }

    // Rewrite the booking file excluding the canceled booking
    FILE *tempBookingFile = fopen("tempBookings.txt", "wb");
    if (tempBookingFile == NULL) {
        printf("Error creating temporary booking file.\n");
        fclose(fptr);
        fclose(bookingFile);
        return;
    }

    fseek(bookingFile, 0, SEEK_SET);
    while (fread(&booking, sizeof(Booking), 1, bookingFile)) {
        if (booking.bookingID != bookingId) {
            fwrite(&booking, sizeof(Booking), 1, tempBookingFile);
        }
    }

    fclose(bookingFile);
    fclose(tempBookingFile);
    remove("bookings.txt");
    rename("tempBookings.txt", "bookings.txt");

    fclose(fptr);

    printf("Booking ID %d has been canceled successfully.\n", bookingId);
}


void editFlightRecord() {
    int found = 0; 
    char edit[20]; 
    FILE *fp = fopen("records.dat", "rb+"); 

    if (fp == NULL) {
        printf("\n\t\t\tError: Unable to open file. Ensure the file exists.\n");
        return;
    }

    headMessage("EDIT FLIGHTS");

    printf("\n\n\t\t\tEnter the flight number to edit: ");
    scanf("%s", edit);
    fflush(stdin); 

    rewind(fp);

    Flight flightInfo;

    while (fread(&flightInfo, sizeof(flightInfo), 1, fp) == 1) {
        if (strcmp(flightInfo.flightNumber, edit) == 0) { 
            found = 1;
            
            printf("\n\t\t\tCurrent Flight Details:\n");
            printf("\t\t\tFlight Number: %s\n", flightInfo.flightNumber);
            printf("\t\t\tDeparture: %s\n", flightInfo.departure);
            printf("\t\t\tArrival: %s\n", flightInfo.arrival);
            printf("\t\t\tTiming: %s\n", flightInfo.time);
            printf("\t\t\tDate: %02d/%02d/%04d\n", flightInfo.flightdate.day, flightInfo.flightdate.month, flightInfo.flightdate.year);

            int choice;
            do {
                printf("\n\t\t\tWhat would you like to edit?\n");
                printf("\t\t\t1. Flight Number\n");
                printf("\t\t\t2. Departure City\n");
                printf("\t\t\t3. Arrival City\n");
                printf("\t\t\t4. Timing\n");
                printf("\t\t\t5. Date\n");
                printf("\t\t\t6. Exit Editing\n");
                printf("\t\t\tEnter your choice: ");
                scanf("%d", &choice);
                fflush(stdin);

                switch (choice) {
                    case 1:
                        printf("\t\t\tNew Flight Number: ");
                        fgets(flightInfo.flightNumber, sizeof(flightInfo.flightNumber), stdin);
                        flightInfo.flightNumber[strcspn(flightInfo.flightNumber, "\n")] = '\0';
                        break;

                    case 2:
                        printf("\t\t\tNew Departure City: ");
                        fgets(flightInfo.departure, sizeof(flightInfo.departure), stdin);
                        flightInfo.departure[strcspn(flightInfo.departure, "\n")] = '\0';
                        break;
                    case 3:
                        printf("\t\t\tNew Arrival City: ");
                        fgets(flightInfo.arrival, sizeof(flightInfo.arrival), stdin);
                        flightInfo.arrival[strcspn(flightInfo.arrival, "\n")] = '\0';
                        break;

                    case 4:
                        printf("\t\t\tNew Timing: ");
                        fgets(flightInfo.time, sizeof(flightInfo.time), stdin);
                        flightInfo.time[strcspn(flightInfo.time, "\n")] = '\0';
                        break;

                    case 5:
                        printf("\t\t\tNew Date (dd mm yyyy): ");
                        scanf("%d %d %d", &flightInfo.flightdate.day, &flightInfo.flightdate.month, &flightInfo.flightdate.year);
                        fflush(stdin);
                        break;

                    case 6:
                        printf("\t\t\tExiting editing menu.\n");
                        break;

                    default:
                        printf("\t\t\tInvalid choice! Please try again.\n");
                        break;
                }
            } while (choice != 6);

            fseek(fp, sizeof(flightInfo), SEEK_CUR);

            if (fwrite(&flightInfo, sizeof(flightInfo), 1, fp) != 1) {
                printf("\t\t\tError updating record.\n");
            } else {
                printf("\t\t\tRecord updated successfully.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("\n\t\t\tFlight number %s not found.\n", edit);
    }

    fclose(fp);
}

void passenger(const char *loggedInUser) {
    FILE *fptr = fopen("bookings.txt", "rb");
    if (fptr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Booking booking;
    int found = 0;
    printf("Booked Flights for %s:\n", loggedInUser);
    while (fread(&booking, sizeof(Booking), 1, fptr)) {
        if (strcmp(booking.passengerName, loggedInUser) == 0) {
            found = 1;
            printf("Booking ID: %d\n", booking.bookingID);
            printf("Passenger Name: %s\n", booking.passengerName);
            printf("Flight Number: %s\n", booking.flightNumber);
            printf("Departure: %s\n", booking.departure);
            printf("Arrival: %s\n", booking.arrival);
            printf("Date: %02d/%02d/%04d\n", booking.flightdate.day, booking.flightdate.month, booking.flightdate.year);
            printf("Seats Booked: %d\n", booking.seatsBooked);
            printf("\n");
        }
    }
    if (!found) {
        printf("No bookings found for %s.\n", loggedInUser);
    }
    fclose(fptr);
}

void admin(){
    FILE *bookingFile = fopen("bookings.txt", "rb");
    if (bookingFile == NULL) {
        printf("Error opening booking file.\n");
        return;
    }

    Booking booking;
    int found = 0;

    printf("All Booked Flights:\n");

    while (fread(&booking, sizeof(Booking), 1, bookingFile)) {
        found = 1;
        printf("Booking ID: %d\n", booking.bookingID);
        printf("Passenger Name: %s\n", booking.passengerName);
        printf("Flight Number: %s\n", booking.flightNumber);
        printf("Departure: %s\n", booking.departure);
        printf("Arrival: %s\n", booking.arrival);
        printf("Date: %02d/%02d/%04d\n", booking.flightdate.day, booking.flightdate.month, booking.flightdate.year);
        printf("Seats Booked: %d\n", booking.seatsBooked);
        printf("\n");
    }

    if (!found) {
        printf("No bookings found.\n");
    }

    fclose(bookingFile);
}


void changeAccountDetails(){
    int choice, found = 0;
    FILE *fp = fopen("Passenger Accounts.txt", "r+b");
    if (fp == NULL) {
        printf("\n\t\t\tError: Unable to open the file.\n");
        return;
    }

    User accountInfo;
    char username[20];
    
    verifyPassengerAccount(username);  // Ensure user is logged in and set the username

    while (fread(&accountInfo, sizeof(accountInfo), 1, fp) == 1) {
        if (strcmp(username, accountInfo.username) == 0) {
            found = 1;
            printf("Account found. Select the field to edit:\n");
            printf("1. Username\n");
            printf("2. Password\n");
            printf("3. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            getchar();  // Clear the newline character left by scanf
            
            switch (choice) {
                case 1:
                    printf("Enter new username: ");
                    fgets(accountInfo.username, sizeof(accountInfo.username), stdin);
                    accountInfo.username[strcspn(accountInfo.username, "\n")] = '\0';  // Remove newline
                    break;
                case 2:
                    printf("Enter new password: ");
                    fgets(accountInfo.password, sizeof(accountInfo.password), stdin);
                    accountInfo.password[strcspn(accountInfo.password, "\n")] = '\0';  // Remove newline
                    break;
                case 3:
                    fclose(fp);
                    return; 
                default:
                    printf("Invalid choice.\n");
                    break;
            }

            // Now update the file with the modified account info
            fseek(fp, -sizeof(accountInfo), SEEK_CUR);  // Move back to the start of the current record
            fwrite(&accountInfo, sizeof(accountInfo), 1, fp);  // Write the modified record

            printf("Account details updated successfully.\n");
            break;  // Exit the loop after updating
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

    do {
        printf("\n--- Main Menu ---\n");
        printf("1. Super Admin Login\n");
        printf("2. Passenger Login\n");
        printf("3. Passenger Sign up\n");
        printf("4. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);
        clearInputBuffer();
        switch (choice) {
            case 1:
                isLoggedIn = verifySuperAdmin();
                if (isLoggedIn) {
                    while (isLoggedIn == 1) {
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
                                deleteFlight();
                                break;
                            case 5:
                            	admin();
                            	break;
                            case 6:
                                printf("Exiting the admin system...\n");
                                isLoggedIn = 0;
                                break;
                            default:
                                printf("Invalid option, please try again.\n");
                                break;
                        }
                    }
                }
                break;
            case 2:  
                isLoggedIn=verifyPassengerAccount(username);
                if (isLoggedIn) {
                    while (isLoggedIn == 1) {
                        passengerMenu();
                        scanf("%d", &choice);
                        clearInputBuffer();
                        switch (choice) {
                            case 1:
                                booking(&username);
                                break;
                            case 2:
                                cancelBookings(&username);
                                break;
                            case 3:
                                changeAccountDetails();
                                break;
                            case 4:
                            	passenger(&username);
                            	break;
                            case 5:
                                printf("Exiting the passenger system...\n");
                                isLoggedIn = 0;
                                break; 
                            default:
                                printf("Invalid option, please try again.\n");
                                break;
                        }
                    }
                }
                break;
            case 3:
                addPassengerAccount();
                break;
            case 4:
                goodbye();  
                exit(0); 
            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    } while (1);

    return 0;
}

