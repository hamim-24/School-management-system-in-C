#include <stdio.h>
#include <string.h>  //string function
#include <stdlib.h>  //system() exit()
#include <time.h>    //time
#include <unistd.h>  //usleep()
#include <termios.h> //change system
#include <ctype.h>   //toupper()

void menu();                                       // shows main menu
void menu_shape(char *menu[], int size);           // makes shape of all menu | take menu and its number
int space_before(char *str);                       // takes pointer, return number of space
int space_after(char *str);                        // these count space of both size so that it can print in middle
void heading();                                    // clear and printf heading
void sub_heading(char *sub_heading[], int option); // clear print heading, sub heading
int pwdchecker();                                  // check pwd | open "AdminPassword",read str,take pwd(***) if match(0) else (1)
void administration(char name[30]);                // administration menu and work
char *generateTime();                              // generate time pointer and '\n' at the end
void ending();                                     // press enter to continue
void file_print(char file[30]);                    // take file, add ".txt", open "file.txt" read and write
void questionCreate(char name[30]);                // create question
void question(char name[30]);                      // question menu
int surityChecker();                               // ensuring if yes (0) else (1)
void exam_system(char id[30]);                     // printf question one by one and make result
void setting(char name[30]);                       // setting menu and set name address number pwd
void notice(char name[30]);                        // control notice
void registration();                               //
void disable_echo_mode();                          // invisible the input in the terminal
void enable_echo_mode();                           // visible the input in the terminal
void loading(char str1[40], char str2[40]);
int is_id_match(const char *text, const char *id);

FILE *fptr;

const int max_char = 80; // lenhth of the out display

int surityChecker()
{
    char ch;
    int value;
    do
    {
        printf("Are you sure(y/n) : ");
        ch = getchar();
        fflush(stdin);
    } while (ch != 'y' && ch != 'n');
    switch (ch)
    {
    case 'y':
        value = 0;
        break;
    case 'n':
        value = 1;
        break;
    default:
        surityChecker();
        break;
    }
    return value;
}

void file_print(char file[30])
{
    char file_name[30], temp[100];
    strcpy(file_name, file);
    strcat(file_name, ".txt");
    fptr = fopen(file_name, "r");
    do
    {
        fgets(temp, sizeof temp, fptr);
        temp[strcspn(temp, "\n")] = '\0';
        puts(temp);
    } while (!feof(fptr));
    fclose(fptr);
}
char *generateTime()
{
    time_t current_time = time(NULL); // generate time
    struct tm *local_time = localtime(&current_time);
    return asctime(local_time);
}

void loading(char str1[40], char str2[40])
{
    for (int i = 0; i <= 100; i++)
    {
        system("clear");
        printf("\n\n\n\t\t%s : [", str1);
        for (int j = 0; j < i / 4; j++)  // print '=' for 50 times
            printf("=");                 // print '=' for i time
        printf(">");                     // =====(i time)==>
        for (int j = i / 4; j < 25; j++) // print ' ' for 50-(i/2) time
            printf(" ");
        printf("\b] %d%%", i); // last time '>' remove [=========] 100%
        fflush(stdout);
        usleep(20000);
        printf("\r");
    }
    printf("\n\n\t**%s**\n", str2);
    fflush(stdout);
    usleep(2000000);
    fflush(stdin);
    system("clear");
}

void disable_echo_mode()
{
    fflush(stdout);
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);          // Get current terminal attributes
    tty.c_lflag &= ~(ECHO | ICANON);        // Disable echo and canonical mode
    tcsetattr(STDIN_FILENO, TCSANOW, &tty); // Set the modified attributes
}

void enable_echo_mode()
{
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);          // Get current terminal attributes
    tty.c_lflag |= (ECHO | ICANON);         // Enable echo and canonical mode
    tcsetattr(STDIN_FILENO, TCSANOW, &tty); // Set the modified attributes
}

int pwdchecker()
{
    int value = 1;

    char pwd[12];
    char u_pwd[12];

    fptr = fopen("AdminPassword.txt", "r");
    fgets(pwd, sizeof pwd, fptr);
    fclose(fptr);

    heading();
    for (int i = 2; i >= 0; i--)
    {
        printf("Enter password : ");
        char ch;
        // Read characters one by one, handle backspace, and show '*' for input
        int j = 0;
        disable_echo_mode();
        while ((ch = getchar()) != 10 && i < 11)
        {
            if (ch == 127) // if back
            {
                if (j > 0)
                {
                    j--;             // Move back in the buffer
                    printf("\b \b"); // Erase '*' from screen by moving cursor back, printing space, then moving cursor back again
                } // clearing buffer
            }
            else
            {
                u_pwd[j++] = ch; // Store the character in the password buffer
                printf("*");     // Display '*'
            }
        }
        u_pwd[j] = '\0'; // last char of str must be null
        enable_echo_mode();
        printf("\n");
        if (i == 0)
        { // last time

            printf("\n**Incorrect Password.**\nAction Failed.\n");
            usleep(1000000);
        }
        else if (strcmp(pwd, u_pwd))
            printf("\n**Incorrect Password.**\nTry again for %d time(s).\n", i);

        else
        {
            printf("\n**Correct Password**.\n");
            value = 0;
            break;
        }
    }
    usleep(1000000);
    fflush(stdout);
    system("clear");
    return value;
}

