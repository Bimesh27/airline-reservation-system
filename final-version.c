#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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


//function declaration kinda useless
void displayHeader();
void displayAvailableSeats(int *seats);
int seatNoValidation(char *seatNumber, int *seats);
void registerPassenger(int *seats, ReservationNode **head);
void cancelReservation(int *seats, ReservationNode **head);
void displayAllReservations(ReservationNode *head);
void displayMyReservation(ReservationNode *head);
void displayMenu(int *seats, ReservationNode *head);


int main(){
  int *seats = (int *)calloc(CAPACITY, sizeof(int));
  ReservationNode *head = NULL;

  displayHeader();
  displayAvailableSeats(seats);
  registerPassenger(seats, &head);

  return 0;
}


//function definition 
void displayHeader() {
  printf("\n***************************************************");
  printf("\n\t     Welcome to Nielit Airline");
  printf("\n\t(same airline, different destination)");
  printf("\n***************************************************\n");
}

void displayAvailableSeats(int *seats) {
  printf("     x means taken\n");
  printf("-------------------------\n");

  for(int i = 0; i < CAPACITY; i++) {
    char row = 'A' + (i/6);
    int col = (i % 6) + 1;

    if(seats[i] == 0) {
      printf(" %c%d ", row, col);
    } else {
      printf("  x ");
    }

    if(col == 6) {
      printf("\n");
    } 
  }
}

int seatNoValidation(char *seatNumber, int *seats) {
  if(strlen(seatNumber) != 2) {
    printf("Invalid seat number format! Please enter in the format of A1, B1 etc. \n");
    return 0;
  }

  char row = seatNumber[0];
  char col = seatNumber[1];

  if(!(row >= 'A' && row <= 'Q' && col >= '1' && col <='6')) {
    printf("Invalid seat number! Row must be between A and Q and column between 1 and 6. \n");
    return 0;
  }

  int rowIndex = row - 'A';
  int colIndex = col -'1';
  int seatIndex = rowIndex * 6 + colIndex;

  if(seats[seatIndex] == 1) {
    printf("Sorry, seat %s is already taken. Please choose another seat.\n", seatNumber);
    return 0;
  }

  return 1;
}

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

  do{
    printf("Enter Seat Number (e.g A1): ");
    scanf("%s", newPassenger.seatNumber);
  } while(!seatNoValidation(newPassenger.seatNumber, seats));

  char row = newPassenger.seatNumber[0];
  char col = newPassenger.seatNumber[1];
  int rowIndex = row - 'A';
  int colIndex = col - '1';
  int seatIndex = rowIndex * 6 + colIndex;

  seats[seatIndex] = 1;

  ReservationNode *newNode = (ReservationNode *)malloc(sizeof(ReservationNode));
  newNode->passenger = newPassenger;
  newNode->next = NULL;

  if(head == NULL) {
    head = newNode;
  } else {
    ReservationNode *temp = head;
    while(temp->next != NULL) {
      temp = temp->next;
    }

    temp->next = newNode;
  }

  printf("Passenger registered successfully ! Seat %s is reserved.\n", newPassenger.seatNumber);
  
}

void cancelReservation(int *seats, ReservationNode **head) {
  char email[50];
  char password[20];

  printf("Enter your Email: ");
  scanf("%s", email);

  printf("Enter your Password: ");
  scanf("%s", password);

  if(head == NULL) {
    printf("No reservation found. \n");
    return 0;
  }

  ReservationNode *temp = head;
  ReservationNode *prev = NULL;


}