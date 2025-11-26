#include "raylib.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define RAYGUI_IMPLEMENTATION
#include "../../../raylib/raylib/src/raygui.h"


// Global variables for login
char cnicText[14] = ""; 
char passwordText[12] = "";    
bool cnicEditMode = false;
bool passwordEditMode = false;
bool loginClicked = false;  
char myString[26];

// Voting system variables
#define MAX 9
int candidate_count = 3;
char candidates[MAX][20] = {"Alice", "Bob", "Charlie"}; 
int preferences[MAX][MAX];
bool locked[MAX][MAX];
bool loginSuccessful = false;
int selectedPreferences[3] = {-1, -1, -1}; 
bool votingComplete = false;
bool showLogout = false;
int logoutTimer = 0;

typedef struct {
    int winner;
    int loser;
} pair;

pair pairs[MAX * (MAX - 1) / 2];
int pair_count = 0;

// Voting logic functions
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

int exitvote(){
    return 0;
}

int preferance(){
    int screenCenterX = GetScreenWidth() / 2;
    int screenCenterY = GetScreenHeight() / 2;
    
    // Balanced form dimensions
    int formWidth = 1000;
    int formHeight = 650;
    
    // Centered positions
    int formX = screenCenterX - (formWidth / 2);
    int formY = screenCenterY - (formHeight / 2);
    
    // Draw custom background and title for voting panel
    DrawRectangle(formX, formY, formWidth, formHeight, (Color){240, 248, 255, 255}); // Light background
    DrawRectangleLines(formX, formY, formWidth, formHeight, (Color){70, 130, 180, 255}); // Border
    
    // Title bar
    DrawRectangle(formX, formY, formWidth, 50, (Color){70, 130, 180, 255}); // Title background
    DrawText("CAST YOUR VOTE", formX + 20, formY + 15, 28, WHITE);
    
    // Main instruction with simple clean font
    DrawText("Select your preferences in order:", formX + 50, formY + 70, 26, (Color){25, 25, 112, 255});
    
    // Button dimensions
    int buttonWidth = 240;
    int buttonHeight = 70;
    int buttonSpacing = 280;
    int startX = formX + 80;
    
    // 1st Preference Section with simple font
    DrawText("1st Choice (Gold):", formX + 50, formY + 110, 24, (Color){25, 25, 112, 255});
    
    for (int i = 0; i < candidate_count; i++) {
        Rectangle buttonRect = { startX + i * buttonSpacing, formY + 150, buttonWidth, buttonHeight };
        
        // Set button color based on selection
        if (selectedPreferences[0] == i) {
            // Selected button - Gold with black text for 1st choice
            GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt((Color){255, 215, 0, 255}));  // Gold
            GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
            GuiSetStyle(BUTTON, BORDER_WIDTH, 4);
            GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt((Color){218, 165, 32, 255})); // Goldenrod
        } else {
            // Normal button - Light blue
            GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt((Color){173, 216, 230, 255})); // Light Blue
            GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
            GuiSetStyle(BUTTON, BORDER_WIDTH, 2);
            GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt((Color){100, 149, 237, 255})); // Cornflower Blue
        }
        
        GuiSetStyle(BUTTON, TEXT_SIZE, 20);
        if (GuiButton(buttonRect, TextFormat("%s%s", 
                      selectedPreferences[0] == i ? "* " : "", candidates[i]))) {
            selectedPreferences[0] = i;
        }
    }
    
    // 2nd Preference Section with simple font
    DrawText("2nd Choice (Silver):", formX + 50, formY + 250, 24, (Color){25, 25, 112, 255});
    
    for (int i = 0; i < candidate_count; i++) {
        if (i != selectedPreferences[0]) { // Can't select same as 1st
            Rectangle buttonRect = { startX + i * buttonSpacing, formY + 290, buttonWidth, buttonHeight };
            
            // Set button color based on selection
            if (selectedPreferences[1] == i) {
                // Selected button - Silver with black text for 2nd choice
                GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt((Color){192, 192, 192, 255}));  // Silver
                GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
                GuiSetStyle(BUTTON, BORDER_WIDTH, 4);
                GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt((Color){169, 169, 169, 255})); // Dark Gray
            } else {
                // Normal button - Light Orange
                GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt((Color){255, 218, 185, 255})); // Peach Puff
                GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
                GuiSetStyle(BUTTON, BORDER_WIDTH, 2);
                GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt((Color){255, 165, 0, 255})); // Orange
            }
            
            GuiSetStyle(BUTTON, TEXT_SIZE, 20);
            if (GuiButton(buttonRect, TextFormat("%s%s", 
                          selectedPreferences[1] == i ? "* " : "", candidates[i]))) {
                selectedPreferences[1] = i;
            }
        } else {
            // Disabled button for already selected candidate
            Rectangle buttonRect = { startX + i * buttonSpacing, formY + 290, buttonWidth, buttonHeight };
            GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(LIGHTGRAY));
            GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(GRAY));
            GuiSetStyle(BUTTON, BORDER_WIDTH, 1);
            GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(GRAY));
            GuiSetStyle(BUTTON, TEXT_SIZE, 18);
            GuiButton(buttonRect, TextFormat("X %s", candidates[i])); // Non-clickable
        }
    }
    
    // 3rd Preference Section with simple font
    DrawText("3rd Choice (Bronze):", formX + 50, formY + 390, 24, (Color){25, 25, 112, 255});
    
    for (int i = 0; i < candidate_count; i++) {
        if (i != selectedPreferences[0] && i != selectedPreferences[1]) { // Can't select same as 1st or 2nd
            Rectangle buttonRect = { startX + i * buttonSpacing, formY + 430, buttonWidth, buttonHeight };
            
            // Set button color based on selection
            if (selectedPreferences[2] == i) {
                // Selected button - Bronze with black text for 3rd choice
                GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt((Color){205, 127, 50, 255}));  // Bronze
                GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
                GuiSetStyle(BUTTON, BORDER_WIDTH, 4);
                GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt((Color){160, 82, 45, 255})); // Saddle Brown
            } else {
                // Normal button - Light Purple
                GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt((Color){221, 160, 221, 255})); // Plum
                GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
                GuiSetStyle(BUTTON, BORDER_WIDTH, 2);
                GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt((Color){186, 85, 211, 255})); // Medium Orchid
            }
            
            GuiSetStyle(BUTTON, TEXT_SIZE, 20);
            if (GuiButton(buttonRect, TextFormat("%s%s", 
                          selectedPreferences[2] == i ? "* " : "", candidates[i]))) {
                selectedPreferences[2] = i;
            }
        } else {
            // Disabled button for already selected candidate
            Rectangle buttonRect = { startX + i * buttonSpacing, formY + 430, buttonWidth, buttonHeight };
            GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(LIGHTGRAY));
            GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(GRAY));
            GuiSetStyle(BUTTON, BORDER_WIDTH, 1);
            GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(GRAY));
            GuiSetStyle(BUTTON, TEXT_SIZE, 18);
            GuiButton(buttonRect, TextFormat("X %s", candidates[i])); // Non-clickable
        }
    }
    
    // Submit button
    Rectangle submitRect = { formX + 350, formY + 540, 300, 60 };
    if (selectedPreferences[0] != -1 && selectedPreferences[1] != -1 && selectedPreferences[2] != -1) {
        // Active submit button - Green
        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt((Color){34, 139, 34, 255})); // Forest Green
        GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
        GuiSetStyle(BUTTON, BORDER_WIDTH, 3);
        GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(DARKGREEN));
        GuiSetStyle(BUTTON, TEXT_SIZE, 24);
        
        if (GuiButton(submitRect, "SUBMIT VOTE")) {
            // Record the vote
            record_preferences(selectedPreferences);
            
            // Save updated results to file
            save_results_to_file();
            
            votingComplete = true;
            showLogout = true;
            logoutTimer = 60; // 1 second 
        }
    } else {
        // Inactive submit button - Gray
        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(LIGHTGRAY));
        GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(GRAY));
        GuiSetStyle(BUTTON, BORDER_WIDTH, 2);
        GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(GRAY));
        GuiSetStyle(BUTTON, TEXT_SIZE, 20);
        GuiButton(submitRect, "Complete all choices first"); // Non-clickable
    }
    
    // Display current selections with simple clean font
    DrawText(TextFormat("Selections: 1st: %s | 2nd: %s | 3rd: %s",
                       selectedPreferences[0] >= 0 ? candidates[selectedPreferences[0]] : "None",
                       selectedPreferences[1] >= 0 ? candidates[selectedPreferences[1]] : "None",
                       selectedPreferences[2] >= 0 ? candidates[selectedPreferences[2]] : "None"),
             formX + 50, formY + 520, 20, (Color){70, 70, 70, 255});
    
    return 0;
}


