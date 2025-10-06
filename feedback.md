**10/5/2025**
* class definition style & standards:  first, member vars  none per line and do not forget to initialize them;  second functions: separate group of functions  by a blank line; either matching setter/getter pairs or list all setters back to back and list all getters back to back; start with a default c’tor, followed by  copy c’tor (if any), then other c’tors in the order of increased number of arguments, d’tor- right after c’tor(s), overloaded functions- list them back to back in the order of increased number of arguments;  all accessor/getter functions should be const; all functions with more than one statement should be normal (defined externally, outside of the class and below main()), no inline functions with more than one statement; initialize all member variables to appropriate default values at the time of definition; all member variables must be private; classes must provide a strong exception guarantee; must have default c’tor; implement Rule of Three when necessary
* To provide you with thorough feedback, your instructor reads your code line by line, sometimes multiple times. Jumping from file to file is too time-consuming. Unless noted otherwise, place your class definitions above the main() and all function definitions below main(), all in one file. While the industry standard involves multi-source file programs, we will use a single file format for these labs unless instructed otherwise.
* Posted instructions are not optional, and not following the instructions will result in a lower grade. It applies to all assignments in this course.
* search does not comply with the assignment description -10
* sort does not comply with the assignment description -10
* getter/accessor function(s) allow object state modification; const int foo() and int foo() const are not the same -5
* 197, 184 and like: if it's not 1 or 0 make it a constant -5
* 520-560 redundant; see assignment -5
* **exit() may not be used in this class  and will result in a grade of zero next time**
* 134 no validation; call to setAccount may result in invalid object; -5
* 134, 158, 172 do not comply with the assignment;  to ensure a strong exception guarantee, all setter functions must call set Account() and all member vars must be initialized at the time of definition; should have created a member functions to validate each piece of data and call them in setAccount();

* 508 should have used setw   to form the heading columns; the same way as in toSting() -1
* 421-439 – should have let it fall through; see assignment for an example -1
* account numbers do not comply with the assignment -1
* 316,317 – unnecessary function calls, how about accts[i].setAccount(…); see rectangle class example discussed during  the class-2

* 251  wasteful computational expense; what for? -1
* vague, poor prompts -1 
```text
   cout << "Cannot open file" << endl;  //NG which file?
```
* hard to read menu in the code; it should look similar to it appearance on a screen -1
```text
//e.g.poo
cout << "\n\nMenu:\n”
“1. Encrypt\n”
“2. Decrypt\n”
“3. Quit\n"<<endl;
```
* 50 and like: member variables and other vars and objects should be defined and initialized on separate lines, one per line -1
* 37 and like: hard to read; put  { } on separate lines -1
```text
string getFirstName() { 
return firstName; 
}
```
* #98 empty case in the switch statement; in case of QUIT -should let the user know program termination; in case of BACK_TO_MAIN – either remove  the case or let the user know -2
* 377 must check all files for opening; what if you're lost rights to a drive or  ther eis not enough memory? -2
* 497 should create a highly reusable function that takes an error message string as a parameter, clears the failed input, and outputs the error message  so it can be called anywhere where a user might enter a value of the wrong data type, including default case of the menu switch
* poor Id(s)  and/or inconsistent naming convention; ids should be self-documenting and as short as possible; use verbs for functions and nouns for variables; use camel-casing for variables (errorMessage) enum & const should be in upper case with words separated by “_”, e.g., MAX_TERMS, PRINT_RECORDS; pointer variables should start with p( if single)  or pp( if double pointer); flags isValid ( clearly what true would mean); if copying – e.g rhsQueue or scrQueue ; do not use IDs that are same as or very similar to C++  keywords and functions; no need to call an array “array”- it is obvious; vars should not be called value; -2
```text
void defaultMenuOption()
 copyFromAccount  //  too long; common name rhs ( right hand side) or source, sourceAcct
 ```

* why define an enum type in main(); all enums types should have a name ?  -1
* 114 should create const to store default values -2
* invalid accounts should not be stored, waste of space; see assignment -2

