Which operating system is running on system?
uname -a

How will you bring a process in forground?
fg processid

How to know how many cpu?
cat /proc/cpuinfo

How do you find process which are running a particular file.
lsof filename

What is NOHUP?
This is added to disbale the SIGHUP signal for the given process.
The SIGHUP is issued by the kernel in case of logout. This was earlier used in case of hang up but now these says its used when virtual terminals are closed. 

How to know run time page size ?
sysconf(_SC_PAGESIZE);

What is core dump?
The main memory image of the program stored in a file in disk.

How is process kept?
Each process has an entry in the process table. Each entry is pointing to a table of file descriptors which has one entry per descriptors. The file descriptor table is pointitng to the file table where
 Read, Write , Execute Permission is stored. Current file offset. A pointer to the v-node table entry for the file. Current file size.

 Each open file has a v-node structure which contains information as to type of file which process are accessing it. it also contains the i-node of the file. 

What happens in dup?
The fd are pointing to the same file table.
1. Call dup()
2. fcntl(fd, FD_DUPFD, 0)
As dup(fd_src, fd_des) is equivalent to close(fd_dest) and fcntl(fd_src, FD_DUPFD, fd_dest)

What is buffered I/O?
When we write to file. Its actually being written in a buffer and is only copied to the disk when somebody else is asking for this buffer or we have to flush the buffer explicitly.

What is fcntl?
it changes the property of the file which is opened using fd.
When called with flag F_GETFLG. The int returned will have the status of the file and by operation & we can check if that bit is set or not. 
Example result_flag & O_NONBLOCK is not zero then its a NONBLOCK socket.

What is the other way to duplicate the file descriptor ?
int dup_fd = open("/dev/fd/0", O_RDWR)
The STDIN is duplicated.

What is 2>&1?
If their is no ampersand then it wil be read as file. 
Now its read as put all stderror to stdout.
>& is required to redirect to a stream.

What is > and >>
> Means send overwriting target
>> Means send appending the target

What is the difference between 
ls > file 2>&1 ------ A
ls 2>&1 > file -------B
A means 1-->file then 2 is pointing to what 1 is pointing to that is 2---->file
B means 2--->stdout as 1--->stdout then 1-->file
hence we see the stderr going to the output

What is block file?
Buffered I/O like disk drives.
In sizes of block I/O.

What is a charactecter file?
On characater at a time like the keyboard, virtual terminal.

What is S_ISSOCK?
They are macros

Where is the userid and groupid?
Its in the passwd file.

What is execute and read permission in directory?
Execute in a directory is also called the search bit as it lets u search through the directory.
Read lets you do the listing of the content of the directory.
Example: /usr/man/file/sample.txt
         I need execute permission in all to traverse through them.

What is setbuf?
To change a file from block buffer to another buffer
stderr is not buffered at all, as it has to be published ASAP.
stderr is always l
Write and Read function calls are not buffered. But the standard I/O is line buffered if connected to terminal otherwise
fully buffered.


What is process id 0 and process id 1?
(kernel based process)Swapper or Scheduler is process id 0.
(Not a kernel process, it is same like other process and it also runs in priveleege mode)Init is the process id 1.

Parent vs Child process.
The child process gets a copy of the parent data, heap and stack space. The parent and child share the text segment.
But now days we use COW. Which make sure that they have one copy only but with protection of readonly mode.
All file descriptors opened in the parent are duplictaed in the children.
File locks of parents are not inherited by the child
Pending alarms are also cleared from the child

How to stop waitpid from hanging?
Use flag = WNOHANG

How to prevent oneself from becoming Zombie?
Kill parent immediatelt and become child of init.

What is pthread_cancel?
Its like some other thread calls pthread_cancel for some other thread with threadid as parameter.
The effect is similar to calling pthread_exit.
The other thread can set their cancelable state to make it a pending call.
It will cancel at the cancellation point.

How to solve the problem of two thread reading from one file and lseek.
Use pread and pwrite. Atomic operation.

What is async-signal-safe?
Preventing certain peiece of code from being interrupted by the signal whose handler also deals with the same kind of code.
Example. The printf is using lock to print.
         The thread called printf and in middle of it .
         The signal was done and the handler is now calling printf.
         Inside printf, it will again try to acquire lock and go under deadlock.
         There are certain C functions which are async-signal-safe.
