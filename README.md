# unix-shell-and-history-feature
This program serves as a shell interface. The shell interface accepts user commands and then executes a separate process. 
In response to the user, the command prompt is entered as follows, then the system waits for the user to enter the command 
and the entered command is executed.

*Step 1: osh>* <br/>
*Step 2: osh>ls*

The waiting relationship between parent and child can be two format. <br/> 1. The parent process waits for the child process to finish. <br/>
2. Parent and child work concurrently. This situation is valid when the "&" character is wrote at the end of the command. <br/>
  *Example: osh>ls &*

If the user enters the **exit** command in the command line entry, the application terminates. <br/>
The example command line looks like the following: <br/>
*osh>exit*

Another special feature of the project is that it supports a special **history** command. For example, the most commonly used 10 commands 
are listed together with usage numbers. <br/>
*osh>history*
