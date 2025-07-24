Phobos Code Flow

This is a terminal-style space exploration game built with SFML for my final. Here's how the code works together:

Entry Point
main.cpp → Initializes SFML and calls PhobosGame::Phobos()

Core Game Flow
phobos.cpp → Main game controller that:
• Creates an 800x600 window with terminal styling
• Shows the main menu with options: New Game, Load Game, Exit
• Routes user choices to appropriate functions

User Interface
ui.cpp → Terminal-style menu system that:
• Loads retro VT323 font for terminal aesthetics
• Handles keyboard navigation (arrows/numpad)
• Renders green text with yellow selection cursor
• Manages menu titles and options

Game Actions
When user selects New Game:

1. story.cpp → Shows animated opening story scroll
2. Gets player name input with blinking cursor
3. save.cpp → Creates JSON save file with player data

When user selects Load Game:

1. save.cpp → Checks if save file exists
2. Loads player data from JSON
3. story.cpp → Displays save information or error message

Save System
save.cpp → JSON-based persistence that stores:
• Player name, level, health, location
• Game state and play time
• a JSON parser 
