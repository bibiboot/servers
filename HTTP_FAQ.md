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

What is pipeline connection?
On a single persistent connection , without waiting for the result of the request made, another request is enqueued on the same connection.
This works only for persistent connection.
The responses must be returned back in the same order of the request.

If the content-length is dubious what to do
-------------------------------------------
If i am a caching proxy then dont cache it and just forward the response to the client and dont try to corrrect it.

What to do in case of abrubt Connection close?
-------------------------------------------
If the transaction which will lead to some damage then dont repeat. Otherwise try again. Even if the alot of request are in pipeline.

Pracautions to be followed when closing?
-------------------------------------------
1. First close your sending descriptor.
2. As soon as the sending descriptor is closed. An EOF will be send to the other side recieve which will close the reading descriptor of the other side.
3. The problem with closing the reading descriptor is that if the sender sends and find a closed connection then a "Connection reset by peer" is issued which will reach the sender and the buffer maintained by the sender which is not read yet will be cleared. Thereby damage done.
Solution: Graceful Close


What is graceful close?
----------------------
1. First close your output.
2. Wait for the other end to close their output. 
3. Once both have issued that they wont be sending any data. The connection can close completely.

5.
--------------------------

What if the url has directory?
------------------------------
If the conf has Directory Index then 
Directory Index index.html index.cgi  (Preference from left to right)
If this is not present and default is not disabled then all the listing of the directory is shown as html page.
To disable : Options -Indexes

How to map the dynamic resources?
--------------------------------
Application servers are all built on this.
SciptAlias /cgi-bin /home/dan/cgi-project ( Any path containing cgi-bin will be executed by program found in the location)
or 
AddHandler cgi-script .cgi ( any file ending with .cgi will be executed by the cgi-script )

6.
-----------------------

Difference b/w proxies and gateways?
----------------------------------
COnnect two computer and gateways are protocol converter
Example of gateway: HTTP/POP
Advantage of proxy: Transcoding means changing the body: Changing the language or converting the form of image like GIF to JPEG

Whhy is Etag used ?
Sometimed If-Modified-Since is not adequte. Like the data is touched.

What is no-store or no-cache in Cache-Control?
no-store means the proxy cache do not store it . It just forward the response.
no-cache means the proxy can store but not serve without revalidation from the origin server.

What is Cache-control: must-revalidate?
The cache must revalidate with the server before serving no matter what. Therefore no chance of stale being served.

What if cache-control is not their?
Then the cache wil calculate the expiry time using heuristic of modification date.

How does the refresh button of thr browser works?
The client can set Cache-Control diectives to achieve the refresh and reload.
Example: Cache-Control: max-stale=2s
         Cache-Control: only if it is cached 

How to cache control using html tag?
<META HTTP-EQUIV="Cache-control" CONTENT="no-cache">

Advitiser problem due to cache , how to fix it?
Use cache-control: no cache. 
Serve using CGI gateways that is dynamic content
Rewrite advitisement url on every request.

Examples of gateway?
1. HTTP---->FTP
2. SSL----->HTTP
3. HTTP---->Application server----->Program

How to know which gateway to go?
The browser has default gateway.

Its a gateway.
What are HTTPS/HTTP accelerator or reverse proxy?
They recieve the HTTPS request and decript it in to HTTP and send ahead the request in normal format.
They use sepcial hardware which efficietly decrypt faster.

What is a resource gateway?

Why tunnel?
Send non-http data through firewall which allow only web data

How to set up tunnel?
1. Send -----> CONNECT hostname:443 HTTP/1.1
               User-Agent: Firefox;
   This reaches a tunnel gateway which firther connects with the host on without tunnel. That is SSL connection.
2. Recieve <---- HTTP/1.1 200 Connection Established
3. Start sending encrypted data.

Are the tunnel secured.
As the tunnel is formed over normal http. Its not till the point of tunnel gateway.
Require Proxy-Authentication.

PART 3
--------------------------