int checkperson(char *cnic, char *password){
    FILE *fptr;
    char *fileCnic, *filePassword;
    fptr = fopen("personinfo.txt", "r");

    if (fptr == NULL) {
        printf("Error: Could not open personinfo.txt\n");
        return -1; 
    }

 
    while(fgets(myString, 27, fptr)) {
       
        myString[strcspn(myString, "\n")] = 0;
        
        
        fileCnic = strtok(myString, "-");
        filePassword = strtok(NULL, "-");
        
        if (fileCnic != NULL && filePassword != NULL) {
            printf("File CNIC: %s (len=%d)\n", fileCnic, (int)strlen(fileCnic));
            printf("File Password: %s (len=%d)\n", filePassword, (int)strlen(filePassword));
            printf("Input CNIC: %s (len=%d)\n", cnic, (int)strlen(cnic));
            printf("Input Password: %s (len=%d)\n", password, (int)strlen(password));
            
           
            if (strlen(fileCnic) == 13 && strlen(filePassword) == 11 && 
                strlen(cnic) == 13 && strlen(password) == 11) {
                if (strncmp(fileCnic, cnic, 13) == 0 && strncmp(filePassword, password, 11) == 0) {
                    
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


bool makecircle(int winner, int loser) {
    if (winner == loser) {
        return true;
    }
    
    for (int i = 0; i < candidate_count; i++) {
        if (locked[loser][i]) {
            if (makecircle(winner, i)) {
                return true;
            }
        }
    }
    return false;
}

void record_preferences(int ranks[]) {
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

void add_pairs(void) {
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            if (preferences[i][j] > preferences[j][i] && i != j) {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i] && i != j) {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

void sort_pairs(void) {
    for (int i = 0; i < pair_count - 1; i++) {
        for (int j = 0; j < pair_count - 1 - i; j++) {
            int margin1 = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            int margin2 = preferences[pairs[j+1].winner][pairs[j+1].loser] - preferences[pairs[j+1].loser][pairs[j+1].winner];
            if (margin1 < margin2) {
                pair temp = pairs[j];
                pairs[j] = pairs[j+1];
                pairs[j+1] = temp;
            }
        }
    }
}

void lock_pairs(void) {
    for (int i = 0; i < pair_count; i++) {
        if (!makecircle(pairs[i].winner, pairs[i].loser)) {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

void print_winner(void) {
    for (int i = 0; i < candidate_count; i++) {
        bool isWinner = true;
        for (int j = 0; j < candidate_count; j++) {
            if (locked[j][i]) {
                isWinner = false;
                break;
            }
        }
        if (isWinner) {
            printf("Winner: %s\n", candidates[i]);
            return;
        }
    }
}

// Load existing voting results from file
void load_existing_results(void) {
    FILE *fptr = fopen("results.txt", "r");
    if (fptr == NULL) {
        // File doesn't exist yet, initialize with zeros
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                preferences[i][j] = 0;
                locked[i][j] = false;
            }
        }
        pair_count = 0;
        return;
    }
    
    // Read preferences matrix
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            fscanf(fptr, "%d", &preferences[i][j]);
        }
    }
    
    fclose(fptr);
    
    // Reset locked array and pair_count for fresh calculation
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            locked[i][j] = false;
        }
    }
    pair_count = 0;
}

// Save current results to file with detailed information
void save_results_to_file(void) {
    // Recalculate winner using Tideman method first
    add_pairs();
    sort_pairs();
    lock_pairs();
    
    FILE *fptr = fopen("results.txt", "w");
    if (fptr == NULL) {
        printf("Error: Could not create results.txt\n");
        return;
    }
    
    // Save preferences matrix (for loading next time)
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            fprintf(fptr, "%d ", preferences[i][j]);
        }
        fprintf(fptr, "\n");
    }
    
    fclose(fptr);
    
    // Create a simple winner file that overwrites each time
    fptr = fopen("current_winner.txt", "w");
    if (fptr == NULL) {
        printf("Error: Could not create current_winner.txt\n");
        return;
    }
    
    // Calculate total votes
    int totalVotes = 0;
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            if (i != j) {
                totalVotes += preferences[i][j];
            }
        }
    }
    totalVotes = totalVotes / (candidate_count - 1); // Each vote counts (candidate_count-1) times
    
    fprintf(fptr, "=== CURRENT ELECTION WINNER ===\n\n");
    fprintf(fptr, "Total Votes Cast: %d\n\n", totalVotes);
    
    // Find and display current winner
    bool foundWinner = false;
    for (int i = 0; i < candidate_count; i++) {
        bool isWinner = true;
        for (int j = 0; j < candidate_count; j++) {
            if (locked[j][i]) {
                isWinner = false;
                break;
            }
        }
        if (isWinner) {
            fprintf(fptr, "CURRENT WINNER: %s\n\n", candidates[i]);
            foundWinner = true;
            break;
        }
    }
    
    if (!foundWinner) {
        fprintf(fptr, "CURRENT STATUS: TIE - NO CLEAR WINNER\n\n");
    }
    
    // Add timestamp
    fprintf(fptr, "\nLast Updated: ");
    time_t now = time(0);
    char* timeStr = ctime(&now);
    fprintf(fptr, "%s", timeStr);
    
    fclose(fptr);
    printf("Results saved to results.txt and current_winner.txt\n");
}

