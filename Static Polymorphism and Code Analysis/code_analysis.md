Ananlysing :
`https://github.com/KimaruThagna/OOP-Inheritance/blob/master/implement.cpp`

- Single Responsibility Pronciple
    What it did wrong: 
    lines 242-248
    The error checking if the life of vehcile is greater than 8 years should be added in another class. And DataInput should only be responsible for taking user input.
    
    What it did right:
    lines 232-287
    Created different instances for the DataInput function for class bike and truck. Since both truck and bike need different data inputs.

- Open Closed Principle
    What it did wrong:
    lines 57 - 136
    If in future the relationship between krarevenue and enginecapacity is changed the whole code had to be changed. This violates the closed principle where the class should be closed to modifications. 
   What it did right:
    file: classheader.h
    The child classes are open to extension. They are extended with different display functions.

- Liskov Substitution Principle
    what it did right:
    According to liskov principle superclass should be replacable by child without breaking the application. Here I can replace the vehicle by ordinary/truck/motobike. All the objects in the subclass behave the same way as the objects in superclass.

- Interface Segregation Principle
    What it did right:
    file: classheader.h
    The classes ordinary are segregating what functions it requires. Not all unnecessary functions are included in ordinary class or motorbike class.

- Dependency Inversion Principle
    what it did wrong:
    classheader.h
    vehicle should have been an abstract class for ordinary and truck to inherit. But rather it is dependednt on concrete implementations.

Improvements Summary:

- The vehicle should be an abstract class rather than based on concrete implementations.
- The error handling should be done in the sepaparte function and not in display function (to follow single responsibility principle).
- All the conditions are hardcoded for krarevenue which if modified in future might break the client. This could be fixed by creating a variable list and amking changes to those if needed in future.
