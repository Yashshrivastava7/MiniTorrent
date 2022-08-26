# Torrent Implementation
## Basics
### Stage 1:
* Try to copy a file using system calls(C/Cpp)
* Given: Source directory+file and destination directory
* First try with a text file
* Then try multimedia file
* example: `./copy.out <src> <dst>`
* example: `./copy.out /Users/yashshrivastava/Documents/abc.txt ./Folder/`
* Assume both directories exist

### Stage 2:
#### Stage 2a:
* Try to split a big file into small chunks of fixed size
* Syntax: `./split.out <filepath> <fixed size in MB> <current path>`
* Example: `./split.out image.jpg 10 .`
* Output Format: `image_1.part image_2.part .... image_N.part`
#### Stage 2b:
* Then try to merge the split files
* Syntax: `./merge.out <path to splitted files> <part prefix> <output path>`
* Example: `./merge.out /Users/SplitFiles/ image /Users/OutputFolder/MergedImage.jpg`


### Stage 3:
* Repeat Stage 1 but with sockets.
* Create a Server which serves the file
* Create a client that connects to the server and requests a particular file.
* Transfer the file from server to client in a chunked(split) manner.
* Flow 
 ```
 Client Requests Server -> Server Receives Request -> Server splits file -> Server sends chunks one by one -> Client receives these chunks and merges them -> Client has the final file now.
 ```
