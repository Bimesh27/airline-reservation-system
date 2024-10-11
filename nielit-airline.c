#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Aeroplane gi sheet ki masing, mi kym channi, khotni
const int CAPACITY = 102;

//sina passenger gi details amam amam sum ibadi nungaitena structure(struct) amada oina punsille
typedef struct Passenger {
    char name[50];
    char email[50];
    char password[20];
    char destination[20];
    char seatNumber[3]; // 
} Passenger;

//sina reserveTwbagi linkList , masigi list sida ywdoise passengerGi details ka mathangi haidi magi hak matungda reserver twba list tugi memory address ka;
typedef struct ReservationNode {
    Passenger passenger; // sina passenger gi details ni
    struct ReservationNode* next; // aduga sina magihek mathngda reserve twrkpa list tugi location
} ReservationNode; // maming (typedef digi matengna)

// sina hek chngbada thagada wahei khra phajanaba yengbada, explain twbagi mathw tade sidi, this fucntion will call later in the main function ======================
void displayHeader() {
    printf("\n***************************************************");
    printf("\n\t     Welcome to Nielit Airline");
    printf("\n\t(same airline, different destination)");
    printf("\n***************************************************");
}

// sina eikhoina book/reserve twgadba seat keido hanna available oibra oidabra yengba, oirgadi seat no thokni haidi A1, B1 oidragana x thokkani
void displayAvailableSeats(int* seats) {
    printf("     x means taken\n");
    printf("------------------------\n");
    for (int i = 0; i < CAPACITY; i++) { // sina seat mymdo print twnaba loop chatlaga oina twre, heitrasu heiba manaba, loop se capacity buk ne run twdoise haidi 102 seats masingdo
        char row = 'A' + (i / 6);  //aduga sina row no do update twnana A gi value se 65 neba integer dadi 66 hek yabada B ondoine adunane i / 6 haise, eg. oins hairabada ahanbada i se 1 ne na khallo 1/6 ti 0.45 ra keinoma taramni adubu int oiba nina 0 oina lwni aduga i sina 6 hek oibada 1+ twraga B ondoine
        int col = (i % 6) + 1;     // sigi co gise kok kharadi ngaobne haidi i se 0 nena twro 0 % 6 ti 1 tai , formuladune "remainder=dividend−(divisor×quotient)" sigi formula se paliniko

        if (seats[i] == 0) { // sina seat he hangbra yengine ahanbada seats loinabkki value se 0 loi lei, marmdi eina main fucntion da calloc sijinaraga memory allocate twbanina, calloc sizinaradi 0 da initialized loi twdoine, 0 leiraga hangge, 1 keigumba leiradi mina book twgre hangdre hairini
            printf(" %c%d ", row, col); //sina seat printtwba c sina A(row), d sina(col);
        } else {
            printf("  x "); // sina keigumba seat to mina hanna book twramadi x oina print twrakani
        }
        if (col == 6) {
            printf("\n"); // sidi eina kok ngaodana hpsilbne haidi row amam2 oina namnaba A gina firstline da B gina tonganba line amada, row amada col 6 hek subada anouba line ama hwgrani
        }
    }
}

// Function to check if the entered seat is either valid or taken
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
        return 0;  // Invalid
    }
    return 1; // Valid
}

// Function to register user ================================
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

    seats[seatIndex] = 1; // Mark the seat as taken

    ReservationNode* newNode = (ReservationNode*)malloc(sizeof(ReservationNode));
    newNode->passenger = newPassenger;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode; // First passenger
    } else {
        ReservationNode* temp = head;
        while (temp->next != NULL) {
            temp = temp->next; // Traverse to the end
        }
        temp->next = newNode; // Append to the end
    }
    printf("Passenger registered successfully! Seat %s is reserved.\n", newPassenger.seatNumber);
    return head;
}

// Function to cancel the reservation =======================
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
                // We are deleting the head node; update head
                head = temp->next;
            } else {
                // Bypass the current node
                prev->next = temp->next;
            }
            free(temp); // Free memory allocated for the reservation
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

// Function to display the menu and choose ==========================
void displayMenu(int* seats, ReservationNode* head) {
    int choice = 0; // sina choice user na khangadba, eina 0 na initialized twrisina global variable oidabnina twda yadbeine, twningbabudi ntte haha;

    while (choice != 6) { // sigi while loop se choice se 6 ka manadribuk cttoine, marmdi 6 ti exit nina
        char* choices[] = {"Register a Passenger", "Available Seats", "Cancel a Reservation",
                           "Display all Reservations (admin Only)", "Display my Reservation", "Exit"}; // sisu eina choice mymdo string gi array amada tungsnle, loop ctlaga print twge twbne heiba mannaba;
        printf("\nChoose an option to continue 1 - 6\n");

        for (int i = 0; i < 6; i++) {
            printf("%d. %s \n", i + 1, choices[i]); // loop ctlaga 1.Register sumaina printtwrknabe %d%s haisina , i + 1 sidi 0 dagi hwbado nungaitena twbne 1 dagi hwnaba;
        }
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        printf("\n***************************************************\n"); //phajanaba thok thak ni sina;
        
        switch (choice) { //switch case twraga choice khanhalle
            case 1:
                head = registerPassenger(seats, head); //keigumba sigi fucntion se khanlakadi sigi fucntion se call twduini, eina head ta assign amuk twrisina main fucntion da reflect laknabani head se pass by value oinabina, natradi fucntion sigi manungda twba thbk mymdo main fn da reflect twrakaroi;
                break; // sigi break se ywdradi mathnda makhagi sisu call twgrani adunani hapise
            case 2:
                printf("Available Seats: \n");
                displayAvailableSeats(seats); //chp manei sisu
                break;
            case 3:
                head = cancelReservation(seats, head); //sisu
                break;
            case 4:
                displayAllReservations(head); //sisu
                break;
            case 5:
                displayMyReservation(head); //sisu
                break;
            case 6:
                printf("Exiting Program.\n"); // sina user duna 6 khnlabanina loire 
                break;
            default:
                printf("Invalid choice. Please try again.\n"); //sina sono chuba minaga 8 kumba khnlakanda Invalid choice hainaba;
        }
    }
}

int main() {
    int* seats = (int*)calloc(CAPACITY, sizeof(int)); // I use calloc because it automatically initializes every element with zero
    ReservationNode* head = NULL;

    displayHeader(); //header fucntion ngasai declare twgibadi call twba 
    displayMenu(seats, head); // siu display menu call twba eina seats masing ga head haidi ahanba linked list ta point twdoriba pointer ga pass twre

    // Free the linked list
    // ReservationNode* current = head;
    // while (current != NULL) {
    //     ReservationNode* next = current->next;
    //     free(current);
    //     current = next;
    // }

    free(seats); //sina konna sijinaba loiraga eina allocate twgiba memory do clean twba
    printf("\nFeel free to contact");
    return 0;
}