Solution: Mask certain piece of code. Masking is inexpensive.

What is pageout daemon?
Writes back dirty pages to disk slowly.
crond is also a daemon.

How you make sure their is only one instance of the daemon running?
Using lock file.
The pid of the cron is written to the file.

How to find daemons?
ps axj

How to create a daemon?
Kill the parent and keep the child alive.
Set session id so that it moves away from the terminal.
Close the stdin, stdout and stderrr.
Direct them to /dev/null
Change the current directory to root.
Make the SIG_HUP signal ignore, as it will be published in case of terminal closing down.

What is sockets and their types?
They are doors to the connections.
Type 1: AF_INET which means for internet
Type 2: AF_UNIX which means for inter process communication.

How to determine if the connection is closed?
The read will return exactly zero as on recieiving the SIN packet.
The write is not so sure.

How to determine the port number of a service?
getservbyname

Why does the netstat -a shows?
ESTABLISHED
TIME_WAIT: This side has closed the connection. Its waiting for the packets to come in order and completetly.
CLOSE_WAIT: The other side has closed the connection . Its waiting for the out of order packets.
LISTENING:
http://www4.cs.fau.de/Projects/JX/Projects/TCP/tcpstate.html

When do i use shutdown?
On closing socket, if the reference is still up. The socket is not closed. To make sure the socket is closed within that moment from both the ends
Both close and shutdown will make the host stop using the socket.
Shutdown makes both the socket destroy themselve. While the close only works on one.
In shutdown the recv returns 0.
Sending EOF can make read return 0.
  Generally the difference between close() and shutdown() is: close()
  closes the socket id for the process but the connection is still
  opened if another process shares this socket id.  The connection stays
  opened both for read and write, and sometimes this is very important.
  shutdown() breaks the connection for all processes sharing the socket
  id.  Those who try to read will detect EOF, and those who try to write
  will reseive SIGPIPE, possibly delayed while the kernel socket buffer
  will be filled.  Additionally, shutdown() has a second argument which
  denotes how to close the connection: 0 means to disable further
  reading, 1 to disable writing and 2 disables both.

What are TCP handshakes?
TCP handshake
-->SYN with sequence number X
<--SYN, ACK with sequence number X+1(Its X+1 denoting the next expected sequence number from the other host)
-->ACK
TCP close handshake
-->FIN, ACK
<--ACK

Which type of handshakes are retransmitted?
The SYN are retransmitted with exponential time.
The ACK are never retransmitted.
FIN is exactly like SYN.

What is SIGIO?
Its the way for asynchronous I/O.
The kernel tells the system that their is soemthing to read or write by issuing a signal. The problem with this is we have to call select if we have multiple sockets and its confusing to deal with.

What is the advantage of select?
Blocks only when their is nothing to read.
It has a timeout option.

WHat is the fix for the buffer problem during TCP?
Use TCP_NODELAY. As the nache's algorithm applies certain rules to see if the data is to be written to the system or not. i.e. to be flushed out of the buffer.

Wht happens when select returns but read returns 0.
When the connection closes on the other front. Then EOF is send which unblocks the select.

What is difference between poll and select?
Select is allowing a limited set of descriptors as it uses bit mask. The size is FD_SETSIZE. It can be changed by kernel but then kernel has to be recompiled.
The poll has user defined array so problem. But the poll is less portable.

What is TCP_NODELAY?
It prevents buffering by stopping the use of Nagle's algorithm thereby increasing network traffic.

Wht is different between read() and recv()?
Both are same with 0 as paramter.

Which signal is generated on read and write?
SIGPIPE is generated. But we tend to ignore it as the parameter for handler is the int signum only.

What is EINTR?
The system call was interrupted by the signal. Just check for them and loop back.
What is out of band data?
It means an urgent piece of data which has to be looked at ASAP. Its a TCP term.

What is SO_REUSEADDR?
If some port is already open but must be closed and we wish to acquire it. Then this paramter is used.

What does SO_LINGER do?
Its aborts the TCP connections instead of the close. Its passed to paramter in socket.

How to determine the clients address?
getpeername

What is the difference between SO_REUSEADDR and SO_REUSEPORT?
SO_REUSEADDR lets you use the address which is in TIME_WAIT.

