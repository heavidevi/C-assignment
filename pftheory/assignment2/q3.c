#include<stdio.h>
#include<stdlib.h>


void show_binary(int value) {
    printf("Binary: ");
    for(int i = 2; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf(" (Decimal: %d)", value);
}

void update_sector_status(int sectors[][3]) {
    int row, col;
    printf("Enter sector coordinates:\n");
    printf("Row (0-2): ");
    scanf("%d", &row);
    printf("Column (0-2): ");
    scanf("%d", &col);
    
    if(row < 0 || row > 2) {
        printf("Invalid row! Please enter 0-2 only.\n");
        return;
    }
    if(col < 0 || col > 2) {
        printf("Invalid column! Please enter 0-2 only.\n");
        return;
    }
    
    int bit_position;
    printf("\nSelect status flag to update:\n");
    printf("0: Power Status (1 = ON, 0 = OFF)\n");
    printf("1: Overload Warning (1 = Overloaded, 0 = Normal)\n");
    printf("2: Maintenance Required (1 = Yes, 0 = No)\n");
    printf("Enter flag number (0-2): ");
    scanf("%d", &bit_position);
    
    if(bit_position < 0 || bit_position > 2) {
        printf("Invalid flag! Please enter 0-2 only.\n");
        return;
    }
    
    int action;
    printf("Enter action (1 = SET flag, 0 = CLEAR flag): ");
    scanf("%d", &action);
    
    if(action < 0 || action > 1) {
        printf("Invalid action! Please enter 0 or 1 only.\n");
        return;
    }
    
    
    int mask = (1 << bit_position);
    
    if(action == 1) {
        
        sectors[row][col] |= mask;
        printf("Sector [%d][%d] flag %d SET successfully!\n", row, col, bit_position);
    } else {
        
        sectors[row][col] &= ~mask;
        printf("Sector [%d][%d] flag %d CLEARED successfully!\n", row, col, bit_position);
    }
    
   
    printf("\n--- CURRENT GRID STATUS ---\n");
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d\t", sectors[i][j]);
        }
        printf("\n");
    }
}

void query_sector_status(int sectors[][3]) {
    int row, col;
    printf("Enter sector coordinates to check:\n");
    printf("Row (0-2): ");
    scanf("%d", &row);
    printf("Column (0-2): ");
    scanf("%d", &col);
    
    if(row < 0 || row > 2) {
        printf("Invalid row! Please enter 0-2 only.\n");
        return;
    }
    if(col < 0 || col > 2) {
        printf("Invalid column! Please enter 0-2 only.\n");
        return;
    }
    
    int power_status = (sectors[row][col] >> 0) & 1;        
    int overload_warning = (sectors[row][col] >> 1) & 1;    
    int maintenance_required = (sectors[row][col] >> 2) & 1; 
    
    printf("\n=== SECTOR [%d][%d] STATUS REPORT ===\n", row, col);
    printf("Raw Value: %d\n", sectors[row][col]);
    printf("Power Status: %s\n", power_status ? "ON" : "OFF");
    printf("Overload Warning: %s\n", overload_warning ? "Overloaded" : "Normal");
    printf("Maintenance Required: %s\n", maintenance_required ? "Yes" : "No");
    
    printf("Binary: ");
    for(int i = 2; i >= 0; i--) {
        printf("%d", (sectors[row][col] >> i) & 1);
    }
    printf(" (Bits: 2,1,0)\n");
    printf("================================\n");
}

void run_system_diagnostic(int sectors[][3]) {
    int overload_count = 0;
    int maintenance_count = 0;
    
    printf("\n=== SYSTEM DIAGNOSTIC REPORT ===\n");
    printf("Scanning 3x3 grid using nested loops...\n\n");
    
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            int overload_check = (sectors[i][j] >> 1) & 1;      
            int maintenance_check = (sectors[i][j] >> 2) & 1;  
            
            if(overload_check == 1) {
                overload_count++;
            }
            if(maintenance_check == 1) {
                maintenance_count++;
            }
        }
    }
    
    printf("Total Sectors OVERLOADED: %d\n", overload_count);
    printf("Total Sectors NEEDING Maintenance: %d\n", maintenance_count);
    
    
    printf("\n--- COMPLETE GRID STATUS ---\n");
    printf("   0  1  2\n");
    for(int i = 0; i < 3; i++) {
        printf("%d  ", i);
        for(int j = 0; j < 3; j++) {
            printf("%d  ", sectors[i][j]);
        }
        printf("\n");
    }
    printf("===============================\n");
}

void show_grid_visual(int sectors[][3]) {
    printf("\n--- VISUAL GRID REPRESENTATION ---\n");
    printf("   Col 0  Col 1  Col 2\n");
    for(int i = 0; i < 3; i++) {
        printf("Row %d: ", i);
        for(int j = 0; j < 3; j++) {
            printf("  %d    ", sectors[i][j]);
        }
        printf("\n");
    }
    printf("----------------------------------\n");
}

void show_main_menu() {
    printf("============== IESCO Power Grid Monitoring System ==============\n");
    printf("1. Update Sector Status\n");
    printf("2. Query Sector Status\n"); 
    printf("3. Run System Diagnostic\n");
    printf("4. Show Grid Visual\n");
    printf("5. Exit\n");
    printf("================================================================\n");
    printf("Grid: 3x3 | Bitwise: 0=Power, 1=Overload, 2=Maintenance\n");
    printf("================================================================\n");
    printf("What do you want to do? ");
}



int main() {
    int choice;
    int sectors[3][3] = {0}; 
    
    printf("=== IESCO Power Grid Monitoring System ===\n");
    printf("Islamabad Capital Territory - 3x3 Grid\n");
    printf("Memory Optimized: 1 integer per sector\n\n");
    
    do {
        show_main_menu();
        scanf("%d", &choice);
        while(getchar() != '\n'); 
        
        switch(choice) {
            case 1:
                printf("\n=== UPDATE SECTOR STATUS ===\n");
                update_sector_status(sectors);
                break;
                
            case 2:
                printf("\n=== QUERY SECTOR STATUS ===\n");
                query_sector_status(sectors);
                break;
                
            case 3:
                printf("\n=== SYSTEM DIAGNOSTIC ===\n");
                run_system_diagnostic(sectors);
                break;
                
            case 4:
                printf("\n=== GRID VISUALIZATION ===\n");
                show_grid_visual(sectors);
                break;
                
            case 5:
                printf("\nSystem shutting down... Goodbye!\n");
                break;
                
            default:
                printf("\nInvalid option! Please select 1-5.\n");
                break;
        }
        
        if(choice != 5) {
            printf("\nPress Enter to continue...");
            getchar();
        }
        
    } while(choice != 5);
    
    return 0;
}