int space_before(char *str)
{
    return ((max_char - 2 - strlen(str)) / 2) + 1;
}

int space_after(char *str)
{
    return (max_char - strlen(str) - space_before(str)) - 2;
}

void menu_shape(char *menu[], int size)
{
    char str[max_char - 2];
    strcpy(str, menu[0]);
    printf("%*s%s\n", space_before(str), "", str); // first str is sub heading

    for (int i = 0; i < max_char; i++)
        printf("=");

    strcpy(str, "");
    for (int i = 1; i < size; i++)
    {
        strcpy(str, menu[i]);
        printf("\n=%*s%d. %s%*s=\n", space_before(str) - 3, "", i, str, space_after(str), "");
        for (int j = 0; j < max_char; j++)
            printf("=");
    }
    printf("\n");
}

void questionCreate(char name[30])
{
    char ques_file[30], code[30], ans_file[30], res_file[30], temp[100], ans_no;
    int size;
    printf("Code of the question : ");
    fgets(code, sizeof code, stdin);
    code[strcspn(code, "\n")] = '\0';
    fflush(stdin);

    strcpy(ques_file, code);
    strcat(ques_file, ".txt"); // opening code.txt file
    fptr = fopen(ques_file, "r");
    while (fptr != NULL) // if exist ask for change it
    {
        fclose(fptr);
        printf("\nThe code exists, so please change it.\n");
        printf("Code of the question : ");
        strcpy(code, "");
        fgets(code, sizeof code, stdin);
        code[strcspn(code, "\n")] = '\0';
        fflush(stdin);

        strcpy(ques_file, code);
        strcat(ques_file, ".txt");
        fptr = fopen(ques_file, "r");
    }
    fclose(fptr);

    fptr = fopen(ques_file, "w");  // creating code.txt file
    printf("Name of the exam : "); // everything of this question will save here
    fgets(temp, sizeof temp, stdin);
    fflush(stdin);
    fprintf(fptr, "Welcome to the exam\nQuestion code : '%s'\n\n%*s%s", code, space_before(temp), "", temp);
    strcpy(temp, "");
    for (int i = 0; i < max_char; i++)
        fprintf(fptr, "=");
    fprintf(fptr, "\n");
    fclose(fptr);

    printf("Number of question : ");
    scanf("%d", &size);
    fflush(stdin);

    strcpy(ans_file, code);
    strcat(ans_file, "Ans.txt");
    for (int i = 0; i < size; i++) // repeat number of question times
    {
        fptr = fopen(ques_file, "a");
        printf("\nQuestion %d : ", i + 1);
        fgets(temp, sizeof temp, stdin);
        fflush(stdin);
        fprintf(fptr, " %d. %s", i + 1, temp);
        for (int j = 0; j < 4; j++) // taking options
        {
            strcpy(temp, "");
            printf("Option (%c) : ", 'a' + j);
            fgets(temp, sizeof temp, stdin);
            fflush(stdin);
            fprintf(fptr, "\t(%c) %s", 'a' + j, temp);
        }
        fclose(fptr);
        do // taking only a,b,c,d
        {
            printf("Answer (a,b,c,d) : ");
            scanf("%c", &ans_no);
            fflush(stdin);
        } while (ans_no != 'a' && ans_no != 'b' && ans_no != 'c' && ans_no != 'd');
        fptr = fopen(ans_file, "a");
        // print answer in the codeAns.txt file
        fprintf(fptr, "%c", ans_no);
        fclose(fptr);
    }
    fptr = fopen("AdminInfo.txt", "a"); // printing in admin info
    fprintf(fptr, "> %s creates question, code : %s TIME:%s ", name, code, generateTime());
    fclose(fptr);

    loading("Creating", "Question Created");
    heading();

    fptr = fopen("QuestionSubmit.txt", "r");
    // if exam is not running "No EXAM is running" will be written in the file
    // else question code will be written
    // after that reading the code, code.txt will opened
    strcpy(temp, "");
    fgets(temp, sizeof temp, fptr);
    fclose(fptr);

    if (strcmp(temp, "No EXAM is running")) // if running
    {
        printf("\n\t**Exam, code : %s is running,stop it to publish.**\n\n", temp);
        ending();
        question(name);
    }
    // if exam is not running
    printf("\nThe question has been created.\nThe question is publishing...\n");
    if (!surityChecker())
    {
        if (!pwdchecker())
        { // publish the question

            loading("Publishing", "Question Published.");

            fptr = fopen("Notice.txt", "a"); // printing in the notice
            fprintf(fptr, "> Question, code : %s is published TIME:%s ", code, generateTime());
            fclose(fptr);

            fptr = fopen("AdminInfo.txt", "a"); // printing in the admin info
            fprintf(fptr, "> %s publishes question, code : %s TIME:%s ", name, code, generateTime());
            fclose(fptr);

            strcpy(res_file, code);
            strcat(res_file, "Result.txt");
            fptr = fopen(res_file, "w");
            // creating codeResult.txt file for print result when question publish
            fprintf(fptr, "  Question code%s\n ", code);
            fclose(fptr);

            fptr = fopen("ResultSubmit.txt", "w");
            // if question is publish, "Result is not Published" will be written in that file
            // else question code will be written
            // after that reading the code, codeResult.txt will opened
            fprintf(fptr, "Result is not Published");
            fclose(fptr);

            fptr = fopen("QuestionSubmit.txt", "w");
            // if question is publish, question code will be written in that file
            // else "Result is not Published" will be written
            // after that reading the code, code.txt will opened
            fprintf(fptr, "%s", code); // print the question code in this file when question publish
            fclose(fptr);
        }
    }
    else
    {
        printf("\n\t**The question, code : %s is not published.**\n\n", code);
        ending();
    }
}

