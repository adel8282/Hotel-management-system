#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define MAX_LENGTH 1000
#define LENGTH 100

void mainMenu();
void login();
void forgotPassword();

//admin
void administrator();
void register_new_user();
void update_user();
void delete_user();
void view_user_status();
void rooms_management();
void view_rooms();
void add_room();
void update_room();
void remove_room();

//staff
void staffMenu();
void manageRoomReservation();
void makeReservation();
void updateReservation();
void viewReservation();
void cancelReservation();
void checkInOut();
void checkIn();
void checkOut();
void viewRoom();
void RoomAvailability();
void bookingHistory();

//customer
void customerMenu();
void Search_available();
void Make_and_cancel_reservation();
void makeReservationCustomer();
void cancelReservationCustomer();
void View_history_and_current_bookings();
void viewHistory();
void currentBookings();


//guest
void guestSection();
void viewRoomAvailability();
void ViewRoomDetails();


int main()
{
    system("clear");
    mainMenu();
}

void login()
{
    char inputUsername[LENGTH], inputPassword[LENGTH];
    char storedUsername[LENGTH], storedPassword[LENGTH];
    char buffer[MAX_LENGTH];
    int loginSuccessful = 0, attempts = 0;

    printf("╔═════════╗\n");
    printf("║ Login ║\n");
    printf("╚═════════╝\n");

    while(attempts < 3)
    {
        attempts++;

        printf("Enter your username: ");
        scanf("%s", inputUsername);

        printf("Enter your password: ");
        scanf("%s", inputPassword);

        FILE*staff;
        staff = fopen("staff.txt", "r");
        if(staff == NULL)
        {
            printf("Error opening staff.txt\n");
            continue;
        }

        // Staff
        while(fgets(buffer, MAX_LENGTH, staff))
        {
            sscanf(buffer, "%[^,], %*[^,], %*[^,], %s", storedUsername, storedPassword);
            if(strcmp(inputUsername, storedUsername) == 0 && strcmp(inputPassword, storedPassword) == 0)
            {
                system("clear");
                staffMenu();
                loginSuccessful = 1;
                break;
            }
        }
        fclose(staff);
         
        // Customer
        if(loginSuccessful == 0)
        {
            FILE*customer;
            customer = fopen("customer.txt", "r");
            if(customer == NULL)
            {
                printf("Error opening customer.txt\n");
                continue;
            }

            while(fgets(buffer, MAX_LENGTH, customer))
            {
                sscanf(buffer, "%[^,], %*[^,], %*[^,], %s", storedUsername, storedPassword);
                if(strcmp(inputUsername, storedUsername) == 0 && strcmp(inputPassword, storedPassword) == 0)
                {
                    system("clear");
                    customerMenu();
                    loginSuccessful = 1;
                    break;
                }
            }
            fclose(customer);
        }


        // Admin
        if(loginSuccessful == 0)
        {
            FILE*admin;
            admin = fopen("admin.txt", "r");
            if(admin == NULL)
            {
                printf("Error opening admin.txt\n");
                continue;
            }

            while(fgets(buffer, MAX_LENGTH, admin))
            {
                sscanf(buffer, "%[^,], %*[^,], %*[^,], %s", storedUsername, storedPassword);
                if(strcmp(inputUsername, storedUsername) == 0 && strcmp(inputPassword, storedPassword) == 0)
                {
                    system("clear");
                    administrator();
                    loginSuccessful = 1;
                    break;
                }
            }
            fclose(admin);
        }

        if(loginSuccessful == 1)
        {
            break;
        }

        if(attempts < 3)
        {
            system("clear");
            printf("Login failed. Please check your username and password and try again\n");
        }
    }

    if(loginSuccessful == 0)
    {
        system("clear");
        printf("We noticed several unsuccessful login attempts. Please click the 'FORGOT PASSWORD' option\n");
        mainMenu();
    }
    
}

void forgotPassword()
{
    char inputAge[LENGTH], inputGmail[LENGTH], buffer[MAX_LENGTH];
    char storedAge[LENGTH], storedGmail[LENGTH], storedUsername[LENGTH], storedPassword[LENGTH];
    int found = 0;

    printf("Enter your gmail: ");
    scanf("%s", inputGmail);

    printf("Enter your age: ");
    scanf("%s", inputAge);

    FILE* staff = fopen("staff.txt", "r");
    if(!staff)
    {
        printf("Error opening the file\n");
    }
    while(fgets(buffer, MAX_LENGTH, staff))
    {
        sscanf(buffer, "%[^,], %[^,], %[^,], %s", storedUsername, storedAge, storedGmail, storedPassword);
        if(strcmp(inputAge, storedAge) == 0 && strcmp(inputGmail, storedGmail) == 0)
        {
            found = 1;
            system("clear");
            printf("Username: %s\n", storedUsername);
            printf("Password: %s\n", storedPassword);
            mainMenu();
        }   
    }

    if(!found)
    {
        FILE* customer = fopen("customer.txt", "r");
        if(!customer)
        {
            printf("Error opening the file\n");
        }
        while(fgets(buffer, MAX_LENGTH, customer))
        {
            sscanf(buffer, "%[^,], %[^,], %[^,], %s", storedUsername, storedAge, storedGmail, storedPassword);
            if(strcmp(inputAge, storedAge) == 0 && strcmp(inputGmail, storedGmail) == 0)
            {
                found = 1;
                system("clear");
                printf("Username: %s\n", storedUsername);
                printf("Password: %s\n", storedPassword);
                mainMenu();
            }   
        }
    }

    if(!found)
    {
        FILE* admin = fopen("admin.txt", "r");
        if(!admin)
        {
            printf("Error opening the file\n");
        }
        while(fgets(buffer, MAX_LENGTH, admin))
        {
            sscanf(buffer, "%[^,], %[^,], %[^,], %s", storedUsername, storedAge, storedGmail, storedPassword);
            if(strcmp(inputAge, storedAge) == 0 && strcmp(inputGmail, storedGmail) == 0)
            {
                found = 1;
                system("clear");
                printf("Username: %s\n", storedUsername);
                printf("Password: %s\n", storedPassword);
                mainMenu();
            }   
        }
    }

    if(!found)
    {
        system("clear");
        printf("User can't be found\n");
        mainMenu();
    }
}

