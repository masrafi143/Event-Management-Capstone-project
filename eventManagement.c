#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct User {
    char name[50];
    char email[50];
    char password[30];
    char phone[20];
    int role;
};
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

void registerUser(){
    printf("--- User Registration---\n");
    struct User u;
    FILE *userFile = fopen("users.txt", "a");
    if(userFile == NULL){
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Name: ");
    fgets(u.name, sizeof(u.name), stdin);
    u.name[strcspn(u.name, "\n")] = '\0';

    printf("Select Role:\n1. Organizer\n2. Participant\nEnter choice (1 or 2): ");
    scanf("%d", &u.role);
    getchar();

    printf("Enter Email: ");
    fgets(u.email, sizeof(u.email), stdin);
    u.email[strcspn(u.email, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(u.password, sizeof(u.password), stdin);
    u.password[strcspn(u.password, "\n")] = '\0';

    printf("Enter Phone: ");
    fgets(u.phone, sizeof(u.phone), stdin);
    u.phone[strcspn(u.phone, "\n")] = '\0';

    char user[20];
    if(u.role == 1){
        strcpy(user, "Organizer");
    } else if(u.role == 2){
        strcpy(user, "Participant");
    }

    fprintf(userFile, "Name: %s\nRole: %s\nEmail: %s\nPassword: %s\nPhone: %s\n", u.name, user, u.email, u.password, u.phone);

    fclose(userFile);

    printf("Registration successful!\n");
    loginUser();
}
void registerVolunteer(){
    printf("\n--- Register Volunteer Section ---\n");
    FILE *eventPtr = fopen("events.txt", "r");
    if(eventPtr == NULL){
        printf("No events found. Please create an event first.\n");
        return;
    }
    char line[300], eventList[100][100];
    int eventCount = 0;

    while(fgets(line, sizeof(line), eventPtr)){
        if(strncmp(line, "Title: ", 7) == 0){
            strcpy(eventList[eventCount], line + 7);
            eventList[eventCount][strcspn(eventList[eventCount], "\n")] = '\0';
            eventCount++;
        }
    }
    fclose(eventPtr);

    if(eventCount == 0){
        printf("No events available for volunteers.\n");
        return;
    }

    printf("\nAvailable Events:\n");
    for(int i = 0; i < eventCount; i++){
        printf("%d. %s\n", i + 1, eventList[i]);
    }

    int choice;
    printf("Select event number to assign volunteer: ");
    scanf("%d", &choice);
    getchar();

    if(choice < 1 || choice > eventCount){
        printf("Invalid event selection.\n");
        return;
    }

    char selectedEvent[100];
    strcpy(selectedEvent, eventList[choice - 1]);

    char volunteerName[50], phone[20], task[200];
    printf("Enter Volunteer Name: ");
    fgets(volunteerName, sizeof(volunteerName), stdin);
    volunteerName[strcspn(volunteerName, "\n")] = '\0';

    printf("Enter Phone Number: ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = '\0';

    printf("Enter Volunteer Task: ");
    fgets(task, sizeof(task), stdin);
    task[strcspn(task, "\n")] = '\0';

    FILE *volunteerPtr = fopen("volunteer.txt", "a");
    if(volunteerPtr == NULL){
        printf("Error opening volunteer file!\n");
        return;
    }
    fprintf(volunteerPtr, "Event Title: %s\n", selectedEvent);
    fprintf(volunteerPtr, "Volunteer Name: %s\n", volunteerName);
    fprintf(volunteerPtr, "Phone: %s\n", phone);
    fprintf(volunteerPtr, "Task: %s\n", task);
    fprintf(volunteerPtr, "-----------------------------\n\n");
    fclose(volunteerPtr);

    printf("\n--- Volunteer Registered Successfully for '%s' ---\n", selectedEvent);
}

char loggedInEmail[50] = "";
int loginUser(){
    printf("---Login---\n");
    char email[50], password[30];

    printf("Enter Email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    FILE *file = fopen("users.txt", "r");
    if(file == NULL){
        printf("No registered users found.\n");
        registerUser();
    }

    char line[256];
    char storedEmail[50] = "";
    char storedPass[30] = "";
    char storedRole[20] = "";
    int found = 0;

    while(fgets(line, sizeof(line), file)){
        if(strncmp(line, "Email: ", 7) == 0){
            strcpy(storedEmail, line + 7);
            storedEmail[strcspn(storedEmail, "\n")] = '\0';
        }
        else if(strncmp(line, "Password: ", 10) == 0){
            strcpy(storedPass, line + 10);
            storedPass[strcspn(storedPass, "\n")] = '\0';
        }
        else if(strncmp(line, "Role: ", 6) == 0){
            strcpy(storedRole, line + 6);
            storedRole[strcspn(storedRole, "\n")] = '\0';
        }

        if(strcmp(email, storedEmail) == 0 && strcmp(password, storedPass) == 0){
            found = 1;
            break;
        }
    
    }
    storedEmail[0] = '\0';
    storedPass[0] = '\0';

    fclose(file);

    if(found){
        printf("Login successful!\n");
        strcpy(loggedInEmail, email);
        if(strcmp(storedRole, "Organizer") == 0){
            organizer();
        } else if(strcmp(storedRole, "Participant") == 0){
            participant();
        }
        return 1;
    } else {
        printf("Invalid email or password. Login failed.\n");
        return 0;
    }
}

void dashboard(){
    char line[256];
    char storedName[50] = "";
    char storedRole[20] = "";
    char storedEmail[50] = "";
    char storedPhone[20] = "";

    FILE *userFile = fopen("users.txt", "r");
    if(userFile == NULL){
        printf("User data file not found.\n");
        return;
    }

    char tempName[50], tempRole[20], tempEmail[50], tempPhone[20];
    while(fgets(line, sizeof(line), userFile)){
        if(strncmp(line, "Name: ", 6) == 0) {
            strcpy(tempName, line + 6);
            tempName[strcspn(tempName, "\n")] = '\0';
        } else if(strncmp(line, "Role: ", 6) == 0){
            strcpy(tempRole, line + 6);
            tempRole[strcspn(tempRole, "\n")] = '\0';
        } else if(strncmp(line, "Email: ", 7) == 0){
            strcpy(tempEmail, line + 7);
            tempEmail[strcspn(tempEmail, "\n")] = '\0';
        } else if(strncmp(line, "Phone: ", 7) == 0){
            strcpy(tempPhone, line + 7);
            tempPhone[strcspn(tempPhone, "\n")] = '\0';

            if(strcmp(tempEmail, loggedInEmail) == 0){
                strcpy(storedName, tempName);
                strcpy(storedRole, tempRole);
                strcpy(storedEmail, tempEmail);
                strcpy(storedPhone, tempPhone);
                break;
            }
        }
    }
    fclose(userFile);

    printf("\n--- User Dashboard ---\n");
    printf("Name : %s\n", storedName);
    printf("Role : %s\n", storedRole);
    printf("Email: %s\n", storedEmail);
    printf("Phone: %s\n", storedPhone);

    FILE *participantFile = fopen("participant.txt", "r");
    if(participantFile == NULL){
        printf("No participant data found.\n");
        return;
    }

    printf("\n--- Registered Events ---\n");
    int registeredCount = 0;
    char eventTitle[100] = "";
    char email[50] = "";

    while(fgets(line, sizeof(line), participantFile)){
        if(strncmp(line, "Event Title: ", 13) == 0){
            strcpy(eventTitle, line + 13);
            eventTitle[strcspn(eventTitle, "\n")] = '\0';
        }
        else if(strncmp(line, "Email: ", 7) == 0){
            strcpy(email, line + 7);
            email[strcspn(email, "\n")] = '\0';

            if(strcmp(email, loggedInEmail) == 0){
                printf("Event: %s\n", eventTitle);
                registeredCount++;
            }
        }
    }
    fclose(participantFile);

    if(registeredCount == 0){
        printf("No registered events found.\n");
    } else{
        printf("Total registered events: %d\n", registeredCount);
    }
    
    FILE *attendanceFile = fopen("attendance.txt", "r");
    if(attendanceFile == NULL){
        printf("\nNo attendance data found.\n");
        return;
    }
    
    printf("\n--- Attended Events ---\n");
    int attendedCount = 0;
    char attEventTitle[100] = "";
    char attParticipantName[50] = "";
    char attParticipantEmail[50] = "";
    char attendanceStatus[20] = "";
    
while(fgets(line, sizeof(line), attendanceFile)){
    if(strncmp(line, "Event Title: ", 13) == 0){
        strcpy(attEventTitle, line + 13);
        attEventTitle[strcspn(attEventTitle, "\n")] = '\0';
    }
    else if(strncmp(line, "Email: ", 7) == 0){
        strcpy(attParticipantEmail, line + 7);
        attParticipantEmail[strcspn(attParticipantEmail, "\n")] = '\0';
    }
    else if(strncmp(line, "Attendance: ", 12) == 0){
        strcpy(attendanceStatus, line + 12);
        attendanceStatus[strcspn(attendanceStatus, "\n")] = '\0';

        if(strcmp(attParticipantEmail, loggedInEmail) == 0 && strcmp(attendanceStatus, "Present") == 0){
            printf("Event: %s\n", attEventTitle);
            attendedCount++;
        }
    }
}
    fclose(attendanceFile);
    
    if(attendedCount == 0){
        printf("No attended events found.\n");
    } else{
        printf("Total attended events: %d\n", attendedCount);
    }
}

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

    char cleanID[20];
    strcpy(cleanID, p.id);
    cleanID[strcspn(cleanID, "\n")] = '\0';

    fprintf(participantPtr, "Event Title: %s", p.eventTitle);
    fprintf(participantPtr, "Participant Name: %s", p.participantName);
    fprintf(participantPtr, "Student ID: %s", p.id);
    fprintf(participantPtr, "Email: %s", p.email);
    fprintf(participantPtr, "Seat Token: S-%s\n", cleanID);
    fprintf(participantPtr, "Food Token: F-%s\n", cleanID);
    fprintf(participantPtr, "---------------------------\n\n");
    
    printf("\n---Congratulations !! Registration completed successfully---\n");
    printf("Your Seat Token: S-%s\n", cleanID);
    printf("Your Food Token: F-%s\n", cleanID);
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
    int totalParticipant=0;
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
            if(status==1){
                totalParticipant++;
                fprintf(attendancePtr, "Attendance: Present\n");
            } else{
                fprintf(attendancePtr, "Attendance: Absent\n");
            }
            fprintf(attendancePtr, "-----------------------------\n\n");
        }
    }
    
    fclose(participantPtr);
    fclose(attendancePtr);
    printf("\n---Attendance marking completed successfully---\n");
    printf("total: %d", totalParticipant);
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
    char eventTitle[100];
    getchar();
    printf("\n--- Generate Report for Specific Event ---\n");
    printf("Enter Event Title: ");
    fgets(eventTitle, sizeof(eventTitle), stdin);
    eventTitle[strcspn(eventTitle, "\n")] = '\0';

    int totalRegistered = 0, totalAttended = 0;
    int eventFound = 0;

    FILE *participantPtr = fopen("participant.txt", "r");
    if(participantPtr == NULL){
        printf("No participant data found for report generation.\n");
        return;
    }

    char line[200];
    while(fgets(line, sizeof(line), participantPtr)){
        if(strncmp(line, "Event Title: ", 13) == 0){
            char title[100];
            strcpy(title, line + 13);
            title[strcspn(title, "\n")] = '\0';
            if(strcmp(title, eventTitle) == 0){
                totalRegistered++;
                eventFound = 1;
            }
        }
    }
    fclose(participantPtr);

    if(eventFound==0){
        printf("\n--- '%s' Event not found ---\n", eventTitle);
        return;
    }

    FILE *attendancePtr = fopen("attendance.txt", "r");
    if(attendancePtr == NULL){
        printf("No attendance data found for report generation.\n");
        return;
    }

    int isMatch = 0;
    while(fgets(line, sizeof(line), attendancePtr)){
        if(strncmp(line, "Event Title: ", 13) == 0){
            char title[100];
            strcpy(title, line + 13);
            title[strcspn(title, "\n")] = '\0';
            isMatch = (strcmp(title, eventTitle) == 0);
        }
        if(isMatch && strncmp(line, "Attendance: Present", 19) == 0){
            totalAttended++;
        }
    }
    fclose(attendancePtr);

    FILE *reportPtr = fopen("events_Report.txt", "a");
    if(reportPtr == NULL){
        printf("Error: Could not open eventReport.txt for writing.\n");
        return;
    }
    fprintf(reportPtr, "\n--- Report for Event: %s ---\n", eventTitle);
    fprintf(reportPtr, "Total Registered Participants: %d\n", totalRegistered);
    fprintf(reportPtr, "Total Attended Participants : %d\n", totalAttended);
    fprintf(reportPtr, "----------------------------------------\n");
    fclose(reportPtr);

    printf("\nReport generated successfully.\n");
}
void faq(){
    FILE *faqFile = fopen("faq.txt", "r");
    char line[256];
    if(faqFile == NULL){
        printf("FAQ file not found.\n");
        return;
    }
    printf("\n");
    while(fgets(line, sizeof(line), faqFile)){
        printf("%s", line);
    }
    fclose(faqFile);
}
void organizer(){
    printf("welcome as organizer\n");
    printf("Event Management System -(Organizer menu)\n");
    printf("1. Create Events\n");
    printf("2. View Events\n");
    printf("3. Update Events\n");
    printf("4. Delete Events\n");
    printf("5. Register Volunteer\n");
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
        case 5: registerVolunteer(); break;
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
    printf("4. Dashboard\n");
    printf("5. Help & FAQ\n");
    printf("6. Exit\n");
    printf("Choose an option: ");
    int option;
    scanf("%d", &option);
    switch(option){
        case 1: viewEvent(); break;
        case 2: registerParticipant(); break;
        case 3: submitFeedback(); break;
        case 4: dashboard(); break;
        case 5: faq(); break;
        case 6: exit(0); break;
        default: printf("Invalid Option\n");
    }
}
int main(){
    printf("Welcome to Event Management System (Ez_VENT)\n1. Registration\n2. Login\nEnter choice: ");
    int choice;
    scanf("%d", &choice);
    getchar();
    switch (choice){
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
            break;    
        default:
            printf("Invalid option\n");
            break;
    }
}