void question(char name[30])
{
    heading();
    fptr = fopen("QuestionSubmit.txt", "r");
    // if question is publish, question code will be written in that file
    // else "Result is not Published" will be written
    // after that reading the code, code.txt will opened
    char saved_code[30], res_file[30];
    fgets(saved_code, sizeof saved_code, fptr);
    fclose(fptr);
    // if exam is not running, "No EXAM is running" will be written in that file
    if (!strcmp(saved_code, "No EXAM is running"))
        printf("\t**%s**\n\n", saved_code);
    // else code wil be written in that file
    else
        printf("\t**Exam is running, code : %s.**\n\n", saved_code);

    char *ques_menu[] = {
        "Question",
        "Create",
        "Publish",
        "Stop Exam and Publish Result",
        "Back"};

    int size = sizeof ques_menu / sizeof ques_menu[0];
    menu_shape(ques_menu, size);

    int quse_opt;
    printf("Please select an option : ");
    scanf("%d", &quse_opt);
    fflush(stdin);

    switch (quse_opt)
    {
    case 1:
        sub_heading(ques_menu, quse_opt);

        printf("\n\t**Rules of creating question**\n\n");
        printf(" 1. Once you select question, option and answer can't reselect.\n");
        printf(" 2. You have to provide 4 options.\n");
        printf(" 3. You need to submit here or in the administration.\n");
        printf(" 3. If you submit more then one answer,1st will be the correct answer.\n");
        printf(" 4. Maximum qusetion 30.\n");

        printf("\nThe creating question is starting...\n");
        if (!surityChecker())
        {
            if (!pwdchecker())
            {
                sub_heading(ques_menu, quse_opt);

                questionCreate(name);
            }
        }
        else
        {
            printf("\n\t**Action Failed.**\n\n");
            ending();
        }
        break;
    case 2:
        sub_heading(ques_menu, quse_opt);
        if (!strcmp(saved_code, "No EXAM is running"))
        { // if exam is not running, question can be published
            char search_code[30];
            printf("Enter the question code : ");
            fgets(search_code, sizeof search_code, stdin);
            search_code[strcspn(search_code, "\n")] = '\0';
            fflush(stdin);

            char file[30];
            strcpy(file, search_code);
            strcat(file, ".txt");
            fptr = fopen(file, "r");
            if (fptr != NULL)
            { // if the code.txt file exist then publish
                printf("\nThe question, code : %s is publising...\n", search_code);
                if (!surityChecker())
                {
                    if (!pwdchecker())
                    {
                        loading("Publishing", "Question Published");
                        fptr = fopen("Notice.txt", "a"); // print in the notice
                        fprintf(fptr, "> Question, code : %s is published TIME:%s ", search_code, generateTime());
                        fclose(fptr);

                        fptr = fopen("AdminInfo.txt", "a"); // print in the admin info
                        fprintf(fptr, "> %s publishes question, code : %s TIME:%s ", name, search_code, generateTime());
                        fclose(fptr);

                        fptr = fopen("ResultSubmit.txt", "w");
                        // if question is publish, "Result is not Published" will be written in that file
                        // else question code will be written
                        // after that reading the code, codeResult.txt will opened
                        fprintf(fptr, "Result is not Published");
                        fclose(fptr);

                        fptr = fopen("QuestionSubmit.txt", "w");
                        // if question is publish,question code will be written in that file
                        // else "No EXAM is running" will be written
                        // after that reading the code, code.txt will opened
                        fprintf(fptr, "%s", search_code);
                        fclose(fptr);

                        strcpy(res_file, search_code);
                        strcat(res_file, "Result.txt"); // codeResult.txt will be created for print result
                        fptr = fopen(res_file, "w");
                        fprintf(fptr, "  Question code%s\n ", search_code);
                        fclose(fptr);
                    }
                }
                else
                {
                    printf("\n\t**The exam, code : %s is not published.**\n\n", search_code);
                    ending();
                }
            }
            else
            {
                printf("\n\t**The question, code : %s is not created.**\n\n", search_code);
                ending();
            }
        }
        else
        {
            printf("\n\t**Exam is running, code : %s. Stop it.**\n\n", saved_code);
            ending();
        }

        break;
    case 3:
        sub_heading(ques_menu, quse_opt);
        if (strcmp(saved_code, "No EXAM is running"))
        { // if stop, question will be remove,result will be publish
            printf("\nThe question, code : %s is stoping... and result is publishing...\n", saved_code);
            if (!surityChecker())
            {
                if (!pwdchecker())
                {
                    loading("Stoping", "Question Stoped and Result Published");
                    fptr = fopen("QuestionSubmit.txt", "w");
                    // if question is publish,question code will be written in that file
                    // else "No EXAM is running" will be written
                    // after that reading the code, code.txt will opened
                    fprintf(fptr, "No EXAM is running");
                    fclose(fptr);

                    fptr = fopen("ResultSubmit.txt", "w");
                    // if question is publish, "Result is not Published" will be written in that file
                    // else question code will be written
                    // after that reading the code, codeResult.txt will opened
                    fprintf(fptr, "%s", saved_code);
                    fclose(fptr);

                    fptr = fopen("AdminInfo.txt", "a"); // print in the admin info
                    fprintf(fptr, "> %s stops question, code : %s TIME:%s ", name, saved_code, generateTime());
                    fclose(fptr);

                    fptr = fopen("Notice.txt", "a"); // print in the notice
                    fprintf(fptr, "> Exam (code : %s) is finished TIME:%s ", saved_code, generateTime());
                    fprintf(fptr, "> Result (code : %s) is published TIME:%s ", saved_code, generateTime());
                    fclose(fptr);
                }
            }
            else
            {
                printf("\n\t**The exam code : %s has not been stoped.**\n\n", saved_code);
                ending();
            }
        }
        else
        {
            printf("\n\t**%s**\n\n", saved_code);
            ending();
        }
        break;
    case 4:
        administration(name);
    default:
        question(name);
        break;
    }
    question(name);
}

