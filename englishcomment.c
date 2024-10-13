#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int CAPACITY = 102;

typedef struct Passenger {
    char name[50];
    char email[50];
    char password[20];
    char destination[20];
    char seatNumber[3];
} Passenger;

typedef struct ReservationNode {
    Passenger passenger;
    struct ReservationNode* next;
} ReservationNode;

void displayHeader() {
    printf("\n***************************************************");
    printf("\n\t     Welcome to Nielit Airline");
    printf("\n\t(same airline, different destination)");
    printf("\n***************************************************");
}

void displayAvailableSeats(int* seats) {
    printf("     x means taken\n");
    printf("------------------------\n");
    for (int i = 0; i < CAPACITY; i++) {
        char row = 'A' + (i / 6);
        int col = (i % 6) + 1;

        if (seats[i] == 0) {
            printf(" %c%d ", row, col);
        } else {
            printf("  x ");
        }
        if (col == 6) {
            printf("\n");
        }
    }
}

int seatNoValidation(char* seatNumber, int* seats) {
    if (strlen(seatNumber) != 2) {
        printf("Invalid seat number format! Please enter in the format of A1, B1 etc.\n");
        return 0;
    }

    char row = seatNumber[0];
    char col = seatNumber[1];

    if (!(row >= 'A' && row <= 'Q' && col >= '1' && col <= '6')) {
        printf("Invalid seat number! Row must be between A and R, and column between 1 and 6.\n");
        return 0;
    }

    int rowIndex = row - 'A';
    int colIndex = col - '1';
    int seatIndex = rowIndex * 6 + colIndex;

    if (seats[seatIndex] == 1) {
        printf("Sorry, seat %s is already taken. Please choose another seat.\n", seatNumber);
        return 0;
    }
    return 1;
}

ReservationNode* registerPassenger(int* seats, ReservationNode* head) {
    Passenger newPassenger;
    printf("Enter Name: ");
    scanf("%s", newPassenger.name);

    printf("Enter Email: ");
    scanf("%s", newPassenger.email);

    printf("Enter Password: ");
    scanf("%s", newPassenger.password);

    printf("Enter your destination: ");
    scanf("%s", newPassenger.destination);

    do {
        printf("Enter Seat Number (e.g., A1): ");
        scanf("%s", newPassenger.seatNumber);
    } while (!seatNoValidation(newPassenger.seatNumber, seats));

    char row = newPassenger.seatNumber[0];
    char col = newPassenger.seatNumber[1];
    int rowIndex = row - 'A';
    int colIndex = col - '1';
    int seatIndex = rowIndex * 6 + colIndex;

    seats[seatIndex] = 1;

    ReservationNode* newNode = (ReservationNode*)malloc(sizeof(ReservationNode));
    newNode->passenger = newPassenger;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        ReservationNode* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf("Passenger registered successfully! Seat %s is reserved.\n", newPassenger.seatNumber);
    return head;
}

ReservationNode* cancelReservation(int* seats, ReservationNode* head) {
    char email[50]; 
    char password[20];

    printf("Enter your Email: ");
    scanf("%s", email);
    printf("Enter your Password: ");
    scanf("%s", password);

    if(head == NULL) { 
        printf("No reservations found.\n");
        return head;
    }

    ReservationNode *temp = head;
    ReservationNode *prev = NULL;

    while(temp != NULL) {
        if(strcmp(temp->passenger.email, email) == 0 && strcmp(temp->passenger.password, password) == 0) {
            char row = temp->passenger.seatNumber[0];
            int rowIndex = row - 'A';
            int colIndex = temp->passenger.seatNumber[1] - '1';
            int seatIndex = rowIndex * 6 + colIndex;
            seats[seatIndex] = 0;

            if (prev == NULL) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Reservation cancelled successfully!\n");
            return head;
        }

        prev = temp;
        temp = temp->next;
    }
    printf("No reservation found with the given email and password.\n");
    return head;
}

void displayAllReservations(ReservationNode* head) {
    if (head == NULL) {
        printf("No reservations found.\n");
        return;
    }

    ReservationNode* current = head;
    while (current != NULL) {
        printf("Passenger Name: %s, Seat: %s, Destination: %s\n",
               current->passenger.name,
               current->passenger.seatNumber,
               current->passenger.destination);
        current = current->next;
    }
}

void displayMyReservation(ReservationNode* head) {
    char email[50];
    char password[20];

    printf("Enter your Email: ");
    scanf("%s", email);

    printf("Enter your password: ");
    scanf("%s", password);

    ReservationNode *current = head;
    int found = 0; 

    while(current != NULL) {
        if(strcmp(current->passenger.email, email) == 0 && strcmp(current->passenger.password, password) == 0) {
            printf("Reservation found:\n");
            printf("Name: %s\n", current->passenger.name);
            printf("Seat: %s\n", current->passenger.seatNumber);
            printf("Destination: %s\n", current->passenger.destination);
            found = 1;
        }
        current = current->next;
    }
    if(!found) {
        printf("No reservation found with the given email and password.\n");
    }
}

void displayMenu(int* seats, ReservationNode* head) {
    int choice = 0;

    while (choice != 6) {
        char* choices[] = {"Register a Passenger", "Available Seats", "Cancel a Reservation",
                           "Display all Reservations (admin Only)", "Display my Reservation", "Exit"};
        printf("\nChoose an option to continue 1 - 6\n");

        for (int i = 0; i < 6; i++) {
            printf("%d. %s \n", i + 1, choices[i]);
        }
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        printf("\n***************************************************\n");
        
        switch (choice) {
            case 1:
                head = registerPassenger(seats, head);
                break;
            case 2:
                printf("Available Seats: \n");
                displayAvailableSeats(seats);
                break;
            case 3:
                head = cancelReservation(seats, head);
                break;
            case 4:
                displayAllReservations(head);
                break;
            case 5:
                displayMyReservation(head);
                break;
            case 6:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    }
}

int main() {
    int* seats = (int*)calloc(CAPACITY, sizeof(int));
    ReservationNode* head = NULL;

    displayHeader();
    displayMenu(seats, head);

    free(seats);
    return 0;
}
