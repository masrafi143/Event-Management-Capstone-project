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
    printf("Events section\n");
    FILE *eventPtr;
    eventPtr = fopen("events.txt", "r");
    if(eventPtr == NULL){
        printf("No events data found.\n");
        return;
    }
    char line[200];
    while(fgets(line, sizeof(line), eventPtr)){
        printf("%s", line);
    }

    fclose(eventPtr);
}
void updateEvent(){   
    printf("update event section\n");
}
void deleteEvent(){
    printf("\n--- Delete Event Section ---\n");
    FILE *eventPtr = fopen("events.txt", "r");
    FILE *tempPtr = fopen("temp.txt", "w");
    if(eventPtr == NULL){
        printf("No events found.\n");
        return;
    }

    char searchTitle[100], line[300];
    int found = 0;
    getchar();
    printf("Enter event title to delete: ");
    fgets(searchTitle, sizeof(searchTitle), stdin);

    int len = strlen(searchTitle);
    if(len > 0 && searchTitle[len-1] == '\n'){
        searchTitle[len-1] = '\0';
    }

    while(fgets(line, sizeof(line), eventPtr)){
        if(strncmp(line, "Title: ", 7) == 0){
            char tempTitle[100];
            strcpy(tempTitle, line + 7);
            len = strlen(tempTitle);
            if(len > 0 && tempTitle[len-1] == '\n'){
                tempTitle[len-1] = '\0';
            }

            if(strcmp(tempTitle, searchTitle) == 0){
                found = 1;
                printf("\n--- Event \"%s\" deleted successfully ---\n", searchTitle);

                for(int i=0; i<7; i++){
                    fgets(line, sizeof(line), eventPtr);
                }
                continue;
            }
        }
        fputs(line, tempPtr);
    }
    fclose(eventPtr);
    fclose(tempPtr);
    remove("events.txt");
    rename("temp.txt", "events.txt");

    if(found){
        printf("--- Event '%s' deleted successfully ---\n", searchTitle);
    } else{
        printf("--- Event '%s' not found ---\n", searchTitle);
        remove("temp.txt");
    }
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
void markAttendance() {
    struct Registration p;
    FILE *participantPtr = fopen("participant.txt", "r");
    FILE *attendancePtr = fopen("attendance.txt", "a");

    if (participantPtr == NULL) {
        printf("No participant found for attendance.\n");
        return;
    }
    char line[200];
    while (fgets(line, sizeof(line), participantPtr)) {
        if (strncmp(line, "Event Title: ", 13) == 0) {
            strcpy(p.eventTitle, line + 13);
            p.eventTitle[strcspn(p.eventTitle, "\n")] = '\0';
        }
        else if (strncmp(line, "Participant Name: ", 18) == 0) {
            strcpy(p.participantName, line + 18);
            p.participantName[strcspn(p.participantName, "\n")] = '\0';
        }
        else if (strncmp(line, "Student ID: ", 12) == 0) {
            strcpy(p.id, line + 12);
            p.id[strcspn(p.id, "\n")] = '\0';
            int status;
            printf("\nMark attendance for:\n");
            printf("Name: %s\nID: %s\nDid the participant attend? (1 for Yes, 0 for No): ", p.participantName, p.id);
            scanf("%d", &status);

            fprintf(attendancePtr, "Event Title: %s\n", p.eventTitle);
            fprintf(attendancePtr, "Participant Name: %s\n", p.participantName);
            fprintf(attendancePtr, "Student ID: %s\n", p.id);
            fprintf(attendancePtr, "Attendance: %s\n", status == 1 ? "Present" : "Absent");
            fprintf(attendancePtr, "-----------------------------\n\n");
        }
    }

    fclose(participantPtr);
    fclose(attendancePtr);
    printf("\n---Attendance marking completed successfully---\n");
}

void viewAttendance(){
    printf("\n---Attendance Section ---\n");
    FILE *attendancePtr;
    attendancePtr = fopen("attendance.txt", "r");
    if(attendancePtr == NULL){
        printf("No attendance data found.\n");
        return;
    }
    char line[200];
    while(fgets(line, sizeof(line), attendancePtr)){
        printf("%s", line);
    }

    fclose(attendancePtr);
    printf("--- End of Attendance List ---\n"); 
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
    printf("6. Mark Attendance\n");
    printf("7. View Attendance\n");
    printf("8. Generate Report\n");
    printf("9. Exit\n");
    printf("Choose an option: ");
    int option;
    scanf("%d", &option);
    switch(option){
        case 1: createEvent(); break;
        case 2: viewEvent(); break;
        case 3: updateEvent(); break;
        case 4: deleteEvent(); break;
        case 5: registerParticipant(); break;
        case 6: markAttendance(); break;
        case 7: viewAttendance(); break;
        case 8: generateReport(); break;
        case 9: exit(0); break;
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