void notice(char name[30])
{
    heading();
    char *note_menu[] = {
        "Notice Control",
        "Add notice",
        "Clear notice",
        "Back"};

    int n_size, n_opt;
    n_size = sizeof note_menu / sizeof note_menu[0];
    menu_shape(note_menu, n_size);

    printf("Please select an option : ");
    scanf("%d", &n_opt);
    fflush(stdin);

    char note[100];
    switch (n_opt)
    {
    case 1:
        sub_heading(note_menu, n_opt);
        printf("You can add a single notice at a time.\n");
        printf("Enter the notice : ");
        fgets(note, sizeof note, stdin);
        note[strcspn(note, "\n")] = '\0';
        fflush(stdout);

        if (!surityChecker())
        {
            loading("Adding", "Notice added.");
            fptr = fopen("Notice.txt", "a");
            fprintf(fptr, "> %s\n ", note);
            fclose(fptr);

            fptr = fopen("AdminInfo.txt", "a"); // print in the notice
            fprintf(fptr, "> %s adds notice TIME:%s ", name, generateTime());
            fclose(fptr);
        }
        else
        {
            printf("\n\t**Notice is not added.**\n\n");
            ending();
        }
        break;
    case 2:
        sub_heading(note_menu, n_opt);
        printf("\nNotice is clearing...\n");
        if (!surityChecker())
        {
            loading("Clearing", "Notice is cleared.");
            fptr = fopen("Notice.txt", "w");
            fprintf(fptr, " "); // print space in the file
            fclose(fptr);

            fptr = fopen("AdminInfo.txt", "a"); // print in the notice
            fprintf(fptr, "> %s clears notice TIME:%s ", name, generateTime());
            fclose(fptr);
        }
        else
        {
            printf("\n\t**Notice is not cleared.**\n\n");
            ending();
        }
        break;
    case 3:
        administration(name);
        break;
    default:
        notice(name);
        break;
    }
    administration(name);
}

void administration(char name[30])
{
    heading();
    char *admin_menu[] = {
        "Administration",
        "Notification",
        "Question",
        "Search Student & Delete",
        "Notice Control",
        "Setting",
        "Back"};
    int size = sizeof admin_menu / sizeof admin_menu[0];
    menu_shape(admin_menu, size);

    int option;
    printf("Please select an option : ");
    scanf("%d", &option);
    fflush(stdin);

    switch (option)
    {
    case 1:
        if (!pwdchecker())
        {
            sub_heading(admin_menu, option);

            file_print("AdminInfo");

            ending();
        }
        break;
    case 2:
        if (!pwdchecker())
        {
            question(name);
        }
        break;
    case 3:
        if (!pwdchecker())
        {
            sub_heading(admin_menu, option);
            char id[30];
            char file[30];

            printf("Enter student ID : ");
            fgets(id, sizeof id, stdin);
            id[strcspn(id, "\n")] = '\0';
            fflush(stdin);

            strcpy(file, id);
            strcat(file, "Info.txt");
            fptr = fopen(file, "r"); // opening idInfo.txt
            if (fptr == NULL)
            { // if file doesn't exist
                fclose(fptr);
                loading("Searching", "Student does not exist.");
            }
            else
            {
                fclose(fptr);
                loading("Searching", "Student exist.");
                sub_heading(admin_menu, option);
                printf(" > ID : %s\n", id);
                strcpy(file, id);
                strcat(file, "Info");

                file_print(file);

                printf("\n\nDeleting ID...\n");
                if (!surityChecker())
                {
                    strcat(file, ".txt");
                    remove(file);

                    fptr = fopen("AdminInfo.txt", "a"); // printing in the admin info
                    fprintf(fptr, "> ID:%s Deleted, TIME:%s ", id, generateTime());
                    fclose(fptr);
                }

                ending();
            }
        }
        break;
    case 4:
        if (!pwdchecker())
            notice(name);
        break;
    case 5:
        setting(name);
        break;
    case 6:
        menu();
        break;
    default:
        administration(name);
        break;
    }
    administration(name);
}

