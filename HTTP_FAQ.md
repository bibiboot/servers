1.
--------------
What is proxies?
--------------
Proxies are intermediatries between server and client.
They direct the request to the real server. They also change the request.
Used in case of security and web content filtering in corporates.
Check for virus downloads.

What is cache?
--------------
Where popular pages are stored near the client.
They are special type of proxu server which has cache and record the data which pass through it. Hance server it later.

What is gateway?
--------------
A type of web server which connects the client to other application without the client knowing.
Used to convert HTTP traffic to other protocol.
Example : The ftp request is recieved using the http request but the data is send further using the ftp protocol.

What is Tunnel?
--------------
Special proxied which do blind relay. Used in case of HTTPS.
They are used to transfer non-HTTP data over http connection.

2.
-------------
What is URI?
URI consist of two parts URLS and URN.

What is URL?
-----------
Locating the file based on path.
The client has to encode the characters of urls which are unsafe so that the middle servers do not act weird.
URL: URL scheme + server location + resource path
URL: scheme://username:pwd@hostname:port/path;param?query#frag
frag is not passed to the server it is for the client to detect section of the response.
query is passed to the gateway application.

What is URN?
-----------
Locating the file based on name.

How is internationalization handled in URLs?
-------------------------------------------
The non-ASCI characaters are followed by escape character and % is added ,followed by the two hexadecimal digits that represent the ASCII code of the character in place of the original character.

What is URL disadvantes?
-----------------------
If the resource moves, the URL is useless.

3.
---------------
What is message consist of?
Message consist of Status line, Headers and Entity body.

What is the constraint on message?
---------------------------------
The startline and headers must be ASCII text and body can be binary or text or empty.

What is OPTIONS?
---------------
Determine which methods can operate over the server.
OPTIONS * HTTP/1.0 ------>
<---------------- Allow: GET, POST, HEAD
                  Content-length: 0

What are status code?
--------------------
100-199: Informational
200-299: Sucess
300-399: Redirection
400-499: Client error
500-599: Server error
If its outside the range then the meaning should e taken from the range.

401: Unauthorized
404: Not found

100: Continue
     The client must continue and the server will respond next onyl when the client sendsa request again.
     This is done when client wants to make sure of something that server approves of.
     Check before sending some large data which the server can not handle.

206: Partial Content

300: Mutliple choices
     For a given url, if the server has multiple resources then the server can offer them all for the client to choose.

301: Redirect
     The location field will have the new location address.
304: Not Modified

400: Bad Request
403: Forbidden

500: Internal Server Error
501: Not implemened
     Soem method not supported by the server.
502: Bad Gateway
     If its unable to connect to its parent gateway.
503: Service unavailable.
505: Http version not supported

What is Trailers?
It is a header which list the set of headers which will be following in the last during chunked transfer encoding.

What is Via:
The proxy though which it has gone through.

What is Referer?
Form which host the requets has generated.

What are the different types of Request headers?
Accept headers.
Conditional headers.
Request security headers. [Authorization. Cookie, Cookie2]

Read from the book Pae 73

4.
----------------------------

What is Performace issue with TCP?
1. TCP handshake
2. TCP slow start . Congestion control
3. Nagle algorithm for aggragation of data.
4. TIME_WAIT in case of closing. 

How to optimize some?
1. SYN
2. ACK-SYN
3. ACK and request packet.
3. Response

What is slow start?
Each time the packet is recieved. The sender gets more permission to send more number of packets.
It initially sends 2 and wait and if they are successfull then it increases the number.

In which case is paralle connection bad for the client ?
When the network bandwidth is less. The amount of time gets decreased and then their is no added advantage.
Normally clients opens 3-4 parallel connection due to resource constraint.

What is keep-alive http connection?
The older HTTP/1.0 to have persistent. This is done with Connection: Keep-Alive.
If the server is ready to keep alive the connection, then the server will respond back with the same header.
(Send by the server)
Connection: Keep-Alive
Keep-Alive: max=10; timeout=300;
In every request the client must send this. The cloent will know when the server is going to close the connection when he stops sending the header.

What is hop-by-hop header?
Connection is a hop-by-hop header. Its applied only on one hop.

What happens with dumb proxies relaying Connection header?
If the dumb proxy does npt understand the Connection header and it does not remove it from the request header to server. The client and server will be in keep alove mode. The proxy will wait for server to close the connection therefore hang and the proxy wont expect any more request on the same connection therefore it wil ignore the next request from the client. Therefore the client next request will timeout.

Solution to the above probelem?
Dont send the header with these titles.
Example: Connection , Proxy-Connection , Authnticate also form cache.
Solution is the sending of the Proxy-Connection.

Client ---->Proxy-Connection Dumb proxy: ---->Proxy-Connection Server
       <----  No header                  <----No header

Client ---->Proxy-Connection Cleverproxy: ---->Connection:Keep-Alive Server
       <----Connection keep-Alive         <----Connection:Keep-Alive

How is persistent connection managed in HTTP/1.1?
If any one doesnpot wants it pass Connection : close
To have persistent connection either send correct content-lenght or it must be transfer encoding type.

Is their any limit on the number of persistent connection?
The client can have maximum 2 persistent connection to a server.
The proxy can have 2N maximum connection if their are atmost N clients trying to access the 

