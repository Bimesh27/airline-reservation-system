#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// aeroplane capacity, no of sheet in other words
const int CAPACITY = 102;

typedef struct Passenger {
  char name[50];
  char email[50];
  char password[10];
  char sheetNumber[3]; // e.g., "A1", "B2", size three because i need to store null terminator
} Passenger;

typedef struct ReservationNode {
  Passenger passenger; //this holds the passenger information
  struct ReservationNode* next; // this points to the next reservation node in the linkedlist
} ReservationNode;

//function to initialized the sheets with the capacity
// ========================DONT NEED OF THIS FUNCTION AS I USE CALLOC======================
// void initializeSeats(int* seats) {
//   for (int i = 0; i < CAPACITY; i++) {
//     seats[i] = 0;
//   }
// }
// ==========================================================================================

//fucntion to look fancy haha not so imp
void displayHeader() {
  printf("\n***************************************************");
  printf("\n\t     Welcome to Nielit Airline");
  printf("\n***************************************************");
}

//function to check the available sheets
void displayAvailableSeats(int* seats) {
  printf("     x means taken\n");
  printf("------------------------\n");
  for (int i = 0; i < CAPACITY; i++) {
      char row = 'A' + (i / 6);  // Determine the row (A, B, C, etc.)
      int col = (i % 6) + 1;     // Determine the seat number in that row  using remainder formula which is -remainder =  Dividend - (Quotient * Divisor)
    if (seats[i] == 0) { // 0 means the seat is available
      // Print the seat in the same row on the same line
      printf(" %c%d ", row, col);
            // After printing 6 seats (one row), start a new line
    } else {
        // If the seat is taken, print a placeholder (space or 'XX')
        printf("  x "); // This will print three spaces for better formatting
    }
    if (col == 6) {
        printf("\n");
    }
  }
}

//fucntion to register user 
void registerPassenger(int* seats, ReservationNode* head) {
  Passenger newPassenger;
  printf("Enter Name: ");
  scanf("%s", newPassenger.name);

  printf("Enter Email: ");
  scanf("%s", newPassenger.email);

  printf("Enter Password: ");
  scanf("%s", newPassenger.password);

  printf("Enter Seat Number (e.g., A1): ");
  scanf("%s", newPassenger.sheetNumber);

  int row = newPassenger.sheetNumber[0] - 'A'; // getting the first row  A -A = 0, B - A = 1
  int col = newPassenger.sheetNumber[1] - '1'; // '1' - '1' = 0; 

  //check the column no of the selected row
  int seatIndex = row * 6 + col;

  if(seats[seatIndex] == 0) { // meaning the seat is empty
    ReservationNode *newNode = (ReservationNode*) malloc(sizeof(ReservationNode));
    newNode->passenger = newPassenger;
    newNode->next = NULL;

    if(head == NULL) {
      head = newNode;
    } else {
      ReservationNode *temp = head;
      while (temp->next != NULL) {
        temp = temp->next;
      }
      temp->next = newNode;  // Append to the end
    }

    seats[seatIndex] = 1;
    printf("Passenger register successfully! Seat %s is reserved \n", newPassenger.sheetNumber);
    return;
  } else {
    printf("Sorry, seat %s is already taken. Please choose another seat.\n",newPassenger.sheetNumber);
  }
}

void cancelReservation(int* seats,ReservationNode* head) {
  printf("Reservation cancel");
}
// function to display the menu, for the user to choose option
void displayMenu(int *seats, ReservationNode *head){
  int choice = 0;

  while (choice != 4) {
    char *choices[] = {"Register a Passenger", "Available Seats", "Cancel a Reservation", "Exit"};
    printf("Choose an option to continue 1 - 4\n");

    for (int i = 0; i < 4; i++){
      printf("%d. %s \n", i + 1, choices[i]);
    }

    printf("Enter your choice: \n");
    scanf("%d", &choice);

    switch (choice){
    case 1:
      registerPassenger(seats, head);
      break;
    case 2:
      printf("Available Seats: \n");
      displayAvailableSeats(seats);
      break;
    case 3:
      cancelReservation(seats, head);
      break;
    case 4:
      printf("Exiting Program. \n");
      break;
    default:
      printf("Invalid choice. Please try again");
    }

  }
}

int main() {  
  int *seats = (int*)calloc(CAPACITY, sizeof(int)); //i use calloc because calloc automatically initialized every element with 0zero)
  // initializeSeats(seats);
  // printf("Sheets have been initialized\n");
  //printing the available sheets
  // printf("Available Seats:\n");
  // displayAvailableSeats(seats);
  ReservationNode* head = NULL;
  displayHeader();
  displayMenu(seats, head);

  free(seats);
  printf("\nFeel free to contact");
  return 0;
}