void setting(char name[30]) // set -> school name, address, number, admin pwd
{
    heading();
    char temp[100];
    char *setting_menu[] = {
        "Setting",
        "Change school name",
        "Change school address",
        "Change school number",
        "Change Admin password",
        "Back"};
    char *filename[] = {
        "SchoolName.txt",
        "SchoolAddress.txt",
        "SchoolPhone.txt"};
    char *s_name[] = {
        "School name",
        "School address",
        "School number",
    };
    // size of pointer array = size of pointer array / size of pointer
    //   5  =  (5x8 bytes) / 8
    int size = sizeof setting_menu / sizeof setting_menu[0];
    menu_shape(setting_menu, size);

    printf("Please enter an option : ");
    int option;
    scanf("%d", &option);
    fflush(stdin);

    if (option == 1 || option == 2 || option == 3)
    {
        if (!pwdchecker()) // checking pwd
        {
            sub_heading(setting_menu, option);

            printf("Enter new %s : ", s_name[option - 1]); // print s_name[option-1]
            fgets(temp, sizeof temp, stdin);
            temp[strcspn(temp, "\n")] = '\0'; // converting '\n' into null char
            fflush(stdin);

            printf("\n%s : %s, is (saving...)\n", s_name[option - 1], temp);
            if (!surityChecker()) // ensuring
            {
                loading("Saving", "Successfully changed.");
                fptr = fopen(filename[option - 1], "w");
                fprintf(fptr, "%s", temp); // changing in file
                strcpy(temp, "");
                fclose(fptr);

                fptr = fopen("AdminInfo.txt", "a"); // print in admin info
                fprintf(fptr, "> %s changed %s, TIME:%s ", name, s_name[option - 1], generateTime());
                fclose(fptr);
            }
            else
            {
                printf("\n\t**%s is not changed.**\n\n", s_name[option - 1]);
                ending();
            }

            setting(name);
        }
        else
            setting(name);
    }
    else if (option == 4)
    {
        if (!pwdchecker()) // checking pwd
        {
            char pwd[12], u_pwd[12];
            sub_heading(setting_menu, option);

            for (int i = 2; i >= 0; i--)
            {
                do
                {
                    printf("\nPassword must be 6 character.\n");
                    printf("Enter new admin password : ");
                    strcpy(pwd, "");
                    fgets(pwd, sizeof pwd, stdin);
                    pwd[strcspn(pwd, "\n")] = '\0'; // converting the last \n into null
                    fflush(stdin);
                } while (strlen(pwd) != 6); // taking 6 character

                printf("Enter again password : ");
                strcpy(u_pwd, "");
                fgets(u_pwd, sizeof u_pwd, stdin);
                u_pwd[strcspn(u_pwd, "\n")] = '\0'; // converting the last \n into null
                fflush(stdin);

                char tempPwd[12];
                fptr = fopen("AdminPassword.txt", "r");
                fscanf(fptr, "%s", tempPwd); // changing pwd
                fclose(fptr);

                if (i == 0)
                {
                    printf("\n**Password is not changed.\n\n");
                    ending();
                }

                else if (strcmp(pwd, u_pwd))
                    printf("\n**Password did not match.**\nTry again for %d time(s).", i);

                else
                { // if the password is same as previous
                    if (!strcmp(tempPwd, pwd))
                    {
                        printf("\n\t**Admin password is still same.**\n\n");
                        ending();
                    }
                    else if (
                        printf("\nSchool password : %s (saving...)\n", pwd) && !surityChecker()) // ensuring
                    {
                        loading("Saving", "Successfully changed.");
                        fptr = fopen("AdminPassword.txt", "w");
                        fprintf(fptr, "%s", pwd); // changing pwd
                        fclose(fptr);

                        fptr = fopen("AdminInfo.txt", "a"); // print in admin info
                        fprintf(fptr, "> %s changed admin password, TIME:%s ", name, generateTime());
                        fclose(fptr);
                    }
                    else
                    {
                        printf("\n\t**Admin password is not changed.**\n\n");
                        ending();
                    }
                    break;
                }
            }
            setting(name);
        }
        else
            setting(name);
    }
    else if (option == 5)
    {
        administration(name);
    }
    else
        setting(name);
}