void mainMenu()
{
    int choice;
    
    printf("-------------------------\n");
    printf("Welcome to Hotel Management System\n");
    printf("-------------------------\n");
    printf("1. LOGIN\n");
    printf("2. JOIN AS GUEST\n");
    printf("3. FORGOT PASSWORD\n");
    printf("0. EXIST\n");
    printf("-------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if(choice == 1)
    {
        system("clear");
        login();
    }
    else if(choice == 2)
    {
        system("clear");
        guestSection();
    }
    else if(choice == 3)
    {
        system("clear");
        forgotPassword();
    }
    else if(choice == 0)
    {
        system("clear");
        printf("Exiting...\n");
        exit(0);
    }
    else
    {
        system("clear");
        printf("please enter an integer number between 1 to 3:\n ");
        mainMenu();
    }
}




//Admin
void administrator() {
    int choice;

    do {
        // Display menu options
        printf("===================================\n");
        printf("   Welcome to Administrator menu\n");
        printf("===================================\n");
        printf("[1] Register new user\n");
        printf("[2] Update user\n");
        printf("[3] View All User Status\n"); // New option
        printf("[4] Delete User\n");
        printf("[5] Rooms Management\n");
        printf("[0] Log out\n");
        printf("==================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Perform actions based on user choice
        switch (choice) {
            case 1:
                system("clear");
                register_new_user();
                break;
            case 2:
                system("clear");
                update_user();
                break;
            case 3:
                system("clear");
                view_user_status(); // Call the new function
                break;
            case 4:
                system("clear");
                delete_user();
                break;
            case 5:
                system("clear");
                rooms_management();
                break;
            case 0:
                system("clear");
                printf("Loging out....\n");
                mainMenu();
                break;
            default:
                system("clear");
                printf("Invalid choice. Please enter a number between 0 and 5.\n");
                break;
        }

    } while (choice != 0);
}

void register_new_user() {
    char name[100], email[100], password[100];
    int age, user_type;
    FILE *file;

    printf("Register as:\n");
    printf("1. Customer\n");
    printf("2. Staff\n");
    printf("Enter your choice: ");
    scanf("%d", &user_type);

    printf("Enter name: ");
    scanf(" %99[^\n]", name);
    printf("Enter age: ");
    scanf("%d", &age);
    printf("Enter email: ");
    scanf(" %99[^\n]", email);
    printf("Create password: ");
    scanf(" %99[^\n]", password);

    if (user_type == 1)
        file = fopen("customer.txt", "a");
    else if (user_type == 2)
        file = fopen("staff.txt", "a");
    else {
        system("clear");
        printf("Invalid choice. Please choose either 1 for Customer or 2 for Staff.\n");
        return;
    }

    if (file == NULL) {
        system("clear");
        printf("Error opening file! Registration could not be completed.\n");
        return;
    }

    system("clear");
    fprintf(file, "%s,%d,%s,%s\n", name, age, email, password);
    printf(user_type == 1 ? "Customer (%s) registered successfully!!\n" : "Staff (%s) registered successfully!!\n", name);

    fclose(file);
}

void update_user() 
{
    char name[100], new_email[100], new_password[100];
    int new_age, user_type;
    char line[256];
    int found = 0;

    printf("Update user for:\n");
    printf("1. Customer\n");
    printf("2. Staff\n");
    printf("Enter your choice: ");
    scanf("%d", &user_type);

    printf("Enter name of the user to update: ");
    scanf(" %99[^\n]", name);

    FILE *file, *temp_file;
    file = user_type == 1 ? fopen("customer.txt", "r") : fopen("staff.txt", "r");
    temp_file = user_type == 1 ? fopen("temp_customer.txt", "w") : fopen("temp_staff.txt", "w");

    if (file == NULL || temp_file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        char current_name[100], email[100], password[100];
        int age;
        sscanf(line, "%99[^,],%d,%99[^,],%99[^\n]", current_name, &age, email, password);

        if (strcmp(current_name, name) == 0) {
            found = 1;
            int update_choice = 0;

            while (update_choice != -1) 
            {
                printf("User found:\n");
                printf("Name: %s\n", current_name);
                printf("Age: %d\n", age);
                printf("Email: %s\n", email);
                printf("Password: %s\n", password);

                printf("\nWhat do you want to update?\n");
                printf("1. Name\n");
                printf("2. Age\n");
                printf("3. Email\n");
                printf("4. Password\n");
                printf("Enter your choice (enter -1 to stop updating): ");
                scanf("%d", &update_choice);

                switch (update_choice) {
                    case 1:
                        printf("Enter new name: ");
                        scanf(" %99[^\n]", current_name); // Update the name
                        break;
                    case 2:
                        printf("Enter new age: ");
                        scanf("%d", &new_age); // Update the age
                        age = new_age;
                        break;
                    case 3:
                        printf("Enter new email: ");
                        scanf(" %99[^\n]", new_email); // Update the email
                        strcpy(email, new_email);
                        break;
                    case 4:
                        printf("Enter new password: ");
                        scanf(" %99[^\n]", new_password); // Update the password
                        strcpy(password, new_password);
                        break;
                    case -1:
                        break;
                    default:
                        printf("Invalid choice.\n");
                        break;
                }

                if (update_choice != -1) 
                {
                    system("clear");
                    printf("User (%s) updated successfully!!\n", current_name);
                }
            }
            system("clear");

            // Write the updated record to the temporary file
            fprintf(temp_file, "%s,%d,%s,%s\n", current_name, age, email, password);
        } else {
            // Write unchanged record to the temporary file
            fprintf(temp_file, "%s,%d,%s,%s\n", current_name, age, email, password);
        }
    }

    fclose(file);
    fclose(temp_file);

    if (found) {
        remove(user_type == 1 ? "customer.txt" : "staff.txt");
        rename(user_type == 1 ? "temp_customer.txt" : "temp_staff.txt", user_type == 1 ? "customer.txt" : "staff.txt");
    } else {
        remove(user_type == 1 ? "temp_customer.txt" : "temp_staff.txt");
    }

    if (!found) 
    {
        system("clear");
        printf("User (%s) not found in the register.\n", name);
    }
}

void view_user_status() {
    int user_type;
    char line[256];

    printf("View user status for:\n");
    printf("1. Customer\n");
    printf("2. Staff\n");
    printf("Enter your choice: ");
    scanf("%d", &user_type);

    FILE *file;
    file = user_type == 1 ? fopen("customer.txt", "r") : fopen("staff.txt", "r");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n%s List:\n", user_type == 1 ? "Customer" : "Staff");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

void delete_user() {
    char name[100];
    int user_type;
    char line[256];
    int found = 0;

    printf("Delete user for:\n");
    printf("1. Customer\n");
    printf("2. Staff\n");
    printf("Enter your choice: ");
    scanf("%d", &user_type);

    printf("Enter name of the user to delete: ");
    scanf(" %99[^\n]", name);

    FILE *file, *temp_file;
    file = user_type == 1 ? fopen("customer.txt", "r") : fopen("staff.txt", "r");
    temp_file = user_type == 1 ? fopen("temp_customer.txt", "w") : fopen("temp_staff.txt", "w");

    if (file == NULL || temp_file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        char current_name[100], email[100], password[100];
        int age;
        sscanf(line, "%99[^,],%d,%99[^,],%99[^\n]", current_name, &age, email, password);

        if (strcmp(current_name, name) == 0) {
            found = 1;
            system("clear");
            printf("User (%s) deleted successfully!!\n", current_name);
        } else {
            // Write unchanged record to the temporary file
            fprintf(temp_file, "%s,%d,%s,%s\n", current_name, age, email, password);
        }
    }

    fclose(file);
    fclose(temp_file);

    if (found) {
        remove(user_type == 1 ? "customer.txt" : "staff.txt");
        rename(user_type == 1 ? "temp_customer.txt" : "temp_staff.txt", user_type == 1 ? "customer.txt" : "staff.txt");
    } else {
        remove(user_type == 1 ? "temp_customer.txt" : "temp_staff.txt");
    }

    if (!found) 
    {
        system("clear");
        printf("User (%s) not found in the register.\n", name);
    }
}

void rooms_management() {
    int choice;

    do {
        printf("\nRooms Status Menu:\n");
        printf("1. View how many rooms added based on the type \n");
        printf("2. Add room\n");
        printf("3. Update room\n");
        printf("4. Remove room\n");
        printf("0. Return to Administrator menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                view_rooms();
                break;
            case 2:
                add_room();
                break;
            case 3:
                update_room();
                break;
            case 4:
                remove_room();
                break;
            case 0:
                return;
            default:
                printf("Invalid choice. Please enter a number between 0 and 4.\n");
                break;
        }

    } while (choice != 0);
}

void view_rooms() {
    FILE *file;
    char line[256], search_room_type[100];
    int count = 0;

    file = fopen("room_status.txt", "r");
    if (file == NULL) {
        printf("Error opening file! Unable to view rooms.\n");
        return;
    }

    printf("Room type options:\n");
    printf("1. Single room with balcony (mall view)\n");
    printf("2. Single room without balcony (mall view)\n");
    printf("3. Single room without balcony (sea view)\n");
    printf("4. Double room (sea view)\n");
    printf("5. Private villa (sea view)\n");
    printf("Choose room type to check num of added rooms from this type: ");

    int room_type_choice;
    scanf("%d", &room_type_choice);

    switch (room_type_choice) {
        case 1:
            strcpy(search_room_type, "Single room with balcony (mall view)");
            break;
        case 2:
            strcpy(search_room_type, "Single room without balcony (mall view)");
            break;
        case 3:
            strcpy(search_room_type, "Single room without balcony (sea view)");
            break;
        case 4:
            strcpy(search_room_type, "Double room (sea view)");
            break;
        case 5:
            strcpy(search_room_type, "Private villa (sea view)");
            break;
        default:
            printf("Invalid room type choice.\n");
            fclose(file);
            return;
    }

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, search_room_type) != NULL) {
            count++;
        }
    }

    fclose(file);

    printf("The number of rooms from type: '%s' is: %d\n", search_room_type, count);
}

