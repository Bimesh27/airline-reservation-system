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
    struct ReservationNode *next;
} ReservationNode;

// Function declarations
void displayHeader();
void displayAvailableSeats(int *seats);
int seatNoValidation(char *seatNumber, int *seats);
void registerPassenger(int *seats, ReservationNode **head);
void cancelReservation(int *seats, ReservationNode **head);
void displayAllReservations(ReservationNode *head);
void displayMyReservation(ReservationNode *head);
void displayMenu(int *seats, ReservationNode **head);
void freeReservations(ReservationNode *head);

int main() {
    int *seats = (int *)calloc(CAPACITY, sizeof(int)); // Seat array initialized
    ReservationNode *head = NULL;                     // Linked list head

    displayHeader();
    displayMenu(seats, &head);

    free(seats);              // Free seat array memory
    freeReservations(head);   // Free linked list memory

    return 0;
}

// Display header
void displayHeader() {
    printf("\n***************************************************");
    printf("\n\t     Welcome to Nielit Airline");
    printf("\n\t(same airline, different destination)");
    printf("\n***************************************************\n");
}

// Display available seats
void displayAvailableSeats(int *seats) {
    printf("     x means taken\n");
    printf("-------------------------\n");

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

// Validate seat number
int seatNoValidation(char *seatNumber, int *seats) {
    if (strlen(seatNumber) != 2) {
        printf("Invalid seat number format! Please enter in the format of A1, B1 etc.\n");
        return 0;
    }

    char row = seatNumber[0];
    char col = seatNumber[1];

    if (!(row >= 'A' && row <= 'Q' && col >= '1' && col <= '6')) {
        printf("Invalid seat number! Row must be between A and Q and column between 1 and 6.\n");
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

// Register passenger
void registerPassenger(int *seats, ReservationNode **head) {
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
        printf("Enter Seat Number (e.g A1): ");
        scanf("%s", newPassenger.seatNumber);
    } while (!seatNoValidation(newPassenger.seatNumber, seats));

    char row = newPassenger.seatNumber[0];
    char col = newPassenger.seatNumber[1];
    int rowIndex = row - 'A';
    int colIndex = col - '1';
    int seatIndex = rowIndex * 6 + colIndex;

    seats[seatIndex] = 1;

    ReservationNode *newNode = (ReservationNode *)malloc(sizeof(ReservationNode));
    newNode->passenger = newPassenger;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        ReservationNode *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    printf("Passenger registered successfully! Seat %s is reserved.\n", newPassenger.seatNumber);
}

// Cancel reservation
void cancelReservation(int *seats, ReservationNode **head) {
    char email[50];
    char password[20];

    printf("Enter your Email: ");
    scanf("%s", email);

    printf("Enter your Password: ");
    scanf("%s", password);

    if (*head == NULL) {
        printf("No reservation found.\n");
        return;
    }

    ReservationNode *temp = *head;
    ReservationNode *prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->passenger.email, email) == 0 && strcmp(temp->passenger.password, password) == 0) {
            char row = temp->passenger.seatNumber[0];
            int rowIndex = row - 'A';
            int colIndex = temp->passenger.seatNumber[1] - '1';
            int seatIndex = rowIndex * 6 + colIndex;
            seats[seatIndex] = 0;

            if (prev == NULL) {
                *head = temp->next;
            } else {
                prev->next = temp->next;
            }

            free(temp);
            printf("Reservation cancelled successfully!\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("No reservation found with the given email and password.\n");
}

// Display all reservations
void displayAllReservations(ReservationNode *head) {
    if (head == NULL) {
        printf("No reservations found.\n");
        return;
    }

    ReservationNode *ptr = head;
    while (ptr != NULL) {
        printf("Passenger Name: %s, Seat: %s, Destination: %s\n",
               ptr->passenger.name, ptr->passenger.seatNumber, ptr->passenger.destination);
        ptr = ptr->next;
    }
}

// Display specific reservation
void displayMyReservation(ReservationNode *head) {
    char email[50];
    char password[20];

    printf("Enter your Email: ");
    scanf("%s", email);

    printf("Enter your Password: ");
    scanf("%s", password);

    ReservationNode *ptr = head;
    int found = 0;

    while (ptr != NULL) {
        if (strcmp(ptr->passenger.email, email) == 0 && strcmp(ptr->passenger.password, password) == 0) {
            printf("Reservation found:\n");
            printf("Name: %s\n", ptr->passenger.name);
            printf("Seat: %s\n", ptr->passenger.seatNumber);
            printf("Destination: %s\n", ptr->passenger.destination);
            found = 1;
            break;
        }
        ptr = ptr->next;
    }

    if (!found) {
        printf("No reservation found with the given email and password.\n");
    }
}

// Free reservations linked list
void freeReservations(ReservationNode *head) {
    ReservationNode *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Display menu
void displayMenu(int *seats, ReservationNode **head) {
    int choice = 0;

    while (choice != 6) {
        printf("\nChoose an option to continue (1-6):\n");
        printf("1. Register a Passenger\n");
        printf("2. Display Available Seats\n");
        printf("3. Cancel a Reservation\n");
        printf("4. Display My Reservation\n");
        printf("5. Display All Reservations\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n***************************************************\n");

        switch (choice) {
            case 1:
                registerPassenger(seats, head);
                break;
            case 2:
                printf("Available Seats:\n");
                displayAvailableSeats(seats);
                break;
            case 3:
                cancelReservation(seats, head);
                break;
            case 4:
                displayMyReservation(*head);
                break;
            case 5:
                printf("All Reservations:\n");
                displayAllReservations(*head);
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