void heading()
{
    printf("\n");
    fflush(stdout);
    system("clear");
    char temp[max_char - 2];
    char *info[] = {
        "SchoolName.txt",
        "SchoolAddress.txt",
        "SchoolPhone.txt"};
    for (int i = 0; i < max_char; i++)
        printf("=");
    for (int i = 0; i < 3; i++)
    {
        fptr = fopen(info[i], "r");
        // in the 1st run file is not created, so it will be null
        // then create file and print "school info"
        // it will print in the heading()
        if (fptr == NULL)
        {
            fclose(fptr);

            fptr = fopen(info[i], "w");
            fputs("Set school info in administration default password 111111", fptr);
            fclose(fptr);

            fptr = fopen(info[i], "r");
        }
        // if file is found, read and print in the header()
        fgets(temp, sizeof temp, fptr);
        printf("\n=%*s%s%*s=", space_before(temp), "", temp, space_after(temp), "");
        strcpy(temp, "");
        fclose(fptr);
    }
    printf("\n");
    for (int i = 0; i < max_char; i++)
        printf("=");

    printf("\n\n\n");
}

void sub_heading(char *sub_heading[], int option)
{
    heading();
    printf("%*s%s", space_before(sub_heading[option]), "", sub_heading[option]);
    printf("\n");
    for (int i = 0; i < max_char; i++)
        printf("=");
    printf("\n");
}

void ending()
{
    for (int i = 0; i < max_char; i++)
        printf("=");
    printf("\nPress enter to continue.");
    getchar();
}

void exam_system(char id[30])
{
    char saved_code[30], file[30], ans[30], stu_ans, ques[100], res_file[30];

    fptr = fopen("QuestionSubmit.txt", "r");
    // if question is publish, question code will be written in that file
    // else "No EXAM is running" will be written
    // after that reading the code, code.txt will opened
    fgets(saved_code, sizeof saved_code, fptr); // taking the code
    fclose(fptr);

    strcpy(file, saved_code);
    strcat(file, "Ans.txt");
    fptr = fopen(file, "r");
    // opening the codeAns.txt file
    fgets(ans, sizeof ans, fptr); // get the answer
    fclose(fptr);

    float mark = 0;
    int ques_num = strlen(ans); // calculating the answer number same as question number

    printf("\n\t**Rules of Exam**\n");
    printf("\n 1. In the exam you will find %d question(s).", ques_num);
    printf("\n 2. You need to enter 'a','b','c','d'.");
    printf("\n 3. Each question contains 1 point.");
    printf("\n 4. Incorrect each question you will obtain -.25 point.");
    printf("\n 5. After answer, press enter for next question.");
    printf("\n 6. For skip just press enter.");
    printf("\n 7. Find result in result option after publishing.");
    printf("\n 8. It will notify you through notice.\n");

    ending();
    loading("Loading", "Question is loaded.");
    heading();
    strcpy(file, saved_code);
    strcat(file, ".txt");
    fptr = fopen(file, "r");
    // heading contains 5 line
    // each question contains 5 lines
    for (int i = 0; i <= ques_num; i++) // repeat for number of question +1 times
    {
        for (int j = 0; j < 5; j++) // print 5 line
        {
            fgets(ques, sizeof ques, fptr);
            printf("%s", ques);
        }
        // at first print heading and first question
        // then ask for answer
        if (i != 0)
        {
            printf("Answer(a,b,c,d) : ");
            scanf("%c", &stu_ans);
            fflush(stdin);

            if (ans[i - 1] == stu_ans) // if correct
                mark++;
            else if (stu_ans == 10) // if skip
                mark = mark;
            else // if incorrect
                mark = mark - .25;
        }
        printf("\n");
    }
    strcpy(res_file, saved_code);
    strcat(res_file, "Result.txt");
    fptr = fopen(res_file, "a");
    // open codeResult.txt and add result
    fprintf(fptr, "> ID: %s   \tMARK: %.2f  \tEXAM TIME: %s ", id, mark, generateTime());
    fclose(fptr);

    printf("\t**Exam is end.**\n\n");
    ending();
}

