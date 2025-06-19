


![flowchart](./flowchart.jpg "flowchart of the program")

test of tokens and make sure the eprogramme make the difference between no quotes, simple or double 
the logique with $ will come later 

csalamithome@penguin:~/Desktop/minishell/src/parsing$ ./a.out 
Token: [echo] | Quote Type: NO_QUOTE
Token: [>] | Quote Type: NO_QUOTE
Token: [hello world] | Quote Type: SINGLE_QUOTE
Token: [42 Málaga] | Quote Type: DOUBLE_QUOTE
Token: [test] | Quote Type: NO_QUOTE
csalamithome@penguin:~/Desktop/minishell/src/parsing$ 


como he tokanisado ahora los built ins fonctionna mejor 
 // test 

csalamithome@penguin:~/Desktop/minishell$ ./minishell 
minishell> /home/csalamithome/Desktop/minishell $ pwd
/home/csalamithome/Desktop/minishell
minishell> /home/csalamithome/Desktop/minishell $ echo "hello"
hello
minishell> /home/csalamithome/Desktop/minishell $ cd src/
minishell> /home/csalamithome/Desktop/minishell/src $ cd ..
minishell> /home/csalamithome/Desktop/minishell $ echo "normal echo"
normal echo
minishell> /home/csalamithome/Desktop/minishell $ echo -n "with no /n"
with no /nminishell> /home/csalamithome/Desktop/minishell $ pwd
/home/csalamithome/Desktop/minishell
minishell> /home/csalamithome/Desktop/minishell $ cd
minishell> /home/csalamithome $ pwd
/home/csalamithome
minishell> /home/csalamithome $ 

need to check ;leaks and also "" and '' 

csalamithome@penguin:~/Desktop/minishell$ valgrind ./minishell 
==9106== Memcheck, a memory error detector
==9106== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==9106== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
==9106== Command: ./minishell
==9106== 
minishell> /home/csalamithome/Desktop/minishell $ pwd
/home/csalamithome/Desktop/minishell
minishell> /home/csalamithome/Desktop/minishell $ cd src/
minishell> /home/csalamithome/Desktop/minishell/src $ cd ..
minishell> /home/csalamithome/Desktop/minishell $ echo "hello"
hello
minishell> /home/csalamithome/Desktop/minishell $ echo 'hello'
hello
minishell> /home/csalamithome/Desktop/minishell $ echo 'hello $USER'
hello csalamithome
minishell> /home/csalamithome/Desktop/minishell $ echo "hello $USER"
hello csalamithome
minishell> /home/csalamithome/Desktop/minishell $ 
exit
==9106== 
==9106== HEAP SUMMARY:
==9106==     in use at exit: 233,217 bytes in 292 blocks
==9106==   total heap usage: 692 allocs, 400 frees, 411,546 bytes allocated
==9106== 
==9106== LEAK SUMMARY:
==9106==    definitely lost: 240 bytes in 33 blocks
==9106==    indirectly lost: 0 bytes in 0 blocks
==9106==      possibly lost: 0 bytes in 0 blocks
==9106==    still reachable: 232,977 bytes in 259 blocks
==9106==         suppressed: 0 bytes in 0 blocks
==9106== Rerun with --leak-check=full to see details of leaked memory
==9106== 
==9106== For lists of detected and suppressed errors, rerun with: -s
==9106== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
csalamithome@penguin:~/Desktop/minishell$ 



FIXED

minishell> /home/csalamithome/Desktop/minishell $ echo "$USER"
csalamithome
minishell> /home/csalamithome/Desktop/minishell $ echo '$USER'
$USER
minishell> /home/csalamithome/Desktop/minishell $ 

