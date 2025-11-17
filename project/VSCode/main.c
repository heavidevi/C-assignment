/*******************************************************************************************
*
*   raygui - Simple GUI Example
*   
*   This example demonstrates basic raygui controls
*
********************************************************************************************/

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "../../../raylib/raylib/src/raygui.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raygui - Simple GUI Example");

    // GUI variables for controls
    bool showMessageBox = false;
    bool exitWindow = false;
    
    // Button states
    float sliderValue = 50.0f;
    bool checkboxChecked = false;
    int toggleGroupActive = 0;
    char textBoxText[64] = "Hello raygui!";
    bool textBoxEditMode = false;
    
    // Color picker
    Color colorPickerValue = RED;
    
    // Progress bar
    float progressValue = 0.4f;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose() && !exitWindow)    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Nothing to update for this example
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

            // Draw GUI controls
            //------------------------------------------------------------------------------
            
            // Title
            GuiLabel((Rectangle){ 25, 25, 200, 24 }, "raygui Controls Demo");
            
            // Button
            if (GuiButton((Rectangle){ 25, 60, 120, 30 }, "Click Me!"))
            {
                showMessageBox = true;
            }
            
            // Slider
            GuiLabel((Rectangle){ 25, 100, 60, 24 }, "Slider:");
            GuiSlider((Rectangle){ 90, 100, 120, 24 }, NULL, NULL, &sliderValue, 0.0f, 100.0f);
            GuiLabel((Rectangle){ 220, 100, 60, 24 }, TextFormat("%.1f", sliderValue));
            
            // Checkbox
            GuiCheckBox((Rectangle){ 25, 140, 24, 24 }, "Enable Feature", &checkboxChecked);
            
            // Toggle group
            GuiLabel((Rectangle){ 25, 180, 100, 24 }, "Toggle Group:");
            GuiToggleGroup((Rectangle){ 25, 200, 60, 24 }, "ONE;TWO;THREE", &toggleGroupActive);
            
            // Text box
            GuiLabel((Rectangle){ 25, 240, 100, 24 }, "Text Input:");
            if (GuiTextBox((Rectangle){ 25, 260, 200, 24 }, textBoxText, 64, textBoxEditMode))
            {
                textBoxEditMode = !textBoxEditMode;
            }
            
            // Color picker
            GuiLabel((Rectangle){ 25, 300, 100, 24 }, "Color Picker:");
            GuiColorPicker((Rectangle){ 25, 320, 156, 156 }, NULL, &colorPickerValue);
            
            // Progress bar
            GuiLabel((Rectangle){ 250, 320, 100, 24 }, "Progress Bar:");
            GuiProgressBar((Rectangle){ 250, 340, 200, 24 }, NULL, NULL, &progressValue, 0.0f, 1.0f);
            
            // Color demonstration rectangle
            DrawRectangle(250, 380, 100, 60, colorPickerValue);
            GuiLabel((Rectangle){ 250, 450, 100, 24 }, "Selected Color");
            
            // Info panel
            GuiPanel((Rectangle){ 480, 60, 280, 200 }, "Info Panel");
            GuiLabel((Rectangle){ 490, 90, 260, 24 }, TextFormat("Slider Value: %.1f", sliderValue));
            GuiLabel((Rectangle){ 490, 110, 260, 24 }, TextFormat("Checkbox: %s", checkboxChecked ? "ON" : "OFF"));
            GuiLabel((Rectangle){ 490, 130, 260, 24 }, TextFormat("Toggle: %d", toggleGroupActive));
            GuiLabel((Rectangle){ 490, 150, 260, 24 }, TextFormat("Progress: %.1f%%", progressValue * 100));
            GuiLabel((Rectangle){ 490, 170, 260, 24 }, TextFormat("Text: %s", textBoxText));
            GuiLabel((Rectangle){ 490, 190, 260, 24 }, TextFormat("Color: #%02X%02X%02X", 
                                                                 colorPickerValue.r, 
                                                                 colorPickerValue.g, 
                                                                 colorPickerValue.b));
            
            // Exit button
            if (GuiButton((Rectangle){ screenWidth - 120, screenHeight - 50, 100, 30 }, "Exit"))
            {
                exitWindow = true;
            }
            
            // Message box
            if (showMessageBox)
            {
                int result = GuiMessageBox((Rectangle){ 85, 70, 250, 100 }, "#191#Message", "Button was clicked!", "OK");
                if (result >= 0) showMessageBox = false;
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
