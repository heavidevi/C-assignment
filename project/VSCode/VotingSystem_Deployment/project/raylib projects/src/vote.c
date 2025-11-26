#include "raylib.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h" 

// Define raygui control IDs
#define DEFAULT 0
#define LABEL 1
#define BUTTON 2  
#define PANEL 3 
#define TEXTBOX 4  

// raygui
#define BORDER_COLOR_NORMAL 0
#define BORDER_COLOR_FOCUSED 1
#define BORDER_COLOR_PRESSED 2
#define BACKGROUND_COLOR 3
#define TEXT_COLOR_NORMAL 4
#define TEXT_COLOR_FOCUSED 5
#define TEXT_COLOR_PRESSED 6
#define TEXT_SIZE 7
#define TEXT_SPACING 8

// Global variables for login
char cnicText[14] = "";
char passwordText[12] = "";
bool cnicEditMode = false;
bool passwordEditMode = false;
bool loginClicked = false;
char myString[26];

// Voting system
#define MAX 9 
int candidate_count = 3;
char candidates[MAX][20] = {"Ali", "Rubas", "Burhan"};
int preferences[MAX][MAX];
bool locked[MAX][MAX];
bool loginSuccessful = false;
int selectedPreferences[3] = {-1, -1, -1};
bool votingComplete = false;
bool showLogout = false;
int logoutTimer = 0;

typedef struct
{
    int winner;
    int loser;
} pair;

pair pairs[MAX * (MAX - 1) / 2];
int pair_count = 0;

// Voting functions
bool makecircle(int winner, int loser);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void save_results_to_file(void);
void load_existing_results(void);

bool hasAlreadyVoted(char *cnic);
void addVotedCnic(char *cnic);

int exitvote()
{
    return 0;
}

int preferance()
{
    int screenCenterX = GetScreenWidth() / 2;
    int screenCenterY = GetScreenHeight() / 2;

    // Form dimensions
    int formWidth = 600;
    int formHeight = 400;

    // Centered positions
    int formX = screenCenterX - (formWidth / 2);
    int formY = screenCenterY - (formHeight / 2);

    // Voting panel
    GuiPanel((Rectangle){formX, formY, formWidth, formHeight}, "CAST YOUR VOTE");

    // Instructions
    GuiLabel((Rectangle){formX + 20, formY + 40, 560, 24}, "Select your preferences in order:");

    // 1st Preference
    GuiLabel((Rectangle){formX + 20, formY + 70, 120, 24}, "1st Preference:");
    for (int i = 0; i < candidate_count; i++)
    {
        if (GuiButton((Rectangle){formX + 150 + i * 130, formY + 70, 120, 30},
                      selectedPreferences[0] == i ? TextFormat("[%s]", candidates[i]) : candidates[i]))
        {
            selectedPreferences[0] = i;
        }
    }

    // 2nd Preference
    GuiLabel((Rectangle){formX + 20, formY + 110, 120, 24}, "2nd Preference:");
    for (int i = 0; i < candidate_count; i++)
    {
        if (i != selectedPreferences[0])
        { 
            if (GuiButton((Rectangle){formX + 150 + i * 130, formY + 110, 120, 30},
                          selectedPreferences[1] == i ? TextFormat("[%s]", candidates[i]) : candidates[i]))
            {
                selectedPreferences[1] = i;
            }
        }
    }

    // 3rd Preference
    GuiLabel((Rectangle){formX + 20, formY + 150, 120, 24}, "3rd Preference:");
    for (int i = 0; i < candidate_count; i++)
    {
        if (i != selectedPreferences[0] && i != selectedPreferences[1])
        { 
            if (GuiButton((Rectangle){formX + 150 + i * 130, formY + 150, 120, 30},
                          selectedPreferences[2] == i ? TextFormat("[%s]", candidates[i]) : candidates[i]))
            {
                selectedPreferences[2] = i;
            }
        }
    }

    // Submit button 
    if (selectedPreferences[0] != -1 && selectedPreferences[1] != -1 && selectedPreferences[2] != -1)
    {
        if (GuiButton((Rectangle){formX + 200, formY + 200, 120, 40}, "SUBMIT VOTE"))
        {
            // Record the vote
            record_preferences(selectedPreferences);

            // Save updated results.txt
            save_results_to_file();

            votingComplete = true;
            showLogout = true;
            logoutTimer = 60; // 1 second
        }
    }

    // Display current selections
    GuiLabel((Rectangle){formX + 20, formY + 260, 560, 24},
             TextFormat("Your choices: 1st: %s, 2nd: %s, 3rd: %s",
                        selectedPreferences[0] >= 0 ? candidates[selectedPreferences[0]] : "None",
                        selectedPreferences[1] >= 0 ? candidates[selectedPreferences[1]] : "None",
                        selectedPreferences[2] >= 0 ? candidates[selectedPreferences[2]] : "None"));

    return 0;
}