// Check if a CNIC has already voted
bool hasAlreadyVoted(char *cnic) {
    FILE *fptr = fopen("voted.txt", "r");
    char votedCnic[15];
    
    if (fptr == NULL) {
     
        return false;
    }
    
    // Read each CNIC from the file
    while (fgets(votedCnic, sizeof(votedCnic), fptr)) {
        
        votedCnic[strcspn(votedCnic, "\n")] = 0;

        // Compare with input CNIC
        if (strncmp(votedCnic, cnic, 13) == 0) {
            fclose(fptr);
            return true; 
        }
    }
    
    fclose(fptr);
    return false; // Not voted
}

// Add a CNIC to the voted list
void addVotedCnic(char *cnic) {
    FILE *fptr = fopen("voted.txt", "a");
    
    if (fptr == NULL) {
        printf("Error: Could not open voted.txt for writing\n");
        return;
    }
    
    // Append the CNIC with newline
    fprintf(fptr, "%.13s\n", cnic);
    fclose(fptr);
    printf("CNIC %s added to voted list\n", cnic);
}


int login(){
    int screenCenterX = GetScreenWidth() / 2;
    int screenCenterY = GetScreenHeight() / 2;
    
    // Enhanced form dimensions for better visibility
    int formWidth = 800;
    int formHeight = 450;
    int inputWidth = 280;
    int inputHeight = 50;
    
    // Centered positions
    int formX = screenCenterX - (formWidth / 2);
    int formY = screenCenterY - (formHeight / 2);
    
    // Draw custom background for the form area without overlapping panel
    DrawRectangle(formX, formY, formWidth, formHeight, (Color){240, 248, 255, 255}); // Alice Blue background
    DrawRectangleLines(formX, formY, formWidth, formHeight, (Color){70, 130, 180, 255}); // Steel Blue border
    
    // Draw title manually instead of using GuiPanel to avoid input blocking
    DrawRectangle(formX, formY, formWidth, 45, (Color){70, 130, 180, 255}); // Slightly taller title bar
    DrawText("SECURE LOGIN PORTAL", formX + 20, formY + 12, 26, WHITE);
    
    // Welcome message with enhanced font styling
    DrawText("Welcome to Electronic Voting System", formX + 50, formY + 65, 28, (Color){25, 25, 112, 255});
    DrawText("Please enter your credentials to continue", formX + 50, formY + 100, 22, (Color){70, 70, 70, 255});
    
    // CNIC input section with enhanced visibility and better fonts
    DrawText("CNIC Number:", formX + 50, formY + 150, 24, (Color){25, 25, 112, 255});
    DrawText("Enter 13 digits without dashes", formX + 50, formY + 175, 20, (Color){100, 100, 100, 255});
    
    // Clear any conflicting styles and use minimal textbox styling
    GuiSetStyle(TEXTBOX, TEXT_SIZE, 0);
    GuiSetStyle(TEXTBOX, BORDER_WIDTH, 0);
    GuiSetStyle(TEXTBOX, BORDER_COLOR_NORMAL, 0);
    GuiSetStyle(TEXTBOX, BASE_COLOR_NORMAL, 0);
    GuiSetStyle(TEXTBOX, TEXT_COLOR_NORMAL, 0);
    
    // CNIC textbox with minimal interference
    Rectangle cnicRect = { formX + 50, formY + 205, inputWidth, inputHeight };
    if (GuiTextBox(cnicRect, cnicText, 14, cnicEditMode))
    {
        cnicEditMode = !cnicEditMode;
    }
    
    // Draw custom border around CNIC textbox for better visibility
    if (cnicEditMode) {
        DrawRectangleLines(cnicRect.x - 2, cnicRect.y - 2, cnicRect.width + 4, cnicRect.height + 4, (Color){30, 144, 255, 255});
    } else {
        DrawRectangleLines(cnicRect.x - 1, cnicRect.y - 1, cnicRect.width + 2, cnicRect.height + 2, (Color){70, 130, 180, 255});
    }

    // Password input section with enhanced font sizing
    DrawText("Password:", formX + 420, formY + 150, 24, (Color){25, 25, 112, 255});
    DrawText("Enter 11 digit password", formX + 420, formY + 175, 20, (Color){100, 100, 100, 255});
    
    // Password textbox with same minimal styling
    Rectangle passwordRect = { formX + 420, formY + 205, inputWidth, inputHeight };
    if (GuiTextBox(passwordRect, passwordText, 12, passwordEditMode))
    {
        passwordEditMode = !passwordEditMode;
    }
    
    // Draw custom border around Password textbox for better visibility
    if (passwordEditMode) {
        DrawRectangleLines(passwordRect.x - 2, passwordRect.y - 2, passwordRect.width + 4, passwordRect.height + 4, (Color){30, 144, 255, 255});
    } else {
        DrawRectangleLines(passwordRect.x - 1, passwordRect.y - 1, passwordRect.width + 2, passwordRect.height + 2, (Color){70, 130, 180, 255});
    }
    
    // Enhanced Login button with proper styling
    Rectangle loginButtonRect = { formX + 320, formY + 280, 160, 55 };
    
    // Set button styles only when needed
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt((Color){70, 130, 180, 255}));
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
    GuiSetStyle(BUTTON, TEXT_SIZE, 20);
    
    if (GuiButton(loginButtonRect, "LOGIN"))
    {
        loginClicked = true;  
        
        // First check if credentials are correct
        int loginResult = checkperson(cnicText, passwordText);
        
        if (loginResult == 1) {
            // Credentials are correct, now check if already voted
            if (hasAlreadyVoted(cnicText)) {
                loginSuccessful = false;
            } else {
                // Valid login and hasn't voted yet
                loginSuccessful = true;
                
                // Load existing results instead of resetting
                load_existing_results();
            }
        } else {
            // Wrong credentials
            loginSuccessful = false;
        }
    }
    
    // Enhanced error messages using DrawText to avoid GUI style conflicts
    if (loginClicked && !loginSuccessful)
    {
        if (hasAlreadyVoted(cnicText)) {
            DrawText("ERROR: You have already voted!", formX + 50, formY + 350, 20, (Color){220, 20, 60, 255});
        } else {
            DrawText("Login failed! Please check your credentials", formX + 50, formY + 350, 20, (Color){220, 20, 60, 255});
        }
    }
    
    return 0;
}