void registration()
{

    char id[30], temp[30], file[30];

    printf("Enter id : ");
    fgets(id, sizeof id, stdin);
    id[strcspn(id, "\n")] = '\0';
    fflush(stdin);

    strcpy(temp, id);
    strcat(temp, "Info.txt");
    fptr = fopen(temp, "r"); // opening idInfo.txt
    if (fptr != NULL)
    { // if file exist
        fclose(fptr);

        printf("\n\t**You have registered.**\n\n");
        ending();
        menu();
    }
    else if (!surityChecker())
    { // registration
        fclose(fptr);

        // user
        strcpy(file, id);
        strcat(file, "Info.txt"); // info
        fptr = fopen(file, "w");
        strcpy(temp, "");
        printf("\nEnter your full name : ");
        fgets(temp, sizeof temp, stdin);
        fflush(stdin);
        fprintf(fptr, " > Full name : %s", temp);
        strcpy(temp, "");
        printf("Enter your roll : ");
        fgets(temp, sizeof temp, stdin);
        fflush(stdin);
        fprintf(fptr, " > Roll : %s", temp);
        strcpy(temp, "");
        printf("Enter your class : ");
        fgets(temp, sizeof temp, stdin);
        fflush(stdin);
        fprintf(fptr, " > Class : %s", temp);
        strcpy(temp, "");
        printf("Enter your phone number : ");
        fgets(temp, sizeof temp, stdin);
        fflush(stdin);
        fprintf(fptr, " > Phone number : %s", temp);
        strcpy(temp, "");
        printf("Enter your Fathers name : ");
        fgets(temp, sizeof temp, stdin);
        fflush(stdin);
        fprintf(fptr, " > Father name : %s", temp);
        strcpy(temp, "");
        printf("Enter your Mothers name : ");
        fgets(temp, sizeof temp, stdin);
        fflush(stdin);
        fprintf(fptr, " > Mother name : %s", temp);
        strcpy(temp, "");
        printf("Enter your address(in a line) : ");
        fgets(temp, sizeof temp, stdin);
        // temp[strcspn(temp, "\n")] = '\0';
        fflush(stdin);
        fprintf(fptr, " > Address : %s ", temp);
        strcpy(temp, "");

        fclose(fptr);
        if (surityChecker())
        {
            remove(file);
            printf("\n\t**Registration  Failed.**\n\n");
            ending();
            menu();
        }
        fptr = fopen("AdminInfo.txt", "a"); // printing in the admin info
        fprintf(fptr, "> NEW ID:%s Registered, TIME:%s ", id, generateTime());
        fclose(fptr);

        loading("Loading", "Registration Complete.");

        menu();
    }
    else
    {
        printf("\n\t**Registration  Failed.**\n\n");
        ending();
        menu();
    }
}

int is_id_match(const char *text, const char *id) // get from chat gpt
{
    int len = strlen(id);
    // Check if the id in text is bounded by id delimiters
    if ((text == id || isspace(*(text - 1)) || ispunct(*(text - 1))) &&
        (isspace(*(text + len)) || ispunct(*(text + len)) || *(text + len) == '\0'))
    {
        return 1; // It's a match
    }

    return 0; // Not a match
}

void menu()
{
    heading();
    int option;
    char *main_menu[] = {
        "Main Menu",
        "Administration",
        "Notic Board",
        "Search Question",
        "Exam",
        "Result",
        "Registration",
        "Exit"};

    int size = sizeof main_menu / sizeof main_menu[0];
    menu_shape(main_menu, size);
    // add user
    char *admin_name[] = {"rabin",
                          "alex"};
    char u_admin_name[30];
    int ad_name_size = sizeof admin_name / sizeof admin_name[0];
    char code[30], file[30];

    printf("Please select an option : ");
    scanf("%d", &option);
    fflush(stdin);

    switch (option)
    {
    case 1:
        heading();
        printf("Enter your name : ");
        fgets(u_admin_name, sizeof u_admin_name, stdin);
        u_admin_name[strcspn(u_admin_name, "\n")] = '\0';
        fflush(stdin);

        for (int i = 0; i < ad_name_size; i++) // repeat total number of admin times
        {
            if (!strcmp(u_admin_name, admin_name[i]))
            {
                if (pwdchecker())
                {
                    fptr = fopen("AdminInfo.txt", "a"); // print in admin info
                    fprintf(fptr, "> %s tried but failed TIME:%s ", u_admin_name, generateTime());
                    fclose(fptr);
                }
                else
                {
                    fptr = fopen("AdminInfo.txt", "a"); // print in admin info
                    fprintf(fptr, "> %s log in TIME:%s ", u_admin_name, generateTime());
                    fclose(fptr);
                    loading("Loading", "Logged in.");
                    administration(u_admin_name);
                }
                break;
            }
            else if (i == ad_name_size - 1)
            {
                printf("\n\t**You can not enter.**\n\n");
                ending();
            }
        }

        break;
    case 2:
        sub_heading(main_menu, option);

        file_print("Notice"); // print notice

        ending();
        break;
    case 3:
        sub_heading(main_menu, option);
        printf("Enter the code of question : ");

        strcpy(code, "");
        fgets(code, sizeof code, stdin);
        code[strcspn(code, "\n")] = '\0';
        fflush(stdin);

        fptr = fopen("QuestionSubmit.txt", "r");
        // if question is publish, question code will be written in that file
        // else "No EXAM is running" will be written
        // after that reading the code, code.txt will opened
        fgets(file, sizeof file, fptr); // get question code
        fclose(fptr);

        if (!strcmp(file, code))
        { // if the exam is running

            loading("Searching", "The exam is running, you can't see this question.");
            menu(); // go to menu()
        }

        strcpy(file, code);
        strcat(file, ".txt");
        fptr = fopen(file, "r"); // open code.txt
        if (fptr == NULL)
        { // if file doesn't exist
            fclose(fptr);

            loading("Searching", "Question is not found.");
        }
        else
        {
            loading("Searching", "Question is found.");
            sub_heading(main_menu, option);
            fclose(fptr);

            printf("\n");
            file_print(code); // print question

            printf("\nPress enter to see the answer.\n");
            getchar();

            strcpy(file, code);
            strcat(file, "Ans");

            printf("Answer(serialy) : ");
            file_print(file); // print ans from codeAns.txt
            ending();
        }
        break;
    case 4:
        sub_heading(main_menu, option);
        char text_file[1000];
        char id[100];
        char *position;

        fptr = fopen("QuestionSubmit.txt", "r");
        // if question is publish, question code will be written in that file
        // else "No EXAM is running" will be written
        // after that reading the code, code.txt will opened
        strcpy(code, "");
        fgets(code, sizeof code, fptr); // get code
        fclose(fptr);

        if (!strcmp(code, "No EXAM is running"))
        { // code = "No EXAM is running"
            printf("\n\t**%s**\n\n", code);
            ending();
            menu(); // go to menu()
        }

        printf("Enter your id : ");
        fgets(id, sizeof id, stdin);
        id[strcspn(id, "\n")] = '\0';
        fflush(stdin);
        int found = 0;

        strcpy(file, code);
        strcat(file, "Result.txt"); // open codeResult.txt
        fptr = fopen(file, "r");
        do
        {
            fgets(text_file, sizeof text_file, fptr);
            // Start searching for the id
            position = text_file;
            while ((position = strstr(position, id)) != NULL)
            {
                // Check if the match is a whole id
                if (is_id_match(position, id))
                {
                    found = 1;
                    break;
                }
                position += strlen(id); // Move past the current match
            }
        } while (!feof(fptr));
        fclose(fptr);

        if (found)
        { // whole id is not found
            printf("\n\t**You can't participate toice.**\n\n");
            ending();
            menu(); // go to menu()
        }

        strcpy(file, id);
        strcat(file, "Info.txt");
        fptr = fopen(file, "r"); // open idInfo.txt
        if (fptr == NULL)
        { // if file doesn't exist
            printf("\n\t**Register your id.**\n\n");
            ending();
        }
        else // if found
            exam_system(id);

        break;
    case 5:
        sub_heading(main_menu, option);

        fptr = fopen("ResultSubmit.txt", "r");
        // if question is publish, "Result is not Published" will be written in that file
        // else question code will be written
        // after that reading the code, codeResult.txt will opened
        fgets(code, sizeof code, fptr);
        fclose(fptr);

        if (!strcmp(code, "Result is not Published"))
        {
            printf("\n\t**%s**\n\n", code);
            ending();
        }
        else
        {
            strcpy(file, code);
            strcat(file, "Result");
            file_print(file);
            ending();
        }
        break;
    case 6:
        sub_heading(main_menu, option);
        registration();
        break;
    case 7:
        loading("Exiting", "Successfully EXIT. Thank You.");
        exit(0);
        break;
    default:
        menu();
        break;
    }
    menu();
}

