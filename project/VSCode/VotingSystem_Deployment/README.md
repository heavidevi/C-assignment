# Voting System - Preference-Based Election

## Overview
This is a secure voting system that implements the **Tideman method** (ranked pairs) for preference-based voting. Voters can select their 1st, 2nd, and 3rd choice candidates, and the system determines the winner using advanced election algorithms.

## Features
- **Secure Login**: CNIC and password authentication
- **Duplicate Prevention**: Prevents users from voting multiple times
- **Preference Voting**: Rank candidates in order of preference
- **Real-time Results**: Current winner updates after each vote
- **Full-screen Interface**: Professional voting experience

## System Requirements
- Windows 10/11 (64-bit)
- No additional software installation required

## How to Use

### For Voters:
1. Run `vote.exe`
2. Enter your 13-digit CNIC and 11-digit password
3. Select your preferences (1st, 2nd, 3rd choice)
4. Submit your vote
5. System will automatically log you out

### For Election Officials:
- Check `current_winner.txt` for real-time election results
- `voted.txt` contains list of CNICs that have voted
- `results.txt` contains detailed voting data

## Files Required:
- `vote.exe` - Main voting application
- `personinfo.txt` - Valid voter credentials (CNIC-Password format)
- `current_winner.txt` - Shows current election winner (auto-generated)
- `results.txt` - Detailed voting results (auto-generated)
- `voted.txt` - List of voters who have cast votes (auto-generated)

## Setup Instructions:
1. Create `personinfo.txt` with valid voter credentials in format:
   ```
   1234567890123-12345678901
   9876543210987-09876543210
   ```
   (13 digits CNIC - 11 digits Password)

2. Run `vote.exe` to start the voting system

## Security Features:
- CNIC/Password validation
- One vote per person enforcement
- Encrypted preference recording
- Tamper-resistant result calculation

## Candidate Configuration:
Current candidates: Alice, Bob, Charlie
(Can be modified in source code if needed)

## Technical Details:
- Built with raylib graphics library
- Implements Tideman ranked pairs algorithm
- Real-time cycle detection for fair elections
- File-based persistence for reliability

---
**Note**: This system is designed for secure, fair elections using advanced voting theory algorithms.