int main()
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Voting System");
    ToggleFullscreen();  
    SetTargetFPS(60);
    
    // Load better fonts with enhanced quality - try multiple font options
    Font customFont = {0};
    
    // Try loading fonts in order of preference with better quality settings
    customFont = LoadFontEx("C:/Windows/Fonts/segoeui.ttf", 32, 0, 250);     // Segoe UI - modern Windows font
    if (customFont.texture.id == 0) {
        customFont = LoadFontEx("C:/Windows/Fonts/calibri.ttf", 32, 0, 250);   // Calibri - clean modern font
    }
    if (customFont.texture.id == 0) {
        customFont = LoadFontEx("C:/Windows/Fonts/arial.ttf", 32, 0, 250);     // Arial fallback
    }
    if (customFont.texture.id == 0) {
        customFont = LoadFontEx("C:/Windows/Fonts/tahoma.ttf", 32, 0, 250);    // Tahoma - very clean
    }
    
    // Apply enhanced font if successfully loaded
    if (customFont.texture.id != 0) {
        GuiSetFont(customFont);
        // Set smooth text rendering
        SetTextureFilter(customFont.texture, TEXTURE_FILTER_BILINEAR);
    }
    
    // Set global GUI style for better appearance and consistency
    GuiSetStyle(DEFAULT, TEXT_SIZE, 22);                    // Slightly larger for better readability
    GuiSetStyle(DEFAULT, BORDER_WIDTH, 1);
    GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
    GuiSetStyle(DEFAULT, TEXT_SPACING, 2);                  // Better character spacing
    GuiSetStyle(BUTTON, BORDER_WIDTH, 2);
    GuiSetStyle(BUTTON, TEXT_SIZE, 20);                     // Consistent button text size
    GuiSetStyle(TEXTBOX, BORDER_WIDTH, 2);
    GuiSetStyle(TEXTBOX, TEXT_SIZE, 20);                    // Good textbox text size
    
    // Set enhanced text rendering for better quality
    SetTextLineSpacing(26);                                 // Better line spacing
    
    SetTargetFPS(60); 

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

            if (showLogout) {
                // Enhanced logout message and countdown
                int centerX = GetScreenWidth() / 2;
                int centerY = GetScreenHeight() / 2;
                
                // Draw success panel with clean background
                DrawRectangle(centerX - 300, centerY - 80, 600, 160, (Color){240, 248, 255, 255});
                DrawRectangleLines(centerX - 300, centerY - 80, 600, 160, (Color){70, 130, 180, 255});
                
                // Title bar for success message
                DrawRectangle(centerX - 300, centerY - 80, 600, 40, (Color){34, 139, 34, 255}); // Green background
                DrawText("VOTE SUBMITTED SUCCESSFULLY", centerX - 280, centerY - 65, 24, WHITE);
                
                // Thank you message with simple font
                DrawText("Thank you for participating in the democratic process!", 
                         centerX - 280, centerY - 30, 22, (Color){25, 25, 112, 255});
                
                // Countdown message with simple styling
                DrawText(TextFormat("Automatically logging out in %.1f seconds...", logoutTimer / 60.0f),
                         centerX - 280, centerY - 5, 20, (Color){70, 70, 70, 255});
                
                // Progress bar for countdown
                float progress = (60.0f - logoutTimer) / 60.0f;
                Rectangle progressRect = { centerX - 200, centerY + 25, 400, 20 };
                DrawRectangle(progressRect.x, progressRect.y, progressRect.width, progressRect.height, LIGHTGRAY);
                DrawRectangle(progressRect.x, progressRect.y, progressRect.width * progress, progressRect.height, GREEN);
                DrawRectangleLines(progressRect.x, progressRect.y, progressRect.width, progressRect.height, DARKGREEN);
                
                logoutTimer--;
                if (logoutTimer <= 0) {
                    // Add CNIC to voted list before logging out (only once)
                    if (!hasAlreadyVoted(cnicText)) {
                        addVotedCnic(cnicText);
                    }
                    
                    // Reset everything for next voter
                    showLogout = false;
                    loginSuccessful = false;
                    votingComplete = false;
                    loginClicked = false;
                    selectedPreferences[0] = selectedPreferences[1] = selectedPreferences[2] = -1;
                    strcpy(cnicText, "");
                    strcpy(passwordText, "");
                }
            }
            else if (!loginSuccessful) {
                // Show login screen
                login();
            }
            else if (!votingComplete) {
                // Show voting screen
                preferance();
            }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}