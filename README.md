# SecureKernel
An x86 based minimal kernel, with extra security based features.

***************************Important Read this section before you use******************************************


We have not yet mapped the functionality of the shift key to user input. If you wish to echo and redirect the output to a text file you need to 
	1.wrap the text you wish to echo int the `(accent) symbol, typically located above the tab button. 
	2.Use the left arrow right arrow key to get the '>' symbol.
	3. name of the file you would like to create.

We also have not yet implemented scrolling, move the text up, or resizing the screen. Therefore, it is very likely you text will run past the view of the window. If this happens just type clear and your cursor will be moved back to the top of the window


CD (Change Directory) can only change one level or file system at a time.
e.g. you can do cd home 
but CANNOT do cd home/camel
cd with no file specified will take you back to the root directory.

Lastly, deleting really messing with our current way of parsing instructions. So if you are entering a command and need to use backspace, expect this to break your command and receive a error that the command you entered was not valid. If you use delete expect to have to reenter that command.

****************************************************************************************************************

Implemented commands:

1. ls
2. ls -la
3. cd <directory_name>
4. mkdir <directory_name>
5. rmdir <directory_name>
6. echo <some text to echo back on the screen>
7. echo `some text to write to a file` > file_to_write_to
8. rm <file_to_remove>
9. help
10. clear
11. cat <file_name>
12 chmod ### <file_name>
	-for chmod each # represents a number between 0 and 7.


