#include<stdio.h>
struct Event{
    char title[100];
    char description[200];
    char date[20];
    char time[20];
    char venue[50];
};
struct Registration{
    char eventTitle[100];
    char participantName[50];
    char id[20];
    char email[40];
};
struct Feedback{
    char eventTitle[100];
    char participantName[50];
    char feedback[1000];
};
void createEvent(){
    struct Event e;
    FILE *eventPtr;
    eventPtr = fopen("events.txt", "a");
    
    printf("Enter how many events you want to create: ");
    int n;
    scanf("%d", &n);
    getchar();
    for(int i=1; i<=n; i++){
        printf("\nCreating Event %d:\n", i);
        printf("Event title: ");
        fgets(e.title, sizeof(e.title), stdin);
        printf("Description: ");
        fgets(e.description, sizeof(e.description), stdin);
        printf("Date: ");
        fgets(e.date, sizeof(e.date), stdin);
        printf("Time: ");
        fgets(e.time, sizeof(e.time), stdin);
        printf("Venue: ");
        fgets(e.venue, sizeof(e.venue), stdin);
    
        fprintf(eventPtr, "Title: %s", e.title);
        fprintf(eventPtr, "Description: %s", e.description);
        fprintf(eventPtr, "Date: %s", e.date);
        fprintf(eventPtr, "Time: %s", e.time);
        fprintf(eventPtr, "Venue: %s\n", e.venue);
        fprintf(eventPtr, "-------------------------\n\n");
        
        printf("--- Event %d saved successfully ---\n", i);
    }
    fclose(eventPtr);   
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
    printf("\n---Register Particiant section.---\nEnter details for registration: \n");
    struct Registration p;
    FILE *participantPtr;
    participantPtr = fopen("participant.txt", "a");

    getchar();
    printf("Event title: ");
    fgets(p.eventTitle, sizeof(p.eventTitle), stdin);
    printf("Participant name: ");
    fgets(p.participantName, sizeof(p.participantName), stdin);
    printf("Student ID: ");
    fgets(p.id, sizeof(p.id), stdin);
    printf("Email: ");
    fgets(p.email, sizeof(p.email), stdin);

    fprintf(participantPtr, "Event Title: %s", p.eventTitle);
    fprintf(participantPtr, "Participant Name: %s", p.participantName);
    fprintf(participantPtr, "Student ID: %s", p.id);
    fprintf(participantPtr, "Email: %s\n", p.email);
    fprintf(participantPtr, "---------------------------\n\n");
    
    printf("\n---Congratulations !! Registration completed successfully---\n");
    fclose(participantPtr);
}
void submitFeedback(){
    printf("---Submit Your Feedback.---\n"); 
    struct Feedback f;
    FILE *feedbackPtr;
    feedbackPtr = fopen("feedback.txt", "a");
    getchar();
    printf("Event title: ");
    fgets(f.eventTitle, sizeof(f.eventTitle), stdin);
    printf("Your Name: ");
    fgets(f.participantName, sizeof(f.participantName), stdin);
    printf("Your Feedback: ");
    fgets(f.feedback, sizeof(f.feedback), stdin);

    fprintf(feedbackPtr, "Event Title: %s", f.eventTitle);
    fprintf(feedbackPtr, "Participant Name: %s", f.participantName);
    fprintf(feedbackPtr, "Feedback: %s\n", f.feedback);
    fprintf(feedbackPtr, "-----------------------------\n\n");

    printf("\n---Thanks for your feedback.---\n");
    fclose(feedbackPtr);
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
    switch (role){
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