In Memory File Cache
Task List

Size of the cache comes from command line. DONE
.There are multiple readers and writers of items. Number of readers and writers comes
from Readers and Writers file which is passed to the program from command line.DONE
.Design an efficient mechanism to retrieve items that are cached.DONE
.Design and implement an efficient eviction mechanism when there is a cache miss.DONE
.Handle the case of dirty cache item, where a writer is modifying the item that is already
cached.DONE
.Your program should handle all corner cases and robust to failures. If it fails, it should fail
gracefully giving out meaningful failure messages.DONE

Compilation:
 

Execution:
The program will take 4 command line arguments and will be executed as:
cache <cache_size> readerfile writerfile itemfile

Details:
The project consists of An IMultiThreadReadWrite interface.
Inherited by Reader and Writer class with own Implementation of Start().
Reader creates appropriate thread for the number of Reader files in reader file and reads content. Handled using constructor for each thread.
This content is then used to fetch data from item file and stored in new reader.out file.
Writer creates appropriate thread for the number of Writer files in writer file and write the content to item file.  
Implementation of Mutex for obtaining locks for appropraite reads and writes.
Implementation of an lru cache class for the reader file where the cache is checked for content if not found then item file is read.
Handle cache miss as it leads to read from item file. 
Handling of uses cases for bad writes.
Include unit cases with data files for manipulation of Readers and Writers in data folder.

Files and function
IMultiThreadReadWriter.h - Interface defined for function shared by Reader and Writer Start();
main.cpp - contains main() which takes the arguments and creates the reader writer threads;
lru.cpp - contains functions for least recentlt used cache manipulation with GET,PUT,EXSISTS,SIZE;
multithread.h - contains a universal namespace consists of variable for data file queue's,mutex's;
reader.h - contains declaration for overriden Start(),GetPostion(),ProduceReaderOut();
reader.cpp -contains definition for overriden Start() GetPosition() to read the individual reader files for data content,ProduceReaderOut() to actually produce the new .out file with updated values from cache 
writer.h - contains declaration for overriden Start(),GetPostion()
writer.cpp -contains definition for overriden Start() GetPosition() to read the individual writer files for data content contain key value pair for writing in item_file