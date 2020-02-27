import os 
import sys

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
fd.write("This is a new file.\n")
fd.close()

try:
    fd = open("new_file.txt", "r")
except IOError:
    print("ERROR: Failed to create file")
print(fd.read())
fd.close()

try:
    fd = open("new_file.txt", "r+")
except IOError:
    print("Failed to open file")

for line in fd:
    for word in line.split():
        if word == "new":
            break;

pos = fd.tell()
print(pos)



#g,k
try:
    print("file.txt     :   " + str(os.stat("file.txt")))
    print("new_file.txt :   " + str(os.stat("new_file.txt")))
    print()
except:
    print("ERROR: Failed to get file information")

#j
try:
    os.remove("new_file.txt")
    print("new_file.txt has been deleted")
except:
    print("Failed to remove new_file.txt")
