File-categorizer

Organizing and categorizing files based on their extensions using c++.

Platform Requirements:

Platform: Cross-platform ( macOS, Linux)
Architectural Requirements:

Architecture: Object-Oriented
User Interface:

UI Type: Command-Line Tool
UI Features: The command-line interface allows users to input the directory path for file organization. After analyzing the directory, the tool categorizes files into different folders based on their extensions, creating new folders if necessary. Users receive feedback on the categorized files and the organization process.
Technology Stack:

Front-End: Command-Line Interface (Terminal)
Back-End: C++ for file manipulation and organization
Libraries: Standard C++ Library, dirent.h for directory traversal
Description:
The "FileCategorizer" command-line tool offers a powerful way to organize files within a directory by sorting them into categorized folders based on their extensions. Built with an object-oriented approach, this tool simplifies the process of decluttering your file system and enhancing file management.

Users provide a directory path through the command line. The tool then analyzes the files within the directory, extracting their extensions and associating them with predefined categories such as "Documents," "Audio," "Video," "Developer," and more. Files that match recognized extensions are moved to their respective categorized folders.

The code employs C++ for efficient file manipulation and organization, utilizing the Standard C++ Library for core functionality. Directory traversal is managed using the dirent.h library. The tool's modular structure allows for extensibility, making it easy to add new categories or modify existing ones.
