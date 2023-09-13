# Week 8
# 2/5/2021
# HTML, CSS, and JavaScript
# https://cs50.harvard.edu/x/2021/weeks/8/

Go from blinking prompt to something graphical. Web Programming.
2 protocols:
TCP/IP

TCP- need to do multiple things. TCP introduces port number. TCP also handles delivery. If data gets lost, TCP will retransmit as needed.

TCP/IP is adaptive- the same data won't always take the same route.

We will kind of abstract the actual internet away. It's now just a service we to which we have access.

Now, we will look at HTTP. We know HTTP already, of course, from URLs.
The web is just one layer on top of the internet. It's a service that uses the underlying plumming.
TCP/IP governs what goes outside the envelopes- HTTP governs what goes inside the envelops.
HTTP comes with 2 realy basic commands: GET and POST.

To request a cat, we write GET cat. It's how a browser requests from a server.

For example, https://www.example.com/
https -> s is for secure version of HTTP. Data between sites in encrypted somehow.
example.com -> the domain name. It's normally something dot somethingelse.
com -> the TLD, top level domain. The "type" of website. .com, .edu, .net, .org. Now there are thousands of TLD. There are almost no hard rules, except for .edu or .mil. Sometimes in other countries, they have their own.
www -> the hostname. Kinda just tells you it's a website, a webserver, not an email server, or file server. Visual cue to humans, and it's optional.

However, you usually go to
https://www.example.com/index.html
index.html is "implicit".

Sample HTTP requests, responses:
send request for a cat...

```
GET / HTTP/1.1
Host: www.example.com
...
```
HTTP/1.1 is just the version number
The Host is bc one company might have multiple websites on their server. Host helps it go to the right place.
```
GET /index.html HTTP/1.1
Host: www.example.com
...
```

We respond:
```
HTTP/1.1 200 OK
Content-Type: text/html
...
```
text/html is webpage
image/jpeg for jpeg. Also called MIME types.

It won't always be this simple...
```
GET / HTTP/1.1
HOST www.harvard.edu
```
Using chrome development tools, view-> developer-> developer tools
Any time you visit a webpage, there's not just one thing there. There could be dozens. The server may reply with dozens of envelopes.
All of this code, those are HTTP headers.

301 MOVED PERMANANTLY

We've of course seen 404.

500 Internal Server Error might be one that we'll start to experience soon. It means a bug in our Python code.

we will use curl -I

```bash
~/ $ curl -I http://safetyschool.org
HTTP/1.1 301 Moved Permanently
Server: Sun-ONE-Web-Server/6.1
Date: Mon, 08 Feb 2021 20:18:25 GMT
Content-length: 122
Content-type: text/html
Location: http://www.yale.edu
Connection: close
```
someone on the internet is paying for the domain safetyschool.org and just redirecting it to yale.edu

```bash
~/ $ curl -I harvardsucks.org
HTTP/1.1 301 Moved Permanently
Age: 239709
Date: Sat, 06 Feb 2021 01:44:31 GMT
Location: http://www.harvardsucks.org/
Server: Squarespace
Set-Cookie: crumb=BboXzDk5E7KMYjJlNmQ3ZmE1MDYyM2I0ODdhMWNkYjU4NzRlOTFk;Path=/
X-Contextid: eRBxLFii/56PvyqjP
```


```
GET /search?q=cats HTTP/1.1
Host: www.google.com
...
```
the ?q=cats is kind of like passing variables to code on web servers.

If we look a little deeper in the envelope, we can see the "webpage". It's not a programming language, it's a markup langugage

html has 2 things: tags and attributes

```html
<!DOCTYPE html>

<html lang="en">
    <head>
        <title>
            hello, title
        </title>
        <body>
            hello, body
        </body>
    </head>
</html>
```
the words like <this> are HTML tags. 
the lang="en" is a html attribute. You'd have to look at the documentation for the tags. 

The <title> and <body> tag are children of the <head> tag

HTML is basically a data structure for your computer. 

# before a word is unique identifier, i.e. #harvard, #yale
. before a word is a class

no symbol before word, it means the tag called a