int checkperson(char *cnic, char *password)
{
    FILE *fptr;
    char *fileCnic, *filePassword;
    fptr = fopen("personinfo.txt", "r");

    if (fptr == NULL)
    {
        printf("Error: Could not open personinfo.txt\n");
        return -1;
    }

    while (fgets(myString, 27, fptr))
    {
        myString[strcspn(myString, "\n")] = 0;

        fileCnic = strtok(myString, "-");
        filePassword = strtok(NULL, "-");

        if (fileCnic != NULL && filePassword != NULL)
        {
            // Decrypt the stored password for comparison
            char *decrypted_password = decrypt_password(filePassword);
            
            printf("File CNIC: %s (len=%d)\n", fileCnic, (int)strlen(fileCnic));
            printf("Decrypted Password: %s (len=%d)\n", decrypted_password, (int)strlen(decrypted_password));
            printf("Input CNIC: %s (len=%d)\n", cnic, (int)strlen(cnic));
            printf("Input Password: %s (len=%d)\n", password, (int)strlen(password));

            if (strlen(fileCnic) == 13 && strlen(decrypted_password) == 11 &&
                strlen(cnic) == 13 && strlen(password) == 11)
            {
                if (strncmp(fileCnic, cnic, 13) == 0 && strncmp(decrypted_password, password, 11) == 0)
                {
                    fclose(fptr);
                    return 1;
                }
            }
        }
    }

    printf("Login failed - CNIC or Password incorrect\n");
    fclose(fptr);
    return 0;
}

bool makecircle(int winner, int loser)
{
    if (winner == loser)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (makecircle(winner, i))
            {
                return true;
            }
        }
    }
    return false;
}

void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i] && i != j)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i] && i != j)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - 1 - i; j++)
        {
            int margin1 = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            int margin2 = preferences[pairs[j + 1].winner][pairs[j + 1].loser] - preferences[pairs[j + 1].loser][pairs[j + 1].winner];
            if (margin1 < margin2)
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
}

void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!makecircle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool isWinner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                isWinner = false;
                break;
            }
        }
        if (isWinner)
        {
            printf("Winner: %s\n", candidates[i]);
            return;
        }
    }
}

// Load existing voting results from file
void load_existing_results(void)
{
    FILE *fptr = fopen("results.txt", "r");
    if (fptr == NULL)
    {
        // File doesn't exist yet, initialize with zeros
        for (int i = 0; i < MAX; i++)
        {
            for (int j = 0; j < MAX; j++)
            {
                preferences[i][j] = 0;
                locked[i][j] = false;
            }
        }
        pair_count = 0;
        return;
    }

    // Read preferences matrix
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            fscanf(fptr, "%d", &preferences[i][j]);
        }
    }

    fclose(fptr);

    // Reset locked array and pair_count for fresh calculation
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            locked[i][j] = false;
        }
    }
    pair_count = 0;
}

