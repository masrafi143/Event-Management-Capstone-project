#include<stdio.h>
void organizer(){
    printf("welcome as organizer\n");
    printf("Event Management System -(Organizer menu)\n");
    printf("1. Create Events\n");
    printf("2. View Events\n");
    printf("3. Update Events\n");
    printf("4. Delete Events\n");
    printf("5. Register Participant\n");
    printf("6. Mark Attendance\n");
    printf("7. View Attendance\n");
    printf("8. Generate Report\n");
    printf("9. Exit\n");
    printf("Choose an option: ");
    int option;
    scanf("%d", &option);
    printf("You chose option: %d", option);
}
void participant(){
    printf("welcome as participant\n");
    printf("Event Management System -(Participant menu)\n");
    printf("1. View Events\n");
    printf("2. Register for Event\n");
    printf("3. Submit Feedback\n");
    printf("4. Exit\n");
    printf("Choose an option: ");
    int option;
    scanf("%d", &option);
    printf("You chose option: %d", option);
}
int main(){
    printf("Login as:\n1. Organizer\n2. Participant\nChose role: ");
    int role;
    scanf("%d", &role);
    switch (role)
    {
    case 1:
        organizer();
        break;
    case 2:
        participant();
        break;    
    default:
        printf("Invalid option");
        break;
    }
}