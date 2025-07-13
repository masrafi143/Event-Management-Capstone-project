#include<stdio.h>
void createEvent(){
    printf("create event section\n");
}
void viewEvent(){
    printf("view event section\n");   
}
void updateEvent(){   
    printf("update event section\n");
}
void deleteEvent(){
    printf("delete event section\n");   
}
void registerParticipant(){  
    printf("resister event section\n");
}
void submitFeedback(){
    printf("submit feedback section\n");  
}
void viewAttendance(){
    printf("view attendance section\n"); 
}
void generateReport(){
    printf("generate report section\n");
}

void organizer(){
    printf("welcome as organizer\n");
    printf("Event Management System -(Organizer menu)\n");
    printf("1. Create Events\n");
    printf("2. View Events\n");
    printf("3. Update Events\n");
    printf("4. Delete Events\n");
    printf("5. Register Participant\n");
    printf("6. View Attendance\n");
    printf("7. Generate Report\n");
    printf("8. Exit\n");
    printf("Choose an option: ");
    int option;
    scanf("%d", &option);
    printf("You chose option: %d\n", option);
    switch(option){
        case 1: createEvent(); break;
        case 2: viewEvent(); break;
        case 3: updateEvent(); break;
        case 4: deleteEvent(); break;
        case 5: registerParticipant(); break;
        case 6: viewAttendance(); break;
        case 7: generateReport(); break;
        case 8: exit(0); break;
        default: printf("Invalid Option\n");
    }
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
    printf("You chose option: %d\n", option);
    switch(option){
        case 1: viewEvent(); break;
        case 2: registerParticipant(); break;
        case 3: submitFeedback(); break;
        case 4: exit(0); break;
        default: printf("Invalid Option\n");
    }
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
        printf("Invalid option\n");
        break;
    }
}