// Save current results to file 
void save_results_to_file(void)
{
    // Recalculate winner 
    add_pairs();
    sort_pairs();
    lock_pairs();

    FILE *fptr = fopen("results.txt", "w");
    if (fptr == NULL)
    {
        printf("Error: Could not create results.txt\n");
        return;
    }

    // Save preferences matrix
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            fprintf(fptr, "%d ", preferences[i][j]);
        }
        fprintf(fptr, "\n");
    }

    fclose(fptr);

    // Winner file
    fptr = fopen("current_winner.txt", "w");
    if (fptr == NULL)
    {
        printf("Error: Could not create current_winner.txt\n");
        return;
    }

    // Calculate total votes
    int totalVotes = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j)
            {
                totalVotes += preferences[i][j];
            }
        }
    }
    totalVotes = totalVotes / (candidate_count - 1); // Each vote counts

    fprintf(fptr, "=== CURRENT ELECTION WINNER ===\n\n");
    fprintf(fptr, "Total Votes Cast: %d\n\n", totalVotes);

    // Find and display current winner
    bool foundWinner = false;
    for (int i = 0; i < candidate_count; i++)
    {
        bool isWinner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                isWinner = false;
                break;
            }
        }
        if (isWinner)
        {
            fprintf(fptr, "CURRENT WINNER: %s\n\n", candidates[i]);
            foundWinner = true;
            break;
        }
    }

    if (!foundWinner)
    {
        fprintf(fptr, "CURRENT STATUS: TIE - NO CLEAR WINNER\n\n");
    }

    // Timestamp
    fprintf(fptr, "\nLast Updated: ");
    time_t now = time(0);
    char *timeStr = ctime(&now);
    fprintf(fptr, "%s", timeStr);

    fclose(fptr);
    printf("Results saved to results.txt and current_winner.txt\n");
}

// CNIC has already voted
bool hasAlreadyVoted(char *cnic)
{
    FILE *fptr = fopen("voted.txt", "r");
    char votedCnic[15];

    if (fptr == NULL)
    {

        return false;
    }

    // Read each CNICc
    while (fgets(votedCnic, sizeof(votedCnic), fptr))
    {

        votedCnic[strcspn(votedCnic, "\n")] = 0;

        // Compare withCNIC
        if (strncmp(votedCnic, cnic, 13) == 0)
        {
            fclose(fptr);
            return true;
        }
    }

    fclose(fptr);
    return false; // Not voted
}

// Add a CNIC to voted.txt
void addVotedCnic(char *cnic)
{
    FILE *fptr = fopen("voted.txt", "a");

    if (fptr == NULL)
    {
        printf("Error: Could not open voted.txt for writing\n");
        return;
    }

    // Append the CNIC
    fprintf(fptr, "%.13s", cnic);
    fclose(fptr);
    printf("CNIC %s added to voted list\n", cnic);
}

int login()
{
    int screenCenterX = GetScreenWidth() / 2;
    int screenCenterY = GetScreenHeight() / 2;

    // Form dimensions
    int formWidth = 500;
    int formHeight = 250;
    int inputWidth = 200;
    int inputHeight = 30;

    // centered
    int formX = screenCenterX - (formWidth / 2);
    int formY = screenCenterY - (formHeight / 2);

    //gradient header label
int headerHeight = 40;
DrawRectangleGradientH(formX, formY - headerHeight, formWidth, headerHeight,
                       (Color){0, 255, 255, 255},
                       (Color){0, 128, 128, 255});
GuiLabel((Rectangle){formX + 10, formY - headerHeight + 8, formWidth, 24}, "LOGIN");

//form panel 
GuiPanel((Rectangle){formX, formY, formWidth, formHeight}, "");

    // CNIC input
    GuiLabel((Rectangle){formX + 20, formY + 40, 80, 24}, "CNIC:");
    if (GuiTextBox((Rectangle){formX + 100, formY + 40, inputWidth, inputHeight}, cnicText, 14, cnicEditMode))
    {
        cnicEditMode = !cnicEditMode;
    }

    // Password input
    GuiLabel((Rectangle){formX + 20, formY + 80, 80, 24}, "PASSWORD:");
    if (GuiTextBox((Rectangle){formX + 100, formY + 80, inputWidth, inputHeight}, passwordText, 12, passwordEditMode))
    {
        passwordEditMode = !passwordEditMode;
    }

    // Login button
    if (GuiButton((Rectangle){formX + 100, formY + 120, 100, 30}, "LOGIN"))
    {
        loginClicked = true;

        // Check credentials
        int loginResult = checkperson(cnicText, passwordText);

        if (loginResult == 1)
        {
            // Credentials are correct, now check if already voted
            if (hasAlreadyVoted(cnicText))
            {
                loginSuccessful = false;
            }
            else
            {
                // Valid login and hasn't voted yet
                loginSuccessful = true;

                // Load existing results instead of resetting
                load_existing_results();
            }
        }
        else
        {
            // Wrong credentials
            loginSuccessful = false;
        }
    }

    //error messages
    if (loginClicked && !loginSuccessful)
    {
        if (hasAlreadyVoted(cnicText))
        {
            GuiLabel((Rectangle){formX + 20, formY + 160, 460, 30}, "ERROR: You have already voted!");
        }
        else
        {
            GuiLabel((Rectangle){formX + 20, formY + 160, 460, 30}, "Login failed! Check your credentials");
        }
    }

    return 0;
}
void SetupGUIColors()
{
    GuiSetStyle(DEFAULT, BACKGROUND_COLOR, 0x00000000); // Transparent

    GuiSetStyle(PANEL, BORDER_COLOR_NORMAL, 0x7F7FFF88); // Soft purple border
    GuiSetStyle(PANEL, BACKGROUND_COLOR, 0x4B367CFF);    // Deep purple bg
    GuiSetStyle(PANEL, TEXT_COLOR_NORMAL, 0xE6E6FAFF);   // Light lavender

    GuiSetStyle(LABEL, TEXT_COLOR_NORMAL, 0xA2CFFEFF); // Pastel blue labels
    GuiSetStyle(LABEL, TEXT_SIZE, 16);

    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x008080FF);  // Teal border
    GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, 0x00FFFFFF); // Cyan border on focus
    GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED, 0x00008BFF); // Dark blue pressed border
    GuiSetStyle(BUTTON, BACKGROUND_COLOR, 0x008080FF);     // Teal background
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xFFFFFFFF);    // White text
    GuiSetStyle(BUTTON, TEXT_SIZE, 16);

    GuiSetStyle(TEXTBOX, BORDER_COLOR_NORMAL, 0x40E0D0FF);  // Turquoise border
    GuiSetStyle(TEXTBOX, BORDER_COLOR_FOCUSED, 0x00CED1FF); // Dark turquoise border focused
    GuiSetStyle(TEXTBOX, BACKGROUND_COLOR, 0x202838FF);     // Dark teal box bg
    GuiSetStyle(TEXTBOX, TEXT_COLOR_NORMAL, 0xE0FFFFFA);    // Pale cyan text
}