void add_room() {
    char room_number[100], room_type[100], persons_allowed[100];
    int original_price;
    FILE *file;
    int room_type_choice;

    printf("Adding room section\n");
    printf("Add room number: ");
    scanf(" %99[^\n]", room_number);

    printf("Add room type:\n");
    printf("1. Single room with balcony (mall view)\n");
    printf("2. Single room without balcony (mall view)\n");
    printf("3. Single room without balcony (sea view)\n");
    printf("4. Double room (sea view)\n");
    printf("5. Private villa (sea view)\n");
    printf("Enter your choice: ");
    scanf("%d", &room_type_choice);

    switch (room_type_choice) {
        case 1:
            strcpy(room_type, "Single room with balcony (mall view)");
            strcpy(persons_allowed, "1-2 persons");
            original_price = 550;
            break;
        case 2:
            strcpy(room_type, "Single room without balcony (mall view)");
            strcpy(persons_allowed, "1-2 persons");
            original_price = 500;
            break;
        case 3:
            strcpy(room_type, "Single room without balcony (sea view)");
            strcpy(persons_allowed, "1-2 persons");
            original_price = 700;
            break;
        case 4:
            strcpy(room_type, "Double room (sea view)");
            strcpy(persons_allowed, "3-4 persons");
            original_price = 1000;
            break;
        case 5:
            strcpy(room_type, "Private villa (sea view)");
            strcpy(persons_allowed, "5-6 persons");
            original_price = 4000;
            break;
        default:
            printf("Invalid room type choice.\n");
            return;
    }

    file = fopen("room_status.txt", "a");
    if (file == NULL) {
        printf("Error opening file! Room addition could not be completed.\n");
    } else {
        fprintf(file, "%s,%s,%s,%d,Available\n",
                room_number, room_type, persons_allowed, original_price);
        printf("Room (%s) added successfully!!\n", room_type);
        fclose(file);
    }
}

void update_room() {
    char room_number[100], new_room_number[100], room_type[100], persons_allowed[100];
    int original_price, room_type_choice;
    char status[100], line[512];
    int found = 0, change_room_number_choice;

    printf("Updating room\n");
    printf("Enter the number of the room that you want to change: ");
    scanf(" %99[^\n]", room_number);

    FILE *file, *temp_file;
    file = fopen("room_status.txt", "r");
    temp_file = fopen("temp_room_status.txt", "w");

    if (file == NULL || temp_file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        char current_room_number[100];
        sscanf(line, "%99[^,]", current_room_number);

        if (strcmp(current_room_number, room_number) == 0) {
            found = 1;
            printf("Do you want to change the room number? (1 for Yes, 2 for No): ");
            scanf("%d", &change_room_number_choice);

            if (change_room_number_choice == 1) {
                printf("Enter new room number: ");
                scanf(" %99[^\n]", new_room_number);
            } else {
                strcpy(new_room_number, room_number);
            }

            printf("Change room type:\n");
            printf("1. Single room with balcony (mall view)\n");
            printf("2. Single room without balcony (mall view)\n");
            printf("3. Single room without balcony (sea view)\n");
            printf("4. Double room (sea view)\n");
            printf("5. Private villa (sea view)\n");
            printf("Enter your choice: ");
            scanf("%d", &room_type_choice);

            switch (room_type_choice) {
                case 1:
                    strcpy(room_type, "Single room with balcony (mall view)");
                    strcpy(persons_allowed, "1-2 persons");
                    original_price = 550;
                    break;
                case 2:
                    strcpy(room_type, "Single room without balcony (mall view)");
                    strcpy(persons_allowed, "1-2 persons");
                    original_price = 500;
                    break;
                case 3:
                    strcpy(room_type, "Single room without balcony (sea view)");
                    strcpy(persons_allowed, "1-2 persons");
                    original_price = 700;
                    break;
                case 4:
                    strcpy(room_type, "Double room (sea view)");
                    strcpy(persons_allowed, "3-4 persons");
                    original_price = 1000;
                    break;
                case 5:
                    strcpy(room_type, "Private villa (sea view)");
                    strcpy(persons_allowed, "5-6 persons");
                    original_price = 4000;
                    break;
                default:
                    printf("Invalid room type choice.\n");
                    fclose(file);
                    fclose(temp_file);
                    return;
            }

            fprintf(temp_file, "%s,%s,%s,%d,%s\n",
                    new_room_number, room_type, persons_allowed, original_price, "Available");
        } else {
            fputs(line, temp_file);
        }
    }

    fclose(file);
    fclose(temp_file);

    remove("room_status.txt");
    rename("temp_room_status.txt", "room_status.txt");

    if (found) {
        printf("Room (%s) updated successfully!!\n", room_number);
    } else {
        printf("Room number %s not found.\n", room_number);
    }
}