int main(int argc, char const *argv[])
{                                           // file for admin pwd
    fptr = fopen("AdminPassword.txt", "r"); // opening
    if (fptr == NULL)
    {                 // if not exist
        fclose(fptr); // close

        fptr = fopen("AdminPassword.txt", "w"); // creqte
        fputs("111111", fptr);                  // default pwd
        fclose(fptr);                           // close

        fptr = fopen("AdminPassword.txt", "r"); // open
    }
    fclose(fptr); // close if file exist
    // file for admin info
    fptr = fopen("AdminInfo.txt", "r");
    if (fptr == NULL)
    {
        fclose(fptr);

        fptr = fopen("AdminInfo.txt", "w");
        fprintf(fptr, " ");
        fclose(fptr);

        fptr = fopen("AdminInfo.txt", "r");
    }
    fclose(fptr);

    fptr = fopen("QuestionSubmit.txt", "r");
    if (fptr == NULL)
    {
        // if question is publish, question code will be written in that file
        // else "No EXAM is running" will be written
        // after that reading the code, code.txt will opened
        fclose(fptr);

        fptr = fopen("QuestionSubmit.txt", "w");
        fprintf(fptr, "No EXAM is running"); // defalut text
        fclose(fptr);

        fptr = fopen("QuestionSubmit.txt", "r");
    }
    fclose(fptr);

    fptr = fopen("ResultSubmit.txt", "r");
    if (fptr == NULL)
    {
        // if question is publish, "Result is not Published" will be written in that file
        // else question code will be written
        // after that reading the code, codeResult.txt will opened
        fclose(fptr);

        fptr = fopen("ResultSubmit.txt", "w");
        fprintf(fptr, "Result is not Published"); // default text(in the first run as no result is to publish)
        fclose(fptr);

        fptr = fopen("ResultSubmit.txt", "r");
    }
    fclose(fptr);
    // file for notice
    fptr = fopen("Notice.txt", "r");
    if (fptr == NULL)
    {
        fclose(fptr);

        fptr = fopen("Notice.txt", "w");
        fprintf(fptr, " ");
        fclose(fptr);

        fptr = fopen("Notice.txt", "r");
    }
    fclose(fptr);

    menu();

    return 0;
}