//encryption/decryption 
char* encrypt_password(char* password) {
    static char encrypted[12];
    for (int i = 0; i < 11; i++) {
        if (password[i] >= '0' && password[i] <= '9') {
           
            encrypted[i] = ((password[i] - '0' + 1) % 10) + '0';
        } else {
            encrypted[i] = password[i];
        }
    }
    encrypted[11] = '\0';
    return encrypted;
}

char* decrypt_password(char* encrypted_password) {
    static char decrypted[12];
    for (int i = 0; i < 11; i++) {
        if (encrypted_password[i] >= '0' && encrypted_password[i] <= '9') {
            // Reverse Caesar cipher
            int digit = encrypted_password[i] - '0';
            decrypted[i] = ((digit - 1 + 10) % 10) + '0';
        } else {
            decrypted[i] = encrypted_password[i];
        }
    }
    decrypted[11] = '\0';
    return decrypted;
}

int main(void)
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Voting System");
    ToggleFullscreen();
    SetTargetFPS(60);

    SetupGUIColors();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        // Draw vertical gradient background
       DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(),
                       (Color){18, 23, 42, 255}, (Color){47, 30, 79, 255});

        if (showLogout)
        {
            //logout message
            int centerX = GetScreenWidth() / 2;
            int centerY = GetScreenHeight() / 2;
            
            // Header label

            GuiPanel((Rectangle){centerX - 200, centerY - 50, 400, 100}, "VOTE SUBMITTED");
            GuiLabel((Rectangle){centerX - 180, centerY - 20, 360, 24},
                     TextFormat("Thank you for voting! Logging out in %.0f seconds...", logoutTimer / 60.0f));

            logoutTimer--;
            if (logoutTimer <= 0)
            {
                // Add CNIC to voted list
                if (!hasAlreadyVoted(cnicText))
                {
                    addVotedCnic(cnicText);
                }

                // Reset everything
                showLogout = false;
                loginSuccessful = false;
                votingComplete = false;
                loginClicked = false;
                selectedPreferences[0] = selectedPreferences[1] = selectedPreferences[2] = -1;
                strcpy(cnicText, "");
                strcpy(passwordText, "");
            }
        }
        else if (!loginSuccessful)
        {
            //login screen
            login();
        }
        else if (!votingComplete)
        {
            //voting screen
            preferance();
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
