HOMEWORK 3: CONNECT FOUR


NAME:  Arnav Pawar


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

ALAC tutoring
Steven

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 12


ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

insert (excluding checking for connected four) - O(n^2)

insert (including checking for connected four) - O(m*n^2)

numTokensInColum - O(1)

numTokensInRow - O(m)

numColumns - O(1)

numRows - O(1)

print - O(n^2)

clear - O(n)


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?

I used Valgrind to find a lot of the memory leaks. Unable to Read errors were caused from not setting my array of pointer to NULL which is mainly caused due to uninitialization. Conditional jump or move depends on uninitialised value were errors that were caused due to paths that were pointer that were not set to a value. When calling these memmory leaks were encountered. Many of my tests just consisted of this and I mainly tested unique situations by adding my own insert function calls. 


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)
- I made my "m_data"(InitPoin) an array pointer of size one instead of a string pointer. This may make its calls look confusing. 

