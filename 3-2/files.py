import os 
import sys
import re

"""
3.2.4 - File operations
"""
try:
    #a
    fd = open("file.txt", "r")
except IOError:
    print("ERROR: Failed to open file")

#b
print(fd.read())
#f
fd.close()

try:
    fd = open("file.txt", "a")
except IOError:
    print("ERROR: Failed to open file")

#i,m
fd.write("Modify this line in the next step.\n")
fd.write("This is the end of the document.\n")
fd.close()

try:
    fd = open("file.txt", "r")
except IOError:
    print("ERROR: Failed to open file")

print(fd.read())
fd.close()

#RESET

try:
    fd = open("file.txt", "w")
except IOError:
    print("ERROR: Failed to open file")
fd.write("The purpose of this file is to test I/O in Python.\n")
fd.close()

#CONTINUE

try:
    #h
    fd = open("new_file.txt", "w")
except IOError:
    print("ERROR: Failed to create file")

#d
fd.write("A line of text.\nThis is a new file.\nThis is the end.\n")
fd.close()

try:
    fd = open("new_file.txt", "r")
except IOError:
    print("ERROR: Failed to create file")
print(fd.read())
fd.close()

try:
    fd = open("new_file.txt", "r")
except IOError:
    print("Failed to open file")

pos = 0
for line in fd:
    for word in line.split():
        #print(word)
        if word == "new":
            fd.seek(0,2)
            break
        else:
            pos += len(word)+1
print()
print("Position at \'new\': " + str(pos))
print("Position at end of line: " + str(fd.tell()))
print()

fd.close()
fd = open("new_file.txt", "w")
fd.seek(pos)
fd.write(line.replace("new", "old"))
fd.close()

fd = open("new_file.txt", "r")
fd.seek(pos)
print(fd.readline())
print(fd.read())
print()

for result in str(os.stat("new_file.txt")).split():
    if result.__contains__('size'):
        size = re.search('\d+', result)
        size = size.group(0)
        break

#g,k
try:
    print("file.txt     :   " + str(os.stat("file.txt")))
    print("new_file.txt :   " + str(os.stat("new_file.txt")))
    print("size of new_file.txt is " + str(size) + " bytes.")
    print()
except:
    print("ERROR: Failed to get file information")

#j
try:
    os.remove("new_file.txt")
    print("new_file.txt has been deleted")
except:
    print("Failed to remove new_file.txt")