void remove_room() {
    char room_number[100], line[512];
    FILE *file, *temp_file;
    int found = 0;

    printf("Removing room\n");
    printf("Enter the number of the room that you want to remove: ");
    scanf(" %99[^\n]", room_number);

    file = fopen("room_status.txt", "r");
    temp_file = fopen("temp_room_status.txt", "w");

    if (file == NULL || temp_file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        char current_room_number[100];
        sscanf(line, "%99[^,]", current_room_number);

        if (strcmp(current_room_number, room_number) != 0) {
            fputs(line, temp_file);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp_file);

    remove("room_status.txt");
    rename("temp_room_status.txt", "room_status.txt");

    if (found) 
    {
        system("clear");
        printf("Room number %s removed successfully!!\n", room_number);
    } else 
    {
        system("clear");
        printf("Room number %s not found.\n", room_number);
    }
}





//Staff
struct staff 
{
    char username[LENGTH];
    char password[LENGTH];
    char gmail[LENGTH];
    char age[LENGTH];
    char guestId[LENGTH];
    char guestName[LENGTH];
    char roomNumber[LENGTH];
    char roomType[LENGTH];
    char maxPerson[LENGTH];
    int  price;
    char roomStatus[LENGTH];
    char reservationDate[LENGTH];
    char newRoomNumber[LENGTH];
    char newRoomType[LENGTH];
    char newReservationDate[LENGTH];
};

void staffMenu()
{
    int choice;
    
    printf("=======================\n");
    printf("   Hotel Staff Menu\n");
    printf("=======================\n");
    printf("[1] Manage Reservation\n");
    printf("[2] Check-In and Check-Out Guests\n");
    printf("[3] View Room Availability And Booking History\n");
    printf("[0] Logout\n");
    printf("=======================\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            system("clear");
            manageRoomReservation();
            break;
        case 2:
            system("clear");
            checkInOut();
            break;
        case 3:
            system("clear");
            viewRoom();
            break;
        case 0:
            system("clear");
            printf("Logging out...\n");
            mainMenu();
            break;
        default:
            system("clear");
            printf("Invalid choice. Please enter a number between 1 and 3.\n");
            staffMenu();
            break;
    }
}

void manageRoomReservation()
{
    int choice;

    printf("=============================\n");
    printf("Reservation Management Menu\n");
    printf("=============================\n");
    printf("[1] Make Reservation\n");
    printf("[2] Update Reservation\n");
    printf("[3] View Reservation\n");
    printf("[4] Cancel Reservation\n");
    printf("[0] Return to staff menu\n");
    printf("=============================\n");
    printf("Enter your choice(1-4): ");
    scanf("%d", &choice);

    switch (choice) 
    {
        case 1:
            system("clear");
            makeReservation();
            break;
        case 2:
            system("clear");
            updateReservation();
            break;
        case 3:
            system("clear");
            viewReservation();
            break;
        case 4:
            system("clear");
            cancelReservation();
            break;
        case 0:
            system("clear");
            printf("Returning to staff menu...\n");
            staffMenu();
            break;
        default:
            system("clear");
            printf("Invalid choice. Please enter a number between 1 and 4.\n");
            manageRoomReservation();
            break;
        }
}

void makeReservation() 
{
    struct staff input, stored;
    char buffer[MAX_LENGTH], buffer2[MAX_LENGTH];
    int roomChoice, find1 = 0, find2 = 1, validChoice = 0;

    printf("Enter guest's name: ");
    scanf("%s", input.guestName);

    FILE *guestFile = fopen("reservation.txt", "r");
    if (!guestFile) 
    {
        printf("Error opening the file");
        return;
    }

    int maxId = 0;
    while (fgets(buffer, MAX_LENGTH, guestFile)) 
    {
        int id;
        sscanf(buffer, "%d,%*s", &id);
        if (id > maxId) {
            maxId = id;
        }
    }
    fclose(guestFile);

    int nextId = maxId + 1;
    sprintf(input.guestId, "%d", nextId);

    while (validChoice == 0) 
    {
        printf("Room types:\n");
        printf("1. Single room with balcony (mall view)\n");
        printf("2. Single room without balcony (mall view)\n");
        printf("3. Single room without balcony (sea view)\n");
        printf("4. Double room (sea view)\n");
        printf("5. Private villa (sea view)\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &roomChoice);

        switch (roomChoice) 
        {
            case 1:
                strcpy(input.roomType, "Single room with balcony (mall view)");
                validChoice = 1;
                break;
            case 2:
                strcpy(input.roomType, "Single room without balcony (mall view)");
                validChoice = 1;
                break;
            case 3:
                strcpy(input.roomType, "Single room without balcony (sea view)");
                validChoice = 1;
                break;
            case 4:
                strcpy(input.roomType, "Double room (sea view)");
                validChoice = 1;
                break;
            case 5:
                strcpy(input.roomType, "Private villa (sea view)");
                validChoice = 1;
                break;
            default:
                system("clear");
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    }

    printf("Enter room number: ");
    scanf("%s", input.roomNumber);

    printf("Enter reservation date (YYYY-MM-DD): ");
    scanf("%s", input.reservationDate);

    time_t t = time(NULL);
    struct tm currentDate = *localtime(&t);

    int inputYear, inputMonth, inputDay;
    sscanf(input.reservationDate, "%d-%d-%d", &inputYear, &inputMonth, &inputDay);

    if (inputYear < (currentDate.tm_year + 1900) ||
       (inputYear == (currentDate.tm_year + 1900) && inputMonth < (currentDate.tm_mon + 1)) ||
       (inputYear == (currentDate.tm_year + 1900) && inputMonth == (currentDate.tm_mon + 1) && inputDay < currentDate.tm_mday)) 
    {
        system("clear");
        printf("Invalid reservation date. The reservation date cannot be before the current date or in an incorrect format (YY-MM-DD). \nMake a new reservation with valid date\n");
        manageRoomReservation();
    }

    FILE *room = fopen("room_status.txt", "r");
    guestFile = fopen("reservation.txt", "r");

    if (!room || !guestFile) 
    {
        printf("Error opening the file");
        return;
    }

    //Check if the room exist
    while (fgets(buffer, MAX_LENGTH, room)) 
    {
        sscanf(buffer, "%[^,], %[^,], %*[^,], %d, %*s", stored.roomNumber, stored.roomType, &stored.price);
        if (strcmp(stored.roomType, input.roomType) == 0 && strcmp(stored.roomNumber, input.roomNumber) == 0) {
            find1 = 1;
            break;
        }
    }

    //Check if the room available 
    while (fgets(buffer2, MAX_LENGTH, guestFile)) 
    {
        sscanf(buffer2, "%*[^,], %*[^,], %[^,], %*[^,], %[^,], %*[^,]", stored.roomNumber, stored.reservationDate);
        if (strcmp(stored.roomNumber, input.roomNumber) == 0 && strcmp(stored.reservationDate, input.reservationDate) == 0) 
        {
            find2 = 0;
            break;
        }
    }

    fclose(room);
    fclose(guestFile);

    //save the reservation
    if (find1 && find2) 
    {
        guestFile = fopen("reservation.txt", "a");
        if (!guestFile) 
        {
            printf("Error opening the file");
            return;
        }
        fprintf(guestFile, "%s,%s,%s,%s,%s,%d\n", input.guestId, input.guestName, input.roomNumber, input.roomType, input.reservationDate, stored.price);
        fclose(guestFile);
        system("clear");
        printf("\nReservation for %s has been successfully made. Please inform the guest about their booking details.\n", input.guestName);
    } 
    else 
    {
        system("clear");
        printf("No available rooms of the selected type.\n");
    }

    manageRoomReservation();
}

void updateReservation() 
{
    struct staff input, stored;
    int guestFound = 0, reservationFound = 1, roomFound = 0, invalidChoice = 1, choice;
    char buffer[MAX_LENGTH];

    printf("Enter guest's ID: ");
    scanf("%s", input.guestId);

    printf("Enter room number: ");
    scanf("%s", input.roomNumber);

    printf("Enter reservation date (YYYY-MM-DD): ");
    scanf("%s", input.reservationDate);

    printf("\n");
    printf("Enter the new room number: ");
    scanf("%s", input.newRoomNumber);

    printf("Enter the new reservation date (YYYY-MM-DD): ");
    scanf("%s", input.newReservationDate);

    while (invalidChoice) 
    {
        printf("Select the new room type:\n");
        printf("1. Single room with balcony (mall view)\n");
        printf("2. Single room without balcony (mall view)\n");
        printf("3. Single room without balcony (sea view)\n");
        printf("4. Double room (sea view)\n");
        printf("5. Private villa (sea view)\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                strcpy(input.newRoomType, "Single room with balcony (mall view)");
                invalidChoice = 0;
                break;
            case 2:
                strcpy(input.newRoomType, "Single room without balcony (mall view)");
                invalidChoice = 0;
                break;
            case 3:
                strcpy(input.newRoomType, "Single room without balcony (sea view)");
                invalidChoice = 0;
                break;
            case 4:
                strcpy(input.newRoomType, "Double room (sea view)");
                invalidChoice = 0;
                break;
            case 5:
                strcpy(input.newRoomType, "Private villa (sea view)");
                invalidChoice = 0;
                break;
            default:
                system("clear");
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
                break;
        }
    }

    time_t t = time(NULL);
    struct tm currentDate = *localtime(&t);

    int inputYear, inputMonth, inputDay;
    sscanf(input.reservationDate, "%d-%d-%d", &inputYear, &inputMonth, &inputDay);

    if (inputYear < (currentDate.tm_year + 1900) ||
       (inputYear == (currentDate.tm_year + 1900) && inputMonth < (currentDate.tm_mon + 1)) ||
       (inputYear == (currentDate.tm_year + 1900) && inputMonth == (currentDate.tm_mon + 1) && inputDay < currentDate.tm_mday)) 
    {
        system("clear");
        printf("Invalid reservation date. The reservation date cannot be earlier than the current date or in an incorrect format (YY-MM-DD). Please update with a valid date.\n");
        manageRoomReservation();
    }

    FILE *guestFile = fopen("reservation.txt", "r+");
    FILE *roomFile = fopen("room_status.txt", "r");

    if (!guestFile || !roomFile) 
    {
        printf("Error opening the file\n");
    }

    //Check if the guest exist 
    while (fgets(buffer, MAX_LENGTH, guestFile)) 
    {
        sscanf(buffer, "%[^,], %[^,], %[^,], %[^,], %[^,], %*s", stored.guestId, stored.guestName, stored.roomNumber, stored.roomType, stored.reservationDate);
        if (strcmp(input.guestId, stored.guestId) == 0 && strcmp(input.roomNumber, stored.roomNumber) == 0 && strcmp(input.reservationDate, stored.reservationDate) == 0) 
        {
            guestFound = 1;
            break;
        }
    }

    if (!guestFound) 
    {
        system("clear");
        printf("Guest ID %s was not found associated with this reservation.\n", input.guestId);
        fclose(guestFile);
        fclose(roomFile);
        manageRoomReservation();
        return;
    }

     //Check if the reservation is available 
    rewind(guestFile);
    while (fgets(buffer, MAX_LENGTH, guestFile)) 
    {
        sscanf(buffer, "%*[^,], %*[^,], %[^,], %*[^,], %[^,], %*s", stored.roomNumber, stored.reservationDate);
        if (strcmp(stored.roomNumber, input.newRoomNumber) == 0 && strcmp(stored.reservationDate, input.newReservationDate) == 0) {
            reservationFound = 0;
            break;
        }
    }

    if (!reservationFound) 
    {
        system("clear");
        printf("The room number %s is already reserved for the date %s.\n", input.newRoomNumber, input.newReservationDate);
        fclose(guestFile);
        fclose(roomFile);
        manageRoomReservation();
    }

    while (fgets(buffer, MAX_LENGTH, roomFile)) 
    {
        sscanf(buffer, "%[^,], %[^,], %*[^,], %d, %*s", stored.roomNumber, stored.roomType, &stored.price);
        if (strcmp(stored.roomNumber, input.newRoomNumber) == 0 && strcmp(stored.roomType, input.newRoomType) == 0) 
        {
            roomFound = 1;
            break;
        }
    }

    if (!roomFound) 
    {
        system("clear");
        printf("No rooms were found with that number %s\n", input.newRoomNumber);
        fclose(guestFile);
        fclose(roomFile);
        manageRoomReservation();
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) 
    {
        printf("Error opening the temporary file\n");
        fclose(guestFile);
        fclose(roomFile);
        return;
    }

    rewind(guestFile);
    while (fgets(buffer, MAX_LENGTH, guestFile)) 
    {
        sscanf(buffer, "%[^,], %[^,], %[^,], %[^,], %[^,], %*s", stored.guestId, stored.guestName, stored.roomNumber, stored.roomType, stored.reservationDate);
        if (strcmp(stored.guestId, input.guestId) == 0 && strcmp(input.roomNumber, stored.roomNumber) == 0 && strcmp(input.reservationDate, stored.reservationDate) == 0) 
        {
            fprintf(tempFile, "%s,%s,%s,%s,%s,%d\n", stored.guestId, stored.guestName, input.newRoomNumber, input.newRoomType, input.newReservationDate, stored.price);
        } 
        else 
        {
            fprintf(tempFile, "%s", buffer);
        }
    }

    fclose(guestFile);
    fclose(tempFile);
    fclose(roomFile);

    remove("reservation.txt");
    rename("temp.txt", "reservation.txt");
    
    system("clear");
    printf("The reservation associated with Guest ID %s has been successfully updated.\n", input.guestId);
    manageRoomReservation();
}

void viewReservation()
{
    struct staff input, stored;
    char buffer[MAX_LENGTH];
    int found = 0, choice, validChoice = 0, i = 1;

    printf("Enter guest's name: ");
    scanf("%s", input.guestName);

    FILE* guest = fopen("reservation.txt", "r");
    if(!guest)
    {
        printf("Error opening the file\n");
    }

    while(fgets(buffer, MAX_LENGTH, guest))
    {
        sscanf(buffer, "%*[^,], %[^,], %[^,], %[^,], %[^,], %d", stored.guestName, stored.roomNumber, stored.roomType, stored.reservationDate, &stored.price);
        if (strcmp(input.guestName, stored.guestName) == 0)
        {
            printf("RESERVATION NUMBER: %d\n", i);
            printf("Room Number: %s\n", stored.roomNumber);
            printf("Room Type: %s\n", stored.roomType);
            printf("Reservation Date: %s\n", stored.reservationDate);
            printf("Price: %d", stored.price);
            i++;
            printf("\n\n");
            found = 1;
        }
    }

    if(!found)
    {
        system("clear");
        printf("%s was not found.\n", input.guestName);
        manageRoomReservation();
    }
    else
    {
        while (validChoice == 0)
        {
            printf("Would you like to view another reservation?\n");
            printf("[1] Yes\n");
            printf("[2] No(Go back)\n");
            printf("Enter your choice(1-2): ");
            scanf("%d", &choice);

            switch(choice)
            {
                case 1:
                    system("clear");
                    viewReservation();
                    validChoice = 1;
                    break;
                
                case 2:
                    system("clear");
                    manageRoomReservation();
                    validChoice = 1;
                    break;

                    default:
                    system("clear");
                    printf("Invalid choice. Please enter number 1 or 2.\n");
            }
        }
    }

}

void cancelReservation()
{
    struct staff input, stored;
    char buffer[MAX_LENGTH];
    int found = 0;

    printf("Enter guest's ID: ");
    scanf("%s", input.guestId);

    FILE* guest = fopen("reservation.txt", "r");
    FILE* temp = fopen("temp.txt", "w");

    while(fgets(buffer, MAX_LENGTH, guest))
    {
        sscanf(buffer, "%[^,], %*[^,], %*[^,], %*[^,], %*[^,], %*d", stored.guestId);
        if (strcmp(stored.guestId, input.guestId) == 0)
        {
            found = 1;
        }
        else
        {
            fputs(buffer, temp);
        }
    }
    fclose(guest);
    fclose(temp);

    remove("reservation.txt");
    rename("temp.txt", "reservation.txt");

    if(found)
    {
        system("clear");
        printf("The reservation for guest ID %s was canceled successfully.\n", input.guestId);
    }
    else
    {
        system("clear");
        printf("The reservation for guest ID %s was not found.\n", input.guestId);
    }

    manageRoomReservation();
}

void checkInOut()
{
    int choice;

    printf("=============================\n");
    printf("Check-In and check-Out Menu\n");
    printf("=============================\n");
    printf("[1] Check-In\n");
    printf("[2] Check-Out\n");
    printf("[0] Return to staff menu\n");
    printf("=============================\n");
    printf("Enter your choice(1-2): ");
    scanf("%d", &choice);

    switch (choice) 
    {
        case 1:
            system("clear");
            checkIn();
            break;
        case 2:
            system("clear");
            checkOut();
            break;
        case 0:
            system("clear");
            staffMenu();
        default:
            system("clear");
            printf("Invalid choice. Please enter number between 1 to 2.\n");
            checkInOut();
            break;
    }
}

void checkIn()
{
    struct staff input, stored;
    char buffer[MAX_LENGTH], buffer2[MAX_LENGTH];
    int found = 0;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char todayDate[11];
    sprintf(todayDate, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    printf("Enter guest's ID: ");
    scanf("%s", input.guestId);

    printf("Enter room number: ");
    scanf("%s", input.roomNumber);

    printf("Enter reservation date (YYYY-MM-DD): ");
    scanf("%s", input.reservationDate);

    FILE* guest = fopen("reservation.txt", "r");
    FILE* tempGuest = fopen("tempGuest.txt", "w");
    if(!guest || !tempGuest)
    {
        printf("Error opening the file");
    }

    //Check if reservation exist
    while(fgets(buffer, MAX_LENGTH, guest))
    {
        sscanf(buffer, "%[^,], %[^,], %[^,], %[^,], %[^,], %*[^,]", stored.guestId, stored.guestName, stored.roomNumber, stored.roomType, stored.reservationDate);
        if (strcmp(input.reservationDate, todayDate) == 0 && strcmp(stored.guestId, input.guestId) == 0 && strcmp(input.roomNumber, stored.roomNumber) == 0 && strcmp(input.reservationDate, stored.reservationDate) == 0)
        {
            FILE*checkIn = fopen("checkIn.txt", "a");
            fprintf(checkIn, "%s,%s,%s,%s,%s\n", stored.guestId, stored.guestName, stored.roomNumber, stored.roomType, stored.reservationDate);
            fclose(checkIn);
            found = 1;
        }
        else
        {
            fputs(buffer, tempGuest);
        }
    }

    fclose(guest);
    fclose(tempGuest);

    remove("reservation.txt");
    rename("tempGuest.txt", "reservation.txt");

    if(!found)
    {
        system("clear");
        printf("The system could not verify a reservation for the provided guest ID %s, room number %s, and room date %s. \nPlease double-check the information you provided and try again.\n", input.guestId, input.roomNumber, input.reservationDate);
        checkInOut();
    }
    else
    {
        FILE* room = fopen("room_status.txt", "r");
        FILE* tempRoom = fopen("tempRoom.txt", "w");
        if(!room || !tempRoom)
        {
            printf("Error opening the file");
        }

        while(fgets(buffer2, MAX_LENGTH, room))
        {
            strcpy(input.roomStatus, "Occupied");
            sscanf(buffer2, "%[^,], %[^,], %[^,], %d, %[^,]", stored.roomNumber, stored.roomType, stored.maxPerson, &stored.price, stored.roomStatus);
            if(strcmp(input.roomNumber, stored.roomNumber) == 0)
            {
                fprintf(tempRoom,"%s,%s,%s,%d,%s\n", stored.roomNumber, stored.roomType, stored.maxPerson, stored.price, input.roomStatus);
            }
            else
            {
                fputs(buffer2, tempRoom);
            }

        }

        fclose(room);
        fclose(tempRoom);

        remove("room_status.txt");
        rename("tempRoom.txt", "room_status.txt");

        system("clear");
        printf("Guest ID %s has checked in successfully.\n", input.guestId);
        checkInOut();
    }
}

void checkOut()
{
    struct staff input, stored;
    char buffer[MAX_LENGTH];
    int found = 0;

    printf("Enter guest's ID: ");
    scanf("%s", input.guestId);

    printf("Enter room number: ");
    scanf("%s", input.roomNumber);

    FILE* checkIn = fopen("checkIn.txt", "r");
    FILE* temp = fopen("temp.txt", "w");
    if(!checkIn || !temp)
    {
        printf("Error opening the file");
    }

    while(fgets(buffer, MAX_LENGTH, checkIn))
    {
        sscanf(buffer, "%[^,], %[^,], %[^,], %[^,], %[^,]", stored.guestId, stored.guestName, stored.roomNumber, stored.roomType, stored.reservationDate);
        if (strcmp(stored.guestId, input.guestId) == 0 && strcmp(input.roomNumber, stored.roomNumber) == 0)
        {
            FILE* history = fopen("bookingHistory.txt", "a");
            fprintf(history, "%s,%s,%s,%s,%s", stored.guestId, stored.guestName, stored.roomNumber, stored.roomType, stored.reservationDate);
            fclose(history);
            found = 1;
        }
        else
        {
            fputs(buffer, temp);
        }
    }

    fclose(checkIn);
    fclose(temp);

    remove("checkIn.txt");
    rename("temp.txt", "checkIn.txt");

    if(!found)
    {
        system("clear");
        printf("The reservation cannot be found for Guest ID %s associated with room number %s.\n", input.guestId, input.roomNumber);
        checkInOut();
    }
    else
    {
        FILE* room = fopen("room_status.txt", "r");
        FILE* tempRoom = fopen("tempRoom.txt", "w");
        if(!room || !tempRoom)
        {
            printf("Error opening the file");
        }

        while(fgets(buffer, MAX_LENGTH, room))
        {
            strcpy(input.roomStatus, "Available");
            sscanf(buffer, "%[^,], %[^,], %[^,], %d, %*[^,]", stored.roomNumber, stored.roomType, stored.maxPerson, &stored.price);
            if(strcmp(input.roomNumber, stored.roomNumber) == 0)
            {
                fprintf(tempRoom,"%s,%s,%s,%d,%s\n", stored.roomNumber, stored.roomType, stored.maxPerson, stored.price, input.roomStatus);
            }
            else
            {
                fputs(buffer, tempRoom);
            }

        }

        fclose(room);
        fclose(tempRoom);

        remove("room_status.txt");
        rename("tempRoom.txt", "room_status.txt");

        system("clear");
        printf("Guest ID %s has checked out successfully.\n", input.guestId);
        checkInOut();
    }

}

void viewRoom()
{
    int choice;

    printf("===========================================\n");
    printf("View Room Availability And Booking History\n");
    printf("===========================================\n");
    printf("[1] View Room Availability\n");
    printf("[2] View Booking History\n");
    printf("[0] Return to staff menu\n");
    printf("========================\n");
    printf("Enter your choice(1-2): ");
    scanf("%d", &choice);

    switch (choice) 
    {
        case 1:
            system("clear");
            RoomAvailability();
            break;
        case 2:
            system("clear");
            bookingHistory();
            break;
        case 0:
            system("clear");
            staffMenu();
        default:
            system("clear");
            printf("Invalid choice. Please enter number between 1 to 2.\n");
            viewRoom();
            break;
    }
}

void RoomAvailability()
{
    struct staff input, stored;
    char buffer[MAX_LENGTH];
    int found = 0, validChoice = 0, choice;


    FILE* room = fopen("room_status.txt", "r");
    if(!room)
    {
        printf("Error opening the file");
    }

    while(fgets(buffer, MAX_LENGTH, room))
    {
        sscanf(buffer, "%[^,], %[^,], %[^,], %d, %s", stored.roomNumber, stored.roomType, stored.maxPerson, &stored.price, stored.roomStatus);
        if(strcmp(stored.roomStatus, "Available") == 0)
        {
            found = 1;
            printf("Room Number: %s\n", stored.roomNumber);
            printf("Room Type: %s\n", stored.roomType);
            printf("Max Occupancy: %s\n", stored.maxPerson);
            printf("Price: %d\n", stored.price);
            printf("\n\n");
        }
    }
    fclose(room);

    if(found)
    {
        while(!validChoice)
        {
            printf("Press 1 to return: ");
            scanf("%d", &choice);
            switch (choice) 
            {
                case 1:
                    system("clear");
                    viewRoom();
                    break;
                default:
                    system("clear");
                    printf("Invalid choice. Please enter number 1.\n");
                    break;
                
            }
        }
    }
    else
    {
        system("clear");
        printf("There are no available rooms\n");
        viewRoom();
    }
}

void bookingHistory()
{
    struct staff input, stored;
    char buffer[MAX_LENGTH];
    int found = 0, validChoice = 0, choice, i = 1;

    printf("Enter guest's name: ");
    scanf("%s", input.guestName);

    FILE* history = fopen("bookingHistory.txt", "r");
    if(!history)
    {
        printf("Error opening the file");
    }

    while(fgets(buffer, MAX_LENGTH, history))
    {
        sscanf(buffer, "%*[^,], %[^,], %[^,], %[^,], %s",stored.guestName, stored.roomNumber, stored.roomType, stored.reservationDate);
        if(strcmp(stored.guestName, input.guestName) == 0)
        {
            found = 1;
            printf("Reservation number: %d\n", i);
            printf("Guest name: %s\n", stored.guestName);
            printf("Room number: %s\n", stored.roomNumber);
            printf("Room Type: %s\n", stored.roomType);
            printf("Date: %s\n", stored.reservationDate);
            printf("\n\n");
            i++;
        }
    }
    fclose(history);

    if(found)
    {
        while(!validChoice)
        {
            printf("Press 1 to return: ");
            scanf("%d", &choice);
            switch (choice) 
            {
                case 1:
                    system("clear");
                    viewRoom();
                    break;
                default:
                    system("clear");
                    printf("Invalid choice. Please enter number 1.\n");
                    break;
                
            }
        }
    }
    else
    {
        system("clear");
        printf("Guest can't be found\n");
        viewRoom();
    }
}





// Customer
void customerMenu()
{
    int choice;
 
    printf("=====================\n");
    printf("   Customer Menu\n");
    printf("=====================\n");
    printf("1. Search for available rooms\n");
    printf("2. Make and cancel reservation\n");
    printf("3. View reservation history and current bookings\n");
    printf("4. Logout\n");
    printf("=====================\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
 
    switch (choice) {
        case 1:
            system("clear");
            Search_available();
            break;
        case 2:
            system("clear");
            Make_and_cancel_reservation();
            break;
        case 3:
            system("clear");
            View_history_and_current_bookings();
            break;
        case 4:
            system("clear");
            mainMenu();
            break;
        default:
            system("clear");
            puts("Invalid choice");
            customerMenu();
            break;
    }
}
 
void Search_available()
{
    char roomNumber[LENGTH], roomType[LENGTH], maxPerson[LENGTH], roomStatus[LENGTH];
    char buffer[MAX_LENGTH];
    int found = 0, validChoice = 0, choice, price;


    FILE* room = fopen("room_status.txt", "r");
    if(!room)
    {
        printf("Error opening the file");
    }

    while(fgets(buffer, MAX_LENGTH, room))
    {
        sscanf(buffer, "%[^,], %[^,], %[^,], %d, %s", roomNumber, roomType, maxPerson, &price, roomStatus);
        if(strcmp(roomStatus, "Available") == 0)
        {
            found = 1;
            printf("Room Number: %s\n", roomNumber);
            printf("Room Type: %s\n", roomType);
            printf("Max Occupancy: %s\n", maxPerson);
            printf("Price: %d\n", price);
            printf("\n\n");
        }
    }
    fclose(room);

    if(found)
    {
        while(!validChoice)
        {
            printf("Press 1 to return: ");
            scanf("%d", &choice);
            switch (choice) 
            {
                case 1:
                    system("clear");
                    customerMenu();
                    break;
                default:
                    system("clear");
                    printf("Invalid choice. Please enter number 1.\n");
                    break;
                
            }
        }
    }
    else
    {
        system("clear");
        printf("There are no available rooms\n");
        viewRoom();
    }
}
 
void Make_and_cancel_reservation()
{
    int choice;
 
    puts("/=============================/");
    puts("    | Make and cancel |    ");
    puts("/=============================/");
    puts("1. Make reservation");
    puts("2. Cancel reservation");
    puts("3. Return to Customer menu");
    puts("===============================");
    printf("Enter your choice: ");
    scanf("%d", &choice);
 
    switch (choice) {
        case 1:
            system("clear");
            makeReservationCustomer();
            break;
        case 2:
            system("clear");
            cancelReservationCustomer();
            break;
        case 3:
            system("clear");
            customerMenu();
            break;
        default:
            puts("Invalid choice");
            break;
    }
}
 
void makeReservationCustomer() 
{
    char customerName[LENGTH], customerID[LENGTH], inputRoomType[LENGTH], inputRoomNumber[LENGTH], inputReservationDate[LENGTH];
    char storedRoomType[LENGTH], storedRoomNumber[LENGTH], storedReservationDate[LENGTH];
    char buffer[MAX_LENGTH], buffer2[MAX_LENGTH];
    int roomChoice, storedPrice, find1 = 0, find2 = 1, validChoice = 0;

    printf("Enter your name: ");
    scanf("%s", customerName);

    // Generate a unique customer ID
    FILE *guestFile = fopen("reservation.txt", "r");
    if (!guestFile) {
        printf("Error opening the file");
        return;
    }

    int maxId = 0;
    while (fgets(buffer, MAX_LENGTH, guestFile)) {
        int id;
        sscanf(buffer, "%d,%*s", &id);
        if (id > maxId) {
            maxId = id;
        }
    }
    fclose(guestFile);

    int nextId = maxId + 1;
    sprintf(customerID, "%d", nextId);

    while (validChoice == 0) {
        printf("Room types:\n");
        printf("1. Single room with balcony (mall view)\n");
        printf("2. Single room without balcony (mall view)\n");
        printf("3. Single room without balcony (sea view)\n");
        printf("4. Double room (sea view)\n");
        printf("5. Private villa (sea view)\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &roomChoice);

        switch (roomChoice) {
            case 1:
                strcpy(inputRoomType, "Single room with balcony (mall view)");
                validChoice = 1;
                break;
            case 2:
                strcpy(inputRoomType, "Single room without balcony (mall view)");
                validChoice = 1;
                break;
            case 3:
                strcpy(inputRoomType, "Single room without balcony (sea view)");
                validChoice = 1;
                break;
            case 4:
                strcpy(inputRoomType, "Double room (sea view)");
                validChoice = 1;
                break;
            case 5:
                strcpy(inputRoomType, "Private villa (sea view)");
                validChoice = 1;
                break;
            default:
                system("clear");
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    }

    printf("Enter room number: ");
    scanf("%s", inputRoomNumber);

    printf("Enter reservation date (YYYY-MM-DD): ");
    scanf("%s", inputReservationDate);

    time_t t = time(NULL);
    struct tm currentDate = *localtime(&t);

    int inputYear, inputMonth, inputDay;
    sscanf(inputReservationDate, "%d-%d-%d", &inputYear, &inputMonth, &inputDay);

    if (inputYear < (currentDate.tm_year + 1900) ||
       (inputYear == (currentDate.tm_year + 1900) && inputMonth < (currentDate.tm_mon + 1)) ||
       (inputYear == (currentDate.tm_year + 1900) && inputMonth == (currentDate.tm_mon + 1) && inputDay < currentDate.tm_mday)) {
        system("clear");
        printf("Invalid reservation date. The reservation date cannot be before the current date or in an incorrect format (YY-MM-DD). \nMake a new reservation with valid date\n");
        Make_and_cancel_reservation();
    }

    FILE *room = fopen("room_status.txt", "r");
    guestFile = fopen("reservation.txt", "r");

    if (!room || !guestFile) {
        printf("Error opening the file");
        return;
    }

    while (fgets(buffer, MAX_LENGTH, room)) {
        sscanf(buffer, "%[^,], %[^,], %*[^,], %d, %*s", storedRoomNumber, storedRoomType, &storedPrice);
        if (strcmp(storedRoomType, inputRoomType) == 0 && strcmp(storedRoomNumber, inputRoomNumber) == 0) {
            find1 = 1;
            break;
        }
    }

    while (fgets(buffer2, MAX_LENGTH, guestFile)) {
        sscanf(buffer2, "%*[^,], %*[^,], %[^,], %*[^,], %[^,], %*[^,]", storedRoomNumber, storedReservationDate);
        if (strcmp(storedRoomNumber, inputRoomNumber) == 0 && strcmp(storedReservationDate, inputReservationDate) == 0) {
            find2 = 0;
            break;
        }
    }

    fclose(room);
    fclose(guestFile);

    if (find1 && find2) {
        guestFile = fopen("reservation.txt", "a");
        if (!guestFile) {
            printf("Error opening the file");
            return;
        }
        fprintf(guestFile, "%s,%s,%s,%s,%s,%d\n", customerID, customerName, inputRoomNumber, inputRoomType, inputReservationDate, storedPrice);
        fclose(guestFile);
        system("clear");
        printf("\nReservation for %s has been successfully made. Please inform the guest about their booking details.\n", customerName);
    } else {
        system("clear");
        printf("No available rooms of the selected type.\n");
    }

    customerMenu();
}
 
void cancelReservationCustomer()
{
    char inputCustomerID[LENGTH], storedCustomerID[LENGTH];
    char buffer[MAX_LENGTH];
    int found = 0;

    printf("Enter your ID: ");
    scanf("%s", inputCustomerID);

    FILE* guest = fopen("reservation.txt", "r");
    FILE* temp = fopen("temp.txt", "w");

    while(fgets(buffer, MAX_LENGTH, guest))
    {
        sscanf(buffer, "%[^,], %*[^,], %*[^,], %*[^,], %*[^,], %*d", storedCustomerID);
        if (strcmp(storedCustomerID, inputCustomerID) == 0)
        {
            found = 1;
        }
        else
        {
            fputs(buffer, temp);
        }
    }
    fclose(guest);
    fclose(temp);

    remove("reservation.txt");
    rename("temp.txt", "reservation.txt");

    if(found)
    {
        system("clear");
        printf("The reservation for Customer ID.\n", inputCustomerID);
    }
    else
    {
        system("clear");
        printf("The reservation for Customer %s.", inputCustomerID);
    }

    Make_and_cancel_reservation();
}

void View_history_and_current_bookings()
{
    int choice;

    printf("===========================================\n");
    printf("View reservation history and current bookings.\n");
    printf("===========================================\n");
    printf("[1] View reservation history\n");
    printf("[2] View current bookings\n");
    printf("[0] Return to customer menu\n");
    printf("========================\n");
    printf("Enter your choice(1-2): ");
    scanf("%d", &choice);

    switch (choice) 
    {
        case 1:
            system("clear");
            viewHistory();
            break;
        case 2:
            system("clear");
            currentBookings();
            break;
        case 0:
            system("clear");
            customerMenu();
        default:
            system("clear");
            printf("Invalid choice. Please enter number between 1 to 2.\n");
            View_history_and_current_bookings();
            break;
    }

}

void currentBookings()
{
    char inputCustomerName[LENGTH], inputReservationDate[LENGTH], inputRoomNumber[LENGTH], storedCustomerName[LENGTH], storedRoomNumber[LENGTH], storedRoomType[LENGTH], storedReservationDate[LENGTH];
    char buffer[MAX_LENGTH];
    int found = 0, choice, validChoice = 0, i = 1, price;

    printf("Enter your name: ");
    scanf("%s", inputCustomerName);  

    FILE* guest = fopen("reservation.txt", "r");
    if(!guest)
    {
        printf("Error opening the file\n");
    }

    while(fgets(buffer, MAX_LENGTH, guest))
    {
        sscanf(buffer, "%*[^,], %[^,], %[^,], %[^,], %[^,], %d", storedCustomerName, storedRoomNumber, storedRoomType, storedReservationDate, &price);
        if (strcmp(inputCustomerName, storedCustomerName) == 0)
        {
            printf("RESERVATION NUMBER: %d\n", i);
            printf("Room Number: %s\n", storedRoomNumber);
            printf("Room Type: %s\n", storedRoomType);
            printf("Reservation Date: %s\n", storedReservationDate);
            printf("Price: %d", price);
            i++;
            printf("\n\n");
            found = 1;
        }
    }

    if(!found)
    {
        system("clear");
        printf("Customer with ID %s not found.\n", inputCustomerName);
        View_history_and_current_bookings();
    }
    else
    {
        while (validChoice == 0)
        {
            printf("Would you like to view another reservation?\n");
            printf("[1] Yes\n");
            printf("[2] No(Go back)\n");
            printf("Enter your choice(1-2): ");
            scanf("%d", &choice);

            switch(choice)
            {
                case 1:
                    system("clear");
                    currentBookings();
                    validChoice = 1;
                    break;
                
                case 2:
                    system("clear");
                    customerMenu();
                    validChoice = 1;
                    break;

                    default:
                    system("clear");
                    printf("Invalid choice. Please enter number 1 or 2.\n");
            }
        }
    }

}

void viewHistory()
{
    char storedCustomerID[LENGTH], storedCustomerName[LENGTH], storedRoomNumber[LENGTH], storedRoomType[LENGTH], storedReservationDate[LENGTH];
    char inputC[LENGTH], inputRoomNumber[LENGTH], inputReservationDate[LENGTH], inputCustomerName[LENGTH];
    char buffer[MAX_LENGTH];
    int found = 0, validChoice = 0, choice, i = 1;

    printf("Enter your name: ");
    scanf("%s", inputCustomerName);

    FILE* history = fopen("bookingHistory.txt", "r");
    if(!history)
    {
        printf("Error opening the file");
    }

    while(fgets(buffer, MAX_LENGTH, history))
    {
        sscanf(buffer, "%[^,], %[^,], %[^,], %[^,], %s", storedCustomerID, storedCustomerName, storedRoomNumber, storedRoomType, storedReservationDate);
        if (strcmp(storedCustomerName, inputCustomerName) == 0)
        {
            found = 1;
            printf("Reservation number: %d\n", i);
            printf("Guest name: %s\n", storedCustomerName);
            printf("Room number: %s\n", storedRoomNumber);
            printf("Room Type: %s\n", storedRoomType);
            printf("Date: %s\n", storedReservationDate);
            printf("\n\n");
            i++;
        }
    }
    fclose(history);

    if(found)
    {
        while(!validChoice)
        {
            printf("Press 1 to return: ");
            scanf("%d", &choice);
            switch (choice) 
            {
                case 1:
                    system("clear");
                    View_history_and_current_bookings();
                    break;
                default:
                    system("clear");
                    printf("Invalid choice. Please enter number 1.\n");
                    break;
                
            }
        }
    }
    else
    {
        system("clear");
        printf("Customer can't be found\n");
        View_history_and_current_bookings();
    }
}

 

//Guest
void guestSection() {
    int choice;

    do {
        printf("===================\n");
        printf("  Guest Section\n");
        printf("===================\n");
        printf("[1] View Room Availability\n");
        printf("[2] View Room Details\n");
        printf("[0] Return to Main Menu\n");
        printf("===================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                system("clear");
                viewRoomAvailability();
                break;
            case 2:
                system("clear");
                ViewRoomDetails();
                break;
            case 0:
                system("clear");
                printf("Returning to Main Menu.\n");
                mainMenu();
                break;
            default:
                system("clear");
                printf("Invalid choice. Please enter a number between 0 and 2.\n");
                break;
        }

    } while (choice != 0);
}

void viewRoomAvailability() {
    FILE *file;
    char line[512];

    file = fopen("room_status.txt", "r");
    if (file == NULL) {
        printf("Error opening file! Unable to view room availability.\n");
        return;
    }

    printf("Available rooms:\n");
    while (fgets(line, sizeof(line), file)) {
        char room_number[100], room_type[100], persons_allowed[100], status[100];
        int original_price;

        // Ensure the line matches the expected format
        int matched = sscanf(line, "%[^,],%[^,],%[^,],%d,%[^,\n]", room_number, room_type, persons_allowed, &original_price, status);
        if (matched == 5 && strcmp(status, "Available") == 0) 
        {
            printf("Room number: %s, Room type: %s\n", room_number, room_type);
        }
    }

    fclose(file);
}

void ViewRoomDetails() {
    FILE *file;
    char line[512];
    int found = 0;

    file = fopen("room_status.txt", "r");
    if (file == NULL) {
        printf("Error opening file! Unable to view room details.\n");
        return;
    }

    printf("We have five room types:\n");
    printf("1. Single room with balcony (mall view)\n");
    printf("2. Single room without balcony (mall view)\n");
    printf("3. Single room without balcony (sea view)\n");
    printf("4. Double room (sea view)\n");
    printf("5. Private villa (sea view)\n");
    printf("Choose room type to provide more information: ");

    int room_type_choice;
    scanf("%d", &room_type_choice);

    char search_room_type[100], room_description[256];
    int room_price;
    switch (room_type_choice) {
        case 1:
            strcpy(search_room_type, "Single room with balcony (mall view)");
            strcpy(room_description, "It is with balcony allocated on the mall but it's near from the beach.");
            break;
        case 2:
            strcpy(search_room_type, "Single room without balcony (mall view)");
            strcpy(room_description, "It is without balcony allocated on the mall but it's near from the beach.");
            break;
        case 3:
            strcpy(search_room_type, "Single room without balcony (sea view)");
            strcpy(room_description, "It allocates on the beach but without balcony.");
            break;
        case 4:
            strcpy(search_room_type, "Double room (sea view)");
            strcpy(room_description, "It is 2 rooms allocated on the beach with balcony.");
            break;
        case 5:
            strcpy(search_room_type, "Private villa (sea view)");
            strcpy(room_description, "it is a private villa that has 3 rooms with the living room allocated on the beach.");
            break;
        default:
            printf("Invalid room type choice.\n");
            fclose(file);
            return;
    }

    while (fgets(line, sizeof(line), file)) {
        char current_room_type[100], persons_allowed[100];
        sscanf(line, "%*[^,],%[^,],%[^,],%d,%*s", current_room_type, persons_allowed, &room_price);

        if (strcmp(current_room_type, search_room_type) == 0) 
        { 
            system("clear");
            printf("The room allowed to be booked for: %s\n", persons_allowed);
            printf("The room price is: %d\n", room_price);
            printf("%s\n", room_description);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Room type '%s' not found.\n", search_room_type);
    }
}

