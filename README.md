# A File Transfer Protocol

This is an implementation of File Transfer Protocol (FTP), using the protocol stack TCP/IPv4 for the user interface to the standard FTP. The server program is a _concurrent server_ which handle multiple clients simultaneously. The FTP prompt with wait for next command until "bye" command is given. Following commands are recognized by this FTP program:

- `bye`<br/>
  Terminate the FTP session with the remote server and exit FTP. An EOF will also terminate the session and exit.<br/><br/>
- `cd` (remote-directory)<br/>
  Change the working directory on the remote machine to remote directory.<br/><br/>
- `cdup`<br/>
  Change the remote machine working directory to the parent of the current remote machine working directory.<br/><br/>
- `close`<br/>
  Terminate the FTP session with the remote server and return to the command interpreter.<br/><br/>
- `disconnect`<br/>
  A synonym for close.<br/><br/>
- `help [ command ]`<br/>
  Print an informative message about the meaning of command. If no argument is given, FTP prints a list of the known commands.<br/><br/>
- `lcd [ directory ]`<br/>
  Change the working directory on the local machine. If no directory is specified, the user’s home directory is used.<br/><br/>
- `open host [port]`<br/>
  Establish a connection to the specified host FTP server. An optional port number may be supplied, in which case, FTP will attempt to contact an FTP server at that port.<br/><br/>
- `pwd`<br/>
  Print the name of the current working directory on the remote machine.<br/><br/>
- `quit`<br/>
  A synonym for bye.<br/><br/>
- `? [ command ]`<br/>
  A synonym for help.<